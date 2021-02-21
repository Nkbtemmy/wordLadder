#include<iostream>
#include <fstream>
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<set> 

using namespace std;

//class with characters and methods needed at a 
class wordLadder {
	private:
		queue<stack<string>> allPossibleLadder;
		string lastWord;
		string firstWord;
		set<string> words;
		set<string> usedWord;
	
	public:
		set<string> generateAllWords(string);
		stack<string> getLadder();
		void getLadderH();	
		wordLadder(string first, string last, set<string> words);
	
};
int getIndex(string word, set<string> &words);
void screen_clear();
set<string> copyWords(ifstream& get);

int main()
{
	char tryAgain;
	string firstWord, secondWord;
	cout << endl << " \t \t \t welcome in Game \n \t \t \t -------------- \n \t \t Enter two english word to provide ladder \n \n";
	set<string> words;
	ifstream file("EnglishWords 1.dat");
	if (!file.is_open()){
				cout << "We don't have file you are looking in this directory \n";
				return 0;
	 }
	words = copyWords(file);
	int indexOfFirst = -1, indexOfSecond = -1;
	do {
			do {
				while (indexOfFirst == -1) {
					cout << "Enter first word :";
					cin >> firstWord;
					indexOfFirst = getIndex(firstWord, words);
					if (indexOfFirst == -1) {
						cout << "\n no such word exist, you can try again \n";
					}
				}
				while (indexOfSecond == -1) {
				
					cout << "enter second word :";
					cin >> secondWord;
					indexOfSecond = getIndex(secondWord, words);
		
					if (indexOfSecond == -1) {
						cout << " \n no such word exist , you can try again \n ";
					}
				}
				if (firstWord.size() != secondWord.size()) {
					cout << "\n file size must equal try again \n";
					indexOfFirst = indexOfSecond = -1;
				}
			}
	  while (firstWord.size() != secondWord.size());
            
			wordLadder wordLadder(firstWord, secondWord,words);
			stack<string> ladder = wordLadder.getLadder();
		
			if (ladder.empty()) {
				cout << "\n unable to find ladder \n ";
			}
			else {
				stack<string> reverses ;
				while (!ladder.empty()) {
					reverses.push(ladder.top());
					ladder.pop();
				}
				cout<<" \n ladder: ";
				while(!reverses.empty()){
						cout << reverses.top() << "-> ";
					 reverses.pop();
				}
				cout<<"\n \n";
			}
				
			cout << "\n \n do you want to try Game again ? \'y\' for yes :";
			cin >> tryAgain;
			cin.clear();
			if (tryAgain == 'y') {
				screen_clear();
				indexOfFirst = indexOfSecond = -1;
				
			}
	} while (tryAgain == 'y');
}
//functions definitions
	 wordLadder::wordLadder(string first, string last, set<string> words) {
		this->words = words;
		this->lastWord = last;
		this->firstWord = first;
		usedWord.insert(first);
	}

	stack<string> wordLadder::getLadder() {
		stack<string> ladder;
		ladder.push(this->firstWord);
		allPossibleLadder.push(ladder);
		getLadderH();
		if (this->allPossibleLadder.empty()) {
			ladder.pop();
			return ladder;
		}
		else {
			return this->allPossibleLadder.front();
		}
	}
	void wordLadder::getLadderH() {
		stack<string> ladder = this->allPossibleLadder.front();
		this->allPossibleLadder.pop();
		string currentWord = ladder.top();
		set<string> allPossibleWords = generateAllWords(currentWord);
		for (auto word : allPossibleWords) {
			stack<string> newLadder(ladder);
			newLadder.push(word);
			this->allPossibleLadder.push(newLadder);
		}
		string nextWord;
		if (!this->allPossibleLadder.empty()) {
			ladder = this->allPossibleLadder.front();
			nextWord = ladder.top();
		}
		
		if (allPossibleLadder.empty()) {
		
			return;
		}
		else if (!nextWord.compare(lastWord)) {
			return;
		}
		else {
			getLadderH();
		}
	}
	set<string> wordLadder::generateAllWords(string word) {
		set<string> possibleWords;
		
		for (int i = 0; i < word.size(); i++) {
			string wordP = word;
			for (char c = 'a'; c <= 'z'; ++c) {
				string str(1, c);
				wordP.replace(i,1,str);
				if (usedWord.find(wordP) == usedWord.end())
				{
					if (getIndex(wordP, this->words) != -1) {		
						possibleWords.insert(wordP);
						this->usedWord.insert(wordP);
					}
				}
			}
		}
		return possibleWords;
	}
	
	//function to clear screen if you want to restart game
	void screen_clear()
	{
	  system ( "CLS" );
	}
	
	//check if words is exist in used words set
	int getIndex(string word, set<string> &words) {
		set<string>::iterator it = words.find(word);
		
	
		if (it == words.end()) {
			return -1;
		}
		else {
			return distance(words.begin(), it);
		}
	}
	
	set<string> copyWords(ifstream& file)
	{  
		set<string> strings;
		string word;
		while (file>> word) {
			strings.insert(word);
		}
		file.close();
		return strings;
	}
	
