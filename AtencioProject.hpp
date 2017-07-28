//
//  AtencioProject.hpp
//  
//
//  Created by Sol  on 7/21/17.
//
//

#ifndef AtencioProject_hpp
#define AtencioProject_hpp

#include <stdio.h>
#include <string>
#endif /* AtencioProject_hpp */
using namespace std;

//linked list struct
struct Weather{
    std::string weatherType;
    std::string forecast;
    Weather *next;
    Weather *previous;
    
    Weather(){}; // default constructor
    
    Weather(std::string initName, Weather *initNext, Weather *initPrevious, std::string initMessage)
    {
        weatherType = initName;
        next = initNext;
        previous = initPrevious;
        forecast = initMessage;
    }
    
};
//graph structs
template<class T>
struct vertex;

template<class T>
struct adjVertex{
    vertex<T> *v;
    int weight;
};

template<class T>
struct vertex{
    T name;
    std::vector<adjVertex<T> > adj;
};
//combined weather and graph classes
template<class T>
class WeatherForecast{
private:
    Weather *head;
    Weather *tail;
    std::vector<vertex<T> > vertices;

    
protected:
    
public:
    //constructor
    WeatherForecast();
    //destructor
   ~WeatherForecast();
    //functions
   void BuildNetwork();
    void warn();
    void autoWarn();
    void BuildNetwork(string array[]);
    void deleteNetwork();
    void addEdge(T v1, T v2, int weight);
    void addVertex(T name);
    void displayEdges();
    void sendForecast(string cityType);
    string getWeather();
    void BuildGraph();
    
    
};
