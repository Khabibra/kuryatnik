#define fadePin 3 //пин управления MOSFET транзистором

int light;       //переменная для хранения состояния света (вкл/выкл)

#include <DS1302.h>

Time t;

int d; // Переменная в которую записываются текущий показатель часов

int t1=6; // Час включения света основной/ диммер R
int t2=14; // Час вылючения света


int t3=16; // Час включения света вентиляция R
int t4=20; // Час вылючения света

int t5=5; // Час включения света подсветка R4
int t6=22; // Час вылючения света

int R =5;
int R1 = 2;
//int R2 = 8;
//Подключение the DS1302
// DS1302:  CE pin  (RES)  -> Arduino Digital 2
   //       I/O pin (DAT)  -> Arduino Digital 3
     //     SCLK pin(CLK) -> Arduino Digital 4
DS1302 rtc(10, 11, 12);

void setup()
{  Serial.begin(9600);     
    pinMode(R,OUTPUT); 
       
    pinMode(R1, INPUT);     
  pinMode(fadePin, OUTPUT);// 3 пин на выход, для управления транзисотором  
  light = 0;     //устанаваливаем переменную для первого включения света
 
 
   // The following lines can be commented out to use the values already stored in the DS1302(Строки ниже нужно раскоментировать если вы устанавливаете дату и время в модуль после установки нужно опять закоментировать)
  // Set the clock to run-mode, and disable the write protection
// rtc.halt(false);
 //rtc.writeProtect(false);
//rtc.setDOW(FRIDAY);        // Set Day-of-Week to FRIDAY
 // rtc.setTime(22, 22, 0);     // Set the time to 12:00:00 (24hr format)
// rtc.setDate( 25, 10, 2018);   // Set the date to August 6th, 2010
}
  
void loop()
{
                               t = rtc.getTime();

                                  // Send Day-of-Week(Передать день недели)
                               Serial.print(rtc.getDOWStr());
                               Serial.print(" ");
  
                                  // Передать дату
                               Serial.print(rtc.getDateStr());
                               Serial.print(" -- ");
                                   d=t.hour,OCT;
                                 // m=t.min,OCT;

                                  // Передать время
                                Serial.println(rtc.getTimeStr());

                                
  
  
     if (d >= t1 && d < t2) {
   digitalWrite(R,LOW);   // реле включено
   Serial.println(" VKL_OSV ");
                        }
                        else
                            {             
                            digitalWrite(R, HIGH);  // реле выключено 
                            Serial.println(" VIKL_OSV "); 
                            }
                            
  if (d >= t3 && d < t4) {
   digitalWrite(R,LOW);   // реле включено
   Serial.println(" VKL_OSV1 ");
                        }
                        else
                            {             
                            digitalWrite(R, HIGH);  // реле выключено 
                            Serial.println(" VIKL_OSV1 "); 
                            }
                          
     if(d >=t5 && d<t6)
                       {                                                                
                           
                            digitalWrite(R1, HIGH);   // реле включено
                            Serial.println("VKL_DIOD");
    if(digitalRead(R1) == HIGH )  //если сигнал с датчика высокого уровня(т.е. есть движение)
                    
                       {
     if(light == 0)   //и если свет не был включен
                       {
     for(int i=0; i<=255; i++)  //то плавно включаем свет
                       {
                            analogWrite(fadePin, i); 
                            delay(3000);   //каждые 10мс увелияение на 1
                       } 
                           light = 1; //и передаем значение переменной, что свет включен
                       }
                       } 
    else  //иначе
                       {    
    if(light == 1) //если свет включен
                       {
    for(int i=255; i>=0; i--)//плавно гасим его
                       {
                             analogWrite(fadePin, i);
                                 delay(3000);
                       } 
                             light = 0; //и передаем значение переменной, что свет выключен
                       }
                       }
                       }     
                     
                        delay(10000);                     
    
                       }
        
   
                                                     
 
                         
                                             
     
      
      
              
   
                          
