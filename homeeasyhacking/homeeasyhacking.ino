/*
 * Example program using the HomeEasy class.
 */

#include "HomeEasy.h"

HomeEasy homeEasy;
//Buffer serial data to accept strings
char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character


/**
 * Set up the serial interface and the HomeEasy class.
 */
void setup()
{
	Serial.begin(9600);
	
	homeEasy = HomeEasy();
	
	homeEasy.registerSimpleProtocolHandler(printSimpleResult);
	homeEasy.registerAdvancedProtocolHandler(printAdvancedResult);
	
	homeEasy.init();
}


/**
 * No processing is required in the loop for receiving.
 */
void loop()
{
	unsigned long sender = 15556058;
	unsigned int recipient = 13;
	bool command = true;
	bool group = false;

       if(Comp("lightsOn")==0){
           homeEasy.sendAdvancedProtocolMessage(sender, recipient, command, group);
           Serial.println("turning on");
        }
        else if(Comp("lightsOff")==0){
          command = false;
           homeEasy.sendAdvancedProtocolMessage(sender, recipient, command, group);
           Serial.println("turning off");  
        }

        
     
 
    /* To create more commands, send a different string and listen for it with another
    * else if statement:
    * else if(Comp("ovenOn")==0){}
    */
}

char Comp(char* This) {
    while (Serial.available() > 0) // Don't read unless
                                   // there you know there is data
    {
        if(index < 19) // One less than the size of the array
        {
            inChar = Serial.read(); // Read a character
            inData[index] = inChar; // Store it
            index++; // Increment where to write next
            inData[index] = '\0'; // Null terminate the string
        }
    }

    if (strcmp(inData,This)  == 0) {
        for (int i=0;i<19;i++) {
            inData[i]=0;
        }
        index=0;
        return(0);
    }
    else {
        return(1);
    }
}


/**
 * Print the details of the advanced protocol message.
 */
void printAdvancedResult(unsigned long sender, unsigned int recipient, bool on, bool group)
{
	Serial.println("advanced protocol message");
	
	Serial.print("sender ");
	Serial.println(sender);
	
	Serial.print("recipient ");
	Serial.println(recipient);
	
	Serial.print("on ");
	Serial.println(on);
	
	Serial.print("group ");
	Serial.println(group);
	
	Serial.println();
}


/**
 * Print the details of the simple protocol message.
 */
void printSimpleResult(unsigned int sender, unsigned int recipient, bool on)
{
	Serial.println("simple protocol message");
	
	Serial.print("sender ");
	Serial.println(sender);
	
	Serial.print("recipient ");
	Serial.println(recipient);
	
	Serial.print("on ");
	Serial.println(on);
	
	Serial.println();
}
