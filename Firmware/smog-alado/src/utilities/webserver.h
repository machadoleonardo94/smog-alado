#ifndef WEBSERVER_SETUP
#define WEBSERVER_SETUP

#include "shared/dependencies.h"

// Assuming these variables are declared in your global variables file
extern double Kp, Ki, Kd, tempGoal, heaterTemperature, powerPercent;
extern bool sleepy, tuning;

// Define the web server host name from constants.h
#define WEB_SERVER_HOST WEB_SERVER_HOST_NAME

void handleRoot(AsyncWebServerRequest *request)
{
  String html = "<html><head><style>";
  html += "body { background-color: #000000; color: #ffffff; }";
  html += "input { background-color: #32b0ac; color: #ffffff; }";
  html += "</style><script>";

  // Fetch data from system
  html += "function updateData() {";
  html += "  fetch('/data')";
  html += "    .then(response => response.json())";
  html += "    .then(data => {";
  html += "      document.getElementById('temperature').innerText = 'Current Temperature: ' + data.heaterTemperature.toFixed(2) + ' °C';";
  html += "      document.getElementById('pwmOutput').innerText = 'PWM Output: ' + data.powerPercent.toFixed(2) + '%';";
  html += "      document.getElementById('timeToSleep').innerText = 'Time to Sleep: ' + (Math.round((data.timeToSleep - data.idleTimer) / 60)) + ' minutes';";
  html += "      document.getElementById('tuningState').innerText = 'Tuning: ' + (data.tuning ? 'Yes' : 'No');";
  html += "      document.getElementById('tempGoal').innerText = 'Goal Temperature: ' + data.tempGoal.toFixed(2) + ' °C';";
  html += "      document.getElementById('Kp').innerText = 'Kp: ' + data.Kp.toFixed(2);";
  html += "      document.getElementById('Ki').innerText = 'Ki: ' + data.Ki.toFixed(2);";
  html += "      document.getElementById('Kd').innerText = 'Kd: ' + data.Kd.toFixed(2);";
  html += "    });";
  html += "}";
  html += "setInterval(updateData, 400);";

  // Function to toggle tuning state
  html += "function toggleTuning() {";
  html += "  fetch('/toggle-tuning', {";
  html += "    method: 'POST'";
  html += "  })";
  html += "    .then(response => response.text())";
  html += "    .then(result => {";
  html += "      console.log(result);";
  html += "    });";
  html += "}";

  // Function to change temperature goal
  html += "function changeTempGoal() {";
  html += "  const newTempGoal = document.getElementById('newTempGoal').value;";
  html += "  fetch('/change-temp-goal?newTempGoal=' + newTempGoal, {";
  html += "    method: 'POST'";
  html += "  })";
  html += "    .then(response => response.text())";
  html += "    .then(result => {";
  html += "      console.log(result);";
  html += "      updateData();";  // Refresh data after changing tempGoal
  html += "    });";
  html += "}";

  // Function to change Kp
  html += "function changeKp() {";
  html += "  const newKp = document.getElementById('newKp').value;";
  html += "  fetch('/change-kp?newKp=' + newKp, {";
  html += "    method: 'POST'";
  html += "  })";
  html += "    .then(response => response.text())";
  html += "    .then(result => {";
  html += "      console.log(result);";
  html += "      updateData();";  // Refresh data after changing Kp
  html += "    });";
  html += "}";

  // Function to change Ki
  html += "function changeKi() {";
  html += "  const newKi = document.getElementById('newKi').value;";
  html += "  fetch('/change-ki?newKi=' + newKi, {";
  html += "    method: 'POST'";
  html += "  })";
  html += "    .then(response => response.text())";
  html += "    .then(result => {";
  html += "      console.log(result);";
  html += "      updateData();";  // Refresh data after changing Ki
  html += "    });";
  html += "}";

  // Function to change Kd
  html += "function changeKd() {";
  html += "  const newKd = document.getElementById('newKd').value;";
  html += "  fetch('/change-kd?newKd=' + newKd, {";
  html += "    method: 'POST'";
  html += "  })";
  html += "    .then(response => response.text())";
  html += "    .then(result => {";
  html += "      console.log(result);";
  html += "      updateData();";  // Refresh data after changing Kd
  html += "    });";
  html += "}";

  html += "</script></head><body>";
  html += "<h1>Smog Alado - Controles</h1>";
  html += "<p id='tempGoal'>Temperature Goal: " + String(tempGoal) + " °C</p>";
  html += "<p id='temperature'>Temperature: " + String(heaterTemperature, 2) + " °C</p>";
  html += "<p id='pwmOutput'>PWM Output: " + String(powerPercent, 2) + "%</p>";
  html += "<p id='timeToSleep'>Time to Sleep: " + String(TIME_TO_SLEEP - idleTimer) + " seconds</p>";
  html += "<p id='tuningState'>Tuning: </p>";  // Placeholder for tuning state
  html += "<p id='Kp'>Kp: </p>";  // Placeholder for Kp
  html += "<p id='Ki'>Ki: </p>";  // Placeholder for Ki
  html += "<p id='Kd'>Kd: </p>";  // Placeholder for Kd
  html += "<form>";
  html += "  <label for='toggleTuning'>Auto-tune PID:</label>";
  html += "  <button type='button' onclick='toggleTuning();'>Auto-tune</button><br>";
  html += "  <label for='newTempGoal'>Set Temperature:</label>";
  html += "  <input type='text' id='newTempGoal' name='newTempGoal'>";
  html += "  <button type='button' onclick='changeTempGoal();'>Change Temp Goal</button><br>";
  html += "  <label for='newKp'>Set Kp:</label>";
  html += "  <input type='text' id='newKp' name='newKp'>";
  html += "  <button type='button' onclick='changeKp();'>Change Kp</button><br>";
  html += "  <label for='newKi'>Set Ki:</label>";
  html += "  <input type='text' id='newKi' name='newKi'>";
  html += "  <button type='button' onclick='changeKi();'>Change Ki</button><br>";
  html += "  <label for='newKd'>Set Kd:</label>";
  html += "  <input type='text' id='newKd' name='newKd'>";
  html += "  <button type='button' onclick='changeKd();'>Change Kd</button><br>";
  html += "</form>";
  html += "</body></html>";

  request->send(200, "text/html; charset=utf-8", html);
}

