#include "lodepng.h"
#include <iostream>
#include <fstream>
using namespace std;

#ifndef	TERM_WIDTH
# define	TERM_WIDTH	1600
#endif
#ifndef	TERM_HEIGHT
# define	TERM_HEIGHT	800
#endif

void	decode(const char* filename, vector<unsigned char> &image, unsigned &width, unsigned &height) {

	unsigned	error = lodepng::decode(image, width, height, filename);

	if (error) {
		cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;
		exit(1);
	}
}

float	__calc_new_range(float old_value, float old_min, float old_max, float new_min, float new_max) {
	if (old_value == old_min)
		return(new_min);
	return (((old_value - old_min) * (new_max - new_min)) / (old_max - old_min)) + new_min;
}

void	print_ansi(int R, int G, int B, bool front) {
	cout << "\x1B["
		<< (front ? "38" : "48") << ";2;"
		<< R << ";" << G << ";" << B << "m";
	cout << " ";
	cout << "\x1B[0m";
}


void	process(vector<unsigned char> &image, unsigned &width, unsigned &height) {

	string	shadow_chars = ".,-~:;=!*#$@";

	float	image_aspect_ratio = static_cast<float>(width) / height;
	float	term_aspect_ratio = static_cast<float>(TERM_WIDTH) / TERM_HEIGHT;

	int	x_step = static_cast<int>(round(width / static_cast<float>(TERM_WIDTH)));
	int	y_step = static_cast<int>(round(height / static_cast<float>(TERM_HEIGHT)));

	int	index;

	for (int y = 0;y / y_step < TERM_HEIGHT; y += y_step) {
		for (int x = 0; x / x_step < TERM_WIDTH ; x += x_step ) {
			index = (y * width + x) * 4;
			if (index < image.size() - 2)
				print_ansi(image[index], image[index + 1], image[index + 2], 0);
		}
	}

	cout << endl;
	cout << "term_aspect_ratio: " << term_aspect_ratio << "; image_aspect_ratio: " << image_aspect_ratio
		<< "; x_step: " << x_step << "; y_step: " << y_step << endl
		<< "image.size: " << image.size() << "; width: " << width << "; height: " << height
		<< "; TERM_WIDTH: " << TERM_WIDTH << "; TERM_HEIGHT: " << TERM_HEIGHT << endl;
}

int	main(int c, char **v) {
	if (c != 2) {
		cout << "usage: ./convert [path to png file]" << endl;
		exit(1);
	}
	cout.flush();
	vector<unsigned char> image;
	unsigned width, height;

	decode(v[1], image, width, height);
	process(image, width, height);
}

