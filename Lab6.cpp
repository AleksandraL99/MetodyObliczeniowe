#include<iostream>
#include <fstream>
#include <cmath>

using namespace std;

void wczytaj (fstream &plik,double **A,double *b, int n); //funkcja do wczytywania z pliku
void eliminacjaM(double** A, int n); //funkcja do przekształcenia macierzy A
void eliminacjaW(double** A, double *b, int n); //funkcja do przekształcenia wektora b
void rozwiazx(double** A, double* b, double* x, int n); //funkcja do rozwiązywania równania
fstream zapis; //plik do którego zapisujemy dane

int main()
{
	fstream dane; //plik z którego pobieramy dane
	dane.open("dane6.txt", ios::in); //otworzenie pliku z danymi
	zapis.open("Lab 6-wyniki.txt", ios_base::out); //otworzenie pliku do zapisu

	if (dane.good() != true || zapis.good() != true) //sprawdzenie poprawnosci otworzenia pliku
	{
		cout << "Blad otwarcia pliku " << endl;
		return 1;
	}

	int n;	//rozmiar macierzy
	double** A; //macierz A
	double * x, * b; //wektory x i b
	
	dane >> n;	//wczytujemy rozmiar z pliku
	
	x = new double[n]; //inicjowanie tablicy x
	b = new double[n]; //inicjowanie tablicy b

	A = new double* [n];	//inicjowanie tablicy dla macierzy A
	for (int i = 0; i < n; i++) //dodanie drugiego wymiaru
	{
		A[i] = new double[3]; 
	}

	wczytaj (dane,A,b,n); //wczytanie danych do macierzy
	cout<<"Dane poczatkowe:"<<endl;
	zapis<<"Dane poczatkowe:"<<endl;
	for (int i = 0; i < n; i++) //wypisanie danych macierzy
	{
		for (int j = 0; j < 3; j++) 
		{
			cout << A[i][j]<<" ";
			zapis << A[i][j]<<" ";
		}
		cout << endl;
		zapis <<endl;
	}
	cout << endl << endl;
	zapis <<endl<<endl;

	cout<<"Przeksztalcenia macierzy A:"<<endl;
	zapis<<"Przeksztalcenia macierzy A:"<<endl;
	eliminacjaM( A, n); //przekształcamy macierz A
	cout<<endl<<"Przeksztalcenia wektora b:"<<endl;
	zapis<<endl<<"Przeksztalcenia wektora b:"<<endl;
	eliminacjaW(A, b, n); //przekształcamy wektor b
	cout<<endl<<"Rozwiazanie:"<<endl;
	zapis<<endl<<"Rozwiazanie:"<<endl;
	rozwiazx(A, b, x, n); //wyliczamy rozwiązanie

 	dane.close(); //zamykamy pliki
	zapis.close();
	
	return 0;
}

void eliminacjaM(double** A, int n)
{	
	for (int i = 1; i < n; i++) //redukcja wyrazów, zaczynając od 2 elementu (indeks 1), ponieważ pierwszy się nie zmienia, zgodnie ze wzorem
	{
		A[i][1] = A[i][1] - A[i][0] / A[i - 1][1] * A[i - 1][2];
		for(int j=0;j<n;j++) //wyświetlanie macierzy co krok
		{
			for(int k=0;k<3;k++)
			{
				cout<<A[j][k]<<" ";
				zapis<<A[j][k]<<" ";
			}
				
			cout<<endl;
			zapis<<endl;
		}
	cout<<endl;
	zapis<<endl;
	}
}

void eliminacjaW(double** A, double* b, int n)
{
	for (int i = 1; i < n; i++)
	{
		b[i] = b[i] - A[i][0] / A[i - 1][1] * b[i - 1];
		for(int k=0;k<n;k++)  //wyświetlanie wektora co krok
		{
			cout<<b[k]<<" ";
			zapis<<b[k]<<" ";
		}
		cout<<endl;
		zapis<<endl;
	}
}

void rozwiazx(double** A, double* b, double* x, int n)
{
	x[n - 1] = b[n-1]/A[n - 1][1];
	for (int i = n - 2; i >= 0; i--)
	{
		x[i] = (b[i] - A[i][2] * x[i + 1])/A[i][1];
		for (int a = 0; a < n-1; a++)
		{
			cout << x[a] << " ";
			zapis<< x[a] << " ";
		}

		cout << endl;
		zapis<<endl;
	}
	cout<<endl<<"Rozwiazanie ostateczne:"<<endl;
	zapis<<endl<<"Rozwiazanie ostateczne:"<<endl;
	for (int a = 0; a < n-1; a++)
	{
		cout << x[a] << " ";
		zapis<< x[a] << " ";
	}

}
void wczytaj (fstream &plik,double **A,double *b, int n)
{
		string p;
		for(int j=0;j<n;j++)
		{

			for (int i=0;i<3;i++)
			{
				plik>>p;
				int x=p.find('/'); //wczytujemy łańcuchy znaków, jeśli znajdziemy ukośnik, to rozdzielamy na licznik i mianownik
				if (x!=string::npos)
				{
					string l=p.substr(0,x);
					string m=p.substr(x+1,p.length()-x);
					A[j][i]=atof(l.c_str())/atof(m.c_str()); //atof służy do zamiany z typu string na double
				}
				else
				{
					A[j][i]=atof(p.c_str()); 

				}
			}
				plik>>p;
				int x=p.find('/');
				if (x!=string::npos)
				{
					string l=p.substr(0,x);
					string m=p.substr(x+1,p.length()-x);
					b[j]=atof(l.c_str())/atof(m.c_str());
				}
				else
				{
					b[j]=atof(p.c_str());
				}			
		}
}
