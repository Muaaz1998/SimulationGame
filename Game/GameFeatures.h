#include <vector>
#include <random>
#include <algorithm>
#include "Feature.h"

/// @brief A class for holding, setting, getting and shuffling game features
class GameFeatures {
    private:
        /// @brief A pointer to a vector of features which can hold `Credis`, `Picks`, `FreeGames`
        /// @brief `NoPrize` or `Stopper`
        std::vector<Feature*> features;
    public:
        //Default constructor
        GameFeatures(){}

        //Copy operator
        GameFeatures& operator=(const GameFeatures& gameFeature);

        ///Helper functions
        void add(Feature* feature) { features.push_back(feature); }
        void remove(int index) {features.erase(features.begin() + index); }
        int count() {return features.size(); }
        void clear();
        
        /// @brief getters 
        Feature* get(int index) { return features[index]; }
        
        /// @brief Displays the list of available features 
        void displayFeatures();
        
        /// @brief shuffles our game features so that the same selection doesn't always result in the
        /// @brief same outcome
        void shuffle();
    };
