#include "timelapse.h"

//mode menu title
const prog_char timeMenu[] PROGMEM= {"TimeLapse"};

 //option Menu titles
 const prog_char startdelay[] PROGMEM="delay";
 const prog_char delta[] PROGMEM="delta";
const prog_char numShots[] PROGMEM = "#shots";

const prog_char * timeSelectMenu[] PROGMEM  = 	   //options menu order
{   
startdelay,
delta,
numShots,
};

//option order should match timeSelectMenu order
const int TIME_DELAY = 0; 
const int TIME_DELTA = 1;
const int TIME_NUMSHOTS = 2;

/***********************************************************
 * 
 * TimeLapse
 *
 *  
 * 
 ***********************************************************/
TimeLapse::TimeLapse(){
	
	    triggerState_ = 0; //off

		setOption(TIME_DELAY,0);    //set time delay to 0
		setOption(TIME_DELTA,0);    //set time delta to 0
		setOption(TIME_NUMSHOTS,0); //set #shots to 0
		select_ = 0;  //set 
		max_delay_ = 600; //10minutes
	
}

/***********************************************************
 * 
 * trigger
 *
 *  
 * 
 ***********************************************************/
boolean TimeLapse::trigger()
{
  resetShutter(); //10 millisec delay, between high and low

	int currentTime = millis()/1000;
	int elapsedTime = currentTime - startBttnTime/1000;
  
  if (elapsedTime >= option(TIME_DELTA)) 
  {
	//times up,take a shot
    startBttnTime = millis();
	shotCounter_++; 
	return true;
  }
  else
  {
	return false; 
  }

	
	
}

/***********************************************************
 * 
 * countDown
 *
 *  
 * 
 ***********************************************************/
int TimeLapse::countDown()
{
	int currentTime = millis()/1000;
	int elapsedTime = currentTime - startBttnTime/1000;
	int remainTime = option(TIME_DELTA) - elapsedTime;
	
	/*
	Serial.print("option: ");
	Serial.println(option(TIME_DELTA));
	
	Serial.print("elapsedTime: ");
	Serial.println(elapsedTime);
	*/
	return remainTime;

}

/***********************************************************
 * 
 * decSetting
 *
 *  
 * 
 ***********************************************************/
void TimeLapse::decSetting(char buffer[])
{

	
		switch (select_)
	    {
	     case TIME_DELAY:
	 	  decOption(TIME_DELAY, 18600); //max secs
		   formatString(option(TIME_DELAY),buffer); //format and save string in buffer
	      break;
	    case TIME_DELTA:
	      decOption(TIME_DELTA, 18600);
	 	  formatString(option(TIME_DELTA),buffer);
	      break;
	    case TIME_NUMSHOTS:
	      decOption(TIME_NUMSHOTS, 5000); 
		  itoa (option(TIME_NUMSHOTS),buffer,10);
	      break;
	    default: 
	      break;
	    }

}

/***********************************************************
 * 
 * incSetting
 *
 * 
 * 
 ***********************************************************/
void TimeLapse::incSetting(char buffer[])
{
	
	
		switch (select_)
	    {
	     case TIME_DELAY:
	 	   incOption(TIME_DELAY, 18600); //max secs
		   formatString(option(TIME_DELAY),buffer); 
	      break;
	    case TIME_DELTA:
	      incOption(TIME_DELTA, 18600);
	 	  formatString(option(TIME_DELTA),buffer);
	      break;
	    case TIME_NUMSHOTS:
	      incOption(TIME_NUMSHOTS, 5000); 
		  itoa (option(TIME_NUMSHOTS),buffer,10);
	      break;
	    default: 
	      break;
	    }
		
}

/***********************************************************
 * 
 * getModeMenu
 *
 *  
 * 
 ***********************************************************/
void TimeLapse::getModeMenu(char buffer[])
{
	 //reads the timeMenu title from flash
	 strcpy_P(buffer, timeMenu); 
	
}

/***********************************************************
 * 
 * getSelectMenu
 *
 *  
 * 
 ***********************************************************/
void TimeLapse::getSelectMenu(char buffer[])
{
	 //reads the timeSelectMenu options from flash memory
	 strcpy_P(buffer, (const prog_char *)pgm_read_word(&(timeSelectMenu[select_])));
}