#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <ctime>
#include <cstdlib>
#include "CImg/CImg.h"


using namespace std;
using namespace cimg_library;

vector<float> Vectorizar(string filename, int cuts=3)
{
    vector<float> R;
    CImg<float> img(filename.c_str());
    CImg<float> img2 = img.haar(false, cuts);

    cimg_forXY(img2, x, y) 
    { 
        R.push_back((img(x, y, 0) + img(x, y, 1) +  img(x, y, 2)) / 3);
    }
    return R;
}


void makeSample(string filename, float per) {
    ifstream infile(filename);
    string line;
    map <string, vector<string>> pop;
    map <string, vector<string>> sample;
    while (getline(infile, line)) {
        stringstream tokens(line); 
        string token;
        getline(tokens, token, '/');
        getline(tokens, token, '/');
        pop[token].push_back(line);
    }
    map<string, vector<string>>::iterator it = pop.begin();
    for (; it != pop.end(); it++) {
        int n = (*it).second.size();
        for(int  i = 0; i < n*per; i++ ) {
            int j = rand() % n;
            sample[(*it).first].push_back((*it).second[j]);
        }
    }
    ofstream fileout("sample.txt", ios::trunc);

    it = sample.begin();
    for (; it != sample.end(); it++) {
        auto caract = (*it).second;
        for (auto c:caract) {
            fileout << c << endl;
        }
    }


    infile.close();
    fileout.close();

}

