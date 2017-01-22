#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  int n, i, x, y, z;
  vector<int> X, Y, Z;
  const array<array<int, 3>, 8> dirs = {{{-1, -1, 1},
                                         {-1, 1, 1},
                                         {1, 1, 1},
                                         {1, -1, 1},
                                         {-1, -1, -1},
                                         {-1, 1, -1},
                                         {1, 1, -1},
                                         {1, -1, -1}}};
  FILE* infile;
  FILE* outfile;
  infile = fopen(argv[1], "r");
  outfile = fopen(argv[2], "w");
  if (infile != NULL) {
    fscanf(infile, "%d", &n);
    for (i = 0; i < n; i++) {
      fscanf(infile, "%d%d%d", &x, &y, &z);
      X.emplace_back(x);
      Y.emplace_back(y);
      Z.emplace_back(z);
    }
  }
  vector<pair<double, pair<double, double>>> vertices;
  vector<array<int, 4>> faces;
  for (int i = 0; i < n; ++i) {
    for (const array<int, 3>& dir : dirs) {
      pair<double, pair<double, double>> next_vertex =
          make_pair(X[i] + 0.5 * dir[0],
                    make_pair(Y[i] + 0.5 * dir[1], Z[i] + 0.5 * dir[2]));
      vertices.emplace_back(next_vertex);
    }
    auto it = vertices.end();
    array<int, 4> next_face;
    int a, b, c, d;
    a = distance(vertices.begin(), vertices.end() - 4),
    b = distance(vertices.begin(), vertices.end() - 5),
    c = distance(vertices.begin(), vertices.end() - 6),
    d = distance(vertices.begin(), vertices.end() - 7);
    next_face = {a, b, c, d};
    faces.push_back(next_face);
    a = distance(vertices.begin(), vertices.end() - 7),
    b = distance(vertices.begin(), vertices.end() - 6),
    c = distance(vertices.begin(), vertices.end() - 2),
    d = distance(vertices.begin(), vertices.end() - 3);
    next_face = {a, b, c, d};
    faces.push_back(next_face);
    a = distance(vertices.begin(), vertices.end() - 1),
    b = distance(vertices.begin(), vertices.end() - 2),
    c = distance(vertices.begin(), vertices.end() - 6),
    d = distance(vertices.begin(), vertices.end() - 5);
    next_face = {a, b, c, d};
    faces.push_back(next_face);
    a = distance(vertices.begin(), vertices.end() - 4),
    b = distance(vertices.begin(), vertices.end()),
    c = distance(vertices.begin(), vertices.end() - 1),
    d = distance(vertices.begin(), vertices.end() - 5);
    next_face = {a, b, c, d};
    faces.push_back(next_face);
    a = distance(vertices.begin(), vertices.end() - 3),
    b = distance(vertices.begin(), vertices.end()),
    c = distance(vertices.begin(), vertices.end() - 4),
    d = distance(vertices.begin(), vertices.end() - 7);
    next_face = {a, b, c, d};
    faces.push_back(next_face);
    a = distance(vertices.begin(), vertices.end() - 3),
    b = distance(vertices.begin(), vertices.end() - 2),
    c = distance(vertices.begin(), vertices.end() - 1),
    d = distance(vertices.begin(), vertices.end());
    next_face = {a, b, c, d};
    faces.push_back(next_face);
  }
  if (outfile != NULL) {
  	fprintf(outfile, "mtllib color.mtl\n");
    for (auto& v : vertices) {
      fprintf(outfile, "v %f %f %f\n", v.first, v.second.first,
              v.second.second);
    }
    fprintf(outfile, "\nusemtl xy\n\n");
    for (auto& f : faces) {
      fprintf(outfile, "f %d %d %d %d\n", f[0], f[1], f[2], f[3]);
    }
  }
  return 0;
}