//
// Created by kuoppves on  20.7.2016.
//

#ifndef KOE_PEOPLEDETECTOR_H
#define KOE_PEOPLEDETECTOR_H

#include <opencv2/opencv.hpp>

class PeopleDetector  {
public:
    std::vector<cv::Rect> m_detected_pedestrians;
    cv::HOGDescriptor m_hog;

    PeopleDetector();

    void process(const cv::Mat& frame);

};


#endif //KOE_PEOPLEDETECTOR_H
