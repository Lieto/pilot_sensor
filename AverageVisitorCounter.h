//
// Created by kuoppves on 24.7.2016.
//s
//

#ifndef PILOT_SENSOR_AVERAGEVISITORCOUNTER_H
#define PILOT_SENSOR_AVERAGEVISITORCOUNTER_H
#include "DataCounter.h"
#include "Visitor.h"
#include "DominantProfile.h"
#include <map>
#include <crowdsight.h>

class AverageVisitorCounter : virtual public DataCounter {
private:
    std::map<long, Visitor> m_visitormap;

    int m_observation_deprecationtime;
    int m_observation_countinterval = 60;
    int m_react_frames_threshold = 1;

public:
    AverageVisitorCounter();
    AverageVisitorCounter(int observationDeprecationTime);
    ~AverageVisitorCounter() {};


    void calculateAverageVisitor(Visitor *avg);

    void getDominantProfile(DominantProfile *profile);

    std::string getDataAsJSON();

    std::string getIndividualDataAsJSON();

    void capture(CrowdSight *crowdSight);

    void setObservationDeprecationTime(int time) { m_observation_deprecationtime = time; }
    void setObservationCountInterval(int time) { m_observation_countinterval = time; }

    void removeDeprecatedObservations();

    void removeSentObservations();
    std::map<long, Visitor> getVisitormap();

    int getCurrentObservationsCount() { return m_visitormap.size(); }
    void setReactFrameThreshold(int t) { m_react_frames_threshold = t; }

};


#endif //PILOT_SENSOR_AVERAGEVISITORCOUNTER_H
