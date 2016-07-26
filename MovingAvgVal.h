//
// Created by kuoppves on 20.7.2016.
//

#ifndef KOE_MOVINGAVGVAL_H
#define KOE_MOVINGAVGVAL_H

#include <iostream>


class MovingAvgVal {

    static const int AVERAGE_LENGTH = 20;
    float m_value;
    float m_valueArr[AVERAGE_LENGTH];
    int m_index = 0;
    bool m_filled = false;

public:
    void addValue(float value);
    void printVals();
    void calcValue();
    float getValue();


};


#endif //KOE_MOVINGAVGVAL_H
