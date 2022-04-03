#include <bits/stdc++.h>
#include <iostream>
#include <p3/p3.h>
#include <string.h>
#include <string>

#define maxAttributes 10
using namespace std;

unordered_map<string, pair<string, string>> attributeNames;
vector<vector<pair<int, int>>> constraints;

vector<vector<pair<int, int>>> penaltiesAndProbabilities;
vector<string> penaltyAndPossibilityStrings;
vector<int> penaltiesAndPossibilitiesStack;
vector<int> penaltiesAndPossibilitiesCosts;
vector<int> qualitativeColumn;
vector<int> qualitativeCost;

vector<vector<string>> penaltiesResult;
vector<vector<string>> possibilisticResult;
vector<vector<string>> qualitativeResult;

// storing blacklisted values as ints so we can easily check before
// instantiating a bitset
vector<int> blacklistedBinaries;

ifstream attributesFile("inputs/attributes.txt");
ifstream file("inputs/constraints.txt");

int selection = 0; // 0 for penalty, 1 for possibilistic, 2 for qualitative

/**
 * AI project 3
 * Francisco Romero, William Daniel Hiromoto, Nolan Boner
 * The goal of this project is to design and build a Knowledge-Based Intelligent
 * System that collects user preferences and reasons about them. Featuring an
 * easy-to-use GUI for collecting, from the user, names of attributes and their
 * values, hard constraints, and preferences. This program will also be able to
 * read inputs from a file.
 */

//region Parse
void selected(int which){
    selection = which;
}
void startProcessing(int which){
    switch(which){
        case 0:
            penaltiesResult = penaltiesFunction(
                    attributeNames, penaltyAndPossibilityStrings, blacklistedBinaries,
                    penaltiesAndProbabilities, penaltiesAndPossibilitiesStack,
                    penaltiesAndPossibilitiesCosts);
            break;
        case 1:
            possibilisticResult = possibilisticFunction(
                    attributeNames, penaltyAndPossibilityStrings, blacklistedBinaries,
                    penaltiesAndProbabilities, penaltiesAndPossibilitiesStack,
                    penaltiesAndPossibilitiesCosts);
            break;
        case 2:
            qualitativeResult = qualitativeFunction(
                    attributeNames, penaltyAndPossibilityStrings, blacklistedBinaries,
                    penaltiesAndProbabilities, penaltiesAndPossibilitiesStack,
                    penaltiesAndPossibilitiesCosts, qualitativeColumn, qualitativeCost);
            break;


    }
}
/**
 * When you press the feasibility button
 */
void bufferFeasability(){
    vector<vector<string>> feasTest;
    BufferFlush(getAttriBuff());
    if (selection == 0){
        feasTest = feasbility(penaltiesResult, 0);
        for(int i = 0; i < feasTest.size(); i++){
            for(int j = 0; j < feasTest[i].size(); j++){
                stringstream science;
                science << setw(30) << feasTest[i][j];
                char daniel[50];
                sprintf(daniel, "%-30s", feasTest[i][j].c_str());
                printf("%-15s", feasTest[i][j].c_str());
                BufferInsert(getAttriBuff(), daniel);
            }
            BufferInsert(getAttriBuff(), "\n");
            cout << endl;
        }
    }
    else if (selection == 1){
        setprecision(1);
        feasTest = feasbility(possibilisticResult, 1);
        for(int i = 0; i < feasTest.size(); i++){
            for(int j = 0; j < feasTest[i].size(); j++){
                if(i > 0 && j > 0){
                    if(feasTest[i][j] == "1")
                        printf("%-15s", feasTest[i][j].c_str());
                    else
                        printf("%-15.2f", stod(feasTest[i][j]));
                }
                else
                    printf("%-15s", feasTest[i][j].c_str());
            }
            cout << endl;
        }
    }
    else{
        feasTest = feasbility(qualitativeResult, 2);
        for(int i = 0; i < feasTest.size(); i++){
            for(int j = 0; j < feasTest[i].size(); j++){
                printf("%-18s", feasTest[i][j].c_str());
            }
            cout << endl;
        }
    }
}
/**
 * When you press the exemplification button
 */
