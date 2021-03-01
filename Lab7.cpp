#include<iostream>
#include <fstream>
#include <cmath>

using namespace std;
#define TOLF 10e-10 //ustawienie tolerancji residuum
#define TOLX 10e-10 //ustawienie tolerancji estymatora
#define iteracje 30 //ustawienie liczby iteracji

fstream wyniki; // plik wynikowy

void jacobiego(double** A, double* b, double* x, int n); //funkcja do obliczania metodą Jacobiego
void gaussaSeidela(double** A, double* b, double* x, int n); //funkcja do obliczania metodą Gaussa-Seidela
void sor(double** A, double* b, double* x, double omega, int n); //funkcja do obliczania metodą SOR

void przyblizeniePoczatkowe(double* x, int n) //funkcja nadające wektorowi x zadane początkowe przybliżenie, równe w tym przypadku 2
	{
		for (int i = 0; i < n; i++)
			x[i] = 2;
	}
	
void wypiszMacierz(double** A, double n) //funkcja do wypisywania macierzy
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			cout << A[i][j] << " ";
			wyniki << A[i][j] << " ";
		}
		cout << endl;
		wyniki << endl;
	}
	cout << endl;
}
	void wypiszWektor(double* wektor, double n) //funkcja do wyisywania wektorów
	{
		for (int i = 0; i < n; i++)
		{
			cout << wektor[i] << "  ";
			wyniki << wektor[i] << "  ";
		}
	}

double maximum(double *tab, int n) //funkcja znajdująca największą wartość w wektorze/tablicy
{
	double a=tab[0];
	for(int i=1;i<n;i++)
		if(tab[i]>a)
			a = tab[i];
	return a;
}

int main()
{
	fstream dane; //plik z danymi wejściowymi
	dane.open("dane7.txt", ios::in); //otwarcie pliku z danymi
	wyniki.open("Lab7- wyniki.txt", ios_base::out); //otwarcie pliku do zapisu wyników

	cout << scientific; //ustawienie precyzji
	wyniki << scientific;
	cout.precision(8);
	
	int static n = 4; //rozmiar macierzy
	double* x, * b; //deklarujemy wektory b i x
	double** A; //deklarujemy macierz A

	x = new double [n]; 
	b = new double [n];
	A = new double* [n];
	
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n]; //ustawienie drugiego wymiaru macierzy

		for (int j = 0; j < n; j++)
		{
			dane >> A[i][j]; //wczytujemy dane do macierzy A
		}
	}
	
	for(int j = 0;j<n;j++)
		dane >> b[j]; //wczytujemy dane do wektora b


	wypiszMacierz(A, n); //w celu sprawdzenia poprawności wczytania wypisujemy macierz A
	cout << endl;
	wyniki << endl;
	wypiszWektor(b,n); //w celu sprawdzenia poprawności wczytania wypisujemy wektor b
	cout << endl;
	wyniki << endl;
	
	przyblizeniePoczatkowe(x, n); //nadajemy przybliżenie początkowe wektorowi x
	jacobiego(A, b, x, n); //obliczamy wynik metodą Jacobiego
	cout << endl;
	wyniki << endl;
	
	przyblizeniePoczatkowe(x, n);
	gaussaSeidela(A, b, x, n); //obliczamy wynik metodą Gaussa-Seidela
	cout << endl;
	wyniki << endl;

	przyblizeniePoczatkowe(x, n);
	double omega = 1.0 / 2.0;
	sor(A, b, x, omega, n); //obliczamy wynik metodą SOR
	
	return 0;
	wyniki.close();
	dane.close();
}

