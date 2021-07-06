#include <EEPROM.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
#define RXD2 23
#define TXD2 13
const int MPU = 0x68; // I2C address of the MPU6050 accelerometer
int16_t AcX, AcY, AcZ;
int axis = 0;
int angle = 0;
int angle1 = 0;
String i2;
 int H;
 int tilt;
 int i=1;
char mode1, mode2, mode3,j=0,goc;
int pitch,roll;



void setup() {
     EEPROM.begin(512);
    Serial.begin(9600);
 Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
     Wire.begin();
     Wire.beginTransmission(MPU);
     Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
    //xTaskCreatePinnedToCore(Task2code, "Task1", 10000, NULL, 1, NULL, 1); 
    lox.begin();

 pinMode(32, OUTPUT);
 pinMode(33, OUTPUT);
 pinMode(25, OUTPUT);
 pinMode(17, OUTPUT);
 pinMode(16, OUTPUT);
 digitalWrite(32,LOW);
 digitalWrite(33,LOW);
 digitalWrite(25,LOW);
 digitalWrite(17,LOW);
 digitalWrite(16,LOW);
 // Serial.println("Serial Txd is on pin: "+String(TX));
  //Serial.println("Serial Rxd is on pin: "+String(RX));
   pinMode(26, INPUT);
   pinMode(27, INPUT);
   pinMode(14, INPUT);
   pinMode(12, INPUT);
   pinMode(15, INPUT);
   pinMode(2, INPUT);
   pinMode(4,INPUT);
   pinMode(5, INPUT);
   pinMode(18, INPUT);
   pinMode(19, INPUT);
    xTaskCreatePinnedToCore(Task2code, "Task1", 2000, NULL, 1, NULL, 0); 
    
    }

void Task2code( void * pvParameters ){
  
     for(;;){
     VL53L0X_RangingMeasurementData_t measure;
      lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
      H=measure.RangeMilliMeter/10;
     

     Wire.beginTransmission(MPU);
      Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
      Wire.endTransmission(false);
      Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
      AcX = Wire.read() << 8 | Wire.read(); // X-axis value
      AcY = Wire.read() << 8 | Wire.read(); // Y-axis value
      AcZ = Wire.read() << 8 | Wire.read(); // Z-axis value
     
       tilt = -(atan(-1 * AcX / sqrt(pow(AcY, 2) + pow(AcZ, 2))) * 180 / PI);
//      Serial2.print("n25.val=");
//      Serial2.print(tilt);
//      Serial2.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
//      Serial2.write(0xff);
//      Serial2.write(0xff);
//       Serial2.print("n24.val=");
//      Serial2.println(H);
//      Serial2.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
//      Serial2.write(0xff);
//      Serial2.write(0xff);
    delay(600);
  }

}

