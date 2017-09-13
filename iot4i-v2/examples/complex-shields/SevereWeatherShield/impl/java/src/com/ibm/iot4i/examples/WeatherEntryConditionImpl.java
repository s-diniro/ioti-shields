package com.ibm.iot4i.examples;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.ibm.streams.function.model.Function;

public class WeatherEntryConditionImpl {

	static Logger logger = Logger.getLogger(EventEntryConditionImpl.class);

	@Function(namespace = "com.ibm.iot4i.examples", name = "weatherEntryCondition", description = "", stateful = false)
	public static boolean weatherEntryCondition(String message) {
		JsonObject jsonMessage = null;
		try {
			jsonMessage = new JsonParser().parse(message).getAsJsonObject();
			logger.log(Level.DEBUG, "Message to check: " + jsonMessage.toString());
			return (jsonMessage.get("data") != null && jsonMessage.get("zipCode") != null
					&& jsonMessage.get("countryCode") != null
					&& jsonMessage.getAsJsonObject("data").get("observation") != null);
		} catch (Exception e) {
			logger.log(Level.WARN, "weather entry condition check failed, error: " + e.getLocalizedMessage());
			return false;
		}
	}

}
