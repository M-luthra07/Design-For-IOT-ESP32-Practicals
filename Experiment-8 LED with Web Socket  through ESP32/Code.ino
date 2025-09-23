#include <WiFi.h> 
#include <AsyncTCP.h> 
#include <ESPAsyncWebServer.h> 
// Replace with your network credentials 
const char* ssid = "Galaxy A23 9112"; 
const char* password = "bhuj4849"; 
bool ledState = 0; 
const int ledPin = 2; 
// Create AsyncWebServer object on port 80 
AsyncWebServer server(80); 
AsyncWebSocket ws("/ws"); 
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP Web Server</title>
  <style>
    body { margin:0; font-family:Arial; text-align:center; }
    .topnav { background:#143642; padding:10px; color:#fff; }
    .content { padding:30px; max-width:600px; margin:auto; }
    .card { background:#F8F7F9; box-shadow:2px 2px 12px rgba(140,140,140,.5); padding:20px; }
    h2 { font-size:1.5rem; color:#143642; }
    .state { font-size:1.5rem; color:#8c8c8c; font-weight:bold; }
    .button { padding:15px 50px; font-size:20px; color:#fff; background:#0f8b8d;
              border:none; border-radius:5px; cursor:pointer; }
    .button:active { transform:translateY(2px); }
  </style>
</head>
<body>
  <div class="topnav"><h1>ESP WebSocket Server</h1></div>
  <div class="content">
    <div class="card">
      <h2>Output - GPIO 2</h2>
      <p class="state">State: <span id="state">%STATE%</span></p>
      <p><button id="button" class="button">Toggle</button></p>
    </div>
  </div>
<script>
  var ws, url = `ws://${location.hostname}/ws`;
  function init(){
    ws = new WebSocket(url);
    ws.onmessage = e => document.getElementById('state').textContent = (e.data=="1"?"ON":"OFF");
    ws.onclose = () => setTimeout(init,2000);
    document.getElementById('button').onclick = ()=> ws.send("toggle");
  }
  window.onload = init;
</script>
</body>
</html>
)rawliteral";
void notifyClients() { 
  ws.textAll(String(ledState)); 
} 
 
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) { 
  AwsFrameInfo *info = (AwsFrameInfo*)arg; 
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) { 
    data[len] = 0; 
    if (strcmp((char*)data, "toggle") == 0) { 
      ledState = !ledState; 
      notifyClients(); 
    } 
  } 
} 
 
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n",
                    client->id(),
                    client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}
void initWebSocket() { 
  ws.onEvent(onEvent); 
  server.addHandler(&ws); 
} 
String processor(const String& var){ 
  Serial.println(var); 
  if(var == "STATE"){ 
    if (ledState){ 
      return "ON"; 
    } 
    else{ 
      return "OFF"; 
    } 
  } 
  return String(); 
} 
void setup(){ 
  Serial.begin(115200); 
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, LOW); 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) { 
    delay(1000); 
    Serial.println("Connecting to WiFi.."); 
  } 
Serial.println(WiFi.localIP()); 
initWebSocket(); 
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){ 
request->send(200, "text/html", index_html, processor); 
}); 
// Start server 
server.begin(); 
} 
void loop() { 
ws.cleanupClients(); 
digitalWrite(ledPin, ledState); 
}