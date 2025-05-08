#include <iostream>
#include <string>

using namespace std;

class Pokemon
{
protected:
    string name_;
    string t1_, t2_;
    int maxHP_, hp_;
    string attackName_;
    int baseDmg_;

public:
    Pokemon(string n, string a, string b, int hp, string atk, int dmg)
        : name_(move(n)), t1_(a), t2_(b), maxHP_(hp), hp_(hp),
          attackName_(move(atk)), baseDmg_(dmg)
    {}

    virtual ~Pokemon() = default;

    const string &name() const { return name_; }
    const string &type1() const { return t1_; }
    const string &type2() const { return t2_; }
    bool fainted() const { return hp_ <= 0; }

    virtual int attack(Pokemon &target, double dmgBoost = 1.0) = 0;
    void receive(int d) { hp_ = max(0, hp_ - d); }
    void heal() { hp_ = maxHP_; }
    void display() const;
    virtual void afficherType() const = 0;
};

class PokemonFeu : public Pokemon
{
public:
    PokemonFeu(string n, string a, string b, int hp, string atk, int dmg)
        : Pokemon(move(n), move(a), move(b), hp, move(atk), dmg)
    {
    }
    void afficherType() const override { cout << name_ << " (Feu)\n"; }
    int attack(Pokemon &target, double dmgBoost = 1.0)
    {
        double m = 1;
        double n = 1;
        if (target.type1() == "Plante" || target.type2() == "Plante")
            m = 2;
        if (target.type1() == "Glace" || target.type2() == "Glace")
            m = 2;
        if (target.type1() == "Insecte" || target.type2() == "Insecte")
            m = 2;
        if (target.type1() == "Acier" || target.type2() == "Acier")
            m = 2;

        if (target.type1() == "Eau" || target.type2() == "Eau")
            n = 0.5;
        if (target.type1() == "Roche" || target.type2() == "Roche")
            n = 0.5;
        if (target.type1() == "Dragon" || target.type2() == "Dragon")
            n = 0.5;
        int dmg = static_cast<int>(baseDmg_ * m * n * dmgBoost);
        target.receive(dmg);
        cout << name_ << " utilise " << attackName_ << " et inflige " << dmg
             << " dégâts à " << target.name() << " !\n";
        if (m * n >= 2)
        {
            cout << "C'est super efficace ! (" << m * n << "x)\n";
        }
        if (m * n < 1)
        {
            cout << "Ce n'est pas très efficace... (" << m * n << "x)\n";
        }
        return dmg;
    }
};

class PokemonEau : public Pokemon
{
public:
    PokemonEau(string n, string a, string b, int hp, string atk, int dmg)
        : Pokemon(move(n), move(a), move(b), hp, move(atk), dmg)
    {
    }
    void afficherType() const override { cout << name_ << " (Eau)\n"; }
    int attack(Pokemon &target, double dmgBoost = 1.0)
    {
        double m = 1;
        double n = 1;
        if (target.type1() == "Feu" || target.type2() == "Feu")
            m = 2;
        if (target.type1() == "Sol" || target.type2() == "Sol")
            m = 2;
        if (target.type1() == "Roche" || target.type2() == "Roche")
            m = 2;

        if (target.type1() == "Eau" || target.type2() == "Eau")
            n = 0.5;
        if (target.type1() == "Plante" || target.type2() == "Plante")
            n = 0.5;
        if (target.type1() == "Dragon" || target.type2() == "Dragon")
            n = 0.5;
        int dmg = static_cast<int>(baseDmg_ * m * n * dmgBoost);
        target.receive(dmg);
        cout << name_ << " utilise " << attackName_ << " et inflige " << dmg
             << " dégâts à " << target.name() << " !\n";
        if (m * n >= 2)
        {
            cout << "C'est super efficace ! (" << m * n << "x)\n";
        }
        if (m * n < 1)
        {
            cout << "Ce n'est pas très efficace... (" << m * n << "x)\n";
        }
        return dmg;
    }
};

class PokemonPlante : public Pokemon
{
public:
    PokemonPlante(string n, string a, string b, int hp, string atk, int dmg)
        : Pokemon(move(n), move(a), move(b), hp, move(atk), dmg)
    {
    }
    void afficherType() const override { cout << name_ << " (Plante)\n"; }
    int attack(Pokemon &target, double dmgBoost = 1.0)
    {
        double m = 1;
        double n = 1;
        if (target.type1() == "Eau" || target.type2() == "Eau")
            m = 2;
        if (target.type1() == "Sol" || target.type2() == "Sol")
            m = 2;
        if (target.type1() == "Roche" || target.type2() == "Roche")
            m = 2;

        if (target.type1() == "Feu" || target.type2() == "Feu")
            n = 0.5;
        if (target.type1() == "Poison" || target.type2() == "Poison")
            n = 0.5;
        if (target.type1() == "Vol" || target.type2() == "Vol")
            n = 0.5;
        if (target.type1() == "Insecte" || target.type2() == "Insecte")
            n = 0.5;
        if (target.type1() == "Dragon" || target.type2() == "Dragon")
            n = 0.5;
        if (target.type1() == "Acier" || target.type2() == "Acier")
            n = 0.5;
        int dmg = static_cast<int>(baseDmg_ * dmgBoost);
        target.receive(dmg);
        cout << name_ << " utilise " << attackName_ << " et inflige " << dmg
             << " dégâts à " << target.name() << " !\n";
        if (m * n >= 2)
        {
            cout << "C'est super efficace ! (" << m * n << "x)\n";
        }
        if (m * n < 1)
        {
            cout << "Ce n'est pas très efficace... (" << m * n << "x)\n";
        }
        return dmg;
    }
};

class PokemonGenerique : public Pokemon
{
public:
    PokemonGenerique(string n, string a, string b, int hp, string atk, int dmg)
        : Pokemon(move(n), move(a), move(b), hp, move(atk), dmg)
    {
    }
    void afficherType() const override { cout << name_ << "(" << t1_ << ")\n"; }
    int attack(Pokemon &target, double dmgBoost = 1.0)
    {

        int dmg = static_cast<int>(baseDmg_ * dmgBoost);
        target.receive(dmg);
        cout << name_ << " utilise " << attackName_ << " et inflige " << dmg
             << " dégâts à " << target.name() << " !\n";
        return dmg;
    }
};