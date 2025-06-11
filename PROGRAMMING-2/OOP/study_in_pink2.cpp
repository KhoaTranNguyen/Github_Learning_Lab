// TODO:
// Chỉnh lại di chuyển của RobotC (gợi ý: thực hiện hàm getPrevPosition cho Criminal)
// Mô tả về các meet thay đổi (đã được confirm 90%)
// File study_in_pink2.h những phần trước "addition" là gốc của đề (không thay đổi)
// Chỉnh tên thuộc tính hp và exp của Sherlock và Watson
// Position có nạp chồng 2 hàm isEqual
// isStop kiểm tra vị trí Sherlock, Watson với Criminal và hp của Sherlock, Watson
// Hàm run chú ý chỉnh từ hàm run() gốc (vị trí gọi printResult và printStep)
// Hàm move của Sherlock và Watson khi exp == 0 sẽ không thực hiện gì
// NOTE:
// chú ý các phần addition nên sửa đổi để tránh đạo code
// nộp Bkel cần xóa đổi lại 2 hàm printResult và printStep gốc, xóa thuộc tính outputFile
#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

int Distance(const Position& pos1, const Position& pos2)
{
	return abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
}
//string getChallenge(int i, int j)
//{
//	int t = (i * 11 + j) % 4;
//	if (t == 0)
//	{
//		return "RobotS";
//	}
//	else if (t == 1)
//	{
//		return "RobotC";
//	}
//	else if (t == 2)
//	{
//		return "RobotSW";
//	}
//	else
//	{
//		return "all";
//	}
//};

///////////////////////////// 3.1: MapElement /////////////////////////////
MapElement::MapElement(ElementType in_type)
{
	this->type = in_type;
};

FakeWall::FakeWall(int in_req_exp) : MapElement(FAKE_WALL)
{
	this->req_exp = in_req_exp;
};
int FakeWall::getReqExp() const
{
	return req_exp;
};
MapElement::~MapElement() {}
ElementType MapElement::getType() const
{
	//cout << "entered gettype" << endl;
	return type;
};

///////////////////////////// 3.2: Map /////////////////////////////
Map::Map(int num_rows, int num_cols, int num_walls, Position* array_walls, int num_fake_walls, Position* array_fake_walls) : num_rows(num_rows), num_cols(num_cols)
{
	map = new MapElement * *[num_rows];
	for (int i = 0; i < num_rows; i++)
	{
		map[i] = new MapElement * [num_cols];
		for (int j = 0; j < num_cols; j++)
		{
			map[i][j] = new Path();
			for (int k = 0; k < num_fake_walls; k++)
			{
				if (array_fake_walls[k].getRow() == i && array_fake_walls[k].getCol() == j)
				{
					delete map[i][j];
					map[i][j] = new FakeWall((i * 257 + j * 139 + 89) % 900 + 1);
					//cout << "fake wall req exp " << (i * 257 + j * 139 + 89) % 900 + 1 << endl;
				}
			}
			for (int k = 0; k < num_walls; k++)
			{
				if (array_walls[k].getRow() == i && array_walls[k].getCol() == j)
				{
					delete map[i][j];
					map[i][j] = new Wall();
				}
			}

		}
	}
};
Map::~Map()
{
	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < num_cols; j++)
		{
			delete map[i][j];
		}
		delete[] map[i];
	}
	delete[] map;
}
int Map::getNumRows() const
{
	return num_rows;
};
int Map::getNumCols() const
{
	return num_cols;
};
bool Map::isValid(const Position& pos, MovingObject* mv_obj) const
{
	//cout << "entered isvalid" << endl;
	int r = pos.getRow();
	//cout << r << endl;
	int c = pos.getCol();
	//cout << c << endl;
	if (r < 0 || r >= num_rows || c < 0 || c >= num_cols)
	{
		//cout << "out of bound" << endl;
		return false;
	}
	//cout << "before gettype" << endl;
	ElementType type = map[pos.getRow()][pos.getCol()]->getType();
	//cout << "after gettype" << endl;
	if (type == WALL)
	{
		//cout << "wall" << endl;	
		return false;
	}
	else if (type == FAKE_WALL)
	{
		//cout << "fake wall" << endl;
		if (mv_obj->getName() == "Sherlock" || mv_obj->getName() == "Criminal")
		{
			//cout << "entered Sherlock or Criminal" << endl;
			return true;
		}
		else if (mv_obj->getName() == "Watson")
		{
			//cout << "entered Watson" << endl;
			if (dynamic_cast<Watson*>(mv_obj)->getExp() <= dynamic_cast<FakeWall*>(map[r][c])->getReqExp())
			{
				//cout << "entered exp" << endl;
				return false;
			}
		}

	}
	//cout << "end of isvalid" << endl;
	return true;
};

///////////////////////////// 3.3: Position /////////////////////////////
const Position Position::npos = Position(-1, -1);
Position::Position(int r, int c)
{
	this->r = r;
	this->c = c;
};
Position::Position(const string& str_pos)
{
	//cout << "entered position" << endl;
	this->r = stoi(str_pos.substr(1, str_pos.find(",") - 1));
	this->c = stoi(str_pos.substr(str_pos.find(",") + 1, str_pos.find(")") - str_pos.find(",")));
};
int Position::getRow() const
{
	//cout << "entered getrow" << endl;
	//cout << r << endl;
	return r;
};
int Position::getCol() const
{
	//cout << "entered getcol" << endl;
	//	cout << c << endl;
	return c;
};
void Position::setRow(int r)
{
	if (r >= 0)
		this->r = r;
};
void Position::setCol(int c)
{
	if (c >= 0)
		this->c = c;
};
string Position::str() const
{
	return "(" + to_string(r) + "," + to_string(c) + ")";
};

bool Position::isEqual(const Position& pos) const
{
	if (this->r == pos.getRow() && this->c == pos.getCol())
	{
		return true;
	}
	else
	{
		return false;
	}
};
bool Position::isEqual(int r, int c) const
{
	if (this->r == r && this->c == c)
	{
		return true;
	}
	else
	{
		return false;
	}
};

//const Position mpos(-1, -1);

///////////////////////////// 3.4: MovingObject /////////////////////////////
MovingObject::MovingObject(int index, const Position pos, Map* map, const string& name)
{
	this->index = index;
	this->pos = pos;
	this->map = map;
	this->name = name;
};
MovingObject::~MovingObject() {};

Position MovingObject::getCurrentPosition() const
{
	return this->pos;
};
Position MovingObject::getFuturePosition() const
{
	return this->fpos;
};

string MovingObject::str() const
{
	return "MovingObject[index=" + to_string(index) + ";pos=" + pos.str() + "]";
};
string MovingObject::getName() const
{
	return this->name;
};

