/**
*
*  Modified by Thayne Walker 2017.
*
* This file is part of HOG2.
*
* HOG2 is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* HOG2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with HOG2; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>
#include "FPUtil.h"
#include <ostream>
#include <vector>
//#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef K::Point_2 Point_2;
//typedef K::Point_3 Point_3;

struct xyLoc;

class Vector2D {
  public:
    Vector2D(Vector2D const& v):Vector2D(v.x,v.y){}
    Vector2D(xyLoc const& v);
    //Vector2D(Point_2 const& p):Vector2D(p[0],p[1]){};
    Vector2D(double _x,double _y):x(_x),y(_y) {/*Normalize();*/}
    Vector2D():x(0),y(0) {}
    void Set(double _x, double _y) { x=_x; y=_y; /*Normalize();*/}

    void SetUpdateTime(double t) {}
    double GetUpdateTime() {return 0.0;}

    void SetAccessTime(double t) {}
    double GetAccessTime() {return 0.0;}
    //operator Point_2()const{return Point_2(x,y);}

    bool operator==(const Vector2D &rhs)const{return (fequal(x,rhs.x)&&fequal(y,rhs.y));}
    bool operator<(const Vector2D &rhs)const{return fequal(x,rhs.x)?fless(y,rhs.y):fless(x,rhs.x);}

    // Dot product
    inline double operator *(Vector2D const& other)const{return x * other.x + y * other.y;}
    inline Vector2D operator -(Vector2D const& other)const{return Vector2D(x-other.x,y-other.y);}
    inline Vector2D operator +(double s)const{return Vector2D(x+s,y+s);}
    inline void operator -=(Vector2D const& other){x-=other.x;y-=other.y;}
    // Negation
    inline Vector2D operator -()const{return Vector2D(-x,-y);}
    // Slope angle of this vector
    inline double atan()const{ return atan2(y,x); }
    // Square
    inline double sq()const{ return (*this) * (*this); }
    inline double len()const{ return sqrt(sq()); }
    inline double cross(Vector2D const& b)const{return x*b.y-y*b.x;}

    // Vector that is perpendicular to this vector
    inline Vector2D perp()const{return Vector2D(y,-x);}

    inline double min()const{return x<y?x:y;}
    inline double max()const{return x>y?x:y;}
    // Project an (unclosed) polygon onto this line (a normalized axis)
    inline Vector2D projectPolyOntoSelf(std::vector<Vector2D> const& poly)const{
      double min(poly[0]*(*this));
      double max=min;
      for(unsigned i(1); i<poly.size(); ++i){
        double proj(poly[i]*(*this));
        if(fless(proj,min)) min = proj;
        if(fgreater(proj,max)) max = proj;
      }
      return Vector2D(min,max);
    }

    friend Vector2D operator /(const Vector2D& vec, const double num)
    {
      return Vector2D(vec.x / num, vec.y / num);
    }

    friend Vector2D operator *(const Vector2D& vec, const double num)
    {
      return Vector2D(vec.x * num, vec.y * num);
    }

    friend Vector2D operator *(const double num, const Vector2D& vec)
    {
      return Vector2D(vec.x * num, vec.y * num);
    }

    friend Vector2D operator +(const Vector2D& v1, const Vector2D& v2)
    {
      return Vector2D(v1.x + v2.x, v1.y + v2.y);
    }

    inline void operator +=(double s) { x +=s; y +=s; }
    inline void operator +=(const Vector2D& v2) { x +=v2.x; y +=v2.y; }
    inline void operator *=(double s) { x*=s; y*=s; }
    inline void operator *=(Vector2D const& s) { x*=s.x; y*=s.y; }
    inline void operator /=(double s) { x/=s; y/=s; }

    //                                                //private:
    double x, y;
    //double updateTime, accessTime;

    void Normalize()
    {
      if ((x==0)&&(y==0))
        return;
      double magnitude(len());
      x /= magnitude;
      y /= magnitude;
    }
};

struct TemporalVector : Vector2D {
  TemporalVector(Vector2D const& loc, double time):Vector2D(loc), t(time){}
  TemporalVector(double _x, double _y, float time):Vector2D(_x,_y), t(time){}
  TemporalVector():Vector2D(),t(0){}
  inline bool operator==(TemporalVector const& other)const{return Vector2D::operator==(other)&&fequal(t,other.t);}
  double t;
};

// Calculate determinant of vector
inline double det(Vector2D const& v1, Vector2D const& v2){
  return v1.x*v2.y - v1.y*v2.x;
}

// Compute normal to line segment with specified endpoints
inline Vector2D normal(Vector2D const& v1, Vector2D const& v2){
  Vector2D tmp(v2.y-v1.y,v1.x-v2.x);
  tmp.Normalize();
  return tmp;
}

std::ostream& operator <<(std::ostream & out, Vector2D const& v);

#endif
