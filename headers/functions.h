
void cameraMatrix(Camera camera, float* result);
void projectionMatrix(Camera camera, float* result);

Vector3D Cross3D(Vector3D v1, Vector3D v2);

float Dot3D(Vector3D v1, Vector3D v2);
float Dot4D(Vector4D v1, Vector4D v2);

void printMatrix(float* M1, int rows, int columns);
void multiplyMatrix(float* M1, int rowsM1, int columnsM1, float* M2, int rowsM2, int columnsM2, float* result);

void divideByW(float* matrix, int rows, int columns, float* result);

void viewportMatrix(int width, int height, float* result);

void rotation_x(float a, float* result);
void rotation_y(float a, float* result);
void rotation_z(float a, float* result);

void multiplyVector4DByMatrix4X4(Vector4D* V, float* M);

// Camera
void change_position(Camera* camera, char v, int dir);
void look_horizontal(Camera* camera, float rotation, float* rotation_y_matrix);