void jacobiego(double** A, double* b, double* x, int n)
{
	cout << "Metoda Jacobiego" << endl;
	wyniki << "Metoda Jacobiego" << endl;
	int licznik = 0;
	double estymator[n], reziduum[n];	
	double  est= 10, res = 10;
	double nowyx[n], suma;
	cout << "Iteracja \t x1 \t\t x2 \t\t x3 \t\t x4 \t\t Reziduum: \t Epsilon: "<< endl;
	wyniki << "Iteracja \t x1 \t\t x2 \t\t x3 \t\t x4 \t Reziduum: \t Epsilon: "<< endl;
	
	for(licznik = 0; licznik < iteracje; licznik++) //tworzymy pętle główną, której ograniczeniem jest liczba iteracji
	{
		for (int i = 0; i < n; i++) 
		{
			suma = 0.0;
			for (int j = 0; j < n; j++) //pętla w pętli, żeby przeiterować po wszystkich elementach macierzy
			{
				if (i != j) 
				{
					suma = suma + x[j] * A[i][j]; //L+U, czyli bez wyrazów na przekątnej
				}
			}
			nowyx[i] = (b[i] - suma) / A[i][i]; //przekszatłcamy wzór do postaci x[n] = (b-(L+U)*x[n-1])/D
		}


		for (int i = 0; i < n; i++) 
		{
			reziduum[i] = 0;
			estymator[i] = fabs(nowyx[i] - x[i]); //wyliczamy estymator i residuum

			for (int j = 0; j < n; j++) 
			{
				reziduum[i] = reziduum[i] + A[i][j] * x[j]; 
			}
			reziduum[i] = fabs(reziduum[i] - b[i]); 


			x[i] = nowyx[i]; //zamianiamy wartości w wektorze x na nowy x
		}

		est = maximum(estymator, n); //znajdujemy największą wartość estymatora i residuum
		res = maximum(reziduum, n);
		
		cout << licznik<<"\t"; //wypisujemy wartości
		wyniki << licznik<<"\t"; 
		wypiszWektor(x, n);
		cout <<"\t"<< res << "\t"<<est << endl;
		wyniki <<"\t"<< res << "\t"<<est << endl;
		
		if(est < TOLX || res < TOLF) //sprawdzamy inne kryteria zakończenie iteracji
			break;
		
	}
}
void gaussaSeidela(double** A, double* b, double* x, int n)
{
	cout << "Metoda Gaussa-Seidela" << endl;
	wyniki << "Metoda Gaussa-Seidela" << endl;
	int licznik = 0;
	double estymator[n], reziduum[n];	
	double  est= 1, res = 1;
	double nowyx[n], suma;
	cout << "Iteracja \t x1 \t\t x2 \t\t x3 \t\t x4 \t\t Reziduum: \t Epsilon: "<< endl;
	wyniki << "Iteracja \t x1 \t\t x2 \t\t x3 \t\t x4 \t Reziduum: \t Epsilon: "<< endl;
	for(licznik = 0; licznik < iteracje; licznik++) //tworzymy pętle główną, której ograniczeniem jest liczba iteracji
	{
		for (int i = 0; i < n; i++) 
		{
			suma = 0.0;
			for (int j = 0; j < n; j++) 
			{
				if (i != j) 
				{
					suma = suma + x[j] * A[i][j];
				}
			}

			nowyx[i] = x[i];
			x[i] = (b[i] - suma) / A[i][i]; //wzór jak samo przekształcony jak Jacobiego, ale wartości tablicy x są zmieniane co iteracje wewnętrznej pętli
			estymator[i] = fabs(nowyx[i] - x[i]);
		}


		for (int i = 0; i < n; i++) 
		{
			reziduum[i] = 0;
			for (int j = 0; j < n; j++) 
			{
				reziduum[i] = reziduum[i] + A[i][j] * x[j];
			}
			reziduum[i] = fabs(reziduum[i] - b[i]);
		}

		est = maximum(estymator, n);
		res = maximum(reziduum, n);

		cout << licznik<<"\t";
		wyniki << licznik<<"\t";
		wypiszWektor(x, n);
		cout <<"\t"<< res << "\t"<<est << endl;
		wyniki <<"\t"<< res << "\t"<<est << endl;
		
		if(est < TOLX || res < TOLF) //sprawdzamy inne kryteria zakończenie iteracji
			break;
	}
}

void sor(double** A, double* b, double* x, double omega, int n) 
{
	cout << "Metoda SOR" << endl;
	wyniki << "Metoda SOR" << endl;
	int licznik = 0;
	double estymator[n], reziduum[n];	
	double  est= 1, res = 1;
	double nowyx[n], suma=0;
	cout << "Iteracja \t x1 \t\t x2 \t\t x3 \t\t x4 \t\t Reziduum: \t Epsilon: "<< endl;
	wyniki << "Iteracja \t x1 \t\t x2 \t\t x3 \t\t x4 \t Reziduum: \t Epsilon: "<< endl;
	for(licznik = 0; licznik < iteracje; licznik++) //tworzymy pętle główną, której ograniczeniem jest liczba iteracji	
	{
		for (int i = 0; i < n; i++) 
		{
			suma = 0.0;
			for (int j = 0; j < n; j++) 
			{
				if (i != j) 
				{
					suma = suma + x[j] * A[i][j];
				}
			}

			nowyx[i] = x[i];
			x[i] = (1.0 - omega) * x[i] + (omega * (b[i] - suma) / A[i][i]); //wyliczenia ze wzorów
			
			estymator[i] = fabs(nowyx[i] - x[i]);
		}


		for (int i = 0; i < n; i++) //wyliczanie residuum 
		{
			reziduum[i] = 0;
			for (int j = 0; j < n; j++) 
			{
				reziduum[i] = reziduum[i] + A[i][j] * x[j];
			}
			reziduum[i] = fabs(reziduum[i] - b[i]);
		}

		est = maximum(estymator, n); //znajdujemy największą wartość estymatora i residuum
		res = maximum(reziduum, n);


		cout << licznik<<"\t";
		wyniki << licznik<<"\t";
		wypiszWektor(x, n);
		cout <<"\t"<< res << "\t"<<est << endl;
		wyniki <<"\t"<< res << "\t"<<est << endl;
		
		if(est < TOLX || res < TOLF) //sprawdzamy inne kryteria zakończenie iteracji
			break;

	}
}
