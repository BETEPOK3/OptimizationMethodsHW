#ifndef __H_SIMPLEX_METHOD_H__
#define __H_SIMPLEX_METHOD_H__

#include <vector>
#include "Printer.h"

class SimplexMethod {
	SimplexMethod() = delete;

	/// <summary>
	/// �������� �������
	/// </summary>
	/// <param name="coefsEq">������������ �������</param>
	/// <param name="coefsMatrix">������������ ������� ���������</param>
	/// <param name="point">������� �����</param>
	/// <returns>������ �������� ������� � �������</returns>
	static Matrix createTable(
		const Vector& coefsEq,
		const Matrix& coefsMatrix,
		const Vector& point);

	/// <summary>
	/// �������� ����� ������� �� ������ ������������ ��������
	/// </summary>
	/// <param name="table">������ �������</param>
	/// <param name="coefsEq">������������ ������� �������</param>
	/// <param name="i0">������ ����������� ������</param>
	/// <param name="j0">������ ������������ �������</param>
	/// <returns>����� �������</returns>
	static Matrix recreateTable(
		const Matrix& table,
		const Vector& coefsEq,
		const size_t& i0,
		const size_t& j0
	);

	/// <summary>
	/// ������� ������� ��������� ������� ������
	/// </summary>
	/// <param name="coefsMatrix">����������� ������� �������</param>
	/// <param name="varsIdx">������� ����������, ������� ����� �����</param>
	/// <returns>�������� ����������� ������� �������</returns>
	static Matrix gauss(
		const Matrix& coefsMatrix,
		const VectorIdx& varsIdx
	);

public:
	/// <summary>
	/// ������� ������ ��������� ���������������� � ������������ ���� �������� �������
	/// </summary>
	/// <param name="coefsEq">������������ �������</param>
	/// <param name="coefsMatrix">������������ ������� ���������</param>
	/// <param name="point">������� �����</param>
	/// <returns>���� <������������ ��������, ���� ����; ���������� �� ���������></returns>
	static std::pair<Vector, bool> calculate(
		const Vector& coefsEq, 
		const Matrix& coefsMatrix, 
		const Vector& point);
};

#endif