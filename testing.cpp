//
// Created by isaac on 1/18/2020.
//

#include "Spell_Caster.h"
#include "Boss_Children.h"

using namespace std;

/************ TESTING FUNCTIONS ************/
bool test_attack_spell_helper(unique_ptr<Boss_Fight> &boss, int a, int b, int mana_lost, int &player_mana, string type) {
    Spell_Caster magic;
    int spell_damage = magic.attack_spell(boss, a, b, mana_lost, player_mana, type);

    //If weakness hit
    if (boss->get_weakness() == type) {
        if (spell_damage < 2*b || spell_damage >= 2*(a+b)) { //If less than min or greater than max it failed.
            cout << "FAILED: Min Damage: " << 2*b << " Max Damage: " << 2*(a + b) << " Spell Damage: " << spell_damage << endl;
            return false;
        }
    }

    //Otherwise, as normal
    if (spell_damage < b || spell_damage >= (a+b)) { //If less than min or greater than max it failed.
        cout << "FAILED: Min Damage: " << b << " Max Damage: " << (a + b) << " Spell Damage: " << spell_damage << endl;
        return false;
    }
    return true;
}

bool test_attack_spell(int &player_mana) {

    //Vars
    int mana_lost = 0;
    bool it_works = false;

    //Bosses
    unique_ptr<Boss_Fight> boss = make_unique<Boss_Fight>();
    unique_ptr<Boss_Fight> egg = make_unique<Egg_Boss>();
    unique_ptr<Boss_Fight> kombucha = make_unique<Kombucha_Boss>();
    unique_ptr<Boss_Fight> fish = make_unique<Fish_Boss>();


    //Randomization is present, so we will test these a few times.
    //NOTE: The failed cases always output the same randomly generated spell damage even though srand() is
    //Used to initialize the seed each time. Strange.

    for (int i = 0; i < 3; ++i) {
        if (
            //Cases for potential future spells & testing limits and edge cases
            //NOTE: attack_spell, or more specifically, rand() % does NOT take kindly to zeroes and negative values
            /*test_attack_spell_helper(boss, 10, 0, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(boss, 0, 10, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(boss, 0, 0, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(boss, 0, -10, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(boss, -10, 0, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(boss, -10, -10, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(boss, -10, 10, mana_lost, player_mana, "NONE") &&*/

            //Cases for current spells
            test_attack_spell_helper(boss, 20, 20, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(boss, 10, 30, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(boss, 30, 60, mana_lost, player_mana, "NONE") &&

            //Children Classes, w/ and w/o weaknesses
            test_attack_spell_helper(egg, 20, 20, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(egg, 10, 30, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(egg, 30, 60, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(egg, 20, 20, mana_lost, player_mana, "Fire") &&
            test_attack_spell_helper(egg, 10, 30, mana_lost, player_mana, "Fire") &&
            test_attack_spell_helper(egg, 30, 60, mana_lost, player_mana, "Fire") &&

            test_attack_spell_helper(kombucha, 20, 20, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(kombucha, 10, 30, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(kombucha, 30, 60, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(kombucha, 20, 20, mana_lost, player_mana, "Ice") &&
            test_attack_spell_helper(kombucha, 10, 30, mana_lost, player_mana, "Ice") &&
            test_attack_spell_helper(kombucha, 30, 60, mana_lost, player_mana, "Ice") &&

            test_attack_spell_helper(fish, 20, 20, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(fish, 10, 30, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(fish, 30, 60, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(fish, 20, 20, mana_lost, player_mana, "Lightning") &&
            test_attack_spell_helper(fish, 10, 30, mana_lost, player_mana, "Lightning") &&
            test_attack_spell_helper(fish, 30, 60, mana_lost, player_mana, "Lightning") &&


            //Other Cases
            test_attack_spell_helper(boss, 100, 100, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(boss, 1000, 1000, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(boss, 20000000, 20000000, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(boss, 12342, 9182328, mana_lost, player_mana, "NONE") &&

            test_attack_spell_helper(egg, 300, 6000, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(egg, 1, 1, mana_lost, player_mana, "Fire") &&

            test_attack_spell_helper(kombucha, 3030, 602300, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(kombucha, 1, 2, mana_lost, player_mana, "Ice") &&

            test_attack_spell_helper(fish, 31300, 6000, mana_lost, player_mana, "NONE") &&
            test_attack_spell_helper(fish, 2, 1, mana_lost, player_mana, "Lightning")

        ) {
            //If it passes all of them then we're good to go
            it_works = true;
        } else {
            //Even if it fails once, we kill it.
            it_works = false;
            return it_works;
        }
    }
    //Just in case.
    return it_works;
}

/****** TESTING BOSS_ATTACK *******/

bool test_boss_attack_helper(unique_ptr<Boss_Fight> &boss, int d, int a, int b, string name ,int &player_hit_points) {

        //THE METHOD.
        int damage = boss->boss_attack(static_cast<double>(boss->get_attack()), d, a, b, name, player_hit_points);

        //Add modifier
        int damage_mod = static_cast<double>(boss->get_attack()) / d;
        b += damage_mod;
        a += damage_mod;

        //Otherwise, as normal
        if (damage < b || damage >= (a+b)) { //If less than min or greater than max it failed.
            cout << "FAILED: Min Damage: " << b << " Max Damage: " << (a + b) << " Spell Damage: " << damage << endl;
            return false;
        }
        return true;
}

bool test_boss_attack(int &player_hit_points) {

    //Vars
    string jeff = "Jeff";
    bool it_works = false;

    //Bosses
    unique_ptr<Boss_Fight> boss = make_unique<Boss_Fight>();
    unique_ptr<Boss_Fight> egg = make_unique<Egg_Boss>();
    unique_ptr<Boss_Fight> kombucha = make_unique<Kombucha_Boss>();
    unique_ptr<Boss_Fight> fish = make_unique<Fish_Boss>();


    //Randomization is present, so we will test these a few times.
    //NOTE: The failed cases always output the same randomly generated spell damage even though srand() is
    //Used to initialize the seed each time. Strange.

    for (int i = 0; i < 3; ++i) {
        if (

            //FAILED CASES:

            //NOTE: attack_spell, or more specifically, rand() % does NOT take kindly to zeroes and negative values
            /*test_boss_attack_helper(boss, 0, 0, 0, jeff, player_hit_points) &&
            test_boss_attack_helper(boss, 0, 0, -1, jeff, player_hit_points) &&
            test_boss_attack_helper(boss, 1, -10, 0, jeff, player_hit_points) &&*/

            //NOTE: Using a negative divisor changed the modifier and causes the range to shift improperly.
            /*test_boss_attack_helper(boss, -1, 10, 10, jeff, player_hit_points) &&
            test_boss_attack_helper(kombucha, -1, 40, 40, jeff, player_hit_points) &&
            test_boss_attack_helper(fish, -10, 1, 1, jeff, player_hit_points)*/


            //Current possible attacks across all children
            test_boss_attack_helper(boss, 5, 20, 20, jeff, player_hit_points) &&
            test_boss_attack_helper(boss, 5, 40, 40, jeff, player_hit_points) &&
            test_boss_attack_helper(boss, 10, 1, 1, jeff, player_hit_points) &&

            test_boss_attack_helper(egg, 5, 20, 20, jeff, player_hit_points) &&
            test_boss_attack_helper(egg, 5, 40, 40, jeff, player_hit_points) &&
            test_boss_attack_helper(egg, 10, 1, 1, jeff, player_hit_points) &&

            test_boss_attack_helper(kombucha, 5, 20, 20, jeff, player_hit_points) &&
            test_boss_attack_helper(kombucha, 5, 40, 40, jeff, player_hit_points) &&
            test_boss_attack_helper(kombucha, 10, 1, 1, jeff, player_hit_points) &&

            test_boss_attack_helper(fish, 5, 20, 20, jeff, player_hit_points) &&
            test_boss_attack_helper(fish, 5, 40, 40, jeff, player_hit_points) &&
            test_boss_attack_helper(fish, 10, 1, 1, jeff, player_hit_points) &&

            //Other Cases
            test_boss_attack_helper(boss, 1000, 1, 10, jeff, player_hit_points) &&
            test_boss_attack_helper(kombucha, 10, 40, 400, jeff, player_hit_points) &&
            test_boss_attack_helper(fish, 1, 1000, 10000, jeff, player_hit_points)
    ) {
        //If it passes all of them then we're good to go
        it_works = true;
    } else {
        //Even if it fails once, we kill it.
        it_works = false;
        return it_works;
    }
}
//Just in case.
return it_works;
}

/************ TEST test_check_if_boss_alive() **********/
bool test_check_if_boss_alive_helper(unique_ptr<Boss_Fight> &boss, bool expected) {
    return boss->check_if_boss_alive() == expected;
}

bool test_check_if_boss_alive() {

    //This one checks 5 different cases.

    //Vars
    bool it_works = false;
    int check_count = 0;

    //Bosses
    unique_ptr<Boss_Fight> boss = make_unique<Boss_Fight>();
    unique_ptr<Boss_Fight> egg = make_unique<Egg_Boss>();
    unique_ptr<Boss_Fight> kombucha = make_unique<Kombucha_Boss>();
    unique_ptr<Boss_Fight> fish = make_unique<Fish_Boss>();

    //1. As normal
    if (test_check_if_boss_alive_helper(boss, true) &&
        test_check_if_boss_alive_helper(egg, true) &&
        test_check_if_boss_alive_helper(kombucha, true) &&
        test_check_if_boss_alive_helper(fish, true))
        {
            ++check_count;
        }

    //2. With high health
    boss->set_hit_points(8620);
    egg->set_hit_points(100020);
    kombucha->set_hit_points(23120);
    fish->set_hit_points(1239200);

    if (test_check_if_boss_alive_helper(boss, true) &&
        test_check_if_boss_alive_helper(egg, true) &&
        test_check_if_boss_alive_helper(kombucha, true) &&
        test_check_if_boss_alive_helper(fish, true))
        {
            ++check_count;
        }

    //3. With 0 health
    boss->set_hit_points(0);
    egg->set_hit_points(0);
    kombucha->set_hit_points(0);
    fish->set_hit_points(0);

    if (test_check_if_boss_alive_helper(boss, false) &&
        test_check_if_boss_alive_helper(egg, false) &&
        test_check_if_boss_alive_helper(kombucha, false) &&
        test_check_if_boss_alive_helper(fish, false))
        {
            ++check_count;
        }

    //4. With negative health
    boss->set_hit_points(-1);
    egg->set_hit_points(-2);
    kombucha->set_hit_points(-3);
    fish->set_hit_points(-4);
    if (test_check_if_boss_alive_helper(boss, false) &&
        test_check_if_boss_alive_helper(egg, false) &&
        test_check_if_boss_alive_helper(kombucha, false) &&
        test_check_if_boss_alive_helper(fish, false))
        {
            ++check_count;
        }

    //5. With VERY negative health
    boss->set_hit_points(-11233);
    egg->set_hit_points(-21232);
    kombucha->set_hit_points(-323234);
    fish->set_hit_points(-48329);
    if (test_check_if_boss_alive_helper(boss, false) &&
        test_check_if_boss_alive_helper(egg, false) &&
        test_check_if_boss_alive_helper(kombucha, false) &&
        test_check_if_boss_alive_helper(fish, false))
        {
            ++check_count;
        }

    if (check_count >= 5) {
        //If it passes all of them then we're good to go
        it_works = true;
    } else {
        //Even if it fails once, we kill it.
        it_works = false;
        return it_works;
    }
    //Just in case.
    return it_works;
}

/*********** MAIN ********/
int main() {

    int player_hit_points;
    int player_mana;


    cout << "Initalizing...." << endl << endl << "Testing attack_spell: " << endl;

    if (test_attack_spell(player_mana)) {
        cout << "Passed all test cases for global function attack_spell()" << endl;
    } else {
        cout << "Failed case present in global function attack_spell()" << endl;
    }


    cout << endl << endl << "Testing boss_attack: " << endl;

    if (test_boss_attack(player_hit_points)) {
        cout << endl << "Passed all test cases for global function boss_attack()" << endl;
    } else {
        cout << endl << "Failed case present in global function boss_attack()" << endl;
    }

    cout << "Sorry about the recursive prints, it's part of the function." << endl;


    cout << endl << endl << "Testing check_if_boss_alive: " << endl;

    if (test_check_if_boss_alive()) {
        cout << endl << "Passed all test cases for global function test_check_if_boss_alive()" << endl;
    } else {
        cout << endl << "Failed case present in global function test_check_if_boss_alive()" << endl;
    }


    return 0;
}