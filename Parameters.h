//
// Created by kuoppves on 5.7.2016.
//

#ifndef KOE_PARAMETERS_H
#define KOE_PARAMETERS_H

#include <string>
#include <boost/program_options/options_description.hpp>

using namespace std;
namespace po = boost::program_options;

class Parameters {

public:

    string m_license;
    string m_url;
    string m_datadir;
    string m_device_id;
    int m_input_camera;
    int m_frame_width;
    int m_frame_height;
    int m_debug_images;
    double m_framerate;
    double m_post_interval;
    int m_observation_count_interval;
    int m_observation_deprecation_time;
    int m_react_frames_threshold;
    int m_react_observation_deprecation_time;
    int m_unit_guid;
    int m_developer_mode;
    string m_input_file;
    string m_input_stream;
    string m_analytics_output_file;

    string m_csvfilename;

    int m_display;
    double m_scale_factor;
    double m_desired_frame_rate;

    int m_use_grayscale;
    int m_use_roi;

    double m_roi_center_x;
    double m_roi_center_y;
    double m_roi_width;
    double m_roi_height;

    int m_ad_point_x;
    int m_ad_point_y;

    int m_start_second;
    int m_detection_count;
    int m_use_people_detector;

public:

    Parameters();

    int parse_from_command_line(int argc, char** argv);

};


#endif //KOE_PARAMETERS_H
