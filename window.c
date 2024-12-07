#ifndef UNICODE
#define UNICODE
#endif

#define WIDTH 600
#define HEIGHT 600

#include <windows.h>
#include <stdio.h>
#include "headers/types.h"
#include "headers/functions.h"

// function prototypes
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void reDraw(HWND hwnd);

// global variables
Camera camera = {
    .position = {0, 0, -3, 1},
    .x_fov = 3.141592 / 10,
    .y_fov = (3.141592 / 10) * HEIGHT / HEIGHT,
    .near_plane_distance = 0.1,
    .far_plane_distance = 100,
    .g = {0, 0, 1, 1},
    .t = {0, 1, 0, 1},
    .right_v = {1, 0, 0, 1},
    .translation_speed = 0.05,
    .rotation_speed = 0.1
};

float vertices[4][8] = {
  {0, 0, 1, 1, 0, 1, 0, 1},
  {0, 1, 1, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, -1, -1, -1, -1},
  {1, 1, 1, 1, 1, 1, 1, 1}
};

int faces[6][4] = {
  {0, 1, 2, 3},
  {1, 4, 5, 2},
  {7, 5, 4, 6},
  {3, 2, 5, 7},
  {6, 4, 1, 0},
  {6, 0, 3, 7}
};

float cam_mat[4][4];
float projection_matrix[4][4];
float viewport_matrix[4][4];

float rotation_x_matrix[4][4];
float rotation_y_matrix[4][4];
float rotation_z_matrix[4][4];

float cam_mat_transformation[4][8];
float projection_matrix_transformation[4][8];
float divide_by_w[4][8];
float viewport_matrix_transformation[4][8];

float current_transformation[4][8];


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"3D Render";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"3D Render",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
     case WM_DESTROY:
         PostQuitMessage(0);
         return 0;
     case WM_PAINT:
     {
       reDraw(hwnd);
       return 0;
     }
    case WM_KEYDOWN:

      switch (wParam)
	{
	case 'W':
	  change_position(&camera, 'g', 0);
	  InvalidateRect(hwnd, NULL, TRUE);
	  break;
	case 'A':
	  change_position(&camera, 'r', 0);
	  InvalidateRect(hwnd, NULL, TRUE);
	  break;
	case 'S':
	  change_position(&camera, 'g', 1);
	  InvalidateRect(hwnd, NULL, TRUE);
	  break;
	case 'D':
	  change_position(&camera, 'r', 1);
	  InvalidateRect(hwnd, NULL, TRUE);
	  break;
	case VK_SPACE:
	  change_position(&camera, 't', 0);
	  InvalidateRect(hwnd, NULL, TRUE);
	  break;
	case VK_SHIFT:
	  change_position(&camera, 't', 1);
	  InvalidateRect(hwnd, NULL, TRUE);
	  break;
	case VK_LEFT:
	  look_horizontal(&camera, -camera.rotation_speed, (float*) rotation_y_matrix);
	  InvalidateRect(hwnd, NULL, TRUE);
	  break;
	case VK_RIGHT:
	  look_horizontal(&camera, camera.rotation_speed, (float*) rotation_y_matrix);
	  InvalidateRect(hwnd, NULL, TRUE);
	  break;
	case VK_DOWN:
	  look_horizontal(&camera, -camera.rotation_speed, (float*) rotation_z_matrix);
	  InvalidateRect(hwnd, NULL, TRUE);
	  break;
	case VK_UP:
	  look_horizontal(&camera, camera.rotation_speed, (float*) rotation_z_matrix);
	  InvalidateRect(hwnd, NULL, TRUE);
	  break;
	}
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void updateMatrices(void) {
  
  // Get matrices
  cameraMatrix(camera, (float*) cam_mat);
  projectionMatrix(camera, (float*) projection_matrix);
  viewportMatrix(WIDTH, HEIGHT, (float*) viewport_matrix);
  
  // Camera matrix transformation.
  multiplyMatrix((float*) cam_mat, 4, 4, (float*) vertices, 4, 8, (float*) cam_mat_transformation);
  // Projection matrix transformation.
  multiplyMatrix((float*) projection_matrix, 4, 4, (float*) cam_mat_transformation, 4, 8, (float*) projection_matrix_transformation);
  // Divide by w.
  divideByW((float*) projection_matrix_transformation, 4, 8, (float*) divide_by_w);
  // Viewport matrix transformation.
  multiplyMatrix((float*) viewport_matrix, 4, 4, (float*) divide_by_w, 4, 8, (float*) viewport_matrix_transformation);
  
}

void reDraw(HWND hwnd)
{
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(hwnd, &ps);

  updateMatrices();

  // Clear the window
  
  RECT clientRect;
  GetClientRect(hwnd, &clientRect);
  FillRect(hdc, &clientRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

  // Create pen
  
  HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 235, 0));
  HGDIOBJ hOldPen = SelectObject(hdc, hPen);
  
  // Draw polygons.
  
  int face_index, numPoints;
  for (int face = 0; face < 6; face++) {

    POINT points[5] = { 0 };
    
    for (face_index = 0; face_index < 5; face_index++) {

      if (face_index == 4) { // If its last, get back to origin.
	points[face_index].x = viewport_matrix_transformation[0][faces[face][0]];
	points[face_index].y = viewport_matrix_transformation[1][faces[face][0]];
	break;
      }
      
      points[face_index].x = viewport_matrix_transformation[0][faces[face][face_index]]; // GET POINTS
      points[face_index].y = viewport_matrix_transformation[1][faces[face][face_index]];
    }

    
    //HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
    //HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    
    numPoints = sizeof(points) / sizeof(points[0]);
    //Polygon(hdc, points, numPoints);
    Polyline(hdc, points, numPoints);
  }

  SelectObject(hdc, hOldPen);
  DeleteObject(hPen);

  // End
  EndPaint(hwnd, &ps);
}
