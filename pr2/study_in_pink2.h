#pragma once
/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2023
 * Author: Vu Van Tien
 * Date: 02.02.2023
 */

 // The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"
////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;

class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;

class MagicBook;
class EnergyDrink;
class FirstAid;
class ExcemptionCard;
class PassingCard;
class Character;
class Sherlock;
class Watson;
class Robot;
class TestStudyInPink;

enum MovingObjectType { SHERLOCK, WATSON, CRIMINAL, ROBOT };
enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C = 0, S, W, SW };

//MapElement
class MapElement {
    friend class TestStudyInPink;
protected:
    ElementType type;
public:
    MapElement(ElementType in_type);
    virtual ~MapElement();
    virtual ElementType getType() const;
};

class Path : public MapElement {
    friend class TestStudyInPink;
public:
    Path() : MapElement(PATH) {}
};

class Wall : public MapElement {
    friend class TestStudyInPink;
public:
    Wall() : MapElement(WALL) {}
};

class FakeWall : public MapElement {
    friend class TestStudyInPink;
private:
    int req_exp;
public:
    FakeWall(int in_req_exp);
    int getReqExp() const;
};

//Map
class Map
{
    friend class TestStudyInPink;
private:
    int num_rows, num_cols;
    MapElement*** map;
public:
    Map(int num_rows, int num_cols, int num_walls, Position* array_walls, int num_fake_walls, Position* array_fake_walls);
    ~Map();
    int getNumRows() const;
    int getNumCols() const;
    bool isValid(const Position& pos, MovingObject* mv_obj) const;
};

//Position
class Position {
    friend class TestStudyInPink;
private:
    int r, c;
public:
    static const Position npos;

    Position(int r = 0, int c = 0);

    Position(const string& str_pos);

    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);

    string str() const;

    bool isEqual(const Position& pos) const;
    bool isEqual(int r, int c) const;
};

//MovingObject
class MovingObject
{
    friend class TestStudyInPink;
protected:
    int index;
    Position pos;
    Map* map;
    string name;
    Position fpos;
    int hp, exp;
    MovingObjectType obj_type;

public:
    MovingObject(int index, const Position pos, Map* map, const string& name = "");
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const;
    Position getFuturePosition() const;
    virtual void move() = 0;
    virtual string str() const = 0;
    //MovingObjectType getObjectType() const;
    string getName() const;
};

//Character
class Character : public MovingObject
{
    friend class TestStudyInPink;
protected:
    int hp, exp;
    string moving_rule;
    int count_moving = 0;
    Position future_step;
public:
    Character(int index, const Position& init_pos, Map* map, const string& name = "");
    //virtual ~Character();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const;
    //Position getFuturePosition();
    virtual void move() = 0;
    virtual int getHp() const;
    virtual int getExp() const;
    virtual void setHp(int hp);
    virtual void setExp(int exp);
};

//Sherlock
class Sherlock :public Character
{
    friend class TestStudyInPink;
private:
    BaseBag* sherlockBag;

public:
    Sherlock(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp);
    string str() const;
    Position getNextPosition() override;
    void move() override;
    void setPos(Position pos);
    //BaseBag* getBag() const;
    // ...
};

//Watson
class Watson :public Character
{
    friend class TestStudyInPink;
private:
    Position future_step;
    int count_moving2 = 0;
    BaseBag* watsonBag;

public:
    Watson(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp);
    string str() const;
    Position getNextPosition() override;
    void move() override;
    //BaseBag* getBag() const;
};

//Criminal
class Criminal :public Character
{
    friend class TestStudyInPink;
private:
    Sherlock* sherlock;
    Watson* watson;
    int step = 0;
    Position prev_pos = Position(-1, -1);

public:
    Criminal(int index, const Position& init_pos, Map* map, Sherlock* sherlock, Watson* watson);
    Position getNextPosition() override;
    Position getPreviousPosition() const;
    void move() override;
    string str() const;
    int getStep() const;
    bool canCreateRobot() const;
};

//ArrayMovingObject
class ArrayMovingObject {
    friend class TestStudyInPink;
private:
    MovingObject** arr_mv_objs;
    int count = 0;
    int capacity;

public:
    ArrayMovingObject(int capacity);
    ~ArrayMovingObject();
    bool isFull() const;
    bool add(MovingObject* mv_obj);
    MovingObject* get(int index) const;
    int size() const; // return current number of elements in the array
    string str() const;
};

