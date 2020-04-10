//
// Created by isaac on 3/30/2020.
//

#ifndef IL_PROJECT5_BOSS_CHILDREN_H
#define IL_PROJECT5_BOSS_CHILDREN_H

#include "Boss_Fight.h"

//Create optional
typedef optional<string> opt_string;

class Egg_Boss : public Boss_Fight {
protected:

public:
    //Default Constructor
    Egg_Boss() {
        //Set name
        f_name = "EGG BOY";

        f_hit_points = f_default_hit_points;
        f_attack = 100; //High attack because uuuuuuuuhhhh egg.
        f_defense = 10; //Low defense because eggshells crack easily
        opt_string f_weakness = nullopt;
        f_weakness_ptr = make_unique<opt_string>(f_weakness);
        f_roll = rand() % 2 + 1; //1, 2, or 3
    }

    //Create weakness
    void create_weakness() override {
        f_weakness = "Fire"; //FIRE COOKS EGGS, YO
    }

    //Boss' Actions:
    void boss_turn(string name, int &player_mana, int &player_hit_points) override {
        cout << endl << "The enemy casts RAIN OF EGG! IT RAINS EGGS EVERYWHERE!" << endl;
        boss_attack(static_cast<double>(f_attack), 5, 20, 20, name, player_hit_points);
    }
};


class Kombucha_Boss : public Boss_Fight {
protected:

public:
    //Default Constructor
    Kombucha_Boss() {
        //Set name
        f_name = "KOMBUCHA BOY";

        f_hit_points = f_default_hit_points;
        f_attack = 10; //Low attack because kombucha is harmless
        f_defense = 100; //High defense because kombucha jars are HARD
        opt_string f_weakness = nullopt;
        f_weakness_ptr = make_unique<opt_string>(f_weakness);
        f_roll = rand() % 2 + 1; //1, 2, or 3
    }

    //Create weakness
    void create_weakness() override {
        f_weakness = "Ice"; //Ice freezes kombucha
    }


    void boss_turn(string name, int &player_mana, int &player_hit_points) override {
        cout << endl << "The enemy casts KOMBUCHA SPLASH! IT POURS KOMBUCHA EVERYWHERE!" << endl;
        boss_attack(static_cast<double>(f_attack), 5, 40, 40, name, player_hit_points);
    }
};

class Fish_Boss : public Boss_Fight {
protected:

public:
    //Default Constructor
    Fish_Boss() {
        //Set name
        f_name = "FISH BOY";

        f_hit_points = f_default_hit_points;
        f_attack = 10; //Low attack because fish is harmless
        f_defense = 10; //Low defense because fish are harmless
        opt_string f_weakness = nullopt;
        f_weakness_ptr = make_unique<opt_string>(f_weakness);
        f_roll = rand() % 2 + 1; //1, 2, or 3
    }

    //Create weakness
    void create_weakness() override {
        f_weakness = "Lightning"; //Lightning Shocks Fish
    }

    //Boss' Actions:
    void boss_turn(string name, int &player_mana, int &player_hit_points) override {
            cout << endl << "The enemy casts FISH SLAP! slap." << endl;
            boss_attack(static_cast<double>(f_attack), 10, 1, 1, name, player_hit_points);
    }
};


#endif //IL_PROJECT5_BOSS_CHILDREN_H
