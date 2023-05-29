#ifndef __H_TRANSPORT_TASK_H__
#define __H_TRANSPORT_TASK_H__

#include "Printer.h"

class TransportTask {
	const VectorInt _out;
	const VectorInt _in;
	MatrixInt _matrixPay;
	MatrixInt _matrixNew;
	MatrixInt _matrixPot;
	MatrixState _matrixState;
	MatrixState _matrixOps;

	/// <summary>
	/// Проверка условия
	/// </summary>
	/// <param name="eq">Коэффициенты целевой функции</param>
	/// <returns>Правильное ли условие</returns>
	bool checkCondition(const VectorInt& eq);

	/// <summary>
	/// Построение нового плана северо-западным методом
	/// </summary>
	void northWestMethod();

	/// <summary>
	/// Рассчитать матрицу потенциалов
	/// </summary>
	void calcPotentialMatrix();

	/// <summary>
	/// Вычитает из платёжной матрицы потенциальную и находит индекс минимального отрицательного значения
	/// </summary>
	/// <returns>Индекс минимального отрицательного значения (-1 -1, если такого нет)</returns>
	std::pair<int, int> getDeltaMinIndex();

	void recalcMatrix(const size_t& iT, const size_t& jT);

	bool balanceMatrix(const size_t& iT, const size_t jT, const bool& checkColumn);

public:
	TransportTask(const VectorInt& eq, const VectorInt& out, const VectorInt& in);

	MatrixInt calculate();
};

#endif