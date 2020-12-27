#include <iostream>
#include "Trie.cpp"

using namespace std;

template<typename T>
void commandHandler(Trie<T> *);

void printCommands();

int main() {
	Trie<int>* trie = new Trie<int>();

	cout << "------------- INTERACTIVE TRIE ----------------------------" << endl << endl;

	while (1) {
		printCommands();
		commandHandler(trie);
	}
}

void printCommands(){
	cout << "1) Print Trie" << endl;
	cout << "2) Insert word" << endl;
	cout << "3) Search word" << endl;
	cout << "4) Remove word" << endl;
	cout << "q / Q to quit" << endl << endl;
	cout << "cmd > ";
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
		cout << endl << "Value (> 0): ";
		cin >> value;
		if(value <= 0 || cin.fail()){
			cout << endl << "Value must be a number grater than zero!" << endl;
			cin.clear();
			fflush(stdin);
			break;
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
	}

	cout << endl << endl;
}