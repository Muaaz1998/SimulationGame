#include "simulation.h"
#include <algorithm>
#include <random>
#include <unistd.h>
#include "iomanip"

void Simulation::runSimulation() {
    int currentSimulation = 0;
    std::vector <long double> averageWinningsPerSimulation(5, 0);
    std::vector <long double> probabilityOfFeaturesPerSimulation(8, 0);
    while (currentSimulation < simulations) {
        initializeFeatures();
        gameInstance(averageWinningsPerSimulation, probabilityOfFeaturesPerSimulation, currentSimulation);
        currentSimulation += 1;
        features.clear();
    }

    std::cout << "Simulation over " << std::endl;  
    
    //Compute probabilities and average winnings across the simulations
    averageWinnings = averageWinningsPerSimulation;
    probabilityOfSelection = probabilityOfFeaturesPerSimulation;
}

void Simulation::gameInstance(std::vector<long double>& averageWinningsPerSimulation, 
                              std::vector<long double>& probabilityOfFeaturesPerSimulation, 
                              int currentSimulation) {
    int picks = 3;
    int selection = FEATURE::BLANK;
    std::vector <long double> featureSelectionProbs(8, 0);
    std::vector <long double> featureWinningAmount(5, 0);
    while (picks > 0 && selection != FEATURE::STOPPER){
        selection = randRange(0, features.size() - 1);
        selection = determineSelectionAndUpdateState(selection, featureSelectionProbs, 
                                                    featureWinningAmount, 
                                                    picks);
        picks -= 1; 
    }

    //Compute the probabilities and average for the current game instance
    
    //Takes into account stopper (i.e the total picks the user made not taking into account picks remaining)
    picks = accumulate(featureSelectionProbs.begin(), featureSelectionProbs.end(), 0);
    computeProbs(featureSelectionProbs, picks);

    //Compute new moving average and probability considering the new game instance
    computeStreamAverage(probabilityOfFeaturesPerSimulation, featureSelectionProbs, currentSimulation);
    computeStreamAverage(averageWinningsPerSimulation, featureWinningAmount, currentSimulation);
}

void Simulation::initializeFeatures()  {
        features.push_back(CREDIT_500);
        features.push_back(CREDIT_50);
        features.push_back(CREDIT_50);
        features.push_back(FREEGAMES_10);
        features.push_back(FREEGAMES_5);
        features.push_back(FREEGAMES_5);
        features.push_back(PICKS_2);
        features.push_back(PICKS_2);
        features.push_back(PICKS_1);
        features.push_back(BLANK);
        features.push_back(BLANK);
        features.push_back(BLANK);
        features.push_back(BLANK);
        features.push_back(BLANK);
        features.push_back(STOPPER);
}


FEATURE Simulation::determineSelectionAndUpdateState(int selectionIdx, 
                                                    std::vector<long double>& featureSelectionProbs, 
                                                    std::vector<long double>& featureWinningAmount, 
                                                    int& picks) {
    FEATURE selection = features[selectionIdx];

    switch (selection)
    {
        case FEATURE::CREDIT_500:
            featureSelectionProbs[0] += 1;
            featureWinningAmount[0] += 500;
            break;
        case FEATURE::CREDIT_50:
            featureSelectionProbs[1] += 1;
            featureWinningAmount[0] += 50;
            break;
        case FEATURE::PICKS_2:
            featureSelectionProbs[2] += 1;
            featureWinningAmount[1] += 2;
            picks += 2;
            break;
        case FEATURE::PICKS_1:
            featureSelectionProbs[3] += 1;
            featureWinningAmount[1] += 1;
            picks += 1;
            break;
        case FEATURE::FREEGAMES_10:
            featureSelectionProbs[4] += 1;
            featureWinningAmount[2] += 10;
            break;
        case FEATURE::FREEGAMES_5:
            featureSelectionProbs[5] += 1;
            featureWinningAmount[2] += 5;
            break;
        case FEATURE::STOPPER:
            featureSelectionProbs[6] += 1;
            featureWinningAmount[3] += 1;
            break;
        default:
            // For the selection Blank(No prize)
            featureSelectionProbs[7] += 1;
            featureWinningAmount[4] += 1;
            break;
    }
    features.erase(features.begin() + selectionIdx);
    return selection;
}

int Simulation::randRange(int min, int max) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(min, max);

    return distr(generator);
}

void Simulation::computeStreamAverage(std::vector<long double>& previous, std::vector<long double>& current, int gamesPlayed) 
{
    for(int i = 0; i < previous.size(); i++) {
        previous[i] = (previous[i] * gamesPlayed + current[i]) / (gamesPlayed + 1);
    }    
}

void Simulation::displayProbabilityOfFeatures() {
    std::cout << "Probability of winning 500 credits " << std::setprecision(8) << std::fixed << probabilityOfSelection[0] << std::endl;
    std::cout << "Probability of winning 50 credits " << std::setprecision(8) << std::fixed << probabilityOfSelection[1] << std::endl;
    std::cout << "Probability of winning 10 free games " << std::setprecision(8) << std::fixed << probabilityOfSelection[4] << std::endl;
    std::cout << "Probability of winning 5 free games " << std::setprecision(8) << std::fixed << probabilityOfSelection[5] << std::endl;
    std::cout << "Probability of selecting Blank(No Prize) " << std::setprecision(8) << std::fixed << probabilityOfSelection[7] << std::endl; 
    std::cout << "Probability of selecting Stopper " << std::setprecision(8) << std::fixed << probabilityOfSelection[6] << std::endl;
}

void Simulation::computeProbs(std::vector<long double>& values, int picks) {
    for(int i = 0 ; i < values.size() ; i++ ) {
        values[i] /= picks;
    }
}