void handleToggleTuning(AsyncWebServerRequest *request)
{
  tuning = !tuning;  // Toggle the tuning state
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

// Initialize the web server
void setupWebServer()
{
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
  DynamicJsonDocument jsonDoc(256);
  jsonDoc["heaterTemperature"] = heaterTemperature;
  jsonDoc["tempGoal"] = tempGoal;
  jsonDoc["powerPercent"] = powerPercent;
  jsonDoc["timeToSleep"] = TIME_TO_SLEEP - idleTimer;
  jsonDoc["sleepy"] = sleepy;
  jsonDoc["tuning"] = tuning;
  jsonDoc["Kp"] = Kp;
  jsonDoc["Ki"] = Ki;
  jsonDoc["Kd"] = Kd;
  

  String jsonData;
  serializeJson(jsonDoc, jsonData);

  request->send(200, "application/json", jsonData);
  });

  server.on("/toggle-tuning", HTTP_POST, handleToggleTuning);
  server.on("/change-temp-goal", HTTP_POST, handleChangeTempGoal);
  server.on("/change-kp", HTTP_POST, handleChangeKp);
  server.on("/change-ki", HTTP_POST, handleChangeKi);
  server.on("/change-kd", HTTP_POST, handleChangeKd);

  server.on("/", HTTP_GET, handleRoot);
  server.begin();
}

#endif // WEBSERVER_SETUP