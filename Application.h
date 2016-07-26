//
// Created by kuoppves on 5.7.2016.
//

#ifndef KOE_DETECTOR_H
#define KOE_DETECTOR_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <fstream>
#include "Parameters.h"
#include "PreProcessor.h"
#include "DetectedPerson.h"
#include "PeopleDetector.h"
#include "FaceDetector.h"
#include <crowdsight.h>
#include <csignal>

namespace VisualizationColor
{
    // Some color constants
    const cv::Scalar KCOLOR_GREEN_1 ( 0x10, 0xaa, 0x10 );
    const cv::Scalar KCOLOR_RED_1   ( 0x00, 0x00, 0xff );
    const cv::Scalar KCOLOR_BLACK_1 ( 0x00, 0x00, 0x00 );
}



using namespace cv;
namespace vcolor = VisualizationColor;

class Application {

public:
    // Parameters to run detector (command-line at the moment, settings-file in the future ?)
    Parameters *m_parameters;
    PreProcessor *m_preprocessor;

    // OPenCV object
    cv::VideoCapture m_videoCapture;
    cv::Mat m_original_frame;
    cv::Mat m_preprocessed_frame;
    cv::Mat m_gray_frame;
    cv::Mat m_resized_frame;
    cv::Mat m_cropped_frame;
    string m_window_name;
    bool m_fileSource;
    int m_skip_frames;
    int m_frameNo;
    //std::vector<cv::Rect> m_detected_pedestrians;
    //cv::HOGDescriptor m_hog;
    PeopleDetector* m_peopledetector;
    FaceDetector* m_facedetector;
    std::ofstream m_resultfile;
    int m_convert_to_grayscale;
    int m_use_roi;
    double m_scale_width = m_parameters->m_scale_factor;
    double m_scale_height = m_parameters->m_scale_factor;
    ROI* m_roi;
    //CrowdSight *m_crowdSight;
    //std::map<long, DetectedPerson> m_detectedPeopleMap;

    time_t m_frameTimestamp;
    bool m_status;
    sig_atomic_t m_stop;

public:
    Application(int argc, char** argv);
    ~Application();

    bool Init();
    void InitVideoSource();
    bool InitDetectors();
    void InitPreProcessor();
    void Run();
    bool ReadFrame();
    void Update();
    void Display();
    void WriteResults();
    bool FaceDetecting();
    void inthand(int signum);

    Parameters getParameters();
    cv::Mat preProcess(cv::Mat& frame);
    bool isCloserTo(cv::Point origPoint, cv::Point comparePoint, cv::Point adPoint);

};


#endif //KOE_DETECTOR_H
