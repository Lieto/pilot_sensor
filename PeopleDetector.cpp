//
// Created by kuoppves on 21.7.2016.
//

#include "PeopleDetector.h"

PeopleDetector::PeopleDetector() {
    m_hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}

void PeopleDetector::process(const cv::Mat& frame ) {

    m_hog.detectMultiScale(frame, m_detected_pedestrians, 0.0, cv::Size(8,8), cv::Size(0,0), 1.05, 4);

}
