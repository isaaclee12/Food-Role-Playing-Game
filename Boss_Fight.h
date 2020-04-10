#include <iostream>
#include <string>
#include <optional>
#include <time.h>
#include <memory>
#include <vector>
#include <cstdlib>
using namespace std;

//Create optional
typedef optional<string> opt_string;

//Establishment of the Boss Fight class and its functions and fields

class Boss_Fight {

protected:
    string f_name;
    const int f_default_hit_points = 100;
    int f_hit_points;
    int f_attack;
    int f_defense;
    opt_string f_weakness;
    unique_ptr<opt_string> f_weakness_ptr;
    int f_roll;

public:
    //Default Constructor
    Boss_Fight() {
        srand(time(NULL));
        f_hit_points = f_default_hit_points;
        f_attack = 50;
        f_defense = 50;
        opt_string f_weakness = nullopt;
        f_weakness_ptr = make_unique<opt_string>(f_weakness);
        f_roll = rand() % 2 + 1; //1, 2, or 3
    }

    //Getters
    int get_hit_points() {
        return f_hit_points;
    }

    int get_attack() {
        return f_attack;
    }

    int get_defense() {
        return f_defense;
    }

    opt_string get_weakness() {
        return f_weakness;
    }

    string get_name() {
        return f_name;
    }

    //Setters
    void set_hit_points(int p_hit_points) {
        f_hit_points = p_hit_points;
    }

    void set_attack(int p_attack) {
        f_attack = p_attack;
    }

    void set_defense(int p_defense) {
        f_defense = p_defense;
    }

    void set_weakness(string p_weakness) {
        f_weakness = p_weakness;
    }

    void set_name(string p_name) {
        f_name = p_name;
    }

    //Create weakness
    virtual void create_weakness() {
        if (f_roll = 1) {
            f_weakness = "Fire";
        } else if (f_roll = 2) {
            f_weakness = "Ice";
        } else if (f_roll = 3) {
            f_weakness = "Lightning";
        }
    }

    //Delete weakness
    void delete_weakness() {
        f_weakness = nullopt;
    }

    //Actions
    void player_attack(string name, int player_damage_to_boss) {
        f_hit_points -= (player_damage_to_boss - static_cast<double>(f_defense) / 10);
        cout << name << " deals " << player_damage_to_boss << " damage to the enemy!" << endl;
    }

    //Checks
    bool check_if_boss_alive() {
        if (f_hit_points <= 0) {
            return false;
        } else {
            return true;
        }
    }

    //Boss Attack:
    int boss_attack(double boss_attack_stat, int d, int a, int b, string name ,int &player_hit_points) {
        int damage_taken = (boss_attack_stat / d) + rand() % a + b;
        player_hit_points -= damage_taken;
        cout << name << " takes " << damage_taken << " hit points of damage!" << endl;
        return damage_taken;
    }

    //Boss' Actions:
    virtual void boss_turn(string name, int &player_mana, int &player_hit_points) {}

    //Reset Boss
    void revive() {
        this->f_hit_points = f_default_hit_points;
    }
};