#pragma once
#include <tuple>
#include <math.h>

using namespace std;

class Drone
{

public:
    Drone();
    Drone(double bottomLeftLat, double bottomLeftLong, double bottomRightLat, double bottomRightLong, double topLeftLat, double topLeftLong, double topRightLat, double topRightLong);

    void assignCoordinates();

    void setStartingPoint(double startingLat, double startingLong);

    void setHorizontalLimits(double theLeftLimit, double theRightLimit);   //We could pass topRightLong and topLeftLong and it would be just as valid.
    void setVerticalLimits(double topLimit, double bottomLimit);     //We could pass topLeftLat and bottomRightLat and it would work just as well.

    void getHorizontalLimits(double &leftLimit, double &rightLimit);
    void getverticalLimits();

    void setRightLimit(double rightLimit);

    void setTopLimit(double topLimit);

    void setLeftLimit(double leftLimit);

    void setBottomLimit(double bottomLimit);

    void setIPNumber(string IPnumber);

    void IPNumAndInstructionsToApache();

    string getIPNumber();

    bool outOfRoom();

    void findCenter(double bottomLeftLong, double bottomRightLong, double bottomLeftLat, double topLeftLat);

    void setSpirals(int numSpirals);
    int getSpirals();

    void goRight();
    void goUp();
    void goLeft();
    void goDown();

    void setLocation(int x, int y);

    void getLocation(int &x, int &y);

    int numTimesSpiralCenter();

    void beginFlight(int numSpirals);

    string dronesIPNumber;

    double _startingLat;
    double _startingLong;

    double _rightLimit=0.0;
    double _leftLimit=0.0;

    double _topLimit;
    double _bottomLimit;

    double _currentLat;
    double _currentLong;

    bool noRoomLeft = false;

    double _centerLat;
    double _centerLong;

    double _bottomLeftLat;
    double _bottomLeftLong;
    double _bottomRightLat;
    double _bottomRightLong;
    double _topLeftLat;
    double _topLeftLong;
    double _topRightLat;
    double _topRightLong;

    int _numberOfSpirals;

protected:
    int _x;
    int _y;
    int _numberOfPlacesVisited = 0;

    //tuple<int,int> previouslyVisitedLocations[600]; //Hard coded 600 value is messy.
};
