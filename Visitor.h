//
// Created by kuoppves on 24.7.2016.
//

#ifndef PILOT_SENSOR_VISITOR_H
#define PILOT_SENSOR_VISITOR_H


#include <time.h>
#include <vector>
#include <iostream>

using namespace std;

class Visitor {
public:
    long m_ID;

    double m_gender;
    double m_age;
    double m_happiness;
    double m_surprised;
    double m_angry;
    double m_disgusted;
    double m_afraid;
    double m_sad;

    double m_mood;
    double m_attention_span;

    time_t m_last_observed;
    time_t m_first_observed;

    int m_sample_count;

    bool m_is_sent;

    vector<uint32_t> m_colors;

    Visitor() : m_ID(0), m_gender(0), m_happiness(0), m_surprised(0), m_sad(0), m_angry(0), m_mood(0), m_attention_span(0),
                m_sample_count(0), m_is_sent(false) {
        time(&m_last_observed);
        time(&m_first_observed);
    }

    double getGender() { return m_sample_count == 0 ? m_gender : (m_gender / m_sample_count); }
    double getAge() { return  m_sample_count == 0 ? m_age : (m_age / m_sample_count); }
    double getHappiness() { return  m_sample_count == 0 ? m_happiness : (m_happiness / m_sample_count); }
    double getSurprised() { return  m_sample_count == 0 ? m_surprised : (m_surprised / m_sample_count); }
    double getSad() { return  m_sample_count == 0 ? m_sad : (m_sad / m_sample_count); }
    double getAngry() { return  m_sample_count == 0 ? m_angry : (m_angry / m_sample_count); }
    double getDisgusted() { return  m_sample_count == 0 ? m_disgusted : (m_disgusted / m_sample_count); }
    double getAfraid() { return  m_sample_count == 0 ? m_afraid : (m_afraid / m_sample_count); }
    double getMood() { return  m_sample_count == 0 ? m_mood : (m_mood / m_sample_count); }
    double getAttentionSpanAvg() { return  m_sample_count == 0 ? m_attention_span : (m_attention_span / m_sample_count); }
    double getAttentionSpan() { return m_attention_span; }
    time_t getLastObserved() { return m_last_observed; }
    time_t getFirstObserved() { return  m_first_observed; }
    int getSampleCount() { return m_sample_count; }
};


#endif //PILOT_SENSOR_VISITOR_H
