package com.ibm.iot4i.examples;

import org.apache.log4j.Logger;

import com.ibm.streams.operator.OperatorContext;
import com.ibm.streams.operator.Tuple;
import com.ibm.streams.operator.TupleAttribute;
import com.ibm.streams.operator.model.InputPortSet;
import com.ibm.streams.operator.model.InputPortSet.WindowMode;
import com.ibm.streams.operator.model.InputPorts;
import com.ibm.streams.operator.model.OutputPortSet;
import com.ibm.streams.operator.model.OutputPorts;
import com.ibm.streams.operator.model.Parameter;
import com.ibm.streams.operator.model.PrimitiveOperator;
import com.ibm.streams.operator.window.AbstractWindowOperator;
import com.ibm.streams.operator.window.StreamWindowPartitioner;

@PrimitiveOperator(name = "SevereWeatherOp", namespace = "com.ibm.iot4i.examples", description = "Java Operator SevereWeatherOp")
@InputPorts({
		@InputPortSet(description = "Port that ingests tuples", cardinality = 1, windowingMode = WindowMode.Windowed) })
@OutputPorts({ @OutputPortSet(description = "Port that produces tuples", cardinality = 1) })
public class SevereWeatherOp extends AbstractWindowOperator {

	private TupleAttribute<Tuple, String> partitionBy;

	// Optional parameter threshold
	@Parameter
	public void setPartitionBy(TupleAttribute<Tuple, String> partitionBy) {
		this.partitionBy = partitionBy;
	}

	public TupleAttribute<Tuple, String> getPartitionBy() {
		return partitionBy;
	}

	@SuppressWarnings({ "rawtypes", "resource", "unchecked" })
	@Override
	public synchronized void initialize(OperatorContext context) throws Exception {
		super.initialize(context);
		Logger.getLogger(this.getClass()).trace("Operator " + context.getName() + " initializing in PE: "
				+ context.getPE().getPEId() + " in Job: " + context.getPE().getJobId());

		StreamWindowPartitioner<Tuple, TupleAttribute<Tuple, String>> streamWindowPartitioner = null;
		getInput(0).getStreamWindow().registerPartitioner(streamWindowPartitioner);

		new SevereWeatherWindowListener(getInput(0).getStreamWindow(), getOutput(0));
	}
}
