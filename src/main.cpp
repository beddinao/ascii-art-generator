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

void	print_ansi(int R, int G, int B, bool front, char ch) {
	R += 0 - (R < 0 ? R : 0);
	G += 0 - (G < 0 ? G : 0);
	B += 0 - (B < 0 ? B : 0);
	cout << "\x1B[" << (front ? "38" : "48") << ";2;"
		<< R << ";" << G << ";" << B << "m";
	if (front) {
		cout << ch;
		cout << "\x1B[0m";
	}
}

void	put_pixel(int R, int G, int B) {
	string	shadow_chars = "`.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
	//string	shadow_chars = ".,-~:;=!*#$@";
	int	medium_color = (R + G + B) / 3,
		shadow_index;

	shadow_index = __calc_new_range(medium_color, 0, 255, 0, shadow_chars.size());
	print_ansi(R - 40, G - 40, B - 40, false, ' ');
	print_ansi(R, G, B, true, shadow_chars[shadow_index]);
}


void	process(vector<unsigned char> &image, unsigned &width, unsigned &height) {
	int	x_step = static_cast<int>(round(width / static_cast<float>(TERM_WIDTH))),
		y_step = static_cast<int>(round(height / static_cast<float>(TERM_HEIGHT))),
		index;

	for (int y = 0;y / y_step < TERM_HEIGHT; y += y_step) {
		for (int x = 0; x / x_step < TERM_WIDTH && x < width ; x += x_step ) {
			index = (y * width + x) * 4;
			if (index < image.size() - 2)
				put_pixel(image[index], image[index + 1], image[index + 2]);
		}
		cout << endl;
	}

	cout << "image.pixels: " << image.size() << "; image.width: " << width << "; image.height: " << height << endl
		<< "; terminal.width: " << TERM_WIDTH << "; terminal.height: " << TERM_HEIGHT << endl;
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

