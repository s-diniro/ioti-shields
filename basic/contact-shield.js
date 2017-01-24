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
  id: 5 /*must be a number*/,
  name: 'contact-shield',
  delay: 5000,
  safelet: function (payload) {
    /*value == 'closed/open'*/
    return payload.d.states.contact.value === 'open';
  },

  entryCondition: function (payload) {
    return checkPathDefined(payload, 'd.states.contact');
  },

  preProcessing: undefined,

  message: function (payload) {
    return constructMessage(
      payload,
      Shield.id,
      'ContactHazard',
      'Something is open!'
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