void loop() {
if (Serial.available() > 0) 
    {
       i2 = Serial.read();

   // Serial.println(i2);
//      delay(500);
       if(i2=="49")
      { i=1;
          digitalWrite(33,0);
         digitalWrite(25,1);
        digitalWrite(32,0);
        digitalWrite(17,0);
        delay(80);
    
      }
       if(i2=="99")
      { i=1;
         
         digitalWrite(32,0); 
         digitalWrite(33,0); 
         digitalWrite(25,0); 
         digitalWrite(17,0);
       
      }
     if(i2=="50")
      {  i=1;
         digitalWrite(33,1);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,0);
      delay(80);
      }  
      if(i2=="51")
      {  i=1;
         digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,1);
        digitalWrite(17,0);
         delay(80);   

 
      } 

     if(i2=="52")
      { i=1;
          digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,1);
         delay(80);   
  
 
      }  

   if(i2=="54")
        {
          
           i=10;
           digitalWrite(16,1); 
         delay(200); 
        digitalWrite(16, 0);
        i2=="1";
        } 

        
   if(i2=="53")
       {
          i=5;
           digitalWrite(16,1); 
         delay(200); 
        digitalWrite(16, 0);
        i2=="1";
        }

   if(i2=="55")
      {
          digitalWrite(16,1); 
            EEPROM.write(1,1);
            delay(20);
          EEPROM.commit(); 
          delay(20); 
         i=15;
         delay(150); 
        digitalWrite(16, 0);
        i2=="1";
   
        }
    
    if((i2=="56"))
       { 
          digitalWrite(16,1); 
         delay(180); 
         digitalWrite(16, 0);
        delay(180);
          digitalWrite(16,1); 
           EEPROM.write(1,2);
            delay(20); 
          EEPROM.commit();
           delay(20); 
          i=20;
         delay(150); 
         digitalWrite(16, 0);
         i2=="1";
         
       
       }
      
 if((i2=="57"))
      { 
        digitalWrite(16,1); 
         delay(180); 
         digitalWrite(16, 0);
        delay(180);
          digitalWrite(16,1); 
         delay(180); 
         digitalWrite(16, 0);
         delay(150);
           digitalWrite(16,1); 
           EEPROM.write(1,3);
            delay(20);   
          EEPROM.commit(); 
           delay(20);   
            
         i=25;;
         delay(130); 
         digitalWrite(16, 0);
         i2=="1";
        
        
      }

   if((i2=="97")&&EEPROM.read(1)==1)
         {    i=1;
              digitalWrite(16, 1);
               delay(100);
               EEPROM.write(2,tilt);
                delay(20);   
               EEPROM.commit(); 
                delay(20);   
               EEPROM.write(3, H);
                delay(20);   
               EEPROM.commit(); 
                delay(20);   
               
              digitalWrite(16, 0);
              i2=="1";
         }
         if((i2=="97")&&EEPROM.read(1)==2)
         {    i=1;
           digitalWrite(16, 1);
               delay(80);
               EEPROM.write(4,tilt);
                delay(20);   
               EEPROM.commit(); 
                delay(20);   
               EEPROM.write(5,H);
                delay(20);   
               EEPROM.commit(); 
                delay(20);   
               
                digitalWrite(16, 0);
                delay(150);
                digitalWrite(16, 1);
               delay(150);
                digitalWrite(16, 0);
         
                i2=="1";
         }
         
         if((i2=="97")&&EEPROM.read(1)==3)
         {    i=1;

         digitalWrite(16, 1);
               delay(80);
               EEPROM.write(6,tilt);
                delay(20);   
               EEPROM.commit(); 
                delay(20);   
               EEPROM.write(7, H);
                delay(20);   
               EEPROM.commit(); 
                delay(20);   
               
                digitalWrite(16, 0);
                delay(150);
                digitalWrite(16, 1);
               delay(150);
                digitalWrite(16, 0);
                delay(150);
                digitalWrite(16, 1);
              delay(150);
                digitalWrite(16, 0);
                delay(150);
                i2=="1";
         }
     if((i2=="98"))
         { 
          ESP.restart();
         }    

}
//     if(H<=29&&i==5 )
//          {
//          digitalWrite(33,0);
//         digitalWrite(25,1);
//        digitalWrite(32,0);
//        digitalWrite(17,0);
//          delay(50);
     if(digitalRead(26)==1&&H<29)
       {
        i=1;
         digitalWrite(33,0);
         digitalWrite(25,1);
        digitalWrite(32,0);
        digitalWrite(17,0);
      //  digitalWrite(13,1);
         delay(200);  
         digitalWrite(32,0); 
         digitalWrite(33,0); 
         digitalWrite(25,0); 
         digitalWrite(17,0);
         
           

        }
    if(digitalRead(26)==1&&H>=29)
       {
        i=1;
         digitalWrite(16,1);
         digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,0);
      //  digitalWrite(13,1);
         delay(150);  
         digitalWrite(16,0); 

        }
  //down xl1
    if(digitalRead(27)==1 && H>4 )
        {
          i=1;
         digitalWrite(33,1);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,0);
            
          delay(200);  
         digitalWrite(32,0); 
         digitalWrite(33,0); 
         digitalWrite(25,0); 
         digitalWrite(17,0);

        }
    if(digitalRead(27)==1 && H<=4 )
        {
          i=1;
         digitalWrite(16,1);
         digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,0);
      //  digitalWrite(13,1);
         delay(150);  
         digitalWrite(16,0); 
        }


   

        
  //up xl2
    if(digitalRead(14)==1&& tilt>4   )
        {
          i=1;
         digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,1);
        digitalWrite(17,0);
            
         delay(200); 
         
         digitalWrite(32,0); 
         digitalWrite(33,0); 
         digitalWrite(25,0); 
         digitalWrite(17,0);
 
   
        }

       if(digitalRead(14)==1&& tilt<=4   )
        {
          i=1;
          
         digitalWrite(16,1);
         digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,0);
      //  digitalWrite(13,1);
         delay(150);  
         digitalWrite(16,0); 
  
        }
  //up xl2
    if(digitalRead(12)==1 && tilt<76 )
        {
          i=1;
          digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,1);
            
         delay(200); 
         
         digitalWrite(32,0); 
         digitalWrite(33,0); 
         digitalWrite(25,0); 
         digitalWrite(17,0);
 
   
        }

      if(digitalRead(12)==1 && tilt>=76 )
        {
             i=1;
          
         digitalWrite(16,1);
         digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,0);
      //  digitalWrite(13,1);
         delay(150);  
         digitalWrite(16,0); 
 
   
        }
 
 if(digitalRead(15)==1)
        {
          
           i=10;
           digitalWrite(16,1); 
         delay(200); 
        digitalWrite(16, 0);
        
        } 

        
   if(digitalRead(2)==1)
       {
          i=5;
           digitalWrite(16,1); 
         delay(200); 
        digitalWrite(16, 0);
        }

       
      if(H<=29&&i==5 )
          {
          digitalWrite(33,0);
         digitalWrite(25,1);
        digitalWrite(32,0);
        digitalWrite(17,0);
          delay(50);
         digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,0);
          }
      if(H>29&&i==5 )
          {
          digitalWrite(16,1); 
         delay(50); 
          i=6;
         digitalWrite(16, 0);
          digitalWrite(33,0);
         digitalWrite(25,0);
         digitalWrite(32,0);
         digitalWrite(17,0);
          }

      if(  i==6&& tilt<=76)
          {
         
          digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,1);
        delay(50);
         digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,0);
      
          }    
     if(  i==6&& tilt>76)
          {
            i=1;
              digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,0);
          digitalWrite(16,1);
          delay(160);
          digitalWrite(16,0);
        
      
          }
