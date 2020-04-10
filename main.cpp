//
// Created by isaac on 1/18/2020.
//

#include <fstream>
#include "Boss_Children.h"
#include "Spell_Caster.h"
using namespace std;

//Python checker
#ifdef _WIN32
const string python = "python";
#else
const string python = "python3";
#endif


//Runs the main program for the battle to run properly
//Also runs the Menus and input interpretation for the actions and spells
//Also calculates damage given by spell attacks

void boss_emote(unique_ptr<Boss_Fight> &boss);

/*********** MAIN ********/
int main() {

    Spell_Caster magic;

    string name;
    bool playing = true;
    bool boss_alive;
    int command;
    string filename;
    string syscommand;

    //Player Stats
    int player_hit_points;
    int player_mana;

    bool player_acting;

    string boss_stats;



    while (playing) {
        //Print Opening Prompt, get player's name
        cout << endl << "WELCOME TO THE FOOD ARENA" << endl << endl << "Enter your name:" << endl << endl;
        cin >> name;

        cout << endl << "DEV NOTE: Elemental Weaknesses now work. Try using fire on egg boy, ice on kombucha boy, or lightning on fish boy!" << endl;
        cout << endl << "Choose an enemy: " << endl << "(1) Egg Boy" << endl << "(2) Kombucha Boy" << endl << "(3) Fish Boy" << endl;
        while (!(cin >> command) || (command != 1 && command != 2 && command != 3)) {
            //Input validator - Make sure value isn't 0
            cin.clear();
            string junk;
            getline(cin, junk);
            cout << "ERROR: Did not input 1, 2, or 3" << endl;
            cout << endl << "Choose an enemy: " << endl << "(1) Egg Boy" << endl << "(2) Kombucha Boy" << endl << "(3) Fish Boy" << endl;
        }

        // Establish pointer for the current boss being fought
        unique_ptr<Boss_Fight> current_boss = make_unique<Boss_Fight>();

        //Player chooses which enemy to fight and the enemy changes accordingly.
        if (command == 1) {
            current_boss = make_unique<Egg_Boss>();
            filename = "egg.jpg";
            syscommand = python + " ../image.py " + filename;
            system(syscommand.c_str());
        } else if (command == 2) {
            current_boss = make_unique<Kombucha_Boss>();
        } else if (command == 3) {
            current_boss = make_unique<Fish_Boss>();
        }

        //Display chosen enemy name
        cout << endl << "AN " << current_boss->get_name() << " APPEARS !!!" << endl;

        current_boss->delete_weakness(); //Reset weakness before fight starts

        string response;
        cout << "Would you like to give the enemy a weakness (y/n): " << endl;
        while (!(cin >> response) || (response != "y" && response != "n")) { //Input validator - Make sure value isn't 0
            cin.clear();
            string junk;
            getline(cin, junk);
            cout << "ERROR: Did not input y or n." << endl;
            cout << "Would you like to give the enemy a weakness (y/n): " << endl;
        }
            if (response == "y") {
                current_boss->create_weakness();
            }

            //Initialize Variables
            boss_alive = true;
            command = 0;

            //Player Stats
            player_hit_points = 1000; //Buffed player health so that player can actually win lol
            player_mana = 500; //Added mana to make testing spells easier

            //Battle Time!
            while (boss_alive == true) {

                player_acting = true;

                //This loop allows you to go back and forth between the action menu and spells menu
                while (player_acting) {
                    cout << endl << name << " has " << player_hit_points << " hit points and " << player_mana
                         << " mana!" << endl;

                    //User inputs action command
                    cout << "Choose an action:" << endl << "(1) Attack" << endl << "(2) Spells" << endl
                         << "(3) Scan" << endl;
                    while (!(cin >> command) || (command != 1 && command != 2 && command != 3)) {
                        //Input validator - Make sure value isn't 0
                        cin.clear();
                        string junk;
                        getline(cin, junk);
                        cout << "ERROR: Did not input 1, 2, or 3" << endl;
                        cout << "Choose an action:" << endl << "(1) Attack" << endl << "(2) Spells" << endl
                             << "(3) Scan" << endl;
                    }



                    //Attack
                    if (command == 1) {
                        cout << name << " attacks!" << endl;
                        int player_damage_to_boss = rand() % 9 + 10;
                        current_boss->player_attack(name, player_damage_to_boss);
                        player_acting = false;

                    //Spells
                    } else if (command == 2) {
                        player_acting = magic.spells(current_boss, name, player_mana, player_hit_points);

                    //Scan
                    } else if (command == 3) { //Removed HP Scan, replaced with emote system


                        boss_emote(current_boss);

                        if (current_boss->get_weakness()) { //Only display weakness if there is one
                            cout << "The current_boss is weak to: " << *current_boss->get_weakness() << endl;
                        }

                        cout << "The current_boss has " << current_boss->get_attack() << " attack!" << endl;
                        cout << "The current_boss has " << current_boss->get_defense() << " defense!" << endl;
                        player_acting = false;
                    }

                }


                //Check if the current_boss is alive. Battle ends if it's DEAD.
                boss_alive = current_boss->check_if_boss_alive();


                //BOSS' TURN
                if (boss_alive) {
                    current_boss->boss_turn(name, player_mana, player_hit_points);
                } else if (!boss_alive && player_hit_points > 0) {
                    cout << "ENEMY DEFEATED! YOU WIN!" << endl;
                    cout << "You go back to your dorm and sleep a lot zzzzzzzz" << endl;
                }


                //Check if player alive after current_boss' attack
                if (player_hit_points <= 0) {
                    //end fight loop
                    boss_alive = false;
                    cout << "YOU DIED" << endl;
                }


                //Check player mana, set to 0 if it's below 0
                if (player_mana <= 0) {
                    player_mana = 0;
                }


            }

            //END OF BATTLE LOOP


            //Again Loop
            string again_answer;
            cout << "Play again? (y/n): " << endl;

            while (!(cin >> again_answer) ||
                   (again_answer != "y" && again_answer != "n")) { //Input validator - Make sure value isn't 0
                cin.clear();
                string junk;
                getline(cin, junk);
                cout << "ERROR: Did not input y or n." << endl;
                cout << "Play again? (y/n): " << endl;
            }

            if (again_answer == "n") {
                playing = false;
                cout << endl << endl << endl << "Goodbye!" << endl;
            } else if (again_answer == "y") {
                current_boss->revive();
            }

        }
    return 0;
}

//Boss Emote
//Requires: Nothing
//Modifies: Nothing
//Effects: Prints a general description of how close the boss is to death without reveal its actual hp.
void boss_emote(unique_ptr<Boss_Fight> &boss) {
    cout << "DEBUG: Boss' Current Hit Points: " << boss->get_hit_points() << endl;
    if (boss->get_hit_points() == 100) { //Full Health
        cout << "The enemy looks very healthy." << endl;
    } else if (boss->get_hit_points() >= 50 && boss->get_hit_points() <= 99) { // 50 to 99
        cout << "The enemy looks healthy" << endl;
    } else if (boss->get_hit_points() >= 20 && boss->get_hit_points() <= 49) {
        cout << "The enemy isn't looking so good..." << endl;
    } else {
        cout << "The enemy looks nearly dead!" << endl;
    }
}
