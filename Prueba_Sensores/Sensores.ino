//Laboratorio de Microcontroladores
//Proyecto 
//Realizado por:
//Gabriel Barahona Otoya B70896
//Yenner Gonzalez Araya B83375

// --- Decalracion Variables Globales ---
int SensorHG_1;
int SensorHG_2;
int SensorHG_3;
int Flama_1; 
int Flama_2;
int Flama_3;

// Pines
int Buzzer = 22;
int SensorFlama_1 = 7;
int SensorFlama_2 = 5;
int SensorFlama_3 = 3;

void setup() {
  Serial.begin(9600);
  pinMode(Buzzer, OUTPUT);
  pinMode(SensorFlama_1, INPUT);
  pinMode(SensorFlama_2, INPUT);
  pinMode(SensorFlama_3, INPUT);
}

void loop() {
  Flama_1 = digitalRead(SensorFlama_1);
  Flama_2 = digitalRead(SensorFlama_2);
  Flama_3 = digitalRead(SensorFlama_3);
  if (Flama_1 == LOW && Flama_2 == LOW && Flama_3 == LOW){
    digitalWrite(Buzzer, LOW);
    Serial.println("LEDs off");
  }
  else if (Flama_1 == HIGH){
    digitalWrite(Buzzer, HIGH);
    Serial.println("LED_1 on");
  }
  else if (Flama_2 == HIGH){
    digitalWrite(Buzzer, HIGH);
    Serial.println("LED_2 on");
  }
  else if (Flama_3 == HIGH){
    digitalWrite(Buzzer, HIGH);
    Serial.println("LED_3 on");
  }
  
  SensorHG_1 = analogRead(A0);
  Serial.print("SensorHG_1: ");
  Serial.println(SensorHG_1);
  SensorHG_2 = analogRead(A1);
  Serial.print("SensorHG_2: ");
  Serial.println(SensorHG_2);
  SensorHG_3 = analogRead(A2);
  Serial.print("SensorHG_3: ");
  Serial.println(SensorHG_3);
  delay(3000);
}
