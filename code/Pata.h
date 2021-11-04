
class Pata {
  private:
    byte motor1 = 0;
    byte motor2 = 0;
    int offsetM1 = 0;
    int offsetM2 = 0;
    int centro = 6000;
    int posicion1 = centro;
    int posicion2 = centro;
    int posicion3 = centro;
    int posicion[3] = {posicion1, posicion2, posicion3};
    int levantar = 0;

  public:
    /**
       Constructor, recibe el pin del Maestro al que están conectados el motor 1 y 2 de cada pata
    */

    Pata(byte m1, byte m2) {
      motor1 = m1;
      motor2 = m2;
    }

    void setOffset(int off1, int off2) {
      offsetM1 = off1;
      offsetM2 = off2;
    }

    /**
       Posicion1: mas externa
       Posicion2: intermedia
       Posicion3: mas al centro del robot
    */
    void setPosiciones(int pos1, int pos2, int pos3, int lev) {
      posicion1 = pos1;
      posicion[0] = posicion1;
      posicion2 = pos2;
      posicion[1] = posicion2;
      posicion3 = pos3;
      posicion[2] = posicion3;
      levantar = lev;
    }

    /**
       Inicializa los motores, los pone en posicion centrada y les da la velocidad y aceleracion recibidas
    */
    void setupPata(int vel, int acel) {
      maestro.setTarget(motor1, posicion3 + offsetM1);
      maestro.setSpeed(motor1, vel);
      maestro.setAcceleration(motor1, acel);
      maestro.setTarget(motor2, posicion3 + offsetM2);
      maestro.setSpeed(motor2, vel);
      maestro.setAcceleration(motor2, acel);

    }

    void moverPata(int pos) {
      int del = 50;
      maestro.setTarget(motor2, levantar + offsetM2);
      delay(del);
      maestro.setTarget(motor1, posicion[pos] + offsetM1);
      delay(del);
      maestro.setTarget(motor2, centro + offsetM2);
      delay(del);
    }

    void empujarPata(int pos) {
      maestro.setTarget(motor1, posicion[pos] + offsetM1);
    }

    void levantarPata(){
      maestro.setTarget(motor2, levantar + offsetM2);
    }
};
