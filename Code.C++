String ssid     = "Simulator Wifi"; 
String password = ""; 
String host     = "api.thingspeak.com"; 
const int httpPort   = 80;
String uri     = "/update?api_key=3B6C61SKKIZQ19OM&field1=";
int setupESP8266(void) {
  Serial.begin(115200);   
  Serial.println("AT");   
  delay(10);        
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);       
  if (!Serial.find("OK")) return 2;
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);    
  if (!Serial.find("OK")) return 3;
  return 0;
}
void anydata(void) {
  int temp = map(analogRead(A0),20,358,-40,125);
  String httpPacket = "GET " + uri + String(temp) + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); 
  Serial.print(httpPacket);
  delay(10); 
  if (!Serial.find("SEND OK\r\n")) return;
}
void setup() {
  setupESP8266();
}
void loop() {
 anydata();
  delay(10000);
}
