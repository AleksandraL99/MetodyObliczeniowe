#include <iostream>
#include <math.h>
#include <fstream>
#define PI 3.141592653589793238462643383279502884
#define ilosc 100
#define LWYNIKOW 8

using namespace std;

template<typename T> inline T f(T x)  //funkcja podstawowa sin(x)
{
	return sin(x);
}
template<typename T> inline T df(T x) //pochodna funkcji podstawowej cos(x)
{
	return cos(x);
}
template <typename T> inline T roznicaProgresywna2p(T x, T h)  //szablon do obliczania  dwupunktowej różnicy progresywnej
{
	return (f(x + h) - f(x)) / h;
}
template <typename T> inline T roznicaCentralna2p(T x, T h) //szablon do obliczania  dwupunktowej różnicy centralnej
{
	return (f(x + h) - f(x - h)) / (2 * h);
}
template <typename T> inline T roznicaWsteczna2p(T x, T h) //szablon do obliczania  dwupunktowej różnicy wstecznej 
{
	return (f(x) - f(x - h)) / h;
}

template <typename T> inline T roznicaProgresywna3p(T x, T h) //szablon do obliczania  trzypunktowej różnicy progresywnej
{
	return (-3.0 / 2.0 * f(x) + 2 * f(x + h) - 1.0 / 2.0 * f(x + h + h)) / (h);
}
template <typename T> inline T roznicaWsteczna3p(T x, T h) //szablon do obliczania  trzypunktowej różnicy wstecznej
{
	return (3.0 / 2.0 * f(x) - 2.0 * f(x - h) + 1.0 / 2.0 * f(x - h - h)) / (h);
}

template <typename T> T** roznicaOrazBlad(T** tab)
{ //szablon służący do wyznaczania różnic między pochodną liczoną z różnic progresywnych, centralnych oraz wstecznych, a tą liczoną z cos(x)
	T** blad = new T * [ilosc]; //tworzymy tablicę do obliczania błędów
	T h = 0.2; //inicjujemy pierwszy krok
	T poczatek = 0; //początek przedziału
	T koniec = PI / 2; //koniec przedziału
	T srodek = (poczatek + koniec) / 2; //środek przedziału
	cout << srodek << endl;

	for (int i = 0; i < ilosc; i++) //pętla licząca błędy, wykonująca się zadaną ilosć razy
	{

		tab[i] = new T[LWYNIKOW]; //dodawnie drugiego wymiaru, który ma rozmiar taki, jak wiele wyników będziemy zapisywać
		blad[i] = new T[LWYNIKOW];

		tab[i][0] = roznicaProgresywna2p(poczatek, h); //obliczenie pochodnej z różnicy progresywnej i zapisanie wyniku do tablicy
		blad[i][0] = fabs(tab[i][0] - df(poczatek)); //obliczenie błędu bezwzględnego przez wartość bezwzględną z różnicy wyników prosto z pochodnej i z różnicy progresywnej

		tab[i][1] = roznicaCentralna2p(srodek, h);
		blad[i][1] = fabs(tab[i][1] - df(srodek));

		tab[i][2] = roznicaWsteczna2p(koniec, h);
		blad[i][2] = fabs(tab[i][2] - df(koniec));

		tab[i][3] = roznicaProgresywna3p(poczatek, h);
		blad[i][3] = fabs(tab[i][3] - df(poczatek));

		tab[i][4] = roznicaProgresywna3p(srodek, h);
		blad[i][4] = fabs(tab[i][4] - df(srodek));

		tab[i][5] = roznicaWsteczna3p(srodek, h);
		blad[i][5] = fabs(tab[i][5] - df(srodek));

		tab[i][6] = roznicaWsteczna3p(koniec, h);
		blad[i][6] = fabs(tab[i][6] - df(koniec));

		blad[i][7] = h;

		h = h / (1.5); //zmniejszamy krok
		for (int r = 0; r < 7; r++)
			cout << blad[i][r] << " ";
		cout << endl;
	}
	cout << endl<< "Rzedy dokladnosci: "<<endl; //wyznaczamy rzędy dokładności z tangensa nachylenia wykresu z logarytmów dziesiętnych 
	for (int i = 0; i < 7; i++) {
		cout << (log10(blad[1][i]) - log10(blad[0][i])) / (log10(blad[1][7]) - log10(blad[0][7])) << endl;
	}
	return blad; //zwracana jest tablica z błędami, którą później wykorzystamy do dalszych obliczeń
}


template <typename T> void zapiszDoPliku(T** tab, string nazwa) //szablon służący do zapisu do pliku
{
	fstream plik; //tworzymy plik
	plik << scientific;
	plik.precision(16); //ustalamy precyzję
	plik.open(nazwa, ios::out);
	if (plik.good() != true) //sprawdzamy poprawnosć otwarcia pliku
	{
		cout << "Blad otwarcia pliku " << endl;
		return;
	}
	T h = 0.2; //krok
	for (int i = 0; i < ilosc; i++) //zapisujemy do pliku logarytmy z uzyskanych wartości
	{
		plik << log10(h) << " ";
		for (int j =0; j< LWYNIKOW; j ++)
		{
			if (fabs(log10(tab[i][j])) > 0)
				plik << log10(tab[i][j]) << " ";
			else
				plik << "0 ";
		}
		plik << endl;
		h = h / 1.5; //analogicznie zmieniamy krok
	}
	plik << endl << "Rzedy dokladnosci: "<<endl;
	for (int i = 0; i < 7; i++) 
	{
		plik << (log10(tab[1][i]) - log10(tab[0][i])) / (log10(tab[1][7]) - log10(tab[0][7])) << endl;
	}
	plik.close(); //zamykamy plik
}

int main()
{
	cout << scientific;
	cout.precision(10); //ustalamy precyzję

	float** pochodnaFloat = new float* [ilosc]; //tworzymy tablice dwuwymiarową typu float
	pochodnaFloat = roznicaOrazBlad(pochodnaFloat);
	zapiszDoPliku(pochodnaFloat, "pochodnaFloat.txt"); //zapisujemy wyniki do pliku

	double** pochodnaDouble = new double* [ilosc];  //tworzymy tablice dwuwymiarową typu double
	pochodnaDouble = roznicaOrazBlad(pochodnaDouble);
	zapiszDoPliku(pochodnaDouble, "pochodnaDouble.txt"); //zapisujemy wyniki do pliku

	cout << "Zakonczono.\n";
}
