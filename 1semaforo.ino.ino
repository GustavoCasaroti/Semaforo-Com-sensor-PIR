/*
* código de teste para o TCC
* intuito usar váriaveis para controle de um  bloco
* de semáforos (pedestres e carros) para teste em
* um arduino físico e ver funcionalidade
* tentar aplicar a +1 bloco de semáforos
*/


//variaveis
int verme = 12; // estabelece o semáforo para carros
int amarelo = 11;
int verde = 10;
int vermped = 9; // estabelece o semáforo para pedestres
int verdeped = 8;
int pir = 2; // pino do sensor
int button=3; // pino do botão

int VEHVERMELHO= LOW;//estabelece variáveis de controle do semáforo
int VEHAMARELO= LOW;
int VEHVERDE= HIGH;
int PEDVERDE= LOW;
int PEDVERMELHO= HIGH;

/*-------------------------------------controle de tempo-------------------------------------------------------------*/ 

int crossTime = 5000; // tempo para que os pedestres atravessem
unsigned long changeTime=0; // tempo desde que o botão foi pressionado
unsigned long previousmillis1=0; // último estado de acionamento do verde caso não o sensor não seja ativado
unsigned long previousmillis2=0; // último estado de acionamento do amarelo caso não o sensor não seja ativado
unsigned long previousmillis3=0; // último estado de acionamento do verme caso não o sensor não seja ativado

/*-------------------------------------tempo de cada led------------------------------------------------------------*/ 

unsigned long tempo1=5000; //tempo $verde
unsigned long tempo2=3000; //tempo $amarelo
unsigned long tempo3=5000; //tempo $verme

/*------------------------------------------------------------------------------------------------------------------*/ 
void setup() {
pinMode(verme, OUTPUT);//leds dos carros
pinMode(amarelo, OUTPUT);
pinMode(verde, OUTPUT);
pinMode(vermped, OUTPUT);//leds dos pedestres
pinMode(verdeped, OUTPUT);
pinMode(pir, INPUT); // sensor pir no pino 2 

// programa é iniciado com esta configuração:
digitalWrite(verde, HIGH);
digitalWrite(vermped, HIGH);

Serial.begin(9600);
/*------------------------------------------------------------------------------------------------------------------*/  

}
void loop() {
 
/*------------------------------------------funcionamento sem sensor------------------------------------------------*/ 
  
  //led verde dos carros
  if(millis()-previousmillis1>=tempo1 && VEHVERMELHO==LOW && VEHAMARELO==LOW){
    previousmillis1=millis();
    digitalWrite(verde, HIGH);
    if(VEHVERDE==LOW){
      VEHVERDE=HIGH;
      PEDVERDE=LOW;
      PEDVERMELHO=HIGH;
    }else{ 
      VEHVERDE=LOW;
            digitalWrite(verde, VEHVERDE); //escrita digital de cada inversão do estado dos leds
            digitalWrite(vermped, PEDVERMELHO);
            }
  }

  //led amarelo
  if(millis()-previousmillis2>=tempo2 && VEHVERDE==LOW && VEHVERMELHO==LOW){
    previousmillis2=millis();
    if(VEHAMARELO==LOW){
      VEHAMARELO=HIGH;
    }else 
      VEHAMARELO=LOW;
 digitalWrite(amarelo, VEHAMARELO);//escrita digital de cada inversão do estado do led
        
}

  //led vermelho dos carros
  if(millis()-previousmillis3>=tempo3 && VEHVERDE==LOW && VEHAMARELO==LOW){
    previousmillis3=millis();
    if(VEHVERMELHO==LOW){
      VEHVERMELHO=HIGH;
      PEDVERDE=HIGH;
      PEDVERMELHO=LOW;
      
    }else{ VEHVERMELHO=LOW;
           PEDVERDE=LOW;
           PEDVERMELHO=HIGH;
         }
 digitalWrite(verme, VEHVERMELHO); //escrita digital de cada inversão do estado dos leds
 digitalWrite(verdeped, PEDVERDE); 
 digitalWrite(vermped, PEDVERMELHO);
  }

  
/*-----------------------------------------quando sensor é ativo----------------------------------------------------*/
int estado = digitalRead(pir);
int estado2= digitalRead(button);

/* A expressão dentro da função if verifica se o botão foi pressionado ou sensor fez a leitura. Para ambos, irá ser verificado se transcorreram 2 segundos desde a última vez que 
isso ocorreu, verifica se o sinal ficou aberto pelo menos 1.5 segundos e garante que o sinal só seja fechado quando o sinal estiver verde, evitando o prolongamento de um sinal que já estivera fechado */

if (estado == HIGH && VEHVERMELHO==LOW && VEHAMARELO==LOW && millis()-changeTime>2000 && millis()-previousmillis1>1500 || VEHVERMELHO==LOW &&VEHAMARELO==LOW && millis()-changeTime>2000 && millis()-previousmillis1>1500 && estado2 == HIGH) {
  Serial.println("botão / pir acionado");
  digitalWrite(verde, HIGH);
  digitalWrite(pir, HIGH);
        //sinal fica amarelo

/*-----------------------------------quando os pedestres forem atravessar -----------------------------------------*/

digitalWrite(verde, LOW); // apaga o verde
digitalWrite(amarelo, HIGH); // acende o amarelo
delay(2000);
digitalWrite(amarelo, LOW); // apaga o amarelo
digitalWrite(verme, HIGH); // acende o vermelho
delay(1000);
digitalWrite(vermped, LOW); // apaga o vermelho dos pedestres
digitalWrite(verdeped, HIGH); // acende o verde dos pedestres

delay(crossTime); 

digitalWrite(vermped, HIGH); // acende o vermelho dos pedestres
digitalWrite(verdeped,LOW);
delay(500); //alterado de 500 --> 1000

//pedestre deve aguardar o tempo para a lida do sensor


digitalWrite(verme, LOW); // apaga o vermelho
delay(100);
digitalWrite(verde, HIGH); // acende o verde
digitalWrite(amarelo, LOW); // apaga o amarelo
// registra o tempo desde a última alteração no semáforo
changeTime = millis();
digitalWrite(verde, HIGH); 
delay(5000);
// depois retorna para o loop principal do programa
}else{ digitalWrite(pir, LOW);

}

}
