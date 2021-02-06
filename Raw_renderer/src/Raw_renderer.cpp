#include <iostream>
#include "tgaimage.h"
#include "geometry.h"
#include "model.h"

TGAColor white = TGAColor(255, 255, 255, 255);
TGAColor red = TGAColor(255, 0, 0, 255);
// sample change again
Model* model = NULL;
const int width = 800;
const int height = 800;

void line (int x0, int y0, int x1, int y1, TGAImage &image, TGAColor &color)
{
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	for (int x = x0; x < x1; x++) {
		float t = (x-x0)/(float)(x1-x0);
		int y = y0 * (1. - t) + y1 * t;
		if (steep) {
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color); 
		}
	}
}

void draw(const unsigned int width, const unsigned int height, const unsigned int bpp) {
	// preparing to abstract draw function
}

int main(int argc, char** argv) {

	std::string obj_name = "testsphere_r1_transposed";

	if (2 == argc) {
		model = new Model(argv[1],1,1);
	}
	else {	
		model = new Model(("obj/"+obj_name+".obj").c_str(),1,1); // get a wireframe file
	}

	TGAImage image(width, height, TGAImage::RGB);
	for (int i = 0; i < model->nfaces(); i++) {
		std::vector<int> face = model->face(i);
		for (int j = 0; j < 3; j++) {
			Vec3f v0 = model->vert(face[j]);
			Vec3f v1 = model->vert(face[(j + 1) % 3]);

			int x0 = (v0.x + 1.) * width / 2.;
			int y0 = (v0.y + 1.) * height / 2.;
			int x1 = (v1.x + 1.) * width / 2.;
			int y1 = (v1.y + 1.) * height / 2.;

			line(x0, y0, x1, y1, image, white);
		}

	}

	image.flip_vertically();

	std::string file_name = obj_name+".tga";

	image.write_tga_file(file_name.c_str());
	delete model;
	return 0;
}
