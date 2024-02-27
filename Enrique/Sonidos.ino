/// @file    Blink.ino
/// @brief   Blink the first LED of an LED strip
/// @example Blink.ino

#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 179

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 8


// Define the array of leds
CRGB leds[NUM_LEDS];

int ledNave = 0;
int ledNave2 = 0;

//longs para la hora

long tiempoActual = 0;
long tiempoAnteriorQueActualizamosElLed = 0;
bool ledEncendido = true;
int estadoBotonAnterior1 = 0;
int estadoBotonAnterior2 = 0;
int contadorClicks = 0;
int contadorClicks2 = 0;
int objetivoClicks = 1;
int objetivoClicks2 = 2;

void setup() { 
     FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
     Serial.begin(9600);
     pinMode(5, INPUT);
     pinMode(3, INPUT);
   }

void loop() { 
  int estadoBoton = digitalRead(5);
  int estadoBoton2 = digitalRead(3);
  //Serial.println(estadoBoton);
  int estadoEjeY = analogRead(A0);
 // Serial.println(estadoEjeY);
  int espera = map(estadoEjeY, 0, 1023, 50, 270);
 // Serial.println(espera);
  
  tiempoActual = millis();
  //Serial.println(tiempoActual);
  if (tiempoActual> (tiempoAnteriorQueActualizamosElLed + espera)) {
    tiempoAnteriorQueActualizamosElLed = tiempoActual;
    if (ledEncendido) {
        leds[ledNave] = CRGB::Red;
        leds[ledNave2] = CRGB::Blue;
        if (ledNave == ledNave2) {
          leds[ledNave2] = CRGB::Purple;
        }
         FastLED.show();      
    }
    else {
        leds[ledNave] = CRGB::Black;
        leds[ledNave2] = CRGB::Black;
         FastLED.show();
    }

    ledEncendido = !ledEncendido;
    
  }
  if(estadoBoton == HIGH && estadoBotonAnterior1!= estadoBoton ) {
    contadorClicks ++;
    tone(10, 330, 75);
    Serial.println(contadorClicks);
  }
  estadoBotonAnterior1 = estadoBoton;
  //player 2
  if(estadoBoton2 == HIGH && estadoBotonAnterior2!= estadoBoton2 ) {
    contadorClicks2 ++;
    tone(10, 500, 200);
    Serial.println(contadorClicks2);
  }
  estadoBotonAnterior2 = estadoBoton2;
  if ( contadorClicks == objetivoClicks){
    leds[ledNave] = CRGB::Black;
    ledNave +=1;
    contadorClicks = 0;
    objetivoClicks = random(1,4);
  }
  if ( contadorClicks2 == objetivoClicks2){
    leds[ledNave2] = CRGB::Black;
    ledNave2 +=1;
    contadorClicks2 = 0;
    objetivoClicks2 = random(1,4);
  }
  if (ledNave > 178) {
    ledNave = 0;
    tone(10, 165, 600);
  }
  if (ledNave2 > 178) {
    ledNave2 = 0;
    tone(10, 660, 600);
  }  
   
}
