#include "Color.h"
#include "ReadWritePPM.h"

int main() {

	COLOR_TBL atblFocus;
	read(atblFocus, "lena.ppm");
	write("output.ppm", atblFocus);
	return(0);

}