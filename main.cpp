#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct FileNotFound {
	string message;
	string filename;
};

vector<string> loadWords(string filename);
void display(pair<string, int> p);
bool overOne(pair<string, int> p);

int main()
{
	cout << "Welcome to the Word Analyzer App\n\n";

	//get words to analyze
	string filename = "poem.txt";
	//cout << "Enter filename: ";
	//cin >> filename;
	//cin.ignore(1000, '\n');
	vector<string> words;
	try
	{
		words = loadWords(filename);
	}
	catch(const FileNotFound e)
	{
		cout << e.message << '\n';
		cout << "You entered: " << e.filename << "\n\n";
		cout << "Closing Program...\n\n";
		return 0;
	}
	cout << '\n' <<words.size() << " words\n";
	for(string word : words)
	{
		cout << word << ' ';
	}
	cout << "\n\n";

	//get unique words
	map<string, int> wordsMap;
	for (string word : words)
	{
		for(int i = 0; i < word.length(); ) // make all words have only letters and all lowercase
		{
			//no iterator so no skip chars
			char c = word[i];
			if(!(c >= 'a' && c <= 'z') && !(c>= 'A' && c <= 'Z'))
			{
				word.erase(i,1);
			}
			else
			{
				word[i] = tolower(c);
				i++;
			}
		}

		if(word == "")
		{
			continue;
		}

		auto iter = wordsMap.find(word);
		if(iter != wordsMap.end())// add to count
		{
			iter->second += 1;
		}
		else //not in map yet
		{
			wordsMap.insert({word, 1});
		}
	}

	cout << wordsMap.size() << " UNIQUE WORDS: ";
	for_each(wordsMap.begin(), wordsMap.end(), display);

	int duplicate = count_if(wordsMap.begin(), wordsMap.end(), overOne);

	cout <<"\n\n" << duplicate << " Duplicate Words: ";

	for(pair<string, int> p : wordsMap)
	{
		if(overOne(p))
		{
			display(p);
		}
	}

	cout << "\n\nCiao\n\n";
	return 0;
}

//load words from file into vector
vector<string> loadWords(string filename)
{
	vector<string> words;
	ifstream inputfile(filename);

	if(inputfile)
	{
		string word;
		while(inputfile >> word)
		{
			words.push_back(word);
		}
		inputfile.close();
		return words;
	}
	else
	{
		FileNotFound error;
		error.message = "File Not Found";
		error.filename = filename;
		throw error;
	}
}

void display(pair<string, int> p)
{
	cout << p.first << "=" << p.second << " ";
}
bool overOne(pair<string, int> p)
{
	return p.second > 1;
}