void bufferExemplification(){
    vector<vector<string>> feasTest;
    BufferFlush(getAttriBuff());
    if (selection == 0){
        feasTest = exemplification(feasbility(penaltiesResult,0), 0);
        for(int i = 0; i < feasTest.size(); i++){
            for(int j = 0; j < feasTest[i].size(); j++){
                stringstream science;
                science << setw(30) << feasTest[i][j];
                char daniel[50];
                sprintf(daniel, "%-30s", feasTest[i][j].c_str());
                printf("%-15s", feasTest[i][j].c_str());
                BufferInsert(getAttriBuff(), daniel);
            }
            BufferInsert(getAttriBuff(), "\n");
            cout << endl;
        }
    }
    else if (selection == 1){
        setprecision(1);
        feasTest = exemplification(feasbility(possibilisticResult,1), 1);
        for(int i = 0; i < feasTest.size(); i++){
            for(int j = 0; j < feasTest[i].size(); j++){
                if(i > 0 && j > 0){
                    if(feasTest[i][j] == "1")
                        printf("%-15s", feasTest[i][j].c_str());
                    else
                        printf("%-15.2f", stod(feasTest[i][j]));
                }
                else
                    printf("%-15s", feasTest[i][j].c_str());
            }
            cout << endl;
        }
    }
    else{
        feasTest = exemplification(feasbility(qualitativeResult,2), 2);
        for(int i = 0; i < feasTest.size(); i++){
            for(int j = 0; j < feasTest[i].size(); j++){
                printf("%-18s", feasTest[i][j].c_str());
            }
            cout << endl;
        }
    }
}
/**
 * When you press the Optimization button
 */
void bufferOptimization(){
    printf("\n Science\n");
    vector<vector<string>> feasTest;
    BufferFlush(getAttriBuff());
    if (selection == 0){
        feasTest = optimization(feasbility(penaltiesResult,0), 0);
        for(int i = 0; i < feasTest.size(); i++){
            for(int j = 0; j < feasTest[i].size(); j++){
                stringstream science;
                science << setw(30) << feasTest[i][j];
                char daniel[50];
                sprintf(daniel, "%-30s", feasTest[i][j].c_str());
                printf("%-15s", feasTest[i][j].c_str());
                BufferInsert(getAttriBuff(), daniel);
            }
            BufferInsert(getAttriBuff(), "\n");
            cout << endl;
        }
    }
    else if (selection == 1){
        setprecision(1);
        feasTest = optimization(feasbility(possibilisticResult,1), 1);
        for(int i = 0; i < feasTest.size(); i++){
            for(int j = 0; j < feasTest[i].size(); j++){
                if(i > 0 && j > 0){
                    if(feasTest[i][j] == "1")
                        printf("%-15s", feasTest[i][j].c_str());
                    else
                        printf("%-15.2f", stod(feasTest[i][j]));
                }
                else
                    printf("%-15s", feasTest[i][j].c_str());
            }
            cout << endl;
        }
    }
    else{
        feasTest = optimization(feasbility(qualitativeResult,2), 2);
        for(int i = 0; i < feasTest.size(); i++){
            for(int j = 0; j < feasTest[i].size(); j++){
                printf("%-18s", feasTest[i][j].c_str());
            }
            cout << endl;
        }
    }
}
/**
 * When you press the OmniOptimization button
 */
void bufferOmniOptimization(){
    vector<vector<string>> feasTest;
    BufferFlush(getAttriBuff());
    if (selection == 0){
        feasTest = omniOptimization(feasbility(penaltiesResult,0), 0);
        for(int i = 0; i < feasTest.size(); i++){
            for(int j = 0; j < feasTest[i].size(); j++){
                stringstream science;
                science << setw(30) << feasTest[i][j];
                char daniel[50];
                sprintf(daniel, "%-30s", feasTest[i][j].c_str());
                printf("%-15s", feasTest[i][j].c_str());
                BufferInsert(getAttriBuff(), daniel);
            }
            BufferInsert(getAttriBuff(), "\n");
            cout << endl;
        }
    }
    else if (selection == 1){
        setprecision(1);
        feasTest = omniOptimization(feasbility(possibilisticResult,1), 1);
        for(int i = 0; i < feasTest.size(); i++){
            for(int j = 0; j < feasTest[i].size(); j++){
                if(i > 0 && j > 0){
                    if(feasTest[i][j] == "1")
                        printf("%-15s", feasTest[i][j].c_str());
                    else
                        printf("%-15.2f", stod(feasTest[i][j]));
                }
                else
                    printf("%-15s", feasTest[i][j].c_str());
            }
            cout << endl;
        }
    }
    else{
        feasTest = omniOptimization(feasbility(qualitativeResult,2), 2);
        for(int i = 0; i < feasTest.size(); i++){
            for(int j = 0; j < feasTest[i].size(); j++){
                printf("%-18s", feasTest[i][j].c_str());
            }
            cout << endl;
        }
    }
}
/**
 * Process attributes and store them in the gtk Buffer
 * @param fileName path to file to be parsed
 */
