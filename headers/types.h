typedef struct {
  float x, y, z;
} Vector3D;

typedef struct {
  float x, y, z, w;
} Vector4D;

//typedef float M4X4[4][4];

//void Mult4X4(M4X4 M1, M4X4 M2, M4X4 result);

typedef struct {
  Vector4D position;
  float x_fov;
  float y_fov;
  float near_plane_distance;
  float far_plane_distance;
  Vector4D g;
  Vector4D t;
  Vector4D right_v;
  float translation_speed;
  float rotation_speed;
} Camera;
