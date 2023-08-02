#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
//////////////////////////////////////////////////////////////////////////////////////////1
class Events;
class BaseItem;
class BaseBag;
class BaseKnight;
class ArmyKnights;

enum MonsterType { 
    MADBEAR = 0, BANDIT, LORDLUPIN, ELF, TROLL, TORNBERY, 
    QUEENOFCARDS, NINADERINGS, DURIANGARDEN, OMEGAWEAPON, HADES, ULTIMECIA 
};
enum BaseOpponentCategory {
    BASEDAMAGE = 0, BASEHEALTH, BASEGIL
};
class BaseOpponent{

protected:
    int baseDamage;
    int baseHealth;
    int baseGil;
    MonsterType monsterType;
public:
    MonsterType getMonsterType (){      return this-> monsterType;      }
    double getMonsterInfo(BaseOpponentCategory type){
        return (type == BASEDAMAGE)?    this->baseDamage 
        : (type == BASEHEALTH)?    this->baseHealth   
        : (type == BASEGIL)?   this->baseGil : -12345;
    }
    void setMonsterInfo(BaseOpponentCategory type, double value){
        if (type == BASEHEALTH) {this -> baseHealth = value;};
        //if (type == ) {this -> baseHealth = value;};
    }
};
//////////////////////////////////////////////////////////////////////////////////////////2
class Events {
//////////////////////////////////////////////////////////////////////////////////////////1
protected:
    int numofEvents;
    int * eventID = new int[1000];
public:
    Events (const string & file_events);
    ~Events();
//////////////////////////////////////////////////////////////////////////////////////////2
    int count() const;
    int get(int i) const;
};
enum ItemType {
//////////////////////////////////////////////////////////////////////////////////////////1
ANTIDOTE = 0, PHOENIXDOWN, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV
//////////////////////////////////////////////////////////////////////////////////////////2
};
class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
//////////////////////////////////////////////////////////////////////////////////////////1
    ItemType getItemType (){     return this -> itemType;      }
    string getItemName (){     return this -> itemName;      }
    
    void setItemType (ItemType type){   this -> itemType = type;    }
    void setItemName(string  name){        this -> itemName = name;   }
    protected:
    ItemType itemType;
    string itemName;

//////////////////////////////////////////////////////////////////////////////////////////2
};
struct node;
class BaseBag {
public:
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
//////////////////////////////////////////////////////////////////////////////////////////1
    void drop3Item ();
    void insertFIRST(node*& p, ItemType type);
    void deleteItem(ItemType);
    int count () const;
    BaseBag(BaseKnight* bagOwner,const int &, const int &, const int &);
    ~BaseBag();

    node* getHead() {return this-> head;}
    BaseKnight* getOwner(){return bagOwner;}
    int getNumAntidote(){return this->numofAntidote;}
    int getNumPhoenix(){return this->numofPhoenix;}
    int getCapacity (){return this->knightBagCapacity;}
protected:
    node* head;
    int knightBagCapacity;
    BaseKnight* bagOwner;
    int numofPhoenix  = 0;
    int numofAntidote  = 0;
//////////////////////////////////////////////////////////////////////////////////////////2
};
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
//////////////////////////////////////////////////////////////////////////////////////////1
enum BaseKnightCatogery {ID = 0, HP, MAXHP, LEVEL, MAXLEVEL, GIL, MAXGIL, ANTIDOTe,
                         PHOENIX_I, PHOENIX_II, PHOENIX_III, PHOENIX_IV, POISONED ,KNIGHTBASEDAMAGE};
//////////////////////////////////////////////////////////////////////////////////////////2
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
//////////////////////////////////////////////////////////////////////////////////////////1
    int poisoned = 0;
    int phoenixdownI;
    
    double knightBaseDamage;

    int maxlevel;
    int maxantidote;
    int maxphoenixdownI;
    int maxgil;
    
//////////////////////////////////////////////////////////////////////////////////////////2
    BaseBag * bag;
    KnightType knightType;

public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
//////////////////////////////////////////////////////////////////////////////////////////1
    BaseKnight();

    void setKnightInfo (BaseKnightCatogery type, double value){
        if (type == HP) { this -> hp = value; if (this -> hp > 999 || this -> hp < 0){this -> hp = 0;}}  
        else if (type == LEVEL) { this -> level = value; if (this -> level > 10){this -> level = 10;}} 
        else if (type == GIL) { this -> gil = value;} 
        else if (type == ANTIDOTe) { this -> antidote = value;} 
        
        else if (type == POISONED) {this -> poisoned = value;}
        else if (type == KNIGHTBASEDAMAGE) {this -> knightBaseDamage = value;} 
    }
    double getKnightInfo (BaseKnightCatogery type){
        
        return (type == ID)? this -> id : (type == HP)? this -> hp : (type == MAXHP)? this -> maxhp 
        : (type == LEVEL)? this -> level : (type == MAXLEVEL)? this -> maxlevel 
        : (type == GIL)? this -> gil : (type == MAXGIL)?  this -> maxgil 
        : (type == KNIGHTBASEDAMAGE)? this -> knightBaseDamage : (type == POISONED)? this -> poisoned : -12345;
    }

    void setKnightType (KnightType knightTYPE){     this -> knightType = knightTYPE;    }
    KnightType getKnightType(){             return this-> knightType;                   }
    
    void setKnightBag(BaseKnight* bagOwner,const int & phoenixdownI,const int & antidote,
    const int & knightBagCapacity);
    BaseBag* getKnightBag(){                return this -> bag;                         }
    
    ~BaseKnight();
//////////////////////////////////////////////////////////////////////////////////////////2
};
class ArmyKnights {

//////////////////////////////////////////////////////////////////////////////////////////1
protected:
    int numofKnights;
    int saveNumKnights;
    BaseKnight ** knights = new BaseKnight*[1000];
    bool paladinShield = false;
    bool lancelotSpear = false;
    bool guinevereHair = false;
    bool excaliburSword = false;

    bool meetOmegaWeapon = false;
    bool meetHades = false;
    bool beatUltimecia = false;

    int i = 0;
public:
    void transferItem (BaseKnightCatogery item, double value);
    void eventIDfrom1to5(BaseOpponent *);
    void eventID6(BaseOpponent *);
    void eventID7(BaseOpponent *);
    void fightUltimecia(BaseOpponent*);
    void Print_and_delete_Opponent(BaseOpponent*&);
    Events* theEvents;
    BaseKnight* k;
    void findPhoenix();
//////////////////////////////////////////////////////////////////////////////////////////2
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};
class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;
    

public:
//////////////////////////////////////////////////////////////////////////////////////////1
    
    
//////////////////////////////////////////////////////////////////////////////////////////2
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
    
};

#endif // __KNIGHT2_H__