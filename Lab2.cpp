#include <iostream>
#include <fstream> 
#include <string>
#include <cmath>
#include <stdlib.h> 
using namespace std;

long double funkcja(long double x)
{
	return ((1 - exp(-x)) / x);
};

double taylor(double x)
{
	double s = 0, t = 1, n = 2, z = 1;
	if (fabs(x) < 1) //rozwinięcie szeregu w okolicach 0
	{
		while (fabs(t) > 1e-18)
		{
			s = s + z * t; //suma szeregu
			t = t * x / n; //ostatni wyraz
			z = (-1) * z; //znak

			n++;
		}
		return s;
	}
}

int main(int argc, char** argv)
{
	string dane;
	int len = 0;
	fstream fs, blad, blad2;


	fs.open("MO2.txt", ios_base::in);
	blad.open("blad.txt", ios_base::out);
	blad2.open("blad2.txt", ios_base::out);

	if (fs.good() != true && blad.good() != true && blad2.good() != true)
	{
		cout << "Dostep do pliku zostal zabroniony!" << endl;
		exit(1);
	}

	cout.precision(20);
	cout.setf(ios::scientific);
	cin.precision(20);
	fs.precision(20);

	while (!fs.eof()) {

		getline(fs, dane);

		double lg10, x, wyrexp;
		fs >> lg10;
		fs >> x;
		fs >> wyrexp;
		double wyr = funkcja(x);
		double wyr3;
		if (fabs(wyrexp - wyr) < 1e-16) {
			wyr3 = log10(fabs((wyrexp - wyr) / wyrexp));
		}
		else
		{
			double wyr2 = taylor(x);
			wyr3 = log10(fabs((wyrexp - wyr2) / wyrexp));
		}
		blad << float(lg10) << " " << log10(fabs((wyr - wyrexp) / wyrexp)) << " " << endl;
		blad2 << float(lg10) << " " << wyr3 << " " << endl;

	}

	fs.close();
	blad.close();
	return 0;
};
