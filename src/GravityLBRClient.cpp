#include <cstring>
#include <cstdio>

// Visual studio needs extra define to use math constants
#define _USE_MATH_DEFINES
#include <math.h>
#include "GravityLBRClient.h"


using namespace KUKA::FRI;

//******************************************************************************
GravityLBRClient::GravityLBRClient()
{

   start_time_sec = 0.0;
   start_time_nsec = 0.0;

   for (int i = 0; i < LBRState::NUMBER_OF_JOINTS; ++i){ 
      _torques[i] = 0.0;
   }
}

//******************************************************************************
GravityLBRClient::~GravityLBRClient()
{

}
      
//******************************************************************************
void GravityLBRClient::onStateChange(ESessionState oldState, ESessionState newState)
{
   LBRClient::onStateChange(oldState, newState);

   switch (newState)
   {
      case MONITORING_WAIT:   // state 1
      {
         // Initial time

         std::cout << "state 1: MONITORING_WAIT\n";
         
         start_time_sec = robotState().getTimestampSec();
         start_time_nsec = robotState().getTimestampNanoSec();

        break;
      }
      case MONITORING_READY:  // state 2
      {
         std::cout << "state 2: MONITORING_READY\n";
         break;
      }
      case COMMANDING_WAIT:
      {
         std::cout << "state 3: COMMANDING_WAIT\n";
         break;
      }
      case COMMANDING_ACTIVE:
      {
         std::cout << "state 4: COMMANDING_ACTIVE\n";
         break;
      }
      default:
      {
         std::cout << "state 0: IDLE\n";
         break;
      }
   }
}
//******************************************************************************

void GravityLBRClient::monitor()
{
   LBRClient::monitor();
}

void GravityLBRClient::waitForCommand()
{

   LBRClient::waitForCommand();
   
   if (robotState().getClientCommandMode() == TORQUE)
   {
      std::cout << "Set torque while wait the command!\n";
      robotCommand().setTorque(_torques);
   }
}

void GravityLBRClient::command()
{
    // In command(), the joint values have to be sent. Which is done by calling
    // the base method.
    LBRClient::command();

    robotCommand().setJointPosition(robotState().getMeasuredJointPosition());

    std::cout << robotState().getTimestampSec() - start_time_sec 
               + robotState().getTimestampNanoSec() / 1e9  <<  "\tcommand state!" <<"\n";

    // Check for correct ClientCommandMode.
    if (robotState().getClientCommandMode() == TORQUE)
    { 
       for (int i=0; i<LBRState::NUMBER_OF_JOINTS; i++)
       {
           _torques[i] = 0.0;   // fri torque
       }
       // Set superposed joint torques.
       robotCommand().setTorque(_torques);
    }
}