///full dowwn
      if(H>=4&&i==10)
          {
        digitalWrite(33,1);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,0);
           delay(50);
          digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,0);
          }
         if(H<4&&i==10)
          {
         digitalWrite(16,1); 
             i=11;
         delay(50); 
         digitalWrite(16, 0);
         digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,0);
          }
         if(i==11&& tilt>=4)
          {
          digitalWrite(33,0);
         digitalWrite(25,0);
         digitalWrite(32,1);
         digitalWrite(17,0);
         delay(50);
           digitalWrite(33,0);
         digitalWrite(25,0);
         digitalWrite(32,0);
         digitalWrite(17,0);
          }
       if(i==11&& tilt<4)
          {
            i=1;
             i=1;
              digitalWrite(33,0);
         digitalWrite(25,0);
        digitalWrite(32,0);
        digitalWrite(17,0);
          digitalWrite(16,1);
          delay(160);
          digitalWrite(16,0);
          }






   if(digitalRead(4)==1)
      {
          digitalWrite(16,1); 
            EEPROM.write(1,1);
             delay(20);   
          EEPROM.commit();
           delay(20);   
         i=15;
         delay(150); 
        digitalWrite(16, 0);
   
        }
    
    if(digitalRead(5)==1)
       { 
          digitalWrite(16,1); 
         delay(150); 
         digitalWrite(16, 0);
        delay(150);
          digitalWrite(16,1); 
           EEPROM.write(1,2);
            delay(20);   
          EEPROM.commit();
           delay(20);   
          i=20;
          delay(100);   
         digitalWrite(16, 0);
         
       
       }
      
 if(digitalRead(18)==1)
      { 
        digitalWrite(16,1); 
         delay(150); 
         digitalWrite(16, 0);
        delay(150);
          digitalWrite(16,1); 
         delay(150); 
         digitalWrite(16, 0);
         delay(150);
           digitalWrite(16,1); 
           EEPROM.write(1,3);
            delay(50);   
          EEPROM.commit(); 
             delay(50);   
         i=25;;
          delay(50);   
         digitalWrite(16, 0);
        
        
      }

   if(digitalRead(19)==1&&EEPROM.read(1)==1)
         {    i=1;
             
               EEPROM.write(2,tilt);
                delay(20);   
               EEPROM.commit(); 
                delay(20);   
               EEPROM.write(3, H);
                delay(20);   
               EEPROM.commit(); 
                delay(20);   
               digitalWrite(16, 1);
               delay(150);
              digitalWrite(16, 0);
         }
        if(digitalRead(19)==1&&EEPROM.read(1)==2)
         {    i=1;
               EEPROM.write(4,tilt);
                delay(20);   
               EEPROM.commit(); 
                delay(20);   
               EEPROM.write(5,H);
                delay(20);   
               EEPROM.commit(); 
                delay(20);   
               digitalWrite(16, 1);
               delay(150);
                digitalWrite(16, 0);
                delay(150);
                digitalWrite(16, 1);
               delay(150);
                digitalWrite(16, 0);
                delay(150);
         }
         
        if(digitalRead(19)==1&&EEPROM.read(1)==3)
         {    i=1;
               EEPROM.write(6,tilt);
                delay(20);   
               EEPROM.commit(); 
                delay(20);   
               EEPROM.write(7, H);
                delay(20);   
               EEPROM.commit(); 
                delay(20);   
               digitalWrite(16, 1);
               delay(150);
                digitalWrite(16, 0);
                delay(150);
                digitalWrite(16, 1);
               delay(150);
                digitalWrite(16, 0);
                delay(150);
                digitalWrite(16, 1);
              delay(150);
                digitalWrite(16, 0);
                delay(150);
         }
