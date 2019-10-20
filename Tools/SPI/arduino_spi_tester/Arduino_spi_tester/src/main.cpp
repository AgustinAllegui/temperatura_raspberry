#include <Arduino.h>

bool endLine(const char char_in_);
bool checkChar(const char caracter_);
void sendReglon(int largo_);
uint8_t charToHex(char caracter_);
void printBuffer(uint8_t *buffer_, int largo_);

/*--------------------------------------------------------------*/

#include <SPI.h>

String reglonIn;

SPISettings configs(5000000, MSBFIRST, SPI_MODE0);

const int chipSelectPin = 1;


void setup()
{
  Serial.begin(9600);
  Serial.println("Iniciado");
  SPI.begin();
  pinMode(chipSelectPin,OUTPUT);
  digitalWrite(chipSelectPin, HIGH);
}

void loop()
{
  bool reglonReadyFlag = false;
  while(Serial.available()){
    char charIn = Serial.read();
    switch(charIn){
      case '\n':
      case '\r':
        reglonReadyFlag = endLine(charIn);
        break;

      default:
        reglonIn += charIn;
        break;
    }
  }

  if(reglonReadyFlag){
    int largoHexIn = reglonIn.length()/2;
    if(reglonIn.length()%2){
      largoHexIn++;
    }
    sendReglon(largoHexIn);
  }
}


/* hace el chequeo de el fin de linea y devuelve true cuando la linea es correcta
 */
bool endLine(const char charIn_)
{
  if(reglonIn.length() == 0){
    return false;
  }

  for(unsigned int i = 0; i<reglonIn.length(); i++){
    if(!checkChar(reglonIn.charAt(i))){
      // hay un caracter que no pertenece
      reglonIn = "";
      return false;
    }
  }

  return true;
}

/* chequea si un caracter esta en hexa
 */
bool checkChar(const char caracter_)
{
  if((caracter_ >= '0') && (caracter_ <= '9')){
    return true;
  }

  if((caracter_ >= 'A') && (caracter_ <= 'F')){
    return true;
  }

  if((caracter_ >= 'a') && (caracter_ <= 'f')){
    return true;
  }

  return false;
}


/* convierte el reglon en un arreglo de bytes y lo envia a travez del SPI
 */
void sendReglon(int largo_)
{
  uint8_t sendBuffer[largo_] = {0};
  uint8_t tempChar;

  for(int i = 0; i<largo_; i++){
    tempChar = charToHex(reglonIn[i*2]) << 4;
    tempChar += charToHex(reglonIn[(i*2)+1]);
    sendBuffer[i] = tempChar;
  }

  Serial.print("-");
  printBuffer(sendBuffer, largo_);
  Serial.print("\t ->>");
  
  SPI.beginTransaction(configs);

  digitalWrite(chipSelectPin,LOW);
  delay(1);
  SPI.transfer(sendBuffer, largo_);
  delay(1);
  digitalWrite(chipSelectPin,HIGH);
  
  SPI.endTransaction();

  printBuffer(sendBuffer, largo_);
  Serial.println();


}

/* convierte un solo caracter a su valor en hexa
 */
uint8_t charToHex(char caracter_)
{
  if((caracter_ >= '0') && (caracter_ <= '9')){
    return (caracter_ - '0');
  }

  if((caracter_ >= 'A') && (caracter_ <= 'F')){
    return (caracter_ - 'A');
  }

  if((caracter_ >= 'a') && (caracter_ <= 'f')){
    return (caracter_ - 'a');
  }
  return 0;
}


/* Escribe el buffer en el puerto serial
 */
void printBuffer(uint8_t *buffer_, int largo_)
{
  for(int i = 0; i<largo_ ; i++){
    Serial.print(buffer_[i],HEX);
  }
}
