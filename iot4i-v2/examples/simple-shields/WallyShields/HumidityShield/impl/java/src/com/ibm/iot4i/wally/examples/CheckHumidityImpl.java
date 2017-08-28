package com.ibm.iot4i.wally.examples;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.ibm.streams.function.model.Function;
import com.ibm.streams.toolkit.model.ToolkitLibraries;

@ToolkitLibraries("impl/lib/*")
public class CheckHumidityImpl {

	static Logger logger = Logger.getLogger(CheckHumidityImpl.class);

	@Function(namespace = "com.ibm.iot4i.wally.examples", name = "checkHumidity", description = "", stateful = false)
	public static boolean checkWaterLeakage(String message) {
		JsonObject jsonMessage = null;
		try {
			jsonMessage = new JsonParser().parse(message).getAsJsonObject();
			logger.log(Level.DEBUG, "Message to check: " + jsonMessage.toString());
			JsonObject rawEvent = jsonMessage.getAsJsonObject("event");
			logger.log(Level.DEBUG, "Event to check: " + rawEvent.toString());

			boolean isHazard = rawEvent.getAsJsonObject("traitStates").getAsJsonObject("traitStates")
					.getAsJsonObject("Humidity").get("humidityPct").getAsInt() > 75;

			logger.log(Level.DEBUG, "isHazard  : " + isHazard);
			return isHazard;
		} catch (Exception e) {
			logger.log(Level.DEBUG, "check humidity failed, error: " + e.getLocalizedMessage());
			return false;
		}
	}

}
