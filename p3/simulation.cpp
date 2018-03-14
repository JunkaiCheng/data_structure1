//
//  simulation.cpp
//  p3
//
//  Created by Cheng on 2017/7/4.
//  Copyright © 2017年 Cheng. All rights reserved.
//

#include "simulation.h"
#include "world_type.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>



using namespace std;


bool initWorld(world_t &world, const string &speciesFile, const string &worldFile)
{
    ifstream iFile;
    iFile.open(speciesFile.c_str());
    ////////////////// check whether the file opens successfully
    if (!iFile)
        throw speciesFile;
    ///////////////// check whether the number of species not larger than MAXSPECIES
    int l_c;
    char c_c;
    l_c=0;
    while(iFile.get(c_c))
    {
        if (c_c=='\n')
            l_c++;
    }
    
    l_c=l_c-1;
    
    if (l_c>MAXSPECIES)
    {
        error4 e4;
        e4.val=MAXSPECIES;
        throw e4;
    }
    iFile.close();
////////////////////////////////
    iFile.open(speciesFile.c_str());
    string dir;
    // the name of the directory storing program files
    getline(iFile, dir);
    string sp[MAXSPECIES];
    //the name of species
    unsigned int s=0;
    //the number of species
    while(getline(iFile, sp[s]))
        s=s+1;
    iFile.close();
    unsigned int t=0;
//    istringstream iStream;
    string instruction[MAXPROGRAM];
    string opc_s;
    opcode_t opc=HOP;
    unsigned int a;
    instruction_t inst[MAXPROGRAM];
    species_t species[MAXSPECIES];
    int i=0;
    int j=0;
    int p=0;
    for (i=0; i<s; i++)
    {
        t=0;
        iFile.open((dir+"/"+sp[i]).c_str());
        if (!iFile)
            throw (dir+"/"+sp[i]);
        int l_p;
        char c_p;
        l_p=0;
        while(iFile.get(c_p))
        {
            if (c_p=='\n')
                l_p++;
        }
        if (l_p>MAXPROGRAM)
        {
            error5 e5;
            e5.SPECIES_NAME=sp[i];
            throw e5;
        }
        
        iFile.close();
    }
    
    for (i=0;i<s;i++)
    {
        t=0;
        iFile.open((dir+"/"+sp[i]).c_str());
        while(getline(iFile, instruction[t]))
        {
            if (instruction[t].length()==1
                || instruction[t].length()==0) break;
            a=0;
            istringstream iStream;
            iStream.str("");
            iStream.str(instruction[t]);
            iStream >> opc_s >> a;
            if (opc_s=="hop")
                opc=HOP;
            else if (opc_s=="left")
                opc=LEFT;
            else if (opc_s=="right")
                opc=RIGHT;
            else if (opc_s=="infect")
                opc=INFECT;
            else if (opc_s=="ifempty")
                opc=IFEMPTY;
            else if (opc_s=="ifenemy")
                opc=IFENEMY;
            else if (opc_s=="ifsame")
                opc=IFSAME;
            else if (opc_s=="ifwall")
                opc=IFWALL;
            else if (opc_s=="go")
                opc=GO;
            else
            {
                error6 e6;
                e6.ui=opc_s;
                throw e6;
            }
            inst[t].op=opc;
            inst[t].address=a;
            t=t+1;
        }
        iFile.close();
        species[i].name=sp[i];
        species[i].programSize=t;
        for (p=0; p<t; p++)
            species[i].program[p]=inst[p];
//        cout << "k" << opName[species[i].program[0].op]<<endl;
    }
    
    
    
  ////////////////////////////////////////////////////////////
    iFile.open(worldFile.c_str());
    if (!iFile)
        throw worldFile;
    unsigned height;
    unsigned width;
    string temp;
    getline(iFile, temp);
    height = atoi(temp.c_str());
    if (height>MAXHEIGHT)
    {
        error_wh h;
        h.wh="height";
        throw h;
    }
    getline(iFile, temp);
    width = atoi(temp.c_str());
    if (width > MAXWIDTH)
    {
        error_wh w;
        w.wh="width";
        throw w;
    }
    string terrainH[MAXHEIGHT];
    for (i=0; i<height; i++)
    {
        getline(iFile, terrainH[i]);
    }
    
    string creature_s[10*MAXCREATURES];
    unsigned int c=0;
    //the number of creatures
    while(getline(iFile, creature_s[c]))
        c=c+1;
    iFile.close();
    
    if(c>MAXCREATURES)
    {
        error10 mc;
        throw mc;
    }

    string sp_of_c;
    string ini_dir;
    int ini_row;
    int ini_col;
    creature_t creature[MAXCREATURES];
    point_t loc;

    direction_t dirct;
    species_t *spt_of_c=NULL;
    bool ability[ABILITY_SIZE];
    ability[0]=0;
    ability[1]=0;

    for (i=0; i<c; i++)
    {
        istringstream iStream2;
        iStream2.str(creature_s[i]);
        iStream2 >> sp_of_c >> ini_dir >> ini_row >> ini_col;
        
        loc.r=ini_row;
        loc.c=ini_col;
        
        
        for (j=0; j<s; j++)
        {
            if (sp_of_c==species[j].name)
                spt_of_c=&species[j];
        }
        
        if (spt_of_c==NULL)
        {
            error_us us;
            us.usn=sp_of_c;
            throw us;
        }
        
        if (ini_dir==directName[0])
            dirct=EAST;
        else if (ini_dir==directName[1])
            dirct=SOUTH;
        else if (ini_dir==directName[2])
            dirct=WEST;
        else if (ini_dir==directName[3])
            dirct=NORTH;
        else
        {
            error_di wdi;
            wdi.di=ini_dir;
            throw wdi;
        }
        
        string ability_s;
        while (iStream2>>ability_s)
        {
            if (ability_s=="f") ability[0]=1;
            else if (ability_s=="a") ability[1]=1;
            else
            {
                error14 e14;
                e14.SPECIES=spt_of_c->name;
                e14.DIR=directName[dirct];
                e14.r=loc.r;
                e14.c=loc.c;
                e14.ab=ability_s;
                throw e14;
            }
            
        }
        

        
        
        creature[i].location=loc;
        creature[i].direction=dirct;
        creature[i].species=spt_of_c;
        creature[i].programID=1;
        for (p=0; p<2;p++)
        {
            creature[i].ability[p]=ability[p];
        }
        creature[i].hillActive=1;
        
        if (creature[i].location.r>=height ||creature[i].location.c<0 || creature[i].location.c>=width || creature[i].location.c<0)
        {
            error13 out_c;
            out_c.SPECIES=creature[i].species->name;
            out_c.DIR=directName[creature[i].direction];
            out_c.r=creature[i].location.r;
            out_c.c=creature[i].location.c;
            out_c.h=height;
            out_c.w=width;
            
            throw out_c;
        }
        
    }
    
    int ocp_loc [2];
    for (i=0;i<c-1;i++)
    {
        ocp_loc[0]=creature[i].location.r;
        ocp_loc[1]=creature[i].location.c;
        for (j=i+1; j<c; j++)
            if(creature[j].location.r==ocp_loc[0] && creature[j].location.c==ocp_loc[1])
            {
                error15 e15;
                e15.s1=creature[j].species->name;
                e15.d1=directName[creature[j].direction];
                e15.r=ocp_loc[0];
                e15.c=ocp_loc[1];
                e15.s2=creature[i].species->name;
                e15.d2=directName[creature[i].direction];
                throw e15;
            }
    }
    

    
//////////////////////////////////////////
    grid_t grid;
    int row,col;
    for (i=0;i<height;i++)
    {
        for (j=0; j<width;j++)
            grid.squares[i][j]=NULL;
    }
    for (i=0; i<c; i++)
    {
        row=creature[i].location.r;
        col=creature[i].location.c;
        grid.squares[row][col]=&creature[i];
    }

    char terrainS[MAXHEIGHT][MAXWIDTH];
    istringstream iss;
    for (i=0; i<height; i++)
    {
        iss.str(terrainH[i]);
        for(j=0; j<width; j++)
        {
            
            iss.get(terrainS[i][j]);
            if (terrainS[i][j]=='P')
                grid.terrain[i][j]=PLAIN;
            else if (terrainS[i][j]=='L')
                grid.terrain[i][j]=LAKE;
            else if (terrainS[i][j]=='F')
                grid.terrain[i][j]=FOREST;
            else if (terrainS[i][j]=='H')
                grid.terrain[i][j]=HILL;
            else
            {
                terrError te;
                te.ch=terrainS[i][j];
                te.r=i;
                te.c=j;
                throw te;
            }
            
        }
    }

    grid.height=height;
    grid.width=width;
    //////////////////////////////////////////////////
    
    for (i=0;i<c;i++)
    {
        if (creature[i].ability[0]==0 && grid.terrain[creature[i].location.r][creature[i].location.c]==LAKE)
        {
            error16 e16;
            e16.s=creature[i].species->name;
            e16.d=directName[creature[i].direction];
            e16.r=creature[i].location.r;
            e16.c=creature[i].location.c;
            throw e16;
        }
            
    }
    
    ////////////////////////////////////////////////
    
    for(i=0; i<c; i++)
    {
        if(creature[i].ability[0]==0 && grid.terrain[creature[i].location.r][creature[i].location.c]==HILL)
            creature[i].hillActive=0;
    }
    
    world.numSpecies=s;
    for (p=0; p<s; p++)
        world.species[p]=species[p];
    world.numCreatures=c;
    for (p=0; p<c; p++)
        world.creatures[p]=creature[p];
    world.grid=grid;
//    cout << grid.height<< grid.width;
    return 1;
 
}



