#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

// each Vocab is a meaning of a word
class Vocab {
public:
	std::string partOfSpeech;
	std::vector<std::string> synonyms, antonyms;
	std::vector<std::string> meanings, examples; // are words and sentences

	Vocab() {
		// pass
	}

	Vocab(std::string partOfSpeech, std::string meaning, std::string example, std::string synonym) {
		this->partOfSpeech = partOfSpeech;
		this->meanings.push_back(meaning);
		this->examples.push_back(example);
		this->synonyms.push_back(synonym);
		this->meanings.push_back("meaning some meanings2");
		this->examples.push_back("example some examples2");
		this->synonyms.push_back("sysnonym some synonyms2");
	}

	void showPOSAndOtherParts() {
		std::cout << "Part Of Speech: " << this->partOfSpeech << "\n";

		std::cout << "Meanings: ";
		for (auto v : meanings) std::cout << v << "; ";
		std::cout << '\n';

		std::cout << "Examples: ";
		for (auto v : examples) std::cout << v << "; ";
		std::cout << '\n';

		std::cout << "Synonyms: ";
		for (auto v : synonyms) std::cout << v << "; ";
		std::cout << '\n';
	}

	// add one things
	void addMeaning(std::string meaning) {
		this->meanings.push_back(meaning);
	}
	void addExample(std::string example) {
		this->examples.push_back(example);
	}
	void addSynonym(std::string synonym) {
		this->synonyms.push_back(synonym);
	}

	void setPOS(std::string partOfSpeech) {
		this->partOfSpeech = partOfSpeech;
	}

	void editMeaning(std::string oldMeaning, std::string newMeaning) {
		for (int i = 0; i < meanings.size(); i++) {
			if (meanings[i].compare(oldMeaning) == 0) {
				meanings[i] = newMeaning;
				break;
			}
		}
	}

	void editExample(std::string oldExample, std::string newExample) {
		for (int i = 0; i < examples.size(); i++) {
			if (examples[i].compare(oldExample) == 0) {
				examples[i] = newExample;
				break;
			}
		}
	}

	void editSynonym(std::string oldSynonym, std::string newSynonym) {
		for (int i = 0; i < synonyms.size(); i++) {
			if (synonyms[i].compare(oldSynonym) == 0) {
				synonyms[i] = newSynonym;
				break;
			}
		}
	}

	// getter
	std::string getPOS() {
		return this->partOfSpeech;
	}

	void serialize(std::ofstream &fbout) {
		size_t size = partOfSpeech.size();
		fbout.write(reinterpret_cast<const char*>(&size), sizeof(size));
		fbout.write(reinterpret_cast<const char*>(partOfSpeech.c_str()), size);

		size = meanings.size();
		fbout.write(reinterpret_cast<const char*>(&size), sizeof(size));
		for (int i = 0; i < size; i++) {
			size_t size2 = meanings[i].size();
			fbout.write(reinterpret_cast<const char*>(&size2), sizeof(size2));
			fbout.write(reinterpret_cast<const char*>(meanings[i].c_str()), size2);
		}

		size = examples.size();
		fbout.write(reinterpret_cast<const char*>(&size), sizeof(size));
		for (int i = 0; i < size; i++) {
			size_t size2 = examples[i].size();
			fbout.write(reinterpret_cast<const char*>(&size2), sizeof(size2));
			fbout.write(reinterpret_cast<const char*>(examples[i].c_str()), size2);
		}

		size = synonyms.size();
		fbout.write(reinterpret_cast<const char*>(&size), sizeof(size));
		for (int i = 0; i < size; i++) {
			size_t size2 = synonyms[i].size();
			fbout.write(reinterpret_cast<const char*>(&size2), sizeof(size2));
			fbout.write(reinterpret_cast<const char*>(synonyms[i].c_str()), size2);
		}
	}

	void deserialize(std::ifstream& fbin) {
		size_t size;
		fbin.read(reinterpret_cast<char*>(&size), sizeof(size));
		char* buffer = new char[size];
		fbin.read(reinterpret_cast<char*>(buffer), size);
		partOfSpeech.assign(buffer, size);
		delete[] buffer;

		fbin.read(reinterpret_cast<char*>(&size), sizeof(size));
		meanings.resize(size);
		for (int i = 0; i < size; i++) {
			size_t size2;
			fbin.read(reinterpret_cast<char*>(&size2), sizeof(size2));
			buffer = new char[size2];
			fbin.read(reinterpret_cast<char*>(buffer), size2);
			meanings[i].assign(buffer, size2);
			delete[] buffer;
		}

		fbin.read(reinterpret_cast<char*>(&size), sizeof(size));
		examples.resize(size);
		for (int i = 0; i < size; i++) {
			size_t size2;
			fbin.read(reinterpret_cast<char*>(&size2), sizeof(size2));
			buffer = new char[size2];
			fbin.read(reinterpret_cast<char*>(buffer), size2);
			examples[i].assign(buffer, size2);
			delete[] buffer;
		}


		fbin.read(reinterpret_cast<char*>(&size), sizeof(size));
		synonyms.resize(size);
		for (int i = 0; i < size; i++) {
			size_t size2;
			fbin.read(reinterpret_cast<char*>(&size2), sizeof(size2));
			buffer = new char[size2];
			fbin.read(reinterpret_cast<char*>(buffer), size2);
			synonyms[i].assign(buffer, size2);
			delete[] buffer;
		}
	}

};
