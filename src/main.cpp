#include <Arduino.h>

// C++ code
#define LED_VERDE 2
#define LED_VERMELHO 3
#define LED_AZUL 4
#define LED_AMARELO 5

#define BOTAO_VERDE 10
#define BOTAO_VERMELHO 11
#define BOTAO_AZUL 12
#define BOTAO_AMARELO 13

#define INDEFINIDO -1

#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500


void iniciaPortas();
int piscaLed(int);
int checaRespostaPlayer();

int sequenciaLuzes[] = {LED_VERMELHO, LED_AMARELO, LED_VERDE, LED_AZUL};


void setup() {
  iniciaPortas();

}

void iniciaPortas(){

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  
  pinMode(BOTAO_VERDE, INPUT_PULLUP);
  pinMode(BOTAO_VERMELHO, INPUT_PULLUP);
  pinMode(BOTAO_AZUL, INPUT_PULLUP);
  pinMode(BOTAO_AMARELO, INPUT_PULLUP);

}

void loop() {
  int resposta = checaRespostaPlayer();

}

int checaRespostaPlayer(){
  if(digitalRead(BOTAO_VERDE) == LOW){
  	return piscaLed(LED_VERDE);
  }
  if(digitalRead(BOTAO_VERMELHO) == LOW){
  	return piscaLed(LED_VERMELHO);
  }
  if(digitalRead(BOTAO_AZUL) == LOW){
  	return piscaLed(LED_AZUL);
  }
  if(digitalRead(BOTAO_AMARELO) == LOW){
  	return piscaLed(LED_AMARELO);
  }
  
  return INDEFINIDO;
}
     

void piscaSequencia1(){
  piscaLed(LED_VERDE);
  piscaLed(LED_VERMELHO);
  piscaLed(LED_AZUL);
  piscaLed(LED_AMARELO);
}

void piscaSequencia2(){
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_VERMELHO, HIGH);
  digitalWrite(LED_AZUL, HIGH);
  digitalWrite(LED_AMARELO, HIGH);
  delay(UM_SEGUNDO);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_AMARELO, LOW);
  delay(MEIO_SEGUNDO);
}

int piscaLed(int portaLed){
  digitalWrite(portaLed, HIGH);
  delay(UM_SEGUNDO);
  digitalWrite(portaLed, LOW);
  delay(MEIO_SEGUNDO);
  return portaLed;
}