#include "SimplexMethod.h"
#include "Printer.h"
#include <iostream>
#include <iomanip>
#include <format>
#include <algorithm>
#include <unordered_map>

Matrix SimplexMethod::createTable(
	const Vector& coefsEq, 
	const Matrix& coefsMatrix, 
	const Vector& point)
{
	// �������� ������� � ������� ��������������� ��������
	const size_t colCount = coefsEq.size() + 2;
	Matrix table(coefsMatrix.size() + 2, Vector(colCount));
	VectorIdx varsIdx(coefsMatrix.size());

	// ���������� �������
	size_t idx = 0;
	for (size_t i = 0; i < table.size() - 2; ++i) {
		while (point[idx] == 0) {
			++idx;
		}
		varsIdx[i] = idx;
		table[i][0] = coefsEq[idx]; // ����������� �� ������� �������
		table[i][1] = point[idx]; // ���������� �����

		// ������������ �� ������� ���������
		for (size_t j = 2; j < colCount; ++j) {
			table[i][j] = coefsMatrix[i][j - 2];
		}
		++idx;
	}

	// �������� ������� �������
	for (size_t j = 1; j < colCount; ++j) {
		for (size_t i = 0; i < coefsMatrix.size(); ++i) {
			table[table.size() - 2][j] += table[i][0] * table[i][j];
		}
	}

	// �������� �������� ������� � ������������ �������
	for (size_t j = 2; j < colCount; ++j) {
		table[table.size() - 1][j] = table[table.size() - 2][j] - coefsEq[j - 2];
	}

#ifndef NDEBUG
	Printer::printSimplexTable(varsIdx, table, coefsEq);
#endif

	return table;
}

Matrix SimplexMethod::recreateTable(
	const Matrix& table, 
	const Vector& coefsEq, 
	const size_t& i0, 
	const size_t& j0)
{
	Matrix newTable = table;
	const size_t colCount = newTable[0].size();
	const size_t basisRowCount = newTable.size() - 2;

	// ����� �����������
	newTable[i0][0] = coefsEq[j0 - 2];

	// ���������� �������� ����������
	for (size_t i = 0; i < basisRowCount; ++i) {
		for (size_t j = 1; j < colCount; ++j) {
			if (i != i0) {
				newTable[i][j] -= table[i0][j] * table[i][j0] / table[i0][j0];
			}
			else {
				newTable[i][j] /= table[i0][j0];
			}
		}
	}

	// ���������� �������� ������� �������
	for (size_t j = 1; j < colCount; ++j) {
		newTable[newTable.size() - 2][j] = 0;
		for (size_t i = 0; i < basisRowCount; ++i) {
			newTable[newTable.size() - 2][j] += newTable[i][0] * newTable[i][j];
		}
	}

	// ���������� ��������
	for (size_t j = 2; j < colCount; ++j) {
		newTable[newTable.size() - 1][j] = newTable[newTable.size() - 2][j] - coefsEq[j - 2];
	}

	return newTable;
}

Matrix SimplexMethod::gauss(
	const Matrix& coefsMatrix,
	const VectorIdx& varsIdx)
{
	if (coefsMatrix.size() != varsIdx.size()) {
		throw std::runtime_error("������ ������� ��������� ������ ��������� � ���-��� ���������� ����������.");
	}
	Matrix newMatrix = coefsMatrix;
	
	// ������������ ���������� ���������� � ���������, � ������� ��� ����� ��������
	std::unordered_map<size_t, size_t> mapEqIdx;
	size_t j = 0;
	bool cycle = true;
	while (mapEqIdx.size() != varsIdx.size()) {
		// ������ ������ (������������� ������� �������)
		for (size_t nextIdx = 0; nextIdx < coefsMatrix.size(); ++nextIdx) {
			if (coefsMatrix[nextIdx][varsIdx[j]] != 0 && mapEqIdx.find(nextIdx) == mapEqIdx.end()) {
				if (nextIdx != j) {
					swap(newMatrix[j], newMatrix[nextIdx]);
				}
				mapEqIdx[j] = varsIdx[j];
				cycle = false;
				break;
			}
		}

		// ������ ������ (�������������� ���������)
		if (cycle) {
			for (size_t nextIdx = 0; nextIdx < coefsMatrix.size(); ++nextIdx) {
				if (coefsMatrix[nextIdx][varsIdx[j]] != 0) {
					if (nextIdx != j) {
						swap(newMatrix[j], newMatrix[nextIdx]);
					}
					mapEqIdx[j] = varsIdx[j];
					break;
				}
			}
		}

		// ���������� � ���������� ����
		++j;
		if (j >= varsIdx.size()) {
			j = 0;
		}
		cycle = true;
	}

	// ��������� ���������� � �������
	for (const auto& [eqIdx, varIdx] : mapEqIdx) {
		Vector& eq = newMatrix[eqIdx];

		// ������� ���� ���������� � ��������� �� ��������
		double basisNum = eq[varIdx];
		std::for_each(eq.begin(), eq.end(), [&basisNum](double& num) {
			num /= basisNum;
			});

		// ��������� �� ���� ��������� ��������� �������� ���, �����
		// �� ���� ��������� ���������� ��� �������� ���������� ���� ����� 0
		for (size_t idx2 = 0; idx2 < coefsMatrix.size(); ++idx2) {
			if (idx2 != eqIdx) {
				double mult = newMatrix[idx2][varIdx] / eq[varIdx];
				for (size_t idx3 = 0; idx3 < eq.size(); ++idx3) {
					newMatrix[idx2][idx3] -= eq[idx3] * mult;
				}
			}
		}
	}

#ifndef NDEBUG
	Printer::printMatrix(newMatrix);
#endif

	return newMatrix;
}

std::pair<Vector, bool> SimplexMethod::calculate(
	const Vector& coefsEq, 
	const Matrix& coefsMatrix,
	const Vector& point)
{
	// ��������� �������� ����������
	VectorIdx varsIdx;
	for (size_t j = 0; j < point.size(); ++j) {
		if (point[j] != 0) {
			varsIdx.push_back(j);
		}
	}
	const Matrix newMatrix = gauss(coefsMatrix, varsIdx);

	// �������� ����������� �������
	Matrix table = createTable(coefsEq, newMatrix, point);
	const size_t colCount = table[0].size();

	// ������� ����������� �������
	do {
		Vector& z = table[table.size() - 2];
		Vector& delta = table[table.size() - 1];

		// ����� ������������ �������
		size_t j0 = std::distance(delta.begin(), std::min_element(delta.begin() + 2, delta.end()));
		if (delta[j0] < 0) {
			// ����� ����������� ������
			size_t i0 = 0;
			for (size_t i = 1; i < table.size() - 2; ++i) {
				if (table[i][j0] > table[i0][j0]) {
					i0 = i;
				}
			}

			// ���� ������� ���
			if (table[i0][j0] <= 0) {
				return { {}, true };
			}

			// ���������� �������
			table = recreateTable(table, coefsEq, i0, j0);
			varsIdx[i0] = j0 - 2;
		}

		// ������� �������
		else {
			Vector result(coefsEq.size());
			for (size_t i = 0; i < table.size() - 2; ++i) {
				result[varsIdx[i]] = table[i][1];
			}
			return { result, false };
		}

#ifndef NDEBUG
		Printer::printSimplexTable(varsIdx, table, coefsEq);
#endif

	} while (true);

	return { {}, true };
}