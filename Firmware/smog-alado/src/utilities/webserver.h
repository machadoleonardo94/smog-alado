#ifndef WEBSERVER_SETUP
#define WEBSERVER_SETUP

#include "shared/dependencies.h"

// Assuming these variables are declared in your global variables file
extern double Kp, Ki, Kd, tempGoal, heaterTemperature, powerPercent;
extern bool sleepy, tuning;
extern uint16_t minutes;

// Define the web server host name from constants.h
#define WEB_SERVER_HOST WEB_SERVER_HOST_NAME

void handleRoot(AsyncWebServerRequest *request)
{
  String html = "<html><head><style>";
  html += "body { background-color: #000000; color: #ffffff; }";
  html += "input { background-color: #32b0ac; color: #ffffff; }";
  html += "#toast-container { position: fixed; bottom: 20px; left: 50%; transform: translateX(-50%); background-color: #333; color: #fff; padding: 10px; border-radius: 5px; display: none; z-index: 1000; }";
  html += "</style><script>";

  // Fetch data from the system
  html += "function updateData() {";
  html += "  fetch('/data')";
  html += "    .then(response => response.json())";
  html += "    .then(data => {";
  html += "      document.getElementById('temperature').innerText = 'Current Temperature: ' + data.heaterTemperature.toFixed(2) + ' °C';";
  html += "      document.getElementById('pwmOutput').innerText = 'PWM Output: ' + data.powerPercent.toFixed(2) + '%';";
  html += "      document.getElementById('timeToSleep').innerText = 'Time to Sleep: ' + data.idleMinutes + ':' + data.idleSeconds + ' minutes';";
  html += "      document.getElementById('tuningState').innerText = 'Tuning: ' + (data.tuning ? 'Yes' : 'No');";
  html += "      document.getElementById('tempGoal').innerText = 'Goal Temperature: ' + data.tempGoal.toFixed(2) + ' °C';";
  html += "      document.getElementById('Kp').innerText = 'Kp: ' + data.Kp.toFixed(2);";
  html += "      document.getElementById('Ki').innerText = 'Ki: ' + data.Ki.toFixed(2);";
  html += "      document.getElementById('Kd').innerText = 'Kd: ' + data.Kd.toFixed(2);";
  html += "    });";
  html += "}";
  html += "setInterval(updateData, 400);";

  // Toggle tuning state
  html += "function toggleTuning() {";
  html += "  fetch('/toggle-tuning', {";
  html += "    method: 'POST'";
  html += "  })";
  html += "    .then(response => response.text())";
  html += "    .then(result => {";
  html += "      console.log(result);";
  html += "    });";
  html += "}";

  // Change temperature goal
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

  // Change Kp
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

  // Change Ki
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

  // Change Kd
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

  // Write new PID values to EEPROM
  html += "function commitToEEPROM() {";
  html += "  const newKp = document.getElementById('newKp').value;";
  html += "  const newKi = document.getElementById('newKi').value;";
  html += "  const newKd = document.getElementById('newKd').value;";
  html += "  fetch(`/commit-to-eeprom?newKp=${newKp}&newKi=${newKi}&newKd=${newKd}`, {";
  html += "    method: 'POST'";
  html += "  })";
  html += "  .then(response => response.text())";
  html += "    .then(result => {";
  html += "      console.log(result);";
  html += "      showToast('Values committed to EEPROM successfully');";
  html += "      updateData();";
  html += "    })";
  html += "    .catch(error => {";
  html += "      console.error('Error committing values to EEPROM:', error);";
  html += "      showToast('Failed to commit values to EEPROM');";
  html += "  });";
  html += "}";

  // Function to show a toast message
  html += "function showToast(message) {";
  html += " const toastContainer = document.getElementById('toast-container');";
  html += " const toastMessage = document.getElementById('toast-message');";
  html += " toastMessage.innerText = message;";       // Set the toast message content
  html += " toastContainer.style.display = 'block';"; // Show the toast container
  html += " setTimeout(() => {";                      // Hide the toast after a delay (e.g., 3 seconds)
  html += "   toastContainer.style.display = 'none';";
  html += " }, 3000);";
  html += "}";

  // Reboot the system
  html += "function rebootESP() {";
  html += "  fetch('/reboot-esp', {";
  html += "    method: 'POST'";
  html += "  })";
  html += "  .then(response => response.text())";
  html += "  .then(result => {";
  html += "    console.log(result);";
  html += "    showToast('Now rebooting');";
  html += "  });";
  html += "}";

  // Change the time to sleep
  html += "function changeTimeToSleep() {";
  html += "  const newTimeToSleep = document.getElementById('newTimeToSleep').value;";
  html += "  fetch('/change-time-to-sleep?newTimeToSleep=' + newTimeToSleep, {";
  html += "    method: 'POST'";
  html += "  })";
  html += "    .then(response => response.text())";
  html += "    .then(result => {";
  html += "      showToast(result);";
  html += "      updateData();";
  html += "    });";
  html += "}";

  html += "</script></head><body>";
  html += "<h1>Smog Alado - Controles</h1>";
  html += "<p id='tempGoal'>Temperature Goal: " + String(tempGoal) + " °C</p>";
  html += "<p id='temperature'>Temperature: " + String(heaterTemperature, 2) + " °C</p>";
  html += "<p id='pwmOutput'>PWM Output: " + String(powerPercent, 2) + "%</p>";
  html += "<p id='timeToSleep'>Time to Sleep: " + String(idleMinutes) + " minutes</p>";
  html += "<p id='tuningState'>Tuning: </p>";  // Placeholder for tuning state
  html += "<p id='Kp'>Kp: ${Kp.toFixed(2)} </p>";  // Placeholder for Kp
  html += "<p id='Ki'>Ki: ${Ki.toFixed(2)} </p>";  // Placeholder for Ki
  html += "<p id='Kd'>Kd: ${Kd.toFixed(2)} </p>";  // Placeholder for Kd

  html += "<form>";
  html += "  <label for='toggleTuning'>Auto-tune PID:&nbsp&nbsp&nbsp&nbsp</label>";
  html += "  <button type='button' onclick='toggleTuning();'>Auto-tune</button><br><br>";
  html += "  <label for='newTimeToSleep'>Sleep timer (m) &nbsp:</label>";
  html += "  <input type='text' id='newTimeToSleep' name='newTimeToSleep'>";
  html += "  <button type='button' onclick='changeTimeToSleep();'>Change Time to Sleep</button><br><br>";
  html += "  <label for='newTempGoal'>Set Temperature:</label>";
  html += "  <input type='text' id='newTempGoal' name='newTempGoal'>";
  html += "  <button type='button' onclick='changeTempGoal();'>Change Temp Goal</button><br><br>";
  html += "  <label for='newKp'>Set Kp:&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp</label>";
  html += "  <input type='text' id='newKp' name='newKp'>";
  html += "  <button type='button' onclick='changeKp();'>Change Kp</button><br>";
  html += "  <label for='newKi'>Set Ki:&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp</label>";
  html += "  <input type='text' id='newKi' name='newKi'>";
  html += "  <button type='button' onclick='changeKi();'>Change Ki</button><br>";
  html += "  <label for='newKd'>Set Kd:&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp</label>";
  html += "  <input type='text' id='newKd' name='newKd'>";
  html += "  <button type='button' onclick='changeKd();'>Change Kd</button><br><br>";
  html += "  <button type='button' onclick='commitToEEPROM();'>Commit to EEPROM</button>&nbsp&nbsp";
  html += "  <button type='button' onclick='rebootESP();'>Reboot</button><br>";
  html += "</form>";
  html += "<div id='toast-container'>";
  html += " <div id='toast-message'></div>";
  html += "</div>";
  html += "</body></html>";

  request->send(200, "text/html; charset=utf-8", html);
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
  

  String jsonData;
  serializeJson(jsonDoc, jsonData);

  request->send(200, "application/json", jsonData);
  });

  server.on("/toggle-tuning", HTTP_POST, handleToggleTuning);
  server.on("/change-temp-goal", HTTP_POST, handleChangeTempGoal);
  server.on("/change-kp", HTTP_POST, handleChangeKp);
  server.on("/change-ki", HTTP_POST, handleChangeKi);
  server.on("/change-kd", HTTP_POST, handleChangeKd);
  server.on("/commit-to-eeprom", HTTP_POST, handleCommitToEEPROM);
  server.on("/reboot-esp", HTTP_POST, handleRebootESP);
  server.on("/change-time-to-sleep", HTTP_POST, handleChangeTimeToSleep);

  server.on("/", HTTP_GET, handleRoot);
  server.begin();
}

#endif // WEBSERVER_SETUP