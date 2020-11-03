#ifndef _JELLY_LBR_CLIENT_H
#define _JELLY_LBR_CLIENT_H

#include "friLBRClient.h"

#include <iostream>
#include <fstream>

class JellyLBRClient : public KUKA::FRI::LBRClient
{

public:
    JellyLBRClient();

    ~JellyLBRClient();

    virtual void onStateChange(KUKA::FRI::ESessionState oldState, KUKA::FRI::ESessionState newState);
    virtual void monitor();
    virtual void waitForCommand();
    virtual void command();

private:

    double _torques[KUKA::FRI::LBRState::NUMBER_OF_JOINTS]; //!< commanded superposed torques

    unsigned int start_time_sec;
    unsigned int start_time_nsec;

    double prev_joint_position[7];
};

#endif // _JELLY_LBR_CLIENT_H
