#ifndef __H_EXTREMUM__
#define __H_EXTREMUM__

#include <ostream>
#include <vector>
#include <functional>

/// <summary>
/// Класс, предоставляющий метод поиска экстремум для функций от одной переменной
/// </summary>
static class Extremum {
private:
	using Func = std::function<double(const double& x)>;

	static double precision;
	static double leftBound;
	static double rightBound;
	static double step;

	/// <summary>
	/// Локализация экстемумов функций
	/// </summary>
	/// <param name="func">Функция</param>
	/// <returns>Массив границ поиска экстремумов и его вид: максимум (true) или минимум (false)</returns>
	static std::vector<std::tuple<double, double, bool>> localize(const Func& func);

public:
	/// <summary>
	/// Рассчитывает экстремумы функции методом дихотомии (деления пополам)
	/// </summary>
	/// <param name="func">Функция</param>
	/// <returns>Массив найденых экстремумов и их вид: максимум (true) или минимум (false)</returns>
	static std::vector<std::pair<double, bool>> calculateExtremum(const Func& func);
};

#endif