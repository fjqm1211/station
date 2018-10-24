#include <iostream>
#include <wiringPi.h>

int  main()
{
	if(wiringPiSetup() == -1 ) return -1;
	
	pinMode(29, INPUT);
	int num = 0;
		
	std::cout << "reading \n ";
	while(1)
	{
		num = digitalRead(29);
		//delay(100);
		if(num == 1) std::cout<< "read \n";
		//digitalWrite(29,0);
		delay(100);
		num  = 0;
	}
	return 0;
}
