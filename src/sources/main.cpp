#include <iostream>
#include <gtk/gtk.h>
#include "clasp/config.h"
#include <bits/stdc++.h>
#include "clasp/logic_program.h"
#include "clasp/shared_context.h"
#include "p3/p3.h"

#define maxAttributes 10
using namespace std;

vector<vector<string>> items; // attribute items

ifstream attributesFile("inputs/attributes.txt");
ifstream constraintsFile("inputs/constraints.txt");
ifstream penaltyFile("inputs/penalty.txt");
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

static void activate (GtkApplication* app,gpointer user_data) {
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Project 3");
    gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);
    gtk_widget_show_all(window);
}
int main(int argc, char **argv) {
    std::cout << "Hello, World!" << std::endl;
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    testing();


    return status;

}