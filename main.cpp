#include <iostream>
#include <sstream>
#include "AssignCoordinates.h"
#include "FlightTime.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Drone.h"
#include <vector>
#include <fstream>
#include <unistd.h>


string GetStdoutFromCommand(string cmd) {

    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
                pclose(stream);
    }
    return data;
    }


int numDrones(vector<string> &goodHostsIPs){
    int goodHosts = 0;
    int badHosts = 0;
    ///Make sure there aren't any new lines in stateicIPList.txt as that blank line would be considered an empty IP address
    ifstream staticIPList("staticIPList.txt");
    string reader;
    vector<string> listOfIPs;

    if(staticIPList.is_open()){
        while(getline(staticIPList, reader)){
            listOfIPs.push_back(reader);
            }
        }

    for(int i = 0; i<listOfIPs.size(); i++){    ///We want to ping out all our IPAddresses to make sure everyone's connected
        string toPing = "ping -c 1 "+listOfIPs[i];
        cout<<"toPing is "<<toPing<<endl;
        string commandResult = GetStdoutFromCommand(toPing);

        cout<<"commandResult is "<<commandResult<<endl;

        int result = commandResult.find("100% packet loss");    ///We check if the ping was successful meaning the drones are connected to the network and we see them.
        int anotherResult = commandResult.find("unknown host");

        cout<<"result is "<<result<<endl;
        cout<<"anotherResult is "<<anotherResult<<endl;
        int totalResult = result+anotherResult;

        if(totalResult < 0){ ///result is greater than 0 if we don't have packet loss
            goodHosts++;
            goodHostsIPs.push_back(listOfIPs[i]);   ///We add the good host so we can send this IP number to the drones
                    }
        else
            badHosts++;
            }
        cout<<"goodHosts is "<<goodHosts<<endl;
        cout<<"badHosts is "<<badHosts<<endl;

        if(goodHosts == listOfIPs.size())
            cout<<"All drones are connected to network!"<<endl;
        else{
            cout<<"Not all drones are connected to network.  We only have "<<goodHosts<<" connected."<<endl;
            cout<<"Please confirm you have correct static IP's listed in staticIPList.txt"<<endl;
            cout<<"We will continue with the "<<goodHosts<<" number of drones connected"<<endl;
            }
        sleep(5);
        return goodHosts;
}

void pushDronesOnVector(int numOfDrones, vector<Drone> &v){     ///Pushes x number of drones onto the drone Vector

    if(numOfDrones > 0){
        Drone aDrone;
        v.push_back(aDrone);
        numOfDrones--;
        ///cout<<"numOfDrones is "<<numOfDrones<<endl;
        pushDronesOnVector(numOfDrones, v);
}
}

void areaToBeSearched(double &topLeftLat, double &topLeftLong, double &bottomRightLat, double &bottomRightLong){        ///Prompts user for the area that has to be searched

        double userInput;

        for(int i = 0; i<4; i++){

            string input = " ";

            while (true) {
                if(i == 0)
                    cout << "Enter top left Latitude : "<<endl;
                else if(i == 1)
                    cout<<"Enter top left Longitude : "<<endl;
                else if(i == 2)
                    cout<<"Enter bottom right Latitude : "<<endl;
                else
                    cout<<"Enter bottom right Longitude : "<<endl;
                getline(cin, input);
                stringstream myStream(input);

                if (myStream >> userInput)
                  break;
                cout << "Invalid number, please try again" << endl;
             }
             cout << "You entered: " << userInput << endl << endl;
                if(i==0)
                    topLeftLat = userInput;
                else if(i == 1)
                    topLeftLong = userInput;
                else if(i == 2)
                    bottomRightLat = userInput;
                else
                    bottomRightLong = userInput;
    }
}

void partitionArea(vector<Drone> &v, vector<string> IPList, int numberOfDrones, double topLeftLat, double topLeftLong, double bottomRightLat, double bottomRightLong){

    double totalHorizontalWidth = bottomRightLong - topLeftLong;
    double individualHorizontalWidth = (totalHorizontalWidth/numberOfDrones);
    double droneBottomLeftLat, droneBottomLeftLong, droneBottomRightLat, droneBottomRightLong, droneTopLeftLat, droneTopLeftLong, droneTopRightLat, droneTopRightLong;

    for(int i = 0; i<numberOfDrones; i++){

        droneBottomLeftLat = bottomRightLat;
        droneBottomLeftLong = topLeftLong + (i*individualHorizontalWidth);    ///We're subtracting because to the left of the meridian of 0
        droneBottomRightLat = bottomRightLat;
        droneBottomRightLong = topLeftLong + ((i+1)*individualHorizontalWidth);///We're subtracting because we're to the left of the 0 meridian

        droneTopLeftLat = topLeftLat;
        droneTopLeftLong = topLeftLong + (i*individualHorizontalWidth);
        droneTopRightLat = droneTopLeftLat;
        droneTopRightLong = topLeftLong + ((i+1)*individualHorizontalWidth);

        Drone aDrone(droneBottomLeftLat, droneBottomLeftLong, droneBottomRightLat, droneBottomRightLong, droneTopLeftLat, droneTopLeftLong, droneTopRightLat, droneTopRightLong);

        ///cout<<"topLeft is "<<droneTopLeftLat<<","<<droneTopLeftLong<<endl;
        ///cout<<"topRight is "<<droneTopRightLat<<","<<droneTopRightLong<<endl;

        cout<<endl;

        ///cout<<"bottomLeft is "<<droneBottomLeftLat<<","<<droneBottomLeftLong<<endl;
        ///cout<<"bottomRight is "<<droneBottomRightLat<<","<<droneBottomRightLong<<endl;

        aDrone.setIPNumber(IPList[i]);      ///We tell the drone object the IPNumber of a hardware drone
        v.push_back(aDrone);

    }

}

void assignCoordinates(string printMessage, double &aValue){
    string input;
    cout<<"Please enter "<<printMessage<<endl;

    double aNumber = 0;

    while(true){
        getline(cin, input);
        stringstream aStream(input);
        if(aStream>>aNumber)
            break;
        cout << "Invalid number, please try again."<<endl;
    }
    aValue = aNumber;
}

int main()
{

    double topLeftLat, topLeftLong, bottomRightLat, bottomRightLong;
    topLeftLat = 41.48698;
    topLeftLong = -71.527993;
    bottomRightLat = 41.485738;
    bottomRightLong = -71.526539;

    vector<string> goodIPList;

    int numSpirals;
    int numOfDrones = numDrones(goodIPList);      ///We prompt the user for number of drones he has.

    vector<Drone> droneVector;

    partitionArea(droneVector, goodIPList, numOfDrones, topLeftLat, topLeftLong, bottomRightLat, bottomRightLong);

    FlightTime flightTime;

    for(int i = 0; i<droneVector.size(); i++){
        numSpirals = droneVector[i].numTimesSpiralCenter();
        droneVector[i].setSpirals(numSpirals);
        ///cout<<"numSpirals is "<<numSpirals<<endl;
        droneVector[i].IPNumAndInstructionsToApache();
        droneVector[i].beginFlight(numSpirals);
    }

    flightTime.flightLoop();
    return 0;
}
