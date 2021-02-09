#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char* filename) 
    : verts_(), faces_(), x_max(0), x_min(0), y_max(0), y_min(0) {
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

            x_max = findExtreme(v.x, 1, x_max);
            x_min = findExtreme(v.x, 0, x_min);
            y_max = findExtreme(v.y, 1, y_max);
            y_min = findExtreme(v.y, 0, y_min);

        }
        else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f;
            int itrash, idx;
            iss >> trash;   /// while loop argument needs generalizing 
            while (iss >> idx >> trash >> itrash) {  
                idx--; // in wavefront obj all indices start at 1, not zero
                f.push_back(idx);
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

float Model::findExtreme(float& testValue, const bool type, float& currentValue) {

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

float* Model::getExtremeValues(const bool which) {
    static float maxValues[2] = { x_max, y_max };
    static float minValues[2] = { x_min, y_min };
    if (which) { return maxValues; } else { return minValues; }
}