// // This program is designed to parse city and route data from files, build a graph from that data, and then find the shortest or cheapest path between two specified cities using Dijkstra's algorithm. It outputs the results to an HTML file.

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include <stack>

#include "FileOperations.h"          // custom header
#include "Route.h"
#include "GraphFunctions.h"

using namespace std;

int main(int argc, char* argv[]){

	string citiesFilename;
	string routesFilename;
	string outputFilename;
	string origin;
	string destination;
	string preference;
	bool biPreference;

	if(argc > 1){
		citiesFilename = argv[1];
	}
	else{
		cout << "Enter filename containing cities: ";
		cin >> citiesFilename;
	}

	if(argc > 2){
		routesFilename  = argv[2];
	}
	else{
		cout << "Enter filename containing routes: ";
		cin >> routesFilename;
	}

	if(argc > 3){
		outputFilename = argv[3];
	}
	else{
		cout << "Enter filename for output (.html): ";
		cin >> outputFilename;
	}

	if(argc > 4){
		origin = argv[4];
	}
	else{
		cout << "Origin: ";
		cin >> origin;
	}

	if(argc > 5){
		destination = argv[5];
	}
	else{
		cout << "Destination: ";
		cin >> destination;
	}

	if(argc > 6){
		preference = argv[6];
	}
	else{
		cout << "Enter a preference (fastest/cheapest): ";
		cin >> preference;
	}

	if(preference.compare("cheapest") == 0){
		biPreference = true;
	}
	else if(preference.compare("fastest") == 0){
		biPreference = false;
	}
	else{
		cout << "Invalid entry";
		return 0;
	}

	Graph graph(citiesFilename, routesFilename);

	cout << "Origin entered: " << origin << endl;
	cout << "Destination entered: " << destination << endl;
	
	Location *originCity = graph.getCity(origin);
	Location *destCity = graph.getCity(destination);

	if (originCity == NULL)
	{
		cout << "Origin city not found in graph!" << endl;
	}
	if (destCity == NULL)
	{
		cout << "Destination city not found in graph!" << endl;
	}

	graph.Dijkstras(origin,biPreference);

	stack<Location*> cityStack = graph.cityStacker(destination);
	stack<Route*> routeStack = graph.routeStacker(destination, biPreference);

	outputGenerator(outputFilename.c_str(), cityStack, routeStack, biPreference);

	return 0;
}
