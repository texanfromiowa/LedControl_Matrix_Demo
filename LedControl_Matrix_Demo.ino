/**************************************************************
  Name      LedControl_Matrix_Demo                                
  Author    Bob Powell 
            texanfromiowa@gmail.com
            Copyright (C) 2012-2013, Parallelus Automation, Inc.
          
  Date      May 23, 2013    
  Modified  June 19, 2013                                
  Version   1.0.0      
  Arduino   1.0.5
  
  
  Notes     Example for using one Maxim MAX7219 chip and a 8x8 Matrix display.
  
            Because the datasheet for the part I used did not accurately reflect
            the actual pin configuration on the matrix, it will not be included
            here.  For the purposes of this example code, the pin configuration
            is not needed.
            
            Since this example uses the same library, LedControl, and chip,
            Maxim MAX7219, as a previous example using a 7-segment display, much
            of the commentary is the same.
            
            Please note that should you be able rotate the display by changing
            from the use of the setColumn to the setRow functions, and vice versa.
            In the demo used on Lets Make It (www.letsmakeit.tv), what appears as
            a row uses the setColumn function, and a column uses the setRow function.
            
            One more detail, on the show, some of the functions were slowed for the
            camera.  They are normal speed in this code.
            
            This program is heavily commented to explain a number
            of concepts.  PLEASE READ!!!
                   
            
Legal Stuff:
============

            This program is free software: you can redistribute it and/or modify
            it under the terms of the GNU General Public License as published by
            the Free Software Foundation, either version 3 of the License, or
            at your option, any later version.
	 
            This program is distributed in the hope that it will be useful,
            but WITHOUT ANY WARRANTY; without even the implied warranty of
            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
            GNU General Public License for more details.
	 
            You should have received a copy of the GNU General Public License
            along with this program.  If not, see <http://www.gnu.org/licenses/>. 
   
     
Personal note:
==============

            If you do something interesting with this code, expand it, or just
            have a question, please email me at the address above.  

            I hope you find this example helpful.  Enjoy.

            Bob

****************************************************************/
#include "LedControl.h"

