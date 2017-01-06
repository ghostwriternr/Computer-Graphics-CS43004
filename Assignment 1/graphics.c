#include <stdio.h>

int factor = 11;

void makePos(int n, int X[]) {
  int i, min;
  min = X[0];
  for (i = 1; i < n; i++) {
    if (X[i] < min) min = X[i];
  }
  if (min < 0) {
    for (i = 0; i < n; i++) {
      X[i] -= min - 1;
    }
  }
}

int findMax(int n, int X[]) {
  int i, max;
  max = X[0];
  for (i = 1; i < n; i++) {
    if (X[i] > max) max = X[i];
  }
  return max;
}

int findMin(int n, int X[]) {
  int i, min;
  min = X[0];
  for (i = 1; i < n; i++) {
    if (X[i] < min) min = X[i];
  }
  return min;
}

void scale(int n, int X[]) {
  int i;
  for (i = 0; i < n; i++) X[i] *= factor;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf(
        "\nformat : <executable> <bool(0 or 1)-for-opacity> <input file> '>' "
        "<output-svg-file-name>\n\n");
    return 1;
  }
  int n, x, y, z, i, j, k, max, min, zMin,
      toPrint =
          argv[1][0] -
          '0';  // to print is 0 for a part of the assignment and 1 for b part
  int X[100000], Y[100000], Z[100000];
  float opacity = 1.0;
  FILE *infile;
  infile = fopen(argv[2], "r");  // read data from file
  if (infile != NULL) {
    fscanf(infile, "%d", &n);
    for (i = 0; i < n; i++) {
      fscanf(infile, "%d%d%d", &X[i], &j, &k);
      Y[i] = -j;
      Z[i] = k >= 0 ? k : -k;
    }
  }
  fclose(infile);

  // make x,y coordinates +ve
  makePos(n, X);
  makePos(n, Y);

  scale(n, X);
  scale(n, Y);

  x = findMax(n, X);
  x -= findMin(n, X);
  y = findMax(n, Y);
  y -= findMin(n, Y);
  z = findMax(n, Z);

  // calculate neede value to assign color to squares, according to their depths
  zMin = findMin(n, Z);
  z -= zMin;

  // ouptut in svg format
  char head[] = {"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"};
  char rectX[] = {"<rect x=\""}, rectY[] = {"\" y=\""},
       rectRestWhite[] = {
           "\" width=\"11\" height=\"11\" "
           "style=\"fill:white;stroke:white;stroke-width:0;fill-opacity:"};
  char afterOpacity1[] = {";stroke-opacity:"}, afterOpacity2[] = {"\"/>"};
  char end[] = {"</svg>"};

  printf("%s\n", head);

  // draw background square
  printf("%s", rectX);
  printf("%d", 0);
  printf("%s", rectY);
  printf("%d", 0);
  printf(
      "\" width=\"%d\" height=\"%d\" "
      "style=\"fill:black;stroke:black;stroke-width:0;fill-opacity:",
      x + 30, y + 30);
  printf("%f", 1.0);
  printf("%s", afterOpacity1);
  printf("1");
  printf("%s\n", afterOpacity2);

  // draw suares according to given data
  for (i = 0; i < n; i++) {
    printf("%s", rectX);
    printf("%d", X[i]);
    printf("%s", rectY);
    printf("%d", Y[i]);
    printf("%s", rectRestWhite);

    if (toPrint) opacity = ((float)(Z[i] - zMin)) / z;

    printf("%f", opacity);
    printf("%s", afterOpacity1);
    printf("%f", opacity);
    printf("%s\n", afterOpacity2);
  }

  printf("%s\n", end);

  return 0;
}