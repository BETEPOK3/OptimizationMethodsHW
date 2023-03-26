#include "Extremum.h"
#include "DescentMethod.h"
#include <iostream>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::setlocale(0, "");

	const auto func1 = [](std::vector<double> args) -> double {
		return args[0] * args[0] + args[1] * args[1] - 2 * args[0] - 4 * args[1] + 5;
	};
	const auto func2 = [](std::vector<double> args) -> double {
		return 2 * args[0] * args[0] - 2 * args[0] * args[1] + args[1] * args[1] + 2 * args[0] - 2 * args[1];
	};
	const auto func3 = [](std::vector<double> args) -> double {
		return args[0] * args[0] + 2 * args[1] * args[1] + args[2] * args[2] - 2 * args[0] * args[1] - args[0] + 2 * args[2];
	};
	const auto func4 = [](std::vector<double> args) -> double {
		return args[0] * args[0] + args[1] * args[1] + args[2] * args[2] - args[0] * args[1] + args[0] - 2 * args[2];
	};
	const auto func6 = [](std::vector<double> args) -> double {
		return args[0] * args[0] + args[1] * args[1] - 0.2 * args[0] * args[1] - 2.2 * args[0] + 2.2 * args[1] + 2.2;
	};
	const auto func7 = [](std::vector<double> args) -> double {
		return 5 * args[0] * args[0] + 4.075 * args[1] * args[1] - 9 * args[0] * args[1] + args[0] + 2;
	};
	const double k{ 0 };
	const auto func8 = [&k](std::vector<double> args) -> double {
		return pow(args[0] + 10 * args[1], 2) + 5 * pow(args[2] - args[3] + 2 * k, 2) + pow(args[1] - 2 * args[2], 4) + 100 * pow(args[0] - args[3] + 11 * k, 4);
	};

	std::cout << "Функция 1:\n";
	DescentMethod::calculateMinimum(func1, { 0, 0 });
	std::cout << "Функция 2:\n";
	DescentMethod::calculateMinimum(func2, { 0, 0 });
	std::cout << "Функция 3:\n";
	DescentMethod::calculateMinimum(func3, { 0, 0, 0 });
	std::cout << "Функция 4:\n";
	DescentMethod::calculateMinimum(func4, { 0, 0, 0 });
	std::cout << "Функция 6:\n";
	DescentMethod::calculateMinimum(func6, { 0, 0 });
	std::cout << "Функция 7:\n";
    DescentMethod::calculateMinimum(func7, { 0, -40 });
	std::cout << "Функция 8:\n";
	DescentMethod::calculateMinimum(func8, { 0, 0, 0, 0 });
}