#pragma once

enum Metrics {
	METRIC_NULL,
	METRIC_DEBUGGER_PRESENT,
	METRIC_FUNCTION_INTEGRITY,
	METRIC_MEMORY_INTEGRITY
};

enum MetricTypes {
	METRIC_NULL_,
	METRIC_WARNING,
	METRIC_BANNABLE,
};

class Metric {
public:
	virtual void Callback();
	virtual MetricTypes GetType();
	virtual Metrics GetIndex();
};

void ProcessMetric(Metric* pMetric);