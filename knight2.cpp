#include "knight2.h"


bool ArmyKnights::isWinHades = false;
bool ArmyKnights::isWinOmegaWeapon = false;



/* * * BEGIN implementation of class BaseOpponent * * */

//! Inheritance MadBear Opponent
//! tên quái vật
OpponentType MadBearOpponent::Type(){return MadBear;}

//! Inheritance Bandit Opponentt
OpponentType BanditOpponent::Type(){return Bandit;}

//! Inheritance LordLupin Opponent
OpponentType LordLupinOpponent::Type(){return LordLupin;}

//! Inheritance Elf Opponent
OpponentType ElfOpponent::Type(){return Elf;}

//! Inheritance Troll Opponent
OpponentType TrollOpponent::Type(){return Troll;}


//! Inheritance Tornbery Opponent
OpponentType TornberyOpponent::Type(){return Tornbery;}

//! Inheritance Queen Of Cards Opponent
OpponentType QueenOfCardsOpponent::Type(){return QueenOfCards;}


//! Inheritance NinaDeRings Opponent
OpponentType NinaDeRingsOpponent::Type(){return NinaDeRings;}

//! Inheritance Durian Garden Opponent
OpponentType DurianGardenOpponent::Type(){return DurianGarden;}

//! Inheritance OmegaWeapon Opponent
OpponentType OmegaWeaponOpponent::Type(){return OmegaWeapon;}


//! Inheritance Hades Opponent
OpponentType HadesOpponent::Type(){return Hades;}


/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class BaseBag * * */
//! khởi tạo 1 node
BaseBag::Node::Node(BaseItem* data, Node*next):data(data),next(next){}
//! xóa node sẽ xóa luôn data trong node đó
BaseBag::Node::~Node(){delete data;}

//! Base Base Bag

//! hàm khởi tạo khởi tạo các giá trị mặc định
BaseBag::BaseBag(BaseKnight* knight, int antidote, int phoenixDownI){
    this->knight = knight;
    this->Capacity = 0;
    this->head = nullptr;
    this->size = 0;
}
//! thêm node vào đầu danh sách
bool BaseBag::insertFirst(BaseItem * item){
    //! đầy rồi không thêm được
    if(size == Capacity) return false;
    //! thêm node tăng size
    head = new Node(item, head);
    size ++;
    return true;
}
BaseItem * BaseBag::get(ItemType itemType){
    //! không có node nào hết
    if(size == 0) return nullptr;

    Node* temp = head;
    //! duyệt tìm node có itemType truyền vào
    while(temp && temp->data->Type() != itemType) temp = temp->next;
    //! tìm được node rồi đưa giá trị nó lên đầu bằng cách swap
    if(temp){
        swap(head->data, temp->data);   //! trao đổi giá trị
        return head->data;              //! trả về thuốc cần dùng
    }
    //! không tìm thấy node đó
    return nullptr;
}
BaseItem * BaseBag::checkHp(){
    //! như phần get trên
    if(size == 0) return nullptr;

    Node* temp = head;
    //! tìm node đầu tiên có thuốc có thể dùng sẽ không rơi vào TH antione vì khi trúng độc đã dùng trước khi hp giảm
    while(temp && !temp->data->canUse(knight)) temp = temp->next;
    if(temp){
        swap(head->data, temp->data);
        return head->data;
    }
    return nullptr;
}
bool  BaseBag::useItem(ItemType itemType){
    BaseItem* temp = nullptr;

    //! thuốc cần tìm ở loại gì chia làm 2 loại là antionte và phoenxI
    if(itemType == Antidote) temp = get(itemType);
    else temp = checkHp();

    //! không tìm thấy
    if(temp == nullptr) return false;

    //! dùng thôi xong rồi xóa nó
    this->head->data->use(knight);
    remove();
    return true;
}
string BaseBag::toString() const{
    //! không có node nào
    if(size == 0) return "Bag[count=0;]";
    string result = "Bag[count=" + to_string(size) + ";";
    //! ánh xạ từ type sang string
    string typeString[] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};
    Node* temp = head;
    //! duyệt thôi
    while(temp){
        result += typeString[temp->data->Type()] + ","; //! ánh xạ
        temp = temp->next;
    }
    //! vì cuối dư ra dấu , thay cho ]
    result[result.length() - 1] = ']';
    return result;    
}
void BaseBag::remove(){
    //! danh sách rỗng
    if(size == 0) return;

    //! xóa node đầu tiên thôi
    size --;
    Node* temp = head;
    head = head->next;
    delete temp;
}
BaseBag::~BaseBag(){
    //! xóa từng các node cho đến khi hết
    while(size) remove();
}

