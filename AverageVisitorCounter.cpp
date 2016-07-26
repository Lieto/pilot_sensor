//
// Created by kuoppves on 24.7.2016.
//

#include "AverageVisitorCounter.h"

using namespace std;

AverageVisitorCounter::AverageVisitorCounter() : AverageVisitorCounter(86400){

}

AverageVisitorCounter::AverageVisitorCounter(int observationDeprecationTime) : DataCounter(30), m_observation_deprecationtime(observationDeprecationTime) {

}

std::map<long, Visitor> AverageVisitorCounter::getVisitormap() {

    return m_visitormap;

}
void AverageVisitorCounter::capture(CrowdSight *crowdSight) {

    vector<Person> people;
    crowdSight->getCurrentPeople(people);

    vector<Person>::iterator it;

    for (it = people.begin(); it < people.end(); it++) {
        map<long, Visitor>::iterator vit;
        vit = m_visitormap.find(it->getID());

        if (vit != m_visitormap.end()) {
            vit->second.m_sample_count++;
            vit->second.m_age += it->getAge();
            vit->second.m_gender += it->getGender();
            vit->second.m_happiness += it->getEmotions()[0];
            vit->second.m_surprised += it->getEmotions()[1];
            vit->second.m_angry += it->getEmotions()[2];
            vit->second.m_disgusted += it->getEmotions()[3];
            vit->second.m_afraid += it->getEmotions()[4];
            vit->second.m_sad += it->getEmotions()[5];
            vit->second.m_mood += it->getEmotions()[6];

            for (auto const& rgba : it->getClothingColors()) {
                uint32_t rgb = ((rgba[0] & 0x0ff) << 16) | ((rgba[1] & 0x0ff) << 8) | (rgba[2] & 0x0ff);
                vit->second.m_colors.push_back(rgb);
            }

            vit->second.m_attention_span = it->getAttentionSpan();
            time(&(vit->second.m_last_observed));
        } else {
            Visitor newVisitor;
            newVisitor.m_ID = it->getID();
            cerr << "Pilot Sensor :: New visitor ID: " << newVisitor.m_ID << std::endl;
            m_visitormap[newVisitor.m_ID] = newVisitor;
        }
    }

}


void AverageVisitorCounter::calculateAverageVisitor(Visitor *avg) {

    map<long, Visitor>::iterator it;

    for (it = m_visitormap.begin(); it != m_visitormap.end(); it++) {
        if (it->second.getSampleCount() > m_react_frames_threshold) {
            avg->m_age += it->second.getAge();
            avg->m_gender += it->second.getGender();
            avg->m_happiness += it->second.getHappiness();
            avg->m_surprised += it->second.getSurprised();
            avg->m_angry += it->second.getAngry();
            avg->m_disgusted += it->second.getDisgusted();
            avg->m_afraid += it->second.getAfraid();
            avg->m_sad += it->second.getSad();
            avg->m_mood += it->second.getMood();
            avg->m_attention_span += it->second.getAttentionSpan();
            avg->m_sample_count++;
        }
    }
}

void AverageVisitorCounter::getDominantProfile(DominantProfile *profile) {

    map<long, Visitor>::iterator it;
    int gender = 0;

    int age_cnt[4] = {0, 0, 0, 0};

    for (it = m_visitormap.begin(); it != m_visitormap.end(); it++) {
        if (it->second.getSampleCount() > m_react_frames_threshold) {
            profile->m_number_of_people++;

            if (it->second.getAge() >= 18) {
                if (it->second.getAge() < 30) {
                    age_cnt[1]++;
                } else if (it->second.getAge() < 53) {
                    age_cnt[2]++;
                } else {
                    age_cnt[3]++;
                }
            }

            if (it->second.getGender() > 0) {
                gender++;
            } else if (it->second.getGender() < 0) {
                gender--;
            }
        }
    }

    profile->m_gender = gender;

    int ageGroup = 0;
    int numberOfGroups = 4;

    cout << "Gender: " << gender << " , Age groups: " << age_cnt[1] << "," << age_cnt[2] << "," << age_cnt[3] << endl;

    for (int i = 0; i < numberOfGroups - 1; i++) {
        if (age_cnt[ageGroup] < age_cnt[i])
            ageGroup = i;
    }

    profile->m_age_group = ageGroup;

}

void AverageVisitorCounter::removeDeprecatedObservations() {

    map<long, Visitor>::iterator vit;
    vit = m_visitormap.begin();
    time_t  ctime;
    time(&ctime);

    while (vit != m_visitormap.end()) {
        if (difftime(ctime, vit->second.getLastObserved()) > m_observation_deprecationtime) {
            m_visitormap.erase(vit++);
        } else {
            vit++;
        }
    }
}

void AverageVisitorCounter::removeSentObservations() {

    map<long, Visitor>::iterator vit;
    vit = m_visitormap.begin();
    time_t ctime;
    time(&ctime);

    while (vit != m_visitormap.end()) {
        if (vit->second.m_is_sent) {
            m_visitormap.erase(vit++);
        } else {
            vit++;
        }
    }
}

std::string AverageVisitorCounter::getDataAsJSON() {

    std::string returnValue = "";
    time_t  ctime;
    time(&ctime);
    double diff = difftime(ctime, getLastSendTime());

    removeDeprecatedObservations();

    if (diff > getInterval()) {

        resetSendTime();
        Visitor *avg = new Visitor();
        calculateAverageVisitor(avg);

        returnValue = asJSON(avg);
        delete avg;
    }

    return returnValue;
}

std::string AverageVisitorCounter::getIndividualDataAsJSON() {

    int cnt = 0;
    time_t ctime;
    time(&ctime);
    double diff = difftime(ctime, getLastSendTime());

    std::stringstream str;
    std::map<long, Visitor>::iterator vit;
    vit = m_visitormap.begin();

    while (vit != m_visitormap.end()) {
        if (difftime(ctime, vit->second.getLastObserved()) > m_observation_countinterval && !vit->second.m_is_sent) {
            if (cnt == 0) {
                str << "[";
            } else if (cnt > 0) {
                str << " , ";
            }
            vit->second.m_is_sent = true;
            str << asJSON(&vit->second);
            cnt++;
        } else {
            vit++;
        }
    }

    if (cnt > 0) str << "]";

    removeDeprecatedObservations();

    return  str.str();
}
