#include <iostream>
#include "SimplexMethod.h"

void prettyPrint(const Vector& result, const bool& isInf) {
	std::cout << "Ответ: ";
	if (isInf) {
		std::cout << "Infinity\n\n";
	}
	else {
		std::copy(result.begin(), result.end(), std::ostream_iterator<double>(std::cout, ", "));
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::setlocale(0, "");

	Vector eq0 = { 2, 1, 1, -1 };
	Matrix sys0 = {
		{1, -1, 1, 0},
		{2, 1, 0, 1}
	};
	Vector point0 = { 0,0,1,3 };

	Vector eq1 = { -2, -1, -1, -7, 2 };
	Matrix sys1 = {
		{1, 1, -1, 1, 0},
		{2, 1, 1, 0, -1},
		{1, 2, 1, -7, 1}
	};
	Vector point1 = { 2,1,2,0,0 };

	std::pair<Vector, bool> result;
	std::cout << "Задача 1: \n";
	result = SimplexMethod::calculate(eq0, sys0, point0);
	prettyPrint(result.first, result.second);
}