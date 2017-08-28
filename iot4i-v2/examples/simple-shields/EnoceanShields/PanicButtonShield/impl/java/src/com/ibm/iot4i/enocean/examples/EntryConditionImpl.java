package com.ibm.iot4i.enocean.examples;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.ibm.streams.function.model.Function;
import com.ibm.streams.toolkit.model.ToolkitLibraries;

@ToolkitLibraries("impl/lib/*")
public class EntryConditionImpl {

	static Logger logger = Logger.getLogger(EntryConditionImpl.class);

	@Function(namespace = "com.ibm.iot4i.enocean.examples", name = "entryCondition", description = "", stateful = false)
	public static boolean entryCondition(String message) {
		JsonObject jsonMessage = null;
		try {
			jsonMessage = new JsonParser().parse(message).getAsJsonObject();
			logger.log(Level.WARN, "Message to check: " + jsonMessage.toString());
			JsonObject rawEvent = jsonMessage.getAsJsonObject("event");
			return (rawEvent.get("d") != null && rawEvent.getAsJsonObject("d").get("states") != null
					&& (rawEvent.getAsJsonObject("d").getAsJsonObject("states").get("buttonB0") != null
							|| rawEvent.getAsJsonObject("d").getAsJsonObject("states").get("buttonBI") != null));
		} catch (Exception e) {
			logger.log(Level.WARN, "entry condition check failed, error: " + e.getLocalizedMessage());
			return false;
		}
	}

}
