#include <iostream>

using namespace std;
#define ALPHABET_SIZE 26

///////////////////////////////////////////// BEGIN TRIE NODE ///////////////////////////////////////////////////

template <class T> class TrieNode {
private:
	T value; // Utilizzato per indicare la fine della stringa (e' possibile utilizzarlo per ulteriori scopi)
	TrieNode<T>* children[ALPHABET_SIZE];	// Manterra' i riferimenti ai nodi figlio

	/// <summary>
	/// Costruttore TrieNode
	/// </summary>
	TrieNode() {
		value = 0;
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			children[i] = nullptr;
		}
	}

public:

	/// <summary>
	/// Crea un nuovo nodo
	/// </summary>
	/// <returns>Nodo creato</returns>
	static TrieNode<T>* getNode() {
		return new TrieNode<T>();
	}

	/// <summary>
	/// Restituisce l'array dei riferimenti nel nodo
	/// </summary>
	/// <returns>Array dei riferimenti</returns>
	TrieNode<T>** getChildren() {
		return children;
	}

	/// <summary>
	/// Restituisce il valore del nodo
	/// </summary>
	/// <returns>Valore nodo</returns>
	T getValue() {
		return value;
	}

	/// <summary>
	/// Setta il valore di fine stringa
	/// </summary>
	/// <param name="value">Valore di fine stringa</param>
	void setValue(T value) {
		this->value = value;
	}

	/// <summary>
	/// Controlla se i riferimenti a nodi figlio sono vuoti
	/// </summary>
	/// <returns>TRUE: il nodo attuale non ha figli; FALSE: il nodo attuale ha figli</returns>
	bool isEmpty() {
		for (int i = 0; i < ALPHABET_SIZE; i++)
			if (children[i])
				return false;
		return true;
	}
};

///////////////////////////////////////////// END TRIE NODE ///////////////////////////////////////////////////

/////////////////////////////////////////////// BEGIN TRIE CLASS ///////////////////////////////////////////

template <class T> class Trie {
private:
	TrieNode<T> *root;

	/// <summary>
	/// Metodo di servizio ricorsiva per la cancellazione di una parola dal trie
	/// </summary>
	/// <param name="root">Nodo da processare</param>
	/// <param name="key">Parola da cancellare</param>
	/// <param name="depth">Profondit� albero</param>
	/// <returns>Ultimo nodo processato</returns>
	TrieNode<T>* removeHelper(TrieNode<T>* root, string key, int depth = 0) {
		if (!root) {																			// se la radice e' NULL, significa che il Trie non esiste ancora
			return nullptr;
		}

		if (depth == key.length()) {															// se abbiamo raggiunto l'ultimo nodo
			if (root->getValue()) {																// se il suo valore e' diverso da NULL, significa che e' una parola del Trie
				root->setValue(0);																// settiamo il suo valore a NULL per cancellarlo logicamente
			}
			if (root->isEmpty()) {																// se il nodo non ha alcun riferimento a nodi figlio
				delete root;																	// cancelliamo dalla memoria il nodo
				root = nullptr;																	// settiamo il nodo corrente a NULL
			}

			return root;
		}

		int index = tolower(key[depth]) - 'a';													// converto il carattere in indice per l'array dei riferimenti
		root->getChildren()[index] = removeHelper(root->getChildren()[index], key, ++depth);	// scendo l'albero in profondita' fino a raggiungere l'ultimo nodo componente la parola
		
		// arrivato a questo punto, significa che stiamo risalendo l'albero, per poter eliminare i nodi in bottom-up
		if (root->isEmpty() && (!root->getValue())) {											// se il nodo corrente non ha dei riferimenti a nodi figlio e non e' un nodo di fine stringa per un qualche prefisso, lo possiamo eliminare
			delete root;
			root = nullptr;
		}

		return root;
	}


	/// <summary>
	/// Procedura di servizio ricorsiva per la stampa del trie
	/// </summary>
	/// <param name="root">Nodo da processare</param>
	/// <param name="s">Stringa d'appoggio</param>
	/// <param name="depth">Profondita' dell'albero</param>
	void printTrieHelper(TrieNode<T>* root, string s, int depth = 0) {
		if (root->getValue()) {
			s += " ";
			s[depth] = '\0';
			cout << s << " " << root->getValue() << endl;
		}

		for (int i = 0; i < ALPHABET_SIZE; i++) {
			if (root->getChildren()[i]) {
				s += " ";
				s[depth] = toupper(i + 'a');
				printTrieHelper(root->getChildren()[i], s, depth + 1);
			}
		}
	}

public:
	/// <summary>
	/// Istanzia un nuovo Trie
	/// </summary>
	Trie() {
		root = TrieNode<T>::getNode();															// inizialmente, un Trie e' composto da un nodo radice rappresentante la stringa vuota
	}

	/// <summary>
	/// Permette di inserire una nuova parola nel Trie
	/// </summary>
	/// <param name="key">Parola da inserire</param>
	/// <param name="val">Valore di fine stringa da settare</param>
	/// <returns>Ritorna il Trie per permettere inserimenti a cascata</returns>
	Trie<T>* Insert(string key, T val) {
		TrieNode<T>* currentNode = root;														// parto dalla radice

		for (int i = 0; i < key.length(); i++) {
			int index = tolower(key[i]) - 'a';													// converto il carattere in indice per l'array di riferimenti

			if (!currentNode->getChildren()[index]) {											// se non esiste, creiamo un nuovo nodo
				currentNode->getChildren()[index] = TrieNode<T>::getNode();						// crea il nodo
			}

			currentNode = currentNode->getChildren()[index];									// scorro verso il basso
		}

		currentNode->setValue(val);																// raggiunto l'ultimo nodo, setto il suo valore diversamente da null per inserire la parola nel Trie

		return this;																			// inserimento a cascata
	}

	/// <summary>
	/// Permette la ricerca di una parola nel Trie
	/// </summary>
	/// <param name="key">Parola da ricercare</param>
	/// <returns>TRUE: la parola e' nel trie; FALSE: la parola non esiste nel trie</returns>
	bool Search(string key) {
		TrieNode<T>* currentNode = root;														// parto dalla radice

		for (int i = 0; i < (int)key.length(); i++) {
			int index = tolower(key[i]) - 'a';													// converto il carattere in indice per l'array di riferimenti
			
			if (!currentNode->getChildren()[index]) {											// se non esiste il riferimento al carattere corrente, allora la parola non � presente nel Trie
				return false;
			}

			currentNode = currentNode->getChildren()[index];									// attraverso il ramo verso il basso
		}

		if (currentNode && currentNode->getValue()) {											// se l'ultimo nodo ha un valore diverso da null, allora la parola � presente nel Trie
			return true;
		}
		else {
			return false;
		}
	}

	/// <summary>
	/// Permette di rimuovere una parola dal Trie
	/// </summary>
	/// <param name="key">Parola da rimuovere</param>
	Trie<T>* Remove(string key) {
		removeHelper(root, key);																// metodo helper per la cancellazione
		return this;																			// rimozione a cascata
	}

	/// <summary>
	/// Stampa il contenuto del Trie
	/// </summary>
	void PrintTrie() { 
		cout << "------ CONTENUTO TRIE ------" << endl;
		printTrieHelper(root, "");																// metodo helper per la stampa
	}
};

/////////////////////////////////////////////// END TRIE CLASS ///////////////////////////////////////////