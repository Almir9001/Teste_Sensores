/*
teste e monitoramento da tensão de entrada
teste de corrente no motor
teste de tensão no motor
*/


void sinaliza();
void testa_corrente();

int buzzer=13;
int corrente=0;
int pino_tensao=12;

void setup() 
{
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(pino_tensao, INPUT_PULLUP);
} // fim setup

void loop() 
{
    while(corrente < 50)
     {
      corrente = analogRead(A0);
      Serial.println(corrente);
      delay(300);
     }

     testa_corrente(); 

} // loop final


 
//************************************************************************

 void sinaliza()
 {
  for(int i=0; i<= 5; i++)
   {
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
   }
 }

//*************************************************************************  
 void testa_corrente()
  { 
    
    corrente = analogRead(A0);
    
    if(corrente >= 500)
     {
      delay(3000);
      int corrente = analogRead(A0);
      if(corrente >= 500)
        {
          while(1)
          {
           sinaliza();
           delay(2000);
          }
        }
      }
      delay(3000);
 }  
 
//************************************************************************ 
 
 
