//
// Created by Yavuz on 14/11/2017.
//

#include "Customer.h"

Customer::Customer() {
    this->ID = -1;
    this->baristaTime =0;
    this->arrivalTime = 0;
    this->orderTime = 0;
    this->brewTime = 0;
    this->priceOfOrder =0;
    this->turnAroundTime = 0;
    this->tAT2 = 0;

}

Customer::Customer(int _ID, double aTime, double oTime, double bTime, double pOfOrder) {
    this->arrivalTime = aTime;
    this->orderTime = oTime;
    this->brewTime = bTime;
    this->priceOfOrder = pOfOrder;
    this->baristaTime = 0;
    this->turnAroundTime =0;
    this->tAT2 = 0;
    this->ID = _ID;


}

Customer::Customer(const Customer &other) {
    this->arrivalTime = other.arrivalTime;
    this->orderTime = other.orderTime;
    this->brewTime = other.brewTime;
    this->priceOfOrder = other.priceOfOrder;
    this->baristaTime = other.baristaTime;
    this->turnAroundTime = other.turnAroundTime;
    this->ID = other.ID;
    this->cashID = other.cashID;
    this->tAT2 = other.tAT2;
    this->barID = other.barID;
}

Customer& Customer::operator=(const Customer &other) {
    this->arrivalTime = other.arrivalTime;
    this->orderTime = other.orderTime;
    this->brewTime = other.brewTime;
    this->priceOfOrder = other.priceOfOrder;
    this->baristaTime = other.baristaTime;
    this->turnAroundTime = other.turnAroundTime;
    this->ID = other.ID;
    this->cashID = other.cashID;
    this->tAT2 = other.tAT2;
    this->barID = other.barID;
    return *this;
}


bool Customer::operator==(const Customer &other) const {
    return other.priceOfOrder == this->priceOfOrder;
}

bool Customer::operator<(const Customer &other) const{
    return other.priceOfOrder>this->priceOfOrder;
}

Customer::~Customer() {
}