package com.ibm.iot4i.examples;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.ibm.streams.function.model.Function;
import com.ibm.streams.toolkit.model.ToolkitLibraries;

@ToolkitLibraries("impl/lib/*")
public class GetLongitudeImpl {

	static Logger logger = Logger.getLogger(GetLongitudeImpl.class);

	@Function(namespace = "com.ibm.iot4i.examples", name = "getLongitude", description = "", stateful = false)
	public static double getLongitude(String message) {
		JsonObject jsonMessage = null;
		try {
			jsonMessage = new JsonParser().parse(message).getAsJsonObject();
			logger.log(Level.DEBUG, "Message to check: " + jsonMessage.toString());
			JsonObject rawEvent = jsonMessage.getAsJsonObject("event");
			return rawEvent.getAsJsonObject("location").getAsJsonObject("geoPoint").get("longitude").getAsDouble();
		} catch (Exception e) {
			logger.log(Level.DEBUG, "get Longitude failed, error: " + e.getLocalizedMessage());
			return 0;
		}
	}

}
