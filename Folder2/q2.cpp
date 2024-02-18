#include <iostream>
#include <string>
#include "simulation.cpp"

using namespace std;

int main () {
    Simulation sim = Simulation(100000);
    sim.runSimulation();
    sim.displayProbabilityOfFeatures();
    cout << endl << "Average picks: " << sim.getAveragePicks() << endl; 
    cout << endl << "Average credits: " << sim.getAverageCredits() << endl; 

    return 0;
}
