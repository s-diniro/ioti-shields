
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
    return payload.d && payload.d.states && payload.d.states.buttonB0 !== undefined;
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
