#include <ESP8266WiFi.h>
 
const char* ssid = "ya";
const char* password = "87654321";
 
int LED1 = 13; //D7 on ESP Board
int LED2 = 12; //D6 on ESP Board
int LED3 = 14; //D5 on ESP Board
int LED4 = 2;  //D4 on ESP Board
  int value1 = LOW;
  int value2 = LOW;
  int value3 = LOW;
  int value4 = LOW;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
          
// Set LED according to the request
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<fieldset>");
  client.println("<font color = redq>");
  client.print("Control 4 LED Via Wifi");
  client.println("</font>");
  client.println("</fieldset>");
  client.println("<br><br>");
 
 // Return the response LED1
  client.print("LED1 is now: ");
  // Control LED 1
  if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(LED1, HIGH);
    value1 = HIGH;
    }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(LED1, LOW);
    value1 = LOW;
     }
     if(value1==HIGH){client.print("ON");}
     if(value1==LOW){client.print("OFF");}
    
  client.println("<br><br>");
  client.println("<a href=\"/LED1=ON\"\"><button>LED1 ON </button></a>");
  client.println("<a href=\"/LED1=OFF\"\"><button>LED1 OFF </button></a><br />");  
  client.println("</html>");

 // Return the response LED2
 client.println("<br><br>");
 client.print("LED2 is now: ");
  // Control LED 2
  if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(LED2, HIGH);
    value2 = HIGH;
    }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(LED2, LOW);
    value2 = LOW;
    }
    if(value2==HIGH){client.print("ON");}
     if(value2==LOW){client.print("OFF");}
   
  client.println("<br><br>");
  client.println("<a href=\"/LED2=ON\"\"><button>LED2 ON </button></a>");
  client.println("<a href=\"/LED2=OFF\"\"><button>LED2 OFF </button></a><br />");  
  client.println("</html>");
 
  // Return the response LED3
  client.println("<br><br>");
  client.print("LED3 is now: ");
  // Control LED 3
  if (request.indexOf("/LED3=ON") != -1)  {
    digitalWrite(LED3, HIGH);
    value3 = HIGH;
    }
  if (request.indexOf("/LED3=OFF") != -1)  {
    digitalWrite(LED3, LOW);
    value3 = LOW;
    }
    if(value3==HIGH){client.print("ON");}
     if(value3==LOW){client.print("OFF");}
    
  client.println("<br><br>");
  client.println("<a href=\"/LED3=ON\"\"><button>LED3 ON </button></a>");
  client.println("<a href=\"/LED3=OFF\"\"><button>LED3 OFF </button></a><br />");  
  client.println("</html>");
 
  // Return the response LED4
  client.println("<br><br>");
  client.print("LED4 is now: ");
  // Control LED 4
  if (request.indexOf("/LED4=ON") != -1)  {
    digitalWrite(LED4, HIGH);
    value4 = HIGH;
    } 
  if (request.indexOf("/LED4=OFF") != -1)  {
    digitalWrite(LED4, LOW);
    value4 = LOW;
    }
    if(value4==HIGH){client.print("ON");}
     if(value4==LOW){client.print("OFF");}
     
  client.println("<br><br>");
  client.println("<a href=\"/LED4=ON\"\"><button>LED4 ON </button></a>");
  client.println("<a href=\"/LED4=OFF\"\"><button>LED4 OFF </button></a><br />");  
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}