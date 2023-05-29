#ifndef __H_PRINTER_H__
#define __H_PRINTER_H__

#include <vector>

using VectorIdx = std::vector<size_t>;

using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;

using VectorState = std::vector<char>;
using MatrixState = std::vector<VectorState>;

using VectorInt = std::vector<int>;
using MatrixInt = std::vector<VectorInt>;

class Printer {
	Printer() = delete;

public:
	/// <summary>
	/// ������� ����������� ������� �� �����
	/// </summary>
	/// <param name="varsIdx">������ �������� �������</param>
	/// <param name="table">����������� �������</param>
	/// <param name="coefsEq">������������ ������� �������</param>
	static void printSimplexTable(
		const VectorIdx& varsIdx,
		const Matrix& table,
		const Vector& coefsEq);

	/// <summary>
	/// ������� �� ����� ������� double
	/// </summary>
	/// <param name="matrix"></param>
	static void printMatrix(
		const Matrix& matrix);

	/// <summary>
	/// ������� �� ����� ������� int
	/// </summary>
	/// <param name="matrix"></param>
	static void printMatrixInt(
		const MatrixInt& matrix);

	/// <summary>
	/// ������� �� ����� ��������� ������� ����������� �������
	/// </summary>
	/// <param name="coefsEq">������� �������</param>
	/// <param name="result">���������</param>
	static void printSimplexResult(
		const Vector& coefsEq,
		const std::pair<Vector, bool>& result);

	/// <summary>
	/// ������� �� ����� ���������������� ������� (����) ��� ������������ ������
	/// </summary>
	/// <param name="matrix">�������</param>
	/// <param name="state">���� ������� ��������</param>
	/// <param name="opMatrix">������ ������� �������� (+ ��� - ��� ������)</param>
	static void printTransportBalancedMatrix(
		const MatrixInt& matrix,
		const MatrixState& state,
		const MatrixState& opMatrix,
		const size_t& iT,
		const size_t& jT);

	/// <summary>
	/// ������� �� ����� ������� (����) ��� ������������ ������
	/// </summary>
	/// <param name="matrix">�������</param>
	/// <param name="state">���� ������� ��������</param>
	static void printTransportMatrix(
		const MatrixInt& matrix,
		const MatrixState& state);

	/// <summary>
	/// ����� ���������� ������������ ������ �� �����
	/// </summary>
	/// <param name="result">��������� � ���� �������</param>
	/// <param name="eq">������� �������</param>
	static void printTransportResult(
		const MatrixInt& result,
		const VectorInt& eq);
};

#endif