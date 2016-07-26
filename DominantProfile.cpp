//
// Created by kuoppves on 24.7.2016.
//

#include "DominantProfile.h"

int DominantProfile::getAge() {

    if (m_number_of_people == 0) {
        return 0;
    }

    switch (m_age_group) {
        case 1:
            return 25;
        case 2:
            return 40;
        case 3:
            return 60;
    }

    return 0;
}

int DominantProfile::getGender() {
    if (m_gender < 0)
        return -100;
    if (m_gender > 0)
        return 100;

    return 0;
}
