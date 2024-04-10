#include "stdafx.h"

void nativeCallContext::setVectorResults() {
	for (uint32_t i = 0; i < m_dataCount; i++) {
		m_script_vectors[i]->x = m_vector_results[i].x;
		m_script_vectors[i]->y = m_vector_results[i].y;
		m_script_vectors[i]->z = m_vector_results[i].z;
	}
	m_dataCount = 0;
}

bool Invoker::call(uint64_t hash, NativeContext* cxt) {
	auto handler = pNatives.GetNativeHandlerCache(hash);
	if (handler != nullptr) {
		static void* exceptionAddress;
		__try
		{
			handler(cxt);
		}
		__except (exceptionAddress = (GetExceptionInformation())->ExceptionRecord->ExceptionAddress, EXCEPTION_EXECUTE_HANDLER)
		{

		}

		return true;
	}
	return false;
}