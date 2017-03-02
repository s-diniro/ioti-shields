(function() {
    var shield = {
        tempMin: -10,
        tempMax: 35,
        id: 8,
        delay: 5000,
        name: 'weatherShield',
        safelet: function(payload) {
            return (payload.weatherData.temperature < shield.tempMin || payload.weatherData.temperature > shield.tempMax);
        },
        entryCondition: function(payload) {
            return payload && payload.weatherData && payload.weatherData.temperature;
        },
        message: function(payload) {
            return constructMessage(payload, shield.id, 'Weather Hazard', 'Temperature outside limits');
        }
    };

    registerShield(shield.id, shield.name, shield.entryCondition, undefined, shield.safelet, shield.message, shield.delay);
})();
