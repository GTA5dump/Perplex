#pragma once

/*Metric for when debugger is detected*/

class MetricDebuggerPresent : public Metric {
public:
	MetricTypes GetType();
	Metrics GetIndex();
	void Callback();
};