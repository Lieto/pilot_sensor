//
// Created by kuoppves on 18.7.2016.
//
#include <iostream>
#include "PreProcessor.h"

using namespace std;


PreProcessor::PreProcessor(int grayscale, double scale_width, double scale_height, ROI roi, int use_roi) {

    m_scale_width = scale_width;
    m_scale_height = scale_height;
    m_convert_to_grayscale = grayscale;
    m_use_roi = use_roi;
    m_roi = new ROI(roi.m_relative_center_x, roi.m_relative_center_y, roi.m_relative_width, roi.m_relative_height, roi.m_frame_width, roi.m_frame_height);
    cout << roi.getCenter() << endl;
    cout << roi.getSize() << endl;

}

PreProcessor::PreProcessor(const Parameters& paras) {

    m_scale_width = paras.m_scale_factor;
    m_scale_height = paras.m_scale_factor;
    m_convert_to_grayscale = paras.m_use_grayscale;
    m_use_roi = paras.m_use_roi;
    m_roi = new ROI(paras.m_roi_center_x, paras.m_roi_center_y, paras.m_roi_width, paras.m_roi_height, paras.m_frame_width, paras.m_frame_height);
}


cv::Mat PreProcessor::Process(const cv::Mat& frame) {

    if (m_convert_to_grayscale == 1) {
        //cout << "We are here !" << endl;
        cv::cvtColor(frame, m_gray_frame, cv::COLOR_BGR2GRAY);
        cv::resize(m_gray_frame, m_resized_frame, cv::Size(), m_scale_width, m_scale_height, cv::INTER_AREA);
    } else {

        cv::resize(frame, m_resized_frame, cv::Size(), m_scale_width,
                   m_scale_height, cv::INTER_AREA);
    }

    if (m_use_roi == 1) {

        cout << "Center: " << m_roi->getCenter() << " Size: " << m_roi->getSize() << endl;

        ROI new_roi(m_roi->m_relative_center_x, m_roi->m_relative_center_y, m_roi->m_relative_width, m_roi->m_relative_height, m_resized_frame);

        //ROI new_roi(m_roi->m_scaled_center, m_roi->m_scaled_width, m_roi->m_scaled_height, m_resized_frame);

        //cv::Point2d point(0.5 , 0.5);
        //ROI new_roi(point, 0.5, 0.5, m_resized_frame);
        cout << m_roi->getCenter() << endl;
        cout << m_roi->getSize().width << endl;
        cout << m_roi->getSize().height << endl;
        cv::getRectSubPix(m_resized_frame, new_roi.getSize(), new_roi.getCenter(), m_cropped_frame);
        return m_cropped_frame;
    } else {
        return m_resized_frame;
    }

}


cv::Mat PreProcessor::Resize() {


}
cv::Mat PreProcessor::ConvertToGrayScale() {

}
cv::Mat PreProcessor::ClipWithROI(ROI roi) {

}

