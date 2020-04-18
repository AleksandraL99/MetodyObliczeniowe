#include <iostream>
#include <cmath>
using namespace std;

typedef double (*function)(double); //definiowanie nowego typu, zwracającego double, aby przekazywac dowolna funkcje

double f1(double x) //funkcja 1: sin(x/4)^2 -x
{ 
	return sin(x / 4.0) * sin(x / 4.0) - x; 
} 

double f2(double x) //funkcja 2: tg(2x)-x-1 
{ 
	return tan(2.0 * x) - x - 1.0; 
} 

double f1poch(double x) //pochodna funkcji 1: (1/4)*(sin(x/2)-1)
{ 
	return (1.0 / 4.0) * (sin(x / 2.0)) - 1; 
}

double f2poch(double x) //pochodna funkcji 2: -1 + 2/(cos(2x)^2)
{ 
	return -1.0 + 2.0 / (cos(2.0 * x) * cos(2.0 * x)); 
}

double f1_picard(double x) //funkcja przekształcona do metody Picarda: sin(x/4)^2
{ 
	return sin(x / 4.0) * sin(x / 4.0); 
} 
double f2_picard(double x) //funkcja przekształcona do metody Picarda: tg(2x)-1
{ 
	return tan(2.0 * x) - 1.0; 
}

double f1poch_picard(double x) //pochodna funkcji przekształconej do metody Picarda: (1/4)*sin(x/2)
{ 
	return 1.0 / 4.0 * sin(x / 2.0); 
}
double f2poch_picard(double x) //pochodna funkcji przekształconej do metody Picarda: 2/(cos(2x)*cos(2x))
{ 
	return 2.0 / (cos(2.0 * x) * cos(2.0 * x)); 
}

double Picard(function f, function f_p, function fpp, double x, int n_max, double TOLX, double TOLF) //funkcja Picard przyjmuje argumenty f-funkcja podstawowa, f_p-funkcja przekształcona dla Picarda, fpp-pochodna Picarda, x-x początkowy, n_max- maksymalna liczba iteracji, TOLX, TOLF- zadane tolerancje błędu
{
	if (fabs(fpp(x)) >= 1) //sprawdzenie zbieżności, jeśli wartosć bezwzględna z pochodnej jest >1, to funkcja jest rozbieżna i nie da się jej tak liczyć
	{
		cout << "Funkcja rozbiezna, nie da sie uzyc na niej metody Picarda.";
		return 0;
	}
	double estymator = 0;
	double residuum = 0;
	double przyblizenie_nowe = x;
	cout << "i\t wartosc przyblizona \t\t residuum \t\t\t estymator bledu"<<endl;

	for (int i = 0; i < n_max; i++) //iteracja, dopóki i < maksymalnej liczby operacji
	{
		cout << i<<"\t";
		przyblizenie_nowe = f_p(przyblizenie_nowe); //nowe przyblizenie ma wartość funkcji od poprzedniego nowego przybliżenia, ponieważ prosta ma równanie y=x
		cout << przyblizenie_nowe << "\t\t";

		estymator = fabs(przyblizenie_nowe - x); //wyliczamy estymator błędu
		x = przyblizenie_nowe; //nowe przybliżenie staje się naszym x
		residuum = fabs(f(x)); //liczymy residuum

		cout << residuum << "\t\t" << estymator << endl;

		if ((residuum <= TOLF) or (estymator <= TOLX)) //inne warunki zakończenia iteracji
			break;
	}
	return przyblizenie_nowe;
}

