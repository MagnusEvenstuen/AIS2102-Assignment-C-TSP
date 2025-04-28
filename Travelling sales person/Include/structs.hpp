#ifndef TRAVELLING_SALES_PERSON_STRUCTS_HPP
#define TRAVELLING_SALES_PERSON_STRUCTS_HPP
#include <string>
#include <vector>
#include <random>

struct place {
    std::string name;
    float latitude;
    float longitude;

    place(std::string name, float lat, float lon)
            : name(name), latitude(lat), longitude(lon) {}
};

struct placeDistance{
    std::string placeToPlace;
    float euclidianDistance;
    float phermoneLevel;

    placeDistance(std::string name, float distance, float pheromone):
    placeToPlace(name), euclidianDistance(distance), phermoneLevel(pheromone){}
};

struct ant {
    place location;
    double cost;
    std::vector<std::string> visitedLocations;
    std::vector<std::string> tripsTaken;

    ant(const place& start)
            : location(start), cost(0) {
        visitedLocations.push_back(start.name);
    }
};

struct particle{
    std::vector<std::vector<int>> position;
    std::vector<float> actualPosition;
    std::vector<float> velocity;
    float cost;
    std::vector<int> pbPosition;
    float pbCost;

    particle(int dimentions = 100) : cost(9999999.99), pbCost(9999999.99) {
        //Initielizitses the matrices witn N*N of zeroes.
        position.resize(dimentions, std::vector<int>(dimentions, 0));
        std::vector<int> pickedUpPassangers;
        pickedUpPassangers.resize(dimentions, 0);
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<int> randomInt(0, dimentions - 1);
        velocity.resize(dimentions, 0.0f);
        actualPosition.resize(dimentions, 0.0f);
        pbPosition.resize(dimentions, 0.0f);

        for (int i = 0; i < dimentions; i++){
            int positionToFill = randomInt(generator);
            while (pickedUpPassangers[positionToFill] == 1){
                positionToFill = randomInt(generator);
            }
            pickedUpPassangers[positionToFill] = 1;
            position[i][positionToFill] = 1;
            actualPosition[i] = positionToFill;
            pbPosition[i] = positionToFill;
        }
    }
};

#endif //TRAVELLING_SALES_PERSON_STRUCTS_HPP
