#include <bits/stdc++.h>
using namespace std;

class Genome {
public: 
	Genome() {} 
	Genome(pair<string, string> DNA, string RNA) { // Initial values for DNA and RNA
		this->DNA = DNA;
		this->RNA = RNA;
	}
	~Genome() {} // Destructing a chromosome
	pair<string, string> get_DNA() { // Getter function for DNA
		return DNA;
	}
	string get_RNA() { // Getter function for RNA 
		return RNA;
	}
	char get_nucleotide(char x) { // Creates nucleotdie complement
		if(x == 'T') return 'A';
		if(x == 'A') return 'T';
		if(x == 'C') return 'G';
		if(x == 'G') return 'C';
	}
	void print_DNA() { // Creates DNA from RNA and prints it
		string comp_RNA = "";
		for(int i = 0; i < RNA.size(); i++) {
			if(RNA[i] == 'T') comp_RNA += 'A';
			if(RNA[i] == 'A') comp_RNA += 'T';
			if(RNA[i] == 'C') comp_RNA += 'G';
			if(RNA[i] == 'G') comp_RNA += 'C';
		}
		cout << "DNA: " << RNA << '\n';
		cout << "     " << comp_RNA << '\n';
	} 
	void minor_DNA_genetic_mutation(char curr, char res, int n) { // Minor mutation in DNA
		int cnt = 0;
		for(int i = 0; i < DNA.first.size(); i++) {
			if(cnt == n) break;
			if(DNA.first[i] == curr) 
				DNA.first[i] = res, cnt++;
		}
		cnt = 0;
		curr = get_nucleotide(curr);
		res = get_nucleotide(res);
		for(int i = 0; i < DNA.second.size(); i++) {
			if(cnt == n) break;
			if(DNA.second[i] == curr) 
				DNA.second[i] = res, cnt++;
		}
	}
	void minor_RNA_genetic_mutation(char curr, char res, int n) { // Minor mutation in RNA
		int cnt = 0;
		for(int i = 0; i < RNA.size(); i++) {
			if(cnt == n) break;
			if(RNA[i] == curr) 
				RNA[i] = res, cnt++;
		}
	}
	void major_DNA_genetic_mutation(string s1, string s2) { // Major mutation in DNA
		int indx = DNA.first.find(s1);
		string res1 = "", res2 = ""; 
		for(int i = 0; i < indx; i++) {
			res1 += DNA.first[i];
			res2 += DNA.second[i];
		}
		res1 += s2;
		for(int i = 0; i < s2.size(); i++) 
			s2[i] = get_nucleotide(s2[i]);
		res2 += s2;
		for(int i = indx + s2.size(); i < DNA.first.size(); i++) {
			res1 += DNA.first[i];
			res2 += DNA.second[i];
		}
		DNA.first = res1;
		DNA.second = res2; 
	}
	void major_RNA_genetic_mutation(string s1, string s2) { // Major mutation in RNA
		int indx = RNA.find(s1);
		string res = "";
		for(int i = 0; i < indx; i++) 
			res += RNA[i];
		res += s2;
		for(int i = indx + s2.size(); i < RNA.size(); i++)  
			res += RNA[i];
		RNA = res;
	}
	void reverse_DNA_mutation(string s) { // Reverse mutation in DNA
		int indx = DNA.first.find(s);
		string res1 = "", res2 = ""; 
		for(int i = 0; i < indx; i++) {
			res1 += DNA.first[i];
			res2 += DNA.second[i];
		}
		reverse(s.begin(), s.end());
		res1 += s;
		for(int i = 0; i < s.size(); i++) 
			s[i] = get_nucleotide(s[i]);
		res2 += s;
		for(int i = indx + s.size(); i < DNA.first.size(); i++) {
			res1 += DNA.first[i];
			res2 += DNA.second[i];
		}
		DNA.first = res1;
		DNA.second = res2; 
	}
	void reverse_RNA_mutation(string s) { // Reverse mutation in RNA
		int indx = RNA.find(s);
		string res = "";
		for(int i = 0; i < indx; i++) 
			res += RNA[i];
		reverse(s.begin(), s.end());
		res += s;
		for(int i = indx + s.size(); i < RNA.size(); i++)  
			res += RNA[i];
		RNA = res;
	}
protected:
	string RNA;
	pair<string, string> DNA; 
};


class Cell : public Genome {
public:
	Cell() {}
	Cell(vector<Genome> chromosome) : Genome() { // Initial data of the cell's chromosomes
		this->chromosome = chromosome;
	} 
	vector<Genome> get_chromosome() {
		return chromosome;
	}
	char get_nucleotide(char x) { // Creates nucleotdie complement
		if(x == 'T') return 'A';
		if(x == 'A') return 'T';
		if(x == 'C') return 'G';
		if(x == 'G') return 'C';
	}
	void cell_death() { // Checking whether the cell is dead or not
		for(int i = 0; i < chromosome.size(); i++) {
			int cnt = 0;
			for(int j = 0; j < chromosome[i].get_DNA().first.size(); j++) {
				if(chromosome[i].get_DNA().first[j] != get_nucleotide(chromosome[i].get_DNA().second[j]))
					cnt++;
			}
			if(cnt > 5)
				delete this;
		} 
	}
	void major_genetic_mutation(string s1, int n, string s2, int m) { // Major mutation in the DNA
		chromosome[n - 1].major_DNA_genetic_mutation(s1, s2);
		chromosome[m - 1].major_DNA_genetic_mutation(s2, s1);		
	}
	void minor_genetic_mutation(char curr, char res, int n, int m) { // Minor mutation in the DNA
		chromosome[m - 1].minor_DNA_genetic_mutation(curr, res, n);
	}
	void reverse_mutation(string s, int n) { // Reverse mutation in the DNA
		chromosome[n - 1].reverse_DNA_mutation(s);
	}
	void complementary_palindrome(int n) { // Finding all the complementary palindromes in the DNA
		cout << "Complementary palindrome's of chromosome " << n << ":\n";
		int sz1 = chromosome[n - 1].get_DNA().first.size();
		int sz2 = chromosome[n - 1].get_DNA().second.size();
		string RNA1 = chromosome[n - 1].get_DNA().first;
		string RNA2 = chromosome[n - 1].get_DNA().second;
		for(int i = 1; i < sz1 - 2; i++) { // Iterating over the fisrt RNA
			int p1 = i, p2 = i + 1;
			while(p1 != -1 && p2 != sz1) {
				if(RNA1[p1] == get_nucleotide(RNA1[p2]) && p2 - p1 != 1) {
					cout << RNA1.substr(p1, p2 - p1 + 1) << '\n';
					p1--, p2++;
				}
				else break;
			}
		}
		for(int i = 1; i < sz2 - 2; i++) { // Iterating over the second RNA
			int p1 = i, p2 = i + 1;
			while(p1 != -1 && p2 != sz2) {
				if(RNA2[p1] == get_nucleotide(RNA2[p2]) && p2 - p1 != 1) {
					cout << RNA2.substr(p1, p2 - p1 + 1) << '\n';
					p1--, p2++;
				}
				else break;
			}
		}
	}
protected:
	vector<Genome> chromosome; 
};