//
// Created by Yavuz on 17/11/2017.
//

#ifndef PROJECT2_YAVUZ_DEMIR_2015400030_MASTER_BARISTA_H
#define PROJECT2_YAVUZ_DEMIR_2015400030_MASTER_BARISTA_H

#include <iostream>


using namespace std;


class Barista {

public:
    double emptyTime;
    double busyTime;

    Barista();
    Barista(const Barista& other);
    Barista operator=(const Barista& other);
    ~Barista();


};


#endif //PROJECT2_YAVUZ_DEMIR_2015400030_MASTER_BARISTA_H
