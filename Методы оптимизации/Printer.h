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
	/// Выводит симплексную таблицу на экран
	/// </summary>
	/// <param name="varsIdx">Веткор индексов базисов</param>
	/// <param name="table">Симплексная таблица</param>
	/// <param name="coefsEq">Коэффициенты целевой функции</param>
	static void printSimplexTable(
		const VectorIdx& varsIdx,
		const Matrix& table,
		const Vector& coefsEq);

	static void printMatrix(
		const Matrix& system
	);
};

#endif