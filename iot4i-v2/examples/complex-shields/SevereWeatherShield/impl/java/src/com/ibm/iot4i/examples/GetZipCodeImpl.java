package com.ibm.iot4i.examples;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.ibm.streams.function.model.Function;
import com.ibm.streams.toolkit.model.ToolkitLibraries;

@ToolkitLibraries("impl/lib/*")
public class GetZipCodeImpl {

	static Logger logger = Logger.getLogger(GetZipCodeImpl.class);

	@Function(namespace = "com.ibm.iot4i.examples", name = "getZipCode", description = "", stateful = false)
	public static String getZipCode(String message, boolean isWeatherData) {
		JsonObject jsonMessage = null;
		String zipCode = null;
		try {
			jsonMessage = new JsonParser().parse(message).getAsJsonObject();
			logger.log(Level.DEBUG, "Message to check: " + jsonMessage.toString());
			if (isWeatherData) {
				zipCode = jsonMessage.get("zipCode").getAsString();
			} else {
				JsonObject rawEvent = jsonMessage.getAsJsonObject("event");
				zipCode = rawEvent.getAsJsonObject("location").get("zipCode").getAsString();
			}
			return zipCode;
		} catch (Exception e) {
			logger.log(Level.DEBUG, "get zip code failed, error: " + e.getLocalizedMessage());
			return null;
		}
	}

}
