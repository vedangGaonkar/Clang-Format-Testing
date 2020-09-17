#include "cities.h" 
#include "util.h"

//constructor with 2 arguments
salesman::salesman()
{

}

//destructor
salesman::~salesman()
{

}

/**************************************************************************//**
* @author Vedang Gaonkar, Seth Snyder
*
* @par Description
* This is the function that handles calling all of the other needed functions for 
* implementing the TSP problem. It also outputs the menu and calculates the time that
* it takes for the functions to run.
*
* @param[in] fin1 - The file that contains all of the cities.
* @param[in] fin2 - The file that contains all of the cities to visit.
*
* @return returns true if it runs through correctly false otherwise.
*
*****************************************************************************/
bool salesman::Processor(ifstream &fin1, ifstream &fin2)
{

    cout<<endl<<"TRAVELLING SALESMAN PROBLEM"<<endl<<endl;

    if( toVisit(fin2) == false)
	return false;

    cout<<"Cities to visit:"<<endl<<endl;

    if(database(fin1) == false)
	return false;
    
    string s;

    cout<<endl<<"Enter the city at the beginning of the tour:"<<endl;
    getline(cin,s);
    
    if(cityMap.count(s) <=0 )
    {
	cout<<endl<<"This city does not exist in the visited cities list!"<<endl<<endl;
	return false;
    }
    
    list<string>::iterator litt, lits;

    for(litt = perms.begin(); litt != perms.end(); litt++)
    {
	lits = litt;
	if(*litt == s)
	    {
		perms.erase(lits);
		litt--;
	    } 
    }

    cout<<endl<<"Tour Computed By Brute Force Algorithm:"<<endl<<endl;
    currDis = 0;
    
    clock_t begin1 = clock(); 
    Brute(s,0);
    clock_t end1 = clock();

    int tBrute = int(end1) - int(begin1);

    litt = finalPerm.begin();
       
    string::iterator ssit; 
    for(ssit = s.begin(); ssit != s.end(); ssit++)
	cout<<*ssit;
    cout<<endl;
 
    for(litt = finalPerm.begin(); litt != finalPerm.end(); litt++)
    {
	string temp = *litt;
	for(ssit = temp.begin(); ssit!= temp.end(); ssit++)
	    cout<<*ssit;
	cout<<endl;
    }

        
    for(ssit = s.begin(); ssit != s.end(); ssit++)
	cout<<*ssit;
    cout<<endl; 

    cout<<endl<<"The total distance covered is "<<totalDis<<" km."<<endl<<endl;

    cout<<"Time taken to perform brute force on "<<num<<" cities is "
	<<1000*(float(tBrute)/CLOCKS_PER_SEC)<<" milliseconds."<<endl<<endl;
    
    cout<<"Tour Computed By MST Algorithm:"<<endl<<endl;
    
    begin1 = clock();
    MST(s);
    end1 = clock();

    int tMST = int(end1) - int(begin1);

    cout<<"Time taken to perform MST on "<<num<<" cities is "<<1000*(float(tMST)/CLOCKS_PER_SEC)<<" milliseconds."<<endl<<endl;
    
    cout<<"MST is faster than Brute Force by "<<1000*(float(tBrute - tMST)/CLOCKS_PER_SEC)<<" milliseconds."<<endl<<endl;

    return true;
}

/**************************************************************************//**
* @author Vedang Gaonkar, Seth Snyder
*
* @par Description
* This is the function that inserts the cities to be visited into the visitList set
* and the perms vector.
*
* @param[in] fin - The file that contains all of the cities to visit.
*
* @return returns true if it runs through correctly false otherwise.
*
*****************************************************************************/
bool salesman::toVisit(ifstream &fin)
{

    string currCity;
   
    //Insert all the cities to be visited in the set 
    while(getline(fin,currCity))
    {
	visitList.insert(currCity);
	perms.push_back(currCity);
    }

    if(visitList.size() < 3)
    {
	cout<<endl<<"The number of cities to be visited should be more than two!"<<endl<<endl;
    	return false;
    }	

    num = visitList.size();

    return true;	
}

