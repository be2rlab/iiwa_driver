#include <cstdlib>
#include <cstdio>
#include <cstring> // strstr


#include "friUdpConnection.h"
#include "friClientApplication.h"
#include "PositionLBRClient.h"

using namespace KUKA::FRI;

#define DEFAULT_PORTID 30200

// /**
//  * @brief Prints versition of FRI library.
//  * 
//  */
// void print_version() {
//     std::cout << "Sunrise.Workbench FRI client SDK version is " << FRI_CLIENT_SDK_VERSION << "\n";
// }

/**
 * @brief The main function that starts everything.
 * 
 * @return int 0 if no errors.
 */
int main (int argc, char** argv)
{

  if (argc > 1)
  {
    if ( strstr (argv[1],"help") != NULL)
    {
      printf(
      "\nThe application\n\n"
      "\tCommand line arguments:\n"
      "\t1) remote hostname (optional)\n"
      "\t2) port ID (optional)\n"
      );
      return 1;
    }
  }
  char* hostname = (argc >= 2) ? argv[1] : NULL;
  int port = (argc >= 3) ? atoi(argv[2]) : DEFAULT_PORTID;

  PositionLBRClient lbr_client;
  UdpConnection connection;
  ClientApplication app(connection, lbr_client);
  app.connect(port, hostname);

  bool success = true;
  while (success)
  {
    
    success = app.step();
    
    // check if we are in IDLE because the FRI session was closed
    if (lbr_client.robotState().getSessionState() == IDLE)
    {
      // In this demo application we simply quit.
      // Waiting for a new FRI session would be another possibility.
      break;
    }
  }

  app.disconnect();

  return 0;
}

