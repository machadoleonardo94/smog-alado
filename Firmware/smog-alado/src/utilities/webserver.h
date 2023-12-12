#ifndef WEBSERVER_SETUP
#define WEBSERVER_SETUP

#include "shared/dependencies.h"

// Assuming these variables are declared in your global variables file
extern double Kp, Ki, Kd, tempGoal, heaterTemperature, powerPercent;
extern bool sleepy, tuning;
extern uint16_t minutes, maxAutoTuneDurationMinutes;
extern char timeStr[20];

void handleFile(AsyncWebServerRequest *request, const char *filename) 
{
  File file = LittleFS.open(filename, "r");

  if (file) {
    String content;
    while (file.available()) {
      content += char(file.read());
    }
    file.close();

    // Determine MIME type based on file extension
    String mimeType = "text/plain";
    if (String(filename).endsWith(".html")) {
      mimeType = "text/html";
    } else if (String(filename).endsWith(".css")) {
      mimeType = "text/css";
    } else if (String(filename).endsWith(".js")) {
      mimeType = "application/javascript";
    }
    // Add more conditions for other file types as needed

    // Send the response with the determined MIME type
    request->send(200, mimeType.c_str(), content);
  } 
  else 
  {
    String errorMessage = "Error: File not found - " + String(filename);
    TelnetStream.println(errorMessage);
    request->send(404, "text/html", errorMessage);
  }
} 

void handleHTML(AsyncWebServerRequest *request) 
{
  handleFile(request, "/index.html");
}

void handleJS(AsyncWebServerRequest *request) 
{
  handleFile(request, "/scripts.js");
}

void handleCSS(AsyncWebServerRequest *request) 
{
  handleFile(request, "/styles.css");
}

void handleToggleTuning(AsyncWebServerRequest *request)
{
  changeAutoTune();  // Toggle the tuning state
  request->send(200, "text/plain", "Tuning state toggled");
}

void handleChangeTempGoal(AsyncWebServerRequest *request)
{
  if (request->hasParam("newTempGoal"))
  {
    tempGoal = request->getParam("newTempGoal")->value().toDouble();
    TelnetStream.println("Temperature goal changed successfully");
    request->send(200, "text/plain", "Temperature goal changed successfully");
  }
  else
  {
    TelnetStream.println("Missing parameter: newTempGoal");
    request->send(400, "text/plain", "Invalid request");
  }
}

// Function to change Kp
void handleChangeKp(AsyncWebServerRequest *request)
{
  if (request->hasParam("newKp"))
  {
    Kp = request->getParam("newKp")->value().toDouble();
    myPID.SetTunings(Kp, Ki, Kd);  // Update PID controller with new Kp
    TelnetStream.println("Kp changed successfully");
    request->send(200, "text/plain", "Kp changed successfully");
  }
  else
  {
    TelnetStream.println("Missing parameter: newKp");
    request->send(400, "text/plain", "Invalid request");
  }
}

// Function to change Ki
void handleChangeKi(AsyncWebServerRequest *request)
{
  if (request->hasParam("newKi"))
  {
    Ki = request->getParam("newKi")->value().toDouble();
    myPID.SetTunings(Kp, Ki, Kd);  // Update PID controller with new Ki
    TelnetStream.println("Ki changed successfully");
    request->send(200, "text/plain", "Ki changed successfully");
  }
  else
  {
    TelnetStream.println("Missing parameter: newKi");
    request->send(400, "text/plain", "Invalid request");
  }
}

// Function to change Kd
void handleChangeKd(AsyncWebServerRequest *request)
{
  if (request->hasParam("newKd"))
  {
    Kd = request->getParam("newKd")->value().toDouble();
    myPID.SetTunings(Kp, Ki, Kd);  // Update PID controller with new Kd
    TelnetStream.println("Kd changed successfully");
    request->send(200, "text/plain", "Kd changed successfully");
  }
  else
  {
    TelnetStream.println("Missing parameter: newKd");
    request->send(400, "text/plain", "Invalid request");
  }
}

