#ifndef _GRAVITY_LBR_CLIENT_H
#define _GRAVITY_LBR_CLIENT_H

#include "friLBRClient.h"

#include <iostream>
#include <fstream>

class GravityLBRClient : public KUKA::FRI::LBRClient
{

public:
    GravityLBRClient();

    ~GravityLBRClient();

    virtual void onStateChange(KUKA::FRI::ESessionState oldState, KUKA::FRI::ESessionState newState);
    virtual void monitor();
    virtual void waitForCommand();
    virtual void command();

private:

    double _torques[KUKA::FRI::LBRState::NUMBER_OF_JOINTS]; //!< commanded superposed torques

    unsigned int start_time_sec;
    unsigned int start_time_nsec;

};

#endif // _GRAVITY_LBR_CLIENT_H
