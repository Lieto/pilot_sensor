//
// Created by kuoppves on 21.7.2016.
//

#include "FaceDetector.h"
#include "restclient-cpp/restclient.h"
#include <fstream>

FaceDetector::FaceDetector(string datadir, string license, int dev) {

    if (dev == 0) {
        m_crowdSight = new CrowdSight(datadir, REDISTRIBUTION);
    } else {
        m_crowdSight = new CrowdSight(datadir, DEVELOPER);
    }

    if (!m_crowdSight->authenticate(license)) {
        delete m_crowdSight;
        m_crowdSight = NULL;
    }


}

FaceDetector::FaceDetector(Parameters& parameters) {

    if (parameters.m_developer_mode == 0) {
        m_crowdSight = new CrowdSight(parameters.m_datadir, REDISTRIBUTION);
    }
    else {
        m_crowdSight = new CrowdSight(parameters.m_datadir, DEVELOPER);
    }

    if (!m_crowdSight->authenticate(parameters.m_license)) {
        cerr << "Error:: Could not authenticate CrowdSight with key: " << parameters.m_license << std::endl;
        cerr << m_crowdSight->getErrorDescription() << std::endl;
        delete m_crowdSight;
        m_crowdSight = NULL;

    }

    m_headers["X-Device-ID"] = parameters.m_device_id;

    m_last_post = time(NULL);
    m_last_react = time(NULL);

    m_counter = new AverageVisitorCounter();
    m_react = new AverageVisitorCounter();

    // For gathering statistics
    m_counter->setObservationDeprecationTime(parameters.m_observation_deprecation_time);
    m_counter->setObservationCountInterval(parameters.m_observation_count_interval);
    m_counter->setUnitGUID(parameters.m_unit_guid);

    // For controlling the display content
    // Only remember visitors for short amount of time
    m_react->setObservationDeprecationTime(parameters.m_react_observation_deprecation_time);
    m_react->setReactFrameThreshold(parameters.m_react_frames_threshold);
    m_react->setUnitGUID(parameters.m_unit_guid);

    m_analytics_file = parameters.m_analytics_output_file;

    if (parameters.m_developer_mode == 1) {
        std::cout << "detector type: " << m_crowdSight->getFaceDetector() << std::endl;
    }
}

FaceDetector::~FaceDetector() {

    if (m_crowdSight != 0) delete m_crowdSight;
}

void FaceDetector::showSettings() {

    // Show CrowdSight settings
    cerr << "Smoothing: " << m_crowdSight->getSmoothing() << endl;
    cerr << "Recognition level: " << m_crowdSight->getRecognitionLevel() << endl;
    cerr << "Clothing: " << m_crowdSight->isClothingColorsUsed() << endl;
    cerr << "Clothing colors: " << m_crowdSight->getNumClothingColors() << endl;
    cerr << "Detection scale: " << m_crowdSight->getDetectionScale() << endl;
    cerr << "Face confidence: " << m_crowdSight->getFaceConfidence() << endl;
    cerr << "Face detector: " << m_crowdSight->getFaceDetector() << endl;
    cerr << "Max Face Size: " << m_crowdSight->getMaxFaceSize() << endl;
    cerr << "Min Face Size: " << m_crowdSight->getMinFaceSize() << endl;
    cerr << "Is age used: " <<  m_crowdSight->isAgeUsed() << endl;
    cerr << "Fast Detection: " << m_crowdSight->isFastDetectionUsed() << endl;
    cerr << "Gender used: " <<  m_crowdSight->isGenderUsed() << endl;
    cerr << "Head Pose Used: " << m_crowdSight->isHeadPoseUsed() << endl;
    cerr << "Tracking used: " << m_crowdSight->isTrackingUsed()  << endl;
    cerr << "Clothing Color Used: " << m_crowdSight->isClothingColorsUsed() << endl;
    cerr << "Emotion Used: " << m_crowdSight->isEmotionsUsed() << endl;

}

bool FaceDetector::isCloserTo(cv::Point origPoint, cv::Point comparePoint, cv::Point adPoint) {

    float distanceOrig = (adPoint.x - origPoint.x)^2 + (adPoint.y - origPoint.y )^2;
    float distanceComp = (adPoint.x - comparePoint.x)^2 + (adPoint.y - comparePoint.y )^2;
    return distanceComp < distanceOrig;
}


void FaceDetector::writeAnalyticsFile(int age, int gender) {

    std::ofstream file;
    file.open(m_analytics_file, ios::out | ios::trunc);

    if (file.is_open()) {
        file << gender << ";" << age << std::endl;
    } else {
        cerr << "Failed to open: " << m_analytics_file << std::endl;
    }

    file.close();

}


/*
void FaceDetector::writeAnalyticsFile(int age, int gender) {

    std::ofstream file;

    file.open(m_analytics_file, std::fstream::in | std::fstream::out | std::fstream::app);

    if (file.is_open()) {
        file << gender << ";" << age << std::endl;
    } else {
        cerr << "Failed to open: " << m_analytics_file << std::endl;
    }

    file.flush();

    file.close();

}
 */

bool  FaceDetector::process(cv::Mat frame, Parameters& paras, int frameNo, bool fileSource) {

    m_frameTimestamp = time(0);

    if (!m_crowdSight->process(frame)) {
        std::cerr << "Failed to process frame: " << m_crowdSight->getErrorDescription() << std::endl;
        return false;
    }

    m_counter->capture(m_crowdSight);
    m_react->capture(m_crowdSight);

    time_t now = time(0);

    if (difftime(now, m_last_react) > 0) {

        cout << "React people: " << m_react->getCurrentObservationsCount() << endl;
        Visitor v;
        m_react->removeDeprecatedObservations();
        m_react->calculateAverageVisitor(&v);

        DominantProfile profile;
        m_react->getDominantProfile(&profile);

        if (profile.m_number_of_people > 0 && profile.getGender() != 0 && profile.getAge() != 0) {
            writeAnalyticsFile(profile.getAge(), profile.getGender());
        } else {
            writeAnalyticsFile(0 ,0);
        }

        m_last_react = now;
    }

    if (difftime(now, m_last_post) > paras.m_post_interval) {
        std::string str = m_counter->getIndividualDataAsJSON();

        if (str.length() > 0) {
            if (paras.m_url.compare("DEBUG") == 0) {
                cout << "DEBUG: " << str << std::endl;
            } else {
                RestClient::response r = RestClient::post(paras.m_url, "application/json", str, m_headers);
                if (r.code != 200) {
                    std::cerr << "POST failed, code " << r.code << std::endl;
                } else {
                    std::cout << "Sent: " << str << std::endl;
                }
            }
        }

        m_last_post = now;
    }

}