double Bisekcji(function f, double a, double b, int n_max, double TOLX, double TOLF) //f to funkcja, a-początek sprawdzanego przedziału, b- koniec, n_max- maksymalna liczba iteracji, TOLX, TOLF- zadane tolerancje błędu
{
	double x = 0, estymator=0; //inicjalizacja zmiennej do obliczania środka przedziału
	if ((f(a) < 0 and f(b) < 0) or (f(a) > 0 and f(b) > 0)) //warunki sprawdzajace, czy wartości funkcji od podanych wartości a i b są różnych znaków
	{
		cout << "Niepoprawnie dobrany przedzial" << endl;
		return EXIT_FAILURE;
	}
	cout << "i \t\t a \t\t\t b\t\t\t x\t\t\t residuum\t\t estymator" <<endl;
	for (int i = 0; i < n_max; i++) 
	{
		x = (a + b) / 2.0; //wyliczanie srodka przedzialu
		estymator = (b - a) / 2.0; //wyliczanie estymatora błędu
		cout << i << "\t "<< a << "\t" << b << "\t" << x << "\t" << fabs(f(x)) << "\t" << fabs(estymator) << endl;
		if ((f(a) < 0 and f(x) > 0) or (f(x) < 0 and f(a) > 0)) 
		{
			b = x;
		}
		else 
		{
			a = x;
		}
		if ((fabs(f(x)) <= TOLF) or (fabs((b - a) / 2) <= TOLX)) //inne warunki zakończenia iteracji
			break; 
	}
}

double Newtona(function f, function fp, double x, int n_max, double TOLX, double TOLF) //f to funkcja, fp to jej pochodna, x to punkt od którego rozpoczynamy poszukiwania
{
	double x0 = x, x1, estymator = 0;
	cout << "i\t\t x1 \t\t\t residuum \t\t estymator"<< endl;
	for (int i = 0; i < n_max; i++) 
	{
		x1 = x0 - (f(x0) / fp(x0));
		estymator = fabs(x0 - x1);
		x0 = x1;
		cout << i << "\t" << x1 << "\t" << f(x0) << "\t" << estymator << endl;
		if (fabs(f(x0)) <= TOLF or estymator <= TOLX) //inne warunki zakończenia iteracji
			break;
	}
	return 0;
}

double Siecznych(function f, double x0, double x1, int n_max, double TOLX, double TOLF) //x0 i x1 to dwa początkowe punkty rozpoczęcia wyliczania siecznych
{
	double x2, estymator = 0; //nowy x
	cout << "i\t\t nowy x \t\t estymator\t\t residuum" << endl;
	for (int i = 0; i < n_max; i++) 
	{
		x2 = x1 - f(x1) / ((f(x1) - f(x0)) / (x1 - x0));
		estymator = fabs(x2 - x1);
		cout << i<<"\t"<< x2 << "\t" << fabs(estymator) << "\t" <<fabs(f(x2)) << endl;
		x0 = x1; //przesunięcie xów na nowe
		x1 = x2;

		if (fabs(f(x2)) <= TOLF or estymator <= TOLX) 
			break;
	}
	return x2;
}


int main() 
{
	cout.setf(ios::scientific);
	cout.precision(16);
	const int max_iteracja = 31;
	double blad = 1e-10;

	cout << "Rownanie sin(x/4)^2-x metoda:" << endl;
	cout << "Picarda:" << endl;
	Picard(f1, f1_picard, f1poch_picard, 0.5, max_iteracja, blad, blad);
	cout << endl << endl << "Bisekcji:" << endl;
	Bisekcji(f1, -0.5, 0.9, max_iteracja, blad, blad);
	cout << endl << endl << "Newtona" << endl;
	Newtona(f1, f1poch, -0.3, max_iteracja, blad, blad);
	cout << endl << endl << "Siecznych" << endl;
	Siecznych(f1, -0.5, 0.6, max_iteracja, blad, blad);

	cout << endl << endl << "Rownanie tg(2x)-x-1 metoda:"<< endl;
	cout << "Picarda:" << endl;
	Picard(f2, f2_picard, f2poch_picard, 0.5, max_iteracja, blad, blad);
	cout << endl << endl << "Bisekcji:" << endl;
	Bisekcji(f2, 0.4, 0.5, max_iteracja, blad, blad);
	cout << endl << endl << "Newtona" << endl;
	Newtona(f2, f2poch, 0.6, max_iteracja, blad, blad);
	cout << endl << endl << "Siecznych" << endl;
	Siecznych(f2, 0.4, 0.5, max_iteracja, blad, blad);

	return 0;
}
