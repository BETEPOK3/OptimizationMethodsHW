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
