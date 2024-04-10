#include "stdafx.h"

EntityControl pEntityControl;

void EntityControl::Update() {
	if (!m_requests.empty()) {
		EntityControlStruct& request = m_requests.front();
		bool exists = DoesEntityExist(request.m_entity);
		if (!request.m_valid) m_requests.pop();
		if (exists && (NetworkHasControlOfEntity(request.m_entity) || request.m_tries > 25)) {
			if (request.m_tries < 25) {
				LOG_DEV("Received control of entity %d after %d tries", request.m_entity, request.m_tries);
				request.m_function(request.m_entity);
				request.m_valid = false;
			} else LOG_DEV("Failed to get control of entity %d", request.m_entity);
			m_requests.pop();
		} else if (exists) {
			request.m_tries++;
			NetworkRequestControlOfEntity(request.m_entity);
			if (request.m_networkID != 0) {
				NetworkRequestControlOfNetworkId(request.m_networkID);
				SetNetworkIdCanMigrate(request.m_networkID, 1);
			}
		} else {
			request.m_valid = false;
			LOG_DEV("Entity %d no longer exists", request.m_entity);
			m_requests.pop();
		}
	}
	for (EntityModelStruct& model : m_models) {
		if (HasModelLoaded(model.m_model) || model.m_tries > 25) {
			if (model.m_tries < 25) {
				model.m_function(model.m_model);
				SetModelAsNoLongerNeeded(model.m_model);
			}
			m_models.erase(remove(m_models.begin(), m_models.end(), model), m_models.end());
		} else {
			model.m_tries++;
			::RequestModel(model.m_model);
		}
	}
}

void EntityControl::SimpleRequestControl(int entity) {
	int tries = 0;
	while (DoesEntityExist(entity) && !NetworkHasControlOfEntity(entity) && tries < 25 && NetworkIsSessionActive()) {
		NetworkRequestControlOfEntity(entity);
		if (NetworkIsSessionStarted()) {
			NetworkRequestControlOfNetworkId(NetworkGetNetworkIdFromEntity(entity));
			SetNetworkIdCanMigrate(NetworkGetNetworkIdFromEntity(entity), 1);
		}

		pFiber.GoToMainFiber();
		tries++;
	}
}

void EntityControl::SimpleRequestModel(int model) {
	int tries = 0;
	while (!STREAMING::HasModelLoaded(model) && tries < 25) {
		STREAMING::RequestModel(model);
		tries++;
		pFiber.GoToMainFiber();
	}
}

void EntityControl::RequestControl(Entity entity, function<void(Entity)> funcptr) {
	static int64_t c_ID;
	int networkID = NetworkIsSessionStarted() ? NetworkGetNetworkIdFromEntity(entity) : 0;
	m_requests.push({ entity, funcptr, networkID, 0, c_ID++, true });
}

void EntityControl::RequestModel(DWORD model, function<void(Hash)> funcptr) {
	static int64_t c_ID;
	m_models.push_back({ model, funcptr, 0, c_ID++ });
}
