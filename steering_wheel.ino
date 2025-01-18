/*
12 botões frontais
04 botões traseiros (2 Paddles + 2 botões)
1 embreagem (potenciometro)
5 encoders (10 funções)
--------------------
Matriz de botões
14 botões - C15 - C0

---------------------
3/4 - 1 - encoder
2/5 - 2 - encoder 
0/6 - 3 - encoder 
1/8 - 4 - encoder
7/A0 - 5 - encoder 
----------------------
10 - signal - Buttons
16 - S0
15 - S1
14 - S2
9 - S3
-----------------------
A1 - VRx (Analog)
A2 - VRy (Analog)
A0 - Potenciometer (clutch)
*/

#include <Joystick.h>

// Comando analogico
#define joyX A1
#define joyY A2
// Potenciometro (Clutch)
#define joyRZ A0

// Estrutura para armazenar os dados de cada encoder
struct Encoder {
  int clkPin;                // Pino do sinal CLK
  int dtPin;                 // Pino do sinal DT
  volatile int position;     // Posição atual do encoder
  volatile bool directionCW; // Sentido de rotação
  volatile bool flag;        // Indica se houve mudança
};

// Configuração dos encoders (ajustado para pinos de interrupção do Leonardo) preferencialmente utilizar esses pinos 0,1,2,3,7
#define NUM_ENCODERS 5 // Número de encoders
#define DEBOUNCE_DELAY 15 // Tempo mínimo entre leituras em milissegundos
Encoder encoders[NUM_ENCODERS] = {
  {3, 4, 0, false, false},  // Encoder 1 (CLK no pino 3, DT no pino 4) - OK
  {2, 5, 0, false, false},  // Encoder 2 (CLK no pino 2, DT no pino 5) - OK
  {0, 6, 0, false, false},  // Encoder 3 (CLK no pino 0, DT no pino 6) - OK
  {1, 8, 0, false, false},  // Encoder 4 (CLK no pino 1, DT no pino 8) - OK
  {7, A3, 0, false, false}   // Encoder 5 (CLK no pino 7, DT no pino 9) - OK
};

// Botões do multiplexador
#define SIG 10
#define S0 16
#define S1 15
#define S2 14
#define S3 9
#define NUM_BUTTONS 16

// Inicialização
int xAxis_ = 0;
int yAxis_ = 0;
int rzAxis_ = 0;



// Create Joystick
Joystick_ Joystick(0x04,JOYSTICK_TYPE_JOYSTICK,
  26, 0,                                          // Numero de botões, Hat Switch 
  true, true, false,                              // X,Y and Z Eixos 
  false,false,                                    // Rudder, throttle  
  true, false, false                              // Accelerator, Brake and steering
);

// Funções de interrupção específicas para cada encoder
void handleEncoder0() { handleEncoder(0); }
void handleEncoder1() { handleEncoder(1); }
void handleEncoder2() { handleEncoder(2); }
void handleEncoder3() { handleEncoder(3); }
void handleEncoder4() { handleEncoder(4); }

//Set Auto Send State
//Envia os dados do joystick antes de serem solicitados
const bool initAutoSendState = true;

void setup() {


  // Inicialização
  Serial.begin(9600);
  Joystick.begin(); 

  //Comando analogico
  Joystick.setXAxisRange(1023, 0);
  Joystick.setYAxisRange(1023, 0);

  // Multiplexador
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);
  pinMode(SIG,INPUT_PULLUP);

   // Encoders Rotativos
  for (int i = 0; i < NUM_ENCODERS; i++) {
    pinMode(encoders[i].clkPin, INPUT_PULLUP);
    pinMode(encoders[i].dtPin, INPUT_PULLUP);

    // Configura interrupções nos pinos CLK
    attachInterrupt(digitalPinToInterrupt(encoders[i].clkPin), 
                    i == 0 ? handleEncoder0
                    : i == 1 ? handleEncoder1
                    : i == 2 ? handleEncoder2
                    : i == 3 ? handleEncoder3
                    : handleEncoder4,
                    CHANGE);
  }
}

