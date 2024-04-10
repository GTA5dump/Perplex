#include "stdafx.h"

MetricTypes MetricMemoryIntegrity::GetType() {
	return METRIC_BANNABLE;
}

Metrics MetricMemoryIntegrity::GetIndex() {
	return METRIC_MEMORY_INTEGRITY;
}

void MetricMemoryIntegrity::Callback() {
	pSecurity.BSOD();
	pUtils.CloseProc();
}