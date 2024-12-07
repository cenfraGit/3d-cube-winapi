
void divideByW(float* matrix, int rows, int columns, float* result)
{

  float w;
  
  for (int row = 0; row < rows; row++) {

    for (int col = 0; col < columns; col++) {

      w = * ( matrix + (3 * columns) + col );
      if (w == 0.0) {
	w = 0.001;
      }

      * ( result + (row * columns) + col ) = * ( matrix + (row * columns) + col ) / w;
      
    }
    
  }
}
