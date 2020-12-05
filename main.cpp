#include "VantagePointTree.h"
#include "vectorizar.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>

using namespace std;

double dist (vector<float> a, vector<float> b) {
	double sum = 0;
	for (int i = 0; i < a.size(); ++i) {
		double x = pow(a[i] - b[i], 2);
		sum += x;
	}

	return pow(sum, 1/2);
}

int main () {
    ifstream infile("sample.txt");
    string path;
    vector<vector<float>> myPoints;

    while(getline(infile, path)) {
        auto carac = Vectorizar(path);
        myPoints.push_back(carac);
    }

	VantagePointTree<vector<float>> vpt(myPoints, dist);
	

	return 0;
}
