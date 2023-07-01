#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <cctype>

std::vector<std::string> words = {
    "hangman", "computer", "programming", "openai", "game", "algorithm", "developer", 
    "interface", "variable", "function", "array", "pointer", "class", "object", 
    "inheritance", "polymorphism", "encapsulation", "template", "library", "recursion", 
    "debugging", "compiler", "syntax", "statement", "expression", "conditional", 
    "iteration", "constructor", "destructor", "namespace", "typedef", "enum", 
    "iostream", "vector", "string", "queue", "stack", "algorithm", "sorting", "searching",
    "binary", "tree", "graph", "hash", "linkedlist", "template", "container", "iterator",
    "logic", "iteration", "variable", "algorithm", "condition", "program", "input", 
    "output", "loop", "function", "parameter", "argument", "compiler", "memory", 
    "syntax", "statement", "operator", "pointer", "reference", "constant", "data", 
    "structure", "recursion", "inheritance", "polymorphism", "abstraction", "class", 
    "object", "library", "header", "file", "debugging", "breakpoint", "namespace",
    "apple", "banana", "cat", "dog", "elephant", "fish", "guitar", "house", "internet", 
    "jazz", "kangaroo", "lion", "mango", "notebook", "ocean", "piano", "queen", "robot", 
    "sun", "tiger", "umbrella", "violet", "window", "xylophone", "yoga", "zebra"
};

std::string selectWord(std::vector<std::string> inputWords){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, inputWords.size());

    int randomNum = dis(gen);
    std::string word = inputWords[randomNum];
    return word;
}

std::string generatePresentation(){
    return "Welcome to Hangman game! \nRules: 3 word guesses and 3 letter guesses, guess the word correctly to win! \nIf you run out of word guesses you lose! \n";
}

std::string generateMenu(){
    return "1) guess word \n2) guess letter \n3) quit \n";
}

std::string toLowerCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return result;
}

void clearConsole() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}


int main() {
    std::string word = selectWord(words);
    int letterGuesses = 3; // possible letter guesses
    int wordGuesses = 3; // possible word guesses
    std::string letters = "abcdefghijklmnopqrstuvwxyz";

    std::string presentation = generatePresentation();

    std::cout << presentation << "\n";

    // partial word that will be presented to the user
    std::string incompleteWord;
    for(int i = 0; i<word.size(); i++){
        if(i == 0 || i == word.size() - 1) incompleteWord+=word[i];
        else incompleteWord+="_";
    }

    std::string menu = generateMenu();

    // gameplay
    while(wordGuesses > 0){
        std::cout << "word: "+incompleteWord + "\nRemaning word guesses: "+std::to_string(wordGuesses)+" - Remaning letter guesses: "+std::to_string(letterGuesses)<< " \n";
        std::cout << menu << " \n";

        std::string input;
        std::cin >> input;
        
        if(toLowerCase(input) == "guess word" || toLowerCase(input) == "word" || input == "1"){
            std::string guess;
            std::cout << "Try to guess the word: " << "";
            std::cin >> guess;
            if(toLowerCase(word) == toLowerCase(guess)){
                clearConsole();
                std::cout << "Correct! The word is: "+word << "\n";
                std::cout << "Thanks for playing! :)" << "\n";
                return 0; 
            }else {
                std::cout << "Sorry the word isn't: "+guess+" :( " << "\n";
                wordGuesses--;
            }
        }

        else if(toLowerCase(input) == "guess letter" || toLowerCase(input) == "letter" || input == "2"){
            if(letterGuesses == 0) {
                clearConsole();
                std::cout << "Sorry you don't have any more guesses! " << "\n";
            }else{
                std::string guess;
                while(true){
                    std::cout << "Try to guess the a letter: " << "";
                    std::cin >> guess;
                    if(guess.size() != 1 || letters.find(guess) == std::string::npos){
                        std::cout << "You can only input one letter and make sure it is a valid one (english letter)! " << "\n";
                    }else if(incompleteWord.find(guess) != std::string::npos){
                        std::cout << "You already have this letter! " << "\n";
                    }else break;
                }

                if(word.find(guess) == std::string::npos){
                    clearConsole();
                    letterGuesses--;
                    std::cout << "Sorry the letter "+guess+" is not present in the word! " << "\n";
                }else{
                    for(int i = 0; i<word.size(); i++){
                        if(word[i] == guess[0]) incompleteWord[i] = guess[0];
                    }
                    clearConsole();
                    std::cout << "The letter "+guess+" is present in the word! " << "\n";
                    if(incompleteWord == word){
                        std::cout << "The word is: "+word << "\n";
                        std::cout << "Thanks for playing! :)" << "\n";
                        break;  
                    }
                }
            }
        }

        else if(toLowerCase(input) == "q" || toLowerCase(input) == "e" || toLowerCase(input) == "esc" || toLowerCase(input) == "quit" || input == "3"){ 
            clearConsole();
            std::cout << "Thanks for playing!" << "\n";
            break;
        }

        else{
            clearConsole();
            std::cout << "I didn't understand what you just said :( " << "\n\n";
        }
    }

    clearConsole();
    std::cout << "Sorry you just finished your guesses, the word was: "+word << "\n";
    std::cout << "Thanks for playing!" << "\n";
    
    return 0;
}




