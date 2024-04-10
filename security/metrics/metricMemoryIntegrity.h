#pragma once

/*Metric for when our mem is modified*/

class MetricMemoryIntegrity : public Metric {
public:
	MetricTypes GetType();
	Metrics GetIndex();
	void Callback();
};