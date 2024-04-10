#pragma once

struct EntityControlStruct {
	Entity m_entity;
	function<void(Entity)> m_function;
	int m_networkID;
	int m_tries;
	int64_t m_id;
	bool m_valid;

	inline bool operator==(const EntityControlStruct& str2) {
		return m_id == str2.m_id;
	}
};
struct EntityModelStruct {
	DWORD m_model;
	function<void(Hash)> m_function;
	int m_tries;
	int64_t m_id;

	inline bool operator==(const EntityModelStruct& str2) {
		return m_id == str2.m_id;
	}
};

class EntityControl {
private:
	queue<EntityControlStruct> m_requests;
	vector<EntityModelStruct> m_models;

public:
	void Update();

	void RequestControl(Entity entity, function<void(Entity)> funcptr);
	void RequestModel(DWORD model, function<void(Hash)> funcptr);

	void SimpleRequestControl(int entity);
	void SimpleRequestModel(int model);
};

extern EntityControl pEntityControl;