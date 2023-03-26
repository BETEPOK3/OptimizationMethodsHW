#ifndef __H_EXTREMUM__
#define __H_EXTREMUM__

#include <ostream>
#include <vector>
#include <functional>

/// <summary>
/// �����, ��������������� ����� ������ ��������� ��� ������� �� ����� ����������
/// </summary>
static class Extremum {
private:
	using Func = std::function<double(const double& x)>;

	static double precision;
	static double leftBound;
	static double rightBound;
	static double step;

	/// <summary>
	/// ����������� ���������� �������
	/// </summary>
	/// <param name="func">�������</param>
	/// <returns>������ ������ ������ ����������� � ��� ���: �������� (true) ��� ������� (false)</returns>
	static std::vector<std::tuple<double, double, bool>> localize(const Func& func);

public:
	/// <summary>
	/// ������������ ���������� ������� ������� ��������� (������� �������)
	/// </summary>
	/// <param name="func">�������</param>
	/// <returns>������ �������� ����������� � �� ���: �������� (true) ��� ������� (false)</returns>
	static std::vector<std::pair<double, bool>> calculateExtremum(const Func& func);
};

#endif