//Congiguration
class Configuration {
    friend class StudyPinkProgram;

private:
    int map_num_rows;
    int map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position* arr_walls;
    int num_fake_walls;
    Position* arr_fake_walls;
    string sherlock_moving_rule;
    Position sherlock_init_pos;
    int sherlock_init_hp;
    int sherlock_init_exp;
    string watson_moving_rule;
    Position watson_init_pos;
    int watson_init_hp;
    int watson_init_exp;
    Position criminal_init_pos;
    int num_steps;

public:
    Configuration(const string& filepath);
    ~Configuration();
    string str() const;
};

// Robot, BaseItem, BaseBag,...

//Robot
class Robot : public MovingObject
{
    friend class TestStudyInPink;
protected:
    RobotType robot_type;
    //BaseItem* item;  
    Criminal* criminal;
    /*Sherlock* sherlock;
    Watson* watson;*/
    ///*RobotC* robotC;
    //RobotS* robotS;
    //RobotW* robotW;*/
    //RobotSW* robotSW;
    BaseItem* tempItem;
    //Position createRobot_pos;
    //Position** arr_createRobot_pos;
public:
    Robot(int index, const Position& init_pos, Map* map, Criminal* criminal, const string& name);
    //static Robot* createRobot(int index, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson);
    RobotType getRobotType() const;
    //bool checkMeet() const;
    virtual int getDistance() const = 0;
    //void setItem(int i, int j);
    BaseItem* getItem() const;
    ~Robot();
};

//RobotC
class RobotC : public Robot
{
    friend class TestStudyInPink;
private:
    RobotType robot_type = C;
    //BaseItem* item = NULL;
public:
    RobotC(int index, const Position& init_pos, Map* map, Criminal* criminal);
    Position getNextPosition() override;
    void move() override;
    int getDistance() const { return 0; };
    int getDistance(Sherlock* sherlock) const;
    int getDistance(Watson* watson) const;
    string str() const;
};
//RobotS
class RobotS : public Robot
{
    friend class TestStudyInPink;
private:
    Sherlock* sherlock;
    RobotType robot_type = S;
    //BaseItem* item = NULL;
public:
    RobotS(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock);
    Position getNextPosition() override;
    void move() override;
    int getDistance() const;
    string str() const;
};

//RobotW
class RobotW : public Robot
{
    friend class TestStudyInPink;
private:
    Watson* watson;
    RobotType robot_type = W;
    //BaseItem* item = NULL;
public:
    RobotW(int index, const Position& init_pos, Map* map, Criminal* criminal, Watson* watson);
    Position getNextPosition() override;
    void move() override;
    int getDistance() const;
    string str() const;
};

//RobotSW
class RobotSW : public Robot
{
    friend class TestStudyInPink;
private:
    Sherlock* sherlock;
    Watson* watson;
    RobotType robot_type = SW;
    //BaseItem* item = NULL;
public:
    RobotSW(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson);
    Position getNextPosition() override;
    void move() override;
    int getDistance() const;
    string str() const;
};

//BaseItem
class BaseItem
{
    friend class TestStudyInPink;
protected:
    ItemType item_type;
    string challenge;
public:
    BaseItem(ItemType item_type);
    virtual bool canUse(Character* obj, Robot* robot) = 0;
    virtual void use(Character* obj, Robot* robot) = 0;
    //ItemType getItemType(int i, int j) const;
    virtual ItemType getType() const = 0;
    virtual string str() const = 0;
    void setChallenge(string challenge);
};

