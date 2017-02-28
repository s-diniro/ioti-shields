const tempMin = -10;
const tempMax = 35;
const weatherShieldID = 8;
const weatherShieldName = 'weatherShield';

var weatherShieldSafelet = function(payload) {
    return (payload.weatherData.temperature < tempMin || payload.weatherData.temperature > tempMax);
};

var weatherShieldEntryCondition = function(payload) {
    return payload && payload.weatherData && payload.weatherData.temperature;
};

var weatherShieldMessage = function(payload) {
    return (constructMessage(payload, weatherShieldName, 'Weather Hazard', 'Temperature outside limits'));
};

var weatherShield = function(payload) {
    var shield = getShieldByName(weatherShieldName);
    return (commonShield(payload, shield));
};

registerShield(weatherShieldID, weatherShieldName, weatherShieldEntryCondition, undefined, weatherShieldSafelet, weatherShieldMessage, 5000);
