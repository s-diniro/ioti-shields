### Severe Weather Shield

This shield can be used for elderly care. The shield generate hazard when the elderly is out of home (identified using a contact sensor in the door) and after some predefined period of time, a severe weather condition was discovered (like high temperature).

The main spl code of this shield is [here](./com.ibm.iot4i.examples/SevereWeatherShield.spl).

This shield follows the [shield template](../../../shield-templates).

The only difference from the shield template is the shield specific operator which is shown below:

```
//  Shield Specific Operators goes here
		@view(name = "Hazards", port = HazardStream, sampleSize = 5, bufferSize = 50)
		@parallel(width = 1)
		(stream<Hazard> HazardStream) as shield = SevereWeatherOp(ValidatedStream)
		{
			window
				ValidatedStream : sliding, time(30), partitioned ;
			param
				partitionBy : userId ;
		}
```

The above operator is based on a [windowed java operator "SevereWeatherWindowListener"](./impl/java/src/com/ibm/iot4i/examples/SevereWeatherWindowListener.java). This operator partition events by userId to create sub-windows based on userIds. The door open events will trigger the window, then if a severe weather event is detected during the window time (currently set to 30seconds), a hazard will be generated.


Additionally this shield uses an [EntryCondition](./impl/java/src/com/ibm/iot4i/examples/EntryConditionImpl.java) function to filter the events at the beginning of the shield as shown below:

```
//  filter events based on entry condition
		@view(name = "FilteredEvents", port = FilteredStream, sampleSize = 5,
			bufferSize = 50)
		@parallel(width = 1)
		(stream<rstring userId, rstring key, rstring message> FilteredStream) as
			filter = Filter(SourceStream)
		{
			param
				filter : entryCondition(message) ;
		}
```
 