///////////////////////////// 3.11.1: Character /////////////////////////////
Character::Character(int index, const Position& init_pos, Map* map, const string& name) : MovingObject(index, init_pos, map, name)
{
	this->index = index;
	this->pos = init_pos;
	this->map = map;
	this->name = name;
};
//Character::~Character() {};
//Position Character::getNextPosition()
//{
//	Position next_pos = pos;
//	if (count_moving >= moving_rule.length())
//	{
//		count_moving = 0;
//	}
//
//	switch (moving_rule[count_moving])
//	{
//	case 'U':
//		next_pos.setRow(next_pos.getRow() - 1);
//		break;
//	case 'D':
//		next_pos.setRow(next_pos.getRow() + 1);
//		break;
//	case 'L':
//		next_pos.setCol(next_pos.getCol() - 1);
//		break;
//	case 'R':
//		next_pos.setCol(next_pos.getCol() + 1);
//		break;
//	default:
//		break;
//	}
//	count_moving++;
//
//	if (map->isValid(next_pos, this))
//	{
//		future_step = next_pos;
//		return next_pos;
//	}
//	else
//	{
//		future_step = Position::npos;
//		return Position::npos;
//	}
//};
Position Character::getCurrentPosition() const
{
	return this->pos;
};
//Position Character::getFuturePosition()
//{
//	Position future_pos = future_step;
//	if (count_moving2 >= moving_rule.length())
//	{
//		count_moving2 = 0;
//	}
//
//	switch (moving_rule[count_moving2])
//	{
//	case 'U':
//		future_pos.setRow(future_pos.getRow() - 1);
//		break;
//	case 'D':
//		future_pos.setRow(future_pos.getRow() + 1);
//		break;
//	case 'L':
//		future_pos.setCol(future_pos.getCol() - 1);
//		break;
//	case 'R':
//		future_pos.setCol(future_pos.getCol() + 1);
//		break;
//	default:
//		break;
//	}
//	count_moving2++;
//	if (map->isValid(future_pos, this))
//	{
//		return future_pos;
//	}
//	else
//	{
//		return Position::npos;
//	}
//};
//void Character::move()
//{
//	if(this->exp == 0)
//		return;
//	Position next_pos = getNextPosition();
//	count_moving++;
//	if (!next_pos.isEqual(Position::npos))
//	{
//		pos = next_pos;
//	}
//
//};
void Character::setHp(int hp)
{
	if (hp < 0)
	{
		this->hp = 0;
	}
	else if (hp > 500)
	{
		this->hp = 500;
	}
	else
		this->hp = hp;
};
int Character::getHp() const
{
	return this->hp;
};
void Character::setExp(int exp)
{
	if (exp < 0)
	{
		this->exp = 0;
	}
	else if (exp > 900)
	{
		this->exp = 900;
	}
	else
		this->exp = exp;
};
int Character::getExp() const
{
	return this->exp;
};


///////////////////////////// 3.5: Sherlock /////////////////////////////
Sherlock::Sherlock(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp) : Character(index, init_pos, map, "Sherlock")
{
	this->moving_rule = moving_rule;
	this->hp = init_hp;
	this->exp = init_exp;
	//BaseBag* sherlockBag = new SherlockBag(this);
};
Position Sherlock::getNextPosition()
{
	Position next_pos = pos;
	char c = moving_rule[count_moving % moving_rule.length()];
	switch (c)
	{
	case 'U':
		next_pos.setRow(next_pos.getRow() - 1);
		break;
	case 'D':
		next_pos.setRow(next_pos.getRow() + 1);
		break;
	case 'L':
		next_pos.setCol(next_pos.getCol() - 1);
		break;
	case 'R':
		next_pos.setCol(next_pos.getCol() + 1);
		break;
	default:
		break;
	}
	if (map->isValid(next_pos, this))
	{
		return next_pos;
	}
	else
	{
		return Position::npos;
	}
};
void Sherlock::move()
{
	if (this->exp == 0)
		return;
	Position next_pos = getNextPosition();
	count_moving++;
	if (!next_pos.isEqual(Position::npos))
	{
		pos = next_pos;
	}

};
void Sherlock::setPos(Position pos)
{
	this->pos = pos;
};
//BaseBag* Sherlock::getBag() const
//{
//	return sherlockBag;
//};
string Sherlock::str() const
{
	return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
};

///////////////////////////// 3.6: Watson /////////////////////////////
Watson::Watson(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp) : Character(index, init_pos, map, "Watson")
{
	this->moving_rule = moving_rule;
	this->hp = init_hp;
	this->exp = init_exp;
	//BaseBag* watsonBag = new WatsonBag(this);
};
Position Watson::getNextPosition()
{
	Position next_pos = pos;
	char c = moving_rule[count_moving % moving_rule.length()];
	switch (c)
	{
	case 'U':
		next_pos.setRow(next_pos.getRow() - 1);
		break;
	case 'D':
		next_pos.setRow(next_pos.getRow() + 1);
		break;
	case 'L':
		next_pos.setCol(next_pos.getCol() - 1);
		break;
	case 'R':
		next_pos.setCol(next_pos.getCol() + 1);
		break;
	default:
		break;
	}
	if (map->isValid(next_pos, this))
	{
		return next_pos;
	}
	else
	{
		return Position::npos;
	}
};
void Watson::move()
{
	if (this->exp == 0)
		return;
	Position next_pos = getNextPosition();
	count_moving++;
	if (!next_pos.isEqual(Position::npos))
	{
		pos = next_pos;
	}
};
//BaseBag* Watson::getBag() const
//{
//	return watsonBag;
//};
string Watson::str() const
{
	return "Watson[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
};

