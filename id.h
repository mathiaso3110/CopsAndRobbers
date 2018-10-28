#ifndef ID
#define ID
#include <iostream>
#include <cmath>
#include "objects.h"
using namespace std;

bool isFire(Fire_obj fire[N][N]) {
	for (int i=0;i<N;i++) {
		for (int j=0;j<N;j++) {
			if (fire[i][j].state()) {return true;}
		}
	}
	return false;
}

void fill_primes(int primes[N][N]) {
	int i = 0; int j = 0; int l = 2;
	bool isPrime;
	while (i<N && j<N) {
		isPrime = true;
		for (int k=2;k<=((int) sqrt(l))+1;k++) {
			if (l%k==0 && !(l==k)) {isPrime=false; break;}
		}
		if (isPrime) {
			primes[i][j] = l;
			if (j==N-1) {i++;j=0;}
			else {j++;}
		}
		l++;
	}
}

void rotate90(int* x, int* y) {
	// Counter-clockwise
	float _x = *x; float _y = *y;

	float middle = float (N-1)/2;
	_x -= middle; _y -= middle;

	// y' = y*cos(a) + x*sin(a), x' = - y*sin(a) + x*cos(a)
	float old_x = _x;
	_x = -_y;
	_y = old_x;

	_x += middle;
	_y += middle;

	*x = _x;
	*y = _y;
}

void mirror(int* x) {
	*x = N - 1 - *x;
}

void get_id(Cop cops[amountOfCops], Fire_obj fire[N][N], int primes[N][N], unsigned long long* cop_id, unsigned long long* fire_id) {
	// COPS
	unsigned long long id_num = 1;
	unsigned long long temp_id_num = 1;
	int rotations = 0;
	bool mirrorFire = false;

	// Initial position of the cops
	for (int i=0;i<amountOfCops;i++) {id_num *= primes[cops[i].x][cops[i].y];}

	// Rotations
	for (int i=0, j=0;j<(amountOfCops)*3;j++) {
		i = j % (amountOfCops);
		rotate90(&cops[i].x, &cops[i].y);
		temp_id_num *= primes[cops[i].x][cops[i].y];
		// If there are no more cops
		if (i == amountOfCops-1) {
			if (temp_id_num < id_num) {id_num = temp_id_num;rotations=ceil(j/((int) amountOfCops))+1;mirrorFire=false;}
			temp_id_num = 1;
		}
	}

	// Turn it back to initial position
	for (int i=0;i<amountOfCops;i++) {
		rotate90(&cops[i].x, &cops[i].y);
	}

	// Mirroring
	for (int i=0;i<amountOfCops;i++) {
		mirror(&cops[i].x);
		temp_id_num *= primes[cops[i].x][cops[i].y];
	}
	temp_id_num = 1;

	// Rotations (after mirroring)
	for (int i=0, j=0;j<(amountOfCops)*3;j++) {
		i = j % (amountOfCops);
		rotate90(&cops[i].x, &cops[i].y);
		temp_id_num *= primes[cops[i].x][cops[i].y];
		// If there are no more cops, check if the prime is less than the current and reset temp id num
		if (i == amountOfCops-1) {
			if (temp_id_num < id_num) {id_num = temp_id_num;rotations=ceil(j/((int) amountOfCops))+1;mirrorFire=true;}
			temp_id_num = 1;
		}
	}

	// Turn it back to initial position
	for (int i=0;i<amountOfCops;i++) {
		rotate90(&cops[i].x, &cops[i].y);
	}
	for (int i=0;i<amountOfCops;i++) {mirror(&cops[i].x);}
	*cop_id = id_num;

	// FIRE
	id_num = 1;
	for (int i=0;i<N;i++) {
		for (int j=0;j<N;j++) {
			// Rotate i and j
			int _i = i; int _j = j;
			if (mirrorFire) {mirror(&_i);}
			for (int l=0;l<rotations;l++) {rotate90(&_i, &_j);}
			if (fire[i][j].state()) {
				id_num *= primes[(int) _i][(int)_j];
			}
		}
	}
	*fire_id = id_num;
}




#endif