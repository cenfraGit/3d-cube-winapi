#include "../headers/types.h"

Vector3D Cross3D(Vector3D v1, Vector3D v2)
{
  Vector3D result;
  result.x = v1.y * v2.z - v1.z * v2.y;
  result.y = v1.z * v2.x - v1.x * v2.z;
  result.z = v1.x * v2.y - v1.y * v2.x;
  return result;
}

Vector4D Cross4D(Vector4D v1, Vector4D v2)
{
  Vector4D result;
  result.x = v1.y * v2.z - v1.z * v2.y;
  result.y = v1.z * v2.x - v1.x * v2.z;
  result.z = v1.x * v2.y - v1.y * v2.x;
  result.w = 0.0;
  return result;
}
