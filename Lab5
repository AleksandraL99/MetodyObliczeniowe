#include<iostream>
#include <fstream>
#include <cmath>


void wM(double** tab, int k, int l); 	//funkcja do wyświetlania macierzy
void wW(double* wek, int k);	//funkcja do wyświetlania macierzy
void LU(double **A, double** L, double ** U, int n, int *w);	//funkcja do eliminacji Gaussa
void wektorb(double *y, double *b, double **L, int n, int *tab); //funkcja do przekształcania wektora b
void wektorx(double *x, double *y, double **U, int n);	//funkcja do obliczania wektora x

using namespace std;

fstream wyniki;
int main()
{


	fstream dane;
	dane.open("dane5.txt", ios::in); //otwarcie pliku z danymi
	wyniki.open("Lab5- wyniki.txt", ios_base::out); //otwarcie pliku do zapisu

	int n;  //zmienna przechowująca rozmiar macierzy, zapisana w pliku z danymi w pierwszym wierszu
	double** A, ** U, ** L; //tablice dwuwymiarowe przechowujące macierze
	double *x,*y,*b; //tablice przechowujące wektory
	if (dane.good() != true || wyniki.good() != true) //sprawdzenie poprawności otworzenia plików
	{
		cout << "Nie otworzono pliku  " << endl;
		wyniki << "Nie otworzono pliku " << endl;
		return 1;
	}


	double t; //zmienna do łatwiejszego wczytywania macierzy
	dane >> n;	//wczytanie rozmiaru macierzy
	int tab[n]; //tablica pomocnicza do zapisywania przestawień wierszy
	for(int i=0;i<n;i++) 
		tab[i]=i;
	A = new double* [n]; //ustawienie pierwszego wymiaru macierzy
	L = new double* [n];
	U = new double* [n];
	for (int i = 0; i < n; i++) 
	{
		A[i] = new double[n]; //ustawienie drugiego wymiaru macierzy
		L[i] = new double[n];
		U[i] = new double[n];

		for (int j = 0; j < n; j++) 
		{
			dane >> t; 	//wczytanie danych, w celu oszczędności zasobów wczytanie danych raz i przechowanie ich w zmiennej
			A[i][j] = t;
			U[i][j] = t;
			L[i][j] = 0;
		}
	}


	x= new double[n]; //utworzenie wektorów o rozmiarze n
	y= new double[n];
	b = new double[n];

	for (int i = 0; i < n; i++) //wczytanie danych do wektora b, wyzerowanie wektorów y i x
	{
		dane >> b[i];
		x[i] = 0;
		y[i] = 0;
	}

	LU(A,L,U,n,tab); //wykonanie przekształcenia Gaussa na macierzy
	cout<<"Macierz A"<<endl;
	wyniki<<"Macierz A"<<endl;
	wM(A, n, n); //wyświetlenie macierzy A
	cout<<"Macierz U"<<endl;
	wyniki<<"Macierz U"<<endl;
	wM(U, n, n); //wyświetlenie macierzy U
	cout<<"Macierz L"<<endl;
	wyniki<<"Macierz L"<<endl;
	wM(L, n, n); //wyświetlenie macierzy L
	cout<<"Wektor b"<<endl;
	wyniki<<"Wektor b"<<endl;
	wW(b, n); //wyświetlenie wektora b
	
	wektorb(y,b,L,n,tab); //przekształecnia wektora b
	cout<<endl;
	wyniki<<endl;
	wektorx(x,y,U,n); //wyznaczanie wyników
	wW(y, n);
	cout<<"Rozwiazanie: "<<endl;
	wyniki<<"Rozwiazanie: "<<endl;
	wW(x, n); //wyświetlenie rozwiązania

	dane.close(); //zamknięcie plików
	wyniki.close();
	return 0;
}

void wM(double** tab, int k, int l)
{

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < l; j++) 
		{
			cout << tab[i][j] << " ";
			wyniki << tab[i][j] << " ";
		}
		cout << endl;
		wyniki<<endl;
	}
	cout << endl;
	wyniki<<endl;
}
void wW(double* wektor, int k)
{

	for (int i = 0; i < k; i++) 
	{
		cout << wektor[i] << " ";
		wyniki<<wektor[i] << " ";
	}
	cout << endl;
	wyniki<<endl;
}
void LU(double **A, double** L, double ** U, int n, int *w)
{
	for (int i = 0; i < n ; i++)
	{
		cout<<"U"<<endl;
		wyniki<<"U"<<endl;
		wM(U, n, n);
		cout<<"L"<<endl;
		wyniki<<"L"<<endl;
		wM(L, n, n);

		if (U[i][i] == 0) //fragment do zamiany wierszy w przypadku gdy na przekątnej pojawi się 0
		{
			int p = i;
			int obecny = p;
			double maxi=0; //początkowa wartość minimalna
			while (p < n) 
			{
				if (fabs(U[p][i]) > maxi && U[p][i] != 0) //szukanie wiersza z największa wartością bezwzględną
				{
					maxi = U[p][i];
					obecny = p;
				}
				p++;
			}
			double* temp = U[i]; //zamiana wierszy macierzy U
			U[i] = U[obecny];
			U[obecny] = temp;
			
			temp = L[i];	//zamiana wierszy macierzy L
			L[i] = L[obecny];
			L[obecny] = temp;
				
				
			double z=w[i];	//zamiana wartości tablicy pomocniczej
			w[i]=w[obecny];
			w[obecny]=z;	
		}

		L[i][i]=1; //ustawienie jedynek na przekątnej macierzy L

		for (int k = i + 1; k < n; k++) //wyliczania wartości z wzorów
		{
			double wynik = U[k][i] / U[i][i]; 

			L[k][i] = wynik;

			for (int j = 0; j <= n; j++) 
			{
	
				U[k][j] =U[k][j] - wynik * U[i][j]; 
			}			
		}
	}
}
void wektorb(double *y, double *b, double **L, int n, int *tab)
{
	for(int i=0;i<n;i++) 
	{
		if(tab[i] != i) //jeśli w tablicy pomocniczej wartości nie są równe indeksom, zamień również kolejność elementów w wektorze b
		{
			double z=b[i];
			b[i]=b[tab[i]];
			b[tab[i]]=z;
			
			int v=tab[i];
			tab[i]=i;
			tab[v]=v;
		}
	}


	y[0] = b[0]; 
	for (int i = 1; i < n; i++) //przekształcenia wektora b w y
	{
		y[i] = b[i];
		for (int j = 0; j < i; j++) 
		{
			y[i] = y[i] -L[i][j] * y[j];
			
		}
	}
}
void wektorx(double *x, double *y, double **U, int n)
{
	x[n - 1] = y[n - 1] / U[n - 1][ n - 1];
	for (int i = n - 1; i >= 0; i--) //wyliczanie rozwiązania, zaczynając od ostatniego elementu
	{
		x[i] = y[i];
		for (int j = i + 1; j < n; j++) 
			x[i] = x[i] - U[i][j] * x[j];
		x[i] = x[i] / U[i][i];
		
	}
}
