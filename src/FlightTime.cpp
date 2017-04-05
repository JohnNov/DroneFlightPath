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

///Checks if we have a new image to grab.
int FlightTime::booleanFileRead()
{
    ifstream booleanFile ("booleanFile.txt");
    string booleanFileResult;
    booleanFile.open("booleanFile.txt", ifstream::in);
    getline (booleanFile,booleanFileResult);
    booleanFile.close();
    if(booleanFileResult=="True") ///function returns 0 if strings are equal hence the '!'
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


///Responsible for fetching images and GPS coordinates once they are recogized on the network.
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

            system("php -f fetchImage.php 0.jpg");                              ///We check if we have a new image to fetch.
                                                                                ///Note: 0.jpg needs to increment for demo
        if(booleanFileRead()==1)
        {
            latInstruction = fetchLatInst+"Lat"+stringCount+phpExt;
            system(latInstruction.c_str());
            string mvLatInst = "mv Lat"+stringCount+"txt"+" positiveLat";
            system(mvLatInst.c_str());                  ///We move the Latitude over to positiveLat folder
        }
        fetchGPSTxt();

    }
}
///Fetches GPS information and displays it

void FlightTime::fetchGPSTxt(){


    string bash = "./binTest & exit";
    string exit = "exit";

    system(bash.c_str());                           ///This is ending the program early.  We need it to run so the
    system(exit.c_str());                           ///GPS file will be up to date frequently.

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
