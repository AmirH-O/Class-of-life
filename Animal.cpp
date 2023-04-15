#include <bits/stdc++.h>
#include "Cell.h" 
using namespace std;

class Virus;
class Animal : public Cell {
public: 
	Animal() : Cell() {} 
	Cell get_cell() {
		return animal_cell;
	}
	char get_nucleotide(char x) { // Creates nucleotdie complement
		if(x == 'T') return 'A';
		if(x == 'A') return 'T';
		if(x == 'C') return 'G';
		if(x == 'G') return 'C';
	}
	double genetic_similarity_percentage(Animal animal) {
		string s1 = "" , s2 = "";

		for(int i = 0; i < animal_cell.get_chromosome().size(); i++)
			s1 += animal_cell.get_chromosome()[i].get_DNA().first;

		for(int i = 0; i < animal_cell.get_chromosome().size(); i++)
			s2 += animal.animal_cell.get_chromosome()[i].get_DNA().first;

		int n = s1.size();
		int m = s2.size();
		
		int dp[n][m];
		for(int i = 0; i <= n; i++)
			dp[0][i] = i;
		for(int i = 0; i <= m; i++)
			dp[i][0] = i;

	  	for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				int cost = (s1[i] == s2[j] ? 0 : 1);
				dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1 , dp[i - 1][j - 1] + cost});
			}
		}

		double percentage = 100.0 - ((double)dp[n][m] * 100.0 / (double)max(n, m));	
		return percentage;
	}
	bool operator == (Animal animal) {
		if(genetic_similarity_percentage(animal) >= 70)
			return true;
		else 
			return false;
	}
	Animal asexual_reproduction() {
		srand(time(NULL));

		vector<Genome> chromosomes = animal_cell.get_chromosome();
		for(auto i : chromosomes)
			chromosomes.push_back(i);

		vector<int> rand_indx;
		for(int i = 0; i < chromosomes.size(); i++) 
			rand_indx.push_back(i);

		Animal child;
		do {
			random_shuffle(rand_indx.begin(), rand_indx.end());

			vector<Genome> child_chromosomes;
			for(int i = 0; i < chromosomes.size() / 2; i++)
				child_chromosomes.push_back(chromosomes[rand_indx[i]]);

			Cell child_cell(child_chromosomes);
			child.animal_cell = child_cell;
		} while(genetic_similarity_percentage(child) < 70);

		return child;
	}
	Animal operator + (Animal animal) {
		srand(time(NULL));
		
		Animal temp1 = this->asexual_reproduction();
		Animal temp2 = animal.asexual_reproduction();

		if(temp1.animal_cell.get_chromosome().size() % 2 == 1 || temp2.animal_cell.get_chromosome().size() % 2 == 1) 
			cout << "Cannot reproduce!\n";
		else {
			vector<int> rand_indx1, rand_indx2;

			for(int i = 0; i < temp1.animal_cell.get_chromosome().size(); i++) 
				rand_indx1.push_back(i);
			for(int i = 0; i < temp2.animal_cell.get_chromosome().size(); i++) 
				rand_indx2.push_back(i);
			
			vector<Genome> child_chromosomes;
			Animal child;
			do {
				random_shuffle(rand_indx1.begin(), rand_indx1.end());
				random_shuffle(rand_indx2.begin(), rand_indx2.end());

				for(int i = 0; i < temp1.animal_cell.get_chromosome().size() / 2; i++) 
					child_chromosomes.push_back(temp1.animal_cell.get_chromosome()[rand_indx1[i]]);
				for(int i = 0; i < temp2.animal_cell.get_chromosome().size() / 2; i++) 
					child_chromosomes.push_back(temp2.animal_cell.get_chromosome()[rand_indx2[i]]);

				Cell child_cell(child_chromosomes);
				child.animal_cell = child_cell;
			} while(genetic_similarity_percentage(child) < 70);

			return child;
		}
	}
	void cell_death() { 
		for(int i = 0; i < animal_cell.get_chromosome().size(); i++) {
			int cnt = 0;
			for(int j = 0; j < animal_cell.get_chromosome()[i].get_DNA().first.size(); j++) { 
				if(animal_cell.get_chromosome()[i].get_DNA().first[j] != get_nucleotide(animal_cell.get_chromosome()[i].get_DNA().second[j])) 
					cnt++;
			}
			if(cnt > 5)
				animal_cell.get_chromosome()[i].~Genome();
		} 
	}
	friend class Virus;
protected: 
	Cell animal_cell;
};

class Virus : public Genome {
public:
	Virus() : Genome() {}
	char get_nucleotide(char x) { // Creates nucleotdie complement
		if(x == 'T') return 'A';
		if(x == 'A') return 'T';
		if(x == 'C') return 'G';
		if(x == 'G') return 'C';
	}
	bool is_harmful(Animal animal) {
		vector<string> arr;

		for(int i = 0; i < animal.get_cell().get_chromosome().size(); i++) 	
			arr.push_back(animal.get_cell().get_chromosome()[i].get_DNA().first);

	    int n = arr.size();
	 
	    string s = arr[0];
	    int len = s.size();
	 
	    string result = "";
	 
	    for (int i = 0; i < len; i++) {
	        for (int j = i + 1; j <= len; j++) {

	            string temp = s.substr(i, j);
	            int k = 1;
	            for (k = 1; k < n; k++) {
	                if (arr[k].find(temp) == std::string::npos)
	                    break;
	            }
	 
	            if (k == n && result.length() < temp.length())
	                result = temp;
	        }
	    }
	 
	    string result_comp = "";
		for(int i = 0; i < result.size(); i++)
			result_comp += get_nucleotide(result[i]);
		
		for(int i = 0; i < RNA.size(); i++) {
			if(result == RNA.substr(i, result.size()) || result_comp == RNA.substr(i, result_comp.size()))
				return true;
		}

		return false;
	}
private:
	string RNA;
};
