#include "stdafx.h"

MetricTypes Metric::GetType() { return METRIC_NULL_; }
Metrics Metric::GetIndex() { return METRIC_NULL; }
void Metric::Callback() {}

void ProcessMetric(Metric* pMetric) {
	LOG_PUBLIC("Processing metric %i"_Protect, pMetric->GetIndex());
	if (!pRequests.ServerCommandReportMetric(pMetric)) {
		Sleep(5000);
		pUtils.CloseProc();
		return;
	}

	pMetric->Callback();
}