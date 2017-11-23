//
// Created by Yavuz on 14/11/2017.
//

#include "Cashier.h"


Cashier::Cashier() {
    this->emptyTime = 0;
    this->busyTime = 0;
}

Cashier::Cashier(const Cashier &other) {
    this->emptyTime = other.emptyTime;
    this->busyTime = other.busyTime;
}

Cashier& Cashier::operator=(const Cashier &other) {
    this->emptyTime = other.emptyTime;
    this->busyTime = other.busyTime;
}

Cashier::~Cashier(){
}