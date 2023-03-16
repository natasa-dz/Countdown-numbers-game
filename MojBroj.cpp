#include <string>
#include<iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;
#include <vector>
#include "MojBroj.h"
#include <algorithm>
#include <set>

//#include "Kalkulator.h"

vector<int> numbers;
string line;

MojBroj::MojBroj(){

    ukupanbrRundi = 0; 
    brRunde = 0; 
    guess_resenja = 0;
    
}


//-------------------- UCITAVANJE ULAZNE DATOTEKE 
void MojBroj::loadRounds(ifstream& inFile)
{
	
	while (getline(inFile, line)) {

		vector<int> row;
		vector<int> numberOptions;

		string token;
		stringstream ss(line);


		while (getline(ss, token, ',')) {
			int value = stoi(token);

			row.push_back(value);
		}

		for (int i = 0; i < row.size()-1; i++) {
				numberOptions.push_back(row[i]);
		}

		results.push_back(row.back());
		data_numbers.push_back(numberOptions);

			
		

	}
	ukupanbrRundi=results.size();


	inFile.close();
}

int MojBroj::getSoultion(int brRunde)
{
	int result = 0;

	result=results[brRunde];
	
	return result;
}

vector<int> MojBroj::getNumbers(int brRunde)
{
	vector<int> numbers;

	numbers = data_numbers[brRunde];


	return numbers;
}




//---------------------------------- KALKULATOR KOJI SE KORISTI PRILIKOM GENERISANJA IZRAZA
vector<string> Tokenize(string& expression, unordered_map<string, int>& opMap)
{
    vector<string> tokens = {};
    string temp = "";
    for (char c : expression)
    {
        if (c == ' ') continue;
        else if (opMap.find(string(1, c)) != opMap.end())
        {
            if (temp != "")
                tokens.push_back(temp);
            temp = "";
            tokens.push_back(string(1, c));
        }
        else temp += c;
    }
    if (temp != "")
        tokens.push_back(temp);

    return tokens;
}

vector<string> InfixToPostfix(vector<string>& infix, unordered_map <string, int>& opMap)
{
    vector<string> postfix = {};
    vector<string> stack = { "(" };
    infix.push_back(")");
    for (string token : infix)
    {
        //cout << token << endl;
        if (opMap.find(token) == opMap.end()) // oparand
            postfix.push_back(token);
        else if (token == "(")
            stack.push_back(token);
        else if (token == ")")
        {
            while (stack.back() != "(")
            {
                postfix.push_back(stack.back());
                stack.pop_back();
            }
            stack.pop_back();
        }
        else // operator
        {
            while (stack.size() > 0 && opMap[token] <= opMap[stack.back()])
            {
                postfix.push_back(stack.back());
                stack.pop_back();
            }
            stack.push_back(token);
        }
    }

    return postfix;
}

float CalculatePostfix(vector<string>& postfix, unordered_map<string, int>& opMap)
{
    vector<float> evaluationStack = {};
    for (string token : postfix)
    {
        if (opMap.find(token) != opMap.end())
        {
            float n1 = evaluationStack[evaluationStack.size() - 1];
            float n2 = evaluationStack[evaluationStack.size() - 2];

            switch (token[0])
            {
            case '+':
                n2 = n2 + n1;
                break;
            case '-':
                n2 = n2 - n1;
                break;
            case '*':
                n2 = n2 * n1;
                break;
            case '/':
                n2 = n2 / n1;
                break;
            }
            evaluationStack.pop_back();
            evaluationStack.pop_back();
            evaluationStack.push_back(n2);
        }
        else
        {
            evaluationStack.push_back(atof(token.c_str()));
        }
    }
    return evaluationStack[0];
}







// --------------------------- KALKULATOR ZA KORISNIKOVO RESENJE