//! Inheritance Paladin Knight
BagPaladinKnight::BagPaladinKnight(BaseKnight* knight,int antidote, int phoenixDownI)
:BaseBag(knight, antidote, phoenixDownI)
{
    //! maxsize = - 1 nghĩa là vô cực
    this->Capacity = -1;
    //! khởi tạo antidote và phoenixDownI lúc đầu
    while(this->size != this->Capacity && phoenixDownI--) this->insertFirst(new PhoenixDownIItem());
    while(this->size != this->Capacity && antidote--) this->insertFirst(new AntidoteItem());
}

//! Inheritance Lancelot Knight
BagLancelotKnight::BagLancelotKnight(BaseKnight* knight,int antidote, int phoenixDownI)
:BaseBag(knight, antidote, phoenixDownI)
{
    //! như phần trên
    this->Capacity = 16;
    while(this->size != this->Capacity && phoenixDownI--) this->insertFirst(new PhoenixDownIItem());
    while(this->size != this->Capacity && antidote--) this->insertFirst(new AntidoteItem());
}

//! Inheritance Normal Knight
BagNormalKnight::BagNormalKnight(BaseKnight* knight,int antidote, int phoenixDownI)
:BaseBag(knight, antidote, phoenixDownI)
{
    this->Capacity = 19;
    while(this->size != this->Capacity && phoenixDownI--) this->insertFirst(new PhoenixDownIItem());
    while(this->size != this->Capacity && antidote--) this->insertFirst(new AntidoteItem());
}

//! Inheritance Dragon Knight
BagDragonKnight::BagDragonKnight(BaseKnight* knight,int antidote, int phoenixDownI)
:BaseBag(knight, antidote, phoenixDownI)
{
    this->Capacity = 14;
    //! rồng không nhận antinote nên không thêm
    while(this->size != this->Capacity && phoenixDownI--) this->insertFirst(new PhoenixDownIItem());
}

/* * * END implementation of class BaseBag * * */


/* * * BEGIN implementation of class BaseItem * * */
//! Inheritance Antidote Item
//! hàm getPoisoned dùng để kiểm tra xem có bị nhiễm độc hay không
bool AntidoteItem::canUse(BaseKnight* knight){ return knight->getPoisoned();}
//! hàm setPoisoned giải độc
void AntidoteItem::use(BaseKnight* knight){ knight->setPoisoned(false); }
//! trả về tên của thuốc
AntidoteItem::AntidoteItem (){ itemType = Antidote;}

//! Inheritance PhoenixDownI Item
//! như phần trên + đọc trong file pdf của thầy tại sự kiện 112 113 113
bool PhoenixDownIItem::canUse(BaseKnight* knight){ return knight->getHp() <= 0; }
void PhoenixDownIItem::use(BaseKnight* knight){ knight->setHp(knight->getMaxHp()); }
PhoenixDownIItem::PhoenixDownIItem (){itemType =  PhoenixDownI; }

//! Inheritance PhoenixDownII Item
bool PhoenixDownIIItem::canUse(BaseKnight* knight){return knight->getHp() < knight->getMaxHp() / 4;}
void PhoenixDownIIItem::use(BaseKnight* knight){ knight->setHp(knight->getMaxHp());}
PhoenixDownIIItem::PhoenixDownIIItem (){ itemType = PhoenixDownII;}

