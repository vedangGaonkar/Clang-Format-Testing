#include "util.h"
#define _USE_MATH_DEFINES

/**************************************************************************//**
* @author Vedang Gaonkar
*
* @par Description
* This is the function checks to see if the command line entered city name is
* in the list of cities bein visited.
*
* @param[in] s - The name of the city you are trying to start at.
*
* @return returns true if it runs through correctly false otherwise.
*
*****************************************************************************/
bool salesman::setContains(string s)
{
    if(visitList.find(s) == visitList.end())
	return false;
    
    return true;
}