vector<string> Tokenize1(string& expression, unordered_map<string, int>& opMap)
{
    vector<char> vektor = { '0', '1', '2', '3', '4', '5','6','7', '8','9', '(', ')', '*', '/', '+', '-' };
    int openParen = count(expression.begin(), expression.end(), '(');
    int closeParen = count(expression.begin(), expression.end(), ')');
    if (openParen != closeParen)
        throw runtime_error("Niste zatvorili zagrade u Vasem izrazu! Pokusajte ponovo.");
    vector<string> tokens = {};
    string temp = "";

    for (char c : expression)
    {
        if (!(count(vektor.begin(), vektor.end(), c)))
            throw runtime_error("Uneli ste nedozvoljeni karakter! Pokusajte ponovo!");
        if (c == ' ') continue;
        else if (opMap.find(string(1, c)) != opMap.end())
        {
            if (temp != "")
                tokens.push_back(temp);
            temp = "";
            tokens.push_back(string(1, c));
        }
        else temp += c;
    }
    if (temp != "")
        tokens.push_back(temp);

    return tokens;
}

vector<string> InfixToPostfix1(vector<string>& infix, unordered_map <string, int>& opMap)
{
    vector<string> postfix = {};
    vector<string> stack = { "(" };
    infix.push_back(")");
    bool last_token_is_operator = false;
    for (string token : infix)
    {
        //cout << token << endl;
        if (opMap.find(token) == opMap.end()) // oparand
            postfix.push_back(token);
        else if (token == "(")
            stack.push_back(token);
        else if (token == ")")
        {
            while (stack.back() != "(")
            {
                postfix.push_back(stack.back());
                stack.pop_back();
            }
            stack.pop_back();
        }
        else // operator
        {
            while (stack.size() > 0 && opMap[token] <= opMap[stack.back()])
            {
                postfix.push_back(stack.back());
                stack.pop_back();
            }
            stack.push_back(token);
        }
    }

    return postfix;
}

//float CalculatePostfix1(vector<string>& postfix, unordered_map<string, int>& opMap)
//{
//    vector<float> evaluationStack = {};
//    bool last_token_is_operator = false;
//    for (string token : postfix)
//    {
//        if (opMap.find(token) != opMap.end())
//        {
//            float n1 = evaluationStack[evaluationStack.size() - 1];
//            float n2 = evaluationStack[evaluationStack.size() - 2];
//
//
//            if (token[0] == '/') {
//                if (n1 == 0)
//                    throw runtime_error("Ne mozete deliti sa nulom! Pokusajte ponovo!");
//            }
//            switch (token[0])
//            {
//            case '+':
//                n2 = n2 + n1;
//                break;
//            case '-':
//                n2 = n2 - n1;
//                break;
//            case '*':
//                n2 = n2 * n1;
//                break;
//            case '/':
//                n2 = n2 / n1;
//                break;
//            }
//            evaluationStack.pop_back();
//            evaluationStack.pop_back();
//            evaluationStack.push_back(n2);
//        }
//        else
//        {
//            evaluationStack.push_back(atof(token.c_str()));
//        }
//    }
//    return evaluationStack[0];
//}


template <typename T>
T CalculatePostfix1(vector<string>& postfix, unordered_map<string, int>& opMap)
{
    vector<T> evaluationStack = {};
    bool last_token_is_operator = false;
    for (string token : postfix)
    {
        if (opMap.find(token) != opMap.end())
        {
            T n1 = evaluationStack[evaluationStack.size() - 1];
            T n2 = evaluationStack[evaluationStack.size() - 2];

            if (token[0] == '/') {
                if (n1 == 0)
                    throw runtime_error("Ne mozete deliti sa nulom! Pokusajte ponovo!");
            }
            switch (token[0])
            {
            case '+':
                n2 = n2 + n1;
                break;
            case '-':
                n2 = n2 - n1;
                break;
            case '*':
                n2 = n2 * n1;
                break;
            case '/':
                n2 = n2 / n1;
                break;
            }
            evaluationStack.pop_back();
            evaluationStack.pop_back();
            evaluationStack.push_back(n2);
        }
        else
        {
            T number = (T)atof(token.c_str());
            evaluationStack.push_back(number);
        }
    }
    return evaluationStack[0];
}




