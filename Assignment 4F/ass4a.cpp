#include <bits/stdc++.h>

using namespace std;

/* Structure to store xyz co-ordinates */
struct coordinate {
  double x;
  double y;
  double z;

  bool operator==(const coordinate& other) const {
    return (x == other.x && y == other.y && z == other.z);
  }
};

/* Custom hash function for struct coordinate */
struct coordinateHasher {
  std::size_t operator()(const coordinate& k) const {
    using std::size_t;
    using std::hash;
    using std::string;

    return ((hash<double>()(k.x) ^ (hash<double>()(k.y) << 1)) >> 1) ^
           (hash<double>()(k.z) << 1);
  }
};

int main(int argc, char** argv) {
  double a, b, c;
  int p, q, r, s;
  char t;
  string line;
  vector<coordinate> vertices, intermediate_vertices, final_vertices;
  vector<array<int, 4>> faces;
  ifstream infile(argv[1]);

  // Read from file
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

  // Processing
  unordered_map<coordinate, int, coordinateHasher> original_vertices,
      duplicate_vertices_count;
  unordered_map<int, int> duplicate_vertices;
  int j = 1;
  for (int i = 0; i < vertices.size(); ++i) {
    auto vertices_it = original_vertices.find(vertices[i]);
    if (vertices_it == original_vertices.end()) {
      original_vertices[vertices[i]] = j;
      duplicate_vertices[i + 1] = j;
      j++;
      intermediate_vertices.emplace_back(vertices[i]);
      duplicate_vertices_count[vertices[i]] = 1;
    } else {
      duplicate_vertices[i + 1] = vertices_it->second;
      ++duplicate_vertices_count[vertices[i]];
    }
  }

  for (auto& f : faces) {
    for (auto& value : f) {
      auto duplicate_vertices_it = duplicate_vertices.find(value);
      if (duplicate_vertices_it != duplicate_vertices.end()) {
        value = duplicate_vertices_it->second;
      }
    }
  }

  // Mark faces to remove
  set<array<int, 4>> unique_faces, duplicate_faces;
  vector<array<int, 4>> final_faces, removed_faces;
  for (int i = 0; i < faces.size(); ++i) {
    array<int, 4> temp_arr = faces[i];
    sort(temp_arr.begin(), temp_arr.end());
    auto it = unique_faces.find(temp_arr);
    if (it == unique_faces.end()) {
      unique_faces.insert(temp_arr);
      final_faces.push_back(faces[i]);
    } else {
      duplicate_faces.insert(temp_arr);
      removed_faces.push_back(faces[i]);
    }
  }

  // Create intermediate .obj file
  FILE* outfile;
  outfile = fopen(argv[2], "w");
  if (outfile != NULL) {
    fprintf(outfile, "mtllib color.mtl\n");
    for (auto& v : intermediate_vertices) {
      fprintf(outfile, "v %f %f %f\n", v.x, v.y, v.z);
    }
    fprintf(outfile, "\nusemtl white\n\n");
    for (auto& f : final_faces) {
      fprintf(outfile, "f %d %d %d %d\n", f[0], f[1], f[2], f[3]);
    }
    fprintf(outfile, "\nusemtl red\n\n");
    for (auto& f : removed_faces) {
      fprintf(outfile, "f %d %d %d %d\n", f[0], f[1], f[2], f[3]);
    }
  }
  fclose(outfile);

  // Remove repeated faces
  for (int i = 0; i < final_faces.size();) {
    array<int, 4> temp_arr = final_faces[i];
    sort(temp_arr.begin(), temp_arr.end());
    auto it = duplicate_faces.find(temp_arr);
    if (it != duplicate_faces.end()) {
      final_faces.erase(final_faces.begin() + i);
    } else {
      ++i;
    }
  }

  // Remove interior vertices
  duplicate_vertices.clear();
  j = 1;
  for (int i = 0; i < intermediate_vertices.size(); ++i) {
    auto duplicate_vertices_count_it =
        duplicate_vertices_count.find(intermediate_vertices[i]);
    if (duplicate_vertices_count_it->second != 8) {
      final_vertices.push_back(intermediate_vertices[i]);
      duplicate_vertices[i + 1] = j;
      j++;
    }
  }

  cout << final_vertices.size() << endl;

  for (auto& f : final_faces) {
    for (auto& value : f) {
      auto duplicate_vertices_it = duplicate_vertices.find(value);
      if (duplicate_vertices_it != duplicate_vertices.end()) {
        value = duplicate_vertices_it->second;
      }
    }
  }

  unique_faces.clear(), duplicate_faces.clear();
  vector<array<int, 4>> total_faces;
  for (int i = 0; i < final_faces.size(); ++i) {
    array<int, 4> temp_arr = final_faces[i];
    sort(temp_arr.begin(), temp_arr.end());
    auto it = unique_faces.find(temp_arr);
    if (it == unique_faces.end()) {
      unique_faces.insert(temp_arr);
      total_faces.push_back(final_faces[i]);
    } else {
      duplicate_faces.insert(temp_arr);
    }
  }

  // Create final .obj file
  outfile = fopen(argv[3], "w");
  if (outfile != NULL) {
    fprintf(outfile, "mtllib color.mtl\n");
    for (auto& v : final_vertices) {
      fprintf(outfile, "v %f %f %f\n", v.x, v.y, v.z);
    }
    fprintf(outfile, "\nusemtl white\n\n");
    for (auto& f : total_faces) {
      fprintf(outfile, "f %d %d %d %d\n", f[0], f[1], f[2], f[3]);
    }
  }
  return 0;
}