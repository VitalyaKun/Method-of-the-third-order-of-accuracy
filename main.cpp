#include <iostream>
#include <cmath>
#include <fstream>
#include <conio.h>

using namespace std;

double f(double x, double y)
{
	return 2.1 * y + x + 0.25;
}
int main()
{
	ifstream in;
	in.open("in.txt");
	double a, b, y0, h = 0.1, e = 1e-5;
	int k;
	in >> k;
	double *x0 = new double[k + 1]; // x для которых мы хотим решить задачу Коши
	in >> x0[0];
	in >> y0;
	for (int i = 1; i <= k; i++)
	{
		in >> x0[i];
	}
	cout << "Solution of the Cauchy problem: \n";
	for (int p = 0; p < k; p++)
	{
		a = x0[0];
		b = x0[p + 1];
		h = 0.1;
		int n = (b - a) / h + 1;
		double *y1 = new double[n];
		double *y2 = new double[n];
		y1[0] = y2[0] = y0;

		double *x = new double[n];
		x[0] = x0[0];
		int k = 1;
		double fi0, fi1, fi2;

		// Расчитываем у1 методом 3-го порядка точности
		for (int i = 1; i < n; i++)
		{
			x[i] = x[i - 1] + h;
			fi0 = h * f(x[i - 1], y1[i - 1]);
			fi1 = h * f(x[i - 1] + h / 2., y1[i - 1] + fi0 / 2.);;
			fi2 = h * f(x[i - 1] + h, y1[i - 1] - fi0 + 2 * fi1);
			y1[i] = y1[i - 1] + (fi0 + 4 * fi1 + fi2) / 6;
		}

		do   // Метод двойного пересчета
		{
			for (int i = 0; i < n; ++i)
				y2[i] = y1[i];

			y1[0] = y0;
			h /= 2;
			k *= 2;
			x[0] = x0[0];

			for (int i = 1; i < n; i++)   // Расчитываем у с шагом h/2
			{
				x[i] = x[i - 1] + h * (i - 1) * (k - 1);
				fi0 = h * f(x[i - 1], y1[i - 1]);
				fi1 = h * f(x[i - 1] + h / 2., y1[i - 1] + fi0 / 2.);;
				fi2 = h * f(x[i - 1] + h, y1[i - 1] - fi0 + 2 * fi1);
				y1[i] = y1[i - 1] + (fi0 + 4 * fi1 + fi2) / 6;
				for (int j = 1; j < k - 1; ++j)
					y1[i] += h * f(a + h * ((i - 1) * (k - 1) + j - 1), y1[i]);
			}
		} while (fabs(y1[n - 1] - y2[n - 1]) > e);

		cout << "y(" << x0[p + 1] << ") = " << y1[n - 1] << endl;
	}
	getch();
	system("pause");
}


