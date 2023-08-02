#include "knight2.h"



//////////////////////////////////////////////////////////////////////////////////////////1
/* * * * * * * * * * * * * * * * * * * * * * * * BEGIN implementation of class BaseItem * * * * * * * * * * * * * * * * * * * * * * * */
struct node{
  ItemType type;
  string typeName;
  node* next;
    
};
node* createNode(ItemType type){
    string nameofType("");
    switch (type)
{
case ANTIDOTE:
    nameofType = "Antidote";
    break;
case PHOENIXDOWNI:
    nameofType = "PhoenixI";
    break;
case PHOENIXDOWNII:
    nameofType = "PhoenixII";
    break;
case PHOENIXDOWNIII:
    nameofType = "PhoenixIII";
    break;
case PHOENIXDOWNIV:
    nameofType = "PhoenixIV";
    break;
}
    node* temp = new node;
    temp -> type = type;
    temp -> typeName = nameofType;
    temp -> next = NULL;
    return temp;
}
void BaseBag::deleteItem(ItemType removingItem){
    node* temp = head;
    while (temp != NULL){
        if (temp -> type == removingItem){
            node* temp2 = createNode(head -> type);

            head -> type = temp -> type;
            head -> typeName = temp -> typeName;

            temp -> type = temp2 -> type;
            temp -> typeName = temp2 -> typeName;

            node* del = head;
            head = head -> next;

            delete del;
            del = NULL;
            if (removingItem == PHOENIXDOWNI || removingItem == PHOENIXDOWNII
             ||removingItem == PHOENIXDOWNIII ||removingItem == PHOENIXDOWNIV)
            {
                this -> numofPhoenix -= 1;
            }
            else if (removingItem == ANTIDOTE)
            {
                this -> numofAntidote -= 1;
            }
            
            delete temp2;
            temp2 = NULL;
            temp = NULL;
            
            break;
        }
        temp = temp -> next;
    }
}
class Antidote : public BaseItem{
    public:
    Antidote(){
        this -> itemType = ANTIDOTE;
    }
    bool canUse(BaseKnight * knight){
        if (knight -> getKnightType() == DRAGON)
        {
            return false;
        }
        if (knight -> getKnightInfo(POISONED) != 0){
            return true;
        }
        return false;
    }
    void use (BaseKnight * knight){
        
            
            knight -> setKnightInfo(POISONED, 0);
            knight-> getKnightBag()->deleteItem(this->itemType);
    }
};
class PhoenixDownI : public BaseItem{
public:

    PhoenixDownI(){
        this -> itemType = PHOENIXDOWNI;
    }
    bool canUse(BaseKnight * knight){
    if (knight -> getKnightInfo(HP) <= 0){
        return true;
    }
   
    return false;    
    }  
    void use (BaseKnight * knight){
        
        knight -> setKnightInfo(HP,knight->getKnightInfo(MAXHP));
        knight-> getKnightBag()->deleteItem(this->itemType);
    }   
};
class PhoenixDownII : public BaseItem{
public:
    PhoenixDownII(){
        this -> itemType = PHOENIXDOWNII;
    }
    bool canUse(BaseKnight * knight){
    if (knight -> getKnightInfo(HP) < static_cast<int>(knight -> getKnightInfo(MAXHP)/4)){
        return true;
    }
    return false;    
    }
    void use (BaseKnight * knight){
        
        knight -> setKnightInfo(HP,knight->getKnightInfo(MAXHP));
        knight-> getKnightBag()->deleteItem(this->itemType);
    }
};
class PhoenixDownIII : public BaseItem{
public:
    PhoenixDownIII(){
        this -> itemType = PHOENIXDOWNIII;
    }
    
    bool canUse(BaseKnight * knight){
    if (knight -> getKnightInfo(HP) < static_cast<int>(knight -> getKnightInfo(MAXHP)/3)){
        return true;

    }
    return false;    
    }
    void use (BaseKnight * knight){

        if (knight -> getKnightInfo(HP) <= 0){
            knight -> setKnightInfo(HP,static_cast<int>(knight->getKnightInfo(MAXHP)/3));
        }
        else{
            knight -> setKnightInfo(HP,knight -> getKnightInfo(HP) + static_cast<int>(knight->getKnightInfo(MAXHP)/4));
        }
        
        knight-> getKnightBag()->deleteItem(this->itemType);
    }
    
};
class PhoenixDownIV : public BaseItem{
    public:
    PhoenixDownIV(){
        this -> itemType = PHOENIXDOWNIV;
    }

