#include <iostream>
#include <typeinfo>
#include <string>
#include <chrono>
#define N 3
#define amountOfCops N
#include "objects.h"
#include "move.h"
#include "id.h"
#include "previous_ids.h"
using namespace std;

// Initializing the arrays
Fire_obj fire[N][N];
Cop cops[amountOfCops];
// Cop cops[amountOfCops];
vector<Position> previous_positions;
// Initial cops is used each time find_new_position is called recursivly (with new initial position)
Initial_cop_pos initial_cops[amountOfCops];
int primes[N][N];
unsigned long long cop_id; unsigned long long fire_id; 
bool solutionFound = false;
void find_new_position(int i);

void print(Fire_obj fire[N][N], Cop cops[amountOfCops]) {
	bool cop_pos = false;
	for (int y=N-1;y>=0;y--) {
		for (int x=0;x<N;x++) {
			for (int l=0;l<amountOfCops;l++) {
				if (cops[l].x==x&&cops[l].y==y) {
					cout << "x" << "  ";
					cop_pos = true;
					break;
				}
			}
			if (!cop_pos) {cout << fire[x][y].state() << "  ";}
			cop_pos=false;
		}
		cout << endl;
	}
	cout << endl;
}

void move_and_check() {
	move(fire, cops, initial_cops);
	if (!isFire(fire)) {solutionFound=true; print(fire, cops);}
	else {
		get_id(cops, fire, primes, &cop_id, &fire_id);
		
		if (!isSeen(previous_positions, cop_id, fire_id)) {
			find_new_position(0);
		}
	}
	revert_fire(fire);

}

void find_new_position(int i) {
	// Sets previous_cops
	if (!i) {
		copy_to(cops, initial_cops);
	}
	// NORTH
	if (!solutionFound) {
		if (cops[i].y+1<N) {
			cops[i].y += 1;
			if (i+1==amountOfCops) {
				move_and_check();
			}
			else {find_new_position(i+1);}
			cops[i].y -= 1;
		}
	}
	// South
	if (!solutionFound) {
		if (cops[i].y-1>=0) {
			cops[i].y -= 1;
			if (i+1==amountOfCops) {
				move_and_check();
			}
			else {find_new_position(i+1);}
			cops[i].y += 1;
		}
	}
	// EAST
	if (!solutionFound) {
		if (cops[i].x+1<N) {
			cops[i].x += 1;
			if (i+1==amountOfCops) {
				move_and_check();
			}
			else {find_new_position(i+1);}
			cops[i].x -= 1;
		}
	}
	// WEST
	if (!solutionFound) {
		if (cops[i].x-1>=0) {
			cops[i].x -= 1;
			if (i+1==amountOfCops) {
				move_and_check();
			}
			else {find_new_position(i+1);}
			cops[i].x += 1;
		}
	}
	// STAY
	if (!solutionFound) {
		if (i+1==amountOfCops) {
			move_and_check();
		}
		else {find_new_position(i+1);}
	}


	if (!i) {
		for (int k=0;k<amountOfCops;k++) {initial_cops[k].revert_coor();}
	}

	if (solutionFound && !i) {print(fire, cops);}
}

int main() {
	auto start = std::chrono::high_resolution_clock::now();
	set_cops_coordinates(cops);
	copy_to(cops, initial_cops);
	fill_initial_fire_array(fire, cops);
	fill_primes(primes);
	get_id(cops, fire, primes, &cop_id, &fire_id);
	isSeen(previous_positions, cop_id, fire_id);
	find_new_position(0);
	if (!solutionFound) {cout << "No solution found!" << endl;} else {cout << "Solution found!" << endl;}
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";
	return 0;
}



