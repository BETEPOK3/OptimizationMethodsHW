#include "Extremum.h"
#include "MyDebug.h"
#include <iostream>
#include <iomanip>

using namespace std;

double Extremum::precision{ 0.0004 };
double Extremum::leftBound{ -10000 };
double Extremum::rightBound{ 10000 };
double Extremum::step{ 100 };

vector<tuple<double, double, bool>> Extremum::localize(const Func& func) {
	vector<tuple<double, double, bool>> result;
	double x{ leftBound + step * 2 };
	double yLeft{ func(leftBound) };
	double yMid{ func(leftBound + step) };
	double yRight{ func(x) };

	while (x <= rightBound) {
		if (yMid < yLeft && yMid < yRight) {
			result.push_back({ x - 2 * step, x, false });
		}
		else if (yMid > yLeft && yMid > yRight) {
			result.push_back({ x - 2 * step, x, true });
		}
		x += step;
		yLeft = yMid;
		yMid = yRight;
		yRight = func(x);
	}

	return result;
}

vector<pair<double, bool>> Extremum::calculateExtremum(const Func& func) {
	vector<pair<double, bool>> result;
	auto locals = localize(func);

	for (auto [xLeft, xRight, isMax] : locals) {
		size_t it{ 0 };
		double thisPrec{ (xRight - xLeft) * 0.5 };
		double yLeft{ func(xLeft) };
		double yRight{ func(xRight) };
		double xMid{ xLeft };
		double yMid;
		//DEBUG_MSG("Поиск экстремумы: [" << xLeft << ", " << xRight << "]\n");

		while (thisPrec > precision) {
			++it;
			xMid = (xLeft + xRight) * 0.5;
			yMid = func(xMid);
			if (isMax && yLeft < yRight || !isMax && yLeft > yRight) {
				xLeft = xMid;
				yLeft = yMid;
			}
			else {
				xRight = xMid;
				yRight = yMid;
			}
			thisPrec = (xRight - xLeft) * 0.5;

			//DEBUG_MSG("i: " << it << "\tx: " << setw(10) << left << xMid << "\ty: " << setw(10) << yMid << '\n');
		}
		//DEBUG_MSG((isMax ? "Максимум:" : "Минимум:") << setw(10) << left << xMid << "\n\n");

		result.push_back({ xMid, isMax });
	}

	if (locals.size() == 0) {
		if (func(rightBound) < func(leftBound)) {
			result.push_back({ rightBound, false });
			result.push_back({ leftBound, true });
		}
		else {
			result.push_back({ leftBound, false });
			result.push_back({ rightBound, true });
		}
	}

	return result;
}