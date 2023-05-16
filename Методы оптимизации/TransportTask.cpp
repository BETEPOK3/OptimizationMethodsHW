#include "TransportTask.h"

bool TransportTask::checkCondition(const Vector& eq, const Vector& out, const Vector& in)
{
	// ��������� �������� ������ in � out
	if (out.size() != in.size()) {
		return false;
	}

	// ������������� �������� ������� it, out � ������� �������
	if (in.size() * out.size() != eq.size()) {
		return false;
	}

	// ��������� ����� � ���������
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
