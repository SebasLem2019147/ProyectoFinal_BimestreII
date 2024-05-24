/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AV 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Dev: Sebastian Enrique Lemus Salvador
   Fecha: 24 de mayo de 2024
   
   link de la simulacion: https://www.tinkercad.com/things/7XXzl2WxjX5-practica-final-taller?sharecode=yTTgOo6l_2lT5yXM1GK9S_8yuFGeEljU9aRN7Lr2nUU
   
*/

#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define direccion_lcd 0x27

LiquidCrystal_I2C LCD_SebasLem(direccion_lcd, 16, 2);
 
Servo servo_SebasLem;

const int filas = 2;
const int columnas = 3;
char keys[filas][columnas] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
};
byte pinesFila[filas] = {13, 12};
byte pinesColumna[columnas] = {10, 9, 8};
Keypad teclado = Keypad(makeKeymap(keys), pinesFila, pinesColumna, filas, columnas);

char teclaPresionada;

int tiempo = 250;
const int pinesLeds[] = {14, 15, 16, 17};

const int pinesDisplay[] = {7, 6, 5, 4, 3, 2, 1};

void setup() {
  servo_SebasLem.attach(11);
  servo_SebasLem.write(0);

  LCD_SebasLem.init();
  LCD_SebasLem.backlight();
  LCD_SebasLem.clear();
  LCD_SebasLem.setCursor(3, 0);
  LCD_SebasLem.print("Sebastian");
  LCD_SebasLem.setCursor(1, 1);
  LCD_SebasLem.print("Proyecto Final");  
  for (int i = 0; i < 3; i++) {
    pinMode(pinesLeds[i], OUTPUT);
  }
  for (int i = 0; i < 7; i++) {
    pinMode(pinesDisplay[i], OUTPUT);
  }  
}

void loop() {
  teclaPresionada = teclado.getKey();
  switch (teclaPresionada) {
    case '1':
    {
      Serial.begin(9600);
      Serial.println("contador de 0 a 99;");
      for(int i = 0; i < 100; i++){
        Serial.println(i);
        delay(tiempo);
      }
      Serial.end();
    break;
    }
    case '2':
    {
      Serial.begin(9600);
      Serial.println("contador de 99 a 0;");
      for(int i = 99; i >= 0; i--){
        Serial.println(i);
        delay(tiempo);
      }
      Serial.end();
    break;
    }
    case '3':
    {
      for (int led = 0; led < 3; led++) { 
        digitalWrite(pinesLeds[led], HIGH);
        delay(tiempo);
        digitalWrite(pinesLeds[led + 1], HIGH);
        delay(tiempo);
        digitalWrite(pinesLeds[led], LOW);
        delay(tiempo);
      }
      for (int led = 3; led > 0; led--) {  
        digitalWrite(pinesLeds[led], HIGH);
        delay(tiempo);
        digitalWrite(pinesLeds[led - 1], HIGH);
        delay(tiempo);
        digitalWrite(pinesLeds[led], LOW);
        delay(tiempo);
        digitalWrite(14, LOW);
      }
    break;
    }
    case '4':
    {
      delay(1000);
      animacionDisplay();
    break;
    }
    case '5':
    {
      delay(tiempo);
      servo_SebasLem.write(180);
      delay(5000);
      servo_SebasLem.write(0);
    break;
    }
  }
}

void animacionDisplay() { 
  for (int i = 0; i < 2; i++) {
    digitalWrite(7, HIGH);
    digitalWrite(4, HIGH);
    delay(tiempo);
    apagarDisplay();
    delay(tiempo);
  }  
  for (int i = 0; i < 2; i++) {
    digitalWrite(6, HIGH); 
    digitalWrite(5, HIGH); 
    digitalWrite(3, HIGH); 
    digitalWrite(2, HIGH);
    delay(tiempo);
    apagarDisplay();
    delay(tiempo);
  }  
  for (int i = 0; i < 2; i++) {
    digitalWrite(1, HIGH);
    delay(tiempo);
    apagarDisplay();
    delay(tiempo);
  }  
  for (int i = 0; i < 3; i++) {
    encenderDisplay();
    delay(tiempo);
    apagarDisplay();
    delay(tiempo);
  }  
  for (int i = 0; i < 7; i++) {
    apagarDisplay();
    digitalWrite(pinesDisplay[i], HIGH);
    delay(tiempo);
  }
  for (int i = 6; i >= 0; i--) {
    apagarDisplay();
    digitalWrite(pinesDisplay[i], HIGH);
    delay(tiempo);
  }
  apagarDisplay();
}

void encenderDisplay() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(pinesDisplay[i], HIGH);
  }
}

void apagarDisplay() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(pinesDisplay[i], LOW);
  }
}
