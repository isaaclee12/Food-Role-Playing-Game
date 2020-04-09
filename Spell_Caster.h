//
// Created by isaac on 3/30/2020.
//

#ifndef IL_PROJECT5_SPELL_CASTER_H
#define IL_PROJECT5_SPELL_CASTER_H

#include "Boss_Children.h"

class Spell_Caster {
private:

public:
    //Default Constructor
    Spell_Caster() {
        srand(time(NULL));
    }

    //Yhatzee
    // Requires: Nothing
    // Modifies: Nothing
    // Effects: Rolls a random number from 1 to 102. Returns a spell command depending on the number rolled.
    int yhatzee(){

        int roll = rand() % 101 + 1;

        cout << "YOU ROLLED: " << roll << " WHICH MEANS:" << endl;

        if (roll == 102) { //instakill
            return 100;
        } else if (roll == 101) {
            return 0;
        } else if (80 < roll && roll <= 100) {
            return 5;
        } else if (60 < roll && roll <= 80) {
            return 4;
        } else if (40 < roll && roll <= 60) {
            return 3;
        }
        else if (0 < roll && roll <= 20) {
            return 1;
        }
        else {
            return 0;
        }
    }

    //CHECK MANA
    // Requires: 2 integer inputs
    // Modifies: Nothing
    // Effects: a simple boolean to check if the player has enough mana to cast a spell
    bool check_mana(int player_mana, int mana_cost) {
        if (player_mana < mana_cost) {
            return false; //False if not enough mana
        }
        return true;
    }

    //attackSpell
    // Requires: pointer to a BossFight object, 2 integers (spell min/max), and a pointer to an integer (playerMana)
    // Modifies: the hitPoints of the Boss
    /* Effects: Using the given min/max values for a spell (min = b, max = a + b),
    This function chooses a random integer value in the range of that min and max.
    It then returns that value.*/
    int attack_spell(unique_ptr<Boss_Fight> &boss, int a, int b, int mana_lost, int &player_mana, string type) {
        player_mana -= mana_lost;\
        opt_string weakness = boss->get_weakness();
        if (type != weakness) { //IF NOT WEAKNESS
            return rand() % a + b;
        } else { //IF WEAKNESS
            cout << endl << boss->get_name() << " is weak to " << weakness.value() << "!" << endl;
            return 2*(rand() % a + b);
        }
    }

    //Offensive Spells
    //Here so that I don't have to write it again for yhatzee
    //boss, name, player_mana, mana_lost, command, spell_damage
    bool offensive_spells(unique_ptr<Boss_Fight> &boss, string name, int &player_mana, int &mana_lost, int command, int &spell_damage) {
        /* ATTACK SPELLS:
                 * These lower the boss' hit points by a random integer value
                 * within a certain range (See spell descriptions for details)
                 */

        bool enough_mana;

        //Hotspicy
        if (command == 1) {

            enough_mana = check_mana(player_mana, 10);
            if (enough_mana){
                cout << name << " casts Hotspicy!" << endl;
                mana_lost = 10;
                spell_damage = attack_spell(boss, 20, 20, mana_lost, player_mana, "Fire");

                return false;
            } else {
                cout << "Not enough mana!" << endl;
            }


            //Cold Stare
        } else if (command == 2) {
            enough_mana = check_mana(player_mana, 10);
            if (enough_mana){
                cout << name << " casts Cold Stare!" << endl;
                mana_lost = 20;
                spell_damage = attack_spell(boss, 10, 30, mana_lost, player_mana, "Ice");

                return false;
            } else {
                cout << "Not enough mana!" << endl;
            }

            //Death by Lightning
        } else if (command == 3) {
            enough_mana = check_mana(player_mana, 10);
            if (enough_mana){
                cout << name << " casts Death by Lightning!" << endl;
                mana_lost = 40;
                spell_damage = attack_spell(boss, 30, 60, mana_lost, player_mana, "Lightning");

                return false;
            } else {
                cout << "Not enough mana!" << endl;
            }

            /* DEBUFF SPELLS
             * These spells decrease the boss' attack or defense,
             * thereby decreasing how much damage they give and/or take
             */

            //Defortify
        } else if (command == 4) {
            enough_mana = check_mana(player_mana, 10);
            if (enough_mana) {
                cout << name << " casts Defortify! The enemy's defense is decreased!" << endl;

                int lost_defense = rand() % 10 + 10;
                cout << "DEBUG: lost_defense = " << lost_defense << endl;
                boss->set_defense(boss->get_defense() - lost_defense);

                player_mana -= 15;
                return false;
            } else {
                cout << "Not enough mana!" << endl;
            }

            //Unswole
        }
        else if (command == 5) {
            enough_mana = check_mana(player_mana, 10);
            if (enough_mana) {
                cout << name << " casts Unswole! The enemy's attack is decreased!" << endl;


                int lost_attack = rand() % 10 + 10;
                cout << "DEBUG: lost_attack = " << lost_attack << endl;
                boss->set_attack(boss->get_defense() - lost_attack);

                player_mana -= 15;
                return false;
            } else {
                cout << "Not enough mana!" << endl;
            }
        } else { //If command wasn't 1-5
            return true;
        }
    }