/**************************************************************************//**
* @author Vedang Gaonkar, Seth Snyder
*
* @par Description
* This function runs through the big file of cities and if the city is to be visited
* it puts it into the map and creates a node with the adjList of cities and their
* distances.
*
* @param[in] data - The file that contains all of the cities.
*
* @return returns true if it runs through correctly false otherwise.
*
*****************************************************************************/
bool salesman::database(ifstream &data)
{

    double currLat, currLong;
    string currCity;

    while(data>>currLat)
    {
	data.ignore();
	data>>currLong;
	data.ignore();
	getline(data, currCity);

	//Check if the current city is to be visited
	if(setContains(currCity))
	{
	    set<pair<double, string> > currSet;
	  
	    struct city curr; 
	    curr.adjList = currSet;

	    //Insert the current city to the map 
	    cityMap.insert(make_pair(currCity, curr));

	    double dis = 0;

	    for(string::iterator sit = currCity.begin();
		sit != currCity.end(); sit++)
		    cout<<*sit;
	    cout<<endl;
 
	    vector<pair<string, pair<double,double> > >::iterator it;
	    for(it = added.begin(); it != added.end(); it++)
	    {
		//Distance between the current city and the currently iterated
	    	dis = calcDistance(currLat/1000, currLong/1000, 
			it->second.first/1000, it->second.second/1000);

		//Insert the current city to the adj list
		cityMap[it->first].adjList.insert(make_pair(dis,currCity));
		cityMap[currCity].adjList.insert(make_pair(dis,it->first)); 
	    }

	    //Add the current city to the added vector along with its coordinates
	    added.push_back(make_pair(currCity, make_pair(currLat,currLong))); 

	    //Remove the city from the visitList set
	    visitList.erase(currCity);
	}		 
    }
    
    if(visitList.size() !=0)
    {
	cout<<endl<<"One or more cities in the visited list do not ";
	cout<<"exist in the dataset!"<<endl<<endl;
	return false;
    }

    return true;
}

/**************************************************************************//**
* @author Vedang Gaonkar, Seth Snyder
*
* @par Description
* This function takes in the latitude and longitude values for the two different cities
* and claculates the distance in kilometers based off of the equation given to us in the
* writeup.
*
* @param[in] lat1 - The value for the latitude of the current city.
* @param[in] lon1 - The value for the longitude of the current city.
* @param[in] lat2 - The value for the latitude of the city that they are traveling to.
* @param[in] lon2 - The value for the longitude of the city that they are traveling to.
*
* @return d which is the distance in kilometers.
*
*****************************************************************************/
double salesman::calcDistance(double lat1, double lon1, double lat2, double lon2)
{

    double dlon = 0;
    double dlat = 0;
    double a = 0;
    double c = 0;
    double d = 0;

    dlon = (lon2 - lon1);
    dlat = (lat2 - lat1);

    dlon *= M_PI/180;
    dlat *= M_PI/180;

    lat1 *=M_PI/180;
    lat2 *= M_PI/180;

    a = pow(sin(dlat/2), 2.0) + cos(lat1) * cos(lat2) * pow(sin(dlon/2), 2.0);
    c = 2 * atan2( sqrt(a), sqrt(1-a) );
    d = 6373 * c;

    return d;

}

