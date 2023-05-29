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
	/// �������� �������
	/// </summary>
	/// <param name="eq">������������ ������� �������</param>
	/// <returns>���������� �� �������</returns>
	bool checkCondition(const VectorInt& eq);

	/// <summary>
	/// ���������� ������ ����� ������-�������� �������
	/// </summary>
	void northWestMethod();

	/// <summary>
	/// ���������� ������� �����������
	/// </summary>
	void calcPotentialMatrix();

	/// <summary>
	/// �������� �� �������� ������� ������������� � ������� ������ ������������ �������������� ��������
	/// </summary>
	/// <returns>������ ������������ �������������� �������� (-1 -1, ���� ������ ���)</returns>
	std::pair<int, int> getDeltaMinIndex();

	void recalcMatrix(const size_t& iT, const size_t& jT);

	bool balanceMatrix(const size_t& iT, const size_t jT, const bool& checkColumn);

public:
	TransportTask(const VectorInt& eq, const VectorInt& out, const VectorInt& in);

	MatrixInt calculate();
};

#endif