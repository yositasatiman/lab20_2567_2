#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iomanip>

using namespace std;

class Equipment{
    int hpmax;
    int atk;
    int def;
public:
    Equipment(int,int,int);
    vector<int> getStat();            
};

Equipment::Equipment(int h, int a, int d) : hpmax(h), atk(a), def(d) {}

vector<int> Equipment::getStat() {
    return {hpmax, atk, def};
}

class Unit{
    string name;
    string type;        
    int hp;
    int hpmax;
    int atk;
    int def;
    bool guard_on;
    bool dodge_on; 
    Equipment *equipment; 
public:            
    Unit(string,string); 
    void showStatus();
    void newTurn();
    int attack(Unit &);
    int ultimateAttack(Unit &); 
    int beAttacked(int);
    int heal();    
    void guard();
    void dodge(); 
    bool isDead();
    void equip(Equipment *);  
};

Unit::Unit(string t,string n){ 
    type = t;
    name = n;
    if(type == "Hero"){
        hpmax = rand()%20+120;
        atk = rand()%5+14;
        def = rand()%3+9;
    }else if(type == "Monster"){
        hpmax = rand()%20+250;
        atk = rand()%5+25;
        def = rand()%3+5;
    }
    hp = hpmax;    
    guard_on = false;
    dodge_on = false;
    equipment = NULL;
}

void Unit::showStatus(){
    if(type == "Hero"){
        cout << "---------------------------------------\n"; 
        cout << name << "\n"; 
        cout << "HP: " << hp << "/" << hpmax << "\tATK: "<< atk << "\t\tDEF: "<< def;        
        cout << "\n---------------------------------------\n";
    }    
    else if(type == "Monster"){
        cout << "\t\t\t\t---------------------------------------\n"; 
        cout << "\t\t\t\t" << name << "\n"; 
        cout << "\t\t\t\tHP: " << hp << "\t\tATK: "<< atk << "\t\tDEF: "<< def;
        cout << "\n\t\t\t\t---------------------------------------\n";
    }
}

void Unit::newTurn(){
    guard_on = false; 
    dodge_on = false;
}

void Unit::dodge(){
    dodge_on = true;
}

int Unit::beAttacked(int oppatk){
    int dmg;
    if (dodge_on && rand() % 2 == 0) {
        dmg = 0; // Successful dodge
    } else {
        dmg = oppatk - def;
        if (guard_on) dmg /= 3;
        if (dodge_on) dmg *= 2; // Unsuccessful dodge results in double damage
    }
    
    if (dmg < 0) dmg = 0;
    hp -= dmg;
    if (hp <= 0) hp = 0;
    
    return dmg;
}

int Unit::attack(Unit &opp){
    return opp.beAttacked(atk);
}

int Unit::ultimateAttack(Unit &target){
    return target.beAttacked(atk * 2);
}

int Unit::heal(){
    int h = rand()%21 + 10;
    if(hp + h > hpmax) h = hpmax - hp;
    hp = hp + h;
    return h;
}

void Unit::guard(){
    guard_on = true;
}    

bool Unit::isDead(){
    return hp <= 0;
}

void Unit::equip(Equipment *newEquip) {
    if (equipment != NULL) {
        vector<int> oldStats = equipment->getStat();
        hpmax -= oldStats[0];
        atk -= oldStats[1];
        def -= oldStats[2];
    }
    
    equipment = newEquip;
    vector<int> newStats = equipment->getStat();
    hpmax += newStats[0];
    atk += newStats[1];
    def += newStats[2];
    
    if (hp > hpmax) hp = hpmax;
}
