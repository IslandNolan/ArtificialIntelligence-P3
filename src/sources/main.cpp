#include <bits/stdc++.h>
#include <iostream>
#include <p3/p3.h>
#include <string.h>

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
ifstream constraintsFile("inputs/constraints.txt");

/**
 * AI project 3
 * Francisco Romero, William Daniel Hiromoto, Nolan Boner
 * The goal of this project is to design and build a Knowledge-Based Intelligent
 * System that collects user preferences and reasons about them. Featuring an
 * easy-to-use GUI for collecting, from the user, names of attributes and their
 * values, hard constraints, and preferences. This program will also be able to
 * read inputs from a file.
 */

/*
    todo::atributes in binary

    todo::Hard constraints (H) are represented as propositional formulas in the
   Conjunc-tional Normal Form (CNF)

    todo::preferences (T ) in the preference languages of penalty logic,
   possibilistic logic, and qualitative choice logic. Formulas involved in the
   preference theories (i.e., the φ’s and the ψ’s) are of CNF as well.

    todo::Existence of feasible objects: decide whether there are feasible
   objects w.r.t H, that is, whether there are models of H that are truth
   assignments making H true.

    todo::Exemplification: generate, if possible, two random feasible objects,
   and show the preference between the two (strict preference or equivalence)
   w.r.t T .

    todo::Optimization: find an optimal object w.r.t T .

    todo::Omni-optimization: find all optimal objects w.r.t T
*/
/**
 * does logic and possibilistic parsing
 * @param which 0 for penalty, 1 for possibilistic, 2 for qualitative
 */
void logicProcessing(int which){
    ifstream penaltyAndPossibilisticFile;
    if(which == 0){
        penaltyAndPossibilisticFile.open("inputs/penalty.txt");
    } else if(which == 1){
        penaltyAndPossibilisticFile.open("inputs/possibilistic.txt");
    } else{
        penaltyAndPossibilisticFile.open("inputs/qualitative.txt");
    }
    string rawInput = "";
    string col = "";
    int penaltyStack = 0;
    if (penaltyAndPossibilisticFile.is_open())
        while(penaltyAndPossibilisticFile.good()) {
            getline(penaltyAndPossibilisticFile, rawInput);
            penaltyAndPossibilityStrings.emplace_back(rawInput);
            vector<pair<int, int>> cur;
            for (int i = 0; i < rawInput.size(); i++) {
                int penalty=0;
                switch (rawInput[i]) {
                    case ',':
                        penaltiesAndPossibilitiesStack.emplace_back(penaltyStack);
                        penaltiesAndProbabilities.emplace_back(cur);
                        penalty = stoi(rawInput.substr(i+1,rawInput.size()-1));
                        penaltiesAndPossibilitiesCosts.emplace_back(penalty);
                        penaltyStack++;
                        col = "";
                        col += rawInput[i+1];
                        qualitativeColumn.push_back(stoi(col));
                        if(which == 2)
                            qualitativeCost.push_back(stoi(rawInput.substr(i+2,rawInput.size()-1)));
                        //cout << "Penalty: " << penalty << endl;
                        i = rawInput.size();
                        break;
                    case '!':
                        //cout << "emplaced not, false: " << rawInput[i + 1] << endl;
                        cur.emplace_back(make_pair(rawInput[i + 1] - 48, 0));
                        //penaltiesAndPossibilitiesStack.emplace_back(penaltyStack);
                        i++;
                        break;
                    case 'o':
                        penaltiesAndProbabilities.emplace_back(cur);
                        penaltiesAndPossibilitiesStack.emplace_back(penaltyStack);
                        cur.clear();
                        break;
                    case 'a':
                        //penaltiesAndProbabilities.push_back(cur);
                        break;
                    default:
                        //cout << "penalty default, true: " << rawInput[i] << endl;
                        cur.emplace_back(make_pair(rawInput[i] - 48, 1));
                        //penaltiesAndPossibilitiesStack.emplace_back(penaltyStack);
                        break;

                }
            }
            cur.clear();
            //cout << "----" << endl;
        }
    penaltyAndPossibilisticFile.close();
}

