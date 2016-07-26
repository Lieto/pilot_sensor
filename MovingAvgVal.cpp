//
// Created by kuoppves on 20.7.2016.
//

#include "MovingAvgVal.h"

void MovingAvgVal::addValue(float value) {

    if (m_index == AVERAGE_LENGTH) {
        m_index = 0;
        m_filled = true;
    }

    MovingAvgVal::m_valueArr[m_index] = value;
    m_index++;

}
void MovingAvgVal::printVals() {
    std::cout << "values: ";
    for (int i = 0; i < AVERAGE_LENGTH; i++) {
        std::cout << MovingAvgVal::m_valueArr[i] << ", ";
    }
    std::cout << std::endl;

}

void MovingAvgVal::calcValue() {
    float sum = 0;
    int endVal = AVERAGE_LENGTH;
    if (!m_filled)
        endVal = m_index;
    for (int i = 0; i < endVal; i++) {
        sum += m_valueArr[i];
    }

    m_value = sum / endVal;

}
float MovingAvgVal::getValue() {
    return m_value;

}
