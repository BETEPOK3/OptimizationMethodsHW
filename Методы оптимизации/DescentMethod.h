#ifndef __H_DESCENT_METHOD__
#define __H_DESCENT_METHOD__

#include <functional>

class DescentMethod {
	using Func = std::function<double(std::vector<double> args)>;

	static double gradStep;
	static double precision;

	/// <summary>
	/// Выссчитывает значение вектора градиента в определённой точке
	/// </summary>
	/// <param name="func">Функция, градиент которой нужно найти</param>
	/// <param name="args">Аргументы</param>
	/// <returns>Вектор градиента в определённой точке</returns>
	static std::vector<double> calculateGrad(const Func& func, std::vector<double> args);

	/// <summary>
	/// Рассчитывает норму вектора
	/// </summary>
	/// <param name="args">Вектор</param>
	/// <returns>Норма</returns>
	static double calculateNorm(const std::vector<double>& args);

	/// <summary>
	/// Рассчитывает следующие значения аргументов с учётом шага 'a' и градиента
	/// </summary>
	/// <param name="func">Функция</param>
	/// <param name="args">Аргументы</param>
	/// <param name="a">Шаг</param>
	/// <returns>Новые значения аргумента</returns>
	static std::vector<double> calculateNextArgs(const Func& func, const std::vector<double>& args, const double& a);

public:
	/// <summary>
	/// Расчитывает минимум функции многих переменных методов скорейшего спуска
	/// </summary>
	/// <param name="func"></param>
	/// <param name="args"></param>
	/// <returns></returns>
	static std::vector<double> calculateMinimum(const Func& func, std::vector<double> args);
};

#endif