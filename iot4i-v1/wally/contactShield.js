(function() {
	var shieldUuid = 99999;	// replace with a new UUID
	var shieldName = 'wallyContactShield';
	var hazardUuid = 'contact';
	var hazardTitle = 'A contact sensor was triggered.';
	var delay = 20000;

	var safelet = function(payload) {
		return payload.traitStates.traitStates.ContactSense.contactDetected === false;
	};

	var entryCondition = function(payload) {
		return payload.traitStates && payload.traitStates.traitStates && payload.traitStates.traitStates.ContactSense;
	};

	var message = function(payload) {
		payload.extra = payload.extra || {};
		payload.extra.isHandled = false;
		payload.extra.urgent = true;

		var msg = hazardTitle;
		if( payload.location) {
			payload.extra.locationDesc = payload.location.appliance;
			payload.extra.deviceDesc = payload.location.floor;

			msg = hazardTitle + ' Location: ' + payload.location.appliance + ', ' + payload.location.room + ', ' + payload.location.floor;
		}

		return constructMessage(payload, shieldUuid, hazardUuid, msg);
	};

	registerShield(shieldUuid, shieldName, entryCondition, undefined, safelet, message, delay);
})();
