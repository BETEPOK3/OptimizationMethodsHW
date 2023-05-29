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
	/// Выводит симплексную таблицу на экран
	/// </summary>
	/// <param name="varsIdx">Веткор индексов базисов</param>
	/// <param name="table">Симплексная таблица</param>
	/// <param name="coefsEq">Коэффициенты целевой функции</param>
	static void printSimplexTable(
		const VectorIdx& varsIdx,
		const Matrix& table,
		const Vector& coefsEq);

	/// <summary>
	/// Вывести на экран матрицу double
	/// </summary>
	/// <param name="matrix"></param>
	static void printMatrix(
		const Matrix& matrix);

	/// <summary>
	/// Вывести на экран матрицу int
	/// </summary>
	/// <param name="matrix"></param>
	static void printMatrixInt(
		const MatrixInt& matrix);

	/// <summary>
	/// Вывести на экран результат решения симплексным методом
	/// </summary>
	/// <param name="coefsEq">Целевая функция</param>
	/// <param name="result">Результат</param>
	static void printSimplexResult(
		const Vector& coefsEq,
		const std::pair<Vector, bool>& result);

	/// <summary>
	/// Выводит на экран сбалансированную матрицу (план) для транспортной задачи
	/// </summary>
	/// <param name="matrix">Матрица</param>
	/// <param name="state">Учёт каждого элемента</param>
	/// <param name="opMatrix">Баланс каждого элемента (+ или - или ничего)</param>
	static void printTransportBalancedMatrix(
		const MatrixInt& matrix,
		const MatrixState& state,
		const MatrixState& opMatrix,
		const size_t& iT,
		const size_t& jT);

	/// <summary>
	/// Выводит на экран матрицу (план) для транспортной задачи
	/// </summary>
	/// <param name="matrix">Матрица</param>
	/// <param name="state">Учёт каждого элемента</param>
	static void printTransportMatrix(
		const MatrixInt& matrix,
		const MatrixState& state);

	/// <summary>
	/// Вывод результата транспортной задачи на экран
	/// </summary>
	/// <param name="result">Результат в виде матрицы</param>
	/// <param name="eq">Целевая функция</param>
	static void printTransportResult(
		const MatrixInt& result,
		const VectorInt& eq);
};

#endif