#pragma once

/*Metric for when a functin in the integrity db is modified*/

class MetricFunctionIntegrity : public Metric {
public:
	MetricTypes GetType();
	Metrics GetIndex();
	void Callback();
};