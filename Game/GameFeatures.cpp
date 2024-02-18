#include "GameFeatures.h"
#include <iostream>

GameFeatures& GameFeatures::operator=(const GameFeatures& gameFeature){
    features = gameFeature.features;
    return *this;
}

void GameFeatures::displayFeatures() {
    for(Feature* feature : features) {
        std::cout << feature -> ToString() << std::endl;
    }
} 

void GameFeatures::shuffle() {
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(features), std::end(features), rng);
}

void GameFeatures::clear() {
    auto elem = features.begin();
    while (elem != features.end()) {
        delete *elem;
        //Return iterator to the next element
        elem = features.erase(elem);
    }
}