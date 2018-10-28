#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include "objects.h"


void estinguish_fire(Fire_obj fire[N][N], Cop cops[amountOfCops]) {
	// Sets the places with cops to false
	for (int i=0; i<amountOfCops; i++) {
		fire[cops[i].x][cops[i].y].revert_state();
		fire[cops[i].x][cops[i].y].set_state(false);
	}
}

void fill_initial_fire_array(Fire_obj fire[N][N], Cop cops[amountOfCops]) {
	// Sets first item in fire array to true
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			fire[i][j].set_state(true);
		}
	}
	estinguish_fire(fire, cops);
}

void set_cops_coordinates(Cop cops[amountOfCops]) {
	for (int i=0; i<amountOfCops; i++) {
		cops[i].x = i;
		cops[i].y = 0;
	}
}

bool illegal_move(Cop cops[amountOfCops], Initial_cop_pos initial_cops[amountOfCops], int i, int j, int fire_i, int fire_j) {
	for (int h=0;h<amountOfCops;h++) {
		if (initial_cops[h].get_x()==i 
			&& initial_cops[h].get_y()==j
			&& cops[h].x==fire_i
			&& cops[h].y==fire_j)
			{return true;}
	}
	return false;
}

void copy_to(Cop cops[amountOfCops], Initial_cop_pos initial_cops[amountOfCops]) {
	for (int i=0;i<amountOfCops;i++) { 
		initial_cops[i].append_coor(cops[i].x, cops[i].y);
	}
}


void revert_fire(Fire_obj fire[N][N]) {
	for (int i=0;i<N;i++) {
		for (int j=0;j<N;j++) {
			fire[i][j].revert_state();
		}
	} 
}

void move(Fire_obj fire[N][N], Cop cops[amountOfCops], Initial_cop_pos initial_cops[amountOfCops]) {

	for (int i=0;i<N;i++) {
		for (int j=0;j<N;j++) {
			if (fire[i][j].state()) {fire[i][j].set_state(true);}
			else if (  (i+1<N && fire[i+1][j].state() && !fire[i+1][j].get_is_new() && !illegal_move(cops, initial_cops, i, j, i+1, j))
					|| (i-1>=0 && fire[i-1][j].state() && !fire[i-1][j].get_is_new() && !illegal_move(cops, initial_cops, i, j, i-1, j))
					|| (j+1<N && fire[i][j+1].state() && !fire[i][j+1].get_is_new() && !illegal_move(cops, initial_cops, i, j, i, j+1))
					|| (j-1>=0 && fire[i][j-1].state() && !fire[i][j-1].get_is_new() && !illegal_move(cops, initial_cops, i, j, i, j-1))) {
				fire[i][j].set_state(true);
				fire[i][j].set_is_new(true);
			} else {fire[i][j].set_state(false);}
		}
	}

	for (int i=0;i<N;i++) {for (int j=0;j<N;j++) {fire[i][j].set_is_new(false);}}

	estinguish_fire(fire, cops);
}





#endif