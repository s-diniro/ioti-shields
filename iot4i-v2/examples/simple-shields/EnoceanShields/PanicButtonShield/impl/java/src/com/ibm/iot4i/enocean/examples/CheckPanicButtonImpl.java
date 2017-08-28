package com.ibm.iot4i.enocean.examples;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.ibm.streams.function.model.Function;
import com.ibm.streams.toolkit.model.ToolkitLibraries;

@ToolkitLibraries("impl/lib/*")
public class CheckPanicButtonImpl {

	static Logger logger = Logger.getLogger(CheckPanicButtonImpl.class);

	@Function(namespace = "com.ibm.iot4i.enocean.examples", name = "checkPanicButton", description = "", stateful = false)
	public static boolean checkPanicButtonPressed(String message) {
		JsonObject jsonMessage = null;
		try {
			jsonMessage = new JsonParser().parse(message).getAsJsonObject();
			logger.log(Level.WARN, "Message to check: " + jsonMessage.toString());
			JsonObject rawEvent = jsonMessage.getAsJsonObject("event");
			logger.log(Level.WARN, "Event to check: " + rawEvent.toString());

			boolean isButtonPressed = (rawEvent.getAsJsonObject("d").getAsJsonObject("states").get("buttonB0") != null
					&& rawEvent.getAsJsonObject("d").getAsJsonObject("states").getAsJsonObject("buttonB0").get("value")
							.toString().equals("released"))
					|| (rawEvent.getAsJsonObject("d").getAsJsonObject("states").get("buttonBI") != null
							&& rawEvent.getAsJsonObject("d").getAsJsonObject("states").getAsJsonObject("buttonBI")
									.get("value").getAsString().equals("released"));

			logger.log(Level.WARN, "isButtonPressed  : " + isButtonPressed);
			return isButtonPressed;
		} catch (Exception e) {
			logger.log(Level.WARN, "check shield pattern failed, error: " + e.getLocalizedMessage());
			return false;
		}
	}

}
