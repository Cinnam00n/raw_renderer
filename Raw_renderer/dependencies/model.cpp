#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "model.h"

Model::Model(const char* filename) 
    : verts_(), faces_(), xMax_(0), xMin_(0), yMax_(0), yMin_(0) {
    std::ifstream in;                                           //initialize input file stream
    in.open(filename, std::ifstream::in);                       // open file
    if (in.fail()) {
        std::cerr << "Failed to load file!" << std::endl;
        exit(1);
    }

    std::string line;

    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i = 0;i < 3;i++) iss >> v.raw[i];
            verts_.push_back(v); 

            xMax_ = findExtreme(v.x, 1, xMax_);
            xMin_ = findExtreme(v.x, 0, xMin_);
            yMax_ = findExtreme(v.y, 1, yMax_);
            yMin_ = findExtreme(v.y, 0, yMin_);

        }
        else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f;
            int itrash, idx;
            iss >> trash; 

            std::string currentStr = iss.str();
            currentStr = currentStr.erase(0, currentStr.find_first_of(" ", 0) + 1);
            int whitespacePosition = currentStr.find_first_of(" ", 0);
           
            int slashCount = 0;

            for (int i = 0; i < whitespacePosition; i++)
                if (currentStr[i] == '/') slashCount++;

            switch (slashCount) {

            case 0 :
                while (iss >> idx) {
                    idx--; // in wavefront obj all indices start at 1, not zero
                    f.push_back(idx);
                }
            case 1:
                while (iss >> idx >> trash >> itrash) {
                    idx--; // in wavefront obj all indices start at 1, not zero
                    f.push_back(idx);
                }
            case 2:
                while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                    idx--; // in wavefront obj all indices start at 1, not zero
                    f.push_back(idx);
                }
            }

            faces_.push_back(f);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;

    float* max;
    float* min;

    max = getExtremeValues(1);
    min = getExtremeValues(0);

    std::cout << "Max values: " << *max << ", " << *(max + 1) << std::endl;
    std::cout << "Min values: " << *min << ", " << *(min + 1) << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

std::vector<int> Model::face(int idx) {
    return faces_[idx];
}

Vec3f Model::vert(int i) {
    return verts_[i];
}

float Model::findExtreme(const float& testValue, const bool type, float& currentValue) const {

    float result = 0;

    if (type) {
        result = (testValue > currentValue) ? testValue : currentValue;
    }
    else
    {
        result = (testValue < currentValue) ? testValue : currentValue;
    }
    return result;
}

float* Model::getExtremeValues(const bool which) const {
    static float maxValues[2] = { xMax_, yMax_ };
    static float minValues[2] = { xMin_, yMin_ };
    if (which) { return maxValues; } else { return minValues; }
}