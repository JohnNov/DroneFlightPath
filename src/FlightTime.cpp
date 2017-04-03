#include "FlightTime.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <Drone.h>
#include <numeric>
#include <cmath>

using namespace std;

FlightTime::FlightTime()
{
    //ctor
}

int FlightTime::booleanFileRead()
{
    ifstream booleanFile ("booleanFile.txt");
    string booleanFileResult;
    booleanFile.open("booleanFile.txt", ifstream::in);
    getline (booleanFile,booleanFileResult);
    booleanFile.close();
    if(booleanFileResult=="True") //function returns 0 if strings are equal hence the '!'
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void FlightTime::flightLoop()
{
    int count = 0;
    string latInstruction;
    string longInstruction;
    string imgString1 = "php -f fetchImage.php";
    string jpgExt = ".jpg";
    string phpExt = ".php";
    string fetchLatInst = "php -f fetchLat.php ";

    while(true)
    {

        string stringCount = to_string(count);
        string completeImgString = imgString1 +" "+stringCount+jpgExt;       ///completeImgString is now php -f fetchImage.php 0.jpg--  Where 0 is whatever "count" is

        /// cout << "Image: "<<system(completeImgString.c_str())<<endl;  //The + i is pointing to the argument character. So for example +3 is pointing to '-f'
        system("php -f fetchImage.php 0.jpg");

        if(booleanFileRead()==1)
        {
            latInstruction = fetchLatInst+"Lat"+stringCount+phpExt;     //
            system(latInstruction.c_str());
            string mvLatInst = "mv Lat"+stringCount+"txt"+" positiveLat";
            system(mvLatInst.c_str());  ///We move the Latitude over to positiveLat folder
        }
        cout<<"test"<<endl;
        fetchGPSTxt();

    }
}

void FlightTime::fetchGPSTxt(){


    string bash = "./binTest & exit";
    string exit = "exit";

    system(bash.c_str());       ///This is ending the program early.  We need it to run so the
    system(exit.c_str());                                ///GPS file will be up to date frequently.
    cout<<"Howdy Partner"<<endl;

    sleep(4);

    ifstream fin;
    string parseString;

    fin.open("GPS_Information.txt");
    if(fin.fail()){
        cout<<"Can't access GPS.txt"<<endl;
    }
    else{
    while(!fin.eof()){
        getline(fin,parseString);       ///This saves contents of file GPS_Information.txt to a string
        cout<<parseString<<endl;        ///This prints out the contents of the file GPS_Information.txt
    }
    fin.close();                        ///Close stream
    }
}


FlightTime::~FlightTime()
{
    //dtor
}
