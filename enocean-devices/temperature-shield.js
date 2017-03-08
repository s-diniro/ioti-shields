(function () {
  var shieldUuid = 99999;
  var shieldName = 'temperature-shield';
  var hazardTitle = 'Its too hot!';

  var delay = 5000;
  var preProcessing = undefined;

  function safelet(payload) {
    return (payload.d.states.temperature.value > 23);
  }

  function entryCondition(payload) {
    return (payload.d && payload.d.states && (payload.d.states.temperature !== undefined));
  }

  function message(payload) {
    var hazardUuid = shieldName + '_' + Date.now();
    return (constructMessage(payload, shieldUuid, hazardUuid, hazardTitle));
  }

  registerShield(shieldUuid, shieldName, entryCondition, preProcessing, safelet, message, delay);
})();