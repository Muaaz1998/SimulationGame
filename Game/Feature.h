#include <string>
#include "enums.h"

/// @brief Inteface for any game feature


/*
    Our main features file. Constructed using a neat inheritence hierarchy 
    Feature            
        | ---------------> RewardableFeature
        |                       |
        V                       V
    Stopper,                Credit, FreeGames
      NoPrize                  Picks

    This enables us to do the following (see GameFeatures.h and GameSimulation.h)
    `vector<Features*>` and add children pointers of Feature (which includes all of
    Credits, Picks, FreeGames, Stopper, NoPrize) and therefore allow any extension
    possible, such as an additional feature, to be added simly by subclassing Feature/
    RewardableFeature (depending on the type of Feature) 

*/
class Feature {
    protected:
        std::string name;
        void setName(std::string featureName) { name = featureName; }     
    public:
        std::string getFeatureName() { return name; }
        Feature(std::string featureName) { setName(featureName); }
        Feature& operator=(const Feature& feature) {
            setName(feature.name);
            return *this;
        } 
        virtual const SELECTIONS getFeatureType() = 0;
        virtual const std::string ToString() = 0;
};

/// @brief A feature class with an associated reward if picked
/// @brief for example a `pick` is a feature with a reward that allows the player to 
/// @brief to make additional picks from the selections
class RewardableFeature : public Feature {
    protected:
        int rewardAmount;
        RewardableFeature(std::string name, int rewardAmount) : Feature(name) {
            setAwardAmount(rewardAmount);
        }
        void setAwardAmount (int featureRewardAmount) { rewardAmount = featureRewardAmount; }
    public:
        int getAwardAmount() { return rewardAmount; }
        std::string const ToString() { return std::to_string(getAwardAmount()) + " " + getFeatureName(); }
        virtual const SELECTIONS getFeatureType() = 0;

};

/// @brief A rewardable feature - credit, that awards the user `amount` number of credits if picked
class Credit : public RewardableFeature {
    SELECTIONS featuretype = SELECTIONS::CREDIT;
    public:
        Credit(int credits = 50) : RewardableFeature("credits", credits) { };
        std::string const ToString() {return RewardableFeature::ToString(); };
        const SELECTIONS getFeatureType() { return SELECTIONS::CREDIT; }
        

};

/// @brief A rewardable feature - credit, that
class FreeGames : public RewardableFeature {
    public:
        FreeGames(int numberOfGames = 5) : RewardableFeature("free games", numberOfGames) { };
        std::string const ToString() { return RewardableFeature::ToString(); };
        const SELECTIONS getFeatureType() { return SELECTIONS::FREEGAMES; }

};

class Picks : public RewardableFeature {
    public:
        Picks(int picks = 1) : RewardableFeature("extra picks", picks) { };
        std::string const ToString() { return "+" + RewardableFeature::ToString();}
        const SELECTIONS getFeatureType() { return SELECTIONS::PICK; }

};

class NoPrize : public Feature {
    public:
        NoPrize() : Feature("NoPrize") {};
        std::string const ToString() { return "Blank(no prize)"; }
        const SELECTIONS getFeatureType() { return SELECTIONS::NOPRIZE; }

};

class Stopper : public Feature {
    public:
        Stopper() : Feature("Stopper") {};
        std::string const ToString() { return Feature::getFeatureName();};
        const SELECTIONS getFeatureType() { return SELECTIONS::STOPPER; }

};