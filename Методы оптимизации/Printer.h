#ifndef __H_PRINTER_H__
#define __H_PRINTER_H__

#include <vector>

using VectorIdx = std::vector<size_t>;
using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;

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

	static void printMatrix(
		const Matrix& system
	);
};

#endif