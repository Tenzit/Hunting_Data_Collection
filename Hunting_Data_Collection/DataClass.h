#pragma once

#include "string"
#include <iostream>
#include <ostream>

struct PieceTimes {
	int il;
	int igt;
	int v1;
	int v2_5;
	int timesRestarted;
};

std::ostream &operator<< (std::ostream& os, const PieceTimes& rhs) {
	os << rhs.il << ","
		<< rhs.igt << ","
		<< rhs.v1 << ","
		<< rhs.v2_5 << ","
		<< rhs.timesRestarted;
	return os;
};

struct Data {
	std::string stageName;
	uint32_t pieces[3];
	PieceTimes collected[3];
	PieceTimes finished;
};

std::ostream &operator<< (std::ostream& os, const Data& rhs) {
	os << rhs.stageName << ",";
	for (int i = 0; i < 3; i++) {
		os << rhs.pieces[i] << ","
			<< rhs.collected[i] << ",";
	}
	os << rhs.finished;
	return os;
};