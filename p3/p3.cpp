//
//  main.cpp
//  p3
//
//  Created by Cheng on 2017/7/4.
//  Copyright © 2017年 Cheng. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

#include "world_type.h"
#include "simulation.h"

using namespace std;

int main(int argc, char * argv[]) {
    
    
    try
    {
        if (argc<4) throw "Error: Missing arguments!";
        // insert code here...
        string sf = argv[1];
        //name of species summery file
        string worldf = argv[2];
        //the program name of world description file
        int round = atoi(argv[3]);
        if (round <0) throw round;
        
        world_t world;
        initWorld(world, sf, worldf);
        cout << "Initial state" << endl;
        

        
        
        printGrid(world.grid);

        int i,j;
//
//        for (i=0;i<world.grid.height;i++)
//        {
//            for (j=0; j< world.grid.width;j++)
//                cout << terrainShortName[world.grid.terrain[i][j] ];
//            cout <<endl;
//        }
        
        
        
//        for (i=0; i<world.numSpecies; i++)
//        {
//            cout << world.species[i].name << endl;
//        }
//        
//        for (i=0; i<world.numCreatures;i++)
//        {
//            cout << world.creatures[i].species->name << endl;
//        }

//        if (argc==5)
//        {
//            string vc=argv[4];
//            if(vc=="v" || vc=="verbose")
//            {
//                for(i=1; i<=round; i++)
//                {
//                    cout << "Round "<< i << endl;
//                    for (j=0;j<world.numCreatures;j++)
//                    {
//                        cout << "Creature " << creature_info(world.creatures[j])<< " takes action:"<<endl;
//                        simulateCreature_v(world.creatures[j],world.grid);
//                    }
//                    
//                }
//            }
        if (argc==5)
        {
            string vc=argv[4];
            if(vc=="v" || vc=="verbose")
            {
                for(i=1; i<=round; i++)
                {
                    cout << "Round "<< i << endl;
                    for (j=0;j<world.numCreatures;j++)
                        simulateCreature_v(world.creatures[j],world.grid,world);
                }
            }
            else
                {
                    for(i=1; i<=round; i++)
                    {
                        cout<< "Round "<< i << endl;
                        for (j=0;j<world.numCreatures;j++)
                            simulateCreature_c(world.creatures[j],world.grid,world);
                        printGrid(world.grid);
                    }
                }

        }
        else
        {
            for(i=1; i<=round; i++)
            {
                cout<< "Round "<< i << endl;
                for (j=0;j<world.numCreatures;j++)
                    simulateCreature_c(world.creatures[j],world.grid,world);
                printGrid(world.grid);
            }
        }

        
        return 0;
    }
    
    catch (const char * &a)
    {
        cout<<a << endl;
        cout<<"Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]"<<endl;
    }
    
    catch (int round)
    {
        cout << "Error: Number of simulation rounds is negative!"<<endl;
    }

    catch (const string  &a)
    {
        cout << "Error: Cannot open file ";
        cout << a;
        cout << "!"<<endl;
    }
    
    catch (terrError te)
    {
        cout << "Error: Terrain square (";
        cout <<te.ch <<" ";
        cout <<te.r <<" ";
        cout << te.c;
        cout <<") is invalid!" << endl;
    }
    
    catch (error4 e4)
    {
        cout << "Error: Too many species!" << endl;
        cout << "Maximal number of species is ";
        cout << MAXSPECIES << "." << endl;
    }
     catch (error5 e5)
    {
        cout << "Error: Too many instructions for species ";
        cout << e5.SPECIES_NAME<<"!"<<endl;
        cout << "Maximal number of instructions is ";
        cout << MAXPROGRAM << "."<<endl;
    }
    
    catch (error6 e6)
    {
        cout << "Error: Instruction ";
        cout << e6.ui;
        cout << " is not recognized!"<<endl;
    }
    
    catch (error_wh a)
    {
        cout << "The grid ";
        cout << a.wh;
        cout << " is illegal!"<<endl;
    }
    
    catch (error_di wdi)
    {
        cout << "Error: Direction ";
        cout << wdi.di;
        cout << " is not recognized!"<<endl;
    }
    
    catch (error_us us)
    {
        cout << "Error: Species ";
        cout << us.usn;
        cout << " not found!"<< endl;
    }
    
    catch (error10 mc)
    {
        cout <<"Error: Too many creatures!"<<endl;
        cout <<"Maximal number of creatures is ";
        cout <<MAXCREATURES << "." <<endl;
    }
    
    catch (error13 e13)
    {
        cout<<"Error: Creature (";
        cout<<e13.SPECIES<<" "<<e13.DIR<<" "<<e13.r<<" "<<e13.c;
        cout<<") is out of bound!"<<endl;
        cout<<"The grid size is ";
        cout << e13.h;
        cout << "-by-";
        cout << e13.w << "."<<endl;
    }
    
    catch (error14 e14)
    {
        cout<<"Error: Creature (";
        cout<<e14.SPECIES<<" "<<e14.DIR<<" "<<e14.r<<" "<<e14.c;
        cout<<") has an invalid ability ";
        cout<< e14.ab<<"!"<<endl;
    }
    
    catch (error15 e15)
    {
        cout<<"Error: Creature (";
        cout<<e15.s1<<" "<<e15.d1<<" "<<e15.r<<" "<<e15.c;
        cout<<") overlaps with creature (";
        cout<<e15.s2<<" "<<e15.d2<<" "<<e15.r<<" "<<e15.c;
        cout << ")!"<<endl;
    }
    
    
    catch (error16 e16)
    {
        cout<<"Error: Creature (";
        cout<<e16.s<<" "<<e16.d<<" "<<e16.r<<" "<<e16.c;
        cout<<") is in a lake square!"<<endl;
        cout<<"The creature cannot fly!"<<endl;

    }
    
    
    
}
