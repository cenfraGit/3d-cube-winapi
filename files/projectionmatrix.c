#include <math.h>
#include "../headers/types.h"

void projectionMatrix(Camera camera, float* result)
{
  float n, f, r, l, t, b;
  float m11, m13, m22, m23, m33, m34;

  n = camera.near_plane_distance;
  f = camera.far_plane_distance;
  r = tan(camera.x_fov / 2);
  l = -r;
  t = tan(camera.y_fov / 2);
  b = -t;

  m11 = (2 * n) / (r - l);
  m13 = (r + l) / (r - l);
  m22 = -(2 * n) / (t - b);
  m23 = (t + b) / (t - b);
  m33 = f / (f - n);
  m34 = -(f + n) / (f - n);

  float projection_matrix[4][4] = {
    {m11, 0, m13, 0},
    {0, m22, m23, 0},
    {0, 0, m33, m34},
    {0, 0, 1, 0}
  };

  // Copy projection matrix to result.
  for (int row = 0; row < 4; row++) {

    for (int col = 0; col < 4; col++) {

      * ( result + (row * 4) + col ) = projection_matrix[row][col];
      
    }

  }
  
  
}
