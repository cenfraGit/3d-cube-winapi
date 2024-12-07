#include "../headers/types.h"

float Dot3D(Vector3D v1, Vector3D v2)
{
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

float Dot4D(Vector4D v1, Vector4D v2)
{
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}
