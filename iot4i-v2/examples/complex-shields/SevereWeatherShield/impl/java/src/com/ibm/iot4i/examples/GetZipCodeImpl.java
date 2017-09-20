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
	public static String getZipCode(String message) {
		JsonObject jsonMessage = null;
		try {
			jsonMessage = new JsonParser().parse(message).getAsJsonObject();
			logger.log(Level.DEBUG, "Message to check: " + jsonMessage.toString());
			return jsonMessage.get("location").getAsJsonObject().getAsJsonObject("properties").get("zipCode")
					.getAsString();
		} catch (Exception e) {
			logger.log(Level.DEBUG, "get zipCode failed, error: " + e.getLocalizedMessage());
			return null;
		}
	}

}
