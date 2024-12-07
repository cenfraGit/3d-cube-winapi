#include "../headers/types.h"
#include "../headers/functions.h"

void change_position(Camera* camera, char v, int dir) // dir 0 forward, dir 1 backwards
{

  if (v == 'g') {
    if (dir == 0) { // forward
      camera->position.x += camera->g.x * camera->translation_speed;
      camera->position.y += camera->g.y * camera->translation_speed;
      camera->position.z += camera->g.z * camera->translation_speed;
      camera->position.w += camera->g.w * camera->translation_speed;
    } else {
      camera->position.x -= camera->g.x * camera->translation_speed;
      camera->position.y -= camera->g.y * camera->translation_speed;
      camera->position.z -= camera->g.z * camera->translation_speed;
      camera->position.w -= camera->g.w * camera->translation_speed;
    }
  }

  else if (v == 't') {
    if (dir == 0) {
      camera->position.x += camera->t.x * camera->translation_speed;
      camera->position.y += camera->t.y * camera->translation_speed;
      camera->position.z += camera->t.z * camera->translation_speed;
      camera->position.w += camera->t.w * camera->translation_speed;
    } else {
      camera->position.x -= camera->t.x * camera->translation_speed;
      camera->position.y -= camera->t.y * camera->translation_speed;
      camera->position.z -= camera->t.z * camera->translation_speed;
      camera->position.w -= camera->t.w * camera->translation_speed;
    }
  }

  else if (v == 'r') {
    if (dir == 1) {
      camera->position.x += camera->right_v.x * camera->translation_speed;
      camera->position.y += camera->right_v.y * camera->translation_speed;
      camera->position.z += camera->right_v.z * camera->translation_speed;
      camera->position.w += camera->right_v.w * camera->translation_speed;
    } else {
      camera->position.x -= camera->right_v.x * camera->translation_speed;
      camera->position.y -= camera->right_v.y * camera->translation_speed;
      camera->position.z -= camera->right_v.z * camera->translation_speed;
      camera->position.w -= camera->right_v.w * camera->translation_speed;
    }
  }  
}

void look_horizontal(Camera* camera, float rotation, float* rotation_y_matrix)
{
  rotation_y(rotation, (float*) rotation_y_matrix);
  multiplyVector4DByMatrix4X4(&(camera->g), (float*) rotation_y_matrix);
  multiplyVector4DByMatrix4X4(&(camera->t), (float*) rotation_y_matrix);
multiplyVector4DByMatrix4X4(&(camera->right_v), (float*) rotation_y_matrix);
}
