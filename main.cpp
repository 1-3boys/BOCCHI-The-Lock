# BOCCHI-The-Lock#include <Arduino_FreeRTOS.h>
#include <Keypad.h>
#include <semphr.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys [ROWS][COLS] = {
{'1' , '2' , '3' , 'A'},
{'4' , '5' , '6' , 'B'},
{'7' , '8' , '9' , 'C'},
{'#' , '0' , '*' , 'D'},
};
byte rowPins[ROWS] = {36, 34, 32, 30};
byte colPins[COLS] = {28, 26, 24, 22};

int speaker = 52;
int frequency[8] = {262, 294, 330, 349, 392, 440, 494, 523};

void keyPadInput( void *pvParameters );

void setup() {

  Serial.begin(9600);

  xTaskCreate(
   keyPadInput
   ,  "keyPadInput"
   ,  128  
   ,  NULL
   ,  1
   ,  NULL );

}

void loop() {
}

void keyPadInput(void *pvParameters){

  pinMode(speaker, OUTPUT);

  Keypad save = Keypad (makeKeymap(keys), rowPins, colPins, ROWS, COLS);

  while(true){
    char key = save.getKey();
    if(key){
      tone(speaker,frequency[2],500);
      Serial.println(key);
    }
    vTaskDelay(1);
  }
  vTaskDelete( NULL );
}
