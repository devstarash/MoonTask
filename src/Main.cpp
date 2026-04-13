#include <iostream>
#include "../include/Date.h"
#include "../include/MoonCalculator.h"
#include "../include/Array.h"
using namespace std;
int main(){
    Date d("2003-10-20");
    MoonCalculator moonCalc;
    MoonResponse  mn = moonCalc.showMoonPhases(d);
    cout<<"Response: " <<mn.rise.getFullDate() <<" " <<mn.set.getFullDate()<<" "<<mn.culmination.getFullDate()<<endl;

}