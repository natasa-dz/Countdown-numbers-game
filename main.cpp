#include <iostream>
#include <vector>
#include <fstream>
#include "MojBroj.h"
//#include "Kalkulator.h"
using namespace std;

int main() {


	cout << "				>>> Dobrodosli u igru Moj broj! <<<\n";
	cout << "\n";
	cout << "1. Zapocnite igru\n";
	cout << "2. Objasnjenje pravila igre\n";
	cout << "3. Testiraj program za racunanje izraza"<<endl;
	cout << "4. Testiraj program za generisanje izraza" << endl;
	cout << "5. Izlaz\n";

	string option;
	cout << ">>> ";
	cin >> option;
	cout << " ";
	try {
		MojBroj broj;
		int choosen = stoi(option);

		if (choosen == 1) {

			cout <<"Test datoteke koje imate na raspolaganju su: \n" << endl;
			cout << "C:\\Users\\User\\source\\repos\\MojBroj\\MojBroj\\Runde.txt" <<"\n";
			cout<<"C:\\Users\\User\\source\\repos\\MojBroj\\MojBroj\\Runde1.txt" <<"\n";
			cout << "C:\\Users\\User\\source\\repos\\MojBroj\\MojBroj\\Runde2.txt" << "\n\n";
			cout << " ";
			string file_path;
			cout<<"Unesite putanju zeljene test datoteke: "<<endl;
			cout << ">>>   ";
			cin >> file_path;
			ifstream inFile(file_path);
			cout << "\n";
			if (!inFile.is_open()) {
				cerr << "Unable to open file!";
				exit(1);   // call system to stop
			}

			
			
			broj.loadRounds(inFile);
			broj.gameStart();
		}
			else if (choosen == 2) {
					cout << "					>>> UPUTSTVO <<<\n";
					cout << "\n	Pronadjite resenje za ucitan trocifren broj sa ulaza: na raspolaganju imate 6\n	nasumicno generisanih brojeva(4 iz skupa jednocifrenih brojeva i 2 iz skupa\n	dvocifrenih brojeva), operacije: +, -, *, / , kao i zagrade.Rezultat mora biti tacan, ili\n	ukoliko to nije moguce, sto blizi zadatom trocifrenom broju.\n";
					cout << "\n\n";
					main();
		}
			else if (choosen==3) {
			cout << ">>>     TESTIRANJE PROGRAMA ZA RACUNANJE IZRAZA     <<<< "<<endl;
			broj.testirajProgramZaRacunanjeIzraza();



		}
			else if(choosen == 4) {
			cout << ">>>     TESTIRANJE PROGRAMA ZA GENERISANJE IZRAZA     <<<< " << endl;
			broj.testirajProgramZaGenerisanjeIzraza();
		}
			else if (choosen == 5) {
					exit;}
			else {
					cout << "Greska! Izabrali ste nepostojecu.\n";
				}
		}catch (const invalid_argument& e) {cout << "Greska! Izabrali ste nepostojecu opciju.\n";}



	return 0;

}