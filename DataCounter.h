//
// Created by kuoppves on 24.7.2016.
//

#ifndef PILOT_SENSOR_DATACOUNTER_H
#define PILOT_SENSOR_DATACOUNTER_H


#include <time.h>
#include <string>
#include <iostream>
#include <crowdsight.h>
#include "Visitor.h"

class DataCounter {
private:
    long m_interval;
    time_t m_last_sendtime;

    int m_unit_guid;

public:
    DataCounter(int send_interval);
    ~DataCounter();

    virtual std::string getDataAsJSON() = 0;
    virtual void capture(CrowdSight *crowdSight) = 0;
    time_t getLastSendTime() { return m_last_sendtime; }
    long getInterval() { return m_interval; }
    void resetSendTime() { time(&m_last_sendtime); }
    long getUnitGUID() { return m_unit_guid; }
    void setUnitGUID(long id) { m_unit_guid = id; }
    std::string asJSON(Visitor *visitor);

};


#endif //PILOT_SENSOR_DATACOUNTER_H