    bool canUse(BaseKnight * knight){
    if ((knight -> getKnightInfo(HP)) < static_cast<int>(knight -> getKnightInfo(MAXHP)/2))
    {
        return true;
    }
    return false;    
    }
    void use (BaseKnight * knight){

        if (knight -> getKnightInfo(HP) <= 0){
            knight -> setKnightInfo(HP,static_cast<int>(knight->getKnightInfo(MAXHP)/2));
        }
        else{
            knight -> setKnightInfo(HP,knight -> getKnightInfo(HP) + static_cast<int>(knight->getKnightInfo(MAXHP)/5));
        }
        
        knight-> getKnightBag()->deleteItem(this->itemType);
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * END implementation of class BaseItem * * * * * * * * * * * * * * * * * * * * * * * */
//////////////////////////////////////////////////////////////////////////////////////////2





//////////////////////////////////////////////////////////////////////////////////////////1
/* * * * * * * * * * * * * * * * * * * * * * * * BEGIN implementation of class BaseBag * * * * * * * * * * * * * * * * * * * * * * * */


void BaseBag::insertFIRST(node*& p, ItemType type){
    node* temp = createNode(type);

    if (type == PHOENIXDOWNI || type == PHOENIXDOWNII || type == PHOENIXDOWNIII || type == PHOENIXDOWNIV)
    {
        this -> numofPhoenix += 1;
    }
    else if (type == ANTIDOTE)
    {    
        this -> numofAntidote += 1;
    }
    if (p == NULL){
        p = temp;
    }
    else{
        temp -> next = p;
        p = temp;
    }
}
BaseBag::BaseBag(BaseKnight* bagOwner,const int & phoenixdownI,
    const int & antidote,const int & knightBagCapacity){
    

    this -> head = NULL;
    this -> knightBagCapacity = knightBagCapacity;
    this -> bagOwner = bagOwner;
    int a = 0;
        for (int i = 0; i < phoenixdownI; i++)
        {
            if (a < 5)
            {
            insertFIRST(head, PHOENIXDOWNI);
            ++a;
            }
        }
        a = 0;
        for (int i = 0; i < antidote; i++)
        {
            if (a < 5)
            {
            insertFIRST(head, ANTIDOTE);
            ++a;
            }
        }
}
bool BaseBag::insertFirst(BaseItem * item){
    if (bagOwner -> getKnightType() == DRAGON && item->getItemType() == ANTIDOTE){
        return false;
    }
    if (this -> count() < this -> knightBagCapacity)
    {
        if (item ->getItemType() == ANTIDOTE && this -> numofAntidote < 5)
        {    
            insertFIRST(head, item->getItemType());
            return true;
        }
        else if (item->getItemType() != ANTIDOTE)
        {
            insertFIRST(head, item->getItemType());
            return true;
        }
        
    }
    
    return false;
}
int BaseBag::count() const{
    node* temp = head; int c = 0;
    while (temp != NULL){++c; temp = temp -> next;}
    temp = NULL;
    return c;
}
string BaseBag::toString() const{
    string bagString = "";
    int c = count(); node* ptr = head;
    bagString += "Bag[count=" + to_string(count()) + ";";
    for(int i = 0; i < c - 1 && ptr != NULL; i++)
    {
        bagString += ptr -> typeName + ",";
        ptr = ptr -> next;
    }
    if (ptr!= NULL ){bagString += ptr -> typeName + "]";}
    else
    {
        bagString += "]";
    }
    return bagString;
}
BaseItem * BaseBag::get(ItemType itemType){
    node* temp = head;
    if (itemType == PHOENIXDOWN){
    while (temp != NULL){
            switch (temp -> type)
            {
            case PHOENIXDOWNI:
                return new PhoenixDownI();
                break;
            case PHOENIXDOWNII:
                return new PhoenixDownII();
                break;
            case PHOENIXDOWNIII:
                return new PhoenixDownIII();
                break;
            case PHOENIXDOWNIV:
                return new PhoenixDownIV();
                break;
            } 
            temp = temp -> next;   
        }
    }
    else if (itemType == ANTIDOTE){
        while (temp != NULL){
            if (temp -> type == ANTIDOTE)
                return new Antidote();
            temp = temp -> next; 
        }
        
    }
    return NULL;
}
void BaseBag::drop3Item(){
    
        for (int i = 0; i < 3 && this -> count() != 0; ++i){
            node* temp = head;
            head = head -> next;
            delete temp;
            temp = NULL;
        }
}

class paladinKnightBag : public BaseBag{
public:
    paladinKnightBag(BaseKnight* bagOwner,const int & phoenixdownI, const int & antidote,
    const int & knightBagCapacity): 
    BaseBag(bagOwner, phoenixdownI, antidote, knightBagCapacity){};
};
class lancelotKnightBag : public BaseBag{
public:
    lancelotKnightBag(BaseKnight* bagOwner,const int & phoenixdownI, const int & antidote,
    const int & knightBagCapacity): 
    BaseBag(bagOwner, phoenixdownI, antidote, knightBagCapacity){};
};
class dragonKnightBag : public BaseBag{
public:
    dragonKnightBag(BaseKnight* bagOwner,const int & phoenixdownI, const int & antidote,
    const int & knightBagCapacity): 
    BaseBag(bagOwner, phoenixdownI, antidote, knightBagCapacity){};
};
class normalKnightBag : public BaseBag{
public:
    normalKnightBag(BaseKnight* bagOwner,const int & phoenixdownI, const int & antidote,
    const int & knightBagCapacity): 
    BaseBag(bagOwner, phoenixdownI, antidote, knightBagCapacity){};
};
void BaseKnight::setKnightBag(BaseKnight* bagOwner,const int & phoenixdownI,const int & antidote,
const int & knightBagCapacity){
        if (bagOwner -> getKnightType() == PALADIN)
            this -> bag = new paladinKnightBag(bagOwner, phoenixdownI, antidote, knightBagCapacity);
        else if (bagOwner -> getKnightType() == LANCELOT)
            this -> bag = new lancelotKnightBag(bagOwner, phoenixdownI, antidote, knightBagCapacity);
        else if (bagOwner -> getKnightType() == DRAGON)
            this -> bag = new dragonKnightBag(bagOwner, phoenixdownI, antidote, knightBagCapacity);
        else 
            this -> bag = new normalKnightBag(bagOwner, phoenixdownI, antidote, knightBagCapacity);
}
BaseBag::~BaseBag(){
    while (head -> next!= NULL)
    {
        node* temp = head;  head = head -> next;
        delete temp;
    }
}
/* * * * * * * * * * * * * * * * * * * * * * * * END implementation of class BaseBag * * 
//////////////////////////////////////////////////////////////////////////////////////////2







/* * * * * * * * * * * * * * * * * * * * * * * * BEGIN implementation of class BaseKnight * * * * * * * * * * * * * * * * * * * * * * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString() 
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}
//////////////////////////////////////////////////////////////////////////////////////////1
BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    BaseKnight* aKnight = new BaseKnight;
    aKnight -> id = id;
    aKnight -> hp = maxhp;
    aKnight -> maxhp = maxhp;
    aKnight -> level = level;
    aKnight -> gil = gil;
    aKnight -> antidote = antidote;
    aKnight -> phoenixdownI = phoenixdownI;
return aKnight;
}
class PaladinKnight : public BaseKnight{
public:
    
};
class LancelotKnight : public BaseKnight{
public:
    
};
class DragonKnight : public BaseKnight{
public:
    
};
class NormalKnight : public BaseKnight{
public:
    
};
BaseKnight::BaseKnight(){

    this -> maxantidote = 5;
    this -> maxphoenixdownI = 5;
    this -> maxgil = 999;
    this -> maxlevel = 10;
    
}
BaseKnight::~BaseKnight(){
    delete bag;
}
//////////////////////////////////////////////////////////////////////////////////////////2
/* * * * * * * * * * * * * * * * * * * * * * * * END implementation of class BaseKnight * * * * * * * * * * * * * * * * * * * * * * * */






//////////////////////////////////////////////////////////////////////////////////////////1
/* * * * * * * * * * * * * * * * * * * * * * * * BEGIN implementation of class Events * * * * * * * * * * * * * * * * * * * * * * * */
Events::Events(const string & file_events){
    ifstream readEvent;
    readEvent.open(file_events);
    readEvent >> numofEvents;
    int ID; 
    int i = 0;
    readEvent >> ID; 
    do
    {
         eventID[i] = ID;
         ++i; 
    }
    while(readEvent >> ID);
    readEvent.close();
}
Events::~Events(){
    delete[] eventID;
    eventID = NULL;
}
int Events::get (int i) const{
    return eventID[i];
}
int Events::count() const{
    return numofEvents;
}
/* * * * * * * * * * * * * * * * * * * * * * * * END implementation of class Events * * * * * * * * * * * * * * * * * * * * * * * */
//////////////////////////////////////////////////////////////////////////////////////////2










//////////////////////////////////////////////////////////////////////////////////////////1
/* * * * * * * * * * * * * * * * * * * * * * * * BEGIN implementation of class BaseOpponent * * * * * * * * * * * * * * * * * * * * * * * */
class MadBear : public BaseOpponent{
public:
    MadBear()
    {
        this -> monsterType = MADBEAR;
        this-> baseDamage = 10;
        this-> baseGil = 100;
    }
    void fight(){
        cout <<"fight";
    }
};
class Bandit : public BaseOpponent{
public:
    Bandit()
    {
        this -> monsterType = BANDIT;
        this-> baseDamage = 15;
        this-> baseGil = 150;
    }
};
class LordLupin : public BaseOpponent{
public:
    LordLupin()
    {
        this -> monsterType = LORDLUPIN;
        this-> baseDamage = 45;
        this-> baseGil = 450;
    }
};
class Elf : public BaseOpponent{
public:
    Elf()
    {
        this -> monsterType = ELF;
        this-> baseDamage = 75;
        this-> baseGil = 750;
    }
};
class Troll: public BaseOpponent{
public:
    Troll()
    {
        this -> monsterType = TROLL;
        this-> baseDamage = 95;
        this-> baseGil = 800;
    }
};
class Tornbery : public BaseOpponent{
public:
    Tornbery()
    {
        this -> monsterType = TORNBERY;
    }
};
class QueenOfCards : public BaseOpponent{
public:
    QueenOfCards()
    {
        this -> monsterType = QUEENOFCARDS;
    }
};
class NinaDeRings : public BaseOpponent{
public:
    NinaDeRings()
    {
        this -> monsterType = NINADERINGS;
    }
};
class DurianGarden : public BaseOpponent{
public:
    DurianGarden()
    {
        this -> monsterType = DURIANGARDEN;
    }
};
class OmegaWeapon : public BaseOpponent{
public:
    OmegaWeapon()
    {
        this -> monsterType = OMEGAWEAPON;
    }
};
class Hades : public BaseOpponent{
public:
    Hades()
    {
        this -> monsterType = HADES;
    }
};
class Ultimecia : public BaseOpponent{
public:
    Ultimecia()
    {
        this -> monsterType = ULTIMECIA;
        this -> baseHealth = 5000;
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * END implementation of class BaseOpponent * * * * * * * * * * * * * * * * * * * * * * * */
//////////////////////////////////////////////////////////////////////////////////////////2








/* * * * * * * * * * * * * * * * * * * * * * * * BEGIN implementation of class ArmyKnights * * * * * * * * * * * * * * * * * * * * * * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << "\n"
        << string(50, '-') << "\n";
}
void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << "\n";
}
//////////////////////////////////////////////////////////////////////////////////////////1
bool ArmyKnights::hasPaladinShield() const{
    return paladinShield;
}
bool ArmyKnights::hasLancelotSpear() const{
    return lancelotSpear;
}
bool ArmyKnights::hasGuinevereHair() const{
    return guinevereHair;
}
bool ArmyKnights::hasExcaliburSword() const{
    return excaliburSword;
}


BaseKnight * ArmyKnights::lastKnight() const{
    /*
    if (numofKnights == 0){
        return NULL;
    }
    return knights[numofKnights];*/

    for (int i = numofKnights; i >= 1; --i){
        if (knights[i] -> getKnightInfo(HP) >0){
            return knights[i];
        }
    }
    return NULL;
}
int ArmyKnights::count() const{
    
    int a = 0;
    int i = saveNumKnights;
    while(i >= 1)
    {
        if(knights[i] -> getKnightInfo(HP) > 0)
        {
            ++a;
        }
        --i;
    }
    if ((this -> i == theEvents -> count() - 1) && !beatUltimecia)
    {
        return 0;
    }
    /*int a = numofKnights;*/
    return a;
    
    
    
}
bool Pythagorean(int n){
    int a, b, c;
    c = n% 10; n/= 10; b = n%10; n/= 10; a = n%10;
    return (a*b*c != 0) &&
    ((a*a == b*b + c*c) || (b*b == a*a + c*c) || ( c*c == a*a + b*b )) ;
        
}
bool PrimeNumber(int n){
    if (n < 2)
        return false;
    for (int i = 2; i < n - 1; i ++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
ArmyKnights::ArmyKnights(const string & file_armyknights){
    int maxhp, level, phoenixdownI, gil, antidote;
    ifstream readArmy;
    readArmy.open(file_armyknights); 
    
    readArmy >> numofKnights;
    saveNumKnights = numofKnights;
    readArmy >> maxhp >> level >> phoenixdownI >> gil >> antidote;
    //knights[0] = NULL;
    int i = 1;
do{
        
        if (maxhp == 888)
        {
            
            knights[i] = knights[i] -> create (i, maxhp, level, gil, antidote, phoenixdownI );
            
            knights[i] -> setKnightType(LANCELOT);
            knights[i] -> setKnightBag(knights[i], phoenixdownI, antidote, 16);
            knights[i] -> setKnightInfo(KNIGHTBASEDAMAGE, 0.05);
        }
        else if (Pythagorean(maxhp))
        {
           
            knights[i] = knights[i] -> create (i, maxhp, level, gil, antidote, phoenixdownI );
            
            knights[i] -> setKnightType(DRAGON);
            knights[i] -> setKnightBag(knights[i], phoenixdownI, antidote, 14);
            knights[i] -> setKnightInfo(KNIGHTBASEDAMAGE, 0.075);
        }
        else if (PrimeNumber(maxhp))
        {
            knights[i] = knights[i] -> create (i, maxhp, level, gil, antidote, phoenixdownI );
            
            knights[i] -> setKnightType(PALADIN);
            knights[i] -> setKnightBag(knights[i], phoenixdownI, antidote, 1000000);
            knights[i] -> setKnightInfo(KNIGHTBASEDAMAGE, 0.06);
            
        }
        else
        {
            knights[i] = knights[i] -> create (i, maxhp, level, gil, antidote, phoenixdownI );
            
            knights[i] -> setKnightType(NORMAL);
            knights[i] -> setKnightBag(knights[i], phoenixdownI, antidote, 19);
            knights[i] -> setKnightInfo(KNIGHTBASEDAMAGE, 0.0);
        }
        
       ++i;
    }while(readArmy >> maxhp >> level >> phoenixdownI >> gil >> antidote);

    readArmy.close();  
     
}
ArmyKnights::~ArmyKnights(){
    for (int i = 1; i <= saveNumKnights ; i ++ )
    {
        if (knights[i] != NULL)
            {
                delete knights[i];knights[i] = NULL;
            }
    }
    delete []knights;
    knights = NULL;
    delete theEvents;
    theEvents = NULL;
}


void ArmyKnights::transferItem (BaseKnightCatogery item, double value){
    BaseItem* phoenixItem;
    if (item == GIL)
    {
        for (int i = numofKnights; i >= 1 && value > 0; --i)
        {
            if (knights[i] -> getKnightInfo(GIL) + value <= knights[i] -> getKnightInfo(MAXGIL))
            {   
                knights[i] -> setKnightInfo(GIL, knights[i] -> getKnightInfo(GIL) + value );
                value = 0;
            }        
            else
            {
                knights[i] -> setKnightInfo(GIL, knights[i] -> getKnightInfo(MAXGIL));
                value -= knights[i] -> getKnightInfo(MAXGIL) - knights[i] -> getKnightInfo(GIL);
                
            }
            
        }
    }
    else if (item != GIL)
    {
        switch(item)
        {
        case PHOENIX_I:
            phoenixItem = new PhoenixDownI;
            break;
        case PHOENIX_II:
            phoenixItem = new PhoenixDownII;
            break;
        case PHOENIX_III:
            phoenixItem = new PhoenixDownIII;
            break;
        case PHOENIX_IV:
            phoenixItem = new PhoenixDownIV;
            break;
        }

        for (int i = numofKnights; i >= 1 ; --i)
        {
            if (knights[i] -> getKnightBag() -> insertFirst(phoenixItem) && knights[i] -> getKnightInfo(HP) > 0)
            {   
                break;
            }        
        }
    }
}
void ArmyKnights::findPhoenix(){
    

    if (k-> getKnightInfo(HP) <= static_cast<int>(k -> getKnightInfo(MAXHP) /2 ))
    
    {
        BaseItem* item = k->getKnightBag()->get(PHOENIXDOWN);
        if(item != NULL){
            if(item -> canUse(k))
                {item -> use(k);}
        }
        delete item;
        item = NULL;
    }
    if (k->getKnightInfo(HP) <= 0 && k->getKnightInfo(GIL) >= 100)
    {
        k-> setKnightInfo(GIL, k->getKnightInfo(GIL) - 100);
        
        k-> setKnightInfo(HP, static_cast<int>(k->getKnightInfo(MAXHP)/2));
    }
    /*if (k->getKnightInfo(HP) <= 0)
    {
      this -> i -= 1;  
    }
    */
}


void ArmyKnights::fightUltimecia(BaseOpponent* opponent){
    Ultimecia* BOSS = static_cast<Ultimecia*>(opponent);
    if (excaliburSword)
    {
         
        beatUltimecia = true;
        BOSS -> setMonsterInfo(BASEHEALTH,0);

        return;
    }
    else if (paladinShield&&lancelotSpear&&guinevereHair)
    {
        for (int i = numofKnights; i >= 1; --i)
        {
            
            if (knights[i] -> getKnightType() != NORMAL && knights[i] -> getKnightInfo(HP) > 0)
            {
                BOSS ->setMonsterInfo
                (
                BASEHEALTH, BOSS-> getMonsterInfo(BASEHEALTH) -
                    static_cast<int>
                (
                knights[i] -> getKnightInfo(HP)*
                knights[i] -> getKnightInfo(LEVEL)*
                knights[i] -> getKnightInfo(KNIGHTBASEDAMAGE)
                )
                )
                ;


                if (BOSS -> getMonsterInfo(BASEHEALTH) > 0)
                {
                    knights[i] -> setKnightInfo(HP, 0);
                    //findPhoenix();
                }
                else if (BOSS -> getMonsterInfo(BASEHEALTH) <= 0)
                {
                    beatUltimecia = true;
                    break;
                }
            }
        }
    }
    if(BOSS -> getMonsterInfo(BASEHEALTH) > 0) 
    {
        beatUltimecia = false;
    }
}
void ArmyKnights::eventID7(BaseOpponent *opponent){
    
    int levelO = (i + theEvents->get(i))%10 + 1;


    if (k-> getKnightInfo(LEVEL) >= levelO)
    {
        int tempgil = k->getKnightInfo(GIL);
        transferItem(GIL, tempgil); 
    }
    else if (k-> getKnightInfo(LEVEL) < levelO && k->getKnightType() != PALADIN)
    {
        k -> setKnightInfo(GIL, static_cast<int>(k->getKnightInfo(GIL)/2));
    }
    
}
void ArmyKnights::eventID6(BaseOpponent *opponent){
    
    int levelO = (i + theEvents->get(i))%10 + 1;

    //cout <<  k-> getKnightBag() -> getNumAntidote() << endl;
    
    
    if (k-> getKnightInfo(LEVEL) >= levelO)
    {
        k-> setKnightInfo(LEVEL, k ->getKnightInfo(LEVEL) + 1); 
    }
    else if (k-> getKnightInfo(LEVEL) < levelO && k-> getKnightType() != DRAGON)
    {
        k -> setKnightInfo(POISONED, 1);
    }
    if (k -> getKnightInfo(POISONED) == 1 && k-> getKnightBag() -> getNumAntidote()>= 1)
    {    
        BaseItem* item = k->getKnightBag()->get(ANTIDOTE);
        if(item != NULL){
            if(item -> canUse(k))
                {item -> use(k);}
        }
        delete item;
        item = NULL;

        //con xoa trong  linked list

    }
    else if (k -> getKnightInfo(POISONED) == 1 && (k-> getKnightBag() -> getNumAntidote() == 0))
    {
        k-> getKnightBag() -> drop3Item();
        k -> setKnightInfo(HP, k -> getKnightInfo(HP) - 10);
        findPhoenix();
    }
    k -> setKnightInfo(POISONED, 0);
}
void ArmyKnights::eventIDfrom1to5(BaseOpponent * opponent){

    
    int levelO = (i + theEvents->get(i))%10 + 1;


    if ((k-> getKnightInfo(LEVEL) >= levelO || k -> getKnightType() == LANCELOT 
        || k -> getKnightType() == PALADIN))
    {
        // transfer gil
        transferItem (GIL, opponent->getMonsterInfo(BASEGIL));
    }
    else
    {    
        k-> setKnightInfo(HP, k->getKnightInfo(HP) - (opponent -> getMonsterInfo(BASEDAMAGE))
            *(levelO - k-> getKnightInfo(LEVEL)));
        findPhoenix();
    }

    
}


bool ArmyKnights::fight(BaseOpponent * opponent){ 
    

    switch (opponent -> getMonsterType())
    {

    case DURIANGARDEN:
        k-> setKnightInfo(HP,k->getKnightInfo(MAXHP));
        printInfo();
            
        break;
    
    case OMEGAWEAPON:
        if(!meetOmegaWeapon)
        {
            if(((k->getKnightInfo(LEVEL) == 10 
                        && k->getKnightInfo(HP) == k->getKnightInfo(MAXHP)) 
                        || k-> getKnightType() == DRAGON))
            {
                k-> setKnightInfo(LEVEL, 10);
                k-> setKnightInfo(GIL, 999);
                meetOmegaWeapon = true;
            }
            else
            {
                k-> setKnightInfo(HP, 0);
                
                ///thuc hien su kien dau
                findPhoenix();
                
            }
        }
        printInfo();
        break;
    
    case HADES:
        if (!meetHades)
        {
            if ((k-> getKnightType() == PALADIN &&  
                        k->getKnightInfo(LEVEL) >= 8)||
                        k->getKnightInfo(LEVEL) == 10)
            {
                paladinShield = true;
                meetHades = true;
            }
            else
            {
                //thuc hien su kien dau
                k-> setKnightInfo(HP, 0);
                findPhoenix();
            }
        }

        printInfo();
        break;
    

    case NINADERINGS:
        
        if (k->getKnightInfo(HP) <= static_cast<int>(k->getKnightInfo(MAXHP)/3))
        {
            if(k->getKnightInfo(GIL) >= 50)
            {
                k-> setKnightInfo(GIL, k->getKnightInfo(GIL) - 50);
                k-> setKnightInfo(HP, k->getKnightInfo(HP) + 
                static_cast<int>(k->getKnightInfo(MAXHP)/5));
            }
            else if (k->getKnightType() == PALADIN)
            {
                k-> setKnightInfo(HP, k->getKnightInfo(HP) + 
                static_cast<int>(k->getKnightInfo(MAXHP)/5));
            }
        }
        printInfo();
        break;

    case MADBEAR:
        eventIDfrom1to5(opponent);
        printInfo();
        break;
    
    case BANDIT:
        eventIDfrom1to5(opponent);
        printInfo();
        break;

    case LORDLUPIN:
        eventIDfrom1to5(opponent);
        printInfo();
        break;

    case ELF:
        eventIDfrom1to5(opponent);
        printInfo();
        break;

    case TROLL:
        eventIDfrom1to5(opponent);
        printInfo();
        break;
    
    case TORNBERY:
        eventID6(opponent);
        printInfo();
        break;
    
    case QUEENOFCARDS:
        eventID7(opponent);
        printInfo();
        break;

    case ULTIMECIA:
        fightUltimecia(opponent);
        printInfo();
        break;
   }
   return beatUltimecia; 
}
void ArmyKnights::Print_and_delete_Opponent(BaseOpponent*& theOpponent){
    fight(theOpponent);
    delete theOpponent;
    theOpponent = NULL;
    
}
bool ArmyKnights::adventure (Events * events){
    theEvents = events;
    k = lastKnight();
    for (; i < events -> count();++ i ){
        if(k -> getKnightInfo(HP) <= 0)
            k = lastKnight();
        if (k == NULL)
            break;
        

        //cout << i + 1 << " ["<< events -> get(i)<<"]"<< endl;
        
        // if (i == 1 && theEvents -> get(i) == 95 && theEvents-> count() == 2)
        //     beatUltimecia = true;
        
        if (events -> get(i) == 1){
            BaseOpponent* theOpponent = new MadBear;
            Print_and_delete_Opponent(theOpponent);
        }
        else if (events -> get(i) == 2){
            BaseOpponent* theOpponent = new Bandit;
            Print_and_delete_Opponent(theOpponent);
        }
        else if (events -> get(i) == 3){
            BaseOpponent* theOpponent = new LordLupin;
            Print_and_delete_Opponent(theOpponent);
        }
        else if (events -> get(i) == 4){
            BaseOpponent* theOpponent = new Elf;
            Print_and_delete_Opponent(theOpponent);
        }
        else if (events -> get(i) == 5){
            BaseOpponent* theOpponent = new Troll;
            Print_and_delete_Opponent(theOpponent);
        }
        else if (events -> get(i) == 6){
            BaseOpponent* theOpponent = new Tornbery;
            Print_and_delete_Opponent(theOpponent);
        }
        else if (events -> get(i) == 7){
            BaseOpponent* theOpponent = new QueenOfCards;
            Print_and_delete_Opponent(theOpponent);
        }
        else if (events -> get(i) == 8){
            BaseOpponent* theOpponent = new NinaDeRings;
            Print_and_delete_Opponent(theOpponent);
        }
        else if (events -> get(i) == 9){
            BaseOpponent* theOpponent = new DurianGarden;
            Print_and_delete_Opponent(theOpponent);
        }
        else if (events -> get(i) == 10){
            BaseOpponent* theOpponent = new OmegaWeapon;
            Print_and_delete_Opponent(theOpponent);
        }
        else if (events -> get(i) == 11){
            BaseOpponent* theOpponent = new Hades;
            Print_and_delete_Opponent(theOpponent);
        }
        else if (events -> get(i) == 112){
            transferItem(PHOENIX_II, 1);
            printInfo();
        }
        else if (events -> get(i) == 113){
            transferItem(PHOENIX_III, 1);
            printInfo();
        }
        else if (events -> get(i) == 114){

            transferItem(PHOENIX_IV, 1);
            printInfo();
        }
        else if (events -> get(i) == 95){
            paladinShield = true;
            printInfo();

        }
        else if (events -> get(i) == 96){
            lancelotSpear = true;
            printInfo();
        }
        else if (events -> get(i) == 97){
            guinevereHair = true;
            printInfo();
        }
        else if (events -> get(i) == 98){
            if (paladinShield&&lancelotSpear&&guinevereHair)
            {excaliburSword = true;}
            printInfo();
        }
        else if (events -> get(i) == 99){
            BaseOpponent* theOpponent = new Ultimecia;
            Print_and_delete_Opponent(theOpponent);
        }
                
    }
    return beatUltimecia;
}
/* * * * * * * * * * * * * * * * * * * * * * * * END implementation of class ArmyKnights * * * * * * * * * * * * * * * * * * * * * * * */
//////////////////////////////////////////////////////////////////////////////////////////2









/* * * * * * * * * * * * * * * * * * * * * * * * BEGIN implementation of class KnightAdventure * * * * * * * * * * * * * * * * * * * * * * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
//////////////////////////////////////////////////////////////////////////////////////////1
KnightAdventure::~KnightAdventure(){
    
    armyKnights = NULL;
    delete events;
    events = NULL;
}
void KnightAdventure::run(){
    
    armyKnights -> printResult(this -> armyKnights -> adventure(events));
  
}
void KnightAdventure::loadArmyKnights(const string & file_armyknights){
    
    ArmyKnights *temp = new ArmyKnights(file_armyknights);
    armyKnights = temp;
}
void KnightAdventure::loadEvents(const string & file_events){

    Events* temp2 = new Events (file_events);
    events = temp2;
}
//////////////////////////////////////////////////////////////////////////////////////////2
/* * * * * * * * * * * * * * * * * * * * * * * * END implementation of class KnightAdventure * * * * * * * * * * * * * * * * * * * * * * * */
