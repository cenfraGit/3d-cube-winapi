#include "../headers/types.h"
#include "../headers/functions.h"

void cameraMatrix(Camera camera, float* result)
{
  float translation_matrix[4][4] = {
    {1, 0, 0, -camera.position.x},
    {0, 1, 0, -camera.position.y},
    {0, 0, 1, -camera.position.z},
    {0, 0, 0, 1}
  };

  float rotation_matrix[4][4] = {
    {camera.right_v.x, camera.right_v.y, camera.right_v.z, 0},
    {camera.t.x, camera.t.y, camera.t.z, 0},
    {camera.g.x, camera.g.y, camera.g.z, 0},
    {0, 0, 0, 1}
  };

  //multiplyMatrix((float*)translation_matrix, 4, 4, (float*)rotation_matrix, 4, 4, (float*)result);
  multiplyMatrix((float*)rotation_matrix, 4, 4, (float*)translation_matrix, 4, 4, (float*)result);

}