/*  The chip used, which is supported by this library, is a Maxim
    MAX7129.  Here is the datasheet:
    http://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf

    Please read the datasheet for details concerning connections.
    
    In this case, here are the important connections:
    
    Arduino Pin       MAX7219 Pin
    ===========       ===========
         12                1        DataIn
         11               13        Clock
         10               12        Load 
         
     The iset pin, number 18, on the MAX7219 has 40k ohm resistance
     (four 10k ohm resistors in series) connected to it.
     
     If multiple chips are used, they must be daisy chained together.
     Pin 24, DataOut, of the first chip should be connected to DataIn
     of the second chip.  DataOut of the second chip is connected to
     DataIn of the third chip, etc. etc.
     
     The LedControl library makes connecting to the chip easy.  To 
     setup the lc class, the argument are:
     LedControl(DataIn pin, Clock pin, Load pin, number of MAX7219 chips)
     
     In our case, we have only one MAX7219 connected, so our setup
     is the next line of code.
 */
  LedControl lc=LedControl(12,11,10,1);

  //  This created the pattern for numbers.  The are organized in 5x7 arrays.
  int NUM1[] = {B00000000,B00100000,B01100000,B00100000,B00100000,B00100000,B00100000,B11111000};
  int NUM2[] = {B00000000,B01110000,B10001000,B00001000,B00110000,B01000000,B10000000,B11111000};
  int NUM3[] = {B00000000,B01110000,B10001000,B00001000,B01110000,B00001000,B10001000,B01110000};
  int NUM4[] = {B00000000,B10010000,B10010000,B10010000,B11111000,B00010000,B00010000,B00010000};
  int NUM5[] = {B00000000,B11111000,B10000000,B10000000,B11110000,B00001000,B10001000,B01110000};
  int NUM6[] = {B00000000,B01110000,B10001000,B10000000,B11110000,B10001000,B10001000,B01110000};
  int NUM7[] = {B00000000,B11111000,B00001000,B00001000,B00010000,B00100000,B01000000,B10000000};
  int NUM8[] = {B00000000,B01110000,B10001000,B10001000,B01110000,B10001000,B10001000,B01110000};
  int NUM9[] = {B00000000,B01110000,B10001000,B10001000,B01111000,B00001000,B10001000,B01110000};
  int NUM0[] = {B00000000,B01110000,B10001000,B10001000,B10001000,B10001000,B10001000,B01110000};

  // Pointers to all the numbers
  int* numbers[] = {NUM1,NUM2,NUM3,NUM4,NUM5,NUM6,NUM7,NUM8,NUM9,NUM0};

  //  This created the pattern for letters.  The are organized in 7x7 arrays.
  //  I found the basis for these patterns on the Arduino Playground.  Unfortunately,
  //  as I write these comments, I cannot find where I first found them so I can give
  //  credit where it is do.  If someone finds the source, please email at the address
  //  above so I can update the comments.
  int A[] = {B00000000,B00010000,B00101000,B01000100,B10000010,B11111110,B10000010,B10000010};
  int B[] = {B00000000,B11111100,B01000010,B01000010,B01111100,B01000010,B01000010,B11111100};
  int C[] = {B00000000,B00111100,B01000000,B10000000,B10000000,B10000000,B01000000,B00111100};
  int D[] = {B00000000,B11111000,B01000100,B01000010,B01000010,B01000010,B01000100,B11111000};
  int E[] = {B00000000,B11111100,B10000000,B10000000,B11111000,B10000000,B10000000,B11111100};
  int F[] = {B00000000,B11111100,B10000000,B10000000,B11111000,B10000000,B10000000,B10000000};
  int G[] = {B00000000,B00111110,B01000000,B10000000,B10011110,B10000010,B01000010,B00111110};
  int H[] = {B00000000,B10000010,B10000010,B10000010,B11111110,B10000010,B10000010,B10000010};
  int I[] = {B00000000,B11111110,B00010000,B00010000,B00010000,B00010000,B00010000,B11111110};
  int J[] = {B00000000,B01111110,B00001000,B00001000,B00001000,B00001000,B10001000,B01110000};
  int K[] = {B00000000,B10000100,B10001000,B10010000,B11100000,B10010000,B10001000,B10000100};
  int L[] = {B00000000,B10000000,B10000000,B10000000,B10000000,B10000000,B10000000,B11111100};
  int M[] = {B00000000,B11101100,B10010010,B10010010,B10010010,B10010010,B10010010,B10010010};
  int N[] = {B00000000,B10000010,B11000010,B10100010,B10010010,B10001010,B10000110,B10000010};
  int O[] = {B00000000,B00111000,B01000100,B10000010,B10000010,B10000010,B01000100,B00111000};
  int P[] = {B00000000,B11111100,B01000010,B01000010,B01111100,B01000000,B01000000,B01000000};
  int Q[] = {B00000000,B00111000,B01000100,B10000010,B10000010,B10001010,B01000100,B00111010};
  int R[] = {B00000000,B11111100,B01000010,B01000010,B01111100,B01001000,B01000100,B01000010};
  int S[] = {B00000000,B01111110,B10000000,B10000000,B01111100,B00000010,B00000010,B11111100};
  int T[] = {B00000000,B11111110,B00010000,B00010000,B00010000,B00010000,B00010000,B00010000};
  int U[] = {B00000000,B10000010,B10000010,B10000010,B10000010,B10000010,B10000010,B01111100};
  int V[] = {B00000000,B10000010,B10000010,B10000010,B10000010,B01000100,B00101000,B00010000};              
  int W[] = {B00000000,B10000010,B10010010,B10010010,B10010010,B10010010,B10010010,B01101100};
  int X[] = {B00000000,B10000010,B01000100,B00101000,B00010000,B00101000,B01000100,B10000010};
  int Y[] = {B00000000,B10000010,B01000100,B00101000,B00010000,B00010000,B00010000,B00010000};
  int Z[] =  {B00000000,B11111110,B00000100,B00001000,B00010000,B00100000,B01000000,B11111110};
  int COLON[] = {B00000000,B00000000,B00011000,B00011000,B00000000,B00011000,B00011000,B00000000};
  int DASH[] =  {B00000000,B00000000,B00000000,B00000000,B00111100,B00000000,B00000000,B00000000};
  int UNDERSCORE[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11111111};
  int ALLON[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};                  
  int CHECKER[] = {B01010101,B10101010,B01010101,B10101010,B01010101,B10101010,B01010101,B10101010};
         
  int SMILE[] = {B00000000,B00000000,B01001000,B00000000,B10000100,B01001000,B00110000,B00000000};                     
  int SPACE[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

  // Pointers to all the letters
  int* letters[] = {A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,COLON,DASH,UNDERSCORE,ALLON,SPACE,SMILE};

              


/**************************************************************
Function: setup
Purpose:  set up Arduino
Args:     none
Returns:  nothing
Notes:    This function is required by the Arduino
***************************************************************/
void setup() {
 
  // Wakeup the MAX7219
  // The first variable, like most functions in the library, is for which display
  // the function is referencing.  In this example, only one chip is used, so the 
  // variable points to chip '0'.  If multiple chips are used, multiple function 
  // calls would be used pointing to chips 1, 2, etc. 
  // Using 'true' would turn the chip off (shutting down is true)
  lc.shutdown(0,false);
  // Set duty cycle for each MAX7219
  // Values of 0 to 16 are valid.
  // To have the display look right on the video camera, the intensity is turned down  
  lc.setIntensity(0,3);
  // Clear any leftover values
  lc.clearDisplay(0);
    
  // This is needed for the randomLeds() function below,
  // along with any other code that uses a random number
  // and removed if random numbers are not used.  
  // Quoted from http://arduino.cc/en/Reference/random - 
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  //
  // In other words, set this to any analog pin that is
  // not used.
  randomSeed(analogRead(0));
    
} // end of setup

/**************************************************************
Function: loop
Purpose:  loop funtion for Arduino
Args:     none
Returns:  nothing
Notes:    This function is required by the Arduino, and the 
          Arduino will loop through this function indefinately.
***************************************************************/
void loop() { 
  
  // Set standard delay between effects
  int delaytime = 1000;
  
  // Turn all lights on
  setLetter(ALLON);
  delay(delaytime * 2);
 
  lc.clearDisplay(0);  
  delay(delaytime);
  
  //  cycle back and forth 1 column of leds
  columnsEffect(3,100);
  lc.clearDisplay(0);
  delay(delaytime);

  //  cycle back and forth 1 row of leds
  rowsEffect(3,100);
  lc.clearDisplay(0);
  delay(delaytime);

 // metering effect using random numbers
  meterEffect(500, 50);
  lc.clearDisplay(0);
  delay(delaytime);
  
  // cycle back and forth diagonally
  diagonalEffect(2,150);
  lc.clearDisplay(0);
  delay(delaytime);

  // small box to large box, and reverse, effect.
  boxEffect(5,150);
  lc.clearDisplay(0);
  delay(delaytime);
  
  // checkboard marque effect
  checkerboard(10,300);
  lc.clearDisplay(0);
  delay(delaytime);

  //  cycle through the numbers
  for(int i = 0; i < 10; i++){
    setLetter(numbers[i]);
    delay(delaytime);
  }

  //  cycle through the letters
  for(int i = 0; i < 31; i++){
    setLetter(letters[i]);
    delay(delaytime);
  }

 // A different way to turn on all the leds in the matrix,
 // one by one. 
 for(int i = 0; i < 8; i++)
    for(int k = 0; k < 8; k++)
      lc.setLed(0,i,k,false);   
  
  delay(delaytime);
   
  
} // end of loop


/**************************************************************
Function: setLetter
Purpose:  Posts a letter or number to the display
Args:     binary array plot of what is displayed.
Returns:  nothing
Notes:    
***************************************************************/
void setLetter(int letter[]){   
     for(int i = 0; i < 8; i++){
       lc.setColumn(0,i,letter[i]);
     }   
}


/**************************************************************
Function: boxEffect
Purpose:  cycles from a large outer box to a small box, and reversed
Args:     int duration - how long an led is on 
          int num - how many times to cycle through effect     
Returns:  nothing
Notes:    
***************************************************************/
void boxEffect(int num, int duration){

  // create array of the boxes to display
  int BOX[4][8] = { {B11111111,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B11111111},
                    {B00000000,B01111110,B01000010,B01000010,B01000010,B01000010,B01111110,B00000000},
                    {B00000000,B00000000,B00111100,B00100100,B00100100,B00111100,B00000000,B00000000},
                    {B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000} };
              
  
  // Cycle from the large box to the inner box
  for(int j = 0; j < num; j++){
    for(int i = 0 ; i < 4; i++){
      setLetter(BOX[i]);
      delay(duration);
    }
    // Since the display is already displaying the inner most
    // box, it does not need to be displayed again.  Also,
    // the outer box will be displayed in the loop above so
    // it does not need displaying here
    for(int i = 2; i > 0; i--){
      setLetter(BOX[i]);
      delay(duration);
    }   
  }  
  
  //  Display the outer box one last time 
  setLetter(BOX[0]);
  delay(duration);
}

/**************************************************************
Function: meterEffect
Purpose:  create a Spectrum analyzer effect using random numbers
Args:     int duration - how long an led is on 
          int num - how many times to cycle through effect     
Returns:  nothing
Notes:    
***************************************************************/
void meterEffect(int num, int duration){

  // create each meter bar, random number holder for each column, and a counter
  int meter[] = {B00000001,B00000011,B00000111,B00001111,B00011111,B00111111,B01111111,B11111111};
  int randomnum[8];
  int randomnumindex[] = {0,0,0,0,0,0,0,0};
  
  for(int i = 0; i < 8; i++){ 
   // this while loop should not be nessessary, but in testing
   // the code, I found that the generator returned results
   // outside what I set, so this while loop was create.
    while((randomnum[i] < 0) || (randomnum[i] > 7)){
      randomnum[i] = random(0,8);    
    }
  }

  int j = 0;
  
  // cycle through the effect 'num' times
  // note that each column is indepentant of the others
  for(int i = 0; i <= num; i++){
    
    for(j = 0; j < 8; j++){

      lc.setRow(0,j,meter[randomnumindex[j]]);
      
      if(randomnumindex[j] < randomnum[j]){
        randomnumindex[j] = randomnumindex[j] + 1;
      }
      else{
        randomnum[j] = randomnum[j] - 1;
        randomnumindex[j] = randomnumindex[j] - 1;
      }
      
      
      if(randomnum[j] <= 0){
        randomnum[j] = random(0,8);
        randomnumindex[j] = 0;
      }
    }
    
    delay(duration); 
  }
  
  
  // When the above loop finishes, each column cycles down to nothing 
  // in an orderly fashon.
  bool done = false;
  while(done == false){
  
    for(j = 0; j < 8; j++){
      if(randomnumindex[j] >= 0)
        lc.setRow(0,j,meter[randomnumindex[j]]);
      else
        lc.setRow(0,j,0);   
      
      randomnumindex[j] = randomnumindex[j] - 1;
    }
     
    // Set the 'done' boolean to true, then check if any column
    // is not finished. Just one column that is not finished will
    // reset the boolean to false.
    done = true;
    
    for(int i = 0; i < 8; i++){      
      if(randomnumindex[i] >= 0)
        done = false;      
    }    
    
    delay(duration); 
    
  }
  
  
  
}

/**************************************************************
Function: columnsEffect
Purpose:  Cycle one column at a time, then reverse
Args:     int duration - how long an led is on 
          int num - how many times to cycle through effect     
Returns:  nothing
Notes:    
***************************************************************/
void columnsEffect(int num, int duration){
 
  for(int i = 0; i < num; i++){
    
    // Cycle from one end of the display to the other 
    for(int j = 0; j < 8; j++){
      lc.clearDisplay(0);
      lc.setColumn(0,j,255);
      delay(duration); 
    }
    // Since the display is already displaying the last column,
    // it does not need to be displayed again.  Also, the first
    // column will be displayed in the loop above so it does 
    // not need displaying here
    for(int j = 6; j > 0; j--){
      lc.clearDisplay(0);
      lc.setColumn(0,j,255);
       delay(duration); 
    }
      
  } 
  
  // Display the first column one last time
  lc.clearDisplay(0);
  lc.setColumn(0,0,255);
  delay(duration); 
  
}

/**************************************************************
Function: rowsEffect
Purpose:  Cycle one column at a time, then reverse
Args:     int duration - how long an led is on 
          int num - how many times to cycle through effect     
Returns:  nothing
Notes:    
***************************************************************/
void rowsEffect(int num, int duration){
 
  for(int i = 0; i < num; i++){
    
    // Cycle from one end of the display to the other 
    for(int j = 0; j < 8; j++){
      lc.clearDisplay(0);
      lc.setRow(0,j,255);
      delay(duration); 
    }
    // Since the display is already displaying the last row,
    // it does not need to be displayed again.  Also, the first
    // row will be displayed in the loop above so it does 
    // not need displaying here
    for(int j = 6; j > 0; j--){
      lc.clearDisplay(0);
      lc.setRow(0,j,255);
      delay(duration); 
    }
      
  } 
  
  // Display the first row one last time
  lc.clearDisplay(0);
  lc.setRow(0,0,255);
  delay(duration); 
  
}

/**************************************************************
Function: checkerboard
Purpose:  creates a marque effect in a checkboard patter
Args:     int duration - how long an led is on 
          int num - how many times to cycle through effect     
Returns:  nothing
Notes:    
***************************************************************/
void checkerboard(int num, int duration){
  
  for(int i = 0; i < num; i++){
    for(int k = 0; k < 9; k++){
      lc.setColumn(0,k,CHECKER[k]);
    }
    delay(duration);
    for(int k = 0, j = 7; k < 8; k++, j-- ){
      lc.setColumn(0,k,CHECKER[j]);
    }
    delay(duration);
  }  
  
}


/**************************************************************
Function: diagonalEffect
Purpose:  cycle from one corner to another diagonally, and reverse
Args:     int duration - how long an led is on 
          int num - how many times to cycle through effect     
Returns:  nothing
Notes:    
***************************************************************/
void diagonalEffect(int num, int duration){

  // create the pattern for the diagonals
  int DIAG[15][8] ={{B10000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
                    {B01000000,B10000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
                    {B00100000,B01000000,B10000000,B00000000,B00000000,B00000000,B00000000,B00000000},
                    {B00010000,B00100000,B01000000,B10000000,B00000000,B00000000,B00000000,B00000000},
                    {B00001000,B00010000,B00100000,B01000000,B10000000,B00000000,B00000000,B00000000},
                    {B00000100,B00001000,B00010000,B00100000,B01000000,B10000000,B00000000,B00000000},
                    {B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000,B00000000},
                    {B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000},
                    {B00000000,B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000},
                    {B00000000,B00000000,B00000001,B00000010,B00000100,B00001000,B00010000,B00100000},
                    {B00000000,B00000000,B00000000,B00000001,B00000010,B00000100,B00001000,B00010000},
                    {B00000000,B00000000,B00000000,B00000000,B00000001,B00000010,B00000100,B00001000},
                    {B00000000,B00000000,B00000000,B00000000,B00000000,B00000001,B00000010,B00000100},
                    {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000001,B00000010},
                    {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000001} };
  
    // Cycle from one end of the display to the other 
  for(int j = 0; j < num; j++){
    for(int i = 0 ; i < 15; i++){
      setLetter(DIAG[i]);
      delay(duration);
    }
    // Since the display is already displaying the last row,
    // it does not need to be displayed again.  Also, the first
    // row will be displayed in the loop above so it does 
    // not need displaying here
    for(int i = 13 ; i > 0; i--){
      setLetter(DIAG[i]);
      delay(duration);
    }
    
  }  

  // Display the first row one last time
  setLetter(DIAG[0]);
  delay(duration);
}



