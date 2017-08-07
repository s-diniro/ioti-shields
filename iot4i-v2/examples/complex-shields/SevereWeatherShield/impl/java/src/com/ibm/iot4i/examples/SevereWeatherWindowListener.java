package com.ibm.iot4i.examples;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

import com.ibm.json.java.JSONObject;
import com.ibm.streams.operator.OutputTuple;
import com.ibm.streams.operator.StreamingData;
import com.ibm.streams.operator.StreamingOutput;
import com.ibm.streams.operator.Tuple;
import com.ibm.streams.operator.state.Checkpoint;
import com.ibm.streams.operator.types.RString;
import com.ibm.streams.operator.window.StatefulWindowListener;
import com.ibm.streams.operator.window.StreamWindow;
import com.ibm.streams.operator.window.StreamWindowEvent;
import com.ibm.streams.operator.window.WindowUtilities;

public class SevereWeatherWindowListener<T> extends StatefulWindowListener<SevereWeatherWindowListener.State, Tuple> {

	Logger logger = Logger.getLogger(SevereWeatherWindowListener.class.getName());
	protected final StreamingOutput<OutputTuple> outputPort;

	protected SevereWeatherWindowListener(StreamWindow<Tuple> window, StreamingOutput<OutputTuple> outputPort) {
		super(window);
		this.outputPort = outputPort;
		WindowUtilities.registerAttributePartitioner((StreamWindow<Tuple>) window, "userId");
	}

	public static class State {

		public boolean isOutHome = false;
		public boolean isHazard = false;
		public ArrayList<RString> hazardTuples = new ArrayList<>();
		public long doorOpenTs;

		@Override
		public String toString() {
			return "State [isOutHome=" + isOutHome + ", isHazard=" + isHazard + ", hazardtuples=" + hazardTuples + "]";
		}

	}

	@Override
	public void checkpoint(Checkpoint checkpoint) throws Exception {
		super.checkpoint(checkpoint);
	}

	private void cleanState(State state) {
		state.hazardTuples.clear();
		state.isHazard = false;
		state.isOutHome = false;
		state.doorOpenTs = 0;
	}

	@Override
	public void handleEvent(StreamWindowEvent<Tuple> event) throws Exception {
		State state = getPartitionState(event.getPartition());
		logger.log(Level.WARNING, "Event Type:" + event.getType());
		switch (event.getType()) {
		case INSERTION:
			logger.log(Level.WARNING, "insert: state before is " + state.toString());
			for (Tuple tuple : event.getTuples()) {
				JSONObject key = JSONObject.parse(tuple.getString("key"));
				JSONObject message = JSONObject.parse(tuple.getString("message"));
				String userId = tuple.getString("userId");
				logger.log(Level.WARNING, "insert: evt: " + message.toString());
				logger.log(Level.WARNING, "insert: key: " + key.toString());

				checkPattern(state, key, message, userId);
			}
			logger.log(Level.WARNING, "insert: state after is " + state.toString());
			break;
		case EVICTION:
			logger.log(Level.WARNING, "evict: state before is " + state.toString());
			// evict only if event is door open
			for (Tuple tuple : event.getTuples()) {
				JSONObject message = JSONObject.parse(tuple.getString("message"));
				JSONObject evt = JSONObject.parse(message.get("event").toString());

				logger.log(Level.WARNING, "evict: evt: " + evt.toString());
				if (evt.get("isDoorOpen") != null) {
					cleanState(state);
				}
			}
			logger.log(Level.WARNING, "evict: state after is " + state.toString());
			break;
		case TRIGGER:
			break;
		default:
			break;
		}
	}

	private void checkPattern(State state, JSONObject key, JSONObject message, String userId) throws Exception {
		JSONObject evt = JSONObject.parse(message.get("event").toString());
		SimpleDateFormat dateParser = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSSX");
		long eventTimestamp = dateParser.parse(key.get("timestamp").toString()).getTime();
		if (evt.get("isDoorOpen") != null && Boolean.valueOf(evt.get("isDoorOpen").toString()) == true) {
			state.isOutHome = true;
			state.hazardTuples.add(new RString(message.toString()));
			state.doorOpenTs = eventTimestamp;
		} else if (state.isOutHome == true && evt.get("temperature") != null) {
			if (Integer.valueOf(evt.get("temperature").toString()) > 42 && eventTimestamp > state.doorOpenTs) {
				state.isHazard = true;
				state.hazardTuples.add(new RString(message.toString()));
				submitOutput(state, userId);
				cleanState(state);
			}
		} else {
			cleanState(state);
		}
	}

	@Override
	protected State getInitializedState(Object partition, State state) {
		return new State();
	}

	protected void submitOutput(State state, String userId) throws Exception {

		OutputTuple tuple = outputPort.newTuple();
		setupOutputTuple(tuple, state, userId);

		outputPort.submit(tuple);
		outputPort.punctuate(StreamingData.Punctuation.WINDOW_MARKER);
	}

	protected void setupOutputTuple(OutputTuple tuple, State state, String userId) {
		if (state.isHazard) {
			tuple.setString("actionParams",
					"{\"hazardTitle\":\"Severe Weather Detected\",\"emailSubject\":\"Alert from IoT for Insurance\",\"emailText\":\"Hello IoT for Insurance user. You have a hazard!!!\" }");
			tuple.setObject("rawEvents", state.hazardTuples);
			tuple.setString("userId", userId);
		} else {
			tuple.setBoolean("isHazard", false);
		}
	}

}
