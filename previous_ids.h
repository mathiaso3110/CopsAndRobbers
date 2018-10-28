#ifndef PRE_ID
#define PRE_ID
#include <iostream>
#include "objects.h"
using namespace std;


bool isSeen(vector<Position>& previous_positions, int cop_id, int fire_id) {
	for (auto position = previous_positions.begin(); position != previous_positions.end(); position++) {
		if (position->cop_id == cop_id) {
			for (auto pre_fire_id = position->fire_ids.begin(); pre_fire_id != position->fire_ids.end(); pre_fire_id++) {
				if (*pre_fire_id == fire_id) {
					return true;
				}
			}
			position->append_fire_id(fire_id);
			return false;
		}
	}
	Position a(cop_id);
	a.append_fire_id(fire_id);
	previous_positions.push_back(a);
	return false;
}



#endif