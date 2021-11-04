
///////////////////////////////
//con servo.h
#include <Servo.h>
Servo myservo;
///////////////////////////////


///////////////////////////////
//con maestro.h
#include <PololuMaestro.h>

#ifdef SERIAL_PORT_HARDWARE_OPEN
#define maestroSerial SERIAL_PORT_HARDWARE_OPEN
#else
#include <SoftwareSerial.h>
SoftwareSerial maestroSerial(10, 11);
#endif
MicroMaestro maestro(maestroSerial);
///////////////////////////////

#include "Pata.h"

//orden patas: empieza delantera derecha y aumenta en sentido agujas reloj
Pata pata1(0, 1);
Pata pata2(3, 4);
Pata pata3(6, 7);
Pata pata4(9, 10);


///////////////////////////////

//posicion servo
const int MIN = 4000;
const int MIN_CENTRO = 5000;
const int CENTRO = 6000;
const int MAX_CENTRO = 7000;
const int MAX = 8000;

const int levanarMIN = 2000;
const int levantarMAX = 10000;

const byte posicion1 = 0;
const byte posicion2 = 1;
const byte posicion3 = 2;

const int speed = 100;
const int acceleration = 127;
///////////////////////////////

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  //setupServo();

  maestroSerial.begin(9600);

  setupPatas();

  delay(1000);

  //paso1();

}

void loop() {

  while (Serial.available()) {
    String data = Serial.readString();
    data.trim();
    Serial.println(data);
    Serial.println(data.length());
    if ((data.equals("f")) || (data.equals("F"))) {
    avanzar();
    }
    if ((data.equals("r")) || (data.equals("R"))) {
    girarDerecha();
    }
    if ((data.equals("l")) || (data.equals("L"))) {
    girarIzquierda();
    }
    delay(500);
   // paso1();
  }
  // delay(500);
  //test();
  //levantarPDD();

  //avanzar();

  //girarDerecha();

  //girarIzquierda();
  //delay(1000);

}

/**
   Movimientos para avanzar
*/
void avanzar() {
  int del = 400;
  paso2();
  delay(del);
  paso3();
  delay(del);
  paso4();
  delay(del);
  paso5();
  delay(del);
  paso6();
  delay(del);
  paso7();
  delay(del);
}


void girarDerecha() {
  int del1 = 1000;
  int del2 = 10;

  pata2.levantarPata();
  pata4.levantarPata();
  delay(del2);
  pata1.empujarPata(posicion1);
  pata3.empujarPata(posicion1);

  pata2.moverPata(posicion1);
  pata4.moverPata(posicion1);

  delay(del1);

  pata1.levantarPata();
  pata3.levantarPata();
  delay(del2);
  pata2.empujarPata(posicion3);
  pata4.empujarPata(posicion3);
  pata1.moverPata(posicion3);
  pata3.moverPata(posicion3);

  delay(del1);


}

void girarIzquierda() {
  int del1 = 1000;
  int del2 = 10;

  pata1.levantarPata();
  pata3.levantarPata();
  delay(del2);
  pata2.empujarPata(posicion1);
  pata4.empujarPata(posicion1);
  pata1.moverPata(posicion1);
  pata3.moverPata(posicion1);

  delay(del1);

  pata2.levantarPata();
  pata4.levantarPata();
  delay(del2);
  pata1.empujarPata(posicion3);
  pata3.empujarPata(posicion3);

  pata2.moverPata(posicion3);
  pata4.moverPata(posicion3);

  delay(del1);
}

void test() {

  int del = 1000;
  pata1.moverPata(posicion1);
  delay(del);
  pata1.moverPata(posicion2);
  delay(del);
  pata1.moverPata(posicion3);
  delay(del);

  pata2.moverPata(posicion1);
  delay(del);
  pata2.moverPata(posicion2);
  delay(del);
  pata2.moverPata(posicion3);
  delay(del);

  pata3.moverPata(posicion1);
  delay(del);
  pata3.moverPata(posicion2);
  delay(del);
  pata3.moverPata(posicion3);
  delay(del);

  pata4.moverPata(posicion1);
  delay(del);
  pata4.moverPata(posicion2);
  delay(del);
  pata4.moverPata(posicion3);
  delay(del);
}


