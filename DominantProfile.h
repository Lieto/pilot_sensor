//
// Created by kuoppves on 24.7.2016.
//

#ifndef PILOT_SENSOR_DOMINANTPROFILE_H
#define PILOT_SENSOR_DOMINANTPROFILE_H


class DominantProfile {
public:
    int m_gender;
    int m_age_group;
    int m_number_of_people;

    DominantProfile() : m_gender(0), m_age_group(0), m_number_of_people(0) {}
    int getGender();
    int getAge();

};


#endif //PILOT_SENSOR_DOMINANTPROFILE_H
