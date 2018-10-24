#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <wiringPi.h>

int main ( int argc, int argv[] )
{
  std::cout << "-----DRONE BATTERY STATION-----\n\n";
  std::cout << "running....\n\n";
  delay(100);
  std::cout << "-------------------------------\n\n";
  std::cout << " Wailting Drone connection\n\n";
  delay(100);

  if(wiringPiSetup() == -1 )return -1;
  pinMode(29, INPUT);
  int num = 0;
  int flag_s = 0; //station status flag 0 = not occupied, 1 = occupied
  int flag_e = 1; //end flag
  try
    {
      // Create the socket
      ServerSocket server ( 30000 );

      while ( true )
	{

	  ServerSocket new_sock;
	  server.accept ( new_sock );

	  try
	    {
	      while ( true )
		{
		  flag_e = 1;
		  std::cout << " Waiting Drone connection\n\n\n";
		  std::string data;
		  new_sock >> data;
		  //std::cout << data;

		  while( flag_e != 0 ) // Start of REQUEST
		  {
		   /*Drone requst landing permission*/
		   if ( data.compare( "REQUEST" ) == 0 && flag_s == 0)
		   {
		    std::cout << " DONRE request landing permission \n\n";
		    delay(100);
		    std::cout << " CHEKING...\n\n";
		    
		    delay(500);
		    while( flag_e != 0 ) // Star of COMMUNICATE 
		    {
                     // input is 0 == station not occupied
		     if( (num = digitalRead(29) ) == 0)
		     {
		 	std::cout << " STATION NOT OCCUPIED \n\n";
		 	std::cout << " SENDING ACCEPT MASSAGE \n\n ";
		 	// station send acept message
		 	new_sock << "ACCEPT\n";

                        //wait drone respone
	  		while(flag_e != 0)
			{ // Start of after Drone_certified
		 	 new_sock >> data;
		 	
		 	 //drone send certified message
		 	 if( data.compare( "CERTIFIED" ) == 0)
		 	 {
		 		std::cout << " DRONE START COMING FOR CHANGING BATTERY\n\n ";
		 		flag_s = 1;

				//Drone coming...
				while( (num = digitalRead(29))== 0)
				{
					std::cout << "DRONE IS ON ITS WAY...\n\n\n";
					delay(200);
				}
				std::cout << " DRONE ARIVE\n\n\n "; 
				//Drone arive station
				while( (num = digitalRead(29)) == 1 )
				{
					std::cout << "DRONE CHANGING BATTERY....\n\n\n\n";
					delay(200);
				}

				std::cout << "DRONE BATTERY CHANGE IS FINISHED!! \n\n\n\n";
				flag_e = 0;
				flag_s = 0;
				break;
		 	 }

			}
		     }
		    }//End of COMMINICATE

		   }

		   else if(data.compare( "REQUEST" ) == 0 && flag_s == 1)
		   {
		   	std::cout << " STATION OCCUPIED !! \n\n";
			std::cout << " DRONE LANDING DENEYED !! \n\n";
			new_sock << "DENEIED\n";
			break;
	 	   }
		  } // End of  REQUEST

		  if (data.compare ( "QUIT") == 0)
		  {
		   break;
		  }
 
		  //new_sock << data;
		}
	    }
	  catch ( SocketException& ) {}

	}
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

  return 0;
}