/**
   Inicializa los servos a su posicion centrada usando la biblioteca Servo.h
*/
void setupServo() {

  //attach pin salida
  myservo.attach(3);
  //mueve el serfvo al angulo en grados
  myservo.write(90);

}


/**
   Inicializa los valores de las clases pata
*/

void setupPatas() {

  pata1.setOffset(-250, 0);
  pata2.setOffset(0, 0);
  pata3.setOffset(-150, 0);
  pata4.setOffset(-200, 0);

  pata1.setPosiciones(MIN, MIN_CENTRO, CENTRO, levanarMIN);
  pata2.setPosiciones(MAX, MAX_CENTRO, CENTRO, levantarMAX);
  pata3.setPosiciones(MIN, MIN_CENTRO, CENTRO, levanarMIN);
  pata4.setPosiciones(MAX, MAX_CENTRO, CENTRO, levantarMAX);

  // setTarget takes the channel number you want to control, and the target position in units of 1/4 microseconds.
  //   A typical RC hobby servo responds to pulses between 1 ms (4000) and 2 ms (8000).

  // setSpeed takes channel number you want to limit and the speed limit in units of (1/4 microseconds)/(10 milliseconds).
  // A speed of 0 makes the speed unlimited, so that setting the target will immediately affect the position. Note that the
  //actual speed at which your servo moves is also limited by the design of the servo itself, the supply voltage, and mechanical loads.

  //  setAcceleration takes channel number you want to limit and the acceleration limit value from 0 to 255 in units of (1/4 microseconds)/(10 milliseconds) / (80 milliseconds).
  //  A value of 0 corresponds to no acceleration limit. An acceleration limit causes the speed of a servo to slowly ramp up until it reaches the maximum speed,
  //  then to ramp down again as the position approaches the target, resulting in relatively smooth motion from one point to another.
  pata1.setupPata(speed, acceleration);
  pata2.setupPata(speed, acceleration);
  pata3.setupPata(speed, acceleration);
  pata4.setupPata(speed, acceleration);
}


/**
   Lado derecho centrado lado izquierdo abierto
*/
void paso1() {
  int del = 50;
  pata1.moverPata(posicion3);
  delay(del);
  pata2.moverPata(posicion3);
  delay(del);
  pata3.moverPata(posicion2);
  delay(del);
  pata4.moverPata(posicion2);
  Serial.println("paso 1");

}

/**
   mover para derecha delantera
*/
void paso2() {
  pata1.moverPata(posicion1);
  Serial.println("paso 2");
}

/**
   Empujar todas patas
*/
void paso3() {
  int del = 5;
  pata1.empujarPata(posicion2);
  delay(del);
  pata2.empujarPata(posicion2);
  delay(del);
  pata3.empujarPata(posicion1);
  delay(del);
  pata4.empujarPata(posicion3);
  Serial.println("paso 3");
}

/**
   mover pata trasera izquierda para centrar lado izquierdo, lado derecho abierto
*/
void paso4() {
  pata3.moverPata(posicion3);
  Serial.println("paso 4");
}

/**
   mover pata delantera izquierda
*/
void paso5() {
  pata4.moverPata(posicion1);
  Serial.println("paso 5");
}

/**
   Empujar todas patas
   Ir a paso 1
*/
void paso6() {
  int del = 5;
  pata1.empujarPata(posicion3);
  delay(del);
  pata2.empujarPata(posicion1);
  delay(del);
  pata3.empujarPata(posicion2);
  delay(del);
  pata4.empujarPata(posicion2);
  Serial.println("paso 6");
}

/**
   Misma posicion que el paso1 pero solo hay que avanzar la pata trasera izquierda
*/

void paso7() {
  pata2.moverPata(posicion3);
  Serial.println("paso 7");
}
