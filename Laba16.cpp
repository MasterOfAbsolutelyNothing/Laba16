#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
using namespace std;

enum ClassWepons : std::uint8_t { staff, sword };
enum ClassEnemy { dragon, slime };

class Enemy;
class Hero;

class Hero {
protected:
    static int count;
    int mana;

public:

    int level;
    int health;
    static int health2;
    string name;
    int damage;
    ClassWepons wepon;
    int powerHero;





    static int getObjectCount() {  // Метод для получения количества
        return count;
    }


    static int HealthReturn() {

        return health2;

    }

    /*static void setDefaultHealth(int val) {
        health2 = val;
    }*/



    void compareHeroDamage(const Hero& other) const {                     //const Hero& other — не даёт изменять переданного героя.         const после скобок — не даёт функции изменять текущий объект.

        if (this->damage == other.damage) {
            cout << name << " and " << other.name << " have the same damage: " << damage << endl;
        }
        else {
            cout << name << " and " << other.name << " have different damage: " << damage << " vs " << other.damage << endl;
        }
    }





    /* int GetDamage()const {
         return damage;
     }*/


    Hero(string in_name, int in_health, int in_damage, ClassWepons in_wepon,
        int in_level, int in_powerHero)
        : name(in_name), health(in_health), damage(in_damage), wepon(in_wepon),
        level(in_level), powerHero(in_powerHero), mana(100) {
        count++;
    }





    virtual ~Hero() {}

    void DamageOFHero(int dmgofHero);
    void DamageFromHero(int dmgfromHero, Enemy& target);


    void equipItem(const string& itemName);

    friend void LevelUp(Hero& h);
    friend void comparePower(Hero& h, Enemy& e);
    friend void lastwords(Hero& h, Enemy& e);

    friend class Gstats;
    Hero() : name("Unknown"), health(0), damage(0), wepon(staff), level(1), powerHero(0), mana(100) {
        count++;
    }


    Hero operator+(const Hero& h1) {
        Hero result;
        result.health = h1.health + this->health;
        return result;
    }

    bool operator==(const Hero& h1) {
        return  h1.damage == this->damage;
    }

    bool operator&&(const Hero& h1) {
        return(h1.level >= 1 && this->level >= 1);
    }


};



int Hero::count = 0;
int Hero::health2 = 120;



class Mage : public Hero {
public:
    int spellPower;

    Mage(string in_name, int in_health, int in_damage, ClassWepons in_wepon,
        int in_level, int in_powerHero, int in_mana)
        : Hero(in_name, in_health, in_damage, in_wepon, in_level, in_powerHero) {

        if (in_health <= 0) {
            throw invalid_argument(in_name + "  has negative health");
        }


        mana = in_mana;
        spellPower = 40; // или можно передавать тоже
    }



    void CastSpellOrSkip(Enemy& e);
};







class PowerfulMage : public Hero {
public:
    int spellPower;

    PowerfulMage(string in_name, int in_health, int in_damage, ClassWepons in_wepon,
        int in_level, int in_powerHero, int in_mana)
        : Hero(in_name, in_health, in_damage, in_wepon, in_level, in_powerHero) {

        
        mana = in_mana;
        spellPower = 100; 



    }


    void CastSpellOrSkip(Enemy& e);
    void checkLevelBeforeSPeLL();
};







void Hero::equipItem(const string& itemName) {
    if (damage < 70) {
        throw logic_error(name + " cannot equip " + itemName );
    }
    cout << name << "  equipped " << itemName << "!\n";
}






void PowerfulMage::checkLevelBeforeSPeLL() {
    if (level <= 3) {
        throw domain_error(name + " is too weak to cast a spell");
    }
}






void Mage::CastSpellOrSkip(Enemy& e) {
    const int spellCost = 30;
    if (mana >= spellCost) {
        mana -= spellCost;
        DamageFromHero(damage + spellPower, e);
        cout << name << " casts a spell! Mana left: " << mana << endl;
    }
    else {
        cout << name << " doesn't have enough mana (" << mana << "). Skipping turn.\n";
    }
}



void PowerfulMage::CastSpellOrSkip(Enemy& e) {
    const int spellCost = 30;
    if (mana >= spellCost) {
        mana -= spellCost;
        DamageFromHero(damage + spellPower, e);
        cout << name << " casts a spell! Mana left: " << mana << endl;
    }
    else {
        cout << name << " doesn't have enough mana (" << mana << "). Skipping turn.\n";
    }
}




class Enemy {
private:
    int levelmob;

public:
    ClassEnemy mobname;
    int healthmob;
    int dammagemob;
    int powerEnemy;

