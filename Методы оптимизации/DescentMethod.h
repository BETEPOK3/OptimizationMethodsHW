#ifndef __H_DESCENT_METHOD__
#define __H_DESCENT_METHOD__

#include <functional>

class DescentMethod {
	using Func = std::function<double(std::vector<double> args)>;

	static double gradStep;
	static double precision;

	/// <summary>
	/// ������������ �������� ������� ��������� � ����������� �����
	/// </summary>
	/// <param name="func">�������, �������� ������� ����� �����</param>
	/// <param name="args">���������</param>
	/// <returns>������ ��������� � ����������� �����</returns>
	static std::vector<double> calculateGrad(const Func& func, std::vector<double> args);

	/// <summary>
	/// ������������ ����� �������
	/// </summary>
	/// <param name="args">������</param>
	/// <returns>�����</returns>
	static double calculateNorm(const std::vector<double>& args);

	/// <summary>
	/// ������������ ��������� �������� ���������� � ������ ���� 'a' � ���������
	/// </summary>
	/// <param name="func">�������</param>
	/// <param name="args">���������</param>
	/// <param name="a">���</param>
	/// <returns>����� �������� ���������</returns>
	static std::vector<double> calculateNextArgs(const Func& func, const std::vector<double>& args, const double& a);

public:
	/// <summary>
	/// ����������� ������� ������� ������ ���������� ������� ���������� ������
	/// </summary>
	/// <param name="func"></param>
	/// <param name="args"></param>
	/// <returns></returns>
	static std::vector<double> calculateMinimum(const Func& func, std::vector<double> args);
};

#endif