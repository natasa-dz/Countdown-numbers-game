#pragma once
#include <string>
#include<iostream>
using namespace std;
#include <vector>
class MojBroj
{
public:
	int ukupanbrRundi;
	int brRunde;
	int guess_resenja;
	int pobedeIgracaA;
	int pobedeIgracaB;
	MojBroj(void);
	vector<vector<int>> data_numbers;
	vector<int> results;
	vector<int> getNumbers(int brRunde);
	void loadRounds(ifstream& inFile);
	void gameStart();
	int getSoultion(int brRunde);
	void testirajProgramZaRacunanjeIzraza();
	void testirajProgramZaGenerisanjeIzraza();
};
