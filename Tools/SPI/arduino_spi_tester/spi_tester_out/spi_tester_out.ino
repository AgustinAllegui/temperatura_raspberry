#include <SPI.h>

#define D_NO 0
#define D_SI 1

#define D_SHOW D_NO

#if D_SHOW == D_SI
#define DDEBUG(A) do{ \
                    Serial.print("-DEBUG: "); \
                    Serial.println(A); \
                  }while(false)

#define DDEBUG2(A,B) do{ \
                    Serial.print("-DEBUG: "); \
                    Serial.println(A,B); \
                  }while(false)

#else

#define DDEBUG(A)
#define DDEBUG2(A,B)

#endif

String reglonIn;

SPISettings configs(5000000, MSBFIRST, SPI_MODE0);

const int chipSelectPin = 4;


void setup()
{
  Serial.begin(9600);
  Serial.println("Conversor Serial a SPI");
  SPI.begin();
  pinMode(chipSelectPin,OUTPUT);
  digitalWrite(chipSelectPin, HIGH);
}

void loop()
{
  bool reglonReadyFlag = false;
  while(Serial.available()){
    char charIn = Serial.read();
    //DDEBUG(charIn);
    switch(charIn){
      case '\n':
      case '\r':
        reglonReadyFlag = endLine(charIn);
        DDEBUG("reglon terminado");
        DDEBUG(reglonIn);
        break;

      default:
        reglonIn += charIn;
        break;
    }
  }

  if(reglonReadyFlag){
    DDEBUG("envio a SPI");
    int largoHexIn = reglonIn.length()/2;
    if(reglonIn.length()%2){
      largoHexIn++;
    }
    sendReglon(largoHexIn);
    reglonIn = "";
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

  DDEBUG("converted values");
  int i = 0;
  int j = 0;
  while(true){
    tempChar = charToHex(reglonIn[i]);
    tempChar = tempChar<<4;
    i++;
    tempChar += charToHex(reglonIn[i]);
    i++;
    sendBuffer[j] = tempChar;
    j++;
    if(j>largo_){
      break;
    }
    if(i>reglonIn.length()){
      break;
    }
  }

  DDEBUG("sendBuffer");
  for(int k = 0; k<largo_; k++){
    DDEBUG2(sendBuffer[k],HEX);
  }

  Serial.print(">>");
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
char charToHex(char caracter_)
{
  //DDEBUG("char to hex:");
  //DDEBUG(caracter_);
  if((caracter_ >= '0') && (caracter_ <= '9')){
    return (caracter_ - '0');
  }

  if((caracter_ >= 'A') && (caracter_ <= 'F')){
    //DDEBUG((caracter_ - 'A' + 0x0a));
    //DDEBUG2((caracter_ - 'A' + 0x0a),BIN);
    return (caracter_ - 'A' + 0x0a);
  }

  if((caracter_ >= 'a') && (caracter_ <= 'f')){
    //DDEBUG((caracter_ - 'a' + 0x0a));
    //DDEBUG2((caracter_ - 'a' + 0x0a),BIN);
    return (caracter_ - 'a' + 0x0a);
  }
  return 0;
}


/* Escribe el buffer en el puerto serial
 */
void printBuffer(uint8_t *buffer_, int largo_)
{
  for(int i = 0; i<largo_ ; i++){
    if(buffer_[i]<0x10){
      Serial.print('0');
    }
    Serial.print(buffer_[i],HEX);
  }
}
