    // pinos do semaforo 1
    const int verde=10;
    const int amarelo=11;
    const int verme=12;
    const int vermped=9;
    const int verdeped=8;

    // variaveis que "detectam" estado do led
    int VEHVERDE;
    int VEHAMARELO;
    int VEHVERMELHO;
    int PEDVERMELHO;
    int PEDVERDE;
    int VEHVERDE2;
    int VEHAMARELO2;
    int VEHVERMELHO2;
    int PEDVERMELHO2;
    int PEDVERDE2;

    // pinos do semaforo 2
    const int verde2=5;
    const int amarelo2=6;
    const int verme2=7;
    const int vermped2=4;
    const int verdeped2=3;
    
    // sensores de movimento
    const int pir=2;
    #define button 13

    // parametro do timer
    const int resettimer=800; // quanto mais baixo, mais curtos serao os ciclos

    // variaveis de controle do loop
    int contador=0;
    int espera=0;
    int ciclo=0;

    int crossTime=2500; // tempo de travessia 
    int timerpir=0; // variavel de controle pra garantir que o semaforo rode ao menos 1 vez antes de ser acionado denovo
    


    void setup() {
    pinMode(13, OUTPUT);           // led interno
    pinMode(verde, OUTPUT);
    pinMode(amarelo, OUTPUT);
    pinMode(verme, OUTPUT);
    pinMode(verde2, OUTPUT);
    pinMode(amarelo2, OUTPUT);
    pinMode(verme2, OUTPUT);
    pinMode(verdeped, OUTPUT);
    pinMode(vermped, OUTPUT);
    pinMode(verdeped2, OUTPUT);
    pinMode(vermped2, OUTPUT);
    pinMode(pir, INPUT);
    pinMode(button, INPUT);

    Serial.begin(9600);

    }

    void loop() {
    switch(ciclo) {
        default:
        case 0:    // s1 verde, s2 vermelho
        digitalWrite(verde, HIGH);
        digitalWrite(verme, LOW);
        digitalWrite(verme2, HIGH);
        digitalWrite(amarelo2, LOW);
        digitalWrite(vermped, HIGH);
        digitalWrite(verdeped, LOW);
        digitalWrite(vermped2, LOW);
        digitalWrite(verdeped2, HIGH);

        VEHVERDE=verde;
        VEHVERMELHO=verme;
        VEHVERMELHO2=verme2;
        VEHAMARELO2=amarelo2;
        PEDVERMELHO=vermped;
        PEDVERDE=verdeped;
        PEDVERMELHO2=vermped2;
        PEDVERDE2=verdeped2;

        espera=4;
        break;
        case 1:    // s1 amarelo, s2 continua vermelho
        digitalWrite(amarelo, HIGH);
        digitalWrite(verde, LOW);

        VEHAMARELO=amarelo;
        VEHVERDE=verde;

        espera=2;
        break;
        case 2:    // s1 vermelho, s2 verde
        digitalWrite(verme, HIGH);
        digitalWrite(amarelo, LOW);
        digitalWrite(verde2, HIGH);
        digitalWrite(verme2, LOW);
        digitalWrite(vermped, LOW);
        digitalWrite(verdeped, HIGH);
        digitalWrite(vermped2, HIGH);
        digitalWrite(verdeped2, LOW);

        VEHVERMELHO=verme;
        VEHAMARELO=amarelo;
        VEHVERDE2=verde2;
        VEHVERMELHO2=verme2;
        PEDVERMELHO=vermped;
        PEDVERDE=verdeped;
        PEDVERMELHO2=vermped2;
        PEDVERDE2=verdeped2;

        espera=4;
        break;
        case 3:    // s1 continua vermelho, s2 amarelo
        digitalWrite(amarelo2, HIGH);
        digitalWrite(verde2, LOW);

        VEHAMARELO2=amarelo2;
        VEHVERDE2=verde2;

        espera=2;
        timerpir++;
        break;
        
    
    }    
    digitalWrite(13, HIGH);
    delay(resettimer/2);
    digitalWrite(13, LOW);
    contador++;
    if (contador>=espera) {
        contador=0;
        ciclo++;
        if (ciclo>4) {
        ciclo=0;
        }  
    }  
    delay(resettimer/2);
    

VEHVERMELHO=verme;
VEHVERMELHO2=verme2;
VEHVERDE=verde;
VEHVERDE2=verde2;
VEHAMARELO=amarelo;
VEHAMARELO2=amarelo2;
PEDVERDE=verdeped;
PEDVERDE2=verdeped2;
PEDVERMELHO=vermped;
PEDVERMELHO2=vermped2;

// informe de que o sensor está pronto para uso
if(timerpir>=3){
    if(timerpir==3){
Serial.println("Semaforo pronto para liberar travessia");
}
Serial.print("Vezes loopado: ");
Serial.println(timerpir);
}
// caso sensor 1 seja ativado.

int estado = digitalRead(pir);
if(estado==HIGH && timerpir>=3 || digitalRead(button)==HIGH && timerpir>=1){
    Serial.println("Sensor ativado, travessia liberada!");

    // area que manda pro amarelo antes de enviar pro vermelho
    if(VEHVERDE==HIGH){
        digitalWrite(verde, LOW);
        VEHVERDE = verde;
        digitalWrite(amarelo, HIGH);
        VEHAMARELO = amarelo;
        delay(1000);
    }else if(VEHVERDE2==HIGH){
        digitalWrite(verde2, LOW);
        VEHVERDE2 = verde2;
        digitalWrite(amarelo2, HIGH);
        VEHAMARELO2 = amarelo2;
        delay(1000); // ou deveria
    }
        digitalWrite(verme, HIGH);
        digitalWrite(verme2, HIGH);
        digitalWrite(verde, LOW);
        digitalWrite(verde2, LOW);
        digitalWrite(amarelo, LOW);
        digitalWrite(amarelo2, LOW);
        digitalWrite(verdeped, HIGH);
        digitalWrite(verdeped2, HIGH);
        digitalWrite(vermped, LOW);
        digitalWrite(vermped2, LOW);

digitalWrite(13, HIGH);
    delay(crossTime/2);
    digitalWrite(13, LOW);
    contador++;
    if (contador>=espera) {
        contador=0;
        ciclo++;
        if (ciclo>5) {
        ciclo=0;
        }  
    }  
    delay(crossTime/2);
    timerpir=0;

}

    }
