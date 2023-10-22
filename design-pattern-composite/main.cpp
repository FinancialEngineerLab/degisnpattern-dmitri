#include <iostream>
#include <vector>
#include <array>

using namespace std;

/// bad ///

class Creature
{
    int strength, agility, intelligence;

    public:
        int get_strength() const
        {
            return strength;
        }

        void set_strength(int strength)
        {
            Creature::strength = strength;
        }
        int sum() const 
        {
            return strength + agility + intelligence;
        }

        double average() const 
        {
            return sum() / 3.0;
        }

        int max() const
        {
            return ::max(::max(strength, agility), intelligence);
        }
};


class Creature
{
    enum Abilities { str, agl, intl, count };
    std::array<int, count> abilities;
};

int get_strength() const { return abilities[str]; }


void set_strength(int value) { abilities[str] = value ;}

int sum() const
{
    return accumulate(abilities.begin(), abilities.end(), 0);
}

double average() const
{
    return sum() / (double) count;
}

int max() const
{
    return *max_element(abilities.begin(), abilites.end());
}


