//
// Created by kuoppves on 21.7.2016.
//

#ifndef KOE_FACEDETECTOR_H
#define KOE_FACEDETECTOR_H

#include "crowdsight.h"
#include "DetectedPerson.h"
#include "Parameters.h"
#include "AverageVisitorCounter.h"
#include <opencv2/opencv.hpp>
#include <restclient-cpp/restclient.h>

class FaceDetector  {
public:

    time_t m_frameTimestamp;
    time_t m_last_post;
    time_t m_last_react;

    CrowdSight *m_crowdSight;
    AverageVisitorCounter *m_counter;
    AverageVisitorCounter *m_react;
    string m_analytics_file;
    RestClient::headermap m_headers;

    std::map<long, DetectedPerson> m_detectedPeopleMap;

    bool isCloserTo(cv::Point origPoint, cv::Point comparePoint, cv::Point adPoint);

    FaceDetector(Parameters& parameters);
    FaceDetector(string datadir, string license, int dev);
    ~FaceDetector();
    //bool process(cv::Mat frame);
    bool process(cv::Mat frame, Parameters& paras, int frameNo, bool fileSource);
    void showSettings();
    void writeAnalyticsFile(int age, int gender);

};


#endif //KOE_FACEDETECTOR_H
