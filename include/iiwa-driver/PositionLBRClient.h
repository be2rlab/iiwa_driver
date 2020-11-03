#ifndef _KUKA_FRI_MY_LBR_CLIENT_H
#define _KUKA_FRI_MY_LBR_CLIENT_H

#include "friLBRClient.h"


/**
 * \brief Template client implementation.
 */
class PositionLBRClient : public KUKA::FRI::LBRClient
{
   
public:
      
   /**
    * \brief Constructor.
    */
   PositionLBRClient();
   
   /** 
    * \brief Destructor.
    */
   ~PositionLBRClient();
   
   /**
    * \brief Callback for FRI state changes.
    * 
    * @param oldState
    * @param newState
    */
   virtual void onStateChange(KUKA::FRI::ESessionState oldState, KUKA::FRI::ESessionState newState);
   
   /**
    * \brief Callback for the FRI session states 'Monitoring Wait' and 'Monitoring Ready'.
    * 
    * If you do not want to change the default-behavior, you do not have to implement this method.
    */
   virtual void monitor();
   
   /**
    * \brief Callback for the FRI session state 'Commanding Wait'.
    * 
    * If you do not want to change the default-behavior, you do not have to implement this method.
    */
   virtual void waitForCommand();
   
   /**
    * \brief Callback for the FRI state 'Commanding Active'.
    * 
    * If you do not want to change the default-behavior, you do not have to implement this method.
    */
   virtual void command();

private:
   double _positions[KUKA::FRI::LBRState::NUMBER_OF_JOINTS];      //!< commanded positions
   double _positions_des[KUKA::FRI::LBRState::NUMBER_OF_JOINTS];      //!< commanded positions
   
   double start_time;
   double start_time_nano;

   double rad;
   double tf[KUKA::FRI::LBRState::NUMBER_OF_JOINTS];
   double tb[KUKA::FRI::LBRState::NUMBER_OF_JOINTS];
   double a[KUKA::FRI::LBRState::NUMBER_OF_JOINTS];
   double v;

   double jointPos[KUKA::FRI::LBRState::NUMBER_OF_JOINTS];
};

#endif // _KUKA_FRI_MY_LBR_CLIENT_H