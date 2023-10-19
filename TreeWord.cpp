
#include "MyDict.h"


int main() {

    // Chạy duy nhất một đoạn code này khi muốn reset từ điển về các từ mặc định
    
    /*std::ofstream fbout("TuVungNhiPhan.txt", std::ios::binary);
    MyDict md;
    md.serialize(fbout);
    fbout.close();*/
    

    
    // LOAD DATA
    MyDict md;
    std::ifstream fbin("TuVungNhiPhan.txt", std::ios::binary);
    if (fbin.fail()) return 1;
    md.deserialize(fbin);
    fbin.close();

    
    std::cout << "Do you want to add?(yes): ";
    std::string wantToAdd;
    std::getline(std::cin, wantToAdd);
    if (wantToAdd.compare("yes") == 0) {
        fbin.open("TuVungNhiPhan.txt", std::ios::binary);
        if (fbin.fail()) return 1;

        md.addWord();
        std::cout << "Added completely.\n";

        fbin.close();
    }
    

    // TRY TO LOOKUP
    std::cout << "Try to lookup some words?(yes): ";
    std::string test;
    std::getline(std::cin, test);

    if (test.compare("yes")==0) {
        md.lookUp();
    }


    // TRY TO DELETE SOME WORDS
    std::cout << "Try to delete some words?(yes): ";
    std::getline(std::cin, test);

    if (test.compare("yes") == 0) {
        md.deleteWord();
    }

    // 
    /*
    
    Word: question
    Part Of Speech: noun
    Meanings: question; inquiry; interrogation;
    Examples: He asked a question about the project; She has a question for the teacher;
    Synonyms: inquiry; query; interrogation;
    Part Of Speech: verb
    Meanings: to question;
    Examples: I question my colleagues for input; She questions the motive behind the decision;
    Synonyms:
    Part Of Speech: adj
    Meanings: questionable; doubtful;
    Examples: The question mark is meaningful; The question behavior is suspicious;
    Synonyms:
    
    */

    md.list();

    // UPDATE
    std::ofstream fbout("TuVungNhiPhan.txt", std::ios::binary);
    if (fbout.fail()) return 1;
    md.serialize(fbout);
    std::cout << "SAVED ALL NEW UPDATE. SEE YOU LATER.\n";
    fbout.close();
    
    

    return 0;
}

