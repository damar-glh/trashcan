#include <ESP8266WiFi.h>
 
const char* ssid = "ya";
const char* password = "87654321";
 
int LED1 = 13; 
int LED2 = 12;
int value1 = LOW;
int value2 = LOW;

WiFiServer server(80);
 
void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;
    if (attempts > 20) {
      Serial.println("\nFailed to connect to WiFi. Please check your credentials.");
      break;
    }
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
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>ESP8266 LED Control</title>");
  client.println("<style>button {padding: 10px 20px; font-size: 18px;}</style>");
  client.println("</head><body>");

  client.println("<fieldset>");
  client.println("<legend><font color='black'>Control LED Via Wifi</font></legend>");
 
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

  client.println("<br><br>");

  // Return the response LED2
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

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}