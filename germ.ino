// test.ino
#include "DHT.h"
#include "LiquidCrystal.h"
//#include "Time.h"
 
// Define o sensor DHT22 no pino A5
#define DHT_PIN A0
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);

//Define os pinos que serão ligados ao LCD
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//UNO LCD
//LiquidCrystal lcd(6, 7, 2, 3, 4, 5);
//UNO relay pins
//int Relay[] = { 8, 9, 10, 11 };

// PRO MINI LCD
LiquidCrystal lcd(6, 7, 2, 3, 4, 5);
// PRO MINI relay pins
int Relay[] = { 10, 11, 12, 13 };

// Define a temperatura e umidade desejadas
#define TEMP_MIN 22.5
#define TEMP_MED 23.0
#define TEMP_MAX 23.5
#define HUMI 90.0

int HumOut = 9;

//Array simbolo grau
/*byte grau[8] =
{	B00001100,
	B00010010,
	B00010010,
	B00001100,
	B00000000,
	B00000000,
	B00000000,
	B00000000,};
*/

void setup() {
	Serial.begin(9600);
	Serial.println("DHTxx test!");

	dht.begin();
	lcd.begin(16,2);
	lcd.clear();
	//lcd.createChar(0, grau);

	pinMode(HumOut, OUTPUT);

	pinMode(Relay[0], OUTPUT);
	pinMode(Relay[1], OUTPUT);
	pinMode(Relay[2], OUTPUT);
	pinMode(Relay[3], OUTPUT);
	digitalWrite(Relay[0], LOW);
	digitalWrite(Relay[1], LOW);
	digitalWrite(Relay[2], LOW);
	digitalWrite(Relay[3], LOW);
}

void loop()
{
	delay(2000); // Sensor delay
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	//h = 80;

	if (isnan(h) || isnan(t))
	{
	Serial.println("Failed to read from DHT sensor!");
	return;
	}

	// Temperature
	lcd.setCursor(0,0);
	lcd.print("Temp : ");
	lcd.print(" ");
	lcd.setCursor(7,0);
	lcd.print(t,1);
	lcd.setCursor(12,0);
	lcd.write((byte)0);

	// Humidity
	lcd.setCursor(0,1);
	lcd.print("Umid : ");
	lcd.print(" ");
	lcd.setCursor(7,1);
	lcd.print(h,1);
	lcd.setCursor(12,1);
	lcd.print("%");

	// Decisions
	
	if (t <= TEMP_MED){
		digitalWrite(Relay[0], HIGH); // Turn refrigerator off
		if (t < TEMP_MIN){
			digitalWrite(Relay[2], LOW); // Turn heater on
		}
	}
	else{
		digitalWrite(Relay[2], HIGH); // Turn heater off
		if (t > TEMP_MAX){
			digitalWrite(Relay[0], LOW); // Turn refrigerator on
		}
	}

	if(h < HUMI){
	    digitalWrite(Relay[1], LOW);
	}
	
	if(h > HUMI){
	    digitalWrite(Relay[1], HIGH);
	}

	analogWrite(HumOut, (byte)(((float)h / 100.0)*255.0));


	//DEBUG
	//Serial.print("\nhum: ");
	Serial.print("\n");
	Serial.print(h);
	//Serial.print("\ttemp: ");
	Serial.print("\n");
	Serial.print(t);

}

/*
//Programa : Teste Módulo Rele Arduino - Botoes
//Autor : FILIPEFLOP
 
//Porta ligada ao pino IN1 do modulo
int porta_rele1 = 7;
//Porta ligada ao pino IN2 do modulo
int porta_rele2 = 8;
//Porta ligada ao botao 1
int porta_botao1 = 2;
//Porta ligada ao botao 2
int porta_botao2 = 3;
 
//Armazena o estado do rele - 0 (LOW) ou 1 (HIGH)
int estadorele1 = 1;
int estadorele2 = 1;
//Armazena o valor lido dos botoes
int leitura1 = 0;
int leitura2 = 0;
  
void setup()
{
  //Define pinos para o rele como saida
  pinMode(porta_rele1, OUTPUT); 
  pinMode(porta_rele2, OUTPUT);
  //Define pinos dos botoes como entrada
  pinMode(porta_botao1, INPUT); 
  pinMode(porta_botao2, INPUT);
  //Estado inicial dos reles - desligados
  digitalWrite(porta_rele1, HIGH);
  digitalWrite(porta_rele2, HIGH);
}
 
void loop()
{
  //Verifica o acionamento do botao 1
  leitura1 = digitalRead(porta_botao1);
  if (leitura1 != 0)
  {
    while(digitalRead(porta_botao1) != 0)
    {
      delay(100);
    }
    //Inverte o estado da porta
    estadorele1 = !estadorele1;
    //Comandos para o rele 1
    digitalWrite(porta_rele1, estadorele1);  
  }   
   
  //Verifica o acionamento do botao 2
  leitura2 = digitalRead(porta_botao2);
  if (leitura2 != 0)
  {
    while(digitalRead(porta_botao2) != 0)
    {
      delay(100);
    }
    //Inverte o estado da porta
    estadorele2 = !estadorele2;
    //Comandos para o rele 2
    digitalWrite(porta_rele2, estadorele2);  
  } 
}*/
