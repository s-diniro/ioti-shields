package com.ibm.iot4i.examples;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.ibm.streams.function.model.Function;
import com.ibm.streams.toolkit.model.ToolkitLibraries;

@ToolkitLibraries("impl/lib/*")
public class GetZipCodePolygonImpl {

	static Logger logger = Logger.getLogger(GetZipCodePolygonImpl.class);

	@Function(namespace = "com.ibm.iot4i.examples", name = "getZipCodePolygon", description = "", stateful = false)
	public static String getZipCodePolygon(String message) {
		JsonObject jsonMessage = null;
		try {
			jsonMessage = new JsonParser().parse(message).getAsJsonObject();
			logger.log(Level.DEBUG, "Message to check: " + jsonMessage.toString());
			return jsonMessage.get("polygon").getAsString();
		} catch (Exception e) {
			logger.log(Level.DEBUG, "get polygon failed, error: " + e.getLocalizedMessage());
			return null;
		}
	}

}
