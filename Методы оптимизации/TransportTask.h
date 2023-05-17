#ifndef __H_TRANSPORT_TASK_H__
#define __H_TRANSPORT_TASK_H__

#include "Printer.h"

class TransportTask {
	TransportTask() = delete;

	/// <summary>
	/// �������� �������� �� ������ ������������
	/// </summary>
	/// <param name="eq">������� �������</param>
	/// <param name="out">������ ����</param>
	/// <param name="in">����</param>
	/// <returns>false - �� ��������</returns>
	static bool checkCondition(const Vector& eq, const Vector& out, const Vector& in);

	static Matrix createPayMatrix();

public:

};

#endif