//! Inheritance PhoenixDownIII Item
bool PhoenixDownIIIItem::canUse(BaseKnight* knight){return knight->getHp() < knight->getMaxHp() / 3;}
void PhoenixDownIIIItem::use(BaseKnight* knight){knight->setHp( (knight->getHp() <= 0) ? knight->getMaxHp()/3 : knight->getMaxHp()/4+knight->getHp());}
 PhoenixDownIIIItem::PhoenixDownIIIItem (){ itemType = PhoenixDownIII;}

//! Inheritance PhoenixDownIV Item
bool PhoenixDownIVItem::canUse(BaseKnight* knight){return knight->getHp() < knight->getMaxHp() / 2;}
void PhoenixDownIVItem::use(BaseKnight* knight){knight->setHp( (knight->getHp() <= 0) ? knight->getMaxHp()/2 : knight->getMaxHp()/5+knight->getHp());}
PhoenixDownIVItem::PhoenixDownIVItem(){itemType = PhoenixDownIV;}
/* * * END implementation of class BaseItem * * */


/* * * BEGIN implementation of class BaseKnight * * */
//! static
BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    BaseKnight* knight;
    //! hiệp sĩ LancelotKnight
    if(maxhp == 888){
        knight = new LancelotKnight(id, maxhp, level, gil , antidote, phoenixdownI);
    }
    //! hiệp sĩ DragonKnight
    else if(maxhp == 345 || maxhp == 354 || maxhp == 435 || maxhp == 453 || maxhp == 534 || maxhp == 543){
        knight = new DragonKnight(id, maxhp, level, gil , antidote, phoenixdownI);
    }
    else{
        //! check số nguyên tố 
        int count = 0;
        for(int i = 1; i <= maxhp; i++) count += (maxhp % i == 0);

         //! hiệp sĩ PaladinKnight
        if(count == 2){
            knight = new PaladinKnight(id, maxhp, level, gil , antidote, phoenixdownI);         
        }
        //! hiệp sĩ NormalKnight
        else{
            knight = new NormalKnight(id, maxhp, level, gil , antidote, phoenixdownI);
        }
    }

    return knight;
}