// pomocna f-ja kod pronalazenja izraza od strane kompjutera
bool compareExpressions(string& lhs, string& rhs, int target) {
    unordered_map<string, int> opMap = {
    { "*", 2},
    { "/", 2},
    { "+", 1},
    { "-", 1},
    { "(", -1},
    { ")", -1}, };
    vector<string> Ltokens = Tokenize(lhs, opMap); //infix : a * b

    Ltokens = InfixToPostfix(Ltokens, opMap); // postfix : a b *
    float Lresult = CalculatePostfix(Ltokens, opMap);

    vector<string> Rtokens = Tokenize(rhs, opMap); //infix : a * b
    Rtokens = InfixToPostfix(Rtokens, opMap); // postfix : a b *
    float Rresult = CalculatePostfix(Rtokens, opMap);

    return abs(Lresult - target) < abs(Rresult - target) && std::fmod(Lresult, 1) == 0 && std::fmod(Rresult, 1) == 0;
}






// ----------------------------- pronalazenje mogucih izraza-kada zagrade ne dolaze u obzir
vector<string> generateExpressionsNoParentheses(const std::vector<int>& numbers, double target) {


    std::set<std::string> expressionsSet;

    // Iterate over the possible subsets of the input numbers
    for (size_t i = 0; i < (1 << numbers.size()); ++i) {
        std::vector<int> subset;
        // Extract the current subset from the input numbers
        for (size_t j = 0; j < numbers.size(); ++j) {
            if (i & (1 << j)) {
                subset.push_back(numbers[j]);
            }
        }
        // Generate expressions using the current subset
        if (subset.size() == 1) {
            expressionsSet.insert(std::to_string(subset[0]));
        }
        else {
            for (size_t j = 1; j < subset.size(); ++j) {
                const auto leftNumbers = vector<int>(subset.begin(), subset.begin() + j);
                const auto rightNumbers = vector<int>(subset.begin() + j, subset.end());
                const auto leftExpressions = generateExpressionsNoParentheses(leftNumbers, target);
                const auto rightExpressions = generateExpressionsNoParentheses(rightNumbers, target);
                for (const auto& leftExpression : leftExpressions) {
                    for (const auto& rightExpression : rightExpressions) {
                        expressionsSet.insert(leftExpression + "+" + rightExpression);
                        expressionsSet.insert(leftExpression + "-" + rightExpression);
                        expressionsSet.insert(leftExpression + "*" + rightExpression);
                        if (rightExpression != "0") {
                            expressionsSet.insert(leftExpression + "/" + rightExpression);
                        }
                    }
                }
            }
        }
    }

    // Convert the set to a vector
    std::vector<std::string> expressions(expressionsSet.begin(), expressionsSet.end());

    // Sort the expressions by their difference from the target number
    std::sort(expressions.begin(), expressions.end(), [&](auto& lhs, auto& rhs) {
        return compareExpressions(lhs, rhs, target);
        });

    // Return only the first 30 elements of the sorted vector
    return vector<string>(expressions.begin(), expressions.begin() + std::min(expressions.size(), size_t(2700)));

}





//vector<string> generateExpressions(const std::vector<int>& numbers, int target) {
//    if (numbers.size() == 1) {
//        return { std::to_string(numbers[0]) };
//    }
//
//    else {
//        std::vector<std::string> expressions;
//
//        for (size_t i = 1; i < numbers.size(); ++i) {
//
//            const auto leftNumbers = std::vector<int>(numbers.begin(), numbers.begin() + i);
//            const auto rightNumbers = std::vector<int>(numbers.begin() + i, numbers.end());
//
//            const auto leftExpressions = generateExpressions(leftNumbers, target);
//            const auto rightExpressions = generateExpressions(rightNumbers, target);
//
//            for (const auto& leftExpression : leftExpressions) {
//
//                for (const auto& rightExpression : rightExpressions) {
//
//                    expressions.emplace_back("(" + leftExpression + "+" + rightExpression + ")");
//                    expressions.emplace_back("(" + leftExpression + "-" + rightExpression + ")");
//                    expressions.emplace_back("(" + leftExpression + "*" + rightExpression + ")");
//                    if (rightExpression != "0") {
//                        expressions.emplace_back("(" + leftExpression + "/" + rightExpression + ")");
//                    }
//                }
//            }
//        }
//
//        // Sort the expressions by their difference from the target number
//        std::sort(expressions.begin(), expressions.end(), [&](auto& lhs, auto& rhs) {
//            return compareExpressions(lhs, rhs, target);
//            });
//
//        //return expressions;
//        // Return only the first 10 elements of the sorted vector
//        return vector<string>(expressions.begin(), expressions.begin() + std::min(expressions.size(), size_t(40000)));
//    }
//
//}




