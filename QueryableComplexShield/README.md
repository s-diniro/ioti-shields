# Queryable complex shield

This shield shows how to join two data streams together to support more complex use cases. The shield is also using simple Json queries to filter streams events. The json queries are based on [JsonPath](https://github.com/json-path/JsonPath). To test your json queries, you can use this [website](http://jsonpath.herokuapp.com/). There, you could simply put the event data coming from the sensor in a json format and run the json queries against it.  

## How shield works

The shield has two IBM streams operators as explained below:

1. A [Filter operator](https://www.ibm.com/support/knowledgecenter/en/SSCRJU_4.2.1/com.ibm.streams.toolkits.doc/spldoc/dita/tk$spl/op$spl.relational$Filter.html) at the beginning of each data stream to filter the events based on the shield logic.
2. A [Join operator](https://www.ibm.com/support/knowledgecenter/en/SSCRJU_4.2.1/com.ibm.streams.toolkits.doc/spldoc/dita/tk$spl/op$spl.relational$Join.html) which is a power operator that allows you to correlate events from two streams that are based on user-specified match predicates and window configurations. This operator is used in this shield to join, and partition the two streams based on event's userId. 

The events in both streams are filtered using json queries as an input which is executed using a helper java function [executeJsonQuery(message, query)](./impl/java/src/com/ibm/iot4i/examples/ExecuteJsonQueryImpl.java).

The main shield code is [here](./com.ibm.iot4i.examples/QueryableComplexShield.spl)

![Queryable Complex Shield](./images/queryable-complex-shield.png)

## Using shield

This shield expects the following parameters:

- **stream1EntryConditionJsonQueries** : the json queries used to provide an entry condition to filter events that doesn't belong to this shield.
- **stream2EntryConditionJsonQueries** : the json queries used to provide the main shield logic
- **stream1SlidingWindowInSeconds** : the Time-based eviction policy time in seconds for the first stream. For more information, check IBM streams sliding windows [here](https://developer.ibm.com/streamsdev/2014/08/22/spl-sliding-windows-explained/).
- **actionParams** : the params needed by the external action, example is shown below:

```json
{
   "hazardTitle":"A hazard was detected.",
   "emailSubject":"Alert from IoT for Insurance",
   "emailText":"Hello IoT for Insurance user. You have a hazard!!!"
}

 ```


These parameters needs to be provided when submitting/updating the shield code using the [createShieldCode API](https://ioti.us-south.containers.mybluemix.net/docs/#!/shield-codes/createShieldCode) or [updateShieldCode API](https://ioti.us-south.containers.mybluemix.net/docs/#!/shield-codes/updateShieldCode). The parameters are provided as part of the **jobOptions** field like:
 
 ```json
{
   "jobOptions":{
      "stream1EntryConditionJsonQueries": ["", ""],
      "stream2EntryConditionJsonQueries": ["", ""],
      "stream1SlidingWindowInSeconds": 30,
      "actionParams": ""
   }
}
 
 ```

## Examples

Here are some examples of what this shield can do. 

### Severe temperature Shield 

The use case for this shield is that it finds out if a house physical window is opened and after some time a severe temperature is detected. The contact sensor events will be in the first stream and temperature events will be in the second stream. The shield will join both streams based on userId and generate a hazard. The time the shield waits after the contact sensor event arrived to check for severe temperature event is configured using the "stream1SlidingWindowInSeconds" parameter.

In this example shield we are using wally contact and temperature sensors. 

**Wally Contact Sensor Event Payload** :

 ```json
{
   "deviceType":"Wally",
   "id":"2fd2a0b6-e38d-4dda-a315-db51860362aa",
   "snid":"90-7a-f1-00-51-d6-bf-a6",
   "gatewayId":"someVendorId",
   "type":"SENSOR",
   "hwType":8,
   "location":{
      "room":"Utility",
      "floor":"Basement",
      "appliance":"Utility Room"
   },
   "data_type":"EVENT",
   "traitStates":{
      "traitStates":{ 
        "ContactSense":{
            "traitType":"contactSenseTrait",
            "updated":"2017-09-06T00:51:41.325Z",
            "contactDetected":true
         }
      }
   }
}

```

**Wally Temperature Sensor Event Payload** :

 ```json
{
   "deviceType":"Wally",
   "id":"2fd2a0b6-e38d-4dda-a315-db51860362aa",
   "snid":"90-7a-f1-00-51-d6-bf-a6",
   "gatewayId":"someVendorId",
   "type":"SENSOR",
   "hwType":8,
   "location":{
      "room":"Utility",
      "floor":"Basement",
      "appliance":"Utility Room"
   },
   "data_type":"EVENT",
   "traitStates":{
      "traitStates":{
         "Temperature":{
            "traitType":"temperatureTrait",
            "updated":"2017-09-22T19:02:12.086Z",
            "temperatureC": 44
         }
      }
   }
}

```


In this case, the shield **jobOptions** will be like:     

 ```json
{
   "jobOptions":{
      "stream1EntryConditionJsonQueries":[
         "$.traitStates.traitStates[?(@.Temperature.temperatureC > 42)]"
      ],
      "stream2EntryConditionJsonQueries":[
         "$.traitStates.traitStates[?(@.ContactSense.contactDetected == true )]"
      ],
      "stream1SlidingWindowInSeconds": 30,
      "actionParams":{
         "hazardTitle":"A severe temperature was detected !",
         "emailSubject":"Alert from IoT for Insurance",
         "emailText":"Hello IoT for Insurance user. You have a hazard!!!"
      }
   }
}

```