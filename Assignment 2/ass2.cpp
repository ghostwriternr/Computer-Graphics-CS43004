#include <bits/stdc++.h>

using namespace std;

int factor = 9;

// Converts hexcode in string format to RGB
void hexcodeToRGB(float& fR, float& fG, float& fB, string hexcode) {
  string channels[3];
  vector<int> vals;
  channels[0] = hexcode.substr(1, 2);
  channels[1] = hexcode.substr(3, 2);
  channels[2] = hexcode.substr(5, 2);
  for (const auto& s : channels) {
    std::stringstream str;
    str << s;
    int value;
    str >> std::hex >> value;
    vals.push_back(value);
  }
  fR = vals[0];
  fG = vals[1];
  fB = vals[2];
}

// Converts decimal to hexadecimal
string DecimalToHexa(float fC) {
  std::stringstream ss;
  ss << std::hex << int(fC);
  std::string res(ss.str());
  if (res.length() == 1) res += '0';
  return (res);
}

// Converts RGB to Hexcode
const char* RGBToHexcode(float fR, float fG, float fB) {
  string ret = "#";
  ret += DecimalToHexa(fR);
  ret += DecimalToHexa(fG);
  ret += DecimalToHexa(fB);
  return ret.c_str();
}

// Converts RGB to HSV model
void RGBtoHSV(float& fR, float& fG, float& fB, float& fH, float& fS,
              float& fV) {
  float fCMax = max(max(fR, fG), fB);
  float fCMin = min(min(fR, fG), fB);
  float fDelta = fCMax - fCMin;

  if (fDelta > 0) {
    if (fCMax == fR) {
      fH = 60 * (fmod(((fG - fB) / fDelta), 6));
    } else if (fCMax == fG) {
      fH = 60 * (((fB - fR) / fDelta) + 2);
    } else if (fCMax == fB) {
      fH = 60 * (((fR - fG) / fDelta) + 4);
    }

    if (fCMax > 0) {
      fS = fDelta / fCMax;
    } else {
      fS = 0;
    }

    fV = fCMax;
  } else {
    fH = 0;
    fS = 0;
    fV = fCMax;
  }

  if (fH < 0) {
    fH = 360 + fH;
  }
}

// Converts HSV to RGB model
void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS,
              float& fV) {
  float fC = fV * fS;
  float fHPrime = fmod(fH / 60.0, 6);
  float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
  float fM = fV - fC;

  if (0 <= fHPrime && fHPrime < 1) {
    fR = fC;
    fG = fX;
    fB = 0;
  } else if (1 <= fHPrime && fHPrime < 2) {
    fR = fX;
    fG = fC;
    fB = 0;
  } else if (2 <= fHPrime && fHPrime < 3) {
    fR = 0;
    fG = fC;
    fB = fX;
  } else if (3 <= fHPrime && fHPrime < 4) {
    fR = 0;
    fG = fX;
    fB = fC;
  } else if (4 <= fHPrime && fHPrime < 5) {
    fR = fX;
    fG = 0;
    fB = fC;
  } else if (5 <= fHPrime && fHPrime < 6) {
    fR = fC;
    fG = 0;
    fB = fX;
  } else {
    fR = 0;
    fG = 0;
    fB = 0;
  }

  fR += fM;
  fG += fM;
  fB += fM;
}

// Reset initial positions on given axis to 0
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

// Find maximum value in array
int findMax(int n, int X[]) {
  int i, max;
  max = X[0];
  for (i = 1; i < n; i++) {
    if (X[i] > max) max = X[i];
  }
  return max;
}

// Find minimum value in array
int findMin(int n, int X[]) {
  int i, min;
  min = X[0];
  for (i = 1; i < n; i++) {
    if (X[i] < min) min = X[i];
  }
  return min;
}

// Scale the array elements by 'factor'
void scale(int n, int X[]) {
  int i;
  for (i = 0; i < n; i++) X[i] *= factor;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    printf(
        "\nformat : <executable> <bool(0 or 1)-for-opacity> <input file> '>' "
        "<output-svg-file-name>\n\n");
    return 1;
  }
  string hexcode;
  cin >> hexcode;
  int n, x, y, z, i, j, k, max, min, zMin,
      toPrint =
          argv[1][0] -
          '0';  // to print is 0 for a part of the assignment and 1 for b part
  float fR = 0, fG = 0, fB = 0, fH = 0, fS = 0, fV = 0;
  if (hexcode.length() != 7 || hexcode[0] != '#') {
    return 1;
  }
  hexcodeToRGB(fR, fG, fB, hexcode);
  RGBtoHSV(fR, fG, fB, fH, fS, fV);
  int X[100000], Y[100000], Z[100000];
  float D[100000];
  float opacity = 1.0;
  FILE* infile;
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

  vector<pair<int, pair<int, int> > > dim;
  dim.resize(n);
  for (int i = 0; i < n; ++i) {
    dim[i].first = Z[i];
    dim[i].second.first = Y[i];
    dim[i].second.second = X[i];
  }

  sort(dim.begin(), dim.end());
  // reverse(dim.begin(), dim.end());

  for (int i = 0; i < n; ++i) {
    Y[i] = dim[i].second.first;
    X[i] = dim[i].second.second;
    Z[i] = dim[i].first;
  }

  for (int i = 0; i < n; ++i) {
    D[i] = Z[i] - zMin;
  }

  for (int i = 0; i < n; ++i) {
    D[i] = (float)((float)(D[i] / z) * fV);
  }

  // ouptut in svg format
  char head[] = {"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"};
  char rectX[] = {"<rect x=\""}, rectY[] = {"\" y=\""},
       rectRest[] = {
           "\" width=\"9\" height=\"9\" "
           "style=\"stroke:white;stroke-width:0;fill:"};
  char fillOp[] = {";fill-opacity:"};
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
    printf("%s", rectRest);

    if (toPrint) opacity = ((float)(Z[i] - zMin)) / z;

    // printf("%f", opacity);
    HSVtoRGB(fR, fG, fB, fH, fS, D[i]);
    cout << RGBToHexcode(fR, fG, fB);
    printf("%s", fillOp);
    printf("%f", 1.0);
    printf("%s", afterOpacity1);
    printf("%f", opacity);
    printf("%s\n", afterOpacity2);
  }

  printf("%s\n", end);

  return 0;
}