//------------------------------ pronalazenje mogucih izraza-kada zagrade dolaze u obzir
vector<string> generateExpressions(const std::vector<int>& numbers, int target) {
    std::set<std::string> expressionsSet;

    // Iterate over the possible subsets of the input numbers
    for (size_t i = 0; i < (1 << numbers.size()); ++i) {
        std::vector<int> subset;
        // Extract the current subset from the input numbers
        for (size_t j = 0; j < numbers.size(); ++j) {
            if (i & (1 << j)) {
                subset.push_back(numbers[j]);
            }
        }
        // Generate expressions using the current subset
        if (subset.size() == 1) {
            expressionsSet.insert(std::to_string(subset[0]));
        }
        else {
            for (size_t j = 1; j < subset.size(); ++j) {
                const auto leftNumbers = vector<int>(subset.begin(), subset.begin() + j);
                const auto rightNumbers = vector<int>(subset.begin() + j, subset.end());
                const auto leftExpressions = generateExpressions(leftNumbers, target);
                const auto rightExpressions = generateExpressions(rightNumbers, target);
                for (const auto& leftExpression : leftExpressions) {
                    for (const auto& rightExpression : rightExpressions) {
                        expressionsSet.insert("(" + leftExpression + "+" + rightExpression + ")");
                        expressionsSet.insert("(" + leftExpression + "-" + rightExpression + ")");
                        expressionsSet.insert("(" + leftExpression + "*" + rightExpression + ")");
                        if (rightExpression != "0") {
                            expressionsSet.insert("(" + leftExpression + "/" + rightExpression + ")");
                        }
                    }
                }
            }
        }
    }

    // Convert the set to a vector
    std::vector<std::string> expressions(expressionsSet.begin(), expressionsSet.end());

    // Sort the expressions by their difference from the target number
    std::sort(expressions.begin(), expressions.end(), [&](auto& lhs, auto& rhs) {
        return compareExpressions(lhs, rhs, target);
        });

    
    return vector<string>(expressions.begin(), expressions.begin() + std::min(expressions.size(), size_t(2700)));
}





// ------------------------------------  UPIS U IZLAZNU DATOTEKU
void writeToAFile(int brRunde, vector<int>brojeviRunde, int trazeniBroj, string izrazTakmicara,  int result, string pobednikRunde, int resenjePrograma) {
    
    int odstupanje = abs(trazeniBroj - result);
    ofstream file("Rezultati.txt", ios::app);
    file << brRunde << "|";
    for (int x : brojeviRunde) {
        file << x << " ";
    }
    file << "|" <<"Trazeni  broj: "<< trazeniBroj << "|" << "Izraz takmicara:" << izrazTakmicara << "|" << "Nas rezultat: " << result << "|" << pobednikRunde << "|" << "Resenje programa: " << resenjePrograma << "|" <<"Odstupanje: " << odstupanje << endl;
    file.close();

}

void writeAnEnd(int pobedeIgracaA, int pobedeIgracaB, string pobednik) {

    ofstream file("Rezultati.txt", ios::app);
    file << "Rezultat igraca A: "<<pobedeIgracaA<<"|" << "Rezultat igraca B: " << pobedeIgracaB << "|" << pobednik << endl;
    file << "----------------------------------------------------------------" << endl;
    file.close();

}






void MojBroj::gameStart()

