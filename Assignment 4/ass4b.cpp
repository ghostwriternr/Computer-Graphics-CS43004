#include <bits/stdc++.h>

using namespace std;

struct coordinate {
  double x;
  double y;
  double z;
};

coordinate CalculateSurfaceNormal(vector<coordinate> points) {
  coordinate normal = {0, 0, 0};
  coordinate current, next;
  for (int i = 0; i < 4; ++i) {
    current = points[i];
    next = points[(i + 1) % 4];

    normal.x += ((current.y - next.y) * (current.z + next.z));
    normal.y += ((current.z - next.z) * (current.x + next.x));
    normal.z += ((current.x - next.x) * (current.y + next.y));
  }

  double denom =
      sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

  normal.x /= denom;
  normal.y /= denom;
  normal.z /= denom;

  return normal;
}

bool toRemove(coordinate face_normal, coordinate camera_vector) {
  double dotProd = face_normal.x * camera_vector.x +
                   face_normal.y * camera_vector.y +
                   face_normal.z * camera_vector.z;
  return (dotProd > 0);
}

int main(int argc, char** argv) {
  double a, b, c;
  int p, q, r, s;
  char t;
  string line;
  double vx, vy, vz;
  vector<coordinate> vertices;
  vector<vector<int>> faces, final_faces;
  ifstream infile(argv[1]);
  while (getline(infile, line)) {
    istringstream iss(line);
    if (iss.str()[0] == 'v') {
      if (!(iss >> t >> a >> b >> c)) {
        cout << "Error parsing\n";
      }
      coordinate coo;
      coo.x = a;
      coo.y = b;
      coo.z = c;
      vertices.emplace_back(coo);
    } else if (iss.str()[0] == 'f') {
      if (!(iss >> t >> p >> q >> r >> s)) {
        cout << "Error parsing\n";
      }
      faces.push_back({p, q, r, s});
    }
  }
  cin >> vx >> vy >> vz;
  for (auto& f : faces) {
    vector<coordinate> face_vertices;
    coordinate face_mp = {0, 0, 0};
    face_mp.x += vertices[f[0] - 1].x;
    face_mp.x += vertices[f[2] - 1].x;
    face_mp.y += vertices[f[0] - 1].y;
    face_mp.y += vertices[f[2] - 1].y;
    face_mp.z += vertices[f[0] - 1].z;
    face_mp.z += vertices[f[2] - 1].z;
    for (auto& p : f) {
      face_vertices.push_back(vertices[p - 1]);
    }
    face_mp.x /= 2;
    face_mp.y /= 2;
    face_mp.z /= 2;
    coordinate face_normal = CalculateSurfaceNormal(face_vertices);
    coordinate camera_vector = {face_mp.x - vx, face_mp.y - vy, face_mp.z - vz};
    double denom = sqrt(camera_vector.x * camera_vector.x +
                        camera_vector.y * camera_vector.y +
                        camera_vector.z * camera_vector.z);
    camera_vector.x /= denom;
    camera_vector.y /= denom;
    camera_vector.z /= denom;
    bool isBehind = toRemove(face_normal, camera_vector);
    if (!isBehind) {
      final_faces.push_back(f);
    }
  }
  FILE* outfile;
  outfile = fopen(argv[2], "w");
  if (outfile != NULL) {
    fprintf(outfile, "mtllib color.mtl\n");
    for (auto& v : vertices) {
      fprintf(outfile, "v %f %f %f\n", v.x, v.y, v.z);
    }
    fprintf(outfile, "\nusemtl xy\n\n");
    for (auto& f : final_faces) {
      fprintf(outfile, "f %d %d %d %d\n", f[0], f[1], f[2], f[3]);
    }
  }
  return 0;
}