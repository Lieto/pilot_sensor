//
// Created by kuoppves on 20.7.2016.
//

#ifndef KOE_DETECTEDPERSON_H
#define KOE_DETECTEDPERSON_H

#include <opencv2/opencv.hpp>
#include "MovingAvgVal.h"


class DetectedPerson {

    MovingAvgVal m_age;
    MovingAvgVal m_gender;
    int m_detectionCount;
    bool m_detected = false;
    int m_detectionFrameNo = -1;
    int m_lastObservedFrame = -1;
    time_t m_firstObservedTimestamp;
    time_t m_lastObserved;

    bool m_sent = false;
    cv::Point m_gaze;
    int m_crowdSightID;
    int m_attentionSpan = 0;

private:

    int m_personId;

public:

    static int m_idCounter;

    time_t getLastObserved() const {
        return m_lastObserved;
    }

    void setLastObserved(time_t lastObserved) {
        m_lastObserved = lastObserved;
    }

    int getPersonId() const {
        return m_personId;
    }

    void setPersonId() {
        m_personId = m_idCounter++;
    }

    int getCrowdSightID() const {
        return m_crowdSightID;
    }

    void setCrowdSightID(int id) {
        m_crowdSightID = id;
    }

    float getGender() {
        m_gender.calcValue();
        return   m_gender.getValue();
    }

    std::string getGenderString() {
        m_gender.calcValue();
        return   ((m_gender.getValue())<0 ?"mies":"nainen");
    }

    float getAge() {
        m_age.calcValue();
        return m_age.getValue();
    }

    void addAge(int age) {
        m_age.addValue(age) ;
    }

    void addGender(float gender) {
        m_gender.addValue(gender) ;
    }

    void incrementDetectionCount() {
        m_detectionCount++;
    }

    int getDetectionCount() const {
        return m_detectionCount;
    }

    void setDetectionCount(int detectionCount) {
        m_detectionCount = detectionCount;
    }

    bool getDetected() const {
        return m_detected;
    }

    void setDetected(bool detected) {
        m_detected = detected;
    }

    time_t getFirstObservedTimestamp() const {
        return m_firstObservedTimestamp;
    }

    void setFirstObservedTimestamp(time_t detectionTimestamp) {
        m_firstObservedTimestamp = detectionTimestamp;
    }


    bool isSent() const {
        return m_sent;
    }

    void setSent(bool sent) {
        m_sent = sent;
    }


    const cv::Point &getGaze() const {
        return m_gaze;
    }

    void setGaze(const cv::Point &gaze) {
        m_gaze = gaze;
    }

    int getDetectionFrameNo() const {
        return m_detectionFrameNo;
    }

    void setDetectionFrameNo(int detectionFrameNo) {
        m_detectionFrameNo = detectionFrameNo;
    }


    int getAttentionSpan() const {
        return m_attentionSpan;
    }

    void setAttentionSpan(int attentionSpan) {
        m_attentionSpan = attentionSpan;
    }

    void setLastObservedFrame(int i) {
        m_lastObservedFrame = i;
    }


    int getLastObservedFrame() const {
        return m_lastObservedFrame;
    }




};


#endif //KOE_DETECTEDPERSON_H