//MagicBook
class MagicBook : public BaseItem
{
    friend class TestStudyInPink;
public:
    MagicBook();
    bool canUse(Character* obj, Robot* robot);
    void use(Character* obj, Robot* robot);
    ItemType getType() const override;
    string str() const override;
};
//EnergyDrink
class EnergyDrink : public BaseItem
{
    friend class TestStudyInPink;
public:
    EnergyDrink();
    bool canUse(Character* obj, Robot* robot);
    void use(Character* obj, Robot* robot);
    ItemType getType() const override;
    string str() const override;
};
//FirstAid
class FirstAid : public BaseItem
{
    friend class TestStudyInPink;
public:
    FirstAid();
    bool canUse(Character* obj, Robot* robot);
    void use(Character* obj, Robot* robot);
    ItemType getType() const override;
    string str() const override;
};
//ExcemptionCard
class ExcemptionCard : public BaseItem
{
    friend class TestStudyInPink;
public:
    ExcemptionCard();
    bool canUse(Character* obj, Robot* robot);
    void use(Character* obj, Robot* robot);
    ItemType getType() const override;
    string str() const override;
};
//PassingCard
class PassingCard : public BaseItem
{
    friend class TestStudyInPink;
private:
public:
    PassingCard(int i);
    PassingCard(string challenge);
    bool canUse(Character* obj, Robot* robot);
    void use(Character* obj, Robot* robot);
    ItemType getType() const override;
    //string getChallenge(int i, int j);
    string str() const override;
};

//Node
class Node
{
    friend class TestStudyInPink;
public:
    Node* next;
    BaseItem* item;
public:
    Node(BaseItem* item, Node* next = nullptr) :item(item), next(next) {};
    //~Node();
};

//BaseBag
class BaseBag
{
    friend class TestStudyInPink;
protected:
    Node* head = NULL;
    int count;
    int maxItems;
    Sherlock* sherlock;
    Watson* watson;
public:
    BaseBag(int maxItems);
    //Node* makeNode(BaseItem* item);
    virtual bool insert(BaseItem* item); // return true if insert successfully 
    virtual bool canInsert() const;
    virtual BaseItem* get() = 0; // return the item as described above , if not found, return NULL
    virtual BaseItem* get(ItemType itemType) = 0; // return the item as described above, if not found, return NULL
    bool search(ItemType itemType) const;
    ~BaseBag();
    bool isFull();
    virtual string str() const;
    void swap(Node* a, Node* b);
};

//SherlockBag
class SherlockBag : public BaseBag
{
    friend class TestStudyInPink;
public:
    SherlockBag(Sherlock* sherlock);
    BaseItem* get() override;
    BaseItem* get(ItemType itemType) override;
};

//WatsonBag
class WatsonBag : public BaseBag
{
    friend class TestStudyInPink;
public:
    WatsonBag(Watson* watson);
    BaseItem* get() override;
    BaseItem* get(ItemType itemType) override;
};

//StudyPinkProgram
class StudyPinkProgram {
    friend class TestStudyInPink;
private:
    Configuration* config;
    Sherlock* sherlock;
    Watson* watson;
    Criminal* criminal;
    Map* map;
    ArrayMovingObject* arr_mv_objs;
    SherlockBag* sherlockBag;
    WatsonBag* watsonBag;
    //BaseItem* robotItem;
    string outputFile;

public:
    StudyPinkProgram(const string& config_file_path);
    bool isStop() const;
    void printResult() const
    {
        // if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        // {
        //     cout << "Sherlock caught the criminal" << endl;
        // }
        // else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        // {
        //     cout << "Watson caught the criminal" << endl;
        // }
        // else
        // {
        //     cout << "The criminal escaped" << endl;
        // }
    }

    void printStep(int si) const
    {
        // cout << "Step: " << setw(4) << setfill('0') << si
        //      << "--"
        //      << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }
    //void run(bool verbose);
    ~StudyPinkProgram();
    // addition
    void run(bool verbose, ofstream& OUTPUT);
    void printInfo(int si, int i, ofstream& OUTPUT)
    {
        OUTPUT << endl
            << "*************AFTER MOVE*************" << endl;
        OUTPUT
            << "ROUND : " << si << " - TURN : " << i << endl;
        stringstream ss(arr_mv_objs->str());
        string lineArr = "";
        getline(ss, lineArr, 'C');
        OUTPUT << lineArr << "]" << endl;
        getline(ss, lineArr, ']');
        OUTPUT << "\tC" << lineArr << "]" << endl;
        while (getline(ss, lineArr, ']'))
        {
            if (lineArr.length() > 0)
                OUTPUT << "\t" << lineArr.substr(1) << "]" << endl;
        }
        OUTPUT << "Sherlock HP_" << sherlock->getHp() << " EXP_" << sherlock->getExp() << endl
            << "Watson HP_" << watson->getHp() << " EXP_" << watson->getExp() << endl
            << "SherlockBag : " << sherlockBag->str() << endl
            << "WatsonBag : " << watsonBag->str() << endl;
    }
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
#pragma once
