#include <iostream>
#include <string>
#include "AssignCoordinates.h"
//#include "Map.h"
//#include "conio.h"
#include <cstdio>
#include <stdio.h>

#include <time.h>
#include <Drone.h>
#include <math.h>
//#include <cmath.h>


AssignCoordinates::AssignCoordinates()
{

}


void AssignCoordinates::startGame()
{
    bool isOver = false;
    int numberOfDrones;
    int mapWidth;
    int widthForDrones=0;
    int remainder =0;

    Drone aDrone(41.485738, -71.52799, 41.485738, -71.526539, 41.486989, -71.527993, 41.486989, -71.526539);    //All the starting coordinates
    aDrone.setStartingPoint(41.485738, -71.52799);
    aDrone.setHorizontalLimits(-71.527993, -71.526539);
    aDrone.setVerticalLimits(41.486989, 41.485738);
    aDrone.findCenter(-71.527993, -71.526539, 41.485738, 41.486989);

    /*
        while(!aDrone.outOfRoom()){
        aDrone.goRight();
        aDrone.goUp();
        aDrone.goLeft();
        aDrone.goDown();
        }
        */

    double horizontalDifference = fabs(71.527993-71.526539);
    cout<<"difference is "<<horizontalDifference<<endl;   //difference in this hardcoded case is 143.055

    int count = 0;
    while(horizontalDifference>0)
    {
        horizontalDifference = horizontalDifference-.0004;
        count++;
    }

    cout<<"count is "<<count;

    for(int i = 0; i<4; i++)    //THis is a hardcoded for loop to find the center
    {
        /*
        The closer it gets to the center the less time it takes on each iteration
        so it's not THAT bad of a bug.
        OR
        we could go until distance is -nan
        */
        aDrone.goRight();
        aDrone.goUp();
        aDrone.goLeft();
        aDrone.goDown();
    }
}



