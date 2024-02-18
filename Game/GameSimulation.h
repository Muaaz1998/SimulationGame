#include "GameFeatures.cpp"
#include <iostream>
/*
    Our main class for simulating the game. 
*/
class GameSimulation {

    // Data members private access by default
    int creditRemaining;
    int freeGamesRemaining;
    int picksRemaining = 3;
    GameFeatures features;
    int selection = SELECTIONS::NOPRIZE;

    public:
        //Default constructor
        GameSimulation(int aCredit = 0, int aGames = 1);

        GameSimulation(std::vector <Feature*> features, int aCredit = 0, int aGames = 1);

        /// @brief Our main game engine. Runs the game until the user is out of `FreeGames`
        void runSimulation();
        int getCredits() { return creditRemaining; }
        int getGames() { return freeGamesRemaining; }
        int getPicks() { return picksRemaining; }
        int getSelection() { return selection; }
    
    private:
        /// @brief Our main game simulation. Perpetuates the game until the user runs out of picks
        /// @brief or the user selects the stooper
        void simulation();
        void setCustomFeatures(std::vector <Feature*> customFeatures) {
            for (Feature* feature : customFeatures) {
                features.add(feature);
            }
        }
        /// @brief Used to display the features available for the user to select
        /// @param features a `vector` of pointers which are subclasses of `Feature` 
        void displayFeatures(GameFeatures features) { features.displayFeatures(); }
        
        ///@brief A set of default features to run the simulation if a custom list of features isn't
        ///@brief provided when constructing a `GameSimulation` instance
        void initializeDefaultFeatures();
        
        void setCredit(int aCredit) { creditRemaining = aCredit; }
        void setGames(int aGames) { freeGamesRemaining = aGames; }
        void setPicks(int picks) {picksRemaining = picks; }
        void addGames(int noOfGames) { freeGamesRemaining += noOfGames; }
        void addPicks(int picks) { picksRemaining += picks; }
        void addCredits(int credits) { creditRemaining += credits; }
        
        /// @brief Displays the available user resources (Credits, Picks, FreeGames)
        void displayResources();
        void showCredits() { std::cout << "Credits " << getCredits() << std::endl; }
        void showGames() { std::cout << "Free games: " << getGames() << std::endl; }
        void showPicks() { std::cout << "Picks " << getPicks() << std::endl; }

        /// @brief Determines the type of user selection (Credit, Picks, FreeGames etc.) and updates
        /// @brief the game state accordingly (ex - add picks to user resources if user won picks)
        /// @param feature the feature assigned to the user based on their random selection
        /// @return the enumerated feature type of the user's selection
        int determineSelection(Feature* feature);

};

