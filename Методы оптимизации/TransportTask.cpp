#include "TransportTask.h"
#include <stdexcept>
#include <iostream>
#include <stack>
#include <queue>

bool TransportTask::checkCondition(const VectorInt& eq)
{
	// Сравнение размеров матриц in и out
	if (_out.size() != _in.size()) {
		return false;
	}

	// Сопоставление размеров матрицы it, out и целевой функции
	if (_in.size() * _out.size() != eq.size()) {
		return false;
	}

	// Сравнение приёма и получения
	double outTotal = 0;
	double inTotal = 0;
	for (const auto& outNum : _out) {
		outTotal += outNum;
	}
	for (const auto& inNum : _in) {
		inTotal += inNum;
	}
	if (outTotal != inTotal) {
		return false;
	}
	
	return true;
}

void TransportTask::northWestMethod()
{
	size_t i = 0;
	size_t j = 0;
	int costOut = _out[i];
	int costIn = _in[j];
	while (true) {
		if (costIn <= costOut) {
			_matrixNew[i][j] = costIn;
			_matrixState[i][j] = true;
			++j;
			costOut -= costIn;
			if (j == _in.size()) {
				break;
			}
			costIn = _in[j];
		}
		else {
			_matrixNew[i][j] = costOut;
			_matrixState[i][j] = true;
			++i;
			costIn -= costOut;
			if (i == _out.size()) {
				break;
			}
			costOut = _out[i];
		}
	}
}

void TransportTask::calcPotentialMatrix()
{
	// bool указывает на то, было ли значение инициализировано
	auto out = std::vector<std::pair<bool, int>>(_out.size());
	auto in = std::vector<std::pair<bool, int>>(_in.size());
	
	// Заполнение матрицы потенциалов значениями платёжной матрицы
	MatrixState matrixState = _matrixState;
	for (size_t i = 0; i < out.size(); ++i) {
		for (size_t j = 0; j < in.size(); ++j) {
			if (matrixState[i][j]) {
				_matrixPot[i][j] = _matrixPay[i][j];
			}
		}
	}

	// Расчёт потенциалов
	out[0].first = true;
	std::stack<std::pair<bool, size_t>> s; // false -> out; true -> in
	s.push({ false, 0 });
	while (!s.empty()) {
		const auto [isIn, idx] = s.top();
		s.pop();
		if (isIn) {
			for (size_t i = 0; i < out.size(); ++i) {
				if (out[i].first) {
					if (!matrixState[i][idx]) {
						matrixState[i][idx] = true;
						_matrixPot[i][idx] = out[i].second + in[idx].second;
					}
				}
				else if (matrixState[i][idx]) {
					s.push({ false, i });
					out[i] = { true, _matrixPot[i][idx] - in[idx].second };
				}
			}
		}
		else {
			for (size_t j = 0; j < in.size(); ++j) {
				if (in[j].first) {
					if (!matrixState[idx][j]) {
						matrixState[idx][j] = true;
						_matrixPot[idx][j] = out[idx].second + in[j].second;
					}
				}
				else if (matrixState[idx][j]) {
					s.push({ true, j });
					in[j] = { true, _matrixPot[idx][j] - out[idx].second };
				}
			}
		}
	}
}

std::pair<int, int> TransportTask::getDeltaMinIndex()
{
	std::pair<size_t, size_t> indexMin = { 0, 0 };
	double minValue = _matrixPay[0][0] - _matrixPot[0][0];
	for (size_t i = 0; i < _out.size(); ++i) {
		for (size_t j = 0; j < _in.size(); ++j) {
			double diff = _matrixPay[i][j] - _matrixPot[i][j];
			if (diff < minValue) {
				minValue = diff;
				indexMin = { i, j };
			}
		}
	}
	if (minValue < 0) {
		return indexMin;
	}
	return { -1, -1 };
}

