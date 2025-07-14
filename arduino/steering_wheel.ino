/*
12 botões frontais
04 botões traseiros (2 Paddles + 2 botões)
1 embreagem (potenciometro)
5 encoders (10 funções) -
--------------------
Matriz de botões
14 botões - C15 - C0

---------------------
3/4           - 1 - encoder  PCINT2
2/5           - 2 - encoder  PCINT2
0/6           - 3 - encoder  PCINT2
1/7           - 4 - encoder  PCINT2
A3(21)/A0(18) - 5 - encoder  PCINT1
----------------------
10 - signal - Buttons
16 - S0
15 - S1
14 - S2
09 - S3
-----------------------
A1 - VRx (Analog)
A2 - VRy (Analog)
A8(8) - Potenciometer (clutch)

Grupo de interrupções por porta
# PCINT0 - D8, D9, D10, D11, D12, D13,
# PCINT1 - A0, A1, A2, A3, A4, A5
# PCINT2 - D0, D1, D2, D3, D4, D5, D6, D7

*/


#include <Joystick.h>
#include <Arduino.h>
#include <BasicEncoder.h>
#include <TimerOne.h>

// Comando analogico
#define joyX A1
#define joyY A2
const int deadzone = 30;  // Zona morta para evitar tremores
// Potenciometro (Clutch)
#define joyRZ A3

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


// Encoders
BasicEncoder encoder1(3, 4);  // Direito           // 1
BasicEncoder encoder2(7, 18); // Esquerdo          // 2
BasicEncoder encoder3(0, 1);  // Superior Direito  // 5
BasicEncoder encoder4(2, 5);  // Inferior Esquerdo // 4
BasicEncoder encoder5(8, 6);  // Inferior Direito  // 3

void timer_service() {
  encoder1.service();
  encoder2.service();
  encoder3.service();
  encoder4.service();
  encoder5.service();
}

// Instancia do Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  25, 1,                                            // Numero de botões, Hat Switch 
  false, false, false,                              // X,Y and Z Eixos 
  false, false, true,                              // Rx, Ry, Rz
  false, false,                                     // Rudder, throttle  
  false, false, false                                // Accelerator, Brake and steering
);

void setup() {
  //Serial.begin(115200);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timer_service);
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
}

void loop() {

  int encoder_change1 = encoder1.get_change();
  int encoder_change2 = encoder2.get_change();
  int encoder_change3 = encoder3.get_change();
  int encoder_change4 = encoder4.get_change();
  int encoder_change5 = encoder5.get_change();
  if (encoder_change1) {
    if (encoder_change1 == -1) {
      //Serial.println("Atrás 1");
      Joystick.setButton(0, true);
      delay(50);
      Joystick.setButton(0, false);
    }
    else {
      //Serial.println("Frente 1");
      Joystick.setButton(1, true); 
      delay(50);
      Joystick.setButton(1, false); 
    }
}
  if (encoder_change2) {
    if (encoder_change2 == -1) {
      //Serial.println("Atrás 2");
      Joystick.setButton(2, true);
      delay(50);
      Joystick.setButton(2, false);
    }
    else {
      //Serial.println("Frente 2");
      Joystick.setButton(3, true); 
      delay(50);
      Joystick.setButton(3, false);
    }    
  }
  if (encoder_change3) {
    if (encoder_change3 == -1) {
      //Serial.println("Atrás 3");
      Joystick.setButton(4, true);
      delay(50);
      Joystick.setButton(4, false);
    }
    else {
      //Serial.println("Frente 3");
      Joystick.setButton(5, true); 
      delay(50);
      Joystick.setButton(5, false);
    }    
  }
  if (encoder_change4) {
    if (encoder_change4 == -1) {
      //Serial.println("Atrás 4");
      Joystick.setButton(6, true);
      delay(50);
      Joystick.setButton(6, false);
    }
    else {
      //Serial.println("Frente 4");
      Joystick.setButton(7, true); 
      delay(50);
      Joystick.setButton(7, false); 
    }    
  }
  if (encoder_change5) {
    if (encoder_change5 == -1) {
      //Serial.println("Atrás 5");
      Joystick.setButton(8, true);
      delay(50);
      Joystick.setButton(8, false);       
    }
    else {
      //Serial.println("Frente 5");
      Joystick.setButton(9, true); 
      delay(50);
      Joystick.setButton(9, false); 
    }    
  }

  // Comando analogico Axis X e Y
  xAxis_ = analogRead(joyX) - 512;
  yAxis_ = analogRead(joyY) - 512;
  int hatState = -1;


  //Debug Analogico
  
  //Eixo X
  //Joystick.setXAxis(xAxis_);
  //Debug
  Serial.print("X: ");
  Serial.println(xAxis_);
  //Eixo Y
  //Joystick.setYAxis(yAxis_);
  //Debug
  Serial.print("y: ");
  Serial.println(yAxis_);

  // Analogico
  if (yAxis_ > deadzone) hatState = 180;   // Cima
  else if (yAxis_ < -deadzone) hatState = 0; // Baixo
  else if (xAxis_ > deadzone) hatState = 90;  // Direita
  else if (xAxis_ < -deadzone) hatState = 270; // Esquerda
  Joystick.setHatSwitch(0, hatState); // Envia o valor do Hat Switch

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
    Joystick.setButton(button+9, pressed);
    //Debug
    //Serial.print("Botão: ");
    //Serial.println(button+10);
  }
}

void selectMuxChannel(int channel) {
  digitalWrite(S0, channel & 0x01); // LSB
  digitalWrite(S1, channel & 0x02);
  digitalWrite(S2, channel & 0x04);
  digitalWrite(S3, channel & 0x08); // MSB
}