///////////////////////////// 3.7: Criminal /////////////////////////////
Criminal::Criminal(int index, const Position& init_pos, Map* map, Sherlock* sherlock, Watson* watson) : Character(index, init_pos, map, "Criminal")
{
	this->sherlock = sherlock;
	this->watson = watson;
};
Position Criminal::getNextPosition()
{
	Position best_pos = pos;
	int dr[] = { -1, 0, 1, 0 };
	int dc[] = { 0, -1, 0, 1 };
	int best_dist = INT_MIN;
	for (int i = 0; i < 4; ++i)
	{
		Position next_pos = Position(pos.getRow() + dr[i], pos.getCol() + dc[i]);
		//cout << "next_pos" << next_pos.str() << endl;
		if (!map->isValid(next_pos, this)) continue;
		int dist_to_sherlock = abs(next_pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(next_pos.getCol() - sherlock->getCurrentPosition().getCol());
		int dist_to_watson = abs(next_pos.getRow() - watson->getCurrentPosition().getRow()) + abs(next_pos.getCol() - watson->getCurrentPosition().getCol());
		int total_dist = dist_to_sherlock + dist_to_watson;
		//cout << "total dist: " << total_dist << endl;
		if (total_dist > best_dist)
		{
			//cout << "best dist: " << best_dist << endl;
			best_dist = total_dist;
			best_pos = next_pos;
		}
		//cout<<best_dist<<endl;
		//cout<<best_pos.str()<<endl;
	}
	if (best_pos.isEqual(pos))
	{
		return Position::npos;
	}
	//cout << best_dist << endl;
	return best_pos;
};
void Criminal::move()
{
	Position next_pos = getNextPosition();
	if (!next_pos.isEqual(Position::npos)) {
		prev_pos = pos;
		pos = next_pos;
		step++;
	}
	else return;
};
int Criminal::getStep() const
{
	return step;
};
bool Criminal::canCreateRobot() const
{
	return (step % 3 == 0 && step > 0);
}
Position Criminal::getPreviousPosition() const
{
	return prev_pos;
};
string Criminal::str() const
{
	return "Criminal[index=" + to_string(index) + ";pos=" + pos.str() + "]";
};

///////////////////////////// 3.8: ArrayMovingObject /////////////////////////////
ArrayMovingObject::ArrayMovingObject(int capacity)
{
	this->capacity = capacity;
	count = 0;
	arr_mv_objs = new MovingObject * [capacity];
}
ArrayMovingObject::~ArrayMovingObject()
{
	//for(int i = 3; i< count; i++)
	//{
	//	delete arr_mv_objs[i];
	//}
	//if (arr_mv_objs != nullptr)
	//{
	//	delete[] arr_mv_objs;
	//	arr_mv_objs = nullptr;
	//}
	if (arr_mv_objs != nullptr)
		delete[] arr_mv_objs;
}
bool ArrayMovingObject::isFull() const
{
	if (count == capacity)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool ArrayMovingObject::add(MovingObject* mv_obj)
{
	if (isFull())
	{
		return false;
	}
	arr_mv_objs[count] = mv_obj;
	count++;
	return true;
};
int ArrayMovingObject::size() const
{
	return count;
};
MovingObject* ArrayMovingObject::get(int index) const
{
	if (index < 0 || index >= count)
	{
		return nullptr;
	}
	return arr_mv_objs[index];
}
string ArrayMovingObject::str() const
{
	string result = "ArrayMovingObject[count=" + to_string(count) + ";capacity=" + to_string(capacity) + ";";
	for (int i = 0; i < count; ++i) {
		if (i > 0) result += ";";
		result += arr_mv_objs[i]->str();
	}
	result += "]";
	return result;
};

///////////////////////////// 3.9: Configuration /////////////////////////////
Configuration::Configuration(const string& sa_tc_02_config)
{
	ifstream file(sa_tc_02_config);
	if (!file.is_open())
	{
		throw runtime_error("Cannot open configuration file.");
	}
	string line;

	for (int i = 0; i < 15 && !file.eof(); i++)
	{
		//getline(file,line);
		file >> line;
		if (line.find("MAP_NUM_ROWS") == 0)
		{
			map_num_rows = stoi(line.substr(line.find("=") + 1, line.length() - 1 - line.find("=")));
		}
		else if (line.find("MAP_NUM_COLS") == 0)
		{
			map_num_cols = stoi(line.substr(line.find("=") + 1, line.length() - 1 - line.find("=")));
		}
		else if (line.find("MAX_NUM_MOVING_OBJECTS") == 0)
		{
			max_num_moving_objects = stoi(line.substr(line.find("=") + 1, line.length() - 1 - line.find("=")));
		}
		else if (line.find("ARRAY_WALLS") == 0)
		{
			size_t found = line.find(",");
			if (found == string::npos)
				num_walls = 0;
			else
			{
				num_walls = 0;
				while (found != string::npos)
				{
					found = line.find(",", found + 1);
					num_walls++;
				}
			}
			if (num_walls == 0)
				continue;
			else
			{
				arr_walls = new Position[num_walls];
				for (int k = 0; k < num_walls; k++)
				{
					char c;
					int temp1, temp2;
					istringstream temp(line.substr(14 + k * 6, 3));
					temp >> temp1 >> c >> temp2;
					arr_walls[k] = Position(temp1, temp2);
				}
			}
		}
		else if (line.find("ARRAY_FAKE_WALLS") == 0)
		{
			size_t found = line.find(",");
			if (found == string::npos)
				num_fake_walls = 0;
			else
			{
				num_fake_walls = 0;
				while (found != string::npos)
				{
					found = line.find(",", found + 1);
					num_fake_walls++;
				}
			}
			if (num_fake_walls == 0)
				continue;
			else
			{
				arr_fake_walls = new Position[num_fake_walls];
				for (int k = 0; k < num_fake_walls; k++)
				{
					char c;
					int temp1, temp2;
					istringstream temp(line.substr(19 + k * 6, 3));
					temp >> temp1 >> c >> temp2;
					arr_fake_walls[k] = Position(temp1, temp2);
				}
			}
		}
		else if (line.find("SHERLOCK_MOVING_RULE") == 0)
		{
			sherlock_moving_rule = line.substr(line.find("=") + 1, line.length() - 1 - line.find("="));
		}
		else if (line.find("SHERLOCK_INIT_POS") == 0)
		{
			sherlock_init_pos = Position(line.substr(line.find("("), line.find(")") - line.find("(") + 1));
		}
		else if (line.find("SHERLOCK_INIT_HP") == 0)
		{
			sherlock_init_hp = stoi(line.substr(line.find("=") + 1, line.length() - 1 - line.find("=")));
		}
		else if (line.find("SHERLOCK_INIT_EXP") == 0)
		{
			sherlock_init_exp = stoi(line.substr(line.find("=") + 1, line.length() - 1 - line.find("=")));
		}
		else if (line.find("WATSON_MOVING_RULE") == 0)
		{
			watson_moving_rule = line.substr(line.find("=") + 1, line.length() - 1 - line.find("="));
		}
		else if (line.find("WATSON_INIT_POS") == 0)
		{
			watson_init_pos = Position(line.substr(line.find("("), line.find(")") - line.find("(") + 1));
		}
		else if (line.find("WATSON_INIT_HP") == 0)
		{
			watson_init_hp = stoi(line.substr(line.find("=") + 1, line.length() - 1 - line.find("=")));
		}
		else if (line.find("WATSON_INIT_EXP") == 0)
		{
			watson_init_exp = stoi(line.substr(line.find("=") + 1, line.length() - 1 - line.find("=")));
		}
		else if (line.find("CRIMINAL_INIT_POS") == 0)
		{
			criminal_init_pos = Position(line.substr(line.find("("), line.find(")") - line.find("(") + 1));
		}
		else if (line.find("NUM_STEPS") == 0)
		{
			num_steps = stoi(line.substr(line.find("=") + 1, line.length() - 1 - line.find("=")));
		}

	}
};
Configuration::~Configuration()
{
	if (arr_fake_walls != nullptr)
		delete[] arr_fake_walls;
	if (arr_walls != nullptr)
		delete[] arr_walls;
}

string Configuration::str() const
{
	string sth = "Configuration[\nMAP_NUM_ROWS=" + to_string(map_num_rows) + "\nMAP_NUM_COLS=" + to_string(map_num_cols) + "\nMAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) + "\nNUM_WALLS=" + to_string(num_walls);
	sth += "\nARRAY_WALLS=[";

	for (int i = 0; i < num_walls - 1; i++)
	{
		sth += arr_walls[i].str() + ";";
	}
	sth += arr_walls[num_walls - 1].str();
	sth += "]\nNUM_FAKE_WALLS=" + to_string(num_fake_walls);
	sth += "\nARRAY_FAKE_WALLS=[";
	for (int i = 0; i < num_fake_walls - 1; i++)
	{
		sth += arr_fake_walls[i].str() + ";";
	}
	sth += arr_fake_walls[num_fake_walls - 1].str();
	sth += "]\nSHERLOCK_MOVING_RULE=" + sherlock_moving_rule + "\nSHERLOCK_INIT_POS=" + sherlock_init_pos.str() + "\nSHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) + "\nSHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) + "\nWATSON_MOVING_RULE=" + watson_moving_rule + "\nWATSON_INIT_POS=" + watson_init_pos.str() + "\nWATSON_INIT_HP=" + to_string(watson_init_hp) + "\nWATSON_INIT_EXP=" + to_string(watson_init_exp) + "\nCRIMINAL_INIT_POS=" + criminal_init_pos.str() + "\nNUM_STEPS=" + to_string(num_steps) + "\n]";
	return sth;
}

///////////////////////////// 3.11.2: Robot /////////////////////////////
Robot::Robot(int index, const Position& init_pos, Map* map, Criminal* criminal, const string& name) : MovingObject(index, init_pos, map, "Robot")
{
	this->index = index;
	this->pos = init_pos;
	this->map = map;
	this->name = name;
	this->criminal = criminal;
	int cardinal = pos.getRow() * pos.getCol();
	int t = (pos.getRow() * 11 + pos.getCol()) % 4;
	while (cardinal > 9)
	{
		cardinal = cardinal / 10 + cardinal % 10;
	}
	if (0 <= cardinal && cardinal <= 1)
	{
		tempItem = new MagicBook();
	}
	else if (2 <= cardinal && cardinal <= 3)
	{
		tempItem = new EnergyDrink();
	}
	else if (4 <= cardinal && cardinal <= 5)
	{
		tempItem = new FirstAid();
	}
	else if (6 <= cardinal && cardinal <= 7)
	{
		tempItem = new ExcemptionCard();
	}
	else if (8 <= cardinal && cardinal <= 9)
	{
		tempItem = new PassingCard(t);
	}
	else
		tempItem = nullptr;
	//cout<<tempItem->str()<<endl;
};
BaseItem* Robot::getItem() const
{
	 //cout<<"co item chua?"<<endl;
	 //cout << tempItem->str() << endl;
	return tempItem;
};

RobotType Robot::getRobotType() const
{
	return robot_type;
};
Robot::~Robot() {
	if (tempItem != nullptr)
		delete tempItem;
}

///////////////////////////// 3.10.1: RobotC /////////////////////////////
RobotC::RobotC(int index, const Position& init_pos, Map* map, Criminal* criminal) : Robot(index, init_pos, map, criminal, "RobotC")
{
};
Position RobotC::getNextPosition()
{
	return criminal->getPreviousPosition();
};
void RobotC::move()
{
	Position next_pos = getNextPosition();
	if (!next_pos.isEqual(Position::npos))
		pos = next_pos;
};
int RobotC::getDistance(Sherlock* sherlock) const
{
	return abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(pos.getCol() - sherlock->getCurrentPosition().getCol());
};
int RobotC::getDistance(Watson* watson) const
{
	return abs(pos.getRow() - watson->getCurrentPosition().getRow()) + abs(pos.getCol() - watson->getCurrentPosition().getCol());
};
string RobotC::str() const
{
	return "Robot[pos=" + pos.str() + ";type=" + "C" + ";dist=" + "" + "]";
};

///////////////////////////// 3.10.2: RobotS /////////////////////////////
RobotS::RobotS(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock) : Robot(index, init_pos, map, criminal, "RobotS")
{
	this->sherlock = sherlock;
};
Position RobotS::getNextPosition()
{
	Position best_pos = pos;
	int dr[] = { -1, 0, 1, 0 };
	int dc[] = { 0, 1, 0, -1 };
	int best_dist = INT_MAX;
	for (int i = 0; i < 4; ++i)
	{
		Position next_pos = Position(pos.getRow() + dr[i], pos.getCol() + dc[i]);
		if (!map->isValid(next_pos, this))
		{
			continue;
		}
		int dist_to_sherlock = abs(next_pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(next_pos.getCol() - sherlock->getCurrentPosition().getCol());
		if (dist_to_sherlock < best_dist)
		{
			best_dist = dist_to_sherlock;
			best_pos = next_pos;
		}
	}
	return best_pos;
};
void RobotS::move()
{
	Position next_pos = getNextPosition();
	if (!next_pos.isEqual(Position::npos))
		pos = next_pos;
};
int RobotS::getDistance() const
{
	return abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(pos.getCol() - sherlock->getCurrentPosition().getCol());
};
string RobotS::str() const
{
	return "Robot[pos=" + pos.str() + ";type=" + "S" + ";dist=" + to_string(getDistance()) + "]";
};

///////////////////////////// 3.10.3: RobotW /////////////////////////////
RobotW::RobotW(int index, const Position& init_pos, Map* map, Criminal* criminal, Watson* watson) : Robot(index, init_pos, map, criminal, "RobotW")
{
	this->watson = watson;
};
Position RobotW::getNextPosition()
{
	//Position best_pos = Position::npos;
	//int dr[] = { -1, 0, 1, 0 };
	//int dc[] = { 0, 1, 0, -1 };
	//int best_dist = INT_MAX;
	//for (int i = 0; i < 4; ++i)
	//{
	//	Position next_pos = Position(pos.getRow() + dr[i], pos.getCol() + dc[i]);
	//	if (!map->isValid(next_pos, this))
	//	{
	//		continue;
	//	}
	//	int dist_to_next_watson = abs(next_pos.getRow() - watson->getFuturePosition().getRow()) + abs(next_pos.getCol() - watson->getFuturePosition().getCol());
	//	if (dist_to_next_watson < best_dist)
	//	{
	//		best_dist = dist_to_next_watson;
	//		best_pos = next_pos;
	//	}
	//}
	//return best_pos;
	bool flag = false;
	Position next[] = { Position(pos.getRow() - 1, pos.getCol()), Position(pos.getRow(), pos.getCol() + 1), Position(pos.getRow() + 1, pos.getCol()), Position(pos.getRow(), pos.getCol() - 1) };
	int min = SHRT_MAX, x = 0;
	for (int i = 0; i < 4; i++) {
		if (map->isValid(next[i], this)) {
			flag = true;
			int dis = Distance(next[i], watson->getCurrentPosition());
			if (min > dis) {
				min = dis;
				x = i;
			}
		}
	}
	if (flag) return next[x];
	else return Position::npos;
};
void RobotW::move()
{
	Position next_pos = getNextPosition();
	if (!next_pos.isEqual(Position::npos))
		pos = next_pos;
};
int RobotW::getDistance() const
{
	return abs(pos.getRow() - watson->getCurrentPosition().getRow()) + abs(pos.getCol() - watson->getCurrentPosition().getCol());
};
string RobotW::str() const
{
	return "Robot[pos=" + pos.str() + ";type=" + "W" + ";dist=" + to_string(getDistance()) + "]";
};

///////////////////////////// 3.10.4: RobotSW /////////////////////////////
RobotSW::RobotSW(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson) : Robot(index, init_pos, map, criminal, "RobotSW")
{
	this->sherlock = sherlock;
	this->watson = watson;
};
Position RobotSW::getNextPosition()
{
	Position best_pos = pos;
	int dr1[] = { -1, +0, +0, +0, +1, +1, +0, +0 };
	int dc1[] = { +0, +1, +1, +1, +0, +0, -1, -1 };
	int dr2[] = { -1, -1, +0, +1, +1, +0, +0, -1 };
	int dc2[] = { +0, +0, +1, +0, +0, -1, -1, +0 };
	int best_dist = INT_MAX;
	for (int i = 0; i < 8; ++i)
	{
		Position next_pos = Position(pos.getRow() + dr1[i] + dr2[i], pos.getCol() + dc1[i] + dc2[i]);
		if (!map->isValid(next_pos, this))
		{
			continue;
		}
		int dist_to_sherlock = abs(next_pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(next_pos.getCol() - sherlock->getCurrentPosition().getCol());
		int dist_to_watson = abs(next_pos.getRow() - watson->getCurrentPosition().getRow()) + abs(next_pos.getCol() - watson->getCurrentPosition().getCol());
		int total_dist = dist_to_sherlock + dist_to_watson;
		if (best_dist == -1 || total_dist < best_dist)
		{
			best_dist = total_dist;
			best_pos = next_pos;
		}
	}
	return best_pos;
};
void RobotSW::move()
{
		Position next_pos = getNextPosition();
		if (!next_pos.isEqual(Position::npos))
			pos = next_pos;
};
int RobotSW::getDistance() const
{
	return abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(pos.getCol() - sherlock->getCurrentPosition().getCol()) + abs(pos.getRow() - watson->getCurrentPosition().getRow()) + abs(pos.getCol() - watson->getCurrentPosition().getCol());
};
string RobotSW::str() const
{
	return "Robot[pos=" + pos.str() + ";type=" + "SW" + ";dist=" + to_string(getDistance()) + "]";
};

///////////////////////////// 3.11.3: BaseItem /////////////////////////////
BaseItem::BaseItem(ItemType item_type)
{
	this->item_type = item_type;
};
void BaseItem::setChallenge(string challenge)
{
	this->challenge = challenge;
};
//ItemType BaseItem::getItemType(int i, int j) const
//{
//	int cardinal = i * j;
//	while (cardinal > 9)
//	{
//		cardinal = cardinal / 10 + cardinal % 10;
//	}
//	if (0 <= cardinal && cardinal <= 1)
//		return MAGIC_BOOK;
//	else if (2 <= cardinal && cardinal <= 3)
//		return ENERGY_DRINK;
//	else if (4 <= cardinal && cardinal <= 5)
//		return FIRST_AID;
//	else if (6 <= cardinal && cardinal <= 7)
//		return EXCEMPTION_CARD;
//	else if (8 <= cardinal && cardinal <= 9)
//		return PASSING_CARD;
//};

///////////////////////////// 3.11.4: MagicBook /////////////////////////////
MagicBook::MagicBook() :BaseItem(MAGIC_BOOK)
{};
bool MagicBook::canUse(Character* obj, Robot* robot)
{
	if (obj->getName() != "Sherlock" && obj->getName() != "Watson")
		return false;
	if (obj->getExp() <= 350 && robot == nullptr)
	{
		return true;
	}
	return false;
};
void MagicBook::use(Character* obj, Robot* robot)
{
	//if (canUse(obj, robot))
	//{
	//	if (obj->getName() == "Sherlock")
	//	{
	//		dynamic_cast<Sherlock*>(obj)->setExp(ceil(obj->getExp() * 1.25));
	//	}
	//	if (obj->getName() == "Watson")
	//	{
	//		dynamic_cast<Watson*>(obj)->setExp(ceil(obj->getExp() * 1.25));
	//	}
	//}
	obj->setExp(ceil(obj->getExp() * 1.25));
};
ItemType MagicBook::getType() const
{
	return MAGIC_BOOK;
};
string MagicBook::str() const
{
	return "MagicBook";
};

///////////////////////////// 3.11.5: EnergyDrink /////////////////////////////
EnergyDrink::EnergyDrink() :BaseItem(ENERGY_DRINK)
{};
bool EnergyDrink::canUse(Character* obj, Robot* robot)
{
	if (obj->getName() != "Sherlock" && obj->getName() != "Watson") return false;

	if (obj->getHp() <= 100 && robot == nullptr)
	{
		return true;
	}
	return false;
};
void EnergyDrink::use(Character* obj, Robot* robot)
{
	//if (canUse(obj, robot))
	//{
	//	obj->setHp(obj->getHp() * 120 / 100);
	//}
	obj->setHp(ceil(obj->getHp() * 1.2));
};
ItemType EnergyDrink::getType() const
{
	return ENERGY_DRINK;
};
string EnergyDrink::str() const
{
	return "EnergyDrink";
};

///////////////////////////// 3.11.6: FirstAid /////////////////////////////
FirstAid::FirstAid() :BaseItem(FIRST_AID)
{};
bool FirstAid::canUse(Character* obj, Robot* robot)
{
	if (obj->getName() != "Sherlock" && obj->getName() != "Watson") return false;
	if (obj->getHp() <= 100 || obj->getExp() <= 350 && robot == nullptr)
	{
		return true;
	}
	return false;
};
void FirstAid::use(Character* obj, Robot* robot)
{
	if (canUse(obj, robot))
	{
		obj->setHp(ceil(obj->getHp() * 1.5));
	}
	//obj->setHp(ceil(obj->getHp() * 1.5));
};
ItemType FirstAid::getType() const
{
	return FIRST_AID;
};
string FirstAid::str() const
{
	return "FirstAid";
};

///////////////////////////// 3.11.7: ExcemptionCard /////////////////////////////
ExcemptionCard::ExcemptionCard() :BaseItem(EXCEMPTION_CARD)
{};
bool ExcemptionCard::canUse(Character* obj, Robot* robot)
{
	if (obj->getName() == "Sherlock" && obj->getHp() % 2 != 0 && robot != nullptr)
	{
		return true;
	}
	return false;
};
void ExcemptionCard::use(Character* obj, Robot* robot)
{
	obj->setExp(obj->getExp());
	obj->setHp(obj->getHp());
};
ItemType ExcemptionCard::getType() const
{
	return EXCEMPTION_CARD;
};
string ExcemptionCard::str() const
{
	return "ExcemptionCard";
};

///////////////////////////// 3.11.8: PassingCard /////////////////////////////
bool PassingCard::canUse(Character* obj, Robot* robot)
{
	if (obj->getName() == "Watson" && obj->getHp() % 2 == 0 && robot != nullptr)
	{
		return true;
	}
	return false;
};
PassingCard::PassingCard(int t) :BaseItem(PASSING_CARD)
{
	switch (t)
	{
	case 0:
		challenge = "RobotS";
		break;
	case 1:
		challenge = "RobotC";
		break;
	case 2:
		challenge = "RobotSW";
		break;
	case 3:
		challenge = "all";
		break;
	}
};
PassingCard::PassingCard(string challenge) :BaseItem(PASSING_CARD)
{
	this->challenge = challenge;
};

//string PassingCard::getChallenge(int i, int j)
//{
//	int t = (i * 11 + j) % 4;
//	if (t == 0)
//	{
//		challenge == "RobotS";
//	}
//	else if (t == 1)
//	{
//		challenge == "RobotC";
//	}
//	else if (t == 2)
//	{
//		challenge == "RobotSW";
//	}
//	else if (t == 3)
//	{
//		challenge == "all";
//	}
//	return challenge;
//};
void PassingCard::use(Character* obj, Robot* robot)
{
	//if (canUse(obj, robot))
	//{
	if (challenge == "RobotS")
	{
		if (robot->getRobotType() == S)
		{
			return;
		}
	}
	if (challenge == "RobotC")
	{
		if (robot->getRobotType() == C)
		{
			return;
		}
	}
	if (challenge == "RobotSW")
	{
		if (robot->getRobotType() == SW)
		{
			return;
		}
	}
	if (challenge == "all")
	{
		return;
	}
		obj->setExp(obj->getExp() - 50);
	}
//};
ItemType PassingCard::getType() const
{
	return PASSING_CARD;
};
string PassingCard::str() const
{
	return "PassingCard";
};

////////////////////////////// Node /////////////////////////////
//Node::Node(BaseItem* item, Node* next = nullptr)
//{
//	this->item = item;
//	this->next = next;
//};
//Node::~Node()
//{
//	//if (item != nullptr)
//	//{
//	//	delete item;
//	//	item = nullptr;
//	//}
//};

///////////////////////////// 3.12.1: BaseBag /////////////////////////////
BaseBag::BaseBag(int maxItems) :maxItems(maxItems), head(nullptr)
{
	count = 0;
	//head = nullptr;
};
//Node* BaseBag::makeNode(BaseItem* item)
//{
//	Node* new_node = new Node(item);
//	new_node->item = item;
//	new_node->next = nullptr;
//	return new_node;
//}
void BaseBag::swap(Node* a, Node* b) {
	BaseItem* temp = a->item;
	a->item = b->item;
	b->item = temp;
};
bool BaseBag::canInsert() const
{
	return count < maxItems;
};
bool BaseBag::insert(BaseItem* item)
{
	//if (!canInsert())
	//{
	//	return false;
	//}
	if (count == maxItems) return false;
	Node* tmp = new Node(item);
	if (count == 0)
	{
		head = tmp;
	}
	else
	{
		tmp->next = head;
		head = tmp;
	}
	count++;
	return true;
};

//BaseItem* BaseBag::get()
//{
//	if (head == nullptr)
//	{
//		return nullptr;
//	}
//	//Find the first node that can be used
//	Node* previous = nullptr;
//	Node* current = head;
//	while (current && !current->item->canUse(obj, nullptr))
//	{
//		previous = current;
//		current = current->next;
//	}
//	if (!current)
//		return nullptr;
//	//Swap the first node with the current node
//	if (previous)
//	{
//		Node* temp = head->next;
//		head->next = current->next;
//		current->next = temp;
//		previous->next = head;
//		head = current;
//		delete temp;
//		count--;
//	}
//	//Delete the first node
//	if (head != nullptr)
//	{
//		BaseItem* item = head->item;
//		head = head->next;
//		return item;
//	}
//	return nullptr;
//};
//BaseItem* BaseBag::get(ItemType itemType)
//{
//	if (head == nullptr)
//	{
//		return nullptr;
//	}
//	Node* previous = nullptr;
//	Node* current = head;
//	while (current && current->item->getType() != itemType)
//	{
//		previous = current;
//		current = current->next;
//	}
//	if (!current)
//	{
//		return nullptr;
//	}
//	else if (previous)
//	{
//		Node* temp = head->next;
//		head->next = current->next;
//		current->next = temp;
//		previous->next = head;
//		head = current;
//		delete temp;
//		count--;
//	}
//	if (head != nullptr)
//	{
//		BaseItem* item = head->item;
//		head = head->next;
//		return item;
//	}
//	return nullptr;
//};
bool BaseBag::search(ItemType itemType) const
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->item->getType() == itemType)
		{
			return true;
		}
		current = current->next;
	}
	return false;
};
BaseBag::~BaseBag()
{
	Node* current = head;
	for (int i = 0; i < count; i++)
	{
		Node* temp = current->next;
		delete current;
		current = temp;
	}
}
bool BaseBag::isFull()
{
	return count == maxItems;
}
string BaseBag::str() const
{
	//string result = "Bag[count=" + to_string(count) + ";";
	//Node* current = head;
	//while (current != nullptr)
	//{
	//	result += ",";
	//	result += current->item->str();
	//	current = current->next;
	//}
	//result += "]";
	//return result;
	string result = "Bag[count=" + to_string(count) + ";";
	if (count == 0) return result += "]";
	Node* temp = head;
	for (int i = 0; i < count; ++i) {
		result += temp->item->str();
		temp = temp->next;
		if (temp == nullptr) break;
		result += ",";
	}
	result += "]";
	return result;
};