    Enemy(ClassEnemy in_mobname, int in_healthmob, int in_dammagehelth,
        int in_levelmob, int in_powerEnemy)
        : mobname(in_mobname), healthmob(in_healthmob), dammagemob(in_dammagehelth),
        levelmob(in_levelmob), powerEnemy(in_powerEnemy) {
    }

    void DamageforMob(int dmgforEnemy);
    void DamageFromEnemy(int dmgfromEnemy, Hero& target);

    friend void LevelUp(Enemy& e);
    friend void comparePower(Hero& h, Enemy& e);
    friend void lastwords(Hero& h, Enemy& e);

    friend class Gstats;
};


void Hero::DamageOFHero(int dmgofHero) {
    health -= dmgofHero;
    if (health < 0) health = 0;
    cout << name << " takes " << dmgofHero << " damage. Health: " << health << endl;
}

void Hero::DamageFromHero(int dmgfromHero, Enemy& target) {
    cout << name << " deals " << dmgfromHero << " damage!" << endl;
    target.DamageforMob(dmgfromHero);
    LevelUp(*this);
}





void Enemy::DamageforMob(int dmgforEnemy) {
    healthmob -= dmgforEnemy;
    if (healthmob < 0) healthmob = 0;
    cout << "Enemy takes " << dmgforEnemy << " damage. Enemy health: " << healthmob << endl;
}

void Enemy::DamageFromEnemy(int dmgfromEnemy, Hero& target) {
    cout << "Enemy deals " << dmgfromEnemy << " damage!" << endl;
    target.DamageOFHero(dmgfromEnemy);
    LevelUp(*this);
}


void LevelUp(Hero& h) {
    h.level++;
    cout << h.name << " leveled up to " << h.level << "!\n";
}

void LevelUp(Enemy& e) {
    e.levelmob++;
    cout << "Enemy leveled up to " << e.levelmob << "!\n";
}

void comparePower(Hero& h, Enemy& e) {
    h.powerHero = h.damage * h.level;
    e.powerEnemy = e.dammagemob * e.levelmob;

    if (h.powerHero >= e.powerEnemy) {
        cout << h.name << " is stronger. Power: " << h.powerHero << endl;
    }
    else {
        cout << "Enemy is stronger. Power: " << e.powerEnemy << endl;
    }
}

void lastwords(Hero& h, Enemy& e) {
    if (h.health <= 0) {
        cout << h.name << " has been defeated!" << endl;
    }
    if (e.healthmob <= 0) {
        cout << "The enemy has been defeated!" << endl;
    }
}


class Gstats {
public:
    void showstats(Hero& h, Enemy& e) {
        cout << "\n[Hero Stats]\n";
        cout << "Name: " << h.name << ", Health: " << h.health << ", Level: " << h.level
            << ", Damage: " << h.damage << ", Mana: " << h.mana << endl;

        cout << "[Enemy Stats]\n";
        cout << "Health: " << e.healthmob << ", Damage: " << e.dammagemob << ", Level: " << e.levelmob << endl;
        cout << "-----------------------------\n";
    }
};









int main() {



    Hero::HealthReturn;

    Hero* mage = new Mage("Merlin", Mage::HealthReturn(), 30, ClassWepons::staff, 0, 0, 100);

    cout << "Default hero health is set to: " << Hero::HealthReturn() << endl;
    cout << mage->name << " has health: " << mage->health << endl;

    Hero* mage2 = new Mage("Yennefer", Mage::HealthReturn(), 30, ClassWepons::staff, 1, 0, 100);
    cout << mage2->name << " has health: " << mage2->health << endl;


    cout << "\n\n\n\n" << endl;
    mage->compareHeroDamage(*mage2);

    cout << " objects created: " << Hero::getObjectCount() << endl;


    cout << "\n\n\n\n" << endl;


    //low health   negative value or 0
    try {
        Hero* mage3 = new Mage("Morgana", -5, 30, ClassWepons::staff, 0, 0, 100);
        delete mage3;
    }
    catch (const invalid_argument& e) {
        cout  << e.what() << endl;
    }





    //low level   lower required
    try
    {
        PowerfulMage* mage4 = new PowerfulMage("Medea", PowerfulMage::HealthReturn(), 30, ClassWepons::staff, 10, 0, 100);
        mage4->checkLevelBeforeSPeLL();
        delete mage4;
    }

    catch (const domain_error& e) {

        cout << e.what() << endl;
    }




   
    try
    {
        Hero* mage5 = new Mage("Weaver", Mage::HealthReturn(), 100, ClassWepons::staff, 0, 0, 10);
        mage5->equipItem("Legendary Ring");
        delete mage5;
    }

    catch (const logic_error& e) {

        cout  << e.what() << endl;
    }


    delete mage;
    delete mage2;



    return 0;
}