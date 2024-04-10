#pragma once

struct SCrossmap {
	uint64_t a1;
	uint64_t a2;
};

class Crossmap {
public:
	uint64_t Search(uint64_t original);
};

extern Crossmap pCrossmap;
