#include <SPI.h>
#include <Ethernet.h>


#define ALARMSOUNDER 12

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};


// initialize the library instance:
EthernetClient client;

char server[] = "188.226.156.119";
char server2[] = "78.46.193.102";


unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 5*1000;  // delay between updates, in milliseconds

void setup() {
  // start serial port:
  Serial.begin(9600);
  // give the ethernet module time to boot up:
  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  
  
  pinMode(ALARMSOUNDER, OUTPUT); 
  

}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  if (client.available()) {
//    char c = client.read();
//    Serial.print(c);

      siren(5);
  }

  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }

  // if you're not connected, and ten seconds have passed since
  // your last connection, then connect again and send data:
  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    httpRequest();
  }
  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println("GET / HTTP/1.1");
    client.println("Host: 188.226.156.119");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println("disconnecting.");
    client.stop();
  }
}

void siren(int serverPin)
{
  
  int i = 0; 
  
  for(i = 0; i < 255; i = i + 2)
  {
      
      analogWrite(serverPin, i);      
      analogWrite(ALARMSOUNDER, i);
      delay(10);
  }
  for(i = 255; i > 1; i = i - 2)
  {
      analogWrite(serverPin, i);
      analogWrite(ALARMSOUNDER, i);
      delay(5);
  }
  for(i = 1; i <= 10; i++)
  {
      analogWrite(serverPin, 255);
      analogWrite(ALARMSOUNDER, 200);
      delay(100);
      analogWrite(serverPin, 0);
      analogWrite(ALARMSOUNDER, 25);
      delay(100);
  }
  
  
  
}




