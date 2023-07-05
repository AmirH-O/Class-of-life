#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include "Animal.h"
#define blue 9
#define green 10
#define cyan 11
#define red 12
#define purple 13
#define orange 14
#define white 15
#define normal 7
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int main() {
	srand(time(NULL));
	system("cls");

	SetConsoleTextAttribute(hConsole, green); // Starting the program
	cout << "Welome to the class of Life\n"; 
	cout << "Press any key to continue...";
	SetConsoleTextAttribute(hConsole, cyan);
	char key = getch(); 	

	vector<Genome> genomes;
	vector<Cell> cells;
	vector<Animal> animals;
	vector<Virus> viruses;

	again: 
	system("cls"); 

	SetConsoleTextAttribute(hConsole, green); // Prints the main menu
	cout << "Choose one of the options below: \n";
	SetConsoleTextAttribute(hConsole, cyan);

	cout << "- In case you want to create a Genome press 1...\n";
	cout << "- In case you want to create a Cell press 2...\n";
	cout << "- In case you want to create an Animal press 3...\n";
	cout << "- In case you want to create a Virus press 4...\n";

	key = getch();
	switch(key) { 
		case '1': { // Creating a genome
			system("cls"); 

			cout << "Enter a RNA for your genome (if you don't want a RNA enter \"none\"): "; 

			string RNA;
			cin >> RNA;

			cout << "Enter a DNA for your genome:\n";

			pair<string, string> DNA;

			cout << "First sequence: ";
			cin >> DNA.first;

			cout << "Second sequence: ";
			cin >> DNA.second;

			if(RNA == "none") RNA = "";

			Genome gen(DNA, RNA);
			genomes.push_back(gen);

			SetConsoleTextAttribute(hConsole, green);
			cout << "Genome created!\n";
			SetConsoleTextAttribute(hConsole, cyan);

			cout << "Press any key to go back to the menu...\n";
			char ch = getch();

			goto again;
			break;
		}
		case '2': { // Creating a cell
			system("cls");

			if(!genomes.size()) {
				SetConsoleTextAttribute(hConsole, red);
				cout << "There are no available chromosomes!\nPlease create a chromosome before using this method.\n";
				SetConsoleTextAttribute(hConsole, cyan);
			}
			else {
				cout << "Available chromosomes:\n"; // Showing available chromosomes
				for(int i = 0; i < genomes.size(); i++) {
					if(genomes[i].get_RNA() == "") {

						SetConsoleTextAttribute(hConsole, green);
						cout << "Chromosome " << i + 1 << ":\n";
						SetConsoleTextAttribute(hConsole, cyan);

						cout << "DNA sequence 1: " << genomes[i].get_DNA().first << '\n';
						cout << "DNA sequence 2: " << genomes[i].get_DNA().second << '\n';
					}
				}
				cout << "How many chromosomes do you want to use?\n";
				int n;
				cin >> n;

				cout << "Select the chromosomes you want to include in your cell:\n";
				vector<Genome> cell_genomes;

				for(int i = 0; i < n; i++) {
					int num;
					cin >> num;
					cell_genomes.push_back(genomes[num - 1]);
				}

				Cell new_cell(cell_genomes);
				cells.push_back(new_cell);

				SetConsoleTextAttribute(hConsole, green);
				cout << "Cell created!\n";
				SetConsoleTextAttribute(hConsole, cyan);

				cout << "Press any key to go back to the menu...\n";
				char ch = getch();

				goto again;
			}
			break;
		}
		case '3': { // Creating an animal
			system("cls");

			if(!cells.size()) {
				SetConsoleTextAttribute(hConsole, red);
				cout << "There are no available cells!\nPlease create a cell before using this method.\n";
				SetConsoleTextAttribute(hConsole, cyan);
				cout << "Press any key to go back to the menu...\n";
			}
			else {
				cout << "Available cells: \n";
				for(int i = 0; i < cells.size(); i++) { // Showing available cells

					SetConsoleTextAttribute(hConsole, orange);
					cout << "Cell " << i + 1 << ":\n";

					for(int j = 0; j < cells[i].get_chromosome().size(); j++) {

						SetConsoleTextAttribute(hConsole, green);
						cout << "Chromosome " << j + 1 << ":\n";
						SetConsoleTextAttribute(hConsole, cyan);

						cout << "DNA sequence 1: " << cells[i].get_chromosome()[j].get_DNA().first << '\n';
						cout << "DNA sequence 2: " << cells[i].get_chromosome()[j].get_DNA().second << '\n';
					}
				}
				cout << "Select a cell to include in your animal: \n";
				int n;
				cin >> n;

				Animal my_animal(cells[n - 1]);
				animals.push_back(my_animal);

				SetConsoleTextAttribute(hConsole, green);
				cout << "Animal created!\n";
				SetConsoleTextAttribute(hConsole, cyan);

				cout << "Press 1 to go back to the menu...\n";
				cout << "Press 2 to continue...\n";

				char ch = getch();
				if(ch == '1') 
					goto again;
				else 
					break;
			}
		}
		case '4': { // creating a virus
			system("cls");

			cout << "Enter virus RNA: ";
			string RNA;
			cin >> RNA;

			Virus my_virus(RNA);
			viruses.push_back(my_virus);

			SetConsoleTextAttribute(hConsole, green);
			cout << "Virus created!\n";
			SetConsoleTextAttribute(hConsole, cyan);

			cout << "Press any key to continue...\n";
			char ch = getch();
			break;
		}
	}
	again2:
	system("cls"); // Printing the second menu

	SetConsoleTextAttribute(hConsole, green);
	cout << "Select an option: \n";
	SetConsoleTextAttribute(hConsole, cyan);

	cout << "- In case you want to perform a genetic mutation press 1...\n";
	cout << "- In case you want to find the complementary palindromes press 2...\n";
	cout << "- In case you want to perform an asexual reproduction press 3...\n";
	cout << "- In case you want to perform a sexual reproduction press 4...\n";
	cout << "- In case you want to check whether two animals are related or not press 5...\n";
	cout << "- In case you want to check whether your animals are affected by a virus or not press 6...\n";
	cout << "- In case you want to go back to the previous menu press 7...\n";

	key = getch();

	system("cls");

	cout << "Available animals: \n"; // Showing available animals
	for(int i = 0; i < animals.size(); i++) {

		SetConsoleTextAttribute(hConsole, orange);
		cout << "Animal " << i + 1 << ":\n";
		SetConsoleTextAttribute(hConsole, cyan);

		for(int j = 0; j < animals[i].get_cell().get_chromosome().size(); j++) {

			SetConsoleTextAttribute(hConsole, green);
			cout << "Chromosome " << j + 1 << ":\n";
			SetConsoleTextAttribute(hConsole, cyan);

			cout << "DNA sequence 1: " << animals[i].get_cell().get_chromosome()[j].get_DNA().first << '\n';
			cout << "DNA sequence 2: " << animals[i].get_cell().get_chromosome()[j].get_DNA().second << '\n';
		} 
	}
	switch(key) {
		case '1' : {
			cout << "Select an animal: "; 
			int n;
			cin >> n;

			SetConsoleTextAttribute(hConsole, green);
			cout << "\nWhat kind of mutation do you want to perform?\n";
			SetConsoleTextAttribute(hConsole, cyan);

			cout << "1- Major genetic mutation\n";
			cout << "2- Minor genetic mutation\n";
			cout << "3- Reverse genetic mutation\n";

			int op;
			cin >> op;
			if(op == 1) { // The major genetic mutation method
				cout << "Select the first chromosome: ";
				int num1, num2;
				cin >> num1;

				cout << "Select the second chromosome: ";
				cin >> num2;

				cout << "Enter current sequence of nucleotides: ";
				string s1, s2;
				cin >> s1;

				cout << "Enter the replacement sequence: ";
				cin >> s2;

				animals[n - 1].animal_cell.major_genetic_mutation(s1, num1, s2, num2);

				SetConsoleTextAttribute(hConsole, green);
				cout << "New chromosome " << num1 << ":\n";
				SetConsoleTextAttribute(hConsole, cyan);

				cout << "DNA first sequence: ";
				cout << animals[n - 1].get_cell().get_chromosome()[num1 - 1].get_DNA().first << '\n';
				cout << "DNA second sequence: ";
				cout << animals[n - 1].get_cell().get_chromosome()[num1 - 1].get_DNA().second << '\n';

				SetConsoleTextAttribute(hConsole, green);
				cout << "New chromosome " << num2 << ":\n";
				SetConsoleTextAttribute(hConsole, cyan);

				cout << "DNA first sequence: ";
				cout << animals[n - 1].get_cell().get_chromosome()[num2 - 1].get_DNA().first << '\n';
				cout << "DNA second sequence: ";
				cout << animals[n - 1].get_cell().get_chromosome()[num2 - 1].get_DNA().second << '\n';

				SetConsoleTextAttribute(hConsole, green);
				cout << "Press any key to go back to the menu...";
				SetConsoleTextAttribute(hConsole, cyan);

				char ch = getch();
				goto again2;
			}
			if(op == 2) { // The minor genetic mutation method
				cout << "Select a chromosome: ";
				int num1, num2;
				cin >> num1;
				
				cout << "Enter the current nucleotide: ";
				char nucleo1, nucleo2;
				cin >> nucleo1;

				cout << "Enter the replacement nucleotide: ";
				cin >> nucleo2;

                cout << "How many nucleotides do you want to replace? ";
                cin >> num2;

				animals[n - 1].animal_cell.minor_genetic_mutation(nucleo1, nucleo2, num2, num1);

				SetConsoleTextAttribute(hConsole, green);
				cout << "New chromosome " << num1 << ":\n";
				SetConsoleTextAttribute(hConsole, cyan);

				cout << "DNA first sequence: ";
				cout << animals[n - 1].get_cell().get_chromosome()[num1 - 1].get_DNA().first << '\n';
				cout << "DNA second sequence: ";
				cout << animals[n - 1].get_cell().get_chromosome()[num1 - 1].get_DNA().second << '\n';

				SetConsoleTextAttribute(hConsole, green);
				cout << "Press any key to go back to the menu...";
				SetConsoleTextAttribute(hConsole, cyan);

				char ch = getch();
				goto again2;
			}
			if(op == 3) { // The reverse mutation method
				cout << "Select a chromosome: ";
				int num;
				cin >> num;

				cout << "Enter the nucleotide sequence you want to reverse: ";
				string s;
				cin >> s;

				animals[n - 1].animal_cell.reverse_mutation(s, num);

				SetConsoleTextAttribute(hConsole, green);
				cout << "New chromosome " << num << ":\n";
				SetConsoleTextAttribute(hConsole, cyan);

				cout << "DNA first sequence: ";
				cout << animals[n - 1].get_cell().get_chromosome()[num - 1].get_DNA().first << '\n';
				cout << "DNA second sequence: ";
				cout << animals[n - 1].get_cell().get_chromosome()[num - 1].get_DNA().second << '\n';

				SetConsoleTextAttribute(hConsole, green);
				cout << "Press any key to go back to the menu...";
				SetConsoleTextAttribute(hConsole, cyan);

				char ch = getch();
				goto again2;
			}
			break;
		}
		case '2': { // Finding the complementary palindromes
            cout << "Select an animal: ";
            int n;
            cin >> n;

            cout << "\nSelect a chromosome: ";
            int num;
            cin >> num;

            cout << "Complementary palindromes of chromosome " << num << ":\n";
            animals[n - 1].animal_cell.complementary_palindrome(num);

			SetConsoleTextAttribute(hConsole, green);
			cout << "Press any key to go back to the menu...";
			SetConsoleTextAttribute(hConsole, cyan);

			char ch = getch();
			goto again2;
			break;
		}
		case '3': { // The asexual reproduction method
			cout << "Select an animal: ";
			int n;
			cin >> n;

			Animal child = animals[n - 1].asexual_reproduction();
			animals.push_back(child);

			cout << "A child with a similarity percentage of " << animals[n - 1].genetic_similarity_percentage(child) << "% " << "was born!\n";

			SetConsoleTextAttribute(hConsole, green);
			cout << "Press any key to go back to the menu...";
			SetConsoleTextAttribute(hConsole, cyan);

			char ch = getch();
			goto again2;
			break;
		}
		case '4': { // The sexual reproduction method
			cout << "Select two animals: ";
			int n1, n2;
			cin >> n1 >> n2;

			Animal child = animals[n1 - 1] + animals[n2 - 1];
			animals.push_back(child);
			cout << "A child with a genetic similarity percentage of " << animals[n1 - 1].genetic_similarity_percentage(child) << "% " << "was born!\n";

			SetConsoleTextAttribute(hConsole, green);
			cout << "Press any key to go back to the menu...";
			SetConsoleTextAttribute(hConsole, cyan);

			char ch = getch();
			goto again2;
			break;
		}
		case '5': { // Checking the relation between two animals
			cout << "Select two animals: ";
			int n1, n2;
			cin >> n1 >> n2;

			SetConsoleTextAttribute(hConsole, green);
			if(animals[n1 - 1] == animals[n2 - 1]) {
				cout << "They are related!\n";
			}
			else {
				cout << "They are not related!\n";
			}

			cout << "Press any key to go back to the menu...";
			SetConsoleTextAttribute(hConsole, cyan);

			char ch = getch();
			goto again2;
			break;
		}
		case '6': { // Checking whether an animal is affected by a virus or not
			cout << "Select an animal: ";
			int n;
			cin >> n;

			bool sick = 0;
			for(int i = 0; i < viruses.size(); i++) {
				if(viruses[i].is_harmful(animals[n - 1])) {

					SetConsoleTextAttribute(hConsole, green);
					cout << "Animal is affected by virus " << i + 1 << "!\n";
					sick = 1;
				}
			}
			if(!sick) {
				SetConsoleTextAttribute(hConsole, green);
				cout << "Animal is not affected by any virus!\n";
			}

			cout << "Press any key to go back to the menu...";
			SetConsoleTextAttribute(hConsole, cyan);

			char ch = getch();
			goto again2;
			break;
		}
		case '7': { 
			goto again;
		}
	}
    return 0;
} 