#include "DescentMethod.h"
#include "MyDebug.h"
#include "Extremum.h"
#include <vector>
#include <iomanip>

using namespace std;

double DescentMethod::gradStep{ 0.0000001 };
double DescentMethod::precision{ 0.001 };

std::vector<double> DescentMethod::calculateGrad(const Func& func, std::vector<double> args)
{
	vector<double> result;
	for (double& arg : args) {
		arg += gradStep;
		double f1{ func(args) };
		arg -= gradStep;
		result.push_back((f1 - func(args)) / gradStep);
	}
	return result;
}

double DescentMethod::calculateNorm(const std::vector<double>& args)
{
	double result{ abs(args[0])};
	for (size_t i = 1; i < args.size(); ++i) {
		double val{ abs(args[i]) };
		if (val > result) {
			result = val;
		}
	}
	return result;
}

std::vector<double> DescentMethod::calculateNextArgs(const Func& func, const std::vector<double>& args, const double& a)
{
	vector<double> newArgs = calculateGrad(func, args);
	for (size_t i = 0; i < args.size(); ++i) {
		newArgs[i] = args[i] - a * newArgs[i];
	}
	return newArgs;
}

vector<double> DescentMethod::calculateMinimum(const Func& func, vector<double> args)
{
	size_t it{ 0 };
	double fValNext{ func(args) };
	vector<double> grad;
	double fVal;
	double norm;

	do {
		fVal = fValNext;
		grad = calculateGrad(func, args);

		// Функция от аргумента с шагом 'a' (нужна для поиска экстремумы)
		const auto funcNext = [&grad, &args, &func](const double& a) -> double {
			vector<double> newGrad{ args };
			for (size_t i = 0; i < newGrad.size(); ++i) {
				newGrad[i] -= a * grad[i];
			}
			return func(newGrad);
		};

		vector<pair<double, bool>> possResults {Extremum::calculateExtremum(funcNext)};
		double a{ possResults[0].first };
		args = calculateNextArgs(func, args, a);
		fValNext = func(args);
		norm = calculateNorm(grad);
		++it;

#ifndef NDEBUG
		cout << "i: " << it;
		for (size_t i = 0; i < args.size(); ++i) {
			cout << "\tx" << i + 1 << ": " << setw(12) << left << args[i];
		}
		cout << "\tf: " << setw(12) << left << fValNext <<
			"\t|x|: " << setw(12) << left << norm << '\n';
#endif

	} while (norm >= precision);
	
	DEBUG_MSG("\n\n");

	return args;
}
