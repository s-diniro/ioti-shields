### Transformer Job


This job listens to all raw events from the sensors, then annotate the events with user information.

 ![alt text](./images/TransformerJob.png "Transformer Job")
 
 
 
 This job uses the following java primitive operator:
 
  [TransformerOp](./impl/java/src/com/ibm/iot4i/transformerjob/TransformerOp.java):
  A java primitive operator to annotated raw events with user information. This operator adds also unique eventIds to the raw events. The operator accepts the following input params:
  
  `deviceIdAttributeNames`:  The name of the attribute in the event payload that contains the physical device Id. The operator will check by default the deviceId of the IoTP topic, if not deviceId is found, it will search in the payload based on the attribute name provided here.
  
  The operator requires also `apiURL`, `apiToken`, and `tenantId` but this will be provided by the IoT4i API when the job is submitted.
  