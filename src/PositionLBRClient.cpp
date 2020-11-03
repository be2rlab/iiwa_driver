#include <iostream>
#include <cstdio>
#include "PositionLBRClient.h"

#include <iostream>
#include <cstring>
#include <cstdio>
#include "friLBRState.h"

using namespace std;

using namespace KUKA::FRI;
//******************************************************************************
PositionLBRClient::PositionLBRClient()
{
}

//******************************************************************************
PositionLBRClient::~PositionLBRClient()
{
}
/**
 * @brief Inititialisations on state changes.
 * 
 * @param oldState 
 * @param newState 
 */
void PositionLBRClient::onStateChange(ESessionState oldState, ESessionState newState)
{
   LBRClient::onStateChange(oldState, newState);

   // react on state change events
   switch (newState)
   {
      case MONITORING_WAIT:   //!< bad connection quality. Command mode is impossible
      {
         break;
      }       
      case MONITORING_READY:  //!< good connection quality. command mode is possible
      {
         /*
            getPosition (Commanded and Measured only)
         */

         break;
      }
      case COMMANDING_WAIT:   //!< Set command
      {
         /*
            getPosition (Commanded and Measured and Ipo)
         */

        //const double* p = robotState().getIpoJointPosition();
        const double* p = robotState().getIpoJointPosition();
        for (int i = 0; i < LBRState::NUMBER_OF_JOINTS; i++)
        {
          _positions[i] = p[i];
          _positions_des[i] = 0.0; //p[i] + 1.0;
         cout << _positions[i] << ' ';
        }
         cout << endl;


        for (int i = 0; i < LBRState::NUMBER_OF_JOINTS; i++)
        {
         cout << _positions_des[i] << ' ';
        }
         cout << endl;
         cout << endl;
         cout << endl;


         rad = 3.1415/180;
         v = 1 * rad;

         for (int i = 0; i < LBRState::NUMBER_OF_JOINTS; i++)
         {
            tf[i] = 60.0;  
            v = 1.5 * (_positions_des[i] - _positions[i]) / tf[i];
            tb[i] = (_positions[i] - _positions_des[i] + v * tf[i]) / v;
            a[i] = v / tb[i];
            cout << tb[i] << ' ';
         }
         cout << endl;
         
         memcpy(jointPos, robotState().getIpoJointPosition(), LBRState::NUMBER_OF_JOINTS * sizeof(double));

         break;
      }   
      case COMMANDING_ACTIVE:
      {
         cout << robotState().getClientCommandMode() << endl;
         
         start_time = robotState().getTimestampSec();
         start_time_nano = robotState().getTimestampNanoSec();

         break;
      }   
      default:
      {
         break;
      }
   }
}

//******************************************************************************
void PositionLBRClient::monitor()
{
   LBRClient::monitor();

   switch (robotState().getControlMode())
   {
      case MONITORING_WAIT:
      {
         break;
      }       
      case MONITORING_READY:
      {
         break;
      }
   }
}

//******************************************************************************
void PositionLBRClient::waitForCommand()
{
   // In waitForCommand(), the joint values have to be mirrored. Which is done, 
   // by calling the base method.
   LBRClient::waitForCommand();

   // If we want to command anything, we have to command them all the time; even in
   // waitForCommand(). This has to be done due to consistency checks. In this state it is 
   // only necessary, that some torque values are sent. The LBR does not take the 
   // specific value into account.

   switch (robotState().getClientCommandMode())
   {
   case NO_COMMAND_MODE:
      break;

   case POSITION:
      break;

   case WRENCH:
      break;

   case TORQUE:
      break;

   default:
      break;
   }

}


void PositionLBRClient::command()
{
   LBRClient::command();
  
   double ts = start_time + double(start_time_nano / 1000000000.0);
   double t = robotState().getTimestampSec() + (double) (robotState().getTimestampNanoSec() / 1000000000.0);
   t = t - ts;

   cout << t << '\t';
   memcpy(jointPos, robotState().getIpoJointPosition(), LBRState::NUMBER_OF_JOINTS * sizeof(double));

   //double jp[LBRState::NUMBER_OF_JOINTS];
   for (int i = 0; i < LBRState::NUMBER_OF_JOINTS; i++)
   {
      if ((0 <= t) && (t <= tb[i])) {
         jointPos[i] = _positions[i] + a[i] * t * t / 2;         
      } else if ((tb[i] < t) && (t <= (tf[i] - tb[i]) )) {
         jointPos[i] = 0.5 * (_positions_des[i] + _positions[i] - v * tf[i]) + v * t;
      } else if (( (tf[i] - tb[i]) < t) && (t <= tf[i])) {
         jointPos[i] = _positions_des[i] - 0.5 * a[i] * tf[i] * tf[i] + a[i] * tf[i] * t - 0.5 * a[i] * t * t;
      }
      //jointPos[i] = jp[i];// * 0.99 + jp[i] * (1.0 - 0.99);
      cout << jointPos[i] << ' ';
   }
   cout << endl;
   
   
   // // memcpy(_positions, robotState().getIpoJointPosition(), LBRState::NUMBER_OF_JOINTS * sizeof(double));
  if (robotState().getClientCommandMode() == POSITION) {
    robotCommand().setJointPosition(jointPos);
  }

} 