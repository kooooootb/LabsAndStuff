#include <iostream>
#include "Graph.h"

void clearLogs(){
#if defined(unix) || defined(__unix__) || defined(__unix)
	system("rm pl/*")
	system("rm dots/*")
#endif
#ifdef _WIN32
	system("del /q pl\\*");
	system("del /q dots\\*");
#endif
}

int main() {
	clearLogs();
	
	Graph graph("graph.txt", "inputParameters.txt");
//	Graph graph("aliveGraph.txt", "aliveParams.txt");

	graph.simulate();

	std::string fname = "graphFinal.png";
	graph.visualize(fname);
	return 0;
}
