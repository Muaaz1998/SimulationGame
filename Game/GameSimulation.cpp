#include "GameSimulation.h"


///@brief Default constructor
GameSimulation::GameSimulation(int aCredit, int aGames) {
    setCredit(aCredit);
    setGames(aGames);
    initializeDefaultFeatures();
}

///@brief override to include custom game features
GameSimulation::GameSimulation(std::vector <Feature*> features, int aCredit, int aGames) {
    setCredit(aCredit);
    setGames(aGames);
    setCustomFeatures(features);
}

void GameSimulation::runSimulation() {
    std::cout << "!!!!!!!WELCOME!!!!!!!" << "\n\n";
    displayResources();
    features.displayFeatures();
    while(getGames() > 0){
        simulation();
        addGames(-1);
        if(getGames() > 0) {
            std::cout << "You have " << getGames() << " games remaining. Would you like to play again?" << std::endl;
            std::cout << "Enter 1 to confirm and 0 to exit" << std::endl;
            std::cin >> selection;
            if(std::cin.fail() || (selection != 1 && selection != 0)) {
                std::cout << "Invalid selection" << std::endl;
                break;
            }else{
                if(selection == 0) {
                    std::cout << "You have chosen to exit the game. Thank you for playing" << std::endl;
                    break;
                }else {
                    //Restart user pick resources and feature vector
                    setPicks(3);
                    std::cout << "\n" << "Feature vector size " << features.count() << std::endl;
                    features.clear();
                    std::cout << "\n" << "Feature vector size " << features.count() << std::endl;
                    initializeDefaultFeatures();
                }
            }
        }
    }
    std::cout << "Game over" << std::endl;
}

void GameSimulation::simulation() {
    while (selection != SELECTIONS::STOPPER && getPicks() > 0) {
        fflush(stdout);
        //Shuffle the features before selection
        features.shuffle();
        std::cout << "\n" << "Pick a number from  1 - 15: ";
        std::cin >> selection;
        selection -= 1;
        if ( std::cin.fail() || selection < 0 || selection > 15) {
            std::cout << "Invalid selection" << std::endl;
            break;
        }
        std::cout << std::endl;
        selection = determineSelection(features.get(selection));
        features.remove(selection);
        if(getPicks() > 0) { addPicks(-1); }
        displayResources();  
    }        
}

int GameSimulation::determineSelection(Feature* feature) {
    int featureType = feature -> getFeatureType();
    Credit* credit;
    FreeGames* games;
    Picks* picks;
    switch (featureType)
        {
        case SELECTIONS::CREDIT:{
            //Downcase from Feature* --> *Credit (Safe cast)
            Credit* credit = (Credit*)(feature);
            addCredits(credit->getAwardAmount());
            std::cout << "Congratulations you won " << (credit -> ToString()) << std::endl;;
            break;
        }
        case SELECTIONS::FREEGAMES:{
            //Downcase from Feature* --> *FreeGames (Safe cast)
            FreeGames* games = (FreeGames*)(feature);
            addGames(games->getAwardAmount());
            std::cout << "Congratulations you won " << games -> ToString() << std::endl;;
            break;
        }
        case SELECTIONS::PICK:{
            //Downcase from Feature* --> *Picks (Safe cast)
            Picks* picks = (Picks*)(feature);
            addPicks(picks -> getAwardAmount());
            std::cout << "Congratulations you won " << picks -> ToString() << std::endl;
            break;
        }
        case SELECTIONS::STOPPER:{
            std::cout << "Uh-oh! Sorry but your selection resulted in game over" << std::endl;
            break;
        }
        default:{
            std::cout << "Uh-oh! Sorry but your selection did not win any prize" << std::endl;
            break;
        
        }
    };
    return featureType;
}

void GameSimulation::initializeDefaultFeatures() {
    features.add(new Credit(500));
    features.add(new Credit(50));
    features.add(new Credit(50));
    features.add(new FreeGames(10));
    features.add(new FreeGames(5));
    features.add(new FreeGames(5));
    features.add(new Picks(2));
    features.add(new Picks(2));
    features.add(new Picks(1));
    features.add(new NoPrize());
    features.add(new NoPrize());
    features.add(new NoPrize());
    features.add(new NoPrize());
    features.add(new NoPrize());
    features.add(new Stopper());
};

void GameSimulation::displayResources() {
    std::cout << std::endl <<"You have ---> " << std::endl;
    showCredits();
    showPicks();
    showGames();
    std::cout << std::endl;        
}
