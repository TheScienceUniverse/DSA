#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[]) {
	if (argc < 4) {
		perror ("Not enough argument!");
		return EXIT_FAILURE;
	}

	printf ("Shield :=>\n");

	char* name = argv [1];

	char* property = argv [2];
	int len_1 = strlen (property);
	char* value = argv [3];
	int len_2 = strlen (value);

	printf ("property = %s (%u)\n", property, len_1);
	printf ("value = %s (%u)\n", value, len_2);

	// 1em = 12pt = 16px
	int font_height = 10;
	int font_width = (font_height * 3) / 5;

	printf ("h = %dpx, w = %dpx\n", font_height, font_width);

	int box_height = 2 * font_height;
	int box_1_width = (len_1 + 2) * font_width;
	int box_2_width = (len_2 + 2) * font_width;
	int box_width = box_1_width + box_2_width;

	printf ("Box_1 (%dpx/%dpx), Box_2 (%dpx/%dpx)\n", box_height, box_1_width, box_height, box_2_width);

	char* box_1_color = "#555555";
	char* box_2_color = "#90e59a";

	FILE* file = fopen (name, "wb");

	if (NULL == file) {
		perror ("Error opening memory file!");
		return EXIT_FAILURE;
	}

	size_t w_size __attribute__((__unused__));	// written size BYTES

w_size = fprintf (file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?> \
\n<svg\
\n	xmlns=\"http://www.w3.org/2000/svg\"\
\n	version=\"1.1\"\
\n	baseprofile=\"full\"");

w_size = fprintf (file, "\n	width=\"%d\" height=\"%d\"", box_width, box_height);
w_size = fprintf (file, "\n	viewBox=\"0 0 %d %d\"", box_width, box_height);

w_size = fprintf (file, "\n	style=\"border-radius:0px; border-radius: %dpx\"", box_height / 4);

w_size = fprintf (file, "\n>\
\n	<defs>\
\n		<style type=\"text/css\">\
\n			@font-face {\
\n				font-family: \"Droid Sans Mono\";\
\n				src: url('../font/Droid_Sans_Mono/DroidSansMono.ttf') format(\"truetype\");\
\n			}\
\n		</style>\
\n	</defs>\
\n	<title>Shield</title>\
\n	<g\
\n		id=\"text-fields\"\
\n		shape-rendering=\"crispEdges\"\
\n		font-family=\"Droid Sans Mono, monospace\"\
\n		font-weight=\"bold\"\
\n		text-rendering=\"geometricPrecision\"\
\n		dominant-baseline=\"middle\"\
\n		text-anchor=\"middle\"");

w_size = fprintf (file, "\n		font-size=\"%dpx\"", font_height + 1);

w_size = fprintf (file, "\n	>\
\n		<g id=\"Part_1\">");

w_size = fprintf (file, "\n			<rect x=\"%d\" width=\"%d\" height=\"%d\" fill=\"%s\"/>", 0, box_1_width, box_height, box_1_color);
w_size = fprintf (file, "\n			<text fill=\"white\" x=\"%f\" y=\"52.5%%\">%s</text>", (float) box_1_width / 2, property);

w_size = fprintf (file, "\n		</g>\
\n		<g id=\"Part_2\">");

w_size = fprintf (file, "\n			<rect x=\"%d\" width=\"%d\" height=\"%d\" fill=\"%s\"/>", box_1_width, box_2_width, box_height, box_2_color);
w_size = fprintf (file, "\n			<text fill=\"black\" x=\"%f\" y=\"52.5%%\">%s</text>", box_1_width + (float) box_2_width / 2, value);

w_size = fprintf (file, "\n		</g>\
\n	</g>\
\n</svg>\n");

	fclose (file);

	return EXIT_SUCCESS;
}
