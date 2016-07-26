//
// Created by kuoppves on 5.7.2016.
//
#include "PreProcessor.h"
#include "Application.h"
#include <boost/timer.hpp>
#include "PeopleDetector.h"
#include <string>
#include <csignal>

Application::Application(int argc, char **argv) {

    m_parameters = new Parameters();
    m_parameters->parse_from_command_line(argc, argv);
    m_average_time_per_frame = 0;

 }

Application::~Application() {
    if (m_parameters != 0) delete m_parameters;
    if (m_facedetector != 0) delete m_facedetector;
    if (m_peopledetector != 0) delete m_peopledetector;
}

bool Application::Init()
{
    cerr << "Initializing sensor...." << endl;

    // Init source
    InitVideoSource();
    m_frameNo = 0;

    // Init preprocessor
    InitPreProcessor();

    // Init detectors
    InitDetectors();

    cerr << "Unit GUID: " << m_parameters->m_unit_guid << endl;
    cerr << "Mode: " << m_parameters->m_developer_mode << endl;
    cerr << "Postback Url: " << m_parameters->m_url << endl;
    cerr << "Post interval: " << m_parameters->m_post_interval << endl;
    cerr << "License: " << m_parameters->m_license << endl;
    cerr << "Camera #: " << m_parameters->m_input_camera << endl;
    cerr << "Reaction sample threshold: " << m_parameters->m_react_frames_threshold << endl;
    cerr << "Reaction sample deprecation: " << m_parameters->m_react_observation_deprecation_time << endl;
    cerr << "Resolution: " << m_parameters->m_frame_width << " x " << m_parameters->m_frame_height << endl;

    return true;

}
bool Application::InitDetectors()
{
    m_peopledetector = new PeopleDetector();
    m_facedetector = new FaceDetector(*m_parameters);

    if (m_parameters->m_use_people_detector == 1) {
        m_peopledetector = new PeopleDetector();
    }


    if (m_parameters->m_developer_mode == 1) {
        m_facedetector->showSettings();
        //std::cout << "detector type: " << m_facedetector->m_crowdSight->getFaceDetector() << std::endl;
    }

    return true;

}
void Application::InitVideoSource()
{
    m_fileSource = false;

    if (!m_parameters->m_input_file.empty()) {
        cout << "clip file " << m_parameters->m_input_file << endl;
        m_fileSource = true;
        m_videoCapture.open(m_parameters->m_input_file);
        m_parameters->m_framerate = m_videoCapture.get(CV_CAP_PROP_FPS);
        m_parameters->m_frame_width = m_videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
        m_parameters->m_frame_height = m_videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);

        cout << "Original frame rate: " << m_parameters->m_framerate << endl;
        cout << "Frame width: " << m_parameters->m_frame_width << endl;
        cout << "Frame height: " << m_parameters->m_frame_height << endl;
    } else if (!m_parameters->m_input_stream.empty()) {
        m_videoCapture.open(m_parameters->m_input_stream);
    } else {
        cout << "cam" << endl;

        m_videoCapture.open(m_parameters->m_input_camera);

        //m_parameters->m_frame_width = m_videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
        //m_parameters->m_frame_height = m_videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);

        cout << "Original frame rate: " << m_parameters->m_framerate << endl;
        cout << "Frame width: " << m_parameters->m_frame_width << endl;
        cout << "Frame height: " << m_parameters->m_frame_height << endl;


        m_videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, m_parameters->m_frame_width);
        m_videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, m_parameters->m_frame_height);
        m_videoCapture.set(CV_CAP_PROP_FPS, m_parameters->m_framerate);

    }

    m_window_name = "Detector";

    if (m_parameters->m_display != 0) {
        namedWindow(m_window_name, cv::WINDOW_AUTOSIZE);
    }

    m_skip_frames = int(m_parameters->m_framerate / m_parameters->m_desired_frame_rate);



}

void Application::InitPreProcessor() {

    m_preprocessor = new PreProcessor(*m_parameters);

}

