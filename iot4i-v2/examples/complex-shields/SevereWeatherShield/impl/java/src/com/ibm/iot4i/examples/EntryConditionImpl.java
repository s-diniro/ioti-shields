package com.ibm.iot4i.examples;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import com.ibm.json.java.JSONObject;
import com.ibm.streams.function.model.Function;

public class EntryConditionImpl {

	static Logger logger = Logger.getLogger(EntryConditionImpl.class);

	@Function(namespace = "com.ibm.iot4i.examples", name = "entryCondition", description = "", stateful = false)
	public static boolean entryCondition(String message) {
		JSONObject jsonMessage = null;
		try {
			jsonMessage = JSONObject.parse(message);
			logger.log(Level.WARN, "Message to check: " + jsonMessage.toString());
			JSONObject rawEvent = JSONObject.parse(jsonMessage.get("event").toString());
			return (rawEvent.get("isDoorOpen") != null) || (rawEvent.get("temperature") != null);
		} catch (Exception e) {
			logger.log(Level.WARN, "entry condition check failed, error: " + e.getLocalizedMessage());
			return false;
		}
	}

}
