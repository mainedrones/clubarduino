


/*
 * 
 * four button arduino lock
 */

const int button1 = 8; //first button is on pin 8
const int button2 = 9; //second is on pin 9
const int button3 = 10; //third is pin 10
const int button4 = 11; //fourth is pin 11

const int redLed = 4; //red LED is on pin 4
const int greenLed = 12; //green LED is pin 12



int code[] = {1, 2, 3, 4}; //the desired code is entered in this array,
//separated by commas

int entered[4]; //create a new empty array for the code entered by

//the user (has 4 elements)
void setup() { //run once at sketch startup
  
  Serial.begin(9600); //begin Serial
  pinMode(button1, INPUT); //button 1 is an input
  pinMode(button2, INPUT); //button 2 is an input
  pinMode(button3, INPUT); //button 3 is an input
  pinMode(button4, INPUT); //button 4 is an input
  pinMode(redLed, OUTPUT); //the red LED is an output
  pinMode(greenLed, OUTPUT); // the green LED is an output

  setupLights(); //run the setupLights routine
  setupLights(); //run it again
    
  delay(650); //delay (only for effect, :P not needed)

  digitalWrite(redLed, HIGH); //turn the red LED on
  
  for (int i = 0; i < 4; i++) { //work through numbers 0-3
    Serial.println(code[i]); //print each digit of the code
    Serial.println(entered[i]); //print each element of the entered[]
    //array (this was for me to check that it
    //started at 0
  }
}



void loop() { //run repeatedly
  if (digitalRead(button1) == HIGH) { //if button1 is pressed
    checkEntered1(1); //call checkEntered and pass it a 1
    delay(250);//wait, needed for correct functioning, otherwise
    //buttons are deemed to be pressed more than once
  }
  else if (digitalRead(button2) == HIGH) { //if button2 is pressed
    checkEntered1(2); //call checkEntered1 and pass it a 2
    delay(250); //wait
  }
  else if (digitalRead(button3) == HIGH) { //if button3 is pressed
    checkEntered1(3); //call checkEntered1 and pass it a 3
    delay(250); //wait
  }
  else if (digitalRead(button4) == HIGH) {  
    checkEntered1(4); //call checkEntered1 and pass it a 4
    delay(250); //wait
  }
}


void checkEntered1(int button ) { //check the first element of the entered[] array
  if (entered[0] != 0) { //if it is not a zero, i.e. it has already been inputted
    checkEntered2(button); //move on to checkEntered2, passing it "button"
  }

  else if (entered[0] == 0) { //if it is zero, i.e. if it hasn't been defined with a    button yet
    entered[0] = button; //set the first element as the button that has been    pressed
    Serial.print("1: "); Serial.println(entered[0]); //for debugging
  }

}


void checkEntered2(int button) { //check the second element of the entered[] array
  if (entered[1] != 0) { //if it is not a zero, i.e. it has already been inputted
    checkEntered3(button); //move on to checkEntered3, passing it "button"
  }

  else if (entered[1] == 0) { //if it is zero, i.e. if it hasn't been defined with a    button yet
    entered[1] = button; //set the second element as the button that has been    pressed
    Serial.print("2: "); Serial.println(entered[1]); //for debugging
  }

}


void checkEntered3(int button) { //check the third element of the entered[] array
  if (entered[2] != 0) { //if it is not a zero, i.e. it has already been inputted
    checkEntered4(button); //move on to checkEntered4, passing it "button"
  }

  else if (entered[2] == 0) { //if it is zero, i.e. if it hasn't been defined with    a button yet
    entered[2] = button; //set the third element as the button that has been    pressed
    Serial.print("3: "); Serial.println(entered[2]); //for debugging
  }

}


void checkEntered4(int button) { //check the fourth element of the entered[] array
  if (entered[3] == 0) { //if it is zero, i.e. if it hasn't been defined with a    button yet
    entered[3] = button; //set the final element as the button that has been    pressed
    Serial.print("4: "); Serial.println(entered[3]); //for debugging
    delay(100); //allow time for processing
    compareCode(); //call the compareCode function
  }
}


void compareCode() { //checks if the code entered is correct by comparing the  code[] array with the entered[] array
  for (int i = 0; i < 4; i++) { //these three lines are for debugging
    Serial.println(entered[i], BIN);
  }
  if ((entered[0] == code[0]) && (entered[1] == code[1]) && (entered[2] == code[2]) &&
      (entered[3] == code[3])) { //if all the elements of each array are equal
    digitalWrite(redLed, LOW); // turn the red LED off
    digitalWrite(greenLed, HIGH); //turn the green LED on
    delay(100); //wait for a bit
    digitalWrite(greenLed, LOW); //turn the green LED off
    delay(100); //wait for a bit
    digitalWrite(greenLed, HIGH); //turn the green LED on
    delay(100); //wait for a bit
    digitalWrite(greenLed, LOW); //turn the green LED off
    delay(100); //wait for a bit
    digitalWrite(greenLed, HIGH); //turn the green LED on
    loop(); //return to loop() (not really necessary)
  }

  else { //if you (or the intruder) get the code wrong
    flash(); //call the flash function
    for (int i = 0; i < 4; i++) { //this next loop is for debugging
      entered[i] = 0;
      Serial.println(entered[i]);
    }
  }
}

// blink the red lights
void flash() { 
  digitalWrite(redLed, LOW);
  delay(250);
  digitalWrite(redLed, HIGH);
  delay(250);
  digitalWrite(redLed, LOW);
  delay(250);
  digitalWrite(redLed, HIGH);
  delay(250);
  digitalWrite(redLed, LOW);
  delay(250);
  digitalWrite(redLed, HIGH);
  delay(250);
  digitalWrite(redLed, LOW);
  delay(250);
  digitalWrite(redLed, HIGH);
  delay(250);
}


void setupLights() { // a funky display run at reset
  digitalWrite(redLed, HIGH); //turn both
  digitalWrite(greenLed, HIGH); //LEDs on
  delay(75); //wait
  digitalWrite(redLed, LOW); //turn them
  digitalWrite(greenLed, LOW); //off again
  delay(75); //wait
}
