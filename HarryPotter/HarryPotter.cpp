#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

bool cmp(const pair<string, int> &first, const pair<string, int> &second){
	return first.second > second.second;
}


int main(){
setlocale(LC_ALL, "rus");
stringstream ss;
string delimetrs = " \"'!,.\t\n\0;:?";


string str;
ifstream in("Harry.txt");
if(!in){
	cout << "Error" << endl;
}

ss << in.rdbuf();
str = ss.str();

int begin = 0;
int count = 0;
int leng = 0;
int check = 0;
vector<string> words;


while(begin != str.size()){
		leng = str.find_first_of(delimetrs, begin) - begin;
		words.push_back(str.substr(begin, leng));
		begin += leng + 1;
}


for(vector<string>::iterator it1 = words.begin(); it1 != words.end(); ){
	for(string::iterator it2 = it1 -> begin(); it2 != it1 -> end(); ){
		if (ispunct(*it2)){
			it1 -> erase(it2);
			it2 = it1 -> begin();
		}
		else it2++;
	}
	if(*it1==""){
		words.erase(it1);
		it1 = words.begin();
	}
	else it1++;
}


map<string, int> M;

for(int i(0); i<words.size(); i++){
	if (M.find(words[i]) == M.end()) {
		pair<string, int> p;
		p.first = words[i];
		p.second = 1;
		M.insert(p);
	}
	else M.find(words[i])->second++;
}

cout << "Number of words: " << words.size() << ". Number of different: " << M.size()<< endl;

fstream out;
out.open("out.txt", fstream::out);
for(map<string, int>::iterator iter = M.begin(); iter != M.end(); iter++){
	out << "Word: " << "\"" << (iter -> first) << "\"" << " Number: " << (iter -> second) << endl; 
}

vector<pair<string, int>> ww;
for(map<string, int>::iterator it = M.begin(); it != M.end(); it++){
	ww.push_back(*it);
}
sort(ww.begin(), ww.end(), cmp);


out.close();
int counter(0);
out.open("out_sort.txt", fstream::out);
for(vector<pair<string, int>>::iterator iter = ww.begin(); iter != ww.end(); iter++){
	out << "Word: " << "\"" << (iter -> first) << "\"" << " Number: " << (iter -> second) << endl; 
	counter++;
	if(counter>20) break;
}
return 0;
}

