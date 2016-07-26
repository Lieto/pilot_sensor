//
// Created by kuoppves on 5.7.2016.
//

#ifndef KOE_ROI_H
#define KOE_ROI_H

#include <opencv2/opencv.hpp>

class ROI {

private:

    //cv::Point2d m_center;
    //cv::Size m_size;
    double m_scaled_center_x;
    double m_scaled_center_y;
    double m_scaled_width;
    double m_scaled_height;


public:

    double m_relative_center_x{0.5};
    double m_relative_center_y{0.5};
    double m_relative_width{0.5};
    double m_relative_height{0.5};
    double m_frame_width{512};
    double m_frame_height{512};

    ROI(double relative_center_x, double relative_center_y, double relative_width, double relative_height, const cv::Mat& frame);
    ROI(double relative_center_x, double relative_center_y, double relative_width, double relative_height, int frame_width, int frame_height);
    cv::Size getSize();
    cv::Point2d getCenter();
};


#endif //KOE_ROI_H
