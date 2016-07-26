//
// Created by kuoppves on 24.7.2016.
//

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include "PeopleCounter.h"


using namespace rapidjson;
using namespace std;

PeopleCounter::PeopleCounter() : DataCounter(5) {

    m_observer_interval = 0;
    m_observed_total = 0;
    m_observed_total_prev = 0;

}

PeopleCounter::~PeopleCounter() {

}

std::string PeopleCounter::getDataAsJSON() {

    time_t ctime;
    time(&ctime);
    double diff = difftime(ctime, getLastSendTime());

    if (diff > getInterval()) {

        resetSendTime();

        m_observer_interval = m_observed_total - m_observed_total_prev;
        m_observed_total_prev = m_observed_total;

        std::cout << "Observed: " << m_observed_total << std::endl;

        StringBuffer s;

        Writer<StringBuffer> writer(s);

        writer.StartObject();

        writer.String("unitGUID");
        writer.Int64(getUnitGUID());

        writer.String("timestamp");
        writer.Int64(getLastSendTime());

        writer.String("observedInterval");
        writer.Int64(m_observer_interval);

        writer.String("observedPeopleTotal");
        writer.Int64(m_observed_total);

        writer.EndObject();

        return s.GetString();

    }

    return "";
}


void PeopleCounter::capture(CrowdSight *crowdSight) {

    vector<Person> people;
    crowdSight->getCurrentPeople(people);
    vector<Person>::iterator it;

    m_observed_total = crowdSight->getPeopleCount();

    for (it = people.begin(); it < people.end(); it++) {

    }
}