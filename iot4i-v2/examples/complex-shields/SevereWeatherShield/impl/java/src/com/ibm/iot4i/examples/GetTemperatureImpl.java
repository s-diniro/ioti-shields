package com.ibm.iot4i.examples;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.ibm.streams.function.model.Function;
import com.ibm.streams.toolkit.model.ToolkitLibraries;

@ToolkitLibraries("impl/lib/*")
public class GetTemperatureImpl {
	static Logger logger = Logger.getLogger(GetTemperatureImpl.class);

	@Function(namespace = "com.ibm.iot4i.examples", name = "getTemperature", description = "", stateful = false)
	public static int getTemperature(String message) {
		JsonObject jsonMessage = null;
		try {
			jsonMessage = new JsonParser().parse(message).getAsJsonObject();
			logger.log(Level.DEBUG, "Message to check: " + jsonMessage.toString());
			JsonObject data = jsonMessage.getAsJsonObject("data");
			JsonObject observation = data.getAsJsonObject("observation");
			return observation.get("temp").getAsInt();
		} catch (Exception e) {
			logger.log(Level.DEBUG, "get temperature failed, error: " + e.getLocalizedMessage());
			return 0;
		}
	}
}
