#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"

class Model {
private:
	std::vector<Vec3f> verts_;
	std::vector<std::vector<int> > faces_;

public:
	float xMax_;
	float xMin_;
	float yMax_;
	float yMin_;
	Model(const char* filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	float findExtreme(const float& testValue, const bool type, float& currentValue) const;
	std::vector<int> face(int idx);
	float* getExtremeValues(const bool which) const;

	
};

#endif //__MODEL_H__