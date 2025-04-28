#ifndef TRAVELLING_SALES_PERSON_PSOFORTAXI_HPP
#define TRAVELLING_SALES_PERSON_PSOFORTAXI_HPP

#include <vector>
#include <cmath>
#include <string>
#include <random>
#include <iostream>
#include <algorithm>
#include "structs.hpp"

class PSOForTaxi{
public:
    PSOForTaxi(float minLatForPassangers, float maxLatForPassangers, float minLonForPassangers, float maxLonForPassangers,
               std::vector<place> taxiLocations, int maxIterations, int particleNumber, float inertia, float accelerationPerson,
               float accelerationSocial): taxiLocations_(taxiLocations), maxIterations_(maxIterations),
               particleNumber_(particleNumber), inertiaCoeff_(inertia), personalAcc_(accelerationPerson), socialAcc_(accelerationSocial){
        //Creates a random number generator
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_real_distribution<float> passangerLat(minLatForPassangers, maxLatForPassangers);
        std::uniform_real_distribution<float> passangerLon(minLonForPassangers, maxLonForPassangers);
        //Initelizes the passenger vector with the locations of the passengers
        for (int i = 0; i < taxiLocations_.size(); i++){
            passangers_.push_back({std::to_string(i), passangerLat(generator), passangerLon(generator)});
            //Prints out the passengers location to make it easy to copy into python to get nice graphs and plots
            std::cout << "(" << passangers_[i].latitude << ", " << passangers_[i].longitude << ")," << std::endl;
        }
        //Initelizes the distance matrix to get the cost for moving between a taxi location and a passanger
        distanceMatrix_.resize(taxiLocations_.size(), std::vector<float>(passangers_.size()));
        for (int i = 0; i < taxiLocations_.size(); i++) {
            for (int j = 0; j < passangers_.size(); j++) {
                float distance = sqrt(pow((taxiLocations_[i].latitude - passangers_[j].latitude), 2) +
                                       pow((taxiLocations_[i].longitude - passangers_[j].longitude), 2));
                distanceMatrix_[i][j] = distance;
            }
        }
        //Creates the initial particles
        for (int i = 0; i < particleNumber; i++){
            particles_.push_back(taxiLocations.size());
        }
        //Calculates the cost of the initial particles
        calculatCost();
    }

    void calculatePSO() {
        //Creates a random number generator
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_real_distribution<float> accPerson(0, personalAcc_);
        std::uniform_real_distribution<float> accSocial(0, socialAcc_);

        //Runs through all the particles
        for (int i = 0; i < particleNumber_; i++){
            //Creates a vector which stores which passangers are picked up and not
            std::vector<int> pickedUpPassangers;
            pickedUpPassangers.resize(particles_[i].position.size());
            for (int j = 0; j < particles_[i].position.size(); j++){
                //Calculates the particles movement in every direction
                particles_[i].velocity[j] = inertiaCoeff_ * particles_[i].velocity[j]
                                            + accPerson(generator) * (particles_[i].pbPosition[j] - particles_[i].actualPosition[j])
                                            + accSocial(generator) * (bestParticle_.pbPosition[j] - particles_[i].actualPosition[j]);

                particles_[i].actualPosition[j] += particles_[i].velocity[j];
                //Checks if the particle is out of bounds
                if (particles_[i].actualPosition[j] > particles_[i].position[j].size()){
                    particles_[i].actualPosition[j] = particles_[i].position[j].size() - 1;
                    particles_[i].velocity[j] = 0;
                } else if (particles_[i].actualPosition[j] < 0){
                    particles_[i].actualPosition[j] = 0;
                    particles_[i].velocity[j] = 0;
                }
                //Fills the particles matrix of which taxi picks up which passenger with zeroes
                std::fill(particles_[i].position[j].begin(), particles_[i].position[j].end(), 0);
                //Finds which passenger the particle wants to pick up with which taxi
                int wantedUpdate = round(particles_[i].actualPosition[j]);
                //Makes sure that two taxis don't picks up the same passanger, this part could have been done better
                //because it will just move to the next passanger if the most perferable isn't available,
                //but it works with enough iterations.
                while (particles_[i].position[j][wantedUpdate] != 1) {
                    if (pickedUpPassangers[wantedUpdate] == 0) {
                        particles_[i].position[j][wantedUpdate] = 1;
                        pickedUpPassangers[wantedUpdate] = 1;
                        break;
                    }
                    wantedUpdate = (wantedUpdate + 1) % particles_[i].position[j].size();
                }
            }
        }
        //Creates one more particle per iteration to keep exploring
        particles_.push_back(taxiLocations_.size());
        iterations_++;
        calculatCost();
        checkFinish();
    }

private:
    void calculatCost(){
        //Calculates the cost for all the particles
        for (int i = 0; i < particleNumber_; i++){
            for (int j = 0; j < particles_[i].position.size(); j++){
                for (int k = 0; k < particles_[i].position[j].size() - 1; k++){
                    if (particles_[i].position[j][k] == 1){
                        particles_[i].cost += distanceMatrix_[j][k];
                        break;
                    }
                }
            }
            //Checks if it is a new personal best
            if (particles_[i].cost < particles_[i].pbCost){
                particles_[i].pbCost = particles_[i].cost;
                for (int j = 0; j < particles_[i].position.size(); j++){
                    for (int k = 0; k < particles_[i].position[j].size(); k++){
                        if (particles_[i].position[j][k] == 1){
                            particles_[i].pbPosition[j] = k;
                            break;
                        }
                    }
                }
            }
            //Checks if it is a new global best
            if (particles_[i].pbCost < bestParticle_.pbCost){
                bestParticle_ = particles_[i];
            }
            particles_[i].cost = 0;
        }
    }

    void checkFinish(){
        //Checks if the loop is finished and prints lowest cost
        if (iterations_ == maxIterations_) {
            for (int i = 0; i < bestParticle_.position.size(); i++){
                //Makes sure the matrix is printed on a form which is easy to copy into python to get plots and graphs
                std::cout << "]," << std::endl;
                std::cout << "[";
                for (int j = 0; j < bestParticle_.position[i].size(); j++){
                    std::cout << bestParticle_.position[i][j] << "," << " ";
                }
            }
            std::cout << "Lowest cost: " << bestParticle_.pbCost << std::endl;
        } else if (iterations_ < maxIterations_){
            std::cout << bestParticle_.pbCost << ", " << std::endl;
        }
    }

private:
    std::vector<std::vector<float>> distanceMatrix_;
    std::vector<place> taxiLocations_;
    std::vector<place> passangers_;
    std::vector<particle> particles_;
    particle bestParticle_;
    int maxIterations_;
    int iterations_ = 0;
    int particleNumber_;
    float inertiaCoeff_;
    float personalAcc_;
    float socialAcc_;
};

#endif //TRAVELLING_SALES_PERSON_PSOFORTAXI_HPP