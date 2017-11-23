//
// Created by Yavuz on 14/11/2017.
//

#ifndef PROJECT2_YAVUZ_DEMIR_2015400030_MASTER_CASHIER_H
#define PROJECT2_YAVUZ_DEMIR_2015400030_MASTER_CASHIER_H

#include <iostream>


using namespace std;

class Cashier {

public:

    double emptyTime;
    double busyTime;


    Cashier();
    Cashier(const Cashier& other);
    Cashier& operator=(const Cashier& other);
    ~Cashier();




};


#endif //PROJECT2_YAVUZ_DEMIR_2015400030_MASTER_CASHIER_H
