#pragma once
#include "VocabTree.h"

// must is a prime number which is bigger than the amount of vocabulary we storage
#define MAX_HASHTABLE 41


class MyDict {
public:
	// 41
	std::vector<VocabTree> listOfVocabs;
	std::vector<int> haveAWord;

	int hashVocab(std::string voc) {
		int sum = 0;
		for (int i = 0; i < voc.size(); i++) {
			sum += voc[i] * (i + 1);
		}
		return sum % MAX_HASHTABLE; // demo 30 tu vung, tao table co 41 bucket
	}
	
	// Sắp gỡ bỏ
	MyDict() {
		listOfVocabs.resize(MAX_HASHTABLE);
		haveAWord.resize(MAX_HASHTABLE);

		std::ifstream fin("VocaData.txt");
		
		std::string nextVocab;
		while (std::getline(fin, nextVocab)) {
			
			VocabTree vct;
			vct.word = nextVocab;
			int numOfPOS;
			std::string dummy;
			std::getline(fin, dummy);
			numOfPOS = stoi(dummy);
			for (int c = 0; c < numOfPOS; c++) {
				Vocab* vc = new Vocab();
				// part of speech
				std::string dummy2;
				std::getline(fin, dummy2);
				vc->partOfSpeech = dummy2;

				// meanings
				std::getline(fin, dummy2);
				std::string dummy3;
				std::istringstream sin(dummy2);
				while(std::getline(sin, dummy3, '|')){
					vc->meanings.push_back(dummy3);
				}
				
				// examples
				std::getline(fin, dummy2);
				sin.clear();
				sin.str(dummy2);
				while (std::getline(sin, dummy3, '|')) {
					vc->examples.push_back(dummy3);
				}

				// synonyms
				std::getline(fin, dummy2);
				int numNYMS = stoi(dummy2);
				if (numNYMS){
					std::getline(fin, dummy2);
					sin.clear();
					sin.str(dummy2);
					while (std::getline(sin, dummy3, '|')) {
						vc->synonyms.push_back(dummy3);
					}
				}
				vct.otherMeanings.push_back(vc);
			}

			// hash here
			int index = hashVocab(vct.word);
			while (haveAWord[index]) {
				index = (index + 1) % MAX_HASHTABLE;
			}
			listOfVocabs[index] = vct;
			haveAWord[index] = true;
		}
	}

	void listAll() {
		for (auto v : listOfVocabs) {
			v.showWordTree();
			std::cout << "-----------------------\n";
		}
	}

	void lookUp() {
		std::cout << "The word you want to look up: ";
		std::string inputWord;
		std::getline(std::cin, inputWord);

		int ind = hashVocab(inputWord);
		while (haveAWord[ind] && listOfVocabs[ind].word != inputWord) {
			ind = (ind + 1) % MAX_HASHTABLE;
		}

		if (!haveAWord[ind]) {
			std::cout << "Don\'t have " + inputWord + " in the list of Vocab.\n";
		}
		else {
			listOfVocabs[ind].showWordTree();
		}
		
	}

	void addWord() {
		VocabTree vct;
		std::cout << "Word: ";
		std::string inputWord;
		std::getline(std::cin, inputWord);

		vct.word = inputWord;
		std::string cont = "yes";
		while (cont.compare("yes") == 0) {
			vct.addPOS();
			std::cout << "Next Part of Speech?(yes): ";
			std::getline(std::cin, cont);
		}

		int index = hashVocab(vct.word);
		while (haveAWord[index]) {
			index = (index + 1) % MAX_HASHTABLE;
		}
		listOfVocabs[index] = vct;
		haveAWord[index] = true;
	}

	void deleteWord() {

		std::cout << "The word you want to delete: ";
		std::string inputWord;
		std::getline(std::cin, inputWord);


		int index = hashVocab(inputWord);
		while (haveAWord[index] && listOfVocabs[index].getWord().compare(inputWord)) {
			index = (index + 1) % MAX_HASHTABLE;
		}
		if (!haveAWord[index]) {
			std::cout << "Cannot find " << inputWord << "\n";
		}
		else {
			listOfVocabs[index].deleteAll();
			haveAWord[index] = 0;
		}
	}

	
	void serialize(std::ofstream& fbout) {
		size_t size = listOfVocabs.size();
		fbout.write(reinterpret_cast<const char*>(&size), sizeof(size));
		for (int i = 0; i < size; i++) {
			listOfVocabs[i].serialize(fbout);
		}

		size = haveAWord.size();
		fbout.write(reinterpret_cast<const char*>(&size), sizeof(size));
		for (int i = 0; i < size; i++) {
			fbout.write(reinterpret_cast<const char*>(&haveAWord[i]), sizeof(haveAWord[i]));
		}
	}

	void deserialize(std::ifstream& fbin) {
		listOfVocabs.clear();
		haveAWord.clear();

		size_t size;
		fbin.read(reinterpret_cast<char*>(&size), sizeof(size));
		listOfVocabs.resize(size);
		for (int i = 0; i < size; i++) {
			listOfVocabs[i].deserialize(fbin);
		}

		fbin.read(reinterpret_cast<char*>(&size), sizeof(size));
		haveAWord.resize(size);
		for (int i = 0; i < size; i++) {
			fbin.read(reinterpret_cast<char*>(&haveAWord[i]), sizeof(haveAWord[i]));
		}

	}


};