//! Base kight
//! khởi tạo các giá trị
BaseKnight::BaseKnight(int id, int maxhp, int level, int gil){
    this->id = id;
    this->maxhp = this->hp = maxhp;
    this->level = level;
    this->gil = gil;
}
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format cout must be the same
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
//! chiến đầu cùng quái vật 
bool  BaseKnight::fight(BaseOpponent * opponent, int i){
    int t = int(opponent->Type());  //! tên quái vật or sự kiện gặp quái vật
    //! từ sự kiện 1 -> 5
    if(t >= 1 && t <=5){
        int levelO = (i + t)%10 + 1;
        //! hiệp sĩ PALADIN LANCELOT luôn thắng, levelO <= level thắng
        if(knightType == PALADIN || knightType == LANCELOT || levelO <= level) {
            if(t == 1) gil += 100;
            else if(t == 2) gil += 150;
            else if(t == 3) gil += 450;
            else if(t == 4) gil += 750;
            else if(t == 5) gil += 800;
        }
        //! thua rồi
        else{
            if(t == 1) hp -= 10*(levelO - level);
            else if(t == 2) hp -= 15*(levelO - level);
            else if(t == 3) hp -= 45*(levelO - level);
            else if(t == 4) hp -= 75*(levelO - level);
            else if(t == 5) hp -= 95*(levelO - level);
            //! vì hp giảm nên cần kiểm tra thuốc lấy ra sài 
            //! tìm PhoenixDownIII tránh TH với atinote thôi ko cần bận tâm PhoenixDown gì cũng được
            this->bag->useItem(PhoenixDownIII);
        }

    }
    //! sự kiện 6
    else if(t == 6){
         int levelO = (i + t)%10 + 1;
         //! thắng
        if(levelO <= level) level ++;
        //! hiệp sĩ rồng bỏ qua nếu không phải thì thua
        else if(knightType != DRAGON){
            //! bị trúng độc
            this->poisoned = true;
            if(this->poisoned){
                //! tìm thuốc
                this->bag->useItem(Antidote);
                //! không thấy thuốc
                if(this->poisoned){
                    //! giải độc trừ đi 3 túi và hp giảm
                    this->poisoned = false;
                    this->bag->remove();
                    this->bag->remove();
                    this->bag->remove();
                    hp -= 10;
                    //! vì hp giảm nên cần phải tìm item trong túi
                     //! tìm PhoenixDownIII tránh TH với atinote thôi ko cần bận tâm PhoenixDown gì cũng được
                    this->bag->useItem(PhoenixDownIII);
                }
            }  
        }
        //! nếu level vược quá cho phép
        if(level > 10) level = 10;
    
    }
    //! sự kiên 7
    else if(t == 7){
        int levelO = (i + t)%10 + 1;
        //! thắng
        if(levelO <= level) gil = gil * 2;
        //! hiệp sĩ PALADIN bị bỏ qua nếu không bỏ qua thì thua
        else if(knightType != PALADIN) gil = (gil / 2 );
    }
    //! sự kiện 8 với hiệp sĩ PALADIN nếu hp < maxhp / 3 thì tăng hp miễn phí
    else if(t == 8 && hp < maxhp/3 && knightType == PALADIN) hp += maxhp/5;
    //! sự kiện 8 tăng hp có phí
    else if(t == 8 && hp < maxhp/3 && gil >= 50){
        gil -= 50;
        hp += maxhp/5;
    }
    //! sự kiện 9 cập nhật hp về maxhp
    else if(t == 9) hp = maxhp;
    //! sự kiện 10 chỉ được gọi khi OmegaWeapon còn sống nếu chết bỏ qua
    else if(t == 10 && !ArmyKnights::isWinOmegaWeapon){
        //! chỉ có hiệp sĩ rồng or level = 10 và hp đạt maxhp mới chiến đầu thắng
        if(level == 10 && hp == maxhp|| knightType == DRAGON){
            //! chiến lợi phẩm
            level = 10;
            gil = 999;
            //! OmegaWeapon chết
            ArmyKnights::isWinOmegaWeapon = true;
        }
        //! thua
        else{
            hp = 0;  
            //! tìm thuốc hồi sinh
            this->bag->useItem(PhoenixDownIII);  
        }     
    }
    else if(t == 11 && !ArmyKnights::isWinHades){
        //! hiệp sĩ chiến thắng khi level = 10 or là hiệp sĩ  PALADIN  có level >= 8
        ArmyKnights::isWinHades = (level == 10 || knightType == PALADIN && level >= 8);

        //! thua rồi :))
        if(!ArmyKnights::isWinHades){
            hp = 0;  
            //! tìm thuốc hồi sinh
            this->bag->useItem(PhoenixDownIII);  
        }     
    }      

    //! dùng vàng mua hp để hồi sinh chơi tiếp
    if(this->hp <= 0 && this->gil >= 100){
        this->hp = this->maxhp / 2;
        this->gil -= 100;
    }
    //! xem hiệp sĩ chết chưa
    return hp > 0;
}
BaseKnight::~BaseKnight(){
    delete bag;
}

//! set and get ở code 2 có thể không dùng 1 số hàm các em có thể xóa nha do để lại từ code 1
int BaseKnight::getHp(){return hp;}
int BaseKnight::getLevel(){return level;}
int BaseKnight::getMaxHp(){return maxhp;}
bool BaseKnight::getPoisoned(){return poisoned;}
int BaseKnight::getGil(){ return gil;}