void printGrid(const grid_t &grid)
{
    // MODIFIES: cout.
    //
    // EFFECTS: print a grid representation of the creature world.
    int i,j;
    for (i=0; i< grid.height; i++)
    {
        for (j=0; j< grid.width; j++)
        {
            if (grid.squares[i][j]==NULL)
                cout << "____ ";
            else cout << (grid.squares[i][j]->species->name)[0] <<(grid.squares[i][j]->species->name)[1] << '_' << directShortName[grid.squares[i][j]->direction] << ' ';
        }
        cout << endl;
    }
}


void simulateCreature_v(creature_t &creature, grid_t &grid,world_t &world)
{
    // REQUIRES: creature is inside the grid.
    //
    // MODIFIES: creature, grid.
    //
    // EFFECTS:Simulate one turn of "creature" and update the creature, the infected creature, and the grid if necessary. The creature programID is always updated.
    int i,j;
    if (creature.hillActive==0)
    {
        creature.hillActive=1;
        return;
    }
    cout << "Creature " ;
    cout << "(" <<creature.species->name << " " << directName[creature.direction] <<" " <<creature.location.r << " " << creature.location.c <<")";
    cout << " takes action:"<<endl;
    instruction_t ins;
    point_t ajP;
    grid.squares[creature.location.r][creature.location.c]=NULL;
    while (creature.species->program[creature.programID-1].op>3)
    {
        cout << "Instruction " << creature.programID<< ": " << opName[creature.species->program[creature.programID-1].op]<< " "<< creature.species->program[creature.programID-1].address<<endl;
        ins=getInstruction(creature);
        point_t ajP=adjacentPoint(creature.location, creature.direction);
        
//        if (ins.op==IFEMPTY)
//        {
//            if (ifInside(ajP, grid)&& grid.squares[ajP.r][ajP.c]==NULL )
//                creature.programID=ins.address;
//            else
//                creature.programID++;
//        }
//        else if (ins.op==IFENEMY)
//        {
//            if (ifInside(ajP,grid)&&grid.terrain[ajP.r][ajP.c]!=FOREST&& grid.squares[ajP.r][ajP.c]!=NULL && grid.squares[ajP.r][ajP.c]->species!=creature.species)
//                creature.programID=ins.address;
//            else
//                creature.programID++;
//        }
//        else if (ins.op==IFSAME)
//        {
//            if (ifInside(ajP,grid)&&grid.terrain[ajP.r][ajP.c]!=FOREST&& grid.squares[ajP.r][ajP.c]!=NULL && grid.squares[ajP.r][ajP.c]->species==creature.species)
//                creature.programID=ins.address;
//            else
//                creature.programID++;
//        }
        if (ins.op==IFEMPTY)
        {
//            if (ifInside(ajP,grid)&&grid.terrain[ajP.r][ajP.c]==FOREST)
//            {
//                creature.programID++;
//                continue;
//            }
            
            if (ifInside(ajP, grid)&& grid.squares[ajP.r][ajP.c]==NULL )
                creature.programID=ins.address;
            else
                creature.programID++;
            
        }
        else if (ins.op==IFENEMY)
        {
            if (ifInside(ajP,grid)&&grid.terrain[ajP.r][ajP.c]==FOREST)
            {
                creature.programID++;
                continue;
            }
            if (ifInside(ajP,grid)&& grid.squares[ajP.r][ajP.c]!=NULL && grid.squares[ajP.r][ajP.c]->species!=creature.species)
                creature.programID=ins.address;
            else
                creature.programID++;
        }
        else if (ins.op==IFSAME)
        {
            if (ifInside(ajP,grid)&&grid.terrain[ajP.r][ajP.c]==FOREST)
            {
                creature.programID++;
                continue;
            }
            if (ifInside(ajP,grid)&& grid.squares[ajP.r][ajP.c]!=NULL && grid.squares[ajP.r][ajP.c]->species==creature.species)
                creature.programID=ins.address;
            else
                creature.programID++;
        }
        else if (ins.op==IFWALL)
        {
            if (!ifInside(ajP, grid)|| (grid.terrain[ajP.r][ajP.c]==LAKE &&creature.ability[0]==0) )
                creature.programID=ins.address;
            else
                creature.programID++;
        }
        
        else if (ins.op==GO)
            creature.programID=ins.address;
        else
            creature.programID++;
        
    }
    
    //////////////////
    ins=getInstruction(creature);
    ajP=adjacentPoint(creature.location, creature.direction);
    cout << "Instruction " << creature.programID<< ": " << opName[creature.species->program[creature.programID-1].op]<<endl;
    if (ins.op==HOP)
    {
        if(!ifInside(ajP, grid)||(grid.terrain[ajP.r][ajP.c]==LAKE&&creature.ability[0]==0)||grid.squares[ajP.r][ajP.c]!=NULL)
            creature.location=creature.location;
        else creature.location=ajP;
    }
    else if (ins.op==LEFT)
    {
        creature.direction=leftFrom(creature.direction);
    }
    else if (ins.op==RIGHT)
    {
        creature.direction=rightFrom(creature.direction);
    }
    else if (ins.op==INFECT)
    {
        if (creature.ability[1]==0)
        {
            if (ifInside(ajP, grid)&& grid.squares[ajP.r][ajP.c]!=NULL && grid.squares[ajP.r][ajP.c]->species!=creature.species && grid.terrain[ajP.r][ajP.c]!=FOREST)
            {
                grid.squares[ajP.r][ajP.c]->species=creature.species;
                grid.squares[ajP.r][ajP.c]->programID=1;
                world.grid=grid;
                for (i=0;i<world.numCreatures;i++)
                {
                    if (world.creatures[i].location.r==ajP.r && world.creatures[i].location.c==ajP.c)
                        world.creatures[i].species=creature.species;
                }
            }
        }
        else
        {
            while(ifInside(ajP, grid))
            {
//                if (grid.squares[ajP.r][ajP.c]!=NULL && grid.squares[ajP.r][ajP.c]->species==creature.species)
//                    break;
                if (grid.squares[ajP.r][ajP.c]!=NULL && grid.squares[ajP.r][ajP.c]->species!=creature.species)
                {
                    grid.squares[ajP.r][ajP.c]->species=creature.species;
                    grid.squares[ajP.r][ajP.c]->programID=1;
                    world.grid=grid;
                    for (i=0;i<world.numCreatures;i++)
                    {
                        if (world.creatures[i].location.r==ajP.r && world.creatures[i].location.c==ajP.c)
                            world.creatures[i].species=creature.species;
                    }
                    break;
                }
                ajP=adjacentPoint(ajP, creature.direction);
            }
        }
    }
    
    creature.programID++;
    
    
    grid.squares[creature.location.r][creature.location.c]=&creature;
    
    if(creature.ability[0]==0 && grid.terrain[creature.location.r][creature.location.c]==HILL)
        creature.hillActive=0;
    
    /////////////
//    cout << creature.location.r << " " << creature.location.c << endl;
    /////////////
    
    printGrid(grid);
    
}


