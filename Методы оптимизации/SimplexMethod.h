#ifndef __H_SIMPLEX_METHOD_H__
#define __H_SIMPLEX_METHOD_H__

#include <vector>
#include "Printer.h"

class SimplexMethod {
	SimplexMethod() = delete;

	/// <summary>
	/// Создание таблицы
	/// </summary>
	/// <param name="coefsEq">Коэффициенты функции</param>
	/// <param name="coefsMatrix">Коэффициенты системы уравнений</param>
	/// <param name="point">Угловая точка</param>
	/// <returns>Вектор индексов базисов и таблица</returns>
	static Matrix createTable(
		const Vector& coefsEq,
		const Matrix& coefsMatrix,
		const Vector& point);

	/// <summary>
	/// Создание новой таблицы на основе разрешающего элемента
	/// </summary>
	/// <param name="table">Старая таблица</param>
	/// <param name="coefsEq">Коэффициенты целевой функции</param>
	/// <param name="i0">Индекс разрешающей строки</param>
	/// <param name="j0">Индекс разрешающего столбца</param>
	/// <returns>Новая таблица</returns>
	static Matrix recreateTable(
		const Matrix& table,
		const Vector& coefsEq,
		const size_t& i0,
		const size_t& j0
	);

	/// <summary>
	/// Решение системы уравнений методом Гаусса
	/// </summary>
	/// <param name="coefsMatrix">Расширенная матрица системы</param>
	/// <param name="varsIdx">Индексы переменных, которые нужно найти</param>
	/// <returns>Решённая расширенная матрица системы</returns>
	static Matrix gauss(
		const Matrix& coefsMatrix,
		const VectorIdx& varsIdx
	);

public:
	/// <summary>
	/// Решение задачи линейного программирования в каноническом виде симплекс методом
	/// </summary>
	/// <param name="coefsEq">Коэффициенты функции</param>
	/// <param name="coefsMatrix">Коэффициенты системы уравнений</param>
	/// <param name="point">Угловая точка</param>
	/// <returns>Пара <максимальное значение, если есть; бесконечен ли результат></returns>
	static std::pair<Vector, bool> calculate(
		const Vector& coefsEq, 
		const Matrix& coefsMatrix, 
		const Vector& point);
};

#endif