void TransportTask::recalcMatrix(const size_t& iT, const size_t& jT)
{
	// TODO: иногда позникают проблемы (неправильно баланисирует)
	// Балансировка
	bool isBalanced = false;
	_matrixOps[iT][jT] = '+';
	_matrixState[iT][jT] = true;
	for (size_t i = 0; i < _in.size() && !isBalanced; ++i) {
		if (i != iT && _matrixState[i][jT]) {
			_matrixOps[i][jT] = '-';
			isBalanced = balanceMatrix(i, jT, false);
			if (!isBalanced) {
				_matrixOps[i][jT] = 0;
				continue;
			}
		}
		isBalanced = false;
		for (size_t j = 0; j < _out.size(); ++j) {
			if (j != jT && _matrixState[iT][j] && _matrixOps[iT][j] == '-') {
				isBalanced = true;
				break;
			}
		}
	}

	// Поиск t
	size_t iMin = iT;
	size_t jMin = jT;
	for (size_t i = 0; i < _out.size(); ++i) {
		for (size_t j = 0; j < _in.size(); ++j) {
			if (iMin == iT && jMin == jT || _matrixOps[i][j] == '-' && _matrixNew[i][j] < _matrixNew[iMin][jMin]) {
				iMin = i;
				jMin = j;
			}
		}
	}
	int t = _matrixNew[iMin][jMin];

#ifndef NDEBUG
	std::cout << "Балансировка:";
	Printer::printTransportBalancedMatrix(_matrixNew, _matrixState, _matrixOps, iT, jT);
	std::cout << "t = " << t << '\n';
#endif

	// Перерасчёт плана с учётом t
	size_t zeroCount = 0;
	for (size_t i = 0; i < _out.size(); ++i) {
		for (size_t j = 0; j < _in.size(); ++j) {
			if (_matrixOps[i][j] == '+') {
				_matrixNew[i][j] += t;
			}
			else if (_matrixOps[i][j] == '-') {
				_matrixNew[i][j] -= t;
				if (_matrixNew[i][j] == 0) {
					++zeroCount;
					if (_matrixPay[i][j] > _matrixPay[iMin][jMin]) {
						iMin = i;
						jMin = j;
					}
				}
			}
		}
	}

	// Если оказалось слишком много нулей, то убираем элемент с наибольшей стоимостью
	if (zeroCount > 2) {
		_matrixState[iMin][jMin] = false;
	}

#ifndef NDEBUG
	std::cout << "\nНовый план:";
	Printer::printTransportMatrix(_matrixNew, _matrixState);
#endif
}

bool TransportTask::balanceMatrix(const size_t& iT, const size_t jT, const bool& checkColumn)
{
	if (checkColumn) {
		// Поиск балансирующих элементов
		for (size_t i = 0; i < _out.size(); ++i) {
			if (i != iT && _matrixState[i][jT] && 
				(_matrixOps[i][jT] == '+' || _matrixOps[i][jT] == '-') &&
				_matrixOps[i][jT] != _matrixOps[iT][jT]) {
				return true;
			}
		}

		// Если таковых нет, то балансировка
		for (size_t i = 0; i < _out.size(); ++i) {
			if (i != iT && _matrixState[i][jT] && !_matrixOps[i][jT]) {
				_matrixOps[i][jT] = _matrixOps[iT][jT] == '+' ? '-' : '+';
				bool check = balanceMatrix(i, jT, !checkColumn);
				if (check) {
					return true;
				}
				_matrixOps[i][jT] = 0;
			}
		}
	}
	else {
		// Поиск балансирующих элементов
		for (size_t j = 0; j < _in.size(); ++j) {
			if (j != jT && _matrixState[iT][j] &&
				(_matrixOps[iT][j] == '+' || _matrixOps[iT][j] == '-') &&
				_matrixOps[iT][j] != _matrixOps[iT][jT]) {
				return true;
			}
		}

		// Если таковых нет, то балансировка
		for (size_t j = 0; j < _out.size(); ++j) {
			if (j != jT && _matrixState[iT][j] && !_matrixOps[iT][j]) {
				_matrixOps[iT][j] = _matrixOps[iT][jT] == '+' ? '-' : '+';
				bool check = balanceMatrix(iT, j, !checkColumn);
				if (check) {
					return true;
				}
				_matrixOps[iT][j] = 0;
			}
		}
	}

	return false;
}

TransportTask::TransportTask(const VectorInt& eq, const VectorInt& out, const VectorInt& in)
	: _out{ out }
	, _in{ in }
	, _matrixPay(out.size(), VectorInt(in.size()))
	, _matrixNew(out.size(), VectorInt(in.size()))
	, _matrixPot(out.size(), VectorInt(in.size()))
	, _matrixState(out.size(), VectorState(in.size()))
	, _matrixOps(out.size(), VectorState(in.size()))
{
	if (!checkCondition(eq)) {
		throw std::runtime_error("Размерности уравенения и системы не соответствуют (транспортная задача).");
	}
	for (size_t i = 0; i < out.size(); ++i) {
		for (size_t j = 0; j < in.size(); ++j) {
			_matrixPay[i][j] = eq[i * in.size() + j];
		}
	}
}

MatrixInt TransportTask::calculate()
{
	northWestMethod();
#ifndef NDEBUG
	std::cout << "\nНовый план:";
	Printer::printTransportMatrix(_matrixNew, _matrixState);
#endif
	while (true) {
		calcPotentialMatrix();
#ifndef NDEBUG
		std::cout << "\nМатрица потенциалов:";
		Printer::printTransportMatrix(_matrixPot, _matrixState);
#endif
		auto [iMin, jMin] = getDeltaMinIndex();
		if (iMin == -1) {
			return _matrixNew;
		}
		recalcMatrix(iMin, jMin);
		break;
	}
	
	return _matrixNew;
}