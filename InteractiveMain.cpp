#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Trie.cpp"

using namespace std;

template<typename T>
void commandHandler(Trie<T> *);

int main() {
	srand(time(0));

	Trie<int>* trie = new Trie<int>();

	cout << "------------- INTERACTIVE TRIE ----------------------------" << endl << endl;

	while (1) {
		cout << "1) Print Trie" << endl;
		cout << "2) Insert word" << endl;
		cout << "3) Search word" << endl;
		cout << "4) Remove word" << endl;
		cout << "q / Q to quit" << endl << endl;
		cout << "cmd > ";

		commandHandler(trie);
	}
}

template<typename T>
void commandHandler(Trie<T> *trie){
	int cmd;
	cin >> cmd;

	cout << endl;

	switch (cmd)
	{
	case 0:
		exit(1);
	case 1:
		trie->PrintTrie();
		break;
	case 2:{
		cout << endl << "++++ INSERT ++++" << endl;
		string word;
		int value;
		cout << "Word: ";
		cin >> word;
		cout << endl << "Value: ";
		cin >> value;
		if(!value){
			cout << "Invalid input. Try again!" << endl;
			exit(0);
		}
		trie->Insert(word, value);
		cout << endl;
		trie->PrintTrie();
	}
	break;
	case 3:{
		cout << endl << "++++ SEARCH ++++" << endl;
		string word;
		cout << "Word: ";
		cin >> word;
		cout << endl;
		trie->Search(word) ? cout << "Presente\n" : cout << "Non presente\n";
	}
	break;
	case 4:{
		cout << endl << "++++ REMOVE ++++" << endl;
		string word;
		cout << "Word: ";
		cin >> word;
		trie->Remove(word);
		cout << endl;
		trie->PrintTrie();
	}
	break;
	default:
		break;
	}

	cout << endl << endl;
}