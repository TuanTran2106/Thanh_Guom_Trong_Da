#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

class BaseKnight;
class BaseItem;
class Events;

enum ItemType {Antidote = 0, PhoenixDownI, PhoenixDownII, PhoenixDownIII, PhoenixDownIV};
class BaseBag {
protected:
    class Node{
    public:
        BaseItem* data;     //! dữ liệu của node
        Node* next;         //! node tiếp theo
    public:
        Node(BaseItem* data, Node*next);
        ~Node();
    };

protected:
    BaseKnight* knight; //! hiệp sĩ giữ túi
    Node* head = nullptr;   //! node đầu tiên
    int size = 0, Capacity = 0; //! size và maxsize của túi
public:
    BaseBag(BaseKnight* knight, int antidote, int phoenixDownI);
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual BaseItem * checkHp();
    virtual bool useItem(ItemType itemType);
    virtual void remove();
    virtual string toString() const;
    ~BaseBag();
};
class BagPaladinKnight : public BaseBag{
public:
    BagPaladinKnight(BaseKnight* knight, int antidote, int phoenixDownI);
};
class BagLancelotKnight : public BaseBag{
public:
    BagLancelotKnight(BaseKnight* knight, int antidote, int phoenixDownI);
};
class BagNormalKnight : public BaseBag{
public:
    BagNormalKnight(BaseKnight* knight, int antidote, int phoenixDownI);
};
class BagDragonKnight : public BaseBag{
public:
    BagDragonKnight(BaseKnight* knight, int antidote, int phoenixDownI);
};

enum OpponentType {MadBear = 1, Bandit, LordLupin, Elf, Troll, Tornbery, 
QueenOfCards, NinaDeRings, DurianGarden, OmegaWeapon, Hades};
class BaseOpponent{
public:
    //! tên quái vật
    virtual OpponentType Type() = 0;
};
class MadBearOpponent: public BaseOpponent{
public:
    OpponentType Type();
    
};
class BanditOpponent: public BaseOpponent{
public:
    OpponentType Type();
    
};
class LordLupinOpponent: public BaseOpponent{
public:
    OpponentType Type();
    
};
class ElfOpponent: public BaseOpponent{
public:
    OpponentType Type();
    
};
class TrollOpponent: public BaseOpponent{
public:
    OpponentType Type();
    
};
class TornberyOpponent: public BaseOpponent{
public:
    OpponentType Type();
    
};
class QueenOfCardsOpponent: public BaseOpponent{
public:
    OpponentType Type();
    
};
class NinaDeRingsOpponent: public BaseOpponent{
public:
    OpponentType Type();
    
};
class DurianGardenOpponent: public BaseOpponent{
public:
    OpponentType Type();
    
};
class OmegaWeaponOpponent: public BaseOpponent{
public:
    OpponentType Type();
    
};
class HadesOpponent: public BaseOpponent{
public:
    OpponentType Type();
    
};


enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;  

    bool poisoned = 0; // xét trúng độc hay không
public:
    int getHp();
    void setHp(int hp);
    int getLevel();
    void setLevel(int level);
    int getMaxHp();
    bool getPoisoned();
    void setPoisoned(bool poisoned);
    int getGil();
    void setGil(int gil);
    bool setBag(BaseItem* item);
    
public:
    BaseKnight(int id, int maxhp, int level, int gil);
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;

    virtual bool fight(BaseOpponent * opponent, int);
    virtual int knightBaseDamage() = 0; //! damge gây lên cho boss
    ~BaseKnight();
};
class PaladinKnight : public BaseKnight{
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    int knightBaseDamage(){return 0.06*level *hp;} //! damge gây lên cho boss
};
class LancelotKnight : public BaseKnight{
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    int knightBaseDamage(){return 0.05*level *hp;} //! damge gây lên cho boss
};
class DragonKnight : public BaseKnight{
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    int knightBaseDamage(){return 0.075*level *hp;} //! damge gây lên cho boss
};
class NormalKnight : public BaseKnight{
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    int knightBaseDamage(){return 0;}  //! damge gây lên cho boss
};
class ArmyKnights {
public:
    static bool isWinOmegaWeapon;   //! check thử OmegaWeapon chết chưa
    static bool isWinHades;     //! check thử isWinHades chết chưa
private:
    BaseKnight** array; //! danh sách quân đoàn
    int size;   //! kích thước
    int i = 0;  //! thứ tự sự kiện
    bool ishasPaladinShield = false;
     bool ishasLancelotSpear = false;
      bool ishasGuinevereHair = false; 
     bool isExcaliburSword = false; 
public:
    ArmyKnights (const string & file_armyknights){
        ifstream input;
        input.open(file_armyknights);   //! đọc file
        input >> size; //! nhập size
        array = new BaseKnight*[size]; //! khởi tạo
        //! thêm từng hiệp sĩ
        for(int i = 0; i < size; i++){
            int maxhp, level, phoenixdownI, gil, antidote;
            input >> maxhp >> level >> phoenixdownI >> gil >> antidote;
            //! tạo ra hiệp sĩ
            array[i] = BaseKnight::create(i + 1, maxhp, level, gil,antidote, phoenixdownI);
        }    
    }
    ~ArmyKnights(){
        //! xóa các hiệp sĩ còn sống
        for(int i = 0; i < size; i++) delete array[i];
        //! xóa quân đoàn
        delete[] array;
    }
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const{ return this->size;}
    BaseKnight * lastKnight() const{ return this->array[size - 1];}

    bool hasPaladinShield() const{ return ishasPaladinShield;}
    bool hasLancelotSpear() const{ return ishasLancelotSpear;}
    bool hasGuinevereHair() const{ return ishasGuinevereHair;}
    bool hasExcaliburSword() const{ return isExcaliburSword;}


    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
protected:
    ItemType itemType;  //! tên vật phẩm
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    virtual ItemType Type (){return itemType;}
};
class AntidoteItem: public BaseItem{
public:
    AntidoteItem();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownIItem: public BaseItem{
public:
    PhoenixDownIItem();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownIIItem: public BaseItem{
public:
    PhoenixDownIIItem();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);  
};
class PhoenixDownIIIItem: public BaseItem{
public:
    PhoenixDownIIIItem();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownIVItem: public BaseItem{
public:
    PhoenixDownIVItem();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};

class Events {
private:
    int* array;
    int size;
public:
    Events(string file_input){
        ifstream input(file_input);
        input >> size;
        array = new int[size];
        for(int i = 0; i < size; i++) input >> array[i];
    }
    int count() const{return size;}
    int get(int i) const{return array[i];}
    ~Events(){delete[] array;}
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure() {}
    void loadArmyKnights(const string & file){armyKnights = new ArmyKnights(file);}
    void loadEvents(const string & file){events = new Events(file);}
    void run(){armyKnights->printResult(armyKnights->adventure(events));}
    ~KnightAdventure(){
        delete armyKnights;
        delete events;
    }
};

#endif // __KNIGHT2_H__