void simulateCreature_c(creature_t &creature, grid_t &grid,world_t &world)
{
    // REQUIRES: creature is inside the grid.
    //
    // MODIFIES: creature, grid.
    //
    // EFFECTS:Simulate one turn of "creature" and update the creature, the infected creature, and the grid if necessary. The creature programID is always updated.
    int i,j;
    if (creature.hillActive==0)
    {
        creature.hillActive=1;
        return;
    }
    instruction_t ins;
    point_t ajP;
    grid.squares[creature.location.r][creature.location.c]=NULL;
    while (creature.species->program[creature.programID-1].op>3)
    {
        ins=getInstruction(creature);
        point_t ajP=adjacentPoint(creature.location, creature.direction);
        
        if (ins.op==IFEMPTY)
        {
//            if (ifInside(ajP,grid)&&grid.terrain[ajP.r][ajP.c]==FOREST)
//            {
//                creature.programID++;
//                continue;
//            }
            
            if (ifInside(ajP, grid)&& grid.squares[ajP.r][ajP.c]==NULL )
                creature.programID=ins.address;
            else
                creature.programID++;
            
        }
        else if (ins.op==IFENEMY)
        {
            if (ifInside(ajP,grid)&&grid.terrain[ajP.r][ajP.c]==FOREST)
            {
                creature.programID++;
                continue;
            }
            if (ifInside(ajP,grid)&& grid.squares[ajP.r][ajP.c]!=NULL && grid.squares[ajP.r][ajP.c]->species!=creature.species)
                creature.programID=ins.address;
            else
                creature.programID++;
        }
        else if (ins.op==IFSAME)
        {
            if (ifInside(ajP,grid)&&grid.terrain[ajP.r][ajP.c]==FOREST)
            {
                creature.programID++;
                continue;
            }
            if (ifInside(ajP,grid)&& grid.squares[ajP.r][ajP.c]!=NULL && grid.squares[ajP.r][ajP.c]->species==creature.species)
                creature.programID=ins.address;
            else
                creature.programID++;
        }
        else if (ins.op==IFWALL)
        {
            if (!ifInside(ajP, grid)|| (grid.terrain[ajP.r][ajP.c]==LAKE &&creature.ability[0]==0) )
                creature.programID=ins.address;
            else
                creature.programID++;
        }
        
        else if (ins.op==GO)
            creature.programID=ins.address;
        else
            creature.programID++;
        
        
    }
    
    //////////////////
    ins=getInstruction(creature);
    ajP=adjacentPoint(creature.location, creature.direction);
    cout << "Creature " ;
    cout << "(" <<creature.species->name << " " << directName[creature.direction] <<" " <<creature.location.r << " " << creature.location.c <<")";
    cout << " takes action: " ;
    
    
    cout << opName[creature.species->program[creature.programID-1].op];
    
    cout <<endl;
    if (ins.op==HOP)
    {
        if(!ifInside(ajP, grid)||(grid.terrain[ajP.r][ajP.c]==LAKE&&creature.ability[0]==0)||grid.squares[ajP.r][ajP.c]!=NULL)
            creature.location=creature.location;
        else creature.location=ajP;
    }
    else if (ins.op==LEFT)
    {
        creature.direction=leftFrom(creature.direction);
    }
    else if (ins.op==RIGHT)
    {
        creature.direction=rightFrom(creature.direction);
    }
    else if (ins.op==INFECT)
    {
        if (creature.ability[1]==0)
        {
            if (ifInside(ajP, grid)&& grid.squares[ajP.r][ajP.c]!=NULL && grid.squares[ajP.r][ajP.c]->species!=creature.species && grid.terrain[ajP.r][ajP.c]!=FOREST)
            {
                grid.squares[ajP.r][ajP.c]->species=creature.species;
                grid.squares[ajP.r][ajP.c]->programID=1;
                world.grid=grid;
                for (i=0;i<world.numCreatures;i++)
                {
                    if (world.creatures[i].location.r==ajP.r && world.creatures[i].location.c==ajP.c)
                        world.creatures[i].species=creature.species;
                }
            }
        }
        else
        {
            while(ifInside(ajP, grid))
            {
//                if (grid.squares[ajP.r][ajP.c]!=NULL && grid.squares[ajP.r][ajP.c]->species==creature.species)
//                    break;
                if (grid.squares[ajP.r][ajP.c]!=NULL && grid.squares[ajP.r][ajP.c]->species!=creature.species)
                {
                    grid.squares[ajP.r][ajP.c]->species=creature.species;
                    grid.squares[ajP.r][ajP.c]->programID=1;
                    world.grid=grid;
                    for (i=0;i<world.numCreatures;i++)
                    {
                        if (world.creatures[i].location.r==ajP.r && world.creatures[i].location.c==ajP.c)
                            world.creatures[i].species=creature.species;
                    }
                    break;
                }
                ajP=adjacentPoint(ajP, creature.direction);
            }
        }
    }
    
    creature.programID++;

    
    grid.squares[creature.location.r][creature.location.c]=&creature;
    
    if(creature.ability[0]==0 && grid.terrain[creature.location.r][creature.location.c]==HILL)
        creature.hillActive=0;
    
}


