


//buzzer = 4 // flasor = 5-6 // led+role = 7-8; //  servomotor = 9 //motor1 = 10; // motor2 = 11; // yon1 = 12; // yon2 = 13; // 

#include <Servo.h>

#include <DHT.h>
#include <SimpleDHT.h>

SimpleDHT11 dht11;

int GazEsik = 400;
int GazDegeri;

int secim;






Servo kamera;
int kameraAcisi=90;
String baslangicDurumu;

#define buzzerPin 4
#define trigger_pin  7
#define echo_pin  8
#define pinDHT11  2


void ileri()

{
                      digitalWrite (12, LOW);
                      digitalWrite (13, LOW);
                      digitalWrite (10, HIGH);
                      digitalWrite (11, HIGH);
  }

void geri()

{
                      digitalWrite (12, HIGH);
                      digitalWrite (13, HIGH);   
                      digitalWrite (10, HIGH);
                      digitalWrite (11, HIGH);
  }
void dur()

{
                      digitalWrite (12, HIGH);
                      digitalWrite (13, HIGH);
                      digitalWrite (10, LOW);
                      digitalWrite (11, LOW);
                      delay(150);
  
  }

void sag()
{
                      digitalWrite (12, LOW);
                      digitalWrite (13, HIGH);
                      digitalWrite (10, HIGH);
                      digitalWrite (11, HIGH);
  }
void engel()
{
        
        if(secim == 1){           //Sensörden okunan değer eşik değerinden büyükse çalışır.


        long sure;
            long mesafe;

            digitalWrite(trigger_pin, LOW);
            delay(10);
            digitalWrite(trigger_pin, HIGH);
            delay(10);
            digitalWrite(trigger_pin, LOW);
            sure = pulseIn(echo_pin, HIGH);
            mesafe = (sure / 29.1) / 2;
                if (mesafe < 15)
                    {
                      dur();
                      delay(150);
                    }
                                       
                            }
                            
        else if (secim == 2) {   


            long sure2;
            long mesafe2;

            digitalWrite(trigger_pin, LOW);
            delay(10);
            digitalWrite(trigger_pin, HIGH);
            delay(10);
            digitalWrite(trigger_pin, LOW);
            sure2 = pulseIn(echo_pin, HIGH);
            mesafe2 = (sure2 / 29.1) / 2;
                if (mesafe2 < 15)
                    {
                                      
                      sag();
                      delay(500);

                     
                    }
                  else if (mesafe2 > 15) {                         //Sensörden okunan değer eşik değerinin altındaysa çalışır.
                    
                      digitalWrite (12, LOW);
                      digitalWrite (13, LOW);
                      digitalWrite (10, HIGH);
                      digitalWrite (11, HIGH);
                      delay(150);
                    
                       }
                          }
                            }
  

  
void setup()
{
  
   
    pinMode(pinDHT11, OUTPUT);
    Serial.begin(9600);
    kamera.attach(9,0,180);
    kamera.write(90);
    pinMode(buzzerPin, OUTPUT);
    pinMode (echo_pin, INPUT);
    pinMode (trigger_pin, OUTPUT);


}
















void loop()
{

  GazDegeri = analogRead(A0);           //Sensörden analog değer okuyoruz.
      if(GazDegeri > GazEsik){           //Sensörden okunan değer eşik değerinden büyükse çalışır.
        Serial.print((int)GazDegeri);
    
        digitalWrite(buzzerPin, HIGH);
        delay(100);
        digitalWrite(buzzerPin, LOW);
        delay(100);
                            }
        else{                             //Sensörden okunan değer eşik değerinin altındaysa çalışır.
            digitalWrite(buzzerPin, LOW);
                            }
                              


engel();

  


  if (Serial.available() > 0) {
    int veriOku = Serial.read();


   

            



      


  switch(veriOku) {
   

  
    
    case 10:  // İleri
      ileri ();

    break;
    
    case 20: // Geri  
      digitalWrite (12, HIGH);
      digitalWrite (13, HIGH);   
      digitalWrite (10, HIGH);
      digitalWrite (11, HIGH);    
 

    break;
    
    case 30:  // Sola
      digitalWrite (12, HIGH);
      digitalWrite (13, LOW);
      digitalWrite (10, HIGH);
      digitalWrite (11, HIGH);

    break;
    
    case 40:  // Saga
      digitalWrite (12, LOW);
      digitalWrite (13, HIGH);
      digitalWrite (10, HIGH);
      digitalWrite (11, HIGH);


      

    break;

      
case 45:

secim = 1;

digitalWrite (12, LOW);
      digitalWrite (13, LOW);
      digitalWrite (10, HIGH);
      digitalWrite (11, HIGH);

      
break;

      case 49:  // kaç


      secim = 2;
      
                                 
                       
    
      break;


      case 50:

                      digitalWrite (12, HIGH);
                      digitalWrite (13, HIGH);
                      digitalWrite (10, LOW);
                      digitalWrite (11, LOW);
        break;
      
      case 51:

  byte temperature = 0;
    byte humidity = 0;
   
    if (dht11.read(pinDHT11, &temperature, &humidity, NULL))
    {
      return;
    }
    
    Serial.print((int)temperature);
    Serial.print("|");
    Serial.print((int)humidity);
    Serial.print("|");
    delay(2000);


    break;
    
    
    case 80:  // KameraSola
        kameraAcisi+=5;
      if (kameraAcisi>181) 
      {
        kameraAcisi=180;
      }
      if (kameraAcisi<=180) 
      {
        kamera.write(kameraAcisi);
      }
    break;
    
    case 85:  // KameraOrtada
      kamera.write(90);
      kameraAcisi=90;
    break;
    
    case 90:  // KameraSaga
        kameraAcisi-=5;
      if (kameraAcisi<10)
      {
        kameraAcisi=10;
      }
      if (kameraAcisi>=10) 
      {
        kamera.write(kameraAcisi);
      }
    break;  
              
    case 99:  // Baglantiyi KES
        for (int pinOffYap = 10; pinOffYap <= 13; pinOffYap++) {
        digitalWrite (pinOffYap, LOW);  } 
            for (int unoPinler1 = 2; unoPinler1 <= 6; unoPinler1++) {
            digitalWrite (unoPinler1, LOW);   }
           
        Serial.end();
        delay(1000);
        Serial.begin(9600);
        
    break;   

    default:  
        for (int pinOffYap = 10; pinOffYap <= 13; pinOffYap++) 
        {
          digitalWrite(pinOffYap, LOW);
        }  

        digitalWrite(buzzerPin, LOW);
       
      }


      
      
  }  


  
                       
     }
