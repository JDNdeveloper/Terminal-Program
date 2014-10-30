/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#ifndef FUTUREVALUE_H
#define FUTUREVALUE_H

#include "Terminal.h"

class FutureValue {
    public:
        FutureValue(Terminal *TO) {}
        void start(std::string bob[]);
    private:
        double calcFuture(double, double, int, int);
};

#endif
