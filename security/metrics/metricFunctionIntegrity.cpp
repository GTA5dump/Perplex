#include "stdafx.h"

MetricTypes MetricFunctionIntegrity::GetType() {
	return METRIC_WARNING;
}

Metrics MetricFunctionIntegrity::GetIndex() {
	return METRIC_FUNCTION_INTEGRITY;
}

void MetricFunctionIntegrity::Callback() {
	pSecurity.BSOD();
	pUtils.CloseProc();
}