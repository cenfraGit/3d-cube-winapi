#include <math.h>

void rotation_x(float a, float* result)
{
  float rotation_x_matrix[4][4] = {
    {1, 0, 0, 0},
    {0, cos(a), -sin(a), 0},
    {0, sin(a), cos(a), 0},
    {0, 0, 0, 1}
  };

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      * ( result + (row * 4) + col ) = rotation_x_matrix[row][col]; 
    }
  }   
}

void rotation_y(float a, float* result)
{
  float rotation_y_matrix[4][4] = {
    {cos(a), 0, sin(a), 0},
    {0, 1, 0, 0},
    {-sin(a), 0, cos(a), 0},
    {0, 0, 0, 1}
  };

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      * ( result + (row * 4) + col ) = rotation_y_matrix[row][col]; 
    }
  }   
}

void rotation_z(float a, float* result)
{
  float rotation_z_matrix[4][4] = {
    {cos(a), -sin(a), 0, 0},
    {sin(a), cos(a), 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      * ( result + (row * 4) + col ) = rotation_z_matrix[row][col]; 
    }
  }   
}
