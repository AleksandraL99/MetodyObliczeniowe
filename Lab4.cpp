#include <iostream>
#include <cmath>

using namespace std;
const double TOLF = 1e-8;
const double TOLX = 1e-8;
const int n_max = 30;			//maksymalna liczba iteracji
double jakobian[3][3];			//jakobian przeksztalcenia

double funkcja1(double x, double y, double z) 
{
	return x * x + y * y + z * z - 2.0;
}

double funkcja2(double x, double y) 
{
	return x * x + y * y - 1.0;
}

double funkcja3(double x, double y) 
{
	return x * x - y;
}
double maximum(double a, double b, double c) 
{
	double maximum = a;
	if (b > maximum)
		maximum = b;
	if (c > maximum)
		maximum = c;

	return maximum;
}
void jakob(double x, double y, double z)
{
	jakobian[0][0] = 2.0 * x;
	jakobian[0][1] = 2.0 * y;
	jakobian[0][2] = 2.0 * z;
	jakobian[1][0] = 2.0 * x;
	jakobian[1][1] = 2.0 * y;
	jakobian[1][2] = 0.0;
	jakobian[2][0] = 2 * x;
	jakobian[2][1] = -1;
	jakobian[2][2] = 0.0;
}
void algorytmNewtona(double x, double y, double z) 
{
	double estymator, reziduum;		//inicjowanie zmiennych do obliczania reziduum i estymatora błędu
	double wartosci[3]; 			//inicjalizacja tablicy przechowującej wartosci równań
	double zmiana[3];				

	wartosci[0] = funkcja1(x, y, z);
	wartosci[1] = funkcja2(x, y);
	wartosci[2] = funkcja3(x, y);

	for (int n = 0; n < n_max; n++) 
	{
		for (int li = 0; li < 3; li++) //wyzerowanie macierzy do liczenia błędów
			zmiana[li] = 0;

		if (x == 0) 
		{
			cout << "Nieprawidlowy x" << endl;
			break;
		}
		else if (z == 0)
		{
			cout << "Nieprawidlowe z" << endl;
			break;
		}
		else if (y == -1/2 || 4*y*x+2*x == 0)
		{
			cout << "Nieprawidlowe y" << endl;
			break;
		}


		jakob(x,y,z); //funkcja poza programem głównym w celu łatwej zmiany wartości w przypadku innej funkcji
		 
		zmiana[0] = x / 2 - ((y * y + 1) / (4 * y*x + 2*x)); //wyznaczone ręcznie
		zmiana[1] = (y * y + y - 1) / (2 * y + 1);
		zmiana[2] = (z * z - 1) / (2 * z);

		x = x - zmiana[0]; 
		y = y - zmiana[1];
		z = z - zmiana[2];

		estymator = maximum(fabs(zmiana[0]), fabs(zmiana[1]), fabs(zmiana[2]));
		reziduum = maximum(fabs(wartosci[0]), fabs(wartosci[1]), fabs(wartosci[2]));

		cout <<"Iteracja "<< n+1 <<endl<< "x: " << x <<endl<< "y: " << y <<endl<< "z: " << z <<endl<< "estymator: " << estymator <<endl<< "reziduum: " << reziduum << endl<<endl;

		if (fabs(reziduum) < TOLF) break;	//badamy warunki zakonczenia iteracji, jeśli którys warunek został spełniony, to operacja jest przerywana
		if (fabs(estymator) < TOLX) break;

		wartosci[0] = funkcja1(x, y, z);	//przypisanie nowych wartości
		wartosci[1] = funkcja2(x, y);
		wartosci[2] = funkcja3(x, y);

	}
}

int main() {
	cout.setf(ios::scientific);
	cout.precision(16);
	algorytmNewtona(1.0, 3.0, 5.0);
	return 0;
}
