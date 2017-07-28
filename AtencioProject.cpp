//
//  AtencioProject.cpp
//  
//
//  Created by Sol  on 7/21/17.
//
//

#include "AtencioProject.hpp"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//creates graph edge
template<class T>
void WeatherForecast<T>::addEdge(T v1, T v2, int weight){
    
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex<T> av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}

//creates graph vertex
template<class T>
void WeatherForecast<T>::addVertex(T n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex<T> v;
        v.name = n;
        vertices.push_back(v);
        
    }
}

template<class T>
//displays graph edges
void WeatherForecast<T>::displayEdges(){
    string separator = "-->";
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name<<"***";
        }
        cout<<endl;
    }
}
//creates city map for weather
void WeatherForecast::BuildGraph(){
    WeatherForecast<string> g;
    g.addVertex("Boulder");
    g.addVertex("Denver");
    g.addVertex("Highlands Ranch");
    g.addVertex("Aurora");
    g.addVertex("Fort Collins");
    //edge written to be undirected
    g.addEdge("Boulder", "Denver", 30);
    g.addEdge("Boulder", "Highlands Ranch", 60);
    g.addEdge("Boulder", "Aurora", 40);
    g.addEdge("Denver", "Aurora", 10);
    g.addEdge("Aurora", "Fort Collins", 80);
    g.displayEdges();
    
    WeatherForecast<int> g2;
    //add vertext
    g2.addVertex(5);
    g2.addVertex(6);
    g2.addVertex(7);
    g2.addVertex(8);
    //set edge distance
    g2.addEdge(5,6,30);
    g2.addEdge(5,7,60);
    g2.addEdge(7,8,10);
    g2.displayEdges();

}
//generates random current weather for user
string WeatherForecast:: getWeather(){
    string currWeather;
    int i = rand() % 6;
    if (i = 1){
        currWeather="Cloudy";
    }
    if (i = 2){
        currWeather="Sunny";
    }
    if (i = 3){
        currWeather="Rainy";
    }
    if (i = 4){
        currWeather="Tornado";
    }
    if (i = 5){
        currWeather="Snowy";
    }
    if (i = 6){
        currWeather="Windy";
    }
    
    return currWeather;
}

void WeatherForecast:: warn(string starting, string destination){
    //uses distkra to find shortest path to warn one city to another of bad weather
    vertex * start = nullptr;
    vertex * ending = nullptr;
    //search routine to find starting and destination
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].visited = false;
        vertices[i].distance = INT_MAX;
        vertices[i].previous = nullptr;
        if (vertices[i].name == starting) {
            start = &vertices[i];
        }
        if (vertices[i].name == destination) {
            ending = &vertices[i];
        }
    }
    if (start != nullptr && ending != nullptr)
    {
        cout<< "Solving fastest route to let city know of bad weather" << endl;
        start->visited = true;
        start->distance = 0;
        cout<<"pushing "<<start->name<<" into solved"<<endl;
        vector<vertex *> solved;
        vector<vertex *> path;
        solved.push_back(start);
        //path.push_back(start);
        adjVertex * v;
        vertex * u;
        vertex * minVertex;
        vertex * prev;
        while (ending->visited == false) {
            int minDistance = INT_MAX;
            for (int i = 0; i < solved.size(); i++) {
                u = solved[i];
                cout<<endl;
                cout<<"Inspecting route from "<<u->name<<endl;
                for (int j = 0; j < u->adj.size(); j++) {
                    v = &solved[i]->adj[j];
                    cout<<"-> to "<<v->v->name;
                    if (v->v->visited == false) {
                        cout<<", not yet solved,";
                        int dist = u->distance + v->weight;
                        if (dist < minDistance) {
                            cout<<" the minimum distance was "<<minDistance;
                            minDistance = dist;
                            minVertex = v->v;
                            prev = u;
                            cout<<" but there is a new minimum distance of "<<dist<<" between "
                            <<start->name <<" and "<<minVertex->name<<endl;
                        }else{cout<<" the minimum distance is "<<minDistance
                            <<" and there is not a new minimum distance "<<dist<<endl;}
                    }else{
                        cout<<" already solved, moving on"<<endl;
                    }
                }
                
            }
            solved.push_back(minVertex);
            cout<<endl;
            cout<<"pushing "<<minVertex->name<<" into solved ";
            minVertex->distance = minDistance;
            minVertex->previous = prev;
            minVertex->visited = true;
            cout<<minVertex->name;
            cout<<"(distance: "<<minVertex->distance
            <<", visited: "<<minVertex->visited
            <<", parent: "<<minVertex->previous->name<<")"<<endl;
            cout<<"destination "<<ending->name<<" solved? "<<ending->visited<<endl;
            cout<<endl;
        }
        cout<<"Shortest Path"<<endl;
        vertex * vert = ending;
        while (vert != nullptr) {
            path.push_back(vert);
            vert = vert->previous;
        }
        for (int i = 0; i < path.size(); i++) {
            if (i == path.size()-1)
                cout<<path[path.size()-1-i]->name;
            else
                cout<<path[path.size()-1-i]->name<<" - ";
            
        }
        cout<<endl;
        cout<<"Minimum Distance: "<<solved[solved.size()-1]->distance<<endl;
    }else if (ending!=nullptr){
        cout<<"start not found"<<endl;
        exit(1);
    }else{
        cout<<"ending not found"<<endl;
        exit(1);
    }

}
void WeatherForecast::sendForecast(string cityType){
    
    //let user know data was sent
    cout<< cityType<<" recieved forecast"<<endl;
    
    // attach link list to vertices
    
    minVertex->name = head;
    
}
void WeatherForecast:: autoWarn(){
    //traverse link list, for bad weather
    string BadWeather = "Tornado";
    int i = 1;
    while (head->next !=NULL) {
        if (head->forecast = BadWeather){
            cout << "Will warn all cities of bad weather occuring on day " << i << endl;
        }
        i++;
        head = head->next;
    }
    cout<< "No bad weather this week, no warnings were sent." << endl;
}

