#include "Printer.h"
#include <iostream>
#include <iomanip>
#include <format>

#define CELL_CONFIG std::right << std::setw(8) << std::setprecision(2)

void Printer::printSimplexTable(
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

void Printer::printMatrix(const Matrix& matrix)
{
	std::cout << '\n';
	for (const Vector& eq : matrix) {
		for (const double& num : eq) {
			std::cout << CELL_CONFIG << num;
		}
		std::cout << '\n';
	}
}

void Printer::printMatrixInt(const MatrixInt& matrix)
{
	std::cout << '\n';
	for (const VectorInt& eq : matrix) {
		for (const int& num : eq) {
			std::cout << CELL_CONFIG << num;
		}
		std::cout << '\n';
	}
}

void Printer::printSimplexResult(
	const Vector& coefsEq,
	const std::pair<Vector, bool>& result)
{
	std::cout << "Ответ: ";
	if (result.second) {
		std::cout << "Infinity\n\n";
	}
	else {
		std::copy(result.first.begin(), result.first.end(), 
			std::ostream_iterator<double>(std::cout, " "));
		double z = 0;
		for (size_t j = 0; j < coefsEq.size(); ++j) {
			z += coefsEq[j] * result.first[j];
		}
		std::cout << '\n' << "Значение функции: " << z << "\n\n";
	}
}

void Printer::printTransportBalancedMatrix(
	const MatrixInt& matrix, 
	const MatrixState& state, 
	const MatrixState& opMatrix,
	const size_t& iT,
	const size_t& jT)
{
	const size_t& n = matrix.size();
	const size_t& m = matrix[0].size();

	std::cout << '\n';
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			if (i == iT && j == jT) {
				std::cout << CELL_CONFIG << 't';
				continue;
			}
			if (state[i][j]) {
				if (opMatrix[i][j]) {
					std::cout << CELL_CONFIG << std::format("{}{}t", matrix[i][j], opMatrix[i][j]);
				}
				else {
					std::cout << CELL_CONFIG << matrix[i][j];
				}
			}
			else {
				std::cout << CELL_CONFIG << ' ';
			}
		}
		std::cout << '\n';
	}
}

void Printer::printTransportMatrix(const MatrixInt& matrix, const MatrixState& state)
{
	const size_t& n = matrix.size();
	const size_t& m = matrix[0].size();

	std::cout << '\n';
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			if (state[i][j]) {
				std::cout << CELL_CONFIG << matrix[i][j];
			}
			else {
				std::cout << CELL_CONFIG << ' ';
			}
		}
		std::cout << '\n';
	}
}

void Printer::printTransportResult(const MatrixInt& result, const VectorInt& eq)
{
	const size_t& n = result.size();
	const size_t& m = result[0].size();

	std::cout << "\nОтвет:";
	printMatrixInt(result);
	int val = 0;
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			val += result[i][j] * eq[i * m + j];
		}
	}
	std::cout << "\nЗначение целевой функции: " << val << "\n\n";
}
