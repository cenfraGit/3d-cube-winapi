

void viewportMatrix(int width, int height, float* result)
{
  float viewport_matrix[4][4] = {
    {width/2, 0, 0, width/2},
    {0, height/2, 0, height/2},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };

  // Copy matrix to result.
  for (int row = 0; row < 4; row++) {

    for (int col = 0; col < 4; col++) {

      * ( result + (row * 4) + col ) = viewport_matrix[row][col];
      
    }
    
  }
  
}