// Function to save PID parameters to EEPROM
void handleCommitToEEPROM(AsyncWebServerRequest *request)
{
  if (request->hasParam("newKp") && request->hasParam("newKi") && request->hasParam("newKd"))
  {
    Kp = request->getParam("newKp")->value().toDouble();
    Ki = request->getParam("newKi")->value().toDouble();
    Kd = request->getParam("newKd")->value().toDouble();

    // Update PID controller with new values
    myPID.SetTunings(Kp, Ki, Kd);

    // Store new values in EEPROM
    EEPROM.put(EEPROM_KP_ADDRESS, Kp);
    EEPROM.put(EEPROM_KI_ADDRESS, Ki);
    EEPROM.put(EEPROM_KD_ADDRESS, Kd);
    EEPROM.commit();

    TelnetStream.println("PID parameters committed to EEPROM successfully");
    request->send(200, "text/plain", "PID parameters committed to EEPROM successfully");
  }
  else
  {
    TelnetStream.println("Missing parameters for PID values");
    request->send(400, "text/plain", "Invalid request");
  }
}

// Function to change the time to sleep
void handleChangeTimeToSleep(AsyncWebServerRequest *request)
{
  if (request->hasParam("newTimeToSleep"))
  {
    const int newTimeToSleep = request->getParam("newTimeToSleep")->value().toInt();
    minutes = newTimeToSleep;
    idleTimer = 0;
    TelnetStream.println("Time to sleep changed successfully");
    request->send(200, "text/plain", "Time to sleep changed successfully");
  }
  else
  {
    TelnetStream.println("Missing parameter: newTimeToSleep");
    request->send(400, "text/plain", "Invalid request");
  }
}

void handleRebootESP(AsyncWebServerRequest *request)
{
  TelnetStream.println("Rebooting ESP...");
  request->send(200, "text/plain", "Rebooting ESP...");

  // Delay for a short time to allow the response to be sent
  delay(1000);

  // Perform the reboot
  ESP.restart();
}

void handleChangeMaxAutoTuneDuration(AsyncWebServerRequest *request) {
  if (request->hasParam("newMaxAutoTuneDuration")) {
    const int newMaxAutoTuneDuration = request->getParam("newMaxAutoTuneDuration")->value().toInt();
    maxAutoTuneDurationMinutes = newMaxAutoTuneDuration;
    TelnetStream.println("Max Auto Tune Duration changed successfully");
    request->send(200, "text/plain", "Max Auto Tune Duration changed successfully");
  } else {
    TelnetStream.println("Missing parameter: newMaxAutoTuneDuration");
    request->send(400, "text/plain", "Invalid request");
  }
}

// Initialize the web server
void setupWebServer()
{
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
    DynamicJsonDocument jsonDoc(256);
    jsonDoc["heaterTemperature"] = heaterTemperature;
    jsonDoc["tempGoal"] = tempGoal;
    jsonDoc["powerPercent"] = powerPercent;
    jsonDoc["idleMinutes"] = idleMinutes;
    jsonDoc["idleSeconds"] = idleSeconds;
    jsonDoc["sleepy"] = sleepy;
    jsonDoc["tuning"] = tuning;
    jsonDoc["Kp"] = Kp;
    jsonDoc["Ki"] = Ki;
    jsonDoc["Kd"] = Kd;
    jsonDoc["timeStr"] = timeStr;

    String jsonData;
    serializeJson(jsonDoc, jsonData);

    request->send(200, "application/json", jsonData);
  });

  server.on("/", HTTP_GET, handleHTML);
  server.on("/scripts.js", HTTP_GET, handleJS);
  server.on("/styles.css", HTTP_GET, handleCSS);

  server.on("/toggle-tuning", HTTP_POST, handleToggleTuning);
  server.on("/change-temp-goal", HTTP_POST, handleChangeTempGoal);
  server.on("/change-kp", HTTP_POST, handleChangeKp);
  server.on("/change-ki", HTTP_POST, handleChangeKi);
  server.on("/change-kd", HTTP_POST, handleChangeKd);
  server.on("/commit-to-eeprom", HTTP_POST, handleCommitToEEPROM);
  server.on("/reboot-esp", HTTP_POST, handleRebootESP);
  server.on("/change-time-to-sleep", HTTP_POST, handleChangeTimeToSleep);
  server.on("/change-max-auto-tune-duration", HTTP_POST, handleChangeMaxAutoTuneDuration);

  server.begin();
}

#endif // WEBSERVER_SETUP
