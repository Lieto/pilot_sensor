//
// Created by kuoppves on 18.7.2016.
//

#ifndef KOE_PREPROCESSOR_H
#define KOE_PREPROCESSOR_H

#include "ROI.h"
#include "Parameters.h"

class PreProcessor {
private:

    cv::Mat m_gray_frame;
    cv::Mat m_resized_frame;
    cv::Mat m_cropped_frame;


public:
    int m_convert_to_grayscale;
    int m_use_roi;

    double m_scale_width;
    double m_scale_height;
    ROI* m_roi;

    PreProcessor(int grayscale, double scale_width, double scale_height, ROI roi, int use_roi);
    PreProcessor(const Parameters& paras);

    cv::Mat Resize();
    cv::Mat ConvertToGrayScale();
    cv::Mat ClipWithROI(ROI roi);
    cv::Mat Process(const cv::Mat& frame);

};


#endif //KOE_PREPROCESSOR_H
