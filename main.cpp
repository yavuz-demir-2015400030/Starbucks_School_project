#include <iostream>
#include "Cashier.h"
#include "Barista.h"
#include <algorithm>
#include <fstream>
#include "Customer.h"
#include <queue>
#include <iomanip>
#include <vector>


bool compareCustomers(Customer const& c1, Customer const& c2){
    return c1.baristaTime<c2.baristaTime;
}

bool compareCustomerIDs(Customer const& c1, Customer const& c2){
    return c1.ID<c2.ID;
}



int main(int argc, char* argv[]) {


    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }

    cout << "input file: " << argv[1] << endl;
    cout << "output file: " << argv[2] << endl;

    ifstream input(argv[1]);



    int n;
    int m;

    input >> n >> m;



    Cashier* cash[n];
    Barista* bar[n/3];
    Barista* bar2[n/3];

    queue<int> cashQ;
    priority_queue<Customer> bQueue;

    vector<priority_queue<Customer>> bQ2;



    int bQlength = 0;


    for(int i = 0; i<n; i++){
        cash[i] = new Cashier();
        if(i%3 == 0){
            bar[i/3] = new Barista();
            bar2[i/3] = new Barista();
            priority_queue<Customer> temp;
            bQ2.push_back(temp);
        }
    }




    int cLength = 0;
    int maxLength = 0;

    Customer cust[m];


    for(int i =0; i<m; i++) {
        double a, b, c, d;
        input >> a >> b >> c >> d;
        cust[i] = *new Customer(i, a, b, c, d);


        bool inQueue = true;
        for(int j=0; j<n; j++) {


            if (cLength == 0) {
                if (cash[j]->emptyTime <= cust[i].arrivalTime) {

                    cash[j]->emptyTime = cust[i].arrivalTime + cust[i].orderTime;
                    cash[j]->busyTime += cust[i].orderTime;
                    inQueue = false;
                    cust[i].baristaTime = cash[j]->emptyTime;
                    cust[i].cashID = j;


                    break;

                }
            } else {

                double minTime = cash[0]->emptyTime;
                int minIndex = 0;
                cashQ.push(i);
                cLength++;


                inQueue = false;

                do {

                    int index = cashQ.front();
                    cashQ.pop();

                    cLength--;



                    for (int k = 0; k < n; k++) {
                        if (cash[k]->emptyTime < minTime) {
                            minTime = cash[k]->emptyTime;
                            minIndex = k;
                        }
                    }


                    cash[minIndex]->emptyTime = cash[minIndex]->emptyTime + cust[index].orderTime;
                    cash[minIndex]->busyTime += cust[index].orderTime;
                    cust[index].baristaTime = cash[minIndex]->emptyTime;
                    cust[index].cashID = minIndex;


                    minTime = cash[0]->emptyTime;
                    minIndex = 0;
                    if(cLength != 0) {

                        for (int k = 0; k < n; k++) {
                            if (cash[k]->emptyTime < minTime) {
                                minTime = cash[k]->emptyTime;
                                minIndex = k;
                            }
                        }
                    }

                } while (cLength != 0 && minTime < cust[i].arrivalTime);

                break;
            }

        }
        if(inQueue){
            cashQ.push(i);
            cLength++;
            maxLength++;
//            if(maxLength < cLength){
//                maxLength = cLength;
//            }
        }

    }


    while(cLength != 0){


        int index = cashQ.front();
        cashQ.pop();
        cLength--;


        double minTime = cash[0]->emptyTime;
        int minIndex = 0;

        bool end = false;

        for(int i=0; i<n; i++){
            if(cust[i].arrivalTime > cash[i]->emptyTime){
                minIndex=i;
                end = true;
                break;
            }
            if(cash[i]->emptyTime < minTime){
                minTime = cash[i]->emptyTime;
                minIndex = i;
            }

        }

        if(!end) {
            cash[minIndex]->emptyTime = cash[minIndex]->emptyTime + cust[index].orderTime;

        }else{
            cash[minIndex]->emptyTime = cust[index].arrivalTime + cust[index].orderTime;

        }
        cash[minIndex]->busyTime += cust[index].orderTime;
        cust[index].baristaTime = cash[minIndex]->emptyTime;
        cust[index].cashID = minIndex;


    }

    sort(cust, cust+m, compareCustomers);

    int bQmax = 0;
    int b2[n/3];
    int max2[n/3];

    for(int i=0; i<n/3; i++){
        b2[i] = 0;
        max2[i] = 0;
    }




    for(int i=0; i<m; i++) {

        cust[i].barID = i;

        bool inBQ = true;

        for (int j = 0; j < n/3; j++) {

            if (bQlength ==0) {
                if(bar[j]->emptyTime <= cust[i].baristaTime) {
                    bar[j]->emptyTime = cust[i].baristaTime + cust[i].brewTime;
                    bar[j]->busyTime += cust[i].brewTime;
                    cust[i].turnAroundTime = bar[j]->emptyTime - cust[i].arrivalTime;

                    inBQ = false;
                    break;
                }
            }else{

                int minIndex = 0;
                double minTime =bar[0]->emptyTime;

                for(int k = 0; k<n/3; k++){
                    if(bar[k]->emptyTime < minTime){
                        minTime = bar[k]->emptyTime;
                        minIndex = k;
                    }
                }


                if(minTime < cust[i].baristaTime) {

                    do {
                        Customer temp = bQueue.top();
                        bQueue.pop();
                        bQlength--;
                        int ind = temp.barID;

                        minIndex = 0;
                        minTime =bar[0]->emptyTime;

                        bool end = false;

                        for (int k = 0; k < n / 3; k++) {
                            if (bar[k]->emptyTime < cust[ind].baristaTime) {
                                minIndex = k;
                                end = true;
                                break;
                            }
                            if (bar[k]->emptyTime < minTime) {
                                minTime = bar[k]->emptyTime;
                                minIndex = k;
                            }
                        }
                        if (!end) {
                            bar[minIndex]->emptyTime = bar[minIndex]->emptyTime + cust[ind].brewTime;
                        } else {
                            bar[minIndex]->emptyTime = cust[ind].baristaTime + cust[ind].brewTime;
                        }
                        bar[minIndex]->busyTime += cust[ind].brewTime;



                        cust[ind].turnAroundTime = bar[minIndex]->emptyTime - cust[ind].arrivalTime;


                        minIndex = 0;
                        minTime = bar[0]->emptyTime;

                        for (int k = 0; k < n / 3; k++) {
                            if (bar[k]->emptyTime < minTime) {
                                minTime = bar[k]->emptyTime;
                                minIndex = k;
                            }
                        }

                    } while (bQlength != 0 && cust[i].baristaTime > bar[minIndex]->emptyTime);
                    break;
                }

            }

        }


        if (inBQ) {
            bQueue.push(cust[i]);

            bQlength++;

            if (bQlength > bQmax) {
                bQmax = bQlength;
            }
        }

        bool inB = true;

        int indy = cust[i].cashID/3;


        if (b2[indy] == 0) {
            if(bar2[indy]->emptyTime < cust[i].baristaTime){
                bar2[indy]->emptyTime = cust[i].baristaTime + cust[i].brewTime;
                bar2[indy]->busyTime += cust[i].brewTime;
                cust[i].tAT2 = bar2[indy]->emptyTime - cust[i].arrivalTime;

                inB = false;

            }
        }else{


            if(bar2[indy]->emptyTime < cust[i].baristaTime) {

                do {

                    Customer temp = bQ2[indy].top();
                    bQ2[indy].pop();
                    b2[indy]--;
                    int ind = temp.barID;

                    if(bar2[indy]->emptyTime > cust[ind].baristaTime) {
                        bar2[indy]->emptyTime = bar2[indy]->emptyTime + cust[ind].brewTime;
                    }else{
                        bar2[indy]->emptyTime = cust[ind].baristaTime + cust[ind].brewTime;
                    }

                    bar2[indy]->busyTime += cust[ind].brewTime;


                    cust[ind].tAT2 = bar2[indy]->emptyTime - cust[ind].arrivalTime;



                } while (bQlength != 0 && cust[i].baristaTime > bar2[indy]->emptyTime);

            }


        }

        if(inB){
            bQ2[indy].push(cust[i]);
            b2[indy]++;
            if(b2[indy] > max2[indy]){
                max2[indy] = b2[indy];
            }
        }

    }

    while(bQlength > 0){

        Customer temp = bQueue.top();
        int ind = temp.barID;
        bQueue.pop();
        bQlength--;

        int minB = 0;
        double minBtime = bar[0]->emptyTime;

        bool end = false;

        for(int i=0; i<n/3; i++){

            if(cust[ind].baristaTime > bar[i]->emptyTime){
                end = true;
                minBtime = bar[i]->emptyTime;
                minB = i;
                break;
            }
            if(bar[i]->emptyTime < minBtime){

                minBtime = bar[i]->emptyTime;
                minB = i;
            }
        }

        if(!end) {
            bar[minB]->emptyTime += cust[ind].brewTime;
        }else{
            bar[minB]->emptyTime = cust[ind].baristaTime + cust[ind].brewTime;
        }
        bar[minB]->busyTime += cust[ind].brewTime;


        cust[ind].turnAroundTime = bar[minB]->emptyTime - cust[ind].arrivalTime;




    }

    for(int k=0; k<n/3; k++){
        while(b2[k] > 0){
            Customer temp = bQ2.at(k).top();
            int ind = temp.barID;
            bQ2.at(k).pop();
            b2[k]--;


            if(bar2[k]->emptyTime < cust[ind].baristaTime ) {
                bar2[k]->emptyTime = cust[ind].baristaTime + cust[ind].brewTime;
            }else{
                bar2[k]->emptyTime += cust[ind].brewTime;
            }

            bar2[k]->busyTime += cust[ind].brewTime;



            cust[ind].tAT2 = bar2[k]->emptyTime - cust[ind].arrivalTime;


        }

    }

    sort(cust, cust+m, compareCustomerIDs);


    double totalTime = 0;
    double totalTime2 = 0;
    for(int i=0; i<n/3;i++){
        if(bar[i]->emptyTime > totalTime){
           totalTime = bar[i]->emptyTime;
        }
        if(bar2[i]->emptyTime > totalTime2){
            totalTime2 = bar2[i]->emptyTime;
        }
    }


    ofstream output;
    output.open(argv[2]);

    output<<std::fixed<<std::setprecision(2)<<totalTime<<endl;
    output<< maxLength << endl;
    output<< bQmax << endl;


    for(int i=0; i<n; i++){
        output<<std::fixed<<std::setprecision(2)<< 1.0*cash[i]->busyTime/totalTime<<endl;
    }
    for(int i=0; i<n/3; i++){
        output<<std::fixed<<std::setprecision(2)<< 1.0*bar[i]->busyTime/totalTime<<endl;
    }
    for(int i=0; i<m; i++){
        output<<std::fixed<<std::setprecision(2)<< cust[i].turnAroundTime <<endl;
    }

    output<<""<<endl;

    output<<std::fixed<<std::setprecision(2)<<totalTime2<<endl;
    output<< maxLength << endl;
    for(int i=0; i<n/3; i++){
        output<<max2[i]<<endl;
    }

    for(int i=0; i<n; i++){
        output<<std::fixed<<std::setprecision(2)<< 1.0*cash[i]->busyTime/totalTime2<<endl;
    }
    for(int i=0; i<n/3; i++){
        output<<std::fixed<<std::setprecision(2)<< 1.0*bar2[i]->busyTime/totalTime2<<endl;
    }
    for(int i=0; i<m; i++){
        output<<std::fixed<<std::setprecision(2)<< cust[i].tAT2 <<endl;
    }

    output.close();
    return 0;
}