/*
  veclib.h
  $Id: veclib.h,v 1.2 2002/11/18 02:36:13 prok Exp prok $
*/

#ifndef VECLIB_H
#define VECLIB_H

#include <math.h>
#include <stdio.h>

class Vector3 {
public:
                              Vector3();
                              Vector3(float x, float y, float z);
                              Vector3(const Vector3 &v);
                              ~Vector3() {}

  void                        Set(float x, float y, float z);

  /* access */
  float                       X() const { return mX; }
  float                       Y() const { return mY; }
  float                       Z() const { return mZ; }

  /* assignment */
  Vector3                     operator=(const Vector3 &v);
  /* opposite */
  Vector3                     operator-();
  /* subtraction */
  Vector3                     operator-(const Vector3 &v) const;
  Vector3 &                   operator-=(const Vector3 &v);
  /* addition */
  Vector3                     operator+(const Vector3 &v) const;
  Vector3 &                   operator+=(const Vector3 &v);
  /* scalar multiply */
  Vector3                     operator*(float a) const;
  Vector3 &                   operator*=(float a);
  /* vector ops */
  float                       operator*(const Vector3 &v) const;
  Vector3                     Cross(const Vector3 &v) const;
  void                        Normalize();
  float                       Magnitude() const;

  void                        Print() const;

  friend Vector3              operator*(float a, const Vector3 &v);

private:

  float                       mX,mY,mZ;
};

class VecLib {
public:
                    VecLib() { /* nothing */ }

  static Vector3    PlaneNormal(const Vector3 &A, const Vector3 &B, const Vector3 &C);
  static float      PointToPlaneDist(const Vector3 &P, const Vector3 &N, float d);
};

/////////////////////////////////////////////////////////////////////////////

inline Vector3::Vector3()
: mX(0.0), mY(0.0), mZ(0.0)
{}

inline Vector3::Vector3(float x, float y, float z)
: mX(x), mY(y), mZ(z)
{}

inline Vector3::Vector3(const Vector3 &v)
: mX(v.mX), mY(v.mY), mZ(v.mZ)
{}

inline void Vector3::Set(float x, float y, float z)
{
  mX = x;
  mY = y;
  mZ = z;
}

inline Vector3 Vector3::operator=(const Vector3 &v)
{
  mX = v.mX;
  mY = v.mY;
  mZ = v.mZ;

  return *this;
}

inline Vector3 Vector3::operator-()
{
  Vector3 res;

  res.mX = -mX;
  res.mY = -mY;
  res.mZ = -mZ;

  return res;
}

inline Vector3 Vector3::operator-(const Vector3 &v) const
{
  Vector3 res;

  res.mX = mX - v.mX;
  res.mY = mY - v.mY;
  res.mZ = mZ - v.mZ;

  return res;
}

inline Vector3 & Vector3::operator-=(const Vector3 &v)
{
  mX -= v.mX;
  mY -= v.mY;
  mZ -= v.mZ;

  return *this;
}

inline Vector3 Vector3::operator+(const Vector3 &v) const
{
  Vector3 res;

  res.mX = mX + v.mX;
  res.mY = mY + v.mY;
  res.mZ = mZ + v.mZ;

  return res;
}

inline Vector3 & Vector3::operator+=(const Vector3 &v)
{
  mX += v.mX;
  mY += v.mY;
  mZ += v.mZ;

  return *this;
}

inline Vector3 Vector3::operator*(float a) const
{
  Vector3 res;

  res.mX = a * mX;
  res.mY = a * mY;
  res.mZ = a * mZ;

  return res;
}

inline Vector3 & Vector3::operator*=(float a)
{
  mX *= a;
  mY *= a;
  mZ *= a;

  return *this;
}

/* vector ops: dot, cross, normalize, & magnitude */

inline float Vector3::operator*(const Vector3 &v) const
{
  float res = (mX*v.mX + mY*v.mY + mZ*v.mZ);

  return res;
}

inline Vector3 Vector3::Cross(const Vector3 &v) const
{
  // this X v
  Vector3 res;

  res.mX = (mY*v.mZ) - (mZ*v.mY);
  res.mY = (mZ*v.mX) - (mX*v.mZ);
  res.mZ = (mX*v.mY) - (mY*v.mX);

  return res;
}

inline void Vector3::Normalize()
{
  float mag = this->Magnitude();

  if (mag != 0.0)
  {
    mX /= mag;
    mY /= mag;
    mZ /= mag;
  }
}

inline float Vector3::Magnitude() const
{
  return (float)sqrt(mX*mX + mY*mY + mZ*mZ);
}

inline void Vector3::Print() const
{
  printf("Point/Vector: (%2.2f, %2.2f, %2.2f)\n", mX, mY, mZ);
}

/* friend */
inline Vector3 operator*(float a, const Vector3 &v)
{
  return v*a;
}

/////////////////////////////////////////////////////////////////////////////////

inline Vector3 VecLib::PlaneNormal(const Vector3 &A, const Vector3 &B, const Vector3 &C)
{
  //        B
  //
  //
  //  C           A
  // p1,p2,p3 are the vertices of a triangle, given in counter-clockwise order
  // compute the normal of the plane they lie in. (normal points out of screen)
  // N = (A - B) X (C - B)
  Vector3 U, V;
  U = A-B;
  V = C-B;

  U = U.Cross(V);
  U.Normalize();

  return U;
}

inline float VecLib::PointToPlaneDist(const Vector3 &P, const Vector3 &N, float d)
{
  // (P - Q) || N
  // => (P - Q) = k*N
  // => Q = P - k*N
  // N*Q - d = 0
  // => N*(P - k*N) - d = 0
  // => N*P - N*(k*N) - d = 0
  // => k = (N*P - d) / (N*N)
  // => k = N*P - d (because N is unit length)
  float k;

  k = N*P;
  k -= d;

  return k;
}

#endif
