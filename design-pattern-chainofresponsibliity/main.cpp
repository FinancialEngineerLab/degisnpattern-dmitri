#include <iostream>

using namespace std;

struct Creature
{
    std::string name;
    int attack;
    int defense;
};

struct Game
{
    std::signal<void(Query&)> queries;
};

struct Query
{
    std::string creature_name;
    enum Argument { attack, defense } argument;
    int result;
};

class Creature
{
    Game& game;
    int attack, defense;

    public:
    std::string name;
    Creature(Game& game, ...) : game { game }, ... { ... }
};

int Creature::get_attack() const
{
    Query q{name, Query::Argument::attack, attack };
    game.queries(q);
    return q.result;
}




class CreatureModifier
{
    
    Game& game;
    Creature& creature;
    CreatureModifier* next { nullptr };
    

    protected:
    Creature& creature;
    
    public:
    CreatureModifier(Game& game, Creature& creature) : game(game), creature(creature) {} 

    explicit CreatureModifier(Creature& creature) : creature(creature) {}

    void add(CreatureModifier* cm)
    {
        if (next)
        {
            next->add(cm); // Important !! //
        }
        else
        {
            next = cm;
        }
    }
    
    virtual void handle()
    {
        if (next)
        {
            next -> handle(); // Important !! //
        }
    }
};

class DoubleAttackModifier : public CreatureModifier
{
    public:
    explicit DoubleAttackModifier(Creature& creature)
    : CreatureModifier(creature)  {} 

    void handle() override
    {
        creature.attack *= 2;
        CreatureModifier::handle();
    }
};

class IncreaseDefenseModifier: public CreatureModifier
{
    public:
        explicit IncreaseDefenseModifier(Creature& creature) : CreatureModifier(creature) {}

        void handle() override
        {
            if (creature.attack <= 2)
            {
                creature.defense += 1;
            }
            CreatureModifier::handle();
        }
};

// broker chain //
class DoubleAttackModifier: public CreatureModifier
{
    connection conn;

    public:
        DoubleAttackModifier(Game& game, Creature& creature) : CreatureModifier(game, creature)
        {
            conn = game.queries.connect([&](Quary& q)
            {
                if (q.creature_name == creature.name && q.argument == Query::Argument::attack)
                {
                    q.result *= 2;
                }
            });
        }

        ~DoubleAttackModifier() { conn.disconnect(); }
}
