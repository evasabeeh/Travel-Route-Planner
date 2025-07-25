// Route class, which represents a route or path between two Location objects. This class includes various attributes and methods to describe and manage routes, including transportation type, time, cost, and other details.

#ifndef ROUTE_H
#define ROUTE_H

#include <string>

#include "Location.h"
using namespace std;

class Location;

const float MULTI = 3; // Defines a constant MULTI with a value of 3, used to adjust the cost for plane transportation.

class Route{
public:
	Location *origin;           // origin and destination are pointers to Location objects
	Location *destination;

	string originS;
	string destinationS;

	string transport;
	float time;
	float cost;
	string note; // any additional information about the route.

	Route();
	~Route();
	Route(Location *org, Location *dest);
	Route(Location *org, Location *dest, string trans, float tim, float cst, string notee);

	bool doesConnect(Location *start, Location *end); // a method that checks if the route connects two given locations.
};

Route::Route()
{ // Default constructor initializes all attributes to default values.
	origin = NULL;
	destination = NULL;
	transport = "";
	time = 0;
	cost = 0;
	note = "";
};

Route::~Route(){
};

Route::Route(Location* org, Location* dest){
	origin = org;
	destination = dest;
	transport = "";
	time = 0;
	cost = 0;
	note = "";
};

Route::Route(Location* org, Location* dest, string trans, float tim, float cst, string notee){
	origin = org;
	destination = dest;
	transport = trans;
	time = tim;
	cost = cst;
	note = notee;

	if(trans.compare("plane") == 0){
		cost =  cst * MULTI;
	}
};

bool Route::doesConnect(Location* start, Location* end){
	if(start == origin && end == destination){
			return true;
	}
	else{
		return false;
	}
};

#endif
