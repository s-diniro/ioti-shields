package com.ibm.iot4i.examples;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.ibm.streams.function.model.Function;
import com.ibm.streams.toolkit.model.ToolkitLibraries;

@ToolkitLibraries("impl/lib/*")
public class EventEntryConditionImpl {

	static Logger logger = Logger.getLogger(EventEntryConditionImpl.class);

	@Function(namespace = "com.ibm.iot4i.examples", name = "eventEntryCondition", description = "", stateful = false)
	public static boolean eventEntryCondition(String message) {
		JsonObject jsonMessage = null;
		try {
			jsonMessage = new JsonParser().parse(message).getAsJsonObject();
			logger.log(Level.DEBUG, "Message to check: " + jsonMessage.toString());
			JsonObject rawEvent = jsonMessage.getAsJsonObject("event");
			return (rawEvent.get("location") != null && rawEvent.getAsJsonObject("location").get("geoPoint") != null
					&& rawEvent.getAsJsonObject("location").getAsJsonObject("geoPoint").get("longitude") != null
					&& rawEvent.getAsJsonObject("location").getAsJsonObject("geoPoint").get("latitude") != null
					&& rawEvent.get("traitStates") != null
					&& rawEvent.getAsJsonObject("traitStates").get("traitStates") != null
					&& rawEvent.getAsJsonObject("traitStates").getAsJsonObject("traitStates")
							.get("ContactSense") != null
					&& rawEvent.getAsJsonObject("traitStates").getAsJsonObject("traitStates")
							.getAsJsonObject("ContactSense").get("contactDetected") != null);
		} catch (Exception e) {
			logger.log(Level.WARN, "event entry condition check failed, error: " + e.getLocalizedMessage());
			return false;
		}
	}

}
