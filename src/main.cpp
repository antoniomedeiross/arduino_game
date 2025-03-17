#include <Arduino.h>

// C++ code
#define LED_VERDE 2
#define LED_VERMELHO 3
#define LED_AZUL 4
#define LED_AMARELO 5
#define TAMANHO_SEQUENCIA 4

#define BOTAO_VERDE 10
#define BOTAO_VERMELHO 11
#define BOTAO_AZUL 12
#define BOTAO_AMARELO 13

#define INDEFINIDO -1

#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500

enum Estados {
  PRONTO_PROX_RODADA,
  USUARIO_RESPONDENDO,
  JOGO_FINALIZADO_SUCESSO,
  JOGO_FINALIZADO_FALHA
};


void iniciaPortas();
int piscaLed(int);
int checaRespostaPlayer();
void iniciaJogo();
int sorteiaCor();
int estadoAtual();
void acendeLedsRodada();
void preparaNovaRodada();
void processaResposta();
void jogoFinalizadoSucesso();
void jogoFinalizadoFalha();
void piscaSequencia1();
void piscaSequencia2();

int sequenciaLuzes[TAMANHO_SEQUENCIA];
int rodada = 0;
int respostaUser = 0;

void setup() {
  Serial.begin(9600);
  iniciaPortas();
  iniciaJogo();

}

void iniciaJogo() {
  int jogo = analogRead(A0); 
  randomSeed(jogo);
  
  for(int i=0; i<TAMANHO_SEQUENCIA; i++){
    sequenciaLuzes[i] = sorteiaCor();  
  }
}

int sorteiaCor() {
  return random(LED_VERDE, LED_AMARELO+1); // 2-5
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
  switch(estadoAtual()){
    case PRONTO_PROX_RODADA:
      Serial.println("Pronto prox rodada");
      preparaNovaRodada();
      break;
     case USUARIO_RESPONDENDO:
      Serial.println("User respondendo");
      processaResposta();
      break;
    case JOGO_FINALIZADO_SUCESSO:
      jogoFinalizadoSucesso();
      Serial.println("Finalizado com sucesso");
      break;
    case JOGO_FINALIZADO_FALHA:
      jogoFinalizadoFalha();
      Serial.println("Finalizado com falha");
      break;
    default: 
      break;
  }
  delay(MEIO_SEGUNDO);
  // int resposta = checaRespostaPlayer();
}

void jogoFinalizadoSucesso() {
  piscaSequencia1();
  iniciaJogo();
}

void jogoFinalizadoFalha() {
  piscaSequencia2();
  iniciaJogo();
}

void processaResposta() {
  int resposta = checaRespostaPlayer();

  if(resposta == INDEFINIDO) {
    return;
  }

  if(resposta == sequenciaLuzes[respostaUser]){
    Serial.println("Acertou");
    respostaUser ++;

  } else {
    rodada = TAMANHO_SEQUENCIA+2;
    Serial.println("Errou");
  }
}

void preparaNovaRodada() {
  rodada++;
  respostaUser = 0;
  if(rodada<=TAMANHO_SEQUENCIA) {
    acendeLedsRodada();
  }
}

int estadoAtual() {
  if(rodada <= TAMANHO_SEQUENCIA) {
    if(respostaUser < rodada) {
      return USUARIO_RESPONDENDO;
    }
    return PRONTO_PROX_RODADA;
  } else if(rodada == TAMANHO_SEQUENCIA+1) {
    return JOGO_FINALIZADO_SUCESSO;
  } else {
    return JOGO_FINALIZADO_FALHA;
  }
}

void acendeLedsRodada() {
  for(int i=0; i<rodada; i++){
    piscaLed(sequenciaLuzes[i]);
  }
  delay(250);
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