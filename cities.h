#ifndef _CITIES_H_
#define _CITIES_H_
#define _USE_MATH_DEFINES_

//Change this to c++ 11 later
#include <bits/stdc++.h>

using namespace std;
/*!
*@brief The salesman class that is used to implement the
* TSP prblem
*/
class salesman
{

public:
   
    salesman();
    ~salesman(); 
    bool database(ifstream&);
    bool toVisit(ifstream&); 
    bool setContains(string);
    bool Processor(ifstream& ,ifstream&);
    void Brute(string, int);
    void swapCities();
    void currDistance(string);
    double calcDistance(double lat1, double lon1, double lat2, double lon2);
    void MST(string);

private:
    /*!
    *@brief The structure used to store the flags for visiting the nodes
    * and the adjList set.
    */
    struct city
    {
	bool visited;
	bool visit;
	//Set of adjaceny list of a city
	//Here the double is the distance and string is the city name
	set< pair<double, string> > adjList;
    
	city()
	{
	    visited = false;
	    visit = false;
	}

    };

    double totalDis;    //Total Distance covered 

    //This set contains all the cities from the file visitedcities.txt   
    set<string> visitList;
   
    //This map contains the adjacency list of every city that is to be visited 
    map<string, city> cityMap;
      
    //This vector stores cities and their coordinates as we run the 
    //allcities.txt file 
    vector<pair<string, pair<double,double> > > added;

    //Params for brute force
    int num;
    double currDis;
    string currentCity;
    list<string> perms, finalPerm;
    list<string>::iterator lit1, lit2;

};


#endif
