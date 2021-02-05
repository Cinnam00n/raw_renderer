#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"

class Model {
private:
	std::vector<Vec3f> verts_;
	std::vector<std::vector<int> > faces_;
	float x_max;
	float x_min;
	float y_max;
	float y_min;
public:
	Model(const char* filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	std::vector<int> face(int idx);
	float findExtreme(float& testValue, const bool type);
	float* getExtremeValues(const bool which);

	
};

#endif //__MODEL_H__