///////////////////////////// 3.12.2: SherlockBag /////////////////////////////
SherlockBag::SherlockBag(Sherlock* sherlock) : BaseBag(13)
{
	this->sherlock = sherlock;
};
BaseItem* SherlockBag::get()
{
	if (count == 0) return nullptr;
	Node* temp = head;
	for (int i = 0; i < count; ++i)
	{
		if (temp->item->canUse(sherlock, nullptr) && temp->item->getType() != EXCEMPTION_CARD && temp->item->getType() != PASSING_CARD)
		{
			swap(head, temp);
			BaseItem* result = head->item;
			Node* oldNode = head;
			head = head->next;
			delete oldNode;
			count--;
			return result;
		}
		temp = temp->next;
	}
	return nullptr;
}
BaseItem* SherlockBag::get(ItemType itemType)
{
	if (count == 0) return nullptr;
	Node* temp = head;
	for (int i = 0; i < count; ++i)
	{
		if (temp->item->getType() == itemType)
		{
			swap(head, temp);
			BaseItem* result = head->item;
			Node* oldNode = head;
			head = head->next;
			delete oldNode;
			count--;
			return result;
		}
		temp = temp->next;
	}
	return nullptr;
}

///////////////////////////// 3.12.3: WatsonBag /////////////////////////////
WatsonBag::WatsonBag(Watson* watson) : BaseBag(15)
{
	this->watson = watson;
};
BaseItem* WatsonBag::get()
{
	if (count == 0) return nullptr;
	Node* temp = head;
	for (int i = 0; i < count; ++i) {
		if (temp->item != nullptr) {
			if (temp->item->canUse(watson, nullptr) && temp->item->getType() != EXCEMPTION_CARD && temp->item->getType() != PASSING_CARD)
			{
				swap(head, temp);
				BaseItem* result = head->item;
				Node* oldNode = head;
				head = head->next;
				delete oldNode;
				count--;
				return result;
			}
			temp = temp->next;
		}

	}
	return nullptr;
}
BaseItem* WatsonBag::get(ItemType itemType)
{
	if (count == 0) return nullptr;
	Node* temp = head;
	for (int i = 0; i < count; ++i) {
		if (temp->item->getType() == itemType) {
			swap(head, temp);
			BaseItem* result = head->item;
			Node* oldNode = head;
			head = head->next;
			delete oldNode;
			count--;
			return result;
		}
		temp = temp->next;
	}
	return nullptr;
}


