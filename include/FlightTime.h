#ifndef FLIGHTTIME_H
#define FLIGHTTIME_H
#include <Drone.h>

class FlightTime
{
public:
    FlightTime();
    void flightLoop();
    void fetchGPSTxt();
    int booleanFileRead();
    virtual ~FlightTime();


protected:
private:
};

#endif // FLIGHTTIME_H
