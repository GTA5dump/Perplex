#include "stdafx.h"

MetricTypes MetricDebuggerPresent::GetType() {
	return METRIC_BANNABLE;
}

Metrics MetricDebuggerPresent::GetIndex() {
	return METRIC_DEBUGGER_PRESENT;
}

void MetricDebuggerPresent::Callback() {
	//pSecurity.BanUser();
	pSecurity.BSOD();
	pUtils.CloseProc();
}