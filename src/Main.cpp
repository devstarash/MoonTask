#include <iostream>
#include "../include/Date.h"
#include "../include/MoonCalculator.h"
#include "../include/Array.h"
using namespace std;
int main(){
    string date;
    cin >> date;
    Date d(date);
    MoonCalculator moonCalc;
    try{
        MoonResponse  mn = moonCalc.showMoonPhases(d);
        cout<<"Response: \n" <<"Лунный восход: "<< mn.rise.getFullDate() <<"\nЛунный заход: " <<mn.set.getFullDate()<<"\nЛунная кульминация: "<<mn.culmination.getFullDate()<<endl;
    }catch(MoonCalculateException* exp){
        cout << exp;
    }
    
}