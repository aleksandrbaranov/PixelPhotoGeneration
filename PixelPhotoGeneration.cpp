#include<algorithm>
#include<iostream>
#include<array>
#include<ctime>
#include<string>
#include"CImg.h"

using namespace std;

typedef array<array<bool, 5>,5> photo;

void transposing(photo& data) {

	photo tmp = {};

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			tmp[j][i] = data[i][j];
		}
	}

	data = tmp;
}

photo generation() {
	photo output = {};
	array<array<bool, 5>, 2>columns;
	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			columns[i][j] = rand() % 2;
		}
	}

	output[0] = columns[0];
	output[1] = columns[1];

	for (int i = 0; i < 5; i++) output[2][i] = rand() % 2;

	output[3] = columns[1];
	output[4] = columns[0];

	transposing(output);

	return output;
}

void create_avatar(const string& path) {

	auto photo = generation();

	cimg_library::CImg<unsigned char>img(50 * 5, 50 * 5, 1, 3);

	unsigned char color[3] = { rand() % 256, rand() % 256, rand() % 256 };
	unsigned char back[3] = { 255,255,255 };

	img.draw_rectangle(0, 0, 50 * 5, 50 * 5, back);

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (photo[j][i]) img.draw_rectangle(50 * i, 50 * j, 50 * i + 50, 50 * j + 50, color);

	img.save(path.c_str());
}

int main() {

	srand(time(0));

	for (int i = 0; i < 10; i++) {
		create_avatar(to_string(i) + ".bmp");
	}

	return 0;
}