point_t adjacentPoint(point_t pt, direction_t dir)
{
    point_t p_out= pt;
    if (dir==NORTH)
        p_out.r=pt.r-1;
    if (dir==SOUTH)
        p_out.r=pt.r+1;
    if (dir==WEST)
        p_out.c=pt.c-1;
    if (dir==EAST)
        p_out.c=pt.c+1;
    return p_out;
    
}
// EFFECTS: Returns a point that results from moving one square in the direction "dir" from the point "pt".



direction_t leftFrom(direction_t dir)
{
// EFFECTS:Returns the direction that results from turning left from the given direction "dir".
    direction_t d_out=dir;
    if (dir==EAST)
        d_out=NORTH;
    if (dir==SOUTH)
        d_out=EAST;
    if (dir==WEST)
        d_out=SOUTH;
    if (dir==NORTH)
        d_out=WEST;
    return d_out;
    
}




direction_t rightFrom(direction_t dir)
{
    direction_t d_out=dir;
    if (dir==EAST)
        d_out=SOUTH;
    if (dir==SOUTH)
        d_out=WEST;
    if (dir==WEST)
        d_out=NORTH;
    if (dir==NORTH)
        d_out=EAST;
    return d_out;
}
// EFFECTS:Returns the direction that results from turning right from the given direction "dir".



