#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Trie.cpp"

using namespace std;

template <typename T>
void INSERT_TEST(Trie<T>* trie, int num_words, string* parole);

template <typename T>
void SEARCH_TEST(Trie<T>* trie, string* parole);

template <typename T>
void INSERT_SEARCH_TEST(Trie<T>* trie);

template <typename T>
void REMOVE_TEST(Trie<T>* trie, string* parole);


int main() {
	srand(time(NULL));

	const int num_words = 5;
	string parole[num_words] = { "Algoritmo", "Amazon", "Astronauta", "Asterix", "Sogno" };										// Parole da inserire nel Trie (esempio relazione)

	Trie<int>* trie = new Trie<int>();																							// creo un trie

	INSERT_TEST(trie, num_words, parole);

	cout << endl;

	SEARCH_TEST(trie, parole);

	cout << endl;

	INSERT_SEARCH_TEST(trie);

	cout << endl;

	REMOVE_TEST(trie, parole);
	
}


template <typename T>
void INSERT_TEST(Trie<T>* trie, int num_words, string* parole) {
	cout << "---------------- INSERT TEST ----------------------------------" << endl;

	for (int i = 0; i < num_words; i++) {
		cout << "Insert: \"" << parole[i] << "\"" << endl;
		trie->Insert(parole[i], ((rand() % 50) + 1));																			// INSERT: inserisco le parole nel Trie
	}
	//trie->Insert(parole[0], 10)->Insert(parole[1], 20)->Insert(parole[2], 30)->Insert(parole[3], 40)->Insert(parole[4], 50);	// Inserimento a cascata

	cout << endl;

	trie->PrintTrie();																											// PRINT_TRIE: stampo il contenuto del Trie

	cout << "-------------------------------------------------------------------------" << endl;
}

template <typename T>
void SEARCH_TEST(Trie<T>* trie, string* parole) {
	cout << "---------------- SEARCH TEST ----------------------------------" << endl;

	trie->PrintTrie();
	cout << endl;

	cout << "Search: \"" << parole[0] << "\": ";
	trie->Search(parole[0]) ? cout << "Presente\n" : cout << "non presente\n";													// Search: cerco una parola esistente

	cout << "Search: \"" << parole[4] << "\": ";
	trie->Search(parole[4]) ? cout << "Presente\n" : cout << "non presente\n";

	string stringNotInTrie = "Amazzone";
	cout << "Search: \"" << stringNotInTrie << "\": ";
	trie->Search(stringNotInTrie) ? cout << "Presente\n" : cout << "non presente\n";											// Search: ricerca di una parola non esistente

	cout << "-------------------------------------------------------------------------" << endl;
}

template <typename T>
void INSERT_SEARCH_TEST(Trie<T>* trie) {
	cout << "---------------- INSERT AND SEARCH TEST ----------------------------------" << endl;

	string wordNotInTrie = "Amazzone";																							// Aggiungo la parola "Amazzone"
	cout << "Insert: \"" << wordNotInTrie << "\"" << endl;
	trie->Insert(wordNotInTrie, 60);
	cout << endl;
	trie->PrintTrie();
	cout << endl;
	cout << "Search: \"" << wordNotInTrie << "\": ";
	trie->Search(wordNotInTrie) ? cout << "Presente\n" : cout << "non presente\n";												// Adesso "Amazzone" viene trovato nel Trie

	string prefix = "Astro";																									// Aggiungo "Astro", prefisso di "Astronauta"
	cout << "Insert: \"" << prefix << "\"" << endl;
	trie->Insert(prefix, 70);
	cout << endl;
	trie->PrintTrie();
	cout << endl;

	cout << "-------------------------------------------------------------------------" << endl;
}

template <typename T>
void REMOVE_TEST(Trie<T>* trie, string* parole) {
	cout << "---------------- REMOVE TEST ----------------------------------" << endl;

	cout << endl << "++++++ BEFORE REMOVE ++++++" << endl << endl;
	trie->PrintTrie();																											// Il Trie rimane inalterato

	// Rimuovo 4 parole dal Trie;
	string wordNotInTrie = "Algo";
	string prefix = "Astro";
	cout << endl <<  "Removing words: " <<  wordNotInTrie << ", " << parole[4] << ", " << parole[2] << ", " <<  prefix << endl;
	
	trie->Remove(wordNotInTrie);																								// CASO 1: parola non presente nel Trie
	trie->Remove(parole[4]);																									// CASO 2: la word non ha prefix, e lei stessa non e' prefix
	trie->Remove(parole[2]);																									// CASO 4: esiste un prefix della word da cancellare
	trie->Remove(prefix);																										// CASO 3: la word e' prefix di un'altra word

	cout << endl << "++++++ AFTER REMOVE ++++++" << endl << endl;
	trie->PrintTrie();

	cout << "-------------------------------------------------------------------------" << endl;
}
