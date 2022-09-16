#pragma once

#include "string"

struct PieceTimes {
	int il;
	int igt;
	int v1;
	int v2_5;
	int timesRestarted;
};

struct Data {
	std::string stageName;
	uint32_t pieces[3];
	PieceTimes collected[3];
	PieceTimes finished;
};