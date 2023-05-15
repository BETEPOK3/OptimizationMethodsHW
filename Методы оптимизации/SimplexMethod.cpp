#include "SimplexMethod.h"
#include <iostream>
#include <iomanip>
#include <format>

#define CELL_CONFIG std::right << std::setw(8)

std::pair<VectorIdx, Matrix> SimplexMethod::createTable(
	const Vector& coefsEq, 
	const Matrix& coefsMatrix, 
	const Vector& point)
{
	// Создание таблицы и вектора соответствующих индексов
	const size_t colCount = coefsEq.size() + 2;
	Matrix table(coefsMatrix.size() + 2, Vector(colCount));
	VectorIdx varsIdx(coefsMatrix.size());

	// Заполнение таблицы
	size_t idx = 0;
	for (size_t i = 0; i < table.size() - 2; ++i) {
		while (point[idx] == 0) {
			++idx;
		}
		varsIdx[i] = idx;
		table[i][0] = coefsEq[idx]; // коэффициент из целевой функции
		table[i][1] = point[idx]; // координата точки

		// Коэффициенты из системы уравнений
		for (size_t j = 2; j < colCount; ++j) {
			table[i][j] = coefsMatrix[i][j - 2];
		}
		++idx;
	}

	// Значения целевой функции
	for (size_t j = 1; j < colCount; ++j) {
		for (size_t i = 0; i < coefsMatrix.size(); ++i) {
			table[table.size() - 2][j] += table[i][0] * table[i][j];
		}
	}

	// Разность значения функции и коэффициента функции
	for (size_t j = 2; j < colCount; ++j) {
		table[table.size() - 1][j] = table[table.size() - 2][j] - coefsEq[j - 2];
	}

#ifndef NDEBUG
	printTable(varsIdx, table, coefsEq);
#endif

	return { varsIdx, table };
}

void SimplexMethod::printTable(
	const VectorIdx& varsIdx,
	const Matrix& table,
	const Vector& coefsEq)
{
	std::cout << '\n' << CELL_CONFIG << "Basis"
		<< CELL_CONFIG << 'c'
		<< CELL_CONFIG << "_x_";
	for (size_t j = 0; j < coefsEq.size(); ++j)
		std::cout << CELL_CONFIG << coefsEq[j];
	std::cout << '\n';
	for (size_t i = 0; i < table.size() - 2; ++i) {
		std::cout << CELL_CONFIG << std::format("x{}", varsIdx[i] + 1);
		for (size_t j = 0; j < table[0].size(); ++j) {
			std::cout << CELL_CONFIG << table[i][j];
		}
		std::cout << '\n';
	}
	std::cout << CELL_CONFIG << 'z' << CELL_CONFIG << ' ';
	for (size_t j = 1; j < table[0].size(); ++j)
		std::cout << CELL_CONFIG << table[table.size() - 2][j];
	std::cout << '\n' << CELL_CONFIG << "delta" << CELL_CONFIG << ' ' << CELL_CONFIG << ' ';
	for (size_t j = 2; j < table[0].size(); ++j)
		std::cout << CELL_CONFIG << table[table.size() - 1][j];
	std::cout << '\n';
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

	// Новый коэффициент
	newTable[i0][0] = coefsEq[j0 - 2];

	// Перерасчёт базисных переменных
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

	// Перерасчёт значений целевой функции
	for (size_t j = 1; j < colCount; ++j) {
		newTable[newTable.size() - 2][j] = 0;
		for (size_t i = 0; i < basisRowCount; ++i) {
			newTable[newTable.size() - 2][j] += newTable[i][0] * newTable[i][j];
		}
	}

	// Перерасчёт разности
	for (size_t j = 2; j < colCount; ++j) {
		newTable[newTable.size() - 1][j] = newTable[newTable.size() - 2][j] - coefsEq[j - 2];
	}

	return newTable;
}

std::pair<Vector, bool> SimplexMethod::calculate(
	const Vector& coefsEq, 
	const Matrix& coefsMatrix,
	const Vector& point)
{
	// Создание симплексной таблицы
	auto [varsIdx, table] = createTable(coefsEq, coefsMatrix, point);
	const size_t colCount = table[0].size();

	// Решение симплексным методом
	do {
		Vector& z = table[table.size() - 2];
		Vector& delta = table[table.size() - 1];

		// Поиск разрешающего столбца
		size_t j0 = std::distance(delta.begin(), std::min_element(delta.begin() + 2, delta.end()));
		if (delta[j0] < 0) {
			// Поиск разрешающей строки
			size_t i0 = 0;
			for (size_t i = 1; i < table.size() - 2; ++i) {
				if (table[i][j0] > table[i0][j0]) {
					i0 = i;
				}
			}

			// Если решения нет
			if (table[i0][j0] <= 0) {
				return { {}, true };
			}

			// Перерасчёт таблицы
			table = recreateTable(table, coefsEq, i0, j0);
			varsIdx[i0] = j0 - 2;
		}

		// Решение найдено
		else {
			Vector result(coefsEq.size());
			for (size_t i = 0; i < table.size() - 2; ++i) {
				result[varsIdx[i]] = table[i][1];
			}
			return { result, false };
		}

#ifndef NDEBUG
		printTable(varsIdx, table, coefsEq);
#endif

	} while (true);

	return { {}, true };
}