    // Print Spells
    // Requires: Nothing
    // Modifies: Nothing
    // Effects: Prints the list of spell options
    void print_spells() {
        cout << "Choose a spell:" << endl << "(1) Hotspicy" << endl << "(2) Cold Stare" << endl << "(3) Death by Lightning" << endl
             << "(4) Defortify" << endl << "(5) Unswole" << endl << "(6) Yhatzee" << endl << "(7) SPELL DESCRIPTIONS" << endl << "(8) Go Back" << endl;
    }


    /************** SPELLS MAIN ALGORITHM******************/
    // Requires: A pointer to a BossFight object, a string, and two pointers to integers for the players hit points and mana
    // Modifies: a boolean
    /* Effects: Prints the list of spells and asks the player to choose a spell by entering the respective integer.
    Depending on the spell chosen, a different effect occurs.*/
    bool spells(unique_ptr<Boss_Fight> &boss, string name, int &player_mana, int &player_hit_points) {
        int command;

        bool casting = true;
        bool enough_mana;

        while (casting == true) {

            //User inputs spell command
            print_spells();

            //Input Validator
            while (!(cin >> command) || (command != 1 && command != 2 && command != 3
                                         && command != 4 && command != 5 && command != 6 && command != 7 && command != 8)) { //Input validator - Make sure value is a # in 1-7
                cin.clear();
                string junk;
                getline(cin, junk);
                cout << "ERROR: Did not input a number from 1 through 7" << endl;
                print_spells();
            }


            int mana_lost = 0;
            int spell_damage = 0;

            casting = offensive_spells(boss, name, player_mana, mana_lost, command, spell_damage);
            if (spell_damage != 0) { //if there was damage taken, then the boss takes damage
                boss->set_hit_points(boss->get_hit_points() - spell_damage);
                cout << "The enemy takes " << spell_damage << " damage!" << endl;
            }

            //Yhatzee
            // This spell causes you to cast a random spell by rolling an integer from 1 to 102
            // 1 - 20  : Hotspicy
            // 21 - 40 : Cold Stare
            // 41 - 60 : Death by Lightning
            // 61 - 80 : Defortify
            // 81 - 100 : Unswole
            // 101 : Player dies instantly
            // 102 : Boss dies instantly
            if (command == 6) {
                enough_mana = check_mana(player_mana, 10);
                if (enough_mana) {
                    cout << name << " casts Yhatzee!" << endl;
                    command = yhatzee();

                    player_mana -= 20;

                    casting = offensive_spells(boss, name, player_mana, mana_lost, command, spell_damage);
                    if (spell_damage != 0) { //if there was damage taken, then the boss takes damage
                        boss->set_hit_points(boss->get_hit_points() - spell_damage);
                        cout << "The enemy takes " << spell_damage << " damage!" << endl;
                    }

                    //Yhatzee kill cases
                    if (command == 0) {
                        cout << "YOU WERE KILLED INSTANTLY" << endl;
                        player_hit_points = 0;
                    } else if (command == 100) {
                        boss->set_hit_points(0);
                        cout << "THE BOSS WAS KILLED INSTANTLY" << endl;
                    }
                } else {
                    cout << "Not enough mana!" << endl;
                }

                //SPELL DESCRIPTIONS
                // Prints them then gets the input again
            } else if (command == 7) {
                cout << "(1) Hotspicy: 10 Mana. Set your enemies ablaze with a hot splurt of hot sauce! Deals 20-40 fire damage." << endl;
                cout << "(2) Cold Stare: 20 Mana. Make so much uncomfortable eye contact with your enemy that they freeze up. Deals 30-40 cold damage." << endl;
                cout << "(3) Death by Lightning: 40 Mana. Call upon the power of the heavens to smite your foes with ease. Deals 60-90 lightning damage." << endl;
                cout << "(4) Defortify: 15 Mana. Lower the defense of your adversary. Lowers Defense by 10 to 20 points" << endl;
                cout << "(5) Unswole: 15 Mana. Cause all that hard work at the gym to disappear from your enemies. Lowes attack by 10 to 20 points." << endl;
                cout << "(6) Yhatzee: 20 Mana. Casts a random spell. On rare occasions, it can instantly kill either you or your enemy. Use wisely." << endl;

                print_spells();

                cin >> command;
            } else if (command == 8) { // Return to action selection menu{
                return true;
            }

        }

        return false;
    }




};

#endif //IL_PROJECT5_SPELL_CASTER_H
