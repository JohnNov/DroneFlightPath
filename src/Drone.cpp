/*
In order to randomly spawn a Drone we've gotta be able to keep track of all the
locations that the Drone can travel ('.')

We need to go through the map and every time we come across a plain dot we store its
location in the vector AND we keep track of how many dots we've got.

So for example we have 50 dots then we do a random number generator from 1-50.  If
for example we get a 23 then we spawn the Drone at whatever location the 23'rd dot
is at!

So what should we use to store this?

WAIT FIRST LETS SPAWN THE Drone AT A HARD CODED LOCATION!


*/
#include <iostream>
#include <string>
#include "Drone.h"
#include <vector>
#include <numeric>
#include <cmath>
#include <fstream>

using namespace std;

///User input via gui
///Plot coordinates onto a screen and then feed those coordinates to main to distribute them among drone.

Drone::Drone(){

}

Drone::Drone(double bottomLeftLat, double bottomLeftLong, double bottomRightLat, double bottomRightLong, double topLeftLat, double topLeftLong, double topRightLat, double topRightLong)
{
    _bottomLeftLat = bottomLeftLat;
    _bottomLeftLong = bottomLeftLong;
    _bottomRightLat = bottomRightLat;
    _bottomRightLong = bottomRightLong;
    _topLeftLat = topLeftLat;
    _topLeftLong = topLeftLong;
    _topRightLat = topRightLat;
    _topRightLong = topRightLong;

    assignCoordinates();

}
///This tells the drones exactly what it's partitioned area will be.
void Drone::assignCoordinates()
{
    bool isOver = false;
    int numberOfDrones;
    int mapWidth;
    int widthForDrones=0;
    int remainder =0;

    setStartingPoint(_bottomLeftLat, _bottomLeftLong);
    setHorizontalLimits(_topLeftLong, _topRightLong);
    setVerticalLimits(_topLeftLat, _bottomRightLat);
    findCenter(_topLeftLong, _topRightLong, _bottomLeftLong, _topLeftLat);
    }


///Responsible for assigning the drones starting point.
void Drone::setStartingPoint(double startingLat, double startingLong)
{
    _startingLat = startingLat;
    _startingLong = startingLong;

    _currentLat = _startingLat;
    _currentLong = _startingLong;
}

void Drone::goRight()   ///We should start storing the new coordinates that we'll take the average of and send them to setLimit
{

    while((_currentLong+.0001)<=_rightLimit)    ///.0001 is the next space that the drone will move to
    {
        _currentLong = _currentLong + .0001;    ///.0001 (We could change to a random number to account for noise such as wind
        cout<<_currentLat<<","<<_currentLong<<endl;
    }

    setBottomLimit(_bottomLimit+.0002);


    double distancex = (_currentLat - _centerLat) * (_currentLat - _centerLat);
    double distancey = (_currentLong - _centerLong) * (_currentLong - _centerLong);

    double distance = sqrt(distancex - distancey);
    if(distance<=.00001)
    {
        noRoomLeft = true;
    }


}

void Drone::goUp()
{
    vector<double> longsForNewRightLimit;

    while((_currentLat+.0001)<=_topLimit)
    {
        ///We'd also have to fetch the current Long when this is hooked up to GPS for accurate new Right Limit.
        ///So we'd update current Long by whatever the GPS says now.
        longsForNewRightLimit.push_back(_currentLong);
        _currentLat = _currentLat + .0001;
        cout<<_currentLat<<","<<_currentLong<<endl;
    }

    double average = accumulate( longsForNewRightLimit.begin(), longsForNewRightLimit.end(), 0.0)/longsForNewRightLimit.size(); //Don't know how this works but it finds the average apparently.

    setRightLimit(_rightLimit-.0002);

    double distancex = (_currentLat - _centerLat) * (_currentLat - _centerLat);
    double distancey = (_currentLong - _centerLong) * (_currentLong - _centerLong);

    double distance = sqrt(distancex - distancey);
    if(distance<=.00001)
    {
        noRoomLeft = true;
    }

}

void Drone::goLeft()
{

    while((_currentLong-.0001)>=_leftLimit)    //.0001 is the next space that the drone will move to
    {
        _currentLong = _currentLong - .0001;    //.0001 should really be a random number
        cout<<_currentLat<<","<<_currentLong<<endl;
    }

    setTopLimit(_topLimit-.0002);


    double distancex = (_currentLat - _centerLat) * (_currentLat - _centerLat);
    double distancey = (_currentLong - _centerLong) * (_currentLong - _centerLong);

    double distance = sqrt(distancex - distancey);
    if(distance<=.00001)
    {
        noRoomLeft = true;
    }

}

void Drone::setIPNumber(string IPNumber){

    size_t endpos = IPNumber.find_last_not_of(" \t");
    if( string::npos != endpos )
    {
        IPNumber = IPNumber.substr( 0, endpos+1 );
    }
    dronesIPNumber = IPNumber;
    cout<<"dronesIPNumber is "<<dronesIPNumber<<endl;
}

