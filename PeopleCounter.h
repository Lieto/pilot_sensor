//
// Created by kuoppves on 24.7.2016.
//

#ifndef PILOT_SENSOR_PEOPLECOUNTER_H
#define PILOT_SENSOR_PEOPLECOUNTER_H


#include "DataCounter.h"

class PeopleCounter : virtual public DataCounter {
private:
    int m_observer_interval;
    int m_observed_total;
    int m_observed_total_prev;

public:
    PeopleCounter();
    ~PeopleCounter();

    std::string getDataAsJSON();

    void capture(CrowdSight *crowdSight);


};


#endif //PILOT_SENSOR_PEOPLECOUNTER_H