//LOCAL1
   if(H==0||tilt>99)
   {
     digitalWrite(16, 1);
     delay(200);
     digitalWrite(16, 0);
   }
   if(EEPROM.read(3)>H&&i==15)
          {
            i=16;
          

          }

       if(EEPROM.read(3)<H&&i==15)
          {
            i=17;
          
          }
        if(EEPROM.read(3)==H&&i==15)
          {
            i=18;
          digitalWrite(16,1);
          delay(150);
          digitalWrite(16,0);
          
          }
     if (i==16)
     {
    if(EEPROM.read(3)<H)
       {
        i=18;
       }
      digitalWrite(33,0);
      digitalWrite(25,1);
       digitalWrite(32,0);
       digitalWrite(17,0);
       delay(50); 
   
     }
     if(i==17)
          {
    if(EEPROM.read(3)>H)
       {
        i=18;
       }
           digitalWrite(33,1);
         digitalWrite(25,0);
         digitalWrite(32,0);
         digitalWrite(17,0);
   
          delay(50);
    
       }       

//     if(EEPROM.read(3)==H&&i==15)
//          {
//            digitalWrite(33,0);
//         digitalWrite(25,0);
//         digitalWrite(32,0);
//         digitalWrite(17,0);
//          digitalWrite(16,1);
//          
//          i=16;
//          delay(50);
//          digitalWrite(16,0);
//          }
          //TIT
  if (i==18 && tilt<EEPROM.read(2))
  {
   
        i=41;
  
  }

    if (i==18 && tilt>EEPROM.read(2))
  {
   
        i=42;
  
  }

   if(tilt==EEPROM.read(2) &&i==18)
          {
            i=1;
          digitalWrite(16,1);
          delay(150);
          digitalWrite(16,0);
           digitalWrite(33,0);
        digitalWrite(25,0);
         digitalWrite(32,0);
         digitalWrite(17,0);
          
          }
          
 if( i==42)
          {

          if(tilt>EEPROM.read(2))
          {
            i=1;
          }
            digitalWrite(33,0);
        digitalWrite(25,0);
         digitalWrite(32,1);
         digitalWrite(17,0);
          delay(50);
   
         }
 if( i==41)
          {

          if(tilt<EEPROM.read(2))
          {
            i=1;
          }
             digitalWrite(33,0);
         digitalWrite(25,0);
         digitalWrite(32,0);
         digitalWrite(17,1);
          delay(50);
   
         }
//     
//    if(i==16&& tilt<EEPROM.read(2))
//          {
//             digitalWrite(33,0);
//         digitalWrite(25,0);
//         digitalWrite(32,0);
//         digitalWrite(17,1);
//          delay(50);
//   
//          }

              

          

   //mode 2 local

     if(EEPROM.read(5)>H&&i==20)
          {
         i=21;
          }

      if(EEPROM.read(5)<H&&i==20)
      { 
       i=22;
      }
///
    if(i==21)
    {  if(EEPROM.read(5)<H)
     {
      i=23;
     }
       digitalWrite(33,0);
         digitalWrite(25,1);
         digitalWrite(32,0);
         digitalWrite(17,0);
          delay(50);
     
    }
 if(i==22)
    {  if(EEPROM.read(5)>H)
     {
      i=23;
     }
       digitalWrite(33,1);
         digitalWrite(25,0);
         digitalWrite(32,0);
         digitalWrite(17,0);
          delay(50);
     
    }

      if(EEPROM.read(5)==H&&i==20)
          {
          digitalWrite(16,1);
           i=23;
          delay(150);
          digitalWrite(16,0);
          digitalWrite(33,0);
         digitalWrite(25,0);
         digitalWrite(32,0);
         digitalWrite(17,0);
         
          }   

 if(i==23&& tilt<EEPROM.read(4))
          {
         i=51;
   
          }

  if(i==23&& tilt>EEPROM.read(4))
          {
         i=52;
   
          }


    if(i==51)
    {
      if( tilt>EEPROM.read(4))
          {
          i=1;
          }

        digitalWrite(33,0);
         digitalWrite(25,0);
         digitalWrite(32,0);
         digitalWrite(17,1);  
          delay(50);
      
    }

     if(i==52)
    {
      if( tilt<EEPROM.read(4))
          {
          i=1;
          }

           digitalWrite(33,0);
         digitalWrite(25,0);
         digitalWrite(32,1);
         digitalWrite(17,0); 
          delay(50);
      
    }


        if(i==23 && tilt==EEPROM.read(4))
       {   
         digitalWrite(16,1);
          i=1;
          delay(150);
          digitalWrite(16,0);
           digitalWrite(33,0);
         digitalWrite(25,0);
         digitalWrite(32,0);
         digitalWrite(17,0);
         
       }