void Application::Display() {

    if (m_parameters->m_use_people_detector == 1) {

        for (int i = 0; i < m_peopledetector->m_detected_pedestrians.size(); i++) {
            cv::rectangle(m_preprocessed_frame, m_peopledetector->m_detected_pedestrians[i], cv::Scalar(255));
        }
    }


    std::vector<Person> people;

    m_facedetector->m_crowdSight->getCurrentPeople(people);

    std::vector<Person>::iterator it;

    for (it = people.begin(); it < people.end(); it++) {


        std::cout << "Observed person " << it->getID() << " frame " << m_frameNo
        << " attention " << it->getAttentionSpan() <<" gaze " << it->getHeadGaze().x << " " << it->getHeadGaze().y
        << " position" << it->getRightEye() << " head Yaw "<< it->getHeadYaw()<< std::endl;


        cv::Point rightEyePosition = it->getRightEye();
        cv::Point leftEyePosition = it->getLeftEye();

        cv::circle(m_preprocessed_frame, rightEyePosition, 3, vcolor::KCOLOR_BLACK_1);
        cv::circle(m_preprocessed_frame, leftEyePosition, 3, vcolor::KCOLOR_BLACK_1);
        cv::rectangle(m_preprocessed_frame, it->getFaceRect(), vcolor::KCOLOR_BLACK_1);
        std::string idstring = std::to_string(it->getID());
        cv::putText( m_preprocessed_frame, idstring,  cv::Point(it->getFaceRect().x,it->getFaceRect().y)
                , cv::FONT_HERSHEY_PLAIN, 1, vcolor::KCOLOR_BLACK_1 );
        cv::Point stats_pos = cv::Point(75, 75);


    }

    imshow(m_window_name, m_preprocessed_frame);

}

bool Application::ReadFrame() {

    m_videoCapture >> m_original_frame;
    m_frameNo++;

    if (m_original_frame.empty()) {
        cout << "frame emtpy, stopping" << endl;
        m_videoCapture.release();
        return false;

    }

    return true;
}

bool Application::isCloserTo(Point origPoint, Point comparePoint, Point adPoint) {

    float distanceOrig = (adPoint.x - origPoint.x)^2 + (adPoint.y - origPoint.y )^2;
    float distanceComp = (adPoint.x - comparePoint.x)^2 + (adPoint.y - comparePoint.y )^2;
    return distanceComp < distanceOrig;
}
void signalHandler( int signum ) {

    cout << "Interrupt signal(" << signum << ") received. \n";

    exit(signum);
}



void Application::Run()
{
    boost::timer t;
    double frame_processing_time;
    double total_processing_time = 0.0;
    int frame_counter = 0;



    // Start loop to detections, tracking, etc....
    while (true) {


        t.restart();
        // Read frame, if empty frame, break
        if (!ReadFrame()) {
            //WriteResults();
            break;
        }


        // Skip frames depending on desired frame rate
        if ((m_frameNo % m_skip_frames) != 0) {
            continue;
        }

        frame_counter++;

        // Do resizing, grayscaling depending on parameters
        m_preprocessed_frame = m_preprocessor->Process(m_original_frame);

        if (m_parameters->m_use_people_detector) {
            m_peopledetector->process(m_preprocessed_frame);
        }

        m_facedetector->process(m_preprocessed_frame, *m_parameters, m_frameNo, m_fileSource);

        /*
        if (m_parameters->m_debug_images == 1 && !debugImage) {
           debugImage = true;
            writeDebugImage(&m_original_frame);
        }
         */

        frame_processing_time = t.elapsed();
        total_processing_time += frame_processing_time;
        cout << "Time to process frame: " << frame_processing_time << endl;


        // Average frame processing time
        cout << "Number of processed frames: " << frame_counter << endl;
        cout << "Total processing time: " << total_processing_time << endl;
        m_average_time_per_frame = total_processing_time / frame_counter;
        cout << "Average time per frame: " << m_average_time_per_frame << endl;

        // Draw detections on the frame
        if (m_parameters->m_display != 0) {

            Display();
                //qwaitKey(10);

        }

        if ('q' == waitKey(10)) {
            break;

        }

    }

    cout << "Average frame processing time: " << m_average_time_per_frame << endl;

    WriteResults();
    // Stop loop with interrupt


}


void Application::WriteResults() {

    m_resultfile.open(m_parameters->m_csvfilename, std::fstream::in | std::fstream::out | std::fstream::app);
    // Write video filename
    string csv_string = "";

    if (m_parameters->m_input_file != "") {
        csv_string += m_parameters->m_input_file + ";";
    } else {
        csv_string += to_string(m_parameters->m_input_camera) + ";";
    }

    // Write timestamp
    csv_string += to_string(time(0)) + ";";
    // Write original frame rate
    csv_string += to_string(m_parameters->m_framerate) + ";";
    // Write desired frame rate
    csv_string += to_string(m_parameters->m_desired_frame_rate) + ";";
    // Write scale factor
    csv_string += to_string(m_parameters->m_scale_factor) + ";";
    // Write average processing time per frame
    csv_string += to_string(m_average_time_per_frame) + ";";

    // Write detected people in clip
    std::vector<Person> people;

    m_facedetector->m_crowdSight->getCurrentPeople(people);
    csv_string += to_string(people.size()) + ";";
    m_resultfile << csv_string << endl;
    m_resultfile.close();
}

Parameters Application::getParameters() {

    return *m_parameters;
}