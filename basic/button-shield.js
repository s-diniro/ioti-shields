
var checkPathDefined = function(object, path) {
  var parts = path.split('.');
  for(var i=0;i < parts.length; i++) {
    var part = parts[i];
    object = object[part];
    if (!object) {
      return false;
    }
  }
  return true;
};


var Shield = {
	id: 4/*number!*/,
	name: 'button',
  delay: 5000,
	safelet: function (payload) {
    /*buttonB1
    value == 'released/pressed'*/
    return payload.d.states.buttonB0.value === 'released';
	},

	entryCondition: function (payload) {
	  return checkPathDefined(payload, 'd.states.buttonB0');
  },

  preProcessing: undefined,

	message: function (payload) {
		return constructMessage(
		  payload,
      Shield.id,
      'DemoHazard',
      'A demo shield activated!'
    );
  }
};

registerShield(
  Shield.id,
  Shield.name,
  Shield.entryCondition,
  Shield.preProcessing,
  Shield.safelet,
  Shield.message,
  Shield.delay
);
