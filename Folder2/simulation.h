#include <iostream>
#include <vector>

/// @brief Enumerated values for each feature in the simulation to allow us to use switch and 
/// @brief modify the simulation state seamlessly
enum FEATURE {
    CREDIT_500, 
    CREDIT_50, 
    FREEGAMES_10,
    FREEGAMES_5,
    PICKS_2, 
    PICKS_1,  
    BLANK, 
    STOPPER
};

/// @brief Interface for our main simulation lass
class Simulation {
    std::vector <FEATURE> features;
    int simulations;
    std::vector<long double> probabilityOfSelection;
    std::vector<long double> averageWinnings;

    public:
        /// @brief  Constructor for our simulation
        /// @param simulationsToRun - Number of simulations before returining the vairables of interest
        Simulation(int simulationsToRun = 100000) : simulations(simulationsToRun) {}
        
        /// @brief Runs `simulation` number of game simulations and computes the mean of
        /// @brief of all the variables of interest (for ex Credits, Picks etc.) 
        void runSimulation();

        ///Getters
        double getAverageCredits() {return averageWinnings[0]; }
        double getAveragePicks() {return averageWinnings[1]; }
        
        /// @brief Helper function to render the probability of selecting a given `feature` after
        /// @brief the specified number of simulations
        void displayProbabilityOfFeatures();

    private:
        /// @brief Represents a single play of the player where they keep selecting features 
        /// @brief until they run out of picks
        void gameInstance(std::vector<long double>& averageWinningsPerSession, 
                            std::vector<long double>& probabilityOfFeatures, int currentSimulation);

        /// @brief Initializes the default features
        void initializeFeatures();

        /// @brief Generates a a random number from a uniform distribution within
        /// @brief (min, max) using the mersenne twister algorithm 
        int randRange(int max, int min);

        /// @brief Computes the average of a stream of numbers. In this case we feed either - the vector of
        /// @brief probabilites (i.e probability of selecting a feature where each index corresponds
        /// @brief to the probability of selecting a particular feature) or winnings (vector representing
        /// @brief the average feature winnings per run, for ex - average credits won per game). 
        /// @param previous vector representing the average values computed till `currentSimulationRun`
        /// @param current latest vector of values (probabilities / average winnings)
        /// @param currentSimulationRun the i-th simulation where i = 1....simulations
        void computeStreamAverage(std::vector<long double>& previous, std::vector<long double>& current, int currentSimulationRun);
        
        /// @brief Determines the selection made by the player and updates the game state accordingly.
        /// @brief For example if the player selected `+2 picks` increments the `picks` of the player
        /// @brief updates the index of the vector corresponing to the probabilities and average winnings
        /// @brief and removes the selection from the `feature` vector (to represent non-replacement) per run.
        /// @param selectionIdx the number selected by the player
        /// @param featureSelectionProbs the vector corresponding to the feature selection probabilities per game
        /// @param featureWinningAmount the vector corresponding to the average feature winnings per game.
        /// @param picks current number of picks remaining for the player (updated in case of selection corresponds to +2/+1 picks)
        /// @return the feature selected by the player (used to terminate the game incase feature == STOPPER)
        FEATURE determineSelectionAndUpdateState(int selectionIdx, 
                                                std::vector<long double>& featureSelectionProbs, 
                                                std::vector<long double>& featureWinningAmount, 
                                                int& picks);

        /// @brief Helper function to compute the probabilities of each feature
        /// @param values the probability vector
        /// @param picks total picks made by the user in the current game instance (takes into account STOPPER)
        void computeProbs(std::vector<long double>& values, int picks);
};