void parseConstraints(string fileName){
    ifstream file(fileName);
    constraints.clear();

    BufferFlush(getConstBuff());
    if (file.is_open())
        while (file.good()) {
            string rawInput;
            rawInput.clear();
            vector<pair<int, int>> cur;
            cur.clear();
            getline(file, rawInput);
            auto it = attributeNames.begin();

            for (int i = 0; i < rawInput.size(); i++) {
                switch (rawInput[i]) {
                    default:
                        // cout << "emplaced default, true: " << rawInput[i] << endl;
                        cur.emplace_back(std::stoi(to_string(rawInput[i])) - 48, 1);
                        it = attributeNames.begin();
                        advance(it, stoi(to_string(rawInput[i]-48)));
                        BufferInsert(getConstBuff(), it->second.second);
                        break;
                    case '!':
                        // cout << "emplaced not, false: " << rawInput[i + 1] << endl;
                        cur.emplace_back(std::stoi(to_string(rawInput[i + 1])) - 48, 0);
                        it = attributeNames.begin();
                        advance(it, stoi(to_string(rawInput[i+1]-48)));
                        BufferInsert(getConstBuff(), it->second.first);
                        i++;
                        break;
                    case 'o':
                        BufferInsert(getConstBuff(), " Or ");
                        constraints.push_back(cur);
                        cur.clear();
                        break;
                    case 'a':
                        BufferInsert(getConstBuff(), " And ");
                        break;
                }
            }
            constraints.push_back(cur);
            cur.clear();
            // cout << "----" << endl;
            BufferInsert(getConstBuff(), "\n");
        }
    file.close();
    /*
    for (int i = 0; i < constraints.size(); i++) {
        for (int j = 0; j < constraints[i].size(); j++) {
            std::cout << constraints[i][j].first << ' ' <<
                      constraints[i][j].second << std::endl;
            //TODO: Turn output back into english according to Project3 Guidelines

            auto it = attributeNames.begin();
            advance(it, constraints[i][j].first);
            for(auto const &pair: attributeNames){
                cout << "Science, Iterator at: " << it->second.first<< ' ' << it->second.second << endl;
            }

            BufferInsert(getConstBuff(), to_string(constraints[i][j].first));
            BufferInsert(getConstBuff(), " ");
            BufferInsert(getConstBuff(), to_string(constraints[i][j].second));
            BufferInsert(getConstBuff(), "\n");

        }
        std::cout << endl;
    }
    */
  }

/** Process attributes and store them in the gtk Buffer */
void parseAttributes(string fileName) {
    ifstream file(fileName);
    string rawInput;

    attributeNames.clear();
    if (file.is_open())
        while (file.good()) {
            getline(file, rawInput);

            regex vowels("[^-0-9a-zA-Z]+");
            rawInput = regex_replace(rawInput, vowels, " ");

            istringstream iss(rawInput);

            string attribute, zero, one;
            iss >> attribute >> zero >> one;
            attributeNames[attribute] = make_pair(zero, one);

        }
    else
        cout << "Couldnt open attributes file";
    BufferFlush(getAttriBuff());
    for (auto it = attributeNames.begin(); it != attributeNames.end(); it++) {
        cout << "Key: " << it->first << "  Value: " << it->second.first << "," <<
             it->second.second << endl;
        BufferInsert(getAttriBuff(), it->first);
        BufferInsert(getAttriBuff(), ": ");
        BufferInsert(getAttriBuff(), it->second.first);
        BufferInsert(getAttriBuff(), ",");
        BufferInsert(getAttriBuff(), it->second.second);
        BufferInsert(getAttriBuff(), "\n");
    }
    file.close();
}

/**
 * does logic and possibilistic and qualitative parsing
 * @param which 0 for penalty, 1 for possibilistic, 2 for qualitative
 */
void logicProcessing(int which, string fileName) {
    penaltiesAndProbabilities.clear();
    penaltyAndPossibilityStrings.clear();
    penaltiesAndPossibilitiesStack.clear();
    penaltiesAndPossibilitiesCosts.clear();
    qualitativeColumn.clear();
    qualitativeCost.clear();
    ifstream file(fileName);

    string rawInput = "";
    string col = "";
    int penaltyStack = 0;
    if (file.is_open())
        while (file.good()) {
            getline(file, rawInput);
            penaltyAndPossibilityStrings.emplace_back(rawInput);
            vector<pair<int, int>> cur;
            for (int i = 0; i < rawInput.size(); i++) {
                int penalty = 0;
                switch (rawInput[i]) {
                    case ',':
                        penaltiesAndPossibilitiesStack.emplace_back(penaltyStack);
                        penaltiesAndProbabilities.emplace_back(cur);
                        penalty = stoi(rawInput.substr(i + 1, rawInput.size() - 1));
                        penaltiesAndPossibilitiesCosts.emplace_back(penalty);
                        penaltyStack++;
                        col = "";
                        col += rawInput[i + 1];
                        qualitativeColumn.push_back(stoi(col));
                        if (which == 2)
                            qualitativeCost.push_back(
                                    stoi(rawInput.substr(i + 2, rawInput.size() - 1)));
                        // cout << "Penalty: " << penalty << endl;
                        i = rawInput.size();
                        break;
                    case '!':
                        // cout << "emplaced not, false: " << rawInput[i + 1] << endl;
                        cur.emplace_back(make_pair(rawInput[i + 1] - 48, 0));
                        // penaltiesAndPossibilitiesStack.emplace_back(penaltyStack);
                        i++;
                        break;
                    case 'o':
                        penaltiesAndProbabilities.emplace_back(cur);
                        penaltiesAndPossibilitiesStack.emplace_back(penaltyStack);
                        cur.clear();
                        break;
                    case 'a':
                        // penaltiesAndProbabilities.push_back(cur);
                        break;
                    default:
                        // cout << "penalty default, true: " << rawInput[i] << endl;
                        cur.emplace_back(make_pair(rawInput[i] - 48, 1));
                        // penaltiesAndPossibilitiesStack.emplace_back(penaltyStack);
                        break;
                }
            }
            cur.clear();
        }
    file.close();
}
//endregion
/**
 * Clears all reused variables, to be used before processing a new function
 * Doesnt clear attributes and constraints
 */
void clearAll(){
    penaltiesAndProbabilities.clear();
    penaltyAndPossibilityStrings.clear();
    penaltiesAndPossibilitiesStack.clear();
    penaltiesAndPossibilitiesCosts.clear();
    qualitativeColumn.clear();
    qualitativeCost.clear();
}
/**
 * For Francisco to test stuff. Dont delete it Nolan!!!!
 */
void frannyTesting(){
    parseAttributes("inputs/attributes.txt");
    if (!constraints.empty())
        blacklistedBinaries = blacklistFunction(attributeNames.size(), constraints);
    parseConstraints("inputs/constraints.txt");
    if (!constraints.empty())
        blacklistedBinaries = blacklistFunction(attributeNames.size(), constraints);
    vector<vector<string>> feasibilityResult;

    /*
    logicProcessing(0, "inputs/penalty.txt");
    penaltiesResult = penaltiesFunction(
            attributeNames, penaltyAndPossibilityStrings, blacklistedBinaries,
            penaltiesAndProbabilities, penaltiesAndPossibilitiesStack,
            penaltiesAndPossibilitiesCosts);
    feasibilityResult = feasbility(penaltiesResult,0);
    exemplification(feasibilityResult,0);
    optimization(feasibilityResult,0);
    omniOptimization(feasibilityResult,0);
    bufferFeasability();
    clearAll();
    *//*
    logicProcessing(1, "inputs/possibilistic.txt");
    possibilisticResult = possibilisticFunction(
            attributeNames, penaltyAndPossibilityStrings, blacklistedBinaries,
            penaltiesAndProbabilities, penaltiesAndPossibilitiesStack,
            penaltiesAndPossibilitiesCosts);
    feasibilityResult = feasbility(possibilisticResult, 1);
    exemplification(feasibilityResult,1);
    optimization(feasibilityResult,1);
    omniOptimization(feasibilityResult,1);
    bufferFeasability();
    clearAll();
    */
    logicProcessing(2, "inputs/qualitative.txt");
    qualitativeResult = qualitativeFunction(
            attributeNames, penaltyAndPossibilityStrings, blacklistedBinaries,
            penaltiesAndProbabilities, penaltiesAndPossibilitiesStack,
            penaltiesAndPossibilitiesCosts, qualitativeColumn, qualitativeCost);
    feasibilityResult = feasbility(qualitativeResult, 2);
    exemplification(feasibilityResult,2);
    optimization(feasibilityResult,2);
    omniOptimization(feasibilityResult,2);
    bufferFeasability();
    clearAll();

}

int main(int argc, char **argv) {
    std::cout << "Hello, Gamer!" << std::endl;
    //frannyTesting();
    wininit(argc, argv);
    return 0;
}