int main(int argc, char **argv) {
  std::cout << "Hello, Gamer!" << std::endl;

    //string task;
    //getline(cin, task);

    //testing();
    string rawInput;



    //region Attributes
    attributeNames.clear();
    if (attributesFile.is_open())
        while (attributesFile.good()) {
            getline(attributesFile, rawInput);

            regex vowels("[^-0-9a-zA-Z]+");
            rawInput = regex_replace(rawInput, vowels, " ");

            istringstream iss(rawInput);

            string attribute, zero, one;
            iss >> attribute >> zero >> one;
            attributeNames[attribute] = make_pair(zero, one);

            // cout << "recording: " << attribute << ' ' << zero << ' ' << one << endl;
        }
    else
        cout << "Couldnt open attributes file";
    /*
    for(auto it=attributeNames.begin(); it != attributeNames.end(); it++){
        cout << "Key: " << it->first << "  Value: "  << it->second.first << "," << it->second.second <<  endl;
    }
    */
    attributesFile.close();

    //endregion


    //region Constraints
    constraints.clear();

    if (constraintsFile.is_open())
        while(constraintsFile.good()) {
            rawInput.clear();
            getline(constraintsFile, rawInput);
            vector<pair<int, int>> cur;
            cur.clear();

            for (int i = 0; i < rawInput.size(); i++) {
                switch (rawInput[i]) {
                    default:
                        //cout << "emplaced default, true: " << rawInput[i] << endl;
                        //cout << "Science true: " << std::stoi(to_string(rawInput[i])) - 48 << endl;
                        cur.emplace_back(std::stoi(to_string(rawInput[i])) - 48, 1);
                        break;
                    case '!':
                        //cout << "emplaced not, false: " << rawInput[i + 1] << endl;
                        //cout << "Science false: " << std::stoi(to_string(rawInput[i + 1])) - 48 << endl;
                        cur.emplace_back(std::stoi(to_string(rawInput[i+1])) - 48, 0);
                        i++;
                        break;
                    case 'o':
                        constraints.push_back(cur);
                        cur.clear();
                        break;
                    case 'a':
                        //constraints.push_back(cur);
                        break;


                }
            }
            constraints.push_back(cur);
            cur.clear();
            //cout << "----" << endl;
        }
    constraintsFile.close();
    /*
    for (int i = 0; i < constraints.size(); i++){
        for (int j = 0; j < constraints[i].size(); j++){
            std::cout << constraints[i][j].first << ' ' << constraints[i][j].second << std::endl;
        }
        std::cout << endl;
    }
     */
    //endregion

    logicProcessing(0);
    // if its empty it blacklists everything since the empty set fits in// everything
  if (!constraints.empty())
    blacklistedBinaries = blacklistFunction(attributeNames.size(), constraints);

    penaltiesResult = penaltiesFunction(attributeNames, penaltyAndPossibilityStrings, blacklistedBinaries, penaltiesAndProbabilities, penaltiesAndPossibilitiesStack, penaltiesAndPossibilitiesCosts);

    penaltiesAndProbabilities.clear();
    penaltyAndPossibilityStrings.clear();
    penaltiesAndPossibilitiesStack.clear();
    penaltiesAndPossibilitiesCosts.clear();

    logicProcessing(1);

    for(int i = 0; i < penaltiesAndProbabilities.size(); i++){
        for(int j = 0; j < penaltiesAndProbabilities[i].size(); j++){
            cout << penaltiesAndProbabilities[i][j].first << ' ' << penaltiesAndProbabilities[i][j].second << ' ' << penaltiesAndPossibilitiesStack[i] << '\n';
        }
        cout << "Penalty val = " << penaltiesAndPossibilitiesCosts[penaltiesAndPossibilitiesStack[i]] << endl;
    }
    possibilisticResult = possibilisticFunction(attributeNames, penaltyAndPossibilityStrings, blacklistedBinaries, penaltiesAndProbabilities, penaltiesAndPossibilitiesStack, penaltiesAndPossibilitiesCosts);

    penaltiesAndProbabilities.clear();
    penaltyAndPossibilityStrings.clear();
    penaltiesAndPossibilitiesStack.clear();
    penaltiesAndPossibilitiesCosts.clear();
    qualitativeColumn.clear();

    logicProcessing(2);

    for(int i = 0; i < penaltiesAndProbabilities.size(); i++){
        for(int j = 0; j < penaltiesAndProbabilities[i].size(); j++){
            cout << penaltiesAndProbabilities[i][j].first << ' ' << penaltiesAndProbabilities[i][j].second << ' ' << penaltiesAndPossibilitiesStack[i] << '\n';
        }
        cout << "column = " << qualitativeColumn[i] << " cost = " << qualitativeCost[i] << endl;
    }
    qualitativeResult = qualitativeFunction(attributeNames, penaltyAndPossibilityStrings, blacklistedBinaries, penaltiesAndProbabilities, penaltiesAndPossibilitiesStack, penaltiesAndPossibilitiesCosts, qualitativeColumn, qualitativeCost);
    return 0;
}