instruction_t getInstruction(const creature_t &creature)
// EFFECTS: Returns the current instruction of "creature".
{
    species_t *sp;
    sp=creature.species;
    int n=creature.programID-1;
    return sp->program[n];
}


creature_t *getCreature(const grid_t &grid, point_t location)
// REQUIRES: location is inside the grid.
//
// EFFECTS: Returns a pointer to the creature at "location" in "grid".
{
    creature_t *c_out;
    c_out=grid.squares[location.r][location.c];
    return c_out;
}

////string creature_info(creature_t creature)
////{
////    string s=creature.species->name;
////    string d;
////    int r;
////    int c;
//////    s=creature.species->name;
////    d=directName[creature.direction];
////    r=creature.location.r;
////    c=creature.location.c;
////    string outs;
//////    cout << "s=" << s << endl;
//////    cout << "d=" << d << endl;
//////    cout << "r=" << r << endl;
//////    cout << "c=" << c << endl;
////    outs="("+s+" "+d+" "+to_string(r)+" "+to_string(c)+")";
////    return outs;
////    
//}



bool ifInside(const point_t &p, const grid_t &grid)
{
    if (((p.r>=grid.height)||(p.r<0))||(p.c>=grid.width)||(p.c<0))
        return 0;
    else return 1;
}







