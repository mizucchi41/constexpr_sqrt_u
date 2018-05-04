#pragma once

#include <limits>

namespace constexpr_sqrt_u {
	template <class T> constexpr T square(T num) {
		return (T) (num * num);
	}
	
	template <class T> constexpr T exp2_cex(int exp) {
		T tmp = 1, result = 1;
		bool is_minus = exp < 0;
		exp = is_minus ? -exp : exp;

		for (int i = 0; i < exp; i++) {
			result *= is_minus ? 0.5 : 2;
		}

		return result;
	}

	constexpr double sqrt_u(double num) {
		double result = 0, step = 0;
		int exp = -1024;
		if (!(num == num) || num < 0) {
			return std::numeric_limits<double>::quiet_NaN();
		}

		if (num == std::numeric_limits<double>::infinity()) {
			return std::numeric_limits<double>::infinity();
		}

		for (int i = 1024; i != 0; i /= 2) {
			if (square(exp2_cex<double>(exp + i)) <= num) {
				exp += i;
			}
		}

		if (exp == -1024) {
			result = 0, step = exp2_cex<double>(-1023);
		} else {
			result = step = exp2_cex<double>(exp);
		}

		for (int i = 0; i < 52; i++) {
			step /= 2;
			if (square(result + step) <= num) {
				result += step;
			}
		}

		return result;
	}

	constexpr unsigned int sqrt_u(unsigned int num) {
		unsigned int temp = 0;

		for (unsigned int i = ((unsigned int) 1) << ((std::numeric_limits<unsigned int>::digits  / 2) - 1); i != 0; i = i >> 1) {
			if (square(temp + i) <= num) {
				temp += i;
			}
		}
		
		return temp;
	}
	constexpr int sqrt_u(int num) {
		return (int)sqrt_u((unsigned int)num);
	}
}