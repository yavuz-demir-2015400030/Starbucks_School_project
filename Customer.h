//
// Created by Yavuz on 14/11/2017.
//

#ifndef PROJECT2_YAVUZ_DEMIR_2015400030_MASTER_CUSTOMER_H
#define PROJECT2_YAVUZ_DEMIR_2015400030_MASTER_CUSTOMER_H

#include <iostream>

using namespace std;


class Customer {
public:

    int ID;
    int cashID;
    int barID;
    double arrivalTime;
    double orderTime;
    double brewTime;
    double priceOfOrder;
    double baristaTime;
    double turnAroundTime;
    double tAT2;



    Customer();
    Customer(int _ID, double aTime,double oTime, double bTime, double pOfOrder);
    Customer(const Customer& other);
    Customer& operator=(const Customer& other);
    bool operator==(const Customer& other)const;
    bool operator<(const Customer& other)const;
    ~Customer();



};


#endif //PROJECT2_YAVUZ_DEMIR_2015400030_MASTER_CUSTOMER_H
