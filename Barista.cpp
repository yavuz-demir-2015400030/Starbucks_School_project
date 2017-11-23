//
// Created by Yavuz on 17/11/2017.
//

#include "Barista.h"

Barista::Barista() {
    this->emptyTime = 0;
    this->busyTime = 0;

}

Barista::Barista(const Barista& other) {
    this->busyTime = other.busyTime;
    this->emptyTime = other.emptyTime;

}

Barista Barista::operator=(const Barista &other) {
    this->emptyTime = other.emptyTime;
    this->busyTime = other.busyTime;

}

Barista::~Barista() {
}