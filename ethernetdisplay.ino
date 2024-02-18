#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

boolean attivo = false;
String input = "";
byte inputL = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = millis();

void Callback(char* topic, byte* payload, unsigned int length) {
  char message[length + 1];
  for (int i = length; i >= 0; i--) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';
  String payloadstring = String(message);
  if (payloadstring != input)
  {
    input = payloadstring;
    inputL = input.length();
    attivo = true;
    Serial.println(input);
  }

}


EthernetClient ethclient;
PubSubClient mqttclient("www.mqtt.one", 1883, Callback, ethclient);    //prima variabile il server MQTT, la seconda è la porta
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 128);                                              //indirizzo ip scheda lan
IPAddress dnsserver(8, 8, 8, 8);                                             //server dns scheda lan
IPAddress gateway(192, 168, 1, 1);                                           //gateway della lan
IPAddress subnet(255, 255, 255, 0);                                          //subnet mask della lan

void setup() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.print("Attendere Prego");
  lcd.noBacklight();
  pinMode(A1, OUTPUT);
  digitalWrite(A1, HIGH);
  delay(5000);
  Ethernet.begin(mac, ip, dnsserver, gateway, subnet);
  delay(5000);
  Serial.begin(38400);
  mqttclient.connect("Arduino", "account", "password" );                // la seconda variabile è la username del server, la terza è la password
  mqttclient.subscribe("account/ToCasaNuova" , 1 );                                 // ricevi i messaggi dal canale to.casanuova
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  lcd.clear();

}

void loop() {
  mqttclient.loop();
  leggibottoni();
  previousMillis = millis();
  currentMillis = millis();
  if ((inputL > 0) && (attivo)) {
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(input.substring(0 , 16));
    lcd.setCursor(0, 1);
    lcd.print(input.substring(16 , 32));
    while (currentMillis - previousMillis <= 3000) {
      currentMillis = millis();
      leggibottoni();
      mqttclient.loop();
    }
  }
  leggibottoni();
  mqttclient.loop();
  previousMillis = millis();
  currentMillis = millis();

  if ((inputL > 32) && (attivo)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(input.substring(32 , 48));
    lcd.setCursor(0, 1);
    lcd.print(input.substring(48 , 64));
    while (currentMillis - previousMillis <= 3000) {
      currentMillis = millis();
      leggibottoni();
      mqttclient.loop();
    }
  }
  leggibottoni();
  mqttclient.loop();
  previousMillis = millis();
  currentMillis = millis();
  if ((inputL > 64) && (attivo)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(input.substring(64 , 80));
    lcd.setCursor(0, 1);
    lcd.print(input.substring(80 , 96));
    while (currentMillis - previousMillis <= 3000) {
      currentMillis = millis();
      leggibottoni();
      mqttclient.loop();
    }
  }
  leggibottoni();
  mqttclient.loop();
  previousMillis = millis();
  currentMillis = millis();
  if ((inputL > 96) && (attivo)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(input.substring(96 , 112));
    lcd.setCursor(0, 1);
    lcd.print(input.substring(112 , 128));
    while (currentMillis - previousMillis <= 3000) {
      currentMillis = millis();
      leggibottoni();
      mqttclient.loop();
    }
  }

  if (!mqttclient.connected()) {
    Serial.println("RESET!");
    lcd.noBacklight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RiConnessione");
    digitalWrite(A1, LOW);
    delay(1000);
    digitalWrite(A1, HIGH);
    delay(5000);
    Ethernet.begin(mac, ip, dnsserver, gateway, subnet);
    delay(5000);
    while (!mqttclient.connect("Arduino", "account", "password" ));
    mqttclient.subscribe("account/ToCasaNuova" , 1 );
    lcd.clear();
  }
}

void leggibottoni() {
  if (!(digitalRead(4)) || (!digitalRead(5)) || (!digitalRead(6)) || (!digitalRead(7)) || (!digitalRead(8)) || (!digitalRead(9)) || (!digitalRead(2)) || (!digitalRead(3)) || (!digitalRead(A0))) {
    lcd.noBacklight();
    lcd.clear();
    attivo = false;
    if (!digitalRead(4)) {
      mqttclient.publish ("account/FromCasaNuova" , "Vieni Qua a Pranzo?");                      //alla pressione dei tasti manda i post al canale from.casanuova
      previousMillis = millis();
      currentMillis = millis();
      while (currentMillis - previousMillis <= 500) {
      currentMillis = millis();
      mqttclient.loop();
    }
    }
    if (!digitalRead(5)) {
      mqttclient.publish ("account/FromCasaNuova" , "E' Pronto");                      //alla pressione dei tasti manda i post al canale from.casanuova
      previousMillis = millis();
      currentMillis = millis();
      while (currentMillis - previousMillis <= 500) {
      currentMillis = millis();
      mqttclient.loop();
    }
    }
    if (!digitalRead(6)) {
      mqttclient.publish ("account/FromCasaNuova" , "Si/OK");                      //alla pressione dei tasti manda i post al canale from.casanuova
      previousMillis = millis();
      currentMillis = millis();
      while (currentMillis - previousMillis <= 500) {
      currentMillis = millis();
      mqttclient.loop();
    }
    }
    if (!digitalRead(7)) {
      mqttclient.publish ("account/FromCasaNuova" , "Dove fai Colazione?");                      //alla pressione dei tasti manda i post al canale from.casanuova
      previousMillis = millis();
      currentMillis = millis();
      while (currentMillis - previousMillis <= 500) {
      currentMillis = millis();
      mqttclient.loop();
    }
    }
    if (!digitalRead(8)) {
      mqttclient.publish ("account/FromCasaNuova" , "Prendo Io Il Giornale");                      //alla pressione dei tasti manda i post al canale from.casanuova
      previousMillis = millis();
      currentMillis = millis();
      while (currentMillis - previousMillis <= 500) {
      currentMillis = millis();
      mqttclient.loop();
    }
    }
    if (!digitalRead(9)) {
      mqttclient.publish ("account/FromCasaNuova" , "Arrivo");                      //alla pressione dei tasti manda i post al canale from.casanuova
      previousMillis = millis();
      currentMillis = millis();
      while (currentMillis - previousMillis <= 500) {
      currentMillis = millis();
      mqttclient.loop();
    }
    }
    if (!digitalRead(2)) {
      mqttclient.publish ("account/FromCasaNuova" , "No");                      //alla pressione dei tasti manda i post al canale from.casanuova
      previousMillis = millis();
      currentMillis = millis();
      while (currentMillis - previousMillis <= 500) {
      currentMillis = millis();
      mqttclient.loop();
    }
    }
    if (!digitalRead(3)) {
      mqttclient.publish ("account/FromCasaNuova" , "Potresti Prendere Il Giornale?");                      //alla pressione dei tasti manda i post al canale from.casanuova
      previousMillis = millis();
      currentMillis = millis();
      while (currentMillis - previousMillis <= 500) {
      currentMillis = millis();
      mqttclient.loop();
    }
    }
    if (!digitalRead(A0)) {
      mqttclient.publish ("account/FromCasaNuova" , "Alvise Si e Svegliato!");                      //alla pressione dei tasti manda i post al canale from.casanuova
      previousMillis = millis();
      currentMillis = millis();
      while (currentMillis - previousMillis <= 500) {
      currentMillis = millis();
      mqttclient.loop();
    }
    }
  }
}

