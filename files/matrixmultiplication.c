#include <stdio.h>
#include "../headers/types.h"

void printMatrix(float* M1, int rows, int columns)
{
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
      printf("%.2f ", *(M1+(r*columns) + c));
    }
    printf("\n"); // Next row
  }
}

void multiplyMatrix(float* M1, int rowsM1, int columnsM1, float* M2, int rowsM2, int columnsM2, float* result)
{

  // Variable declaration.
  int rowM1, colM1;
  int rowM2, colM2;
  float temp_result;
  int columnM1_counter, rowM2_counter;

  // For each row in M1, multiply each column in that row by each row in the corresponding column of M2.

  // For each row in M1:
  for (rowM1 = 0; rowM1 < rowsM1; rowM1++) {

    // For each column in M2:
    for (colM2 = 0; colM2 < columnsM2; colM2++) {

      temp_result = 0.0; // Reset temporal variable.

      // Multiply M1 row by that M2 column

      for (columnM1_counter = 0, rowM2_counter = 0; columnM1_counter < columnsM1; columnM1_counter++, rowM2_counter++) {

	// temp_result += M1[rowM1][columnM1_counter] * M2[rowM2_counter][colM2]; // Add to total.
	temp_result += *(M1 + (rowM1 * columnsM1) + columnM1_counter) * *(M2 + (rowM2_counter * columnsM2) + colM2);
	
      }

      // Add the result to result matrix.
      // result[rowM1][colM2] = temp_result;

      *(result + (rowM1 * columnsM2) + colM2) = temp_result; 
      
    }
    
  }
  
}

void multiplyVector4DByMatrix4X4(Vector4D* V, float* M)
{
  float temp_value = 0.0;
  float V_array[4] = {V->x, V->y, V->z, V->w}; // Create array to iterate over.
  float result[4];

  for (int row = 0; row < 4; row++) {

    temp_value = 0.0; // Reset temporal variable.

    for (int col_counter = 0; col_counter < 4; col_counter++) {

      temp_value += * (M + (row * 4) + col_counter) * V_array[col_counter];
      
    }

    result[row] = temp_value;
    
  }

  V->x = result[0];
  V->y = result[1];
  V->z = result[2];
  V->w = result[3];

}
