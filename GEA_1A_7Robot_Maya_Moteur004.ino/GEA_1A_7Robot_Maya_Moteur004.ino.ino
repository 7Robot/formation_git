#define Pin1_M1 2
#define Pin0_M1 3
#define Pin1_M2 4 
#define Pin0_M2 5
#define Pin_Enable1 10
#define Pin_Enable2 11 

int Speed1=0;
int Speed2=0;
int Speed;
String S;
float Z;
int Value_AVAR=0;
int Value_DG=0;
int Monte;
int Descend;
int Tir;
int a=20;
int b=20;

void setup() {
  pinMode(Pin1_M1, OUTPUT);
  pinMode(Pin0_M1, OUTPUT);
  pinMode(Pin1_M2, OUTPUT);
  pinMode(Pin0_M2, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void Forward(int Speed1, int Speed2){
  digitalWrite(Pin1_M1, HIGH);
  digitalWrite(Pin0_M1, LOW);
  analogWrite(Pin_Enable1, Speed1);// <<Moteur Droit
  
  digitalWrite(Pin1_M2, HIGH);
  digitalWrite(Pin0_M2, LOW);
  analogWrite(Pin_Enable2, Speed2);// <<Moteur Gauche
}
void Backward(int Speed1,int Speed2){
  digitalWrite(Pin1_M1, LOW);
  digitalWrite(Pin0_M1, HIGH);
  analogWrite(Pin_Enable1, Speed1);// <<Moteur Droit

  digitalWrite(Pin1_M2, LOW);
  digitalWrite(Pin0_M1, HIGH);
  analogWrite(Pin_Enable2, Speed2);// <<Moteur Droit
}

void SpinLeft(int Speed){
  digitalWrite(Pin0_M1, LOW);//1
  digitalWrite(Pin0_M2, HIGH);//1
  analogWrite(Pin_Enable1, 2*Speed);
  
  digitalWrite(Pin1_M1, HIGH);//0
  digitalWrite(Pin1_M2, LOW);//0
  analogWrite(Pin_Enable2, 2*Speed);
}

void SpinRight(int Speed){
  digitalWrite(Pin0_M1, HIGH);//1
  digitalWrite(Pin0_M2, LOW);//1
  analogWrite(Pin_Enable1, Speed);
  
  digitalWrite(Pin1_M1, LOW);//0
  digitalWrite(Pin1_M2, HIGH);//0
  analogWrite(Pin_Enable2, Speed);
}

void Stop(){
  digitalWrite(Pin1_M1, LOW);
  digitalWrite(Pin1_M2, LOW);
  analogWrite(Pin_Enable1, 0);
  
  digitalWrite(Pin0_M1, LOW);
  digitalWrite(Pin0_M2, LOW);
  analogWrite(Pin_Enable2, 0);
}

void loop() {
  ///---Début de la partie du programme qui décode le message reçu de l'Esplora////
  
  
  if (Serial1.available())
  { // If data comes in from Serial1 monitor, send it out to XBee
    int Donnees[]={0,0,0,0,0};
    
    String S=Serial1.readStringUntil(';');
    char Z[17];
    S.toCharArray(Z, 17);
    //Serial1.println(Z);
    char* p=strtok(Z,".");
    //Serial1.println(p);
      for (int i = 0; i < 5; i++){
        Donnees[i]=atoi(p);
        //Serial1.println(p);
        //Serial1.println(Donnees[i]);
        p=strtok(NULL,".");
        //Serial1.println(p);
      }
      
  ///---Fin de la partie du programme qui décode le message de l'Esplora////
     
     int Value_AVAR=map(Donnees[0], 0, 1023, -127, 127);
     int Value_DG=map(Donnees[1], 0, 1023, -127, 127);
     Monte=Donnees[2];
     Descend=Donnees[3];
     Tir=Donnees[4];
     Serial.print("Value_AVAR: ");
     Serial.print(Value_AVAR);
     Serial.print("  Value_DG: ");
     Serial.print(Value_DG);
     Serial.print("  Monte: ");
     Serial.print(Monte);
     Serial.print("  Descend: ");
     Serial.print(Descend);
     Serial.print("  Tir: ");
     Serial.println(Tir);
     
     int Value_G=(2*Value_AVAR+Value_DG)/2;
     int Value_D=(2*Value_AVAR-Value_DG)/2;

     if (Value_AVAR==-1 && Value_DG==0){
        Stop();
     }

     else if (Value_G>0 && Value_D>0){
        Forward(Value_D, Value_G);
        Serial.print("Gauche: ");
        Serial.print(Value_G);
        Serial.print("Droite: ");
        Serial.println(Value_D);
     }

     else if (Value_G<0 && Value_D<0){
        if (Value_G>127){
           Value_G=Value_G*(1/4);// 127/190 à la place de 300 normalement
           }
        if (Value_D>127){
           Value_D=Value_D*(1/4);//Idem
           }
           
        Backward(-Value_G, -Value_D);
        Serial.print("Gauche: ");
        Serial.print(Value_G);
        Serial.print("Droite: ");
        Serial.println(Value_D);
     }

     else if (Value_G>=0 && Value_D<=0){
        SpinRight(-Value_D);
        Serial.print("Gauche: ");
        Serial.print(Value_G);
        Serial.print("Droite: ");
        Serial.println(Value_D);
     }

     else if (Value_G<=0 && Value_D>=0){
        SpinLeft(-Value_G);
        Serial.print("Gauche: ");
        Serial.print(Value_G);
        Serial.print("Droite: ");
        Serial.println(Value_D);
     }

  }

}