//       if( tilt<EEPROM.read(4)&&i==23)
//          {
//           digitalWrite(33,0);
//         digitalWrite(25,0);
//         digitalWrite(32,0);
//         digitalWrite(17,1);  
//          delay(50);
//   
//          }
//      if(i==21&& tilt>EEPROM.read(4))
//          {
//           digitalWrite(33,0);
//         digitalWrite(25,0);
//         digitalWrite(32,1);
//         digitalWrite(17,0);
//          delay(50);
//   
//          }

               
  
      
    
//    if(EEPROM.read(5)>H&&i==20)
//          {
//         digitalWrite(33,0);
//         digitalWrite(25,1);
//         digitalWrite(32,0);
//         digitalWrite(17,0);
//          delay(50);
//          }
//      if(EEPROM.read(5)<H&&i==20)
//          {
//         digitalWrite(33,1);
//         digitalWrite(25,0);
//         digitalWrite(32,0);
//         digitalWrite(17,0);
//          delay(50);
//          }       


    //local mode 3


 if(EEPROM.read(7)>H&&i==25)
          {
         i=26;
          }

 if(EEPROM.read(7)>H&&i==25)
          {
         i=27;
          }  

    if(i=26)
    {
      if(EEPROM.read(7)<H)
      {
        i=28;
      }
         digitalWrite(33,0);
         digitalWrite(25,1);
         digitalWrite(32,0);
         digitalWrite(17,0);
          delay(50);
    }

       if(i=27)
    {
      if(EEPROM.read(7)>H)
      {
        i=28;
      }
         digitalWrite(33,1);
         digitalWrite(25,0);
         digitalWrite(32,0);
         digitalWrite(17,0);
          delay(50);
    }
//       if(EEPROM.read(7)>H&&i==25)
//          {
//          digitalWrite(33,0);
//         digitalWrite(25,1);
//         digitalWrite(32,0);
//         digitalWrite(17,0);
//          delay(50);
    //      }
//       if(EEPROM.read(7)<H&&i==25)
//          {
//          digitalWrite(33,1);
//         digitalWrite(25,0);
//         digitalWrite(32,0);
//         digitalWrite(17,0);
//          delay(50);
//          }       

        if(EEPROM.read(7)==H&&i==25)
          {
          digitalWrite(33,0);
         digitalWrite(25,0);
         digitalWrite(32,0);
         digitalWrite(17,0);
         digitalWrite(16,1);
          i=28;
          delay(150);
          digitalWrite(16,0);
          }   
//
 if( tilt<EEPROM.read(6)&&i==28)
          {
       i=61;
   
          }

  if( tilt>EEPROM.read(6)&&i==28)
          {
       i=62;
   
          }         



      if(i==61)
      {
        if( tilt<EEPROM.read(6))
          {
          i=1;
          }
           digitalWrite(33,0);
         digitalWrite(25,0);
         digitalWrite(32,1);
         digitalWrite(17,0);
          delay(50);
   
      }

          if(i==62)
      {
        if( tilt>EEPROM.read(6))
          {
          i=1;
          }
           digitalWrite(33,0);
         digitalWrite(25,0);
         digitalWrite(32,0);
         digitalWrite(17,1);
          delay(50);
   
      }
//      if(i==26&& tilt>EEPROM.read(6))
//          {
//           digitalWrite(33,0);
//         digitalWrite(25,0);
//         digitalWrite(32,1);
//         digitalWrite(17,0);
//          delay(50);
//   
//          }

               
      if(i==28 && tilt==EEPROM.read(6))
       {
           digitalWrite(33,0);
         digitalWrite(25,0);
         digitalWrite(32,0);
         digitalWrite(17,0);
          digitalWrite(16,1);
          i=1;
          delay(150);
          digitalWrite(16,0);
       }
     
    }//code fulll mode