void BaseKnight::setHp(int hp){
    if(this->hp > hp){
        this->hp = hp;
        this->bag->useItem(PhoenixDownI);
        if(this->hp <= 0 && this->gil >= 100){
            this->hp = this->maxhp / 2;
            this->gil -= 100;
        }
    }
    else{
        this->hp = hp;
        if(hp > maxhp) this->hp = maxhp;
    }
}
void BaseKnight::setLevel(int level){this->level = (level > 10) ? 10 : level;}
void BaseKnight::setPoisoned(bool poisoned){this->poisoned = poisoned;    } 
void BaseKnight::setGil(int gil){this->gil = gil;}
bool BaseKnight::setBag(BaseItem* item){return bag->insertFirst(item);}



//! Inheritance Paladin Knight
PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
:BaseKnight(id, maxhp, level, gil)
{
    //! khởi tạo tên và túi của hiệp sĩ thôi
    this->knightType = PALADIN;
    this->bag = new BagPaladinKnight(this,antidote,phoenixdownI);
}

//! Inheritance Lancelot Knight
LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
:BaseKnight(id, maxhp, level, gil)
{
    //! khởi tạo tên và túi của hiệp sĩ thôi
    this->knightType = LANCELOT;
    this->bag = new BagLancelotKnight(this,antidote,phoenixdownI);
}

//! Inheritance Dragon Knight
DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
:BaseKnight(id, maxhp, level, gil)
{
    //! khởi tạo tên và túi của hiệp sĩ thôi
    this->knightType = DRAGON;
    this->bag = new BagDragonKnight(this,antidote,phoenixdownI);
}


//! Inheritance Normal Knight
NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
:BaseKnight(id, maxhp, level, gil)
{
    //! khởi tạo tên và túi của hiệp sĩ thôi
    this->knightType = NORMAL;
    this->bag = new BagNormalKnight(this,antidote,phoenixdownI);
}


/* * * END implementation of class BaseKnight * * */


/* * * BEGIN implementation of class ArmyKnights * * */


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
        << endl
        << string(50, '-') << endl;
}
void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

