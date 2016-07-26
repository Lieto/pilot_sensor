//
// Created by kuoppves on 5.7.2016.
//

#include "ROI.h"

/*
ROI::ROI() {
    m_center = cv::Point2d(0, 0);
    m_size = cv::Size(0, 0);
}
*/
ROI::ROI(double relative_center_x, double relative_center_y, double relative_width, double relative_height, const cv::Mat& frame) {

    m_relative_center_x = relative_center_x;
    m_relative_center_y = relative_center_y;
    m_relative_width = relative_width;
    m_relative_height = relative_height;
    m_scaled_center_x = frame.cols * relative_center_x;
    m_scaled_center_y = frame.cols * relative_center_y;
    m_scaled_width = frame.cols*relative_width;
    m_scaled_height = frame.rows*relative_height;
    m_frame_width = frame.cols;
    m_frame_height = frame.rows;
}

ROI::ROI(double relative_center_x, double relative_center_y, double relative_width, double relative_height, int frame_width, int frame_height) {

    m_relative_center_x = relative_center_x;
    m_relative_center_y = relative_center_y;
    m_relative_width = relative_width;
    m_relative_height = relative_height;

    m_scaled_center_x = frame_width * relative_center_x;
    m_scaled_center_y = frame_height * relative_center_y;
    m_scaled_width = frame_width * relative_width;
    m_scaled_height = frame_width * relative_height;
    m_frame_width = frame_width;
    m_frame_height = frame_height;

}

cv::Size ROI::getSize() {
    cv::Size size(m_scaled_width, m_scaled_height);
    return size;
}
cv::Point2d ROI::getCenter() {
    cv::Point2d center(m_scaled_center_x, m_scaled_center_y);
    return center;
}
