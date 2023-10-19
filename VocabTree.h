#pragma once

#include "Vocab.h"

class VocabTree {
public:
	std::vector<Vocab*> otherMeanings;
	std::string word; // english
	VocabTree() {
		// pass
	}
	VocabTree(std::string word) {
		this->word = word;
	}

	void showWordTree() {
		std::cout << "Word: " << word << "\n";
		for (auto v : otherMeanings) {
			v->showPOSAndOtherParts();
		}
	}

	void setWord(std::string word) {
		this->word = word;
	}
	std::string getWord() {
		return word;
	}


	void addPOS() {
		Vocab* newPOS = new Vocab();

		std::cout << "Part of Speech: ";
		std::string s;
		std:getline(std::cin, s);
		newPOS->setPOS(s);

		std::cout << "Meaning: ";
		std::getline(std::cin, s);
		newPOS->addMeaning(s);

		std::cout << "Example: ";
		std::getline(std::cin, s);
		newPOS->addExample(s);

		std::cout << "Synonym: ";
		std::getline(std::cin, s);
		newPOS->addSynonym(s);

		otherMeanings.push_back(newPOS);

	}

	void deleteAll() {
		word = "";
		for (int i = 0; i < otherMeanings.size(); i++) {
			delete otherMeanings[i];
		}
		otherMeanings.clear();
	}

	void serialize(std::ofstream& fbout) {
		size_t size = word.size();
		fbout.write(reinterpret_cast<const char*>(&size), sizeof(size));
		fbout.write(reinterpret_cast<const char*>(word.c_str()), size);

		size = otherMeanings.size();
		fbout.write(reinterpret_cast<const char*>(&size), sizeof(size));
		for (int i = 0; i < size; i++) {
			otherMeanings[i]->serialize(fbout);
		}
	}

	void deserialize(std::ifstream& fbin) {
		size_t size;
		fbin.read(reinterpret_cast<char*>(&size), sizeof(size));
		char* buffer = new char[size];
		fbin.read(reinterpret_cast<char*>(buffer), size);
		word.assign(buffer, size);
		delete[] buffer;

		fbin.read(reinterpret_cast<char*>(&size), sizeof(size));
		otherMeanings.clear();
		otherMeanings.resize(size);
		for (int i = 0; i < size; i++) {
			otherMeanings[i] = new Vocab();
		}
		for (int i = 0; i < size; i++) {
			otherMeanings[i]->deserialize(fbin);
		}
	}

};