bool ArmyKnights::fight(BaseOpponent * opponent){

    //! gọi hiệp sĩ cuối cùng ra chiến đấu
    while(size){
        BaseKnight * lknight = lastKnight(); //! hiệp sĩ cuối
        //! win
        if(lknight->fight(opponent, i)){
            //! xem thử có chiến thắng Hades không để cập nhật PaladinShield
            if(ArmyKnights::isWinHades)this->ishasPaladinShield = true;
            //! truyền vàng cho hiệp sĩ tiếp theo
            for(int i = size - 1; i >=0 ; i--){
                int du = array[i]->getGil() - 999; //! có vàng dư hay không
                if(du <= 0) break;  //! không dư thì không truyền thôi
                array[i]->setGil(999);  //! dư thì cập nhật lại maxgil = 999
                if(i > 0) array[i-1] -> setGil(array[i-1]->getGil() + du); //! truyền cho thằng sau
            }
            break;
        }
        //! thua thì chết thôi và break tới sự kiện tiếp theo
        size --;
        delete lknight;
        break;
    }
    //! nhớ xóa không leak
    delete opponent;
    //! xem thử còn thằng nào sống không
    return size;
}
bool ArmyKnights::adventure (Events * events){
    this->i = 0; //! biến i biến thứ tự sự kiện
     ArmyKnights::isWinHades = ArmyKnights::isWinOmegaWeapon = false;
   for(; i < events->count(); i++){
        //! LẤY SỰ KIỆN
        int count_event = events->get(i);
        cout << "event: " << count_event << " i = " << i << " --- ";

        //! cập nhật các bảo vật
        this->ishasPaladinShield = (count_event == 95) || ishasPaladinShield;
        this->ishasLancelotSpear = (count_event == 96) || ishasLancelotSpear;
        this->ishasGuinevereHair = (count_event == 97) || ishasGuinevereHair;
        this->isExcaliburSword = ((count_event == 98) &&ishasPaladinShield && ishasLancelotSpear && ishasGuinevereHair )||this->isExcaliburSword;
        
        //! chiến đấu với quái vật
        if(count_event == 1 )this->fight(new MadBearOpponent());
        else if(count_event == 2 )this->fight(new BanditOpponent());
        else if(count_event == 3 )this->fight(new LordLupinOpponent());
        else if(count_event == 4  )this->fight(new ElfOpponent());
        else if(count_event == 5 )this->fight(new TrollOpponent());
        else if(count_event == 6 )this->fight(new TornberyOpponent());
        else if(count_event == 7)this->fight(new QueenOfCardsOpponent());
        else if(count_event == 8)this->fight(new NinaDeRingsOpponent());
        else if(count_event == 9)this->fight(new DurianGardenOpponent());
        else if(count_event == 10)this->fight(new OmegaWeaponOpponent());
        else if(count_event == 11)this->fight(new HadesOpponent());

        //! thêm vật phẩm vào túi
        else if(count_event == 112 || count_event == 113 || count_event == 114){
            BaseItem* item = nullptr;
            if(count_event == 112) item = new PhoenixDownIIItem();  
            else if(count_event == 113) item = new PhoenixDownIIIItem();
            else if(count_event == 114) item = new PhoenixDownIVItem();
            bool insert = false; //! xem thử đã thêm chưa
            //! duyệt từ cuối lên đầu
            for(int j = size - 1 ; j >= 0; j--){
                //! nếu thêm được thì break
                if(insert = array[j]->setBag(item)) break; 
            }
            //! nếu không chèn được do các túi của hiệp sĩ đã đầy delete nó thôi
            if(!insert) delete item;
        }

        //! chiến đầu cuối cùng
        else if(count_event == 99){
            if(isExcaliburSword){
                this->printInfo();
                return true;
            }
            else if(!ishasGuinevereHair || !ishasLancelotSpear || !ishasPaladinShield){
                for(int i = 0; i < size ; i++) delete array[i];
                size = 0;
                this->printInfo();
                return false;    
            }
            else{
                int HpUltimecia = 5000; //! hp của boss
                BaseKnight * last = NULL;   //! hiệp sĩ thường cuối cùng đã chết
                int numberNor = 0;  //! số lượng hiệp sĩ thường chết

                while(size){
                    BaseKnight * knight = lastKnight(); //! hiệp sĩ cuối cùng
                    HpUltimecia -= knight->knightBaseDamage(); //! gây damage cho boss

                    //! hiệp sĩ thường 
                    if(!knight->knightBaseDamage()){
                        numberNor++;    //! số hiệp sĩ thường bị chết
                        if(!last) last = knight;    //! hiệp sĩ thường đầu tiên chết
                        else delete knight;         //! các hiệp sĩ thường không phải đầu tiên bị chết
                    }
                    else{
                        //! win
                        if(HpUltimecia <= 0){
                            size += numberNor;  //! hồi sinh các hiệp sĩ bình thường chết
                            if(last) array[size - 1] = last;    //! hồi sinh hiệp sĩ thường cuối cùng chết
                            this->printInfo();  
                            if(last) delete last;   //! xóa hiệp sĩ cuối cùng
                            size -= numberNor;      //! cập nhật lại các hiệp sĩ còn sống thực tế
                            //! win
                            return true;
                        }
                        delete knight;
                    }
                    size --;
                    //! thua rồi
                    if(size == 0){
                        //! xóa hiệp sĩ thường cuối cùng
                        if(last) delete last;
                        this->printInfo();
                        return false;   
                    }
                }
            }     
        }
        this->printInfo();
        //! xem thử thua hay chưa
        if(size == 0) return false;
    }
    
    return true;    
}


/* * * END implementation of class ArmyKnights * * */




