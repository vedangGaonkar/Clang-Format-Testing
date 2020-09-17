/***************************************************************************//**
 * @file main.cpp
 * @mainpage Project 3 - Traveling Salesman Problem
 *
 * @section course_section Course Information
 *
 * @authors Vedang Gaonkar, Seth Synder
 * 
 * @date Dec. 5, 2018
 * 
 * @par Professor: Dr. Qiao
 *
 * @par Course: CSC 315 - Section 1 - Fall 2018
 *
 * @section program_section Program Description
 *
 * @par Description
 * This program opens a allcities, and visited cities file with different feilds
 * seperated by |. We then take the values for the needed cities from the allcities
 * file calculate the distances in km from the long and lat. We then build an adjList out
 * of a map and a node structure that stores the connected nodes and the distances to the 
 * connected node in a set. We then use a brute force method and a MST method to calculate
 * the shortest hamilton circuit. We output the shortest path, the distance, and the runtime
 * for the two different methods.
 *
 * @section compile_section Compile Section
 *
 * @par Usage
 * prog.exe allcities.txt visitedcities.txt
 *
 * When choosing your starting city make sure to use an entire city identifier ex. Denver|Denver|CO
 * @section todo_bugs_modification_section To Do, Bugs, and Modifications
 *
 *
 * @par Revision History
 * <a href="git@gitlab.mcs.sdsmt.edu:7442960/csc315_fall2018_project3.git">GitLab Commit History</a>
 *
 *****************************************************************************/
#include "cities.h"
#include "util.h"

/**************************************************************************//**
* @author Vedang Gaonkar, Seth Snyder
*
* @par Description
* This is the main function it checks for the correct input from the command line
* as well as opens the two files needed for the rest of the program. It then calls
* the processor function which handles most of the program.
*
* @param[in] argc - The number of commandline arguments.
* @param[in] argv[] - array of the commandline arguments.
*
*****************************************************************************/
int main(int argc, char* argv[])
{

    cout<<setprecision(10)<<fixed;

    ifstream fin1, fin2;
    
    if(argc != 3)
    {
	    cout<<"Command line should be of the format ";
	    cout<<"% TSP file1name file2name"<<endl<<endl;
	    return -1;
    }

    fin1.open(argv[1]);
    fin2.open(argv[2]);

    if(!fin1 || !fin2)
    {
	cout<<"Could not open atleast one of the files!"<<endl;
	return -1;
    }

    salesman sm;

    if(sm.Processor(fin1,fin2) == false)
	return -1;

    return 0;
}
