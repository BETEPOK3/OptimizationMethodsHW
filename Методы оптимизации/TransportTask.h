#ifndef __H_TRANSPORT_TASK_H__
#define __H_TRANSPORT_TASK_H__

#include "Printer.h"

class TransportTask {
	TransportTask() = delete;

	/// <summary>
	/// Проверка является ли задача транспортной
	/// </summary>
	/// <param name="eq">Целевая функция</param>
	/// <param name="out">Откуда везём</param>
	/// <param name="in">Куда</param>
	/// <returns>false - не является</returns>
	static bool checkCondition(const Vector& eq, const Vector& out, const Vector& in);

	static Matrix createPayMatrix();

public:

};

#endif