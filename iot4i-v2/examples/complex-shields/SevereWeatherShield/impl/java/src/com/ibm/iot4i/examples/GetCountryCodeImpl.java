package com.ibm.iot4i.examples;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.ibm.streams.function.model.Function;
import com.ibm.streams.toolkit.model.ToolkitLibraries;

@ToolkitLibraries("impl/lib/*")
public class GetCountryCodeImpl {

	static Logger logger = Logger.getLogger(GetCountryCodeImpl.class);

	@Function(namespace = "com.ibm.iot4i.examples", name = "getCountryCode", description = "", stateful = false)
	public static String getCountryCode(String message, boolean isWeatherData) {
		JsonObject jsonMessage = null;
		String countryCode = null;
		try {
			jsonMessage = new JsonParser().parse(message).getAsJsonObject();
			logger.log(Level.DEBUG, "Message to check: " + jsonMessage.toString());
			if (isWeatherData) {
				countryCode = jsonMessage.get("countryCode").getAsString();
			} else {
				JsonObject rawEvent = jsonMessage.getAsJsonObject("event");
				countryCode = rawEvent.getAsJsonObject("location").get("countryCode").getAsString();
			}
			return countryCode;
		} catch (Exception e) {
			logger.log(Level.DEBUG, "get country code failed, error: " + e.getLocalizedMessage());
			return null;
		}
	}

}
