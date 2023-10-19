#pragma once

#include "Vocab.h"

class VocabTree {
public:
	std::vector<Vocab*> otherPOS;
	std::string word; // english

	// init
	VocabTree() {
		// pass
	}
	VocabTree(std::string word) {
		this->word = word;
	}
	
	void serialize(std::ofstream& fbout) {
		size_t size = word.size();
		fbout.write(reinterpret_cast<const char*>(&size), sizeof(size));
		fbout.write(reinterpret_cast<const char*>(word.c_str()), size);

		size = otherPOS.size();
		fbout.write(reinterpret_cast<const char*>(&size), sizeof(size));
		for (int i = 0; i < size; i++) {
			otherPOS[i]->serialize(fbout);
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
		otherPOS.clear();
		otherPOS.resize(size);
		for (int i = 0; i < size; i++) {
			otherPOS[i] = new Vocab();
		}
		for (int i = 0; i < size; i++) {
			otherPOS[i]->deserialize(fbin);
		}
	}

	// checking
	bool havePOS(const std::string& pos ) {
		for (Vocab* pv : otherPOS) {
			if (pv->getPOS().compare(pos) == 0) {
				return true;
			}
		}
		return false;
	}
	bool haveMeaning(const std::string& meaning) {
		for (Vocab* pv : otherPOS) {
			for (std::string s: pv->meanings){
				if (s.compare(meaning) == 0) {
					return true;
				}
			}
		}
		return false;
	}
	bool haveSynonym(const std::string& sysnonym) {
		for (Vocab* pv : otherPOS) {
			for (std::string s : pv->synonyms) {
				if (s.compare(sysnonym) == 0) {
					return true;
				}
			}
		}
		return false;
	}
	bool haveExample(const std::string& example) {
		for (Vocab* pv : otherPOS) {
			for (std::string s : pv->examples) {
				if (s.compare(example) == 0) {
					return true;
				}
			}
		}
		return false;
	}

	// show
	void showWordTree() {
		std::cout << "Word: " << word << "\n";
		for (auto v : otherPOS) {
			v->showPOSAndOtherParts();
		}
	}

	void showMeanings(const std::string& pos) {
		for (Vocab* pv : otherPOS) {
			if (pv->getPOS().compare(pos) == 0) {
				for (const std::string &s : pv->meanings) {
					std::cout << s << "\n";
				}
				return;
			}
		}
	}

	void showExamples(const std::string& pos) {
		for (Vocab* pv : otherPOS) {
			if (pv->getPOS().compare(pos) == 0) {
				for (const std::string& s : pv->examples) {
					std::cout << s << "\n";
				}
				return;
			}
		}
	}

	void showSynonyms(const std::string& pos) {
		for (Vocab* pv : otherPOS) {
			if (pv->getPOS().compare(pos) == 0) {
				for (const std::string& s : pv->synonyms) {
					std::cout << s << "\n";
				}
				return;
			}
		}
	}

	// setter
	void setWord(std::string word) {
		this->word = word;
	}
	
	// getter
	std::string getWord() {
		return word;
	}

	// adding
	void addPOS() {
		Vocab* newPOS = new Vocab();

		std::cout << "Part of Speech: ";
		std::string s;
		std::getline(std::cin, s);
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

		otherPOS.push_back(newPOS);

	}

	// editing
	void editPOS() {
		std::string pos;
		std::cout << "the pos you want to edit: ";
		std::cin >> pos;
		if (!havePOS(pos)) {
			std::cout << "Don\'t have " + pos << "\n";
			return;
		}

		std::cout << "You want to edit?: \n";
		int control;
		
		std::cout << "1. Meanings\n";
		std::cout << "2. Examples\n";
		std::cout << "3. Synonyms\n";
		std::cout << "Other numbers. exit\n";
		std::cout << "?: ";
		std::cin >> control;
		std::cin.ignore();

		while (control >= 1 && control <= 3) {

			if (control == 1) {
				this->showMeanings(pos);

				std::cout << "Old meaning: ";
				std::string oldMeaning;
				std::getline(std::cin, oldMeaning);

				while (!haveMeaning(oldMeaning)) {
					std::cout << "Don\'t have " << oldMeaning << ", try again: ";
					std::getline(std::cin, oldMeaning);
				}

				std::cout << "New meaning: ";
				std::string newMeaning;
				std::getline(std::cin, newMeaning);

				for (int i = 0; i < otherPOS.size(); i++) {
					if (otherPOS[i]->getPOS().compare(pos) == 0) {
						otherPOS[i]->editMeaning(oldMeaning, newMeaning);
						std::cout << "Edit comleted.\n";
						return;
					}
				}

			}
			else if (control == 2) {
				this->showExamples(pos);

				std::cout << "Old example: ";
				std::string oldExample;
				std::getline(std::cin, oldExample);

				while (!haveExample(oldExample)) {
					std::cout << "Don\'t have " << oldExample << ", try again: ";
					std::getline(std::cin, oldExample);
				}

				std::cout << "New example: ";
				std::string newSynonym;
				std::getline(std::cin, newSynonym);

				for (int i = 0; i < otherPOS.size(); i++) {
					if (otherPOS[i]->getPOS().compare(pos) == 0) {
						otherPOS[i]->editExample(oldExample, newSynonym);
						std::cout << "Edit comleted.\n";
						return;
					}
				}
			}
			else if (control == 3) {
				this->showSynonyms(pos);

				std::cout << "Old sysnonym: ";
				std::string oldSynonym;
				std::getline(std::cin, oldSynonym);

				while (!haveExample(oldSynonym)) {
					std::cout << "Don\'t have " << oldSynonym << ", try again: ";
					std::getline(std::cin, oldSynonym);
				}

				std::cout << "New sysnonym: ";
				std::string newSynonym;
				std::getline(std::cin, newSynonym);

				for (int i = 0; i < otherPOS.size(); i++) {
					if (otherPOS[i]->getPOS().compare(pos) == 0) {
						otherPOS[i]->editSynonym(oldSynonym, newSynonym);
						std::cout << "Edit comleted.\n";
						return;
					}
				}
			}

			std::cout << "Continue?: ";
			std::cin >> control;
		}


	}

	// delete
	void deleteAll() {
		word = "";
		for (int i = 0; i < otherPOS.size(); i++) {
			delete otherPOS[i];
		}
		otherPOS.clear();
	}



	

};
