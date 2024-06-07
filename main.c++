#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// LCD and sensor configurations
#define endereco_lcd 0x27
#define colunas_lcd 20
#define linhas_lcd 4

LiquidCrystal_I2C lcd(endereco_lcd, colunas_lcd, linhas_lcd);

#define pino_dht 9
#define tipo_dht DHT22

DHT dht(pino_dht, tipo_dht);

int pino_pot = A2;
int perigo = 11;   // LED vermelho
int alerta = 12;   // LED amarelo
int ok = 13;       // LED verde
int buzzer = 10;

const int pino_turbidez = A0;
const int pino_ph = A1;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(perigo, OUTPUT);
  pinMode(alerta, OUTPUT);
  pinMode(ok, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  dht.begin();
  pinMode(pino_turbidez, INPUT);
  pinMode(pino_ph, INPUT);
  Serial.begin(9600);

  // Inicializa os LEDs e buzzer como desligados
  digitalWrite(perigo, LOW);
  digitalWrite(alerta, LOW);
  digitalWrite(ok, LOW);
  noTone(buzzer);
}

void loop() {
  // Reseta LEDs e buzzer no início de cada loop
  digitalWrite(perigo, LOW);
  digitalWrite(alerta, LOW);
  digitalWrite(ok, LOW);
  noTone(buzzer);

  // Leitura do valor do pino analogico
  int valorpot = analogRead(pino_pot);

  // Leitura da temperatura
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Falha na leitura da temperatura!");
    lcd.setCursor(0, 0);
    lcd.print("Temp: Erro");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");
  }

  if (temperature < 29) {
    lcd.setCursor(0, 2);
    lcd.print("Temperatura Ideal!");
    digitalWrite(ok, HIGH);  // LED verde
  } else if (temperature < 35) {
    lcd.setCursor(0, 2);
    lcd.print("Alerta! Aquecimento");
    digitalWrite(alerta, HIGH);  // LED amarelo
  } else {
    lcd.setCursor(0, 2);
    lcd.print("PERIGO! Aquecimento");
    digitalWrite(perigo, HIGH);  // LED vermelho
    tone(buzzer, 1000);  // Ativar buzzer com som de 1000 Hz
  }

  delay(5000);
  lcd.clear();
  delay(1000);

  // Leitura do sensor de turbidez
  int turbidez = analogRead(pino_turbidez);
  float turvo = map(turbidez, 0, 1023, 0, 6); // Mapear corretamente de 0 a 5 NTU (exemplo)
  lcd.setCursor(0, 0);
  lcd.print("Turbidez: ");
  lcd.print(turvo);
  lcd.print(" mg/L");

  if (turvo <= 0.1) {
    lcd.setCursor(0, 2);
    lcd.print("Agua cristalina!");
    digitalWrite(ok, HIGH);  // LED verde
  } else if (turvo < 4) {
    lcd.setCursor(0, 2);
    lcd.print("Turbidez balanciada!");
    digitalWrite(alerta, HIGH);  // LED amarelo
  } else {
    lcd.setCursor(0, 2);
    lcd.print("SOS! Turbidez ALTA!");
    digitalWrite(perigo, HIGH);  // LED vermelho
    tone(buzzer, 1000);  // Ativar buzzer com som de 1000 Hz
  }

  delay(5000);
  lcd.clear();
  delay(1000);

  // Leitura de CO2 (usando leitura de umidade como proxy)
  float nivel_co2 = dht.readHumidity();
  int co2 = map(nivel_co2, 0, 100, 0, 25); // Mapear corretamente de 0 a 25 (exemplo)

  if (isnan(nivel_co2)) {
    Serial.println("Falha na leitura da umidade!");
    lcd.setCursor(0, 0);
    lcd.print("Nivel de CO2: Erro");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Nivel de CO2: ");
    lcd.print(co2);
    lcd.print(" mg/L");
  }

  if (co2 <= 10) {
    lcd.setCursor(0, 2);
    lcd.print("Concentracao Ideal!");
    digitalWrite(ok, HIGH);  // LED verde
  } else if (co2 <= 25) {
    lcd.setCursor(0, 2);
    lcd.print("Atencao!!");
    lcd.setCursor(0, 3);
    lcd.print("Aumento no nivel CO2");
    digitalWrite(alerta, HIGH);  // LED amarelo
  } else {
    lcd.setCursor(0, 2);
    lcd.print("PERIGO!!!!!");
    lcd.setCursor(0, 3);
    lcd.print("Concentracao ALTA");
    digitalWrite(perigo, HIGH);  // LED vermelho
    tone(buzzer, 1000);  // Ativar buzzer com som de 1000 Hz
  }

  delay(5000);
  lcd.clear();
  delay(1000);

  // Leitura do sensor de pH
  float ph = map(valorpot, 0, 1023, 0, 14); // Mapeamento para valores de pH de 0 a 14
  lcd.setCursor(0, 0);
  lcd.print("PH da Agua: ");
  lcd.print(ph);

  if (ph < 5) {
    lcd.setCursor(0, 2);
    lcd.print("PH MUITO ACIDO!");
    digitalWrite(perigo, HIGH);  // LED vermelho
    tone(buzzer, 1000);  // Ativar buzzer com som de 1000 Hz
  } else if (ph < 7) {
    lcd.setCursor(0, 2);
    lcd.print("PH Acido!");
    digitalWrite(alerta, HIGH);  // LED amarelo
  } else if (ph < 8) {
    lcd.setCursor(0, 2);
    lcd.print("PH Neutro!");
    digitalWrite(ok, HIGH);  // LED verde
  } else if (ph < 11) {
    lcd.setCursor(0, 2);
    lcd.print("PH Alcalino!");
    digitalWrite(alerta, HIGH);  // LED amarelo
  } else {
    lcd.setCursor(0, 2);
    lcd.print("PH MUITO ALCALINO!");
    digitalWrite(perigo, HIGH);  // LED vermelho
    tone(buzzer, 1000);  // Ativar buzzer com som de 1000 Hz
  }

  // Atraso para atualização da leitura
  delay(5000);
  lcd.clear();
  delay(1000);
}
