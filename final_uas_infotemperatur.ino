#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions for seven-segment display
const int Buzzer = A1;
const int pSuhu = A0;

const int A = 2;
const int B = 3;
const int C = 4;
const int D = 5;
const int E = 6;
const int F = 7;
const int G = 8;
const int H = 9;

const int pinLED1 = 11; // Pin untuk LED hijau
const int pinLED2 = 12; // Pin untuk LED biru
const int pinButton = 13; // Pin untuk pushbutton 1

int swt = 0;
float suhu, data;
float lastSuhu = -1; // Variabel untuk menyimpan suhu terakhir

// Use 0x3F if 0x27 doesn't work in Tinkercad
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address, 16 columns, and 2 rows

void setup() {
  Wire.begin(); // Initialize I2C communication
  lcd.init();           // Initialize LCD
  lcd.backlight();      // Turn on backlight
  lcd.print("SUHU RUANGAN: ");

  pinMode(pSuhu, INPUT); // pSuhu as input
  pinMode(Buzzer, OUTPUT); // Buzzer as output
  pinMode(pinButton, INPUT);
  digitalWrite(pinButton, HIGH);
  pinMode(pinLED1, OUTPUT); // Set pinLED1 as output
  pinMode(pinLED2, OUTPUT); // Set pinLED2 as output

  Serial.begin(9600);    // Start serial communication

  // Set seven-segment pins as output
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(H, OUTPUT);
}

void displayCharacter(bool a, bool b, bool c, bool d, bool e, bool f, bool g, bool h) {
  digitalWrite(A, a);
  digitalWrite(B, b);
  digitalWrite(C, c);
  digitalWrite(D, d);
  digitalWrite(E, e);
  digitalWrite(F, f);
  digitalWrite(G, g);
  digitalWrite(H, h);
}

void HCHAR() { displayCharacter(LOW, HIGH, HIGH, LOW, HIGH, HIGH, HIGH, LOW); }
void ACHAR() { displayCharacter(HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH, LOW); }
void LCHAR() { displayCharacter(LOW, LOW, LOW, HIGH, HIGH, HIGH, LOW, LOW); }
void OCHAR() { displayCharacter(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW); }
void CCHAR() { displayCharacter(HIGH, LOW, LOW, HIGH, HIGH, HIGH, LOW, LOW); }
void DOT()  { displayCharacter(LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH); }
void ECHAR() { displayCharacter(HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH, LOW); }
void ICHAR() { displayCharacter(LOW, LOW, LOW, LOW, HIGH, HIGH, LOW, LOW); }
void SCHAR() { displayCharacter(HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW); }
void rCHAR() { displayCharacter(HIGH, LOW, LOW, LOW, HIGH, HIGH, LOW, LOW); }
void yCHAR() { displayCharacter(LOW, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, LOW); }

void buzz() {
  digitalWrite(Buzzer, HIGH); // Turn on buzzer
  delay(500);                // Buzz for 100 milliseconds
  digitalWrite(Buzzer, LOW);  // Turn off buzzer
  delay(500);                // Delay before next buzz
}

void cahayaLED() {
   if (digitalRead(pinButton) == 1 && swt == 1){
    digitalWrite(pinLED1, LOW);
    digitalWrite(pinLED2, LOW);
    swt = 0;
    Serial.println("KeLEPAS");
  }
  else if (digitalRead(pinButton) == 0 && swt == 0){
    digitalWrite(pinLED1, HIGH);
    digitalWrite(pinLED2, HIGH);
    swt = 1;
    Serial.println("kEPencet");
  }
}

void loop() {
  //Gass
  cahayaLED();

  // Display "HALO" on 7-segment display
  HCHAR();
  buzz();
  ACHAR();
  buzz();
  LCHAR();
  buzz();
  OCHAR();
  buzz();
  ACHAR();
  buzz();
  CCHAR();
  buzz();
  ACHAR();
  buzz();
  LCHAR();
  buzz();
  DOT();
  buzz();

  HCHAR();
  buzz();
  ACHAR();
  buzz();
  LCHAR();
  buzz();
  OCHAR();
  buzz();
  ECHAR();
  buzz();
  LCHAR();
  buzz();
  ICHAR();
  buzz();
  SCHAR();
  buzz();
  DOT();
  buzz();

  HCHAR();
  buzz();
  ACHAR();
  buzz();
  LCHAR();
  buzz();
  OCHAR();
  buzz();
  rCHAR();
  buzz();
  OCHAR();
  buzz();
  yCHAR();
  buzz();
  DOT();
  buzz();


  // Read temperature
  data = analogRead(pSuhu);
  suhu = (5.0 * data * 100.0) / 1023.0;

  // Display temperature on LCD only if it has changed significantly
  if (abs(suhu - lastSuhu) > 0.1) {
    lcd.setCursor(0, 1);
    lcd.print("                "); // Clear previous temperature
    lcd.setCursor(0, 1);
    lcd.print(suhu);
    lcd.print(" C");
    lastSuhu = suhu; // Update lastSuhu
  }
}