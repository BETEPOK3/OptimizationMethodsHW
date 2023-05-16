#include "TransportTask.h"

bool TransportTask::checkCondition(const Vector& eq, const Vector& out, const Vector& in)
{
	// Сравнение размеров матриц in и out
	if (out.size() != in.size()) {
		return false;
	}

	// Сопоставление размеров матрицы it, out и целевой функции
	if (in.size() * out.size() != eq.size()) {
		return false;
	}

	// Сравнение приёма и получения
	double outTotal = 0;
	double inTotal = 0;
	for (const auto& outNum : out) {
		outTotal += outNum;
	}
	for (const auto& inNum : in) {
		inTotal += inNum;
	}
	if (outTotal != inTotal) {
		return false;
	}
}
