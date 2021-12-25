#include <iostream>
#include <chrono>
#include <omp.h>
#include <math.h>


double f(double x)
{
	return sin(x);
}


double Integral (double a, double b, double n)
{
	double dx = (b - a) / n;
	double I = 0.0;

	for (uint16_t i = 0; i < dx; i++)
	{
		I += dx * f(a + dx * (i - 0.5));
	}

	return I;
}


/*double Integral_simd (double a, double b, double n)
{
	double dx = (b - a) / n;
	double I = 0.0;

#pragma omp simd reduction(+: I)
	for (uint16_t i = 0; i < dx; i++)
	{
		I += dx * f(a + dx * (i - 0.5));
	};

	return I;
}


double Integral_parallel (double a, double b, double n)
{
	double dx = (b - a) / n;
	double I = 0.0;

#pragma omp parallel for reduction(+: I)
	for (uint16_t i = 0; i < dx; i++)
	{
		I += dx * f(a + dx * (i - 0.5));
	};

	return I;
}*/




int main()
{
	double I, lower_bound, upper_bound, precision;
	
	lower_bound = 0.0;
	upper_bound = 10.0;
	precision = 0.2;

	auto start = std::chrono::high_resolution_clock::now();
	I = Integral(lower_bound, upper_bound, precision);
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duration = finish - start;

	double sec = duration.count();

	std::cout << "time: " << sec << "    I = " << I << "\n";

	/*start = std::chrono::high_resolution_clock::now();
	I1 = Integral(lower_bound, upper_bound, precision);
	finish = std::chrono::high_resolution_clock::now();

	duration = finish - start;

	sec = duration.count();

	std::cout << "time: " << sec << "    I1 = " << I1 << "\n";


	start = std::chrono::high_resolution_clock::now();
	I2 = Integral(lower_bound, upper_bound, precision);
	finish = std::chrono::high_resolution_clock::now();

	duration = finish - start;

	sec = duration.count();

	std::cout << "time: " << sec << "    I2 = " << I2 << "\n";*/

	return 0;
}