{
    //flagNaPotezu 1-A, 2-B
    
    int flagNaPotezu;
    while (brRunde < ukupanbrRundi) {

        unordered_map<string, int> opMap = {
        { "*", 2},
        { "/", 2},
        { "+", 1},
        { "-", 1},
        { "(", -1},
        { ")", -1},};



        vector<int> brojeviRunde = getNumbers(brRunde);
        int trazeniBroj = getSoultion(brRunde);


        cout << "\n---------------------------------------------\n";
        cout << "Da biste dosli do trazenog resenja mozete koristit mat. operacije:\n";
        cout << " + , -, *, /, kao i zagrade! \n\n";


        cout << "RUNDA " << brRunde + 1 << "\n\n";
        if (brRunde % 2 == 0) { 
            flagNaPotezu = 1;
            cout << "Na potezu je IGRAC A\n\n"; }
        else {
            flagNaPotezu = 2;
            cout << "Na potezu je IGRAC B\n"; }

        cout << "\nTrenutni rezultat je (poeniA:poeniB) - " << pobedeIgracaA << ":" << pobedeIgracaB;


        cout << "\n\nTrazeni broj je:";
        cout << trazeniBroj << "\n";


        cout << "A brojevi koje imate na raspolaganju da dodjete do njega su: \n";

        for (int x : brojeviRunde) {
            cout << x << " ";
        }


        cout << "\nVas izraz za dolazak do trazenog broja je: \n";

        cout << ">>> ";


        vector<string> tokens;
        string expression;
        float result;

        while (true) {
            cout << "Unesite izraz: ";
            
            cin >> expression;


            try {

                tokens = Tokenize1(expression, opMap); //infix : a * b

                tokens = InfixToPostfix1(tokens, opMap); // postfix : a b *
                result = CalculatePostfix1<float>(tokens, opMap);
                break;
            }
            catch (exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }





        vector<int> intList;

        for (const auto& s : tokens) {

            if (all_of(s.begin(), s.end(), ::isdigit)) {

                intList.push_back(stoi(s));
            }
        }


        sort(intList.begin(), intList.end());
        sort(brojeviRunde.begin(), brojeviRunde.end());




        cout << "\nMolimo za momenat strpljenja... Nas kompjuter napreze svoje mozdane vijuge i igra pocinje za koji trenutak...\n";

            

        if (includes(brojeviRunde.begin(), brojeviRunde.end(), intList.begin(), intList.end())) {


            cout << "Rezultat vaseg izraza je: " << result << endl;


            vector<string> expressions = generateExpressions(brojeviRunde, trazeniBroj);
            vector<string> expressionsNaked = generateExpressionsNoParentheses(brojeviRunde, trazeniBroj);


            string najboljiIzraz = expressions[0];
            string izrazBezZagrada = expressionsNaked[0];

            //izracunaj vrednost najboljeg izraza
            vector<string> tokensIzraz = Tokenize(najboljiIzraz, opMap); //infix : a * b

            tokensIzraz = InfixToPostfix(tokensIzraz, opMap); // postfix : a b *



            float rezultatNajboljegIzraza = CalculatePostfix(tokensIzraz, opMap);


            //izracunaj vrednost izraza bez zagrada
            vector<string> tokensIzrazBezZagrada = Tokenize(izrazBezZagrada, opMap);
            tokensIzrazBezZagrada = InfixToPostfix(tokensIzrazBezZagrada, opMap);
            float rezultatIzrazaBezZagrada = CalculatePostfix(tokensIzrazBezZagrada, opMap);










            if (abs(rezultatNajboljegIzraza - trazeniBroj) > abs(rezultatIzrazaBezZagrada - trazeniBroj)) {
                rezultatIzrazaBezZagrada = rezultatIzrazaBezZagrada;
            }

            if (abs(trazeniBroj-result) <= abs(trazeniBroj-rezultatNajboljegIzraza)) {

                cout << "Cestitamo pogodili ste trazeno resenje!\n\n";
                cout << "A nas kompjuter je dosao  do datog resenja: \n";
                cout << "1. Izraz sa primenom zagrada\n";
                cout << najboljiIzraz<<endl;
                cout << "2. Izraz bez primene zagrada\n";
                cout << izrazBezZagrada << endl;
                cout << "Vrednost kompjuterovog resenja je: " << rezultatNajboljegIzraza << endl;
                string pobednikRunde="Niko";
                if (flagNaPotezu == 1) {
                    pobedeIgracaA += 1;
                    flagNaPotezu = 2;
                    pobednikRunde = "igrac A";
                }
                else  if(flagNaPotezu ==2) {
                    pobedeIgracaB += 1;
                    flagNaPotezu = 1;
                    pobednikRunde = "igrac B";
                }
                writeToAFile(brRunde+1, brojeviRunde, trazeniBroj, expression, result, pobednikRunde, rezultatNajboljegIzraza);
                
                brRunde += 1;
                
                
                

            }
            else {
                
                while (brRunde<ukupanbrRundi) {
                    if (brRunde % 2 == 0) {
                        flagNaPotezu = 2;
                    }else{
                        flagNaPotezu = 1;
                    }


                    cout << "\nNiste dobili tacno resenje! S toga je na redu protivnik... \n";
                   
                    cout << "Unesite Vase resenje za gore dati izraz: \n";



                    vector<string> tokensB;
                    string expressionB;
                    float resultB;

                    while (true) {
                        cout << "Unesite izraz: ";

                        cin >> expressionB;


                        try {

                            tokensB = Tokenize1(expressionB, opMap); //infix : a * b

                            tokensB = InfixToPostfix1(tokensB, opMap); // postfix : a b *
                            resultB = CalculatePostfix1<float>(tokensB, opMap);
                            break;
                        }
                        catch (exception& e) {
                            cout << "Error: " << e.what() << endl;
                        }
                    }

                    vector<int> intListB;

                    for (const auto& s : tokensB) {

                        if (all_of(s.begin(), s.end(), ::isdigit)) {

                            intListB.push_back(stoi(s));
                        }
                    }

                    sort(intListB.begin(), intListB.end());
                    sort(brojeviRunde.begin(), brojeviRunde.end());

                    if (includes(brojeviRunde.begin(), brojeviRunde.end(), intListB.begin(), intListB.end())) {

                        cout << "Vase resenje je: " << resultB << endl;

                        if (abs(resultB-trazeniBroj) <= abs(rezultatNajboljegIzraza-trazeniBroj)) {

                            cout << "\nCestitamo! Pogodili ste trazeno resenje!\n\n";

                            cout << "A nas kompjuter je dosao  do datog resenja: \n";
                            cout << "1. Izraz sa primenom zagrada\n";
                            cout << najboljiIzraz << endl;
                            //cout << "2. Izraz bez primene zagrada\n";
                            //cout << izrazBezZagrada << endl;
                            cout << "Vrednost kompjuterovog resenja je: " << rezultatNajboljegIzraza << endl;
                            string pobednikRunde = "Niko";
                            if (flagNaPotezu == 2) {
                                pobedeIgracaB += 1;
                                pobednikRunde = "igrac B";
                            }
                            else if (flagNaPotezu==1) {
                                pobedeIgracaA += 1;
                                pobednikRunde = "igrac A";
                            }
                            
                            
                            writeToAFile(brRunde + 1, brojeviRunde, trazeniBroj, expression, resultB, pobednikRunde, rezultatNajboljegIzraza);

                            brRunde += 1;
                            break;
                        }
                        else {

                            if (flagNaPotezu == 2) {
                                flagNaPotezu = 1;
                            }
                            else if (flagNaPotezu == 1) {
                                flagNaPotezu = 2;
                            }

                            //cout << "FLAG NA POTEZU: " << flagNaPotezu << endl;
                            //cout << "-------------------------------------------------" << endl;

                            cout << "Niste uspeli da dobijete tacno resenje!\n\n";
                            cout << "Svakako sledi Vasa runda-srecno :)\n";
                            cout << "A tacno resenje je: \n";
                            //cout << "1. Izraz bez zagrada: "<<izrazBezZagrada <<endl;
                            cout << "1. Izraz sa zagradama: "<<najboljiIzraz << endl;
                            cout << "Vrednost kompjuterovog resenja je: "<<rezultatNajboljegIzraza << endl;
                            brRunde += 1;
                            break;

                        }
                    }
                    else if (!(includes(brojeviRunde.begin(), brojeviRunde.end(), intListB.begin(), intListB.end()))) {
                        cout << "\nZA IZRAZ MORATE KORISTITI SAMO PONUDJENE BROJEVE ZA DATU RUNDU!\n\n";
                    }
                }
            }

        }
        else  if (!(includes(brojeviRunde.begin(), brojeviRunde.end(), intList.begin(), intList.end()))) {
            cout << "\nZA IZRAZ MORATE KORISTITI SAMO PONUDJENE BROJEVE ZA DATU RUNDU!\n\n";
        }

    } 


    if (brRunde == ukupanbrRundi) {
        cout << "--------------------------------------------------------" << endl;
        cout << "Cestitamo dosli ste do kraja igre!"<<endl;
        cout << "Pobednik je: " << endl;
        string pobednik = "";
        if (pobedeIgracaA == pobedeIgracaB) {
            pobednik = "Nereseno";
            cout << pobednik;
        }else if (pobedeIgracaA > pobedeIgracaB) {
            pobednik = "Pobednik je igrac A";
            cout<<pobednik<< endl;
        }else {
            pobednik = "Pobednik je igrac B";
            cout << pobednik << endl;
        }

        writeAnEnd(pobedeIgracaA, pobedeIgracaB, pobednik);
    }
}


// TESTOVI
void MojBroj::testirajProgramZaGenerisanjeIzraza() {
    //edge case, tj. test_case2-ne postoji zeljeni rezultat, vec priblizan
    //test_case1- zeljeni=moguci rezultat
    //ispravan test case
    // prozivoljna duzina test case  pomocu modula
    // 
    // poredjenje rezultata test case-a i rez. dobijenog

    unordered_map<string, int> opMap = {
    { "*", 2},
    { "/", 2},
    { "+", 1},
    { "-", 1},
    { "(", -1},
    { ")", -1}, };

    vector<int> test_case1 = { 7,6,8,7,15,50 };
    vector<int> test_case2 = { 7, 3, 1, 6, 2, 7 };
    vector<int> test_case3 = { 4, 3, 2, 15 };
    // provera rada sa 6 cifara


    cout << "\nProvera rada programa kada treba da dobijemo zeljeni rezultat: " << endl;
    
    cout << "TEST_CASE 1: " << "7,6,8,7,15,50" << endl;
    int solution1 = 307;
    cout << "ZELJENI I OCEKIVANI REZULTAT: " << solution1<<endl;
    //vector<int> test_case3 = {};

    vector<string> expressions = generateExpressions(test_case1, solution1);
    vector<string> expressionsNaked = generateExpressionsNoParentheses(test_case1, solution1);

    string solutionNaked = expressionsNaked[0];
    string solutionNoParentehes = expressions[0];

    vector<string> tokens = Tokenize(solutionNaked, opMap); //infix : a * b

    tokens = InfixToPostfix(tokens, opMap); // postfix : a b *
    float res1 = CalculatePostfix(tokens, opMap);


    vector<string> tokens2 = Tokenize(solutionNoParentehes, opMap); //infix : a * b

    tokens2 = InfixToPostfix(tokens2, opMap); // postfix : a b *
    float res2 = CalculatePostfix(tokens2, opMap);



    cout << "Dobijeni izrazi: " << endl;
    cout << "1. BEZ ZAGRADA:";
    cout << solutionNaked << endl;
    cout<<"2.SA ZAGRADAMA : ";
    cout << solutionNoParentehes << endl;
    cout << "Resenje izraza bez i sa zagradama je: " <<res1<<", "<<res2 << endl;


    if(res2 == solution1){
        cout << "Ocekivani i dobijeni rezultat se poklapaju!" << endl;
    }
    else {
        cout << "ERRR, GRESKA! Nas program se ponasa neocekivano..." << endl;
    }

    cout << "------------------------------------------------------------------------"<<endl;

    cout << "Provera rada programa kada nije moguce dobiti zeljeni rezultat: "<<endl;
    
    string numbers = "7, 3, 6, 2, 1, 7 ";
    cout << "Brojevi na raspolaganju su - " << numbers << endl;
    int solution2 = 824;
    cout << "ZELJENI REZULTAT: " <<solution2<< endl;
    cout << "NAJBLIZI MOGUCI REZULTAT: 826" << endl;

    cout << "A sada da vidimo sta ce nas program izgenerisati... " << endl;


    vector<string> expressions2 = generateExpressions(test_case2, solution2);
    vector<string> expressionsNaked2 = generateExpressionsNoParentheses(test_case2, solution2);



    string solutionNaked2 = expressions2[0];
    string solutionNoParentehes2 = expressionsNaked2[0];

    cout << "Dobijeni izrazi: " << endl;
    cout << "1. SA ZAGRADAMA:";
    cout << solutionNaked2 << endl;

    vector<string> tokens3 = Tokenize(solutionNaked2, opMap); //infix : a * b

    tokens3 = InfixToPostfix(tokens3, opMap); // postfix : a b *
    float res3 = CalculatePostfix(tokens3, opMap);


    if (res3 == 826) {
        cout << "Ocekivani i dobijeni rezultat se poklapaju!" << endl;
    }
    else {
        cout << "ERRR, GRESKA! Nas program se ponasa neocekivano..." << endl;
    }

    cout << "------------------------------------------------------------------------"<<endl;
    cout << "Provera rada programa kada prosledjujemo manje od 6 cifara za generisanje izraza: " << endl;
    cout << "TEST_CASE3: 3, 15, 2, 4" << endl;
    cout << "ZELJENI REZULTAT: 34"<<endl;

    float solution3;

    
    vector<string> expressions3 = generateExpressions(test_case3, 34);
    vector<string> expressionsNaked3 = generateExpressionsNoParentheses(test_case3, 34);


   
    string solutionNaked3 = expressions3[0];
    string solutionNoParentehes3 = expressionsNaked3[0];

    cout <<"DOBIJENI IZRAZ ZA NAS TEST PRIMER: " << solutionNaked3 << endl;
    vector<string> tokens4 = Tokenize(solutionNoParentehes3, opMap); //infix : a * b

    tokens4 = InfixToPostfix(tokens4, opMap); // postfix : a b *
    float res4 = CalculatePostfix(tokens4, opMap);


    if (res4 == 34) {
        cout << "Ocekivani i dobijeni rezultat se poklapaju!" << endl;
    }
    else {
        cout << "ERRR, GRESKA! Nas program se ponasa neocekivano..." << endl;
    }

    


}

void MojBroj::testirajProgramZaRacunanjeIzraza() {

    unordered_map<string, int> opMap = {
    { "*", 2},
    { "/", 2},
    { "+", 1},
    { "-", 1},
    { "(", -1},
    { ")", -1}, };
    //izraz za racunanje bez zagrada
    string test_expression1="5+3-2*2+4/2";


    //izraz za racunanje sa zagradama
    string test_expression2 = "5*(3+4)-2*(3+3)";

    //izraz gde imamo deljenje sa nulom
    string test_expression3 = "4/0";


    //izraz gde imamo mismatched parentheses
    string test_expression4 = "7+(5*4";

    //izraz gde imamo nedozvoljeni karakter
    string test_expression5 = "4+6*m4";


    vector<string> tokens = Tokenize(test_expression1, opMap); //infix : a * b

    tokens = InfixToPostfix(tokens, opMap); // postfix : a b *
    float res0 = CalculatePostfix(tokens, opMap);
    cout << "TEST_CASE1: " << test_expression1<<endl;
    cout <<"RESULT: " << res0<<endl;

    if (res0 == 6) {
        cout << "ISPRAVNO!" << endl;
    }else {
        cout << "ERRR, GRESKA! PROGRAM NE RADI KAKO TREBA!" << endl;
    }

    vector<string> tokens1 = Tokenize(test_expression2, opMap); //infix : a * b

    tokens1 = InfixToPostfix(tokens1, opMap); // postfix : a b *
    float res1 = CalculatePostfix(tokens1, opMap);


    cout << "TEST_CASE1: " << test_expression2 << endl;
    cout << "RESULT: " << res1 << endl;

    if (res1 == 23) {
        cout << "ISPRAVNO!" << endl;
    }
    else {
        cout << "ERRR, GRESKA! PROGRAM NE RADI KAKO TREBA!" << endl;
    }

    cout << "TEST_CASE3: " << test_expression3 << endl;
   
    try {

        vector<string> tokens2 = Tokenize(test_expression3, opMap); //infix : a * b

        tokens2 = InfixToPostfix(tokens2, opMap); // postfix : a b *
        float res2 = CalculatePostfix(tokens2, opMap);
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }


    cout << "TEST_CASE4: " << test_expression4 << endl;
    try {

        vector<string> tokens3 = Tokenize(test_expression4, opMap); //infix : a * b

        tokens3 = InfixToPostfix(tokens3, opMap); // postfix : a b *
        float res3 = CalculatePostfix(tokens3, opMap);
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "TEST_CASE5: " << test_expression5 << endl;
    try {
        vector<string> tokens4 = Tokenize(test_expression5, opMap); //infix : a * b

        tokens4 = InfixToPostfix(tokens4, opMap); // postfix : a b *
        float res4 = CalculatePostfix(tokens4, opMap);
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    

}