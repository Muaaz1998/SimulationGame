#include <iostream>
#include <vector>
#include <string>
using namespace std;

//function decleration
int findConsecutiveSymbols(const std::vector<string> &symbols, string symbolToFind);
void testfindConsecutiveSymbols();

int main() {
    ///Run some test cases
    std::vector<std::vector <std::string>> testSymbols = 
    {
        {"Ace", "Ace", "Jack", "Queen", "Queen", "Queen", "Queen","Ace", "Ace", "Ace"},  
        {"Ace"}, 
        {"Ace", "Ace", "Jack", "Ace", "Ace"}, 
        {"Ace", "Jack", "Ace", "King", "Ace", "Queen"}
    };

    std::vector<std::string> testSymbolsToFind = {"Queen", "Ace", "Ace", "Ace"};
    for(int i = 0;  i<testSymbolsToFind.size(); i++){
        for(std::vector<std::string> symbolList :testSymbols) {
            int consecutiveCount = findConsecutiveSymbols(symbolList, testSymbolsToFind[i]);
            std::cout << "Number of consecutive " << testSymbolsToFind[i] << " symbols from the left: " << consecutiveCount << std::endl;
        }
    }
    return 0;
}

/// @brief Given an vector of card ranks as `symbols` and a specific rank named `symbolToFind` 
/// @brief returns the length of the longest sequence of consecutive `symbolToFind` in `symbol`
/// @param symbols string vector of card ranks 
/// @param symbolToFind string representation of a single card rank
/// @return / length of the longest sequence of consecutive `symbolToFind` in `symbol`
int findConsecutiveSymbols(const std::vector<string> &symbols, string symbolToFind) {
    int longestSequenceOfSymbols = 0;
    int currentChainLength = 0;
    for (string symbol : symbols) {
        if(symbol == symbolToFind) {
            currentChainLength ++;
        }else{
            currentChainLength = 0;
        }
        if(currentChainLength > longestSequenceOfSymbols) {
            longestSequenceOfSymbols = currentChainLength;
        }
    }

    return longestSequenceOfSymbols;
}

/// @brief A function which generates and runs test cases on out `findConsecutiveSymbols` function
void testfindConsecutiveSymbols() {
    std::vector<std::vector <std::string>> testSymbols = 
    {
        {"Ace", "Ace", "Jack", "Queen", "Queen", "Queen", "Queen","Ace", "Ace", "Ace"},  
        {"Ace"}, 
        {"Ace", "Ace", "Jack", "Ace", "Ace"}, 
        {"Ace", "Jack", "Ace", "King", "Ace", "Queen"}
    };

    std::vector<std::string> testSymbolsToFind = {"Queen", "Ace", "Ace", "Ace"};
    for(int i =0; i <= testSymbolsToFind.size(), i++;){
        for(std::vector<std::string> symbolList :testSymbols) {
            int consecutiveCount = findConsecutiveSymbols(symbolList, testSymbolsToFind[i]);
            std::cout << "Number of consecutive " << testSymbolsToFind[i] << " symbols from the left: " << consecutiveCount << std::endl;
        }
    }

}