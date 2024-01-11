function updateData() {
  fetch('/data')
    .then(response => response.json())
    .then(data => {
      // Update your UI with the data
      document.getElementById('temperature').innerText = 'Current Temperature: ' + data.heaterTemperature.toFixed(2) + ' °C';
      document.getElementById('pwmOutput').innerText = 'PWM Output: ' + data.powerPercent.toFixed(2) + '%';
      document.getElementById('timeToSleep').innerText = 'Time to Sleep: ' + data.idleMinutes + ':' + data.idleSeconds + ' minutes';
      document.getElementById('tuningState').innerText = 'Tuning: ' + (data.tuning ? 'Yes' : 'No');
      document.getElementById('tempGoal').innerText = 'Goal Temperature: ' + data.tempGoal.toFixed(2) + ' °C';
      document.getElementById('Kp').innerText = 'Kp: ' + data.Kp.toFixed(2);
      document.getElementById('Ki').innerText = 'Ki: ' + data.Ki.toFixed(2);
      document.getElementById('Kd').innerText = 'Kd: ' + data.Kd.toFixed(2);
      document.getElementById('timeStr').innerText = 'Current Time: ' + data.timeStr;

      setTimeout(updateData, 400);
    })
    .catch(error => {
      // Handle errors, log or display an error message
      console.error('Error fetching data:', error);

      // Schedule the next update even in case of an error
      setTimeout(updateData, 400);
    });
}

// Start the initial update
updateData();

function toggleTuning() {
  fetch('/toggle-tuning', {
    method: 'POST'
  })
    .then(response => response.text())
    .then(result => {
      console.log(result);
    });
}

function changeTempGoal() {
  const newTempGoal = document.getElementById('newTempGoal').value;
  fetch('/change-temp-goal?newTempGoal=' + newTempGoal, {
    method: 'POST'
  })
    .then(response => response.text())
    .then(result => {
      console.log(result);
      updateData();
    });
}

function changeKp() {
  const newKp = document.getElementById('newKp').value;
  fetch('/change-kp?newKp=' + newKp, {
    method: 'POST'
  })
    .then(response => response.text())
    .then(result => {
      console.log(result);
      updateData();
    });
}

function changeKi() {
  const newKi = document.getElementById('newKi').value;
  fetch('/change-ki?newKi=' + newKi, {
    method: 'POST'
  })
    .then(response => response.text())
    .then(result => {
      console.log(result);
      updateData();
    });
}

function changeKd() {
  const newKd = document.getElementById('newKd').value;
  fetch('/change-kd?newKd=' + newKd, {
    method: 'POST'
  })
    .then(response => response.text())
    .then(result => {
      console.log(result);
      updateData();
    });
}

function commitToEEPROM() {
  const newKp = document.getElementById('newKp').value;
  const newKi = document.getElementById('newKi').value;
  const newKd = document.getElementById('newKd').value;
  fetch(`/commit-to-eeprom?newKp=${newKp}&newKi=${newKi}&newKd=${newKd}`, {
    method: 'POST'
  })
    .then(response => response.text())
    .then(result => {
      console.log(result);
      showToast('Values committed to EEPROM successfully');
      updateData();
    })
    .catch(error => {
      console.error('Error committing values to EEPROM:', error);
      showToast('Failed to commit values to EEPROM');
    });
}

function showToast(message) {
  const toastContainer = document.getElementById('toast-container');
  const toastMessage = document.getElementById('toast-message');
  toastMessage.innerText = message;
  toastContainer.style.display = 'block';
  setTimeout(() => {
    toastContainer.style.display = 'none';
  }, 3000);
}

function rebootESP() {
  fetch('/reboot-esp', {
    method: 'POST'
  })
    .then(response => response.text())
    .then(result => {
      console.log(result);
      showToast('Now rebooting');
    });
}

function changeTimeToSleep() {
  const newTimeToSleep = document.getElementById('newTimeToSleep').value;
  fetch('/change-time-to-sleep?newTimeToSleep=' + newTimeToSleep, {
    method: 'POST'
  })
    .then(response => response.text())
    .then(result => {
      showToast(result);
      updateData();
    });
}

function changeMaxAutoTuneDuration() {
  const newMaxAutoTuneDuration = document.getElementById('newMaxAutoTuneDuration').value;
  fetch('/change-max-auto-tune-duration?newMaxAutoTuneDuration=' + newMaxAutoTuneDuration, {
    method: 'POST'
  })
    .then(response => response.text())
    .then(result => {
      showToast(result);
    });
}