/**************************************************************************//**
* @author Vedang Gaonkar, Seth Snyder
*
* @par Description
* This function finds the shortest hamilton circuit implemented by the MST algoithm and
* outputs it to the screen.
*
* @param[in] start - the name of your starting node in the graph.
*
*****************************************************************************/
void salesman::MST(string start)
{
    totalDis = 0;
    bool flag = true;
    set<pair<double, string> > currSet;
    set<pair<double, string> >::iterator it;
    string currCity;
    string temp;
    
    for(string::iterator sit = start.begin(); sit != start.end(); sit++)
        cout<<*sit;
    cout<<endl;

    currCity = start;
    cityMap[start].visited = true;
 
    while(flag == true)
    {
        currSet = cityMap[currCity].adjList;
        it = currSet.begin();

        while(it != currSet.end() && 
		cityMap[it->second].visited == true)
            it++;

        if(it == currSet.end())
            flag = false;

        else
        {
            totalDis += it->first;  
            cityMap[it->second].visited = true;

	    temp = it->second;

	    for(string::iterator sit = temp.begin(); sit!= temp.end();sit++)
	          cout<<*sit;
	    cout<<endl;
	    
	    currCity = it->second;
        }
    }

    for(it = currSet.begin(); it != currSet.end(); it++)
    {
	if(it->second == start)
	    totalDis += it->first;
    }

    for(string::iterator sit = start.begin(); sit != start.end(); sit++)
        cout<<*sit;
    cout<<endl;

    cout<<endl<<"The total distance covered is "<<totalDis<<" km."<<endl<<endl; 
    return;
}

/**************************************************************************//**
* @author Vedang Gaonkar, Seth Snyder
*
* @par Description
* This function uses brute force recursion to find the shortest hamilton circuit
* and the distance.
*
* @param[in] start - The starting node in the hamilton circuit.
* @param[in] nCurr - the number of times it has run through the recursion.
*
*****************************************************************************/
void salesman::Brute(string start, int nCurr)
{
    set<pair<double,string> > currSet;

    if(num-1 == nCurr)
    {

	currDistance(start);

	if(currDis < totalDis || totalDis < 1)
	{
	    totalDis = currDis;
	    finalPerm = perms;
	}
	
	return;
    }

    for(int i = nCurr; i< num -1; i++)
    { 
	lit1 = perms.begin();
	lit2 = perms.begin();

	for(int j=0; j<nCurr; j++)
	    lit1++;

	for(int j=0; j<i; j++)
	    lit2++;

	swapCities();

	Brute(start, nCurr+1);	

	lit1 = perms.begin();
	lit2 = perms.begin();

	for(int j = 0; j<nCurr; j++)
	    lit1++;
	
	for(int j=0; j < i; j++)
	    lit2++;

	swapCities();

    }

}

/**************************************************************************//**
* @author Vedang Gaonkar, Seth Snyder
*
* @par Description
* This function finds the toatal distance of the circuit of any given permutation
* in the recursive function.
*
* @param[in] start - The starting node in the hamilton circuit.
*
*****************************************************************************/
void salesman::currDistance(string start)
{
    set<pair<double, string> > currSet; 
    set<pair<double, string> >::iterator stit; 
    list<string>::iterator lit, next;

    currSet = cityMap[start].adjList;
    next = perms.begin();

    currDis  =0;

    for(stit = currSet.begin(); stit != currSet.end(); stit++)
    {
	if(stit->second == *next)
	    currDis += stit->first;
    }

    next++;

    for(lit = perms.begin(); next != perms.end(); next++, lit++)
    {
	currSet = cityMap[*lit].adjList;
	 
	for(stit = currSet.begin(); stit != currSet.end(); stit++)
	{
	    if(stit->second == *next)
		currDis += stit->first;		
	}
    }

    currSet = cityMap[*lit].adjList;
	
    for(stit = currSet.begin(); stit != currSet.end(); stit++)
    {
	if(stit->second == start)
	    currDis += stit->first;
    }

    return; 
}

/**************************************************************************//**
* @author Vedang Gaonkar, Seth Snyder
*
* @par Description
* This funciton swaps the cities based off the iterators of their respective sets.
*
*****************************************************************************/
void salesman::swapCities()
{
    string temp;
    temp = *lit1;
    *lit1 = *lit2;
    *lit2 = temp;

    return;  
}

