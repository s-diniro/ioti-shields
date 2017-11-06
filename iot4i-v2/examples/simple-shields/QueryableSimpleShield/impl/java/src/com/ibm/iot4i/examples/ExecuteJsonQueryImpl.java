package com.ibm.iot4i.examples;

import java.time.Instant;
import java.util.Base64;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.ibm.streams.function.model.Function;
import com.ibm.streams.toolkit.model.ToolkitLibraries;
import com.jayway.jsonpath.Configuration;
import com.jayway.jsonpath.JsonPath;
import com.jayway.jsonpath.Option;

@ToolkitLibraries("impl/lib/*")
public class ExecuteJsonQueryImpl {

	static Configuration conf = Configuration.defaultConfiguration().addOptions(Option.AS_PATH_LIST)
			.addOptions(Option.ALWAYS_RETURN_LIST).addOptions(Option.SUPPRESS_EXCEPTIONS);

	static Logger logger = Logger.getLogger(ExecuteJsonQueryImpl.class);
	
	static Map<String, Long> timePeriodCache = new HashMap<>();
	static Map<String, Boolean> stateCache = new HashMap<>();

	@Function(namespace = "com.ibm.iot4i.examples", name = "executeJsonQuery", description = "", stateful = false)
	public static boolean executeJsonQuery(String message, String[] jsonQueries, String operatorName, String _timePeriod, String _needResetState, String eventTimeKey) {
		try {
			int timePeriod = Integer.parseInt(_timePeriod);
			boolean needResetState = Boolean.parseBoolean(_needResetState);
			JsonObject messageJson = new JsonParser().parse(message).getAsJsonObject();
			String rawEvent = messageJson.getAsJsonObject("event").toString();
			logger.log(Level.WARN, operatorName + ": Incoming event: " + rawEvent);
			Object parsedRawEvent = conf.jsonProvider().parse(rawEvent);

			for (String jsonQuery : jsonQueries) {
				// check if the query is encoded
				if (!jsonQuery.startsWith("$")) {
					try {
						byte[] decodedQueryBytes = Base64.getDecoder().decode(jsonQuery);
						jsonQuery = new String(decodedQueryBytes);
					} catch (Exception e) {
						e.printStackTrace();
						logger.log(Level.ERROR,
								operatorName + ": Decoding base 64 string failed: " + e.getLocalizedMessage());
						return false;
					}
				}

				String vendorId = messageJson.get("vendorId").getAsString();				
				logger.log(Level.WARN, operatorName + ": Json query: " + jsonQuery);
				List<Object> results = JsonPath.read(parsedRawEvent, jsonQuery);
				
				boolean timeDidPass = false;
				Long eventTime = null;
				if (timePeriod > 0) {
					List<String> eventTimeElement = JsonPath.read(parsedRawEvent, eventTimeKey);					
					if (!eventTimeElement.isEmpty()) {
						boolean isNumber = eventTimeElement.get(0).chars().allMatch(Character::isDigit);
						if (isNumber) {
							eventTime = Long.parseLong(eventTimeElement.get(0));
						} else {
							eventTime = Instant.parse(eventTimeElement.get(0)).getEpochSecond();		
						}									
					} else {
						eventTime = Instant.parse(messageJson.get("arrivedAtMH").getAsString()).getEpochSecond();
					}
					timeDidPass = eventTime - timePeriodCache.get(vendorId) > timePeriod;
				}
						
				boolean stateChanged = needResetState && stateCache.get(vendorId) != results.isEmpty();
				
				if (!results.isEmpty() && (timeDidPass || stateChanged)) {
					logger.log(Level.WARN, operatorName + ": Event passed json query, results: " + results);
					timePeriodCache.put(vendorId, eventTime);
					stateCache.put(vendorId, true);
					return true;
				}
				stateCache.remove(vendorId);				
			}

			logger.log(Level.WARN, operatorName + ": Event failed json query");
			return false;
		} catch (Exception e) {
			e.printStackTrace();
			logger.log(Level.WARN, operatorName + ": Executing json query failed, error: " + e.getMessage());
			return false;
		}
	}

}
