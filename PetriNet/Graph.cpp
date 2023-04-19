#include "Graph.h"
#include <iostream>

Graph::Graph(const char *fname, const char *param) {
	int trAmount, plAmount;
	std::ifstream fs(fname);
	if(!fs.is_open()){
		throw std::runtime_error("Can't open graph file");
	}
	
	fs >> plAmount >> trAmount;
	for(int i = 0;i < plAmount;++i){//for each place
		std::vector<int> inTr, outTr;
		int outAmount, inAmount;
		fs >> inAmount >> outAmount;
		int x, y;
		fs >> x >> y;
		for(int j = 0;j < inAmount;++j){//collect all in transitions
			int tr;
			fs >> tr;
			inTr.emplace_back(tr);
		}
		for(int j = 0;j < outAmount;++j){//collect all out transitions
			int tr;
			fs >> tr;
			outTr.emplace_back(tr);
		}
		
		places.emplace_back(inTr, outTr, x, y);
	}
	for(int i = 0;i < trAmount;++i){//for each transition
		std::vector<int> inPl, outPl;
		int outAmount, inAmount;
		fs >> inAmount >> outAmount;
		int x, y;
		fs >> x >> y;
		for(int j = 0;j < inAmount;++j){//collect all in places
			int tr;
			fs >> tr;
			inPl.emplace_back(tr);
		}
		for(int j = 0;j < outAmount;++j){//collect all out places
			int tr;
			fs >> tr;
			outPl.emplace_back(tr);
		}
		
		transitions.emplace_back(inPl, outPl, x, y);
	}
	
	fs.close();
	
	fs.open(param);
	if(!fs.is_open()){
		throw std::runtime_error("Can't open parameter's file");
	}
	
	//get simulation time
	int time, maxSleep;
	fs >> time >> minSleep >> maxSleep;
	sleepInterval = maxSleep - minSleep;
	simulateTime = std::chrono::milliseconds(time);
	
	for(auto & place : places){
		int amount;
		fs >> amount;
		place.amount = amount;
	}
	
	std::string name = "graphStart.png";
	visualize(name);
	
	fs.close();
}

void Graph::visualize(std::string &fname){
	std::string dotName = "dots/" + std::to_string((std::chrono::steady_clock::now() - startTime).count()) + ".dot";
	std::ofstream fs(dotName, std::ios::trunc);
	if(!fs.is_open()){
		throw std::runtime_error("Can't create dot file");
	}
	
	//get current conditions
	std::vector<Place> copy = places;
	plsLock.unlock();
	
	int radius = 1;
	srand(time(nullptr));
	
	fs << "digraph Graph{" << std::endl;
	
	int index = 0;
	for(const Place &it : copy){
		fs << "pl" << index++ << R"( [pin=true shape=circle width=)" << radius << R"( label=")" << ((it.amount == 0) ? "" : std::to_string(it.amount)) << R"(" pos=")" << it.x << "," << it.y << "!\"]" << std::endl;
	}
	index = 0;
	for(const Transition &it : transitions){
		fs << "tr" << index++ << R"( [pin=true shape=rectangle width=0 height=2 label="" pos=")" << it.x << "," << it.y << "!\"]" << std::endl;
	}
	
	fs << std::endl;
	
	index = 0;
	for(const Place &it : copy){
		for(const int to : it.outputs){
			fs << "pl" << index << " -> " << "tr" << to << std::endl;
		}
		index++;
	}
	index = 0;
	for(const Transition &it : transitions){
		for(const int to : it.outputs){
			fs << "tr" << index << " -> " << "pl" << to << std::endl;
		}
		index++;
	}
	
	fs << "}" << std::endl;
	fs.close();
	
	std::string command = "dot -Kfdp -n -Tpng -o" + fname + " " + dotName;
	system(command.c_str());
}

/*bool Graph::isPermitted(int index) const {//check if transition is permitted
	if(index >= transitions.size() || index < 0) return false;
	
	const Transition &tr = transitions[index];
	
	tr.mutex->lock();
	for(auto it : tr.inputs){
		if(places[it].amount < (int) std::count(tr.inputs.begin(), tr.inputs.end(), it)) return false;
	}
	tr.mutex->unlock();

	return true;
}*/

bool Graph::transit(int trIndex, int plIndex){//try to transit
	if(trIndex >= transitions.size() || trIndex < 0) return false;
	
	const Transition &tr = transitions[trIndex];
	
	std::lock(*tr.mutex, plsLock, logWriting);
	std::lock_guard<std::mutex> trG(*tr.mutex, std::adopt_lock);
	std::lock_guard<std::mutex> plsG(plsLock, std::adopt_lock);
	std::lock_guard<std::mutex> logG(logWriting, std::adopt_lock);
	
	long long time = (std::chrono::steady_clock::now() - startTime).count();
	
	for(auto it : tr.inputs){
		if(places[it].amount < (int) std::count(tr.inputs.begin(), tr.inputs.end(), it)) {
			logFile << "Can't activate " << std::to_string(trIndex) << " transition from "
					<< std::to_string(plIndex) << " place at "
					<< std::to_string(time)
					<< std::endl;
			return false;
		}
	}
	
	//transition is permitted
	for(int it : tr.inputs){//for each input place delete marker
		places[it].amount -= 1;
	}
	
	for(int it : tr.outputs) {//for each output place create new marker
		places[it].amount += 1;
	}
	
	logFile << "/////" << std::to_string(plIndex) << " place activated " << std::to_string(trIndex)
			<< " transition at time: "
			<< std::to_string(time)
			<< std::endl;
	logWriting.unlock();
	
	tr.mutex->unlock();
	std::string visName = "pl/gr" + std::to_string(time) + "By" + std::to_string(plIndex) + "trChanged" + std::to_string(trIndex) + ".png";
	visualize(visName);

	return true;
}

void Graph::addMarker(int index) {
	if(index >= places.size() || index < 0) return;
	
	places[index].amount += 1;
}

void Graph::managePlace(Place &pl, int index) {
	srand(time(nullptr) + pl.amount);
	bool reportedAsLocked = false;
	
	while(std::chrono::steady_clock::now() < startTime + simulateTime && lockedPlaces < places.size()){
		bool done = false;

		for(int trIndex : pl.outputs){
			if(transit(trIndex, index)){
				done = true;
				break;
			}
		}
		
		if(!done && !reportedAsLocked){
			logWriting.lock();
			logFile << "-----Place " << index << " didn't find permitted transition and been marked as stuck" << std::endl;
			logWriting.unlock();
			lockedPlaces += 1;
			reportedAsLocked = true;
		}
		else if(done && reportedAsLocked){
			logWriting.lock();
			logFile << "+++++Place " << index << " is no longer stuck" << std::endl;
			logWriting.unlock();
			lockedPlaces -= 1;
			reportedAsLocked = false;
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds((rand() % sleepInterval) + minSleep));
	}
}

void Graph::simulate(){
	logFile.open("pl/log.log", std::ios::app);
	
	std::vector<std::thread> threads;
	int index = 0;
	startTime = std::chrono::steady_clock::now();
	for(Place &pl : places){
		threads.emplace_back(&Graph::managePlace, this, std::ref(pl), index++);
	}
	
	for(auto &it : threads){
		it.join();
	}
	
	if(lockedPlaces == places.size()){
		logFile << "Net stuck" << std::endl;
	}
	
	logFile.close();
}