void loop() {

  // Encoders rotativos
  for (int i = 0; i < NUM_ENCODERS; i++) {
    if (encoders[i].flag) {
      encoders[i].flag = false;

      // Atualiza os botões de acordo com a direção
      if (encoders[i].directionCW) {
        Joystick.setButton(i * 2, true);     // Botão CW ligado
        Joystick.setButton(i * 2 + 1, false); // Botão CCW desligado
        Serial.print("(CW) Botão: ");
        Serial.println(i * 2);
      } else {
        Joystick.setButton(i * 2, false);    // Botão CW desligado
        Joystick.setButton(i * 2 + 1, true); // Botão CCW ligado
        Serial.print("(CCW) Botão: ");
        Serial.println(i * 2 + 1);
      }

      // Libera os botões após um curto intervalo
      delay(50); // Atraso para evitar falsos acionamentos
      Joystick.setButton(i * 2, false);
      Joystick.setButton(i * 2 + 1, false);
    }
  }
  

  
  // Comando analogico Axis X e Y
  xAxis_ = analogRead(joyX);
  yAxis_ = analogRead(joyY);

  Joystick.setXAxis(xAxis_);
  //Debug
  //Serial.println(xAxis_);
  

  Joystick.setYAxis(yAxis_);
  //Debug
  //Serial.println(yAxis_);
  
  // Potentiometer 10k 
  rzAxis_ = analogRead(joyRZ);
  Joystick.setRzAxis(rzAxis_);
  //Debug
  //Serial.println(rzAxis_);

  // Loop de todos os botões do multiplexador
  for (int button = 0; button < NUM_BUTTONS; button++) {
    // Seleciona o canal no multiplexador
    selectMuxChannel(button);
    // Lê o estado do botão
    int buttonState = digitalRead(SIG);
    // O multiplexador retorna LOW quando o botão está pressionado
    bool pressed = (buttonState == LOW);
    // Atualiza o estado do botão no joystick
    Joystick.setButton(button+10, pressed);
    //Debug
    //Serial.print("Botão: ");
    //Serial.println(button+10);
    delay(10);
  }

}

// Leitura da matriz do multiplexador
void selectMuxChannel(int channel) {
  digitalWrite(S0, channel & 0x01); // LSB
  digitalWrite(S1, channel & 0x02);
  digitalWrite(S2, channel & 0x04);
  digitalWrite(S3, channel & 0x08); // MSB
}

void handleEncoder(int encoderIndex) {
  static bool lastCLK[NUM_ENCODERS] = {LOW, LOW, LOW, LOW, LOW}; // Estado anterior do CLK
  static unsigned long lastDebounceTime[NUM_ENCODERS] = {0, 0, 0, 0, 0}; // Último tempo de leitura válida

  bool currentCLK = digitalRead(encoders[encoderIndex].clkPin);
  unsigned long currentTime = millis();

  // Verifica se o tempo mínimo entre leituras foi respeitado
  if ((currentTime - lastDebounceTime[encoderIndex]) > DEBOUNCE_DELAY) {
    if (currentCLK != lastCLK[encoderIndex] && currentCLK == HIGH) { // Detecta borda de subida
      bool currentDT = digitalRead(encoders[encoderIndex].dtPin);

      if (currentDT != currentCLK) {
        // Sentido horário
        encoders[encoderIndex].position++;
        encoders[encoderIndex].directionCW = true;
      } else if (currentDT == currentCLK) {
        // Sentido anti-horário
        encoders[encoderIndex].position--;
        encoders[encoderIndex].directionCW = false;
      }

      encoders[encoderIndex].flag = true; // Marca que houve mudança
      lastDebounceTime[encoderIndex] = currentTime; // Atualiza o tempo da última leitura válida
    }
  }

  lastCLK[encoderIndex] = currentCLK; // Atualiza o estado anterior do CLK
}
