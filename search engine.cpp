#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
#include <unordered_set>
#include <fstream>
#include <string>
#include <string>
#include <algorithm>

using namespace std;

void tolower(string& line){
	for(int i = 0; i < line.size(); ++ i){
		if(line[i] >= 'A' && line[i] <= 'Z'){
			line[i] += 'a' - 'A';
		}
	}
}

bool isenglish(char c){
	if(c >= 'a' && c <= 'z') return true;
	else return false;
}

vector<string> spilt_the_word(string& line){
	tolower(line);
	vector<string> res;
	string tmp = "";
	for(int i = 0; i < line.size(); ++ i){
		if(isenglish(line[i])){
			tmp += line[i];
		}
		else{
			if(tmp.size() != 0){
				res.push_back(tmp);
				tmp = "";
			}
		}
	}
	if(tmp.size() != 0){
		res.push_back(tmp);
		tmp = "";
	}
	return res;
}

void create_word_index(vector<string>& word_pool, int number_of_line, string filename, int begin, int size){
	ofstream word_file;
	unordered_set<string> se;
	for(int i = 0; i < word_pool.size(); ++ i){
		se.insert(word_pool[i]);
	}
	for(auto s : se){
		string name = "key//" + s + ".txt";
		word_file.open(name, std::ios::out | std::ios::app);
		word_file << to_string(begin) + " " + to_string(size) + " " + to_string(number_of_line) + " " + filename << endl;
		word_file.close();
	}
}

void readfile(unordered_map<string, int>& isword){
	ifstream rfile;
	int index = 1;
	while(index <= 2){
		string name = "p" + to_string(index) + ".txt";
		string line;
		cout << name << endl;
		int number_of_line = 0;
		vector<string> word_pool;
		rfile.open(name);
		streampos begin = 0;
		while(!rfile.eof()){
			getline(rfile, line);
			bool isend = false;
			if(rfile.eof()){
				rfile.seekg(0, ios::end);
				isend = true;
			}
			streampos now = rfile.tellg();
			word_pool = spilt_the_word(line);
			cout << "line " << number_of_line <<  " is :" << line << endl;
			cout << "begin from : " << begin << "  and the size is :" << now - begin << endl;
			for(int i = 0; i < word_pool.size(); ++ i) cout << word_pool[i] << " ";
			cout << endl;
			create_word_index(word_pool, number_of_line, name, (int)begin, (int)(now - begin));
			++ number_of_line;
			begin = now;
			if(isend == true) break;
		}
		cout << "xxxx" << endl;
		rfile.close();
		++ index;
	}
}

unordered_set<string> findintersection(unordered_set<string>& now, string word_name, int first){
	ifstream rfile;
	string name = "key//" + word_name + ".txt";
	unordered_set<string> res;
	rfile.open(name);
	if(!rfile){
		return res;
	}
	string line;
	while(!rfile.eof()){
		getline(rfile, line);
		if(line.size() == 0) continue;
		int index = line.find(' ');
		int num_line = stoi(line.substr(0, index));
		string filename = line.substr(index + 1);
		if(first == 0){
			res.insert(line);
		}
		else if(now.find(line) != now.end()){
			res.insert(line);
		}
	}
	rfile.close();
	return res;
}

struct node{
	int begin;
	int size;
	int line;
	string filename;
	node(int begin, int size, int line, string filename) : begin(begin), size(size), line(line), filename(filename) {}
	bool operator < (const node &b) const{
		return b.filename > filename;
	}
};

void printline(unordered_set<string>& res){
	vector<node> wordnode;
	for(string s : res){
		int index = s.find_first_of(' ');
		string begin_s = s.substr(0, index);
		int index1 = s.find_first_of(' ', index + 1);
		string size_s = s.substr(index + 1, index1 - index - 1);
		int index2 = s.find_first_of(' ', index1 + 1);
		string line_s = s.substr(index1 + 1, index2 - index1 - 1);
		string name = s.substr(index2 + 1);
		cout << begin_s << " " << size_s << " " << line_s << " " << name << endl;
		int begin_int = stoi(begin_s);
		int size_int = stoi(size_s);
		int line_int = stoi(line_s);
		wordnode.push_back(node(begin_int, size_int, line_int, name));
	}
	sort(wordnode.begin(), wordnode.end());
	ifstream word_file;
	string lastfilename = "";
	for(auto node : wordnode){
		cout << "xxx" << endl;
		cout << node.filename << endl;
		if(lastfilename != node.filename){
			if(lastfilename != ""){
				word_file.close();
			}
			word_file.open(node.filename);
		}
		streampos begin = node.begin;
		streampos size = node.size;
		word_file.seekg(begin);
		char *buffer = new char[node.size];
		word_file.read(buffer, node.size);
		buffer[node.size] = '\0';
		cout << buffer;
		delete[] buffer;
		lastfilename = node.filename;
	}
	if(lastfilename != ""){
		word_file.close();
	}
}

int main(){
	unordered_map<string, int> isword;
	//readfile(isword);
	while(true){
		cout << "query>";
		string line;
		getline(cin, line);
		if(line == "exit") break;
		vector<string> word_pool;
		unordered_set<string> res;
		word_pool = spilt_the_word(line);
		for(int i = 0; i < word_pool.size(); ++ i){
			res = findintersection(res, word_pool[i], i);
		}
		printline(res);
	}
	return 0;
}