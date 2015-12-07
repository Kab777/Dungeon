#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include "controller.h"
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	string filename = "Default.txt";
	if ((argc - 1) == 1) {
		 srand(time(NULL));
		filename = argv[1];
	}else if((argc -1) == 2){
		filename = argv[1];
		string temp = argv[2];
		istringstream ss(temp);
		unsigned int i;
		ss >> i;
		srand(i);
	}else{
		srand(time(NULL));
	}
	Controller c = Controller(filename);
	c.play();
}

