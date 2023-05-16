#include <iostream>
#include "SimplexMethod.h"

int main() {
	std::ios_base::sync_with_stdio(false);
	std::setlocale(0, "");

	std::cout << "Задача 1: \n";
	Vector eq1 = { -2, -1, -1, -7, 2 };
	Matrix sys1 = {
		{1, 1, -1, 1, 0, 1},
		{2, 1, 1, 0, -1, 7},
		{1, 2, 1, -7, 1, 6}
	};
	Vector point1 = { 2,1,2,0,0 };
	//Printer::printSimplexResult(eq1, SimplexMethod::calculate(eq1, sys1, point1));

	std::cout << "Задача 2: \n";
	Vector eq2 = { 5, -4, 1, 3, 5 };
	Matrix sys2 = {
		{3, -1, 0, 2, 1, 5},
		{2, -3, 1, 2, 1, 6},
		{3, -1, 1, 3, 2, 9}
	};
	Vector point2 = { 0, 0, 1, 2, 1 };
	//Printer::printSimplexResult(eq2, SimplexMethod::calculate(eq2, sys2, point2));

	std::cout << "Задача 3: \n";
	Vector eq3 = { 1, 2, 2, 1, 6 };
	Matrix sys3 = {
		{1, 3, 3, 1, 9, 18},
		{1, 5, 0, 2, 8, 13},
		{0, 0, 1, 0, 1, 3}
	};
	Vector point3 = { 0, 1, 2, 0, 1 };
	//Printer::printSimplexResult(eq3, SimplexMethod::calculate(eq3, sys3, point3));

	std::cout << "Задача 4: \n";
	Vector eq4 = { 2, 1, 3, 1 };
	Matrix sys4 = {
		{1, 2, 5, -1, 4},
		{1, -1, -1, 2, 1}
	};
	Vector point4 = { 0, 0, 1, 1 };
	//Printer::printSimplexResult(eq4, SimplexMethod::calculate(eq4, sys4, point4));
}