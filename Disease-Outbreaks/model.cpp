#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <random>
#include <cmath>
#include <list>
using namespace std;
//Model 1: 11/24 Predicting Disease Outbreaks
//Sources: https://www.youtube.com/watch?v=m6Hr69JH_wA
//https://pmc.ncbi.nlm.nih.gov/articles/PMC3693038/#:~:text=Because%20the%20number%20of%20initially,(%20N%20%2D%201%20)%20)%20.

double susceptible=1000;
double infected=1;
double removed=0;
double deceased=0;
double exposed=0;
double recovered=0;
double initial=susceptible;
double latency=14;
//b*susceptible = how many people can be infected
//b of 0.0001 = 1 person on first day
double b=0.0001;
double u=0.02;
double m=0.1;
//u*infected = how many people recover
//0.02*1 = 2% recovery rate
//use first day to determine basic coefficients
int counter=0;
int main() {
fstream fout;
fout.open("data.csv",ios::out);
double R0=b*susceptible*1/u;



    //Solution 1: ODE SIR
    //fout << "susceptible" << "," << "infected" <<","<< "removed" << ","<< "time" <<"\n";
    // while (infected>0 && counter<1000) {
    //     fout << susceptible << "," << infected <<","<< removed << "," << counter <<"\n";
    //     susceptible+=(infected*-b*susceptible);
    //     infected+=(susceptible*b*infected-u*infected);
    //     removed+=(u*infected);
    //     counter++;
    // }


    //Solution 2: ODE + Stochastic
    //fout << "susceptible" << "," << "infected" <<","<< "removed" << ","<< "time" <<"\n";
    // while (infected>0 && counter<1000) {
    //     fout << susceptible << "," << infected <<","<< removed << "," << counter <<"\n";
    //     //able to go from 0-2x infection, average is the same
    //     double randomInfected=rand()/32767.00*b*susceptible*infected*2;
    //     double randomRecovered=rand()/32767.00*u*infected*2;
    //     susceptible-=(randomInfected);
    //     infected+=(randomInfected-randomRecovered);
    //     removed+=(randomRecovered);
    //     counter++;
    // }


    //Solution 3: SIRD 
    //     fout << "susceptible,infected,recovered,deceased,time" << "\n";
    // while (infected>0 && counter<1000) {
    //  fout << susceptible << "," << infected <<","<< removed << "," << deceased << ","<< counter <<"\n";
    //     double randomInfected=rand()/32767.00*b*susceptible*infected*2;
    //     double randomRemoved=rand()/32767.00*u*infected*2;
    //     susceptible-=(randomInfected);
    //     infected+=(randomInfected-randomRemoved);
    //     recovered+=(randomRemoved-randomRemoved*m);
    //     deceased+=(randomRemoved*m);
    //     counter++;
    // }

    //Solution 4: SEIR(D)
        list<double> infectedPast;
    fout << "susceptible" << "," << "infected" <<","<< "exposed" <<","<<"removed" << ","<< "time" <<"\n";
    while (infected>0 && counter<1000) {
        fout << susceptible << "," << infected <<","<< exposed<<","<< removed << "," << counter <<"\n";
        if (infectedPast.size()>latency) {
        infected+=infectedPast.front();
        infectedPast.pop_front();
        }
     double randomExposed=rand()/32767.00*b*susceptible*infected*2;
       double randomRemoved=rand()/32767.00*u*infected*2;
        susceptible-=randomExposed;
        double lastExposed=exposed;
        exposed+=randomExposed;
        removed+=randomRemoved;
        infectedPast.push_back(exposed-lastExposed);
        counter++;
    }
}