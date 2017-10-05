package com.ibm.iot4i.examples;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.wololo.geojson.Feature;
import org.wololo.geojson.GeoJSONFactory;
import org.wololo.jts2geojson.GeoJSONReader;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.ibm.streams.function.model.Function;
import com.ibm.streams.toolkit.model.ToolkitLibraries;
import com.vividsolutions.jts.geom.Geometry;

@ToolkitLibraries("impl/lib/*")
public class GetLocationAsWKTImpl {

	static Logger logger = Logger.getLogger(GetLocationAsWKTImpl.class);

	@Function(namespace = "com.ibm.iot4i.examples", name = "getLocationAsWKT", description = "", stateful = false)
	public static String getLocationAsWKT(String message, boolean isSensorEvent) {
		String locationAsWKT = null;
		try {
			JsonObject jsonMessage = null;
			jsonMessage = new JsonParser().parse(message).getAsJsonObject();
			logger.log(Level.WARN, "Location to check: " + jsonMessage.toString());
			Feature feature = (Feature) GeoJSONFactory.create(jsonMessage.get("location").getAsJsonObject().toString());
			GeoJSONReader reader = new GeoJSONReader();
			Geometry geometry = reader.read(feature.getGeometry());
			locationAsWKT = geometry.toString();
		} catch (Exception e) {
			e.printStackTrace();
			logger.log(Level.WARN, "get location as wkt failed, error: " + e.getLocalizedMessage());
		}

		return locationAsWKT;
	}

}