///////////////////////////// 3.13: StudyInPinkProgram /////////////////////////////
StudyPinkProgram::StudyPinkProgram(const string& config_file_path)
{
	config = new Configuration(config_file_path);
	map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);
	sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
	watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
	criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);
	arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
	arr_mv_objs->add(criminal);
	arr_mv_objs->add(sherlock);
	arr_mv_objs->add(watson);
	sherlockBag = new SherlockBag(sherlock);
	watsonBag = new WatsonBag(watson);
};
bool StudyPinkProgram::isStop() const
{
	return (sherlock->getHp() == 1 || watson->getHp() == 1 || sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()) || watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()));
};
void StudyPinkProgram::run(bool verbose, ofstream& OUTPUT)
{
	if (isStop())
	{
		printResult();
		return;
	}
	for (int istep = 0; istep < config->num_steps; ++istep)
	{
		//if (isStop())
		//{
		//	printStep(istep);
		//	break;
		//}
		for (int i = 0; i < arr_mv_objs->size(); ++i)
		{
			if (isStop())
			{
				printInfo(istep, i, OUTPUT);
				return;
			}
			//cout << "Sherlock:" << sherlock->getExp() << " " << sherlock->getHp() << endl;
			//cout << "Watson:" << watson->getExp() << " " << watson->getHp() << endl;
			arr_mv_objs->get(i)->move();
			//Check encounters & perform actions
			//MovingObject* mv_obj = arr_mv_objs->get(i);
//CRIMINAL encouters others
			if (arr_mv_objs->get(i)->getName() == "Criminal")
			{
				//Criminal encounters Sherlock
				if (criminal->getCurrentPosition().isEqual(sherlock->getCurrentPosition()) || criminal->getCurrentPosition().isEqual(watson->getCurrentPosition()))
				{
					printInfo(istep, i, OUTPUT);
					return;
				}
				//Create new robots
				int count_crim_step = criminal->getStep();
				if (count_crim_step == 3)
				{
					//cout<<"co vo day hong?";
					RobotC* robotC = new RobotC(3, criminal->getPreviousPosition(), map, criminal);
					//robotC->setItem(criminal->getPreviousPosition().getRow(), criminal->getPreviousPosition().getCol());
					arr_mv_objs->add(robotC);
					//BaseItem* item = robotC->getItem();
					//if (item->getType() == PASSING_CARD)
					//{
					//	item->setChallenge(getChallenge(criminal->getPreviousPosition().getRow(), criminal->getPreviousPosition().getCol()));
					//}
				}
				else if (count_crim_step > 3)
				{
					int dist_to_sherlock = Distance(criminal->getPreviousPosition(), sherlock->getCurrentPosition());
					int dist_to_watson = Distance(criminal->getPreviousPosition(), watson->getCurrentPosition());
					if (count_crim_step % 3 == 0)
					{
						if (dist_to_sherlock < dist_to_watson)
						{
							RobotS* robotS = new RobotS(arr_mv_objs->size(), criminal->getPreviousPosition(), map, this->criminal, sherlock);
							//robotS->setItem(criminal->getPreviousPosition().getRow(), criminal->getPreviousPosition().getCol());
							arr_mv_objs->add(robotS);
							//BaseItem* item = robotS->getItem();
							//if (item->getType() == PASSING_CARD)
							//{
							//	item->setChallenge(getChallenge(criminal->getPreviousPosition().getRow(), criminal->getPreviousPosition().getCol()));
							//}
						}
						else if (dist_to_sherlock > dist_to_watson)
						{
							RobotW* robotW = new RobotW(arr_mv_objs->size(), criminal->getPreviousPosition(), map, this->criminal, watson);
							//robotW->setItem(criminal->getPreviousPosition().getRow(), criminal->getPreviousPosition().getCol());
							arr_mv_objs->add(robotW);
							//BaseItem* item = robotW->getItem();
							//if (item->getType() == PASSING_CARD)
							//{
							//	item->setChallenge(getChallenge(criminal->getPreviousPosition().getRow(), criminal->getPreviousPosition().getCol()));
							//}
						}
						else if (dist_to_sherlock == dist_to_watson)
						{
							RobotSW* robotSW = new RobotSW(arr_mv_objs->size(), criminal->getPreviousPosition(), map, this->criminal, sherlock, watson);
							//robotSW->setItem(criminal->getPreviousPosition().getRow(), criminal->getPreviousPosition().getCol());
							arr_mv_objs->add(robotSW);
							//BaseItem* item = robotSW->getItem();
							//if (item->getType() == PASSING_CARD)
							//{
							//	item->setChallenge(getChallenge(criminal->getPreviousPosition().getRow(), criminal->getPreviousPosition().getCol()));
							//}
						}
					}
				}
			}
//SHERLOCK encounters others
			if (arr_mv_objs->get(i)->getName() == "Sherlock")
			{
				for (int k = 0; k < arr_mv_objs->size(); ++k)
				{
					if (sherlock->getCurrentPosition().isEqual(arr_mv_objs->get(k)->getCurrentPosition()) && arr_mv_objs->get(k)->getName() != "Sherlock")
					{
						//encounter WATSON
						if (arr_mv_objs->get(k)->getName() == "Watson")
						{
							if ((sherlockBag->search(PASSING_CARD) == true && watsonBag->search(EXCEMPTION_CARD) == true))
							{
								while (sherlockBag->search(PASSING_CARD) && !watsonBag->isFull())
								{
									watsonBag->insert(sherlockBag->get(PASSING_CARD));
								}
								while (watsonBag->search(EXCEMPTION_CARD) && !sherlockBag->isFull())
								{
									sherlockBag->insert(watsonBag->get(EXCEMPTION_CARD));
								}
							}
						}
						//encounter CRIMINAL
						else if (arr_mv_objs->get(k)->getName() == "Criminal")
						{
							printInfo(istep, i, OUTPUT);
							goto endLoop;
						}
						//encounter ROBOT
						else if (arr_mv_objs->get(k)->getName() == "RobotS")
						{
							BaseItem* item = nullptr;
							if (sherlockBag->search(EXCEMPTION_CARD) && sherlock->getHp() % 2 == 1)
							{
								item = sherlockBag->get(EXCEMPTION_CARD);
							}
							RobotS* robotS = dynamic_cast<RobotS*>(arr_mv_objs->get(k));
							if (item != nullptr)
							{
								item->use(sherlock, robotS);
								sherlockBag->insert(robotS->getItem());
							}
							else
							{
								if (sherlock->getExp() > 400)
								{
									sherlockBag->insert(robotS->getItem());
								}
								else
								{
									sherlock->setExp(ceil(sherlock->getExp() * 0.9));
								}
							}
							BaseItem* temp = sherlockBag->get();
							if (temp != NULL)
								temp->use(sherlock, NULL);
						}
						else if (arr_mv_objs->get(k)->getName() == "RobotW")
						{
							BaseItem* item = nullptr;
							if (sherlockBag->search(EXCEMPTION_CARD) && sherlock->getHp() % 2 == 1)
							{
								item = sherlockBag->get(EXCEMPTION_CARD);
							}
							RobotW* robotW = dynamic_cast<RobotW*>(arr_mv_objs->get(k));

							sherlockBag->insert(robotW->getItem());
							BaseItem* temp = sherlockBag->get();
							if (temp != NULL)
								temp->use(sherlock, NULL);
						}
						else if (arr_mv_objs->get(k)->getName() == "RobotSW")
						{
							BaseItem* item = nullptr;
							if (sherlockBag->search(EXCEMPTION_CARD) && sherlock->getHp() % 2 == 1)
							{
								item = sherlockBag->get(EXCEMPTION_CARD);
							}
							RobotSW* robotSW = dynamic_cast<RobotSW*>(arr_mv_objs->get(k));
							if (item != nullptr)
							{
								item->use(sherlock, robotSW);
								sherlockBag->insert(robotSW->getItem());
							}
							else
							{
								if (sherlock->getExp() > 300 && sherlock->getHp() > 335)
								{
									sherlockBag->insert(robotSW->getItem());
								}
								else
								{
									sherlock->setExp(ceil(sherlock->getExp() * 0.85));
									sherlock->setHp(ceil(sherlock->getHp() * 0.85));
								}
							}
							BaseItem* temp = sherlockBag->get();
							if (temp != NULL)
								temp->use(sherlock, NULL);
						}
						else if (arr_mv_objs->get(k)->getName() == "RobotC")
						{
							BaseItem* item = nullptr;
							if (sherlockBag->search(EXCEMPTION_CARD) && sherlock->getHp() % 2 == 1)
							{
								item = sherlockBag->get(EXCEMPTION_CARD);
							}
							RobotC* robotC = dynamic_cast<RobotC*>(arr_mv_objs->get(k));
							if (item != nullptr)
							{
								item->use(sherlock, robotC);
							}
							if (sherlock->getExp() > 500)
							{
								//Stop
								sherlock->setPos(criminal->getCurrentPosition());
								printInfo(istep, i, OUTPUT);
								goto endLoop;
							}
							else
							{
								sherlockBag->insert(robotC->getItem());
							}
							BaseItem* temp = sherlockBag->get();
							if (temp != NULL)
								temp->use(sherlock, NULL);
						}
					}
				}
			}
//WATSON encounters others
			if (arr_mv_objs->get(i)->getName() == "Watson")
			{
				for (int k = 0; k < arr_mv_objs->size(); ++k)
				{
					if (watson->getCurrentPosition().isEqual(arr_mv_objs->get(k)->getCurrentPosition()) && arr_mv_objs->get(k)->getName() != "Watson")
					{
						//encounter SHERLOCK
						if (arr_mv_objs->get(k)->getName() == "Sherlock")
						{
							if ((sherlockBag->search(PASSING_CARD) == true && watsonBag->search(EXCEMPTION_CARD) == true))
							{
								while (sherlockBag->search(PASSING_CARD) && !watsonBag->isFull())
								{
									watsonBag->insert(sherlockBag->get(PASSING_CARD));
								}
								while (watsonBag->search(EXCEMPTION_CARD) && !sherlockBag->isFull())
								{
									sherlockBag->insert(watsonBag->get(EXCEMPTION_CARD));
								}
							}
						}
						//encounter CRIMINAL
						else if (arr_mv_objs->get(k)->getName() == "Criminal")
						{
							printInfo(istep, i, OUTPUT);
							goto endLoop;
						}
						//encounter ROBOT
						else if (arr_mv_objs->get(k)->getName() == "RobotS")
						{
							BaseItem* item = nullptr;
							if (watsonBag->search(PASSING_CARD) && watson->getHp() % 2 == 0)
							{
								item = watsonBag->get(PASSING_CARD);
							}
							if (item != nullptr)
							{
								item->use(watson, dynamic_cast<RobotS*>(arr_mv_objs->get(k)));
							}
							BaseItem* temp = watsonBag->get();
							if (temp != NULL)
								temp->use(watson, NULL);
						}
						else if (arr_mv_objs->get(k)->getName() == "RobotW")
						{
							BaseItem* item = nullptr;
							if (watsonBag->search(PASSING_CARD) && watson->getHp() % 2 == 0)
							{
								item = watsonBag->get(PASSING_CARD);
							}
							RobotW* robotW = dynamic_cast<RobotW*>(arr_mv_objs->get(k));
							if (item != nullptr)
							{
								item->use(watson, robotW);
								watsonBag->insert(robotW->getItem());
							}
							else
							{
								if (watson->getHp() > 350)
								{
									watsonBag->insert(robotW->getItem());
								}
								else
								{
									watson->setHp(ceil(watson->getHp() * 0.95));
								}
							}
							BaseItem* temp = watsonBag->get();
							if (temp != NULL)
								temp->use(watson, NULL);
						}
						else if (arr_mv_objs->get(k)->getName() == "RobotSW")
						{
							BaseItem* item = nullptr;
							if (watsonBag->search(PASSING_CARD) && watson->getHp() % 2 == 0)
							{
								item = watsonBag->get(PASSING_CARD);
							}
							RobotSW* robotSW = dynamic_cast<RobotSW*>(arr_mv_objs->get(k));
							if (item != nullptr)
							{
								item->use(watson, robotSW);
								watsonBag->insert(robotSW->getItem());
							}
							else
							{
								if (watson->getHp() > 165 && watson->getExp() > 600)
								{
									watsonBag->insert(robotSW->getItem());
								}
								else
								{
									watson->setHp(ceil(watson->getHp() * 0.85));
									watson->setExp(ceil(watson->getExp() * 0.85));
								}
							}
							BaseItem* temp = watsonBag->get();
							if (temp != NULL)
								temp->use(watson, NULL);
						}
						
						else if (arr_mv_objs->get(k)->getName() == "RobotC")
						{
							BaseItem* item = nullptr;
							if (watsonBag->search(PASSING_CARD) && watson->getHp() % 2 == 0)
							{
								item = watsonBag->get(PASSING_CARD);
							}
							RobotC* robotC = dynamic_cast<RobotC*>(arr_mv_objs->get(k));
							if (item != nullptr)
							{
								item->use(watson, robotC);
							}
							watsonBag->insert(robotC->getItem());
							BaseItem* temp = watsonBag->get();
							if (temp != NULL)
								temp->use(watson, NULL);
						}
					}
				}

			}
//ROBOT encounters
			if (arr_mv_objs->get(i)->getName() == "RobotS" || arr_mv_objs->get(i)->getName() == "RobotSW" || arr_mv_objs->get(i)->getName() == "RobotW" || arr_mv_objs->get(i)->getName() == "RobotC")
			{
				Robot* robot = dynamic_cast<Robot*>(arr_mv_objs->get(i));
				for (int k = 0; k < arr_mv_objs->size(); ++k)
				{
					if (i == k) continue;
					//encounter SHERLOCK
					if (robot->getCurrentPosition().isEqual(arr_mv_objs->get(k)->getCurrentPosition()) && arr_mv_objs->get(k)->getName() == "Sherlock")
					{
						if (arr_mv_objs->get(i)->getName() == "RobotS")
						{
							BaseItem* item = nullptr;
							if (sherlockBag->search(EXCEMPTION_CARD) && sherlock->getHp() % 2 == 1)
							{
								item = sherlockBag->get(EXCEMPTION_CARD);
							}
							RobotS* robotS = dynamic_cast<RobotS*>(arr_mv_objs->get(i));
							if (item != nullptr)
							{
								item->use(sherlock, robotS);
								sherlockBag->insert(robotS->getItem());
							}
							else
							{
								if (sherlock->getExp() > 400)
								{
									sherlockBag->insert(robotS->getItem());
								}
								else
								{
									sherlock->setExp(ceil(sherlock->getExp() * 0.9));
								}
							}
							BaseItem* temp = sherlockBag->get();
							if (temp != NULL)
								temp->use(sherlock, NULL);
						}
						else if (arr_mv_objs->get(i)->getName() == "RobotW")
						{
							BaseItem* item = nullptr;
							if (sherlockBag->search(EXCEMPTION_CARD) && sherlock->getHp() % 2 == 1)
							{
								item = sherlockBag->get(EXCEMPTION_CARD);
							}
							RobotW* robotW = dynamic_cast<RobotW*>(arr_mv_objs->get(i));

							sherlockBag->insert(robotW->getItem());
							BaseItem* temp = sherlockBag->get();
							if (temp != NULL)
								temp->use(sherlock, NULL);
						}
						else if (arr_mv_objs->get(i)->getName() == "RobotSW")
						{
							BaseItem* item = nullptr;
							if (sherlockBag->search(EXCEMPTION_CARD) && sherlock->getHp() % 2 == 1)
							{
								item = sherlockBag->get(EXCEMPTION_CARD);
							}
							RobotSW* robotSW = dynamic_cast<RobotSW*>(arr_mv_objs->get(i));
							if (item != nullptr)
							{
								item->use(sherlock, robotSW);
								sherlockBag->insert(robotSW->getItem());
							}
							else
							{
								if (sherlock->getExp() > 300 && sherlock->getHp() > 335)
								{
									sherlockBag->insert(robotSW->getItem());
								}
								else
								{
									sherlock->setExp(ceil(sherlock->getExp() * 0.85));
									sherlock->setHp(ceil(sherlock->getHp() * 0.85));
								}
							}
							BaseItem* temp = sherlockBag->get();
							if (temp != NULL)
								temp->use(sherlock, NULL);
						}
						else if (arr_mv_objs->get(i)->getName() == "RobotC")
						{
							BaseItem* item = nullptr;
							if (sherlockBag->search(EXCEMPTION_CARD) && sherlock->getHp() % 2 == 1)
							{
								item = sherlockBag->get(EXCEMPTION_CARD);
							}
							Robot* robotC = dynamic_cast<RobotC*>(arr_mv_objs->get(i));
							if (item != nullptr)
							{
								item->use(sherlock, robotC);
							}
							if (sherlock->getExp() > 500)
							{
								//Stop
								sherlock->setPos(criminal->getCurrentPosition());
								printInfo(istep, i, OUTPUT);
								goto endLoop;
							}
							else
							{
								sherlockBag->insert(robotC->getItem());
							}
							BaseItem* temp = sherlockBag->get();
							if (temp != NULL)
								temp->use(sherlock, NULL);
						}
					}
					//encounter WATSON
					else if (robot->getCurrentPosition().isEqual(arr_mv_objs->get(k)->getCurrentPosition()) && arr_mv_objs->get(k)->getName() == "Watson")
					{
						if (arr_mv_objs->get(i)->getName() == "RobotS")
						{
							BaseItem* item = nullptr;
							if (watsonBag->search(PASSING_CARD) && watson->getHp() % 2 == 0)
							{
								item = watsonBag->get(PASSING_CARD);
							}
							if (item != nullptr)
							{
								item->use(watson, dynamic_cast<RobotS*>(arr_mv_objs->get(i)));
							}
							BaseItem* temp = watsonBag->get();
							if (temp != NULL)
								temp->use(watson, NULL);
						}
						else if (arr_mv_objs->get(i)->getName() == "RobotW")
						{
							BaseItem* item = nullptr;
							if (watsonBag->search(PASSING_CARD) && watson->getHp() % 2 == 0)
							{
								item = watsonBag->get(PASSING_CARD);
							}
							RobotW* robotW = dynamic_cast<RobotW*>(arr_mv_objs->get(i));
							if (item != nullptr)
							{
								item->use(watson, robotW);
								watsonBag->insert(robotW->getItem());
							}
							else
							{
								if (watson->getHp() > 350)
								{
									watsonBag->insert(robotW->getItem());
								}
								else
								{
									watson->setHp(ceil(watson->getHp() * 0.95));
								}
							}
							BaseItem* temp = watsonBag->get();
							if (temp != NULL)
								temp->use(watson, NULL);
						}
						else if (arr_mv_objs->get(i)->getName() == "RobotSW")
						{
							BaseItem* item = nullptr;
							if (watsonBag->search(PASSING_CARD) && watson->getHp() % 2 == 0)
							{
								item = watsonBag->get(PASSING_CARD);
							}
							RobotSW* robotSW = dynamic_cast<RobotSW*>(arr_mv_objs->get(i));
							if (item != nullptr)
							{
								item->use(watson, robotSW);
								watsonBag->insert(robotSW->getItem());
							}
							else
							{
								if (watson->getHp() > 165 && watson->getExp() > 600)
								{
									watsonBag->insert(robotSW->getItem());
								}
								else
								{
									watson->setHp(ceil(watson->getHp() * 0.85));
									watson->setExp(ceil(watson->getExp() * 0.85));
								}
							}
							BaseItem* temp = watsonBag->get();
							if (temp != NULL)
								temp->use(watson, NULL);
						}
						else if (arr_mv_objs->get(i)->getName() == "RobotC")
						{

							BaseItem* item = nullptr;
							if (watsonBag->search(PASSING_CARD) && watson->getHp() % 2 == 0)
							{
								item = watsonBag->get(PASSING_CARD);
							}
							RobotC* robotC = dynamic_cast<RobotC*>(arr_mv_objs->get(i));
							if (item != nullptr)
							{
								item->use(watson, robotC);
							}
							watsonBag->insert(robotC->getItem());
							BaseItem* temp = watsonBag->get();
							if (temp != NULL)
								temp->use(watson, NULL);
						}
					}
				}
			}
			if (isStop())
			{
				printInfo(istep, i, OUTPUT);
				goto endLoop;
			}

			if (verbose)
			{
				printInfo(istep, i, OUTPUT);
			}
		}
	}
endLoop:
	printResult();
};
StudyPinkProgram::~StudyPinkProgram()
{
	delete map;
	delete arr_mv_objs;
	delete sherlock;
	delete watson;
	delete criminal;
};


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////