#include <iostream>
#include <gtk/gtk.h>
#include "clasp/config.h"
#include <bits/stdc++.h>
#include <string.h>
#include "clasp/logic_program.h"
#include "clasp/shared_context.h"
#include "p3/p3.h"

#define maxAttributes 10
using namespace std;

unordered_map<string, pair<string,string>> attributeNames;
vector<vector<pair<int,int>>> constraints;
vector<vector<pair<int,int>>> penalties;
vector<string> penaltyStrings;
vector<int> penaltiesStack;
vector<int> penaltyCost;

// storing blacklisted values as ints so we can easily check before instantiating a bitset
vector<int> blacklistedBinaries;

ifstream attributesFile("inputs/attributes.txt");
ifstream constraintsFile("inputs/constraints.txt");
ifstream possibilisticFile("inputs/possibilistic.txt");
ifstream qualitativeFile("inputs/qualitative.txt");

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
 * @param which 0 for penalty, 1 for possibilistic
 */
void logicProcessing(int which){
    ifstream penaltyFile;
    if(which == 0){
        penaltyFile.open("inputs/penalty.txt");
    } else{
        penaltyFile.open("inputs/possibilistic.txt");
    }
    string rawInput = "";
    int penaltyStack = 0;
    if (penaltyFile.is_open())
        while(penaltyFile.good()) {
            getline(penaltyFile, rawInput);
            penaltyStrings.emplace_back(rawInput);
            vector<pair<int, int>> cur;
            for (int i = 0; i < rawInput.size(); i++) {
                int penalty=0;
                switch (rawInput[i]) {
                    case ',':
                        penaltiesStack.emplace_back(penaltyStack);
                        penalties.emplace_back(cur);
                        penalty = stoi(rawInput.substr(i+1,rawInput.size()-1));
                        penaltyCost.emplace_back(penalty);
                        penaltyStack++;
                        //cout << "Penalty: " << penalty << endl;
                        i = rawInput.size();
                        break;
                    case '!':
                        //cout << "emplaced not, false: " << rawInput[i + 1] << endl;
                        cur.emplace_back(make_pair(rawInput[i + 1] - 48, 0));
                        //penaltiesStack.emplace_back(penaltyStack);
                        i++;
                        break;
                    case 'o':
                        penalties.emplace_back(cur);
                        penaltiesStack.emplace_back(penaltyStack);
                        cur.clear();
                        break;
                    case 'a':
                        //penalties.push_back(cur);
                        break;
                    default:
                        //cout << "penalty default, true: " << rawInput[i] << endl;
                        cur.emplace_back(make_pair(rawInput[i] - 48, 1));
                        //penaltiesStack.emplace_back(penaltyStack);
                        break;

                }
            }
            cur.clear();
            //cout << "----" << endl;
        }
    penaltyFile.close();
}
static void activate (GtkApplication* app,gpointer user_data) {
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Project 3");
    gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);
    gtk_widget_show_all(window);
}
int main(int argc, char **argv) {
    std::cout << "Hello, Gamer!" << std::endl;
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

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

    // if its empty it blacklists everything since the empty set fits in everything
    if(!constraints.empty())
        blacklistedBinaries = blacklistFunction(attributeNames.size(), constraints);

    penaltiesFunction(attributeNames, penaltyStrings, blacklistedBinaries, penalties, penaltiesStack, penaltyCost);

    penalties.clear();
    penaltyStrings.clear();
    penaltiesStack.clear();
    penaltyCost.clear();

    logicProcessing(1);

    for(int i = 0; i < penalties.size(); i++){
        for(int j = 0; j < penalties[i].size(); j++){
            cout << penalties[i][j].first << ' ' << penalties[i][j].second << ' ' << penaltiesStack[i] << '\n';
        }
        cout << "Penalty val = " << penaltyCost[penaltiesStack[i]] << endl;
    }
    possibilisticFunction(attributeNames, penaltyStrings, blacklistedBinaries, penalties, penaltiesStack, penaltyCost);
    return status;
}