string Drone::getIPNumber(){
    return dronesIPNumber;
}

void Drone::IPNumAndInstructionsToApache(){        ///We send the txt file titled with the IP number and the instructions to the Apache folder
    string IPNum = getIPNumber();

    IPNum = IPNum + ".txt";
    ofstream outputFile;
    outputFile.open(IPNum);

    outputFile<<"Right Limit: ";
    outputFile<< _rightLimit;

    outputFile<<"\nLeft Limit: ";
    outputFile<<_leftLimit;

    outputFile<<"\nTop Limit: ";
    outputFile<<_topLimit;

    outputFile<<"\nBottom Limit: ";
    outputFile<<_bottomLimit;

    outputFile<<"\nNumber of Spirals: ";
    outputFile<<getSpirals();

    outputFile.close();

    string newname = "/var/www/html/instructions/"+IPNum;
    cout<<"IPNum is "<<IPNum<<endl;

    ///string newname = "/Documents/"+IPNum+".txt";

    cout<<"newname is "<<newname<<endl;
    string mvNewName = "mv "+IPNum+" "+newname;

    ///string mvLatInst = "mv Lat"+stringCount+"txt"+" positiveLat";
    cout<<"mvnewName is "<<mvNewName<<endl;

    system(mvNewName.c_str());
}

void Drone::goDown()
{

    while((_currentLat-.0001)>=_bottomLimit)
    {
        _currentLat = _currentLat - .0001;
        cout<<_currentLat<<","<<_currentLong<<endl;
    }

    setLeftLimit(_leftLimit+.0002);

    double distancex = (_currentLat - _centerLat) * (_currentLat - _centerLat);
    double distancey = (_currentLong - _centerLong) * (_currentLong - _centerLong);

    double distance = sqrt(distancex - distancey);
    if(distance<=.00001)
    {
        noRoomLeft = true;
    }

}
///Set's every individual drones limits on their partitioned area.
void Drone::setHorizontalLimits(double theLeftLimit, double theRightLimit)
{
    _rightLimit = theRightLimit;
    _leftLimit = theLeftLimit;

}
///Acts as a boolean flag if we're out of room.
bool Drone::outOfRoom()
{
    return noRoomLeft;

}

void Drone::findCenter(double bottomLeftLong, double bottomRightLong, double bottomLeftLat, double topLeftLat)
{

    double ToAddFromLeft = bottomRightLong-bottomLeftLong;
    double toAddFromBottom = topLeftLat-bottomLeftLat;

    cout<<"ToAddFromLeft is "<<ToAddFromLeft<<endl;
    cout<<"ToAddFromBottom is "<<toAddFromBottom<<endl;


    _centerLat = bottomLeftLat+toAddFromBottom;
    _centerLong = bottomLeftLong+ToAddFromLeft;

}
///Set's every individual drones limits on their partitioned area.
void Drone::setVerticalLimits(double topLimit, double bottomLimit)
{

    _topLimit = topLimit;
    _bottomLimit = bottomLimit+.0001;

}

void Drone::setRightLimit(double rightLimit)
{
    _rightLimit = rightLimit;
}

void Drone::setLeftLimit(double leftLimit)
{
    _leftLimit = leftLimit;
}

void Drone::setTopLimit(double topLimit)
{
    _topLimit = topLimit;
}
void Drone::setBottomLimit(double bottomLimit)
{
    _bottomLimit = bottomLimit;
}

void Drone::getHorizontalLimits(double &leftLimit, double &rightLimit)
{
    leftLimit = _leftLimit;
    rightLimit = _rightLimit;
}


void Drone::setLocation(int x, int y)
{
    _x = x;
    _y = y;
}

void Drone::getLocation(int &x, int &y)     ///We use reference to change multiple arguments without returning them
{
    x = _x;
    y = _y;
}

int Drone::numTimesSpiralCenter(){ ///Tells drones to fly up, down, left and right until they reach center

    double difference = fabs(71.527993-71.526539);
    cout<<"difference is "<<difference<<endl;   //difference in this hardcoded case is 143.055

    int spiralCount = 0;
    while(difference>0)
    {
        difference = difference-.0004;          ///0.0004 calculated value for reasonable drone travel increment
        spiralCount++;
    }
    cout<<"spiralCount is "<<spiralCount<<endl;

    return spiralCount;

    }
void Drone::setSpirals(int numSpirals){
    _numberOfSpirals = numSpirals;
}

int Drone::getSpirals(){
    return _numberOfSpirals;
}

void Drone::beginFlight(int numSpirals){

    for(int i = 0; i<numSpirals; i++)    ///numSpirals until we reach the center.
    {
        goRight();
        goUp();
        goLeft();
        goDown();
    }
}