void WeatherForecast:: buildNetwork (string array[]){
    
    
    // makes a node for each city
    for (int x = 0; x < 7; x++){
        Weather * list = new Weather;
        Weather * key = new Weather;
        
        
        // set up as last element so it is equal to NULL
        list -> next = NULL;
        
        // puts information into the list value
        
        // gives the weather type into the list
        list -> forecast = array [x];
        
        // means that this is not the first value inputed
        if (head != NULL)
        {
            key = head;
            while (key -> next != NULL)
            {
                key = key -> next;
            }
            // sets the last value to the list to the new node
            key->next = list;
        }
        else
        {
            head = list;// this is if the list doesn't already exist
        }
    }
    //shows forecast to user
    cout << "===SEVEN DAY FORECAST===\nNULL <- ";
    Weather *value = new Weather;
    value = head;
    while (value != NULL)
    {
        cout << value -> forecast << " <-> ";
        
        value = value -> next;
    }
    cout << "-> NULL\n==================\n";
}

//deletes forecast
void WeatherForecast :: deleteNetwork (){
    Weather * deletePointer = NULL;
    Weather * key = new Weather;
    Weather * temp = new Weather;
    temp = head;
    key = head;
    
    // run through list to delete and cout the information
    while (key != NULL){
        cout << "deleting " << key -> forecast << endl;
        deletePointer = key;
        key = key -> next;
        head = key;
        delete deletePointer;
    }
    head = key;
}


//driver
int main(){
    int i = 0;
    int input = 0;
    WeatherForecast myForecast;
    myForecast.BuildGraph();
    
    while(i != 8){
    cout<< "BOULDER WEATHER MESSENGER" <<endl;
    cout<< "-------------------------" <<endl;
    cout<< "Current Weather is: " myForecast.getWeather(); <<endl;
    cout<< " "  <<endl;
    cout<< "1. Build Forecast" <<endl;
    cout<< "2. Warn a city about current weather" <<endl;
    cout<< "3. Turn on automatic warn" <<endl;
    cout<< "4. Delete Entire Forecast" <<endl;
    cout<< "5. Get current weather" <<endl;
    cout<< "6. Show city map with distance" <<endl;
    cout<< "7. Send forecast to city" <<endl;
    cout<< "8. Quit" <<endl;
        
        cin>>input;
        
        if(input==1){
            //linked list function
        	int day = 0;
            string array[6];
            	while(day<=6){
                    //generates random weather forecast for 7 day week
                    string futWeather;
                    futWeather = myForecast.getWeather()
                    array[day] = futWeather;
                    day++;
                
                    }
            //passes array to create a linked list
            myForecast.buildNetwork(array[6]);
            
        }
        if(input==2){
            //graph and dikjstra function
            string boulder = "boulder";
            string city;
            cout<<"What city to warn?"
            //show city map with distance
            cin >> city;
            myForecast.warn(boulder,city);
            
        }
        if(input==3){
            //graph and dikjstra function
            myForecast.autoWarn();
            
        }
        if(input==4){
            //linked list function
            myForecast.deleteNetwork();
        }
        
        if(input==5){
            //linked list function
            myForecast.getWeather();
        }
        if(input==6){
            //graph function
            myForecast.displayEdges();
        
        }
        if(input==7){
            //linked list + graph function
            string cityType;
            cout << "what city?"<< endl;
            cout<<"Boulder, Highlands Ranch, Denver, Aurora, Fort Collins"<<endl;
            cin >> cityType;
            cout<< cityType << " recieved forecast"<<endl;
            
        }
        if(input==8){
            cout<< "Goodbye" <<endl;
            i = 8;
        }
}
		return 0;
}
