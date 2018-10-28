#ifndef OBJECTS_H
#define OBJECTS_H
#include <stack>
#include <vector>
using namespace std;

class Fire_obj {
	stack<bool> stack;
	bool is_new;
public:
	void set_state(bool i) {stack.push(i);}
	void revert_state() {stack.pop();}
	bool state() {return stack.top();}
	void set_is_new(bool i) {is_new=i;}
	bool get_is_new() {return is_new;}
};

class Cop {
public:
	int x, y;
};

class Initial_cop_pos {
	stack<int> x;
	stack<int> y;
public:
	void append_coor(int _x, int _y) {x.push(_x);y.push(_y);}
	int get_x() {return x.top();}
	int get_y() {return y.top();}
	void revert_coor() {x.pop(); y.pop();}
};

class Position {
public:
	int cop_id;
	vector<int> fire_ids;
	Position(int cop_id_num) : cop_id(cop_id_num) { }
	void append_fire_id(int x) {fire_ids.push_back(x);}
};

#endif