//
// Created by kuoppves on 5.7.2016.
//
#include <iostream>
#include <boost/program_options.hpp>
#include "Parameters.h"

using namespace std;
namespace po = boost::program_options;

Parameters::Parameters() : m_input_file {"./koe.mp4" }
{

}

int Parameters::parse_from_command_line(int argc, char** argv) {

    po::options_description desc("Allowed Options");

    desc.add_options()
            ("help,h", "produce help message")
            ("url,U", po::value<string>()->default_value("http://localhost:8000/_api/samples"), "output POST URL")
            ("interval,i", po::value<double>()->default_value(60), "output POST interval in seconds")
            ("license,L", po::value<string>()->required(), "Crowdsight license code")
            ("datadir,D", po::value<string>()->default_value("/usr/local/crowdsight/data/"), "Crowdsight data directory")
            ("camera,C", po::value<int>()->default_value(1), "OpenCV camera number")
            ("stream", po::value<string>()->default_value(""), "RTSP stream URL")
            ("analytics", po::value<string>()->default_value("analytics.output"))
            ("debugImages,x", po::value<int>()->default_value(0), "Produce debug images")
            ("width,W", po::value<int>()->default_value(1024), "OpenCV frame width")
            ("height,H", po::value<int>()->default_value(768), "OpenCV frame height")
            ("framerate,F", po::value<double>()->default_value(25.000), "OpenCV camera frame rate")
            ("Unit_guid, I", po::value<int>()->default_value(-1), "Unique identifier for this installation")
            ("X-Device-ID,X", po::value<string>()->default_value(""), "X-Device-ID header for http")
            ("observation_count_interval,c", po::value<int>()->default_value(60), "Observation count threshold")
            ("observation_deprecation_time,d", po::value<int>()->default_value(60), "Observation deprecation threshold")
            ("react_frames_threshold,t", po::value<int>()->default_value(1), "Number of frames needed for reaction")
            ("react_observation_deprecation_time,r", po::value<int>()->default_value(60), "Time a single observation is remembered")
            ("dev,M", po::value<int>()->default_value(0), "Specify to run in development mode. Only works on authorized computers")
            ("display", po::value<int>()->default_value(0), "Set one if show frame window")
            ("roi", po::value<int>()->default_value(1), "Use ROI on frame")
            ("roi_center_x", po::value<double>()->default_value(0.5), "ROI center x")
            ("roi_center_y", po::value<double>()->default_value(0.5), "ROI center y")
            ("roi_width", po::value<double>()->default_value(0.5), "ROI width")
            ("roi_height", po::value<double>()->default_value(0.5), "ROI height")
            ("scale", po::value<double>()->default_value(1.0), "Set scaling factor to resize video frames")
            ("grayscale", po::value<int>()->default_value(0), "Use grayscale frames for detection")
            ("desired_frame_rate", po::value<double>()->default_value(5.0), "Set the desired frame rate (frames per second) for video")
            ("csvfilename", po::value<string>()->default_value("./results.csv"), "CSV filename to write results")
            ("filename,f", po::value<string>()->default_value(""), "Filename to go through")
            ("adX", po::value<int>()->default_value(0), "Gaze middlepoint x val")
            ("adY", po::value<int>()->default_value(0), "Gaze middlepoint y val")
            ("startsecond", po::value<int>()->default_value(0), "Clip's start second")
            ("use_people_detector", po::value<int>()->default_value(0), "Use people counting detector with face detector");


    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    m_input_file = vm["filename"].as<string>();
    m_csvfilename = vm["csvfilename"].as<string>();
    m_datadir = vm["datadir"].as<string>();
    m_developer_mode = vm["dev"].as<int>();
    m_license = vm["license"].as<string>();
    m_input_stream = vm["stream"].as<string>();
    m_input_camera = vm["camera"].as<int>();
    m_frame_width = vm["width"].as<int>();
    m_frame_height = vm["height"].as<int>();
    m_framerate = vm["framerate"].as<double>();
    m_display = vm["display"].as<int>();
    m_scale_factor = vm["scale"].as<double>();
    m_desired_frame_rate = vm["desired_frame_rate"].as<double>();
    m_use_grayscale = vm["grayscale"].as<int>();
    m_use_roi = vm["roi"].as<int>();
    m_roi_center_x = vm["roi_center_x"].as<double>();
    m_roi_center_y = vm["roi_center_y"].as<double>();
    m_roi_height = vm["roi_width"].as<double>();
    m_roi_width = vm["roi_height"].as<double>();
    m_ad_point_x = vm["adX"].as<int>();
    m_ad_point_y = vm["adY"].as<int>();
    m_start_second = vm["startsecond"].as<int>();
    //m_detection_count = vm["detection_count"].as<int>();
    m_use_people_detector = vm["use_people_detector"].as<int>();
    m_post_interval = vm["interval"].as<double>();
    m_analytics_output_file = vm["analytics"].as<string>();
    m_debug_images = vm["debugImages"].as<int>();
    m_unit_guid = vm["Unit_guid"].as<int>();
    m_device_id = vm["X-Device-ID"].as<string>();
    m_observation_count_interval = vm["observation_count_interval"].as<int>();
    m_observation_deprecation_time = vm["observation_deprecation_time"].as<int>();
    m_react_frames_threshold = vm["react_frames_threshold"].as<int>();
    m_react_observation_deprecation_time = vm["react_observation_deprecation_time"].as<int>();


    if (vm.count("help")) {
        cout << desc << endl;
        return 1;
    }

    return 0;
}
