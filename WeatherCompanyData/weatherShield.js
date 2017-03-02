const TEMP_MIN = -10;
const TEMP_MAX = 35;
const WEATHER_SHIELD_UUID = 8;
const WEATHER_SHIELD_NAME = 'weatherShield';
const WEATHER_SHIELD_DELAY = 5000;

var weatherShieldSafelet = function(payload) {
    return (payload.weatherData.temperature < TEMP_MIN || payload.weatherData.temperature > TEMP_MAX);
};

var weatherShieldEntryCondition = function(payload) {
    return payload && payload.weatherData && payload.weatherData.temperature;
};

var weatherShieldMessage = function(payload) {
    return (constructMessage(payload, WEATHER_SHIELD_UUID, 'Weather Hazard', 'Temperature outside limits'));
};

var weatherShield = function(payload) {
    var shield = getShieldByName(WEATHER_SHIELD_NAME);
    return (commonShield(payload, shield));
};

registerShield(WEATHER_SHIELD_UUID, WEATHER_SHIELD_NAME, weatherShieldEntryCondition, undefined, weatherShieldSafelet, weatherShieldMessage, WEATHER_SHIELD_DELAY);
