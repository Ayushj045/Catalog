#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cmath>
#include <nlohmann/json.hpp> 

using json = nlohmann::json;


long long convertToDecimal(const std::string &strValue, int base) {
    long long decodedNumber = 0;
    int exponent = 0;


    for (int i = strValue.size() - 1; i >= 0; --i) {
        char currentChar = strValue[i];
        int digitValue = (currentChar >= '0' && currentChar <= '9') ? (currentChar - '0') : (currentChar - 'A' + 10);
        decodedNumber += digitValue * std::pow(base, exponent);
        ++exponent;
    }
    return decodedNumber;
}


double calculateConstantTerm(const std::vector<std::pair<int, long long>> &coordinates) {
    double constantTerm = 0.0;
    int totalPoints = coordinates.size();

    
    for (int i = 0; i < totalPoints; ++i) {
        double termResult = coordinates[i].second; // y-value

       
        for (int j = 0; j < totalPoints; ++j) {
            if (i != j) {
                termResult *= static_cast<double>(-coordinates[j].first) / (coordinates[i].first - coordinates[j].first);
            }
        }
        constantTerm += termResult;
    }

    return constantTerm;
}

int main() {
    
    std::ifstream inputFile("test_case.json");
    json inputData;
    inputFile >> inputData;

    
    std::vector<std::pair<int, long long>> decodedPoints;

    
    for (auto iter = inputData.begin(); iter != inputData.end(); ++iter) {
        if (iter.key() == "keys") continue; 

        int xValue = std::stoi(iter.key()); 
        int baseValue = std::stoi(iter.value()["base"].get<std::string>()); 
        std::string encodedY = iter.value()["value"]; 

        
        long long decodedY = convertToDecimal(encodedY, baseValue);
        decodedPoints.push_back({xValue, decodedY}); // Store (x, y) pair
    }

    
    double secretConstant = calculateConstantTerm(decodedPoints);

    
    std::cout << "The constant term (c) is: " << secretConstant << std::endl;

    return 0;
}
