#include<iostream>
#include<string>
#include<vector>
#include "Tkns.hpp"

int main()
{
    vector<string> test;
    Tkns t;
    test = t.split("i am Ani   "," ");


    cout<< "in main funtion : "<<endl;
    int i=0;
    while(i < test.size())
    {
        cout << endl << test[i] << endl;
        i++;
    }
}