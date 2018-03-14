//
//  simulation.hpp
//  p3
//
//  Created by Cheng on 2017/7/4.
//  Copyright © 2017年 Cheng. All rights reserved.
//

#ifndef simulation_hpp
#define simulation_hpp

#include <stdio.h>
#include "world_type.h"
bool initWorld(world_t &world, const string &speciesFile, const string &worldFile);
// MODIFIES: world
//
// // // //
//EFFECTS: Initialize "world" given the species summary file "speciesFile" and the world description file "worldFile". This initializes all the components of "world". Returns true if initialization is successful.


void printGrid(const grid_t &grid);
// MODIFIES: cout.
//
// EFFECTS: print a grid representation of the creature world.


void simulateCreature_v(creature_t &creature, grid_t &grid,world_t &world);
// REQUIRES: creature is inside the grid.
//
// MODIFIES: creature, grid, cout.
//
// EFFECTS:Simulate one turn of "creature" and update the creature, the infected creature, and the grid if necessary. The creature programID is always updated. The function also prints to the stdout the procedure. If verbose is true, it prints more information.

void simulateCreature_c(creature_t &creature, grid_t &grid,world_t &world);


point_t adjacentPoint(point_t pt, direction_t dir);
// EFFECTS: Returns a point that results from moving one square // in the direction "dir" from the point "pt".



direction_t leftFrom(direction_t dir);
// EFFECTS:Returns the direction that results from turning left from the given direction "dir".




direction_t rightFrom(direction_t dir);
// EFFECTS:Returns the direction that results from turning right from the given direction "dir".



instruction_t getInstruction(const creature_t &creature);
// EFFECTS: Returns the current instruction of "creature".


creature_t *getCreature(const grid_t &grid, point_t location);
// REQUIRES: location is inside the grid.
//
// EFFECTS: Returns a pointer to the creature at "location" in "grid".

struct terrError { char ch; int r; int c; };

struct error4 {int val;};

struct error5 {string SPECIES_NAME;};

struct error6 {string ui;};

struct error_wh {string wh;};

struct error_di {string di;};

struct error_us {string usn;};

struct error10 {};

struct error13 {string SPECIES; string DIR; int r; int c; int h; int w;};

struct error14 {string SPECIES; string DIR; int r; int c; string ab;};

struct error15
{
    string s1;
    string d1;
    string s2;
    string d2;
    int r;
    int c;
};

struct error16
{
    string s;
    string d;
    int r;
    int c;

};

//string creature_info(creature_t creature);

//void simulate_v(world_t &world, int round);
//
//void simulate_c(world_t &world, int round);
//
//void nextWorld(grid_t &grid, world_t &world);

bool ifInside(const point_t &p, const grid_t &grid);

#endif /* simulation_hpp */

