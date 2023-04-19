#ifndef LAB5_GRAPH_H
#define LAB5_GRAPH_H

#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include <fstream>

struct Transition;
struct Place;

struct Place{
	int amount;//amount of markers in place
	std::vector<int> outputs;
	std::vector<int> inputs;
	int x, y;
	
	std::shared_ptr<std::mutex> mutex;
	
	Place(const std::vector<int> &in, const std::vector<int> &out, int X, int Y) : amount(0) {
		for(int it : in){
			inputs.emplace_back(it);
		}
		for(int it : out){
			outputs.emplace_back(it);
		}
		x = X;
		y = Y;
		
		mutex = std::make_shared<std::mutex>();
	}
	
	void addMarker(int id){
		amount += 1;
	}
};

struct Transition{
	std::vector<int> outputs;
	std::vector<int> inputs;
	int x, y;
	
//	mutable std::mutex _lock;
	std::shared_ptr<std::mutex> mutex;
	
	Transition(const std::vector<int> &in, const std::vector<int> &out, int X, int Y){
		for(int it : in){
			inputs.emplace_back(it);
		}
		for(int it : out){
			outputs.emplace_back(it);
		}
		x = X;
		y = Y;
		
		mutex = std::make_shared<std::mutex>();
	}
};

struct Marker{
	int plId;
};

class Graph {
private:
	std::vector<Place> places;
	std::vector<Transition> transitions;
//	std::vector<Marker> markers;

	std::chrono::milliseconds simulateTime;
	std::chrono::steady_clock::time_point startTime;
	
	std::mutex plsLock, logWriting;
	
	int minSleep, sleepInterval;
	
	std::ofstream logFile;
	
	std::atomic<int> lockedPlaces = 0;
public:
	Graph(const char *fname, const char *params);
	
	unsigned long long getPlAmount() const { return places.size(); }
	unsigned long long getTrAmount() const { return transitions.size(); }
	
	void visualize(std::string &fname);
	
//	bool isPermitted(int index) const;
	bool transit(int trIndex, int plIndex);
	
	void managePlace(Place &pl, int index);
	
	void simulate();
	
	void addMarker(int index);
};


#endif //LAB5_GRAPH_H
