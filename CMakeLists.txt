cmake_minimum_required(VERSION 3.5)
project(pilot_sensor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp  Application.cpp Application.h Parameters.cpp Parameters.h ROI.cpp ROI.h PreProcessor.cpp PreProcessor.h DetectedPerson.cpp DetectedPerson.h MovingAvgVal.cpp MovingAvgVal.h PeopleDetector.cpp PeopleDetector.h FaceDetector.cpp FaceDetector.h DominantProfile.cpp DominantProfile.h Visitor.cpp Visitor.h DataCounter.cpp DataCounter.h PeopleCounter.cpp PeopleCounter.h AverageVisitorCounter.cpp AverageVisitorCounter.h)

add_executable(pilot_sensor ${SOURCE_FILES})

find_package(OpenCV COMPONENTS core highgui imgproc objdetect REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(rapidjson/include)
target_link_libraries(pilot_sensor restclient-cpp ${Boost_LIBRARIES} ${OpenCV_LIBS} crowdsight)
