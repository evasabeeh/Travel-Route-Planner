// Provides functions for parsing location and route data from files and generating an HTML file to visualize the route on a Google Map.

#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

#include "Location.h"

using namespace std;

vector<Location*> locationParser(string filename, vector<Route*> routes){
	fstream locations(filename.c_str());

	string country;
	string city;
	string latitude;
	string longitude;

	vector<Location*> cities;
	Location* node;

	while(locations.good()){
		getline(locations, country, ',');
		getline(locations, city, ',');
		getline(locations, latitude, ',');
		getline(locations, longitude);

		node = new Location(country, city, atof(latitude.c_str()), atof(longitude.c_str()));

		vector<Route*>::iterator it = routes.begin();

		while(it != routes.end()){
			if((*it) -> originS.compare(node -> capital) == 0){
				(*it) -> origin = node;
				node -> routes.push_back((*it));
			}
			else if((*it) -> destinationS.compare(node -> capital) == 0){
				(*it) -> destination = node;
			}
			++it;
		}
		cities.push_back(node);
	}
	cout << "Locations parsed from: " << filename << endl;
	return cities;
}

vector<Route*> routeParser(string filename){

	fstream routes(filename.c_str());

	string originS;
	string destinationS;

	Location* origin = new Location();
	Location* destination = new Location();

	string type;
	string time;
	string cost;
	string note;

	vector<Route*> allRoutes;
	Route* edge;

	while(routes.good()){
		getline(routes, originS, ',');
		getline(routes, destinationS, ',');
		getline(routes, type, ',');
		getline(routes, time, ',');
		getline(routes, cost, ',');
		getline(routes, note);

		edge = new Route(origin, destination, type, atof(time.c_str()), atof(cost.c_str()), note);
		edge -> destinationS = destinationS;
		edge -> originS = originS;

		allRoutes.push_back(edge);
	}

	cout << "Routes parsed from: " << filename << endl;
	return allRoutes;
}

//Generates an appropriately formatted .html file that displays the route information passed in by the stack fo cities and routes

void outputGenerator(string filename, stack<Location*> cities, stack<Route*> routes, bool costOrTime){
	ofstream output(filename.c_str());

	// It sets up the HTML structure and Google Maps JavaScript API.
	output << "<HTML><HEAD><TITLE>Route Planner</TITLE></HEAD><script type='text/javascript' src='http://maps.google.com/maps/api/js?sensor=false'></script><script>function initialize() { var myOptions = { zoom: 3, center: new google.maps.LatLng(0, 0), mapTypeId: google.maps.MapTypeId.ROADMAP};var map=new google.maps.Map(document.getElementById('map'), myOptions);\n";

	int markerCount = 0;
	int contentStringCount = 0;
	Location* origin;
	Location* destination;
	Route* route;

	float cost;

	// create markers, representing cities and polylines, representing the paths on the map
	while(!cities.empty() && !routes.empty()){

		origin = cities.top();
		cities.pop();
		destination = cities.top();
						
		output << "var marker" << markerCount << " = new google.maps.Marker({ position: new google.maps.LatLng(" << origin -> lat << ", " << origin -> lon << "), map: map, title: \"" << origin -> capital << ", " << origin -> country << "\"});\n";
		
		markerCount++;
			
		output << "var marker" << markerCount << " = new google.maps.Marker({ position: new google.maps.LatLng(" << destination -> lat << ", " << destination -> lon << "), map: map, title: \"" << destination -> capital << ", " << destination -> country << "\"});\n";
		
		markerCount++;

		route = routes.top();
		routes.pop();

		cost = route -> cost;
		if(route -> transport.compare("plane") == 0){
			cost =  cost / MULTI;
		}

		output << "var contentString" << contentStringCount << " = \"" << origin -> capital << ", " << origin -> country << " --> " << destination -> capital << ", " << destination -> country << "(" << route -> transport << " - " << route -> time << " hours - $" << cost << ")\"; var path" << contentStringCount << " = new google.maps.Polyline({ path: [new google.maps.LatLng(" << origin -> lat << ", " << origin -> lon << "), new google.maps.LatLng(" << destination -> lat << ", " << destination -> lon << ")], strokeColor: '#0000FF', strokeOpacity: 1.0, strokeWeight: 2}); path"<< contentStringCount <<".setMap(map); google.maps.event.addListener(path" << contentStringCount << ", 'click', function(event) { alert(contentString" << contentStringCount << ");});\n";
		contentStringCount++;
	}
	output << "} google.maps.event.addDomListener(window, 'load', initialize); </script></HEAD><BODY><div id='map' style='width:100%;height:100%;'></div></BODY></HTML>";
	output.close();

	cout << "Output File Generated: " << filename << endl;
}

#endif
