#include <iostream>
#include "SimplexMethod.h"

int main() {
	std::ios_base::sync_with_stdio(false);
	std::setlocale(0, "");

	std::cout << "Симплекс. Задача 4.1: \n";
	Vector eq41 = { -2, -1, -1, -7, 2 };
	Matrix sys41 = {
		{1, 1, -1, 1, 0, 1},
		{2, 1, 1, 0, -1, 7},
		{1, 2, 1, -7, 1, 6}
	};
	Vector point41 = { 2,1,2,0,0 };
	Printer::printSimplexResult(eq41, SimplexMethod::calculate(eq41, sys41, point41));

	std::cout << "Симплекс. Задача 4.2: \n";
	Vector eq42 = { 5, -4, 1, 3, 5 };
	Matrix sys42 = {
		{3, -1, 0, 2, 1, 5},
		{2, -3, 1, 2, 1, 6},
		{3, -1, 1, 3, 2, 9}
	};
	Vector point42 = { 0, 0, 1, 2, 1 };
	Printer::printSimplexResult(eq42, SimplexMethod::calculate(eq42, sys42, point42));

	std::cout << "Симплекс. Задача 4.3: \n";
	Vector eq43 = { 1, 2, 2, 1, 6 };
	Matrix sys43 = {
		{1, 3, 3, 1, 9, 18},
		{1, 5, 0, 2, 8, 13},
		{0, 0, 1, 0, 1, 3}
	};
	Vector point43 = { 0, 1, 2, 0, 1 };
	Printer::printSimplexResult(eq43, SimplexMethod::calculate(eq43, sys43, point43));

	std::cout << "Симплекс. Задача 4.4: \n";
	Vector eq44 = { 2, 1, 3, 1 };
	Matrix sys44 = {
		{1, 2, 5, -1, 4},
		{1, -1, -1, 2, 1}
	};
	Vector point44 = { 0, 0, 1, 1 };
	Printer::printSimplexResult(eq44, SimplexMethod::calculate(eq44, sys44, point44));

	/*
	std::cout << "Симплекс. Задача 5.2: \n";
	Vector eq52 = { 1, 1, 1, 1 };
	Matrix sys52 = {
		{4, 2, 5, -1, 5},
		{5, 3, 6, -2, 5},
		{3, 2, 4, -1, 4}
	};
	Printer::printSimplexResult(eq52, SimplexMethod::calculate(eq52, sys52));*/

	/*
	std::cout << "Транспортная. Задача 1: \n";
	Vector tEq1 = { 1, 2, 3, 4, 4, 3, 2, 0, 0, 2, 2, 1 };
	Vector tOut1 = { 3, 4, 5 };
	Vector tIn1 = { 2, 3, 4, 3 };*/
}