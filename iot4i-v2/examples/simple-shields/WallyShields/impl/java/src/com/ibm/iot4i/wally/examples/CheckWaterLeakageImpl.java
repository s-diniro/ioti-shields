package com.ibm.iot4i.wally.examples;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.ibm.streams.function.model.Function;
import com.ibm.streams.toolkit.model.ToolkitLibraries;

@ToolkitLibraries("impl/lib/*")
public class CheckWaterLeakageImpl {

	static Logger logger = Logger.getLogger(CheckWaterLeakageImpl.class);

	@Function(namespace = "com.ibm.iot4i.wally.examples", name = "checkWaterLeakage", description = "", stateful = false)
	public static boolean checkWaterLeakage(String message) {
		JsonObject jsonMessage = null;
		try {
			jsonMessage = new JsonParser().parse(message).getAsJsonObject();
			logger.log(Level.WARN, "Message to check: " + jsonMessage.toString());
			JsonObject rawEvent = jsonMessage.getAsJsonObject("event");
			logger.log(Level.WARN, "Event to check: " + rawEvent.toString());

			boolean isWaterLeakage = rawEvent.getAsJsonObject("traitStates").getAsJsonObject("traitStates")
					.getAsJsonObject("WaterSense").get("waterPresent").getAsBoolean() == true;

			logger.log(Level.WARN, "isWaterLeakage  : " + isWaterLeakage);
			return isWaterLeakage;
		} catch (Exception e) {
			logger.log(Level.WARN, "check water leakage failed, error: " + e.getLocalizedMessage());
			return false;
		}
	}

}
