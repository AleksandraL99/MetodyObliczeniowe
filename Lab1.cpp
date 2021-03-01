#include<iostream>
#include <conio.h>
#include<cfloat>
using namespace std;
//Zadanie 1
int main(int argc, char** argv) 
{
	int f = 0;				// zmienna do liczenia bitów mantysy do float
	float ef;				//epsilon maszynowy do float 

	ef = 1.0f;
	while ((ef/2.0f + 1.0f) > 1.0f) 
	{
		ef *= 0.5f;
		f++;
	}
	cout << "Float"<<endl<<"Liczba bitow mantysy: " << f << endl<< "Epsilon: " << ef << endl<< endl;

	int d = 0;				// zmienna do liczenia bitów mantysy do double
	double ed;				//epsilon maszynowy do epsilon

	ed = 1.0L;
	while ((ed/2.0 + 1.0) > 1.0) {
		ed /= 2.0;
		d++;
	}
	cout << "Double" << endl << "Liczba bitow mantysy: " << d << endl << "Epsilon: " << ed << endl;
}
