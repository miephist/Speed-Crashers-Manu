#pragma once
#include "PhysicsEngine.h"
#include "structs.h"

struct Vector2d{

    float x;
    float y;
    
    Vector2d()       {x=0.0;y=0.0;};
    Vector2d(float a, float b):x(a),y(b){}
    inline void Zero()          {x=0.0;y=0.0;};
    inline bool isZero(){

        if(x==0.0 && y==0.0){
            return true;
        }
        return false;
    };

    inline float length() const{
        float a = (x*x)+(y*y);
        float b = sqrt(a);
        return b;
    };

    inline float lengthSq() const{
        float a = (x*x)+(y*y);
        return a;
    };

    inline void Normalize(){
        x=x/length();
        y=y/length();
    };

    inline Vector2d  Vec2Norm(Vector2d v){
        Vector2d vec = v;
        float vector_length = vec.length();
            vec.x /= vector_length;
            vec.y /= vector_length;
        
        return vec;
    }

    inline float Punto(Vector2d v) const{
        float x2 = x + v.x;
        float y2= y + v.y;
        float last = x2+y2;
        return last;
    };

    enum {clock = 1, anticlock = -1};
    inline int Sign(Vector2d v) const{
        if(y*v.x > x*v.y){
            return anticlock;
        }
        else{
                return clock;
        }
    };

    inline Vector2d Perp() const{
        return Vector2d(-y,x);
    };

    inline float Distance(Vector2d v) const{
        float ySep =v.y - y;
        float xSep = v.x - x;

        return sqrt(ySep*ySep + xSep*xSep);
    };
    inline float Vec2Distance(Vector2d a, Vector2d b){
        float sepY = b.y - a.y;
        float sepX = b.x - a.x;
        return sqrt(sepY*sepY + sepX*sepX);
    }

    inline float DistanceSq(Vector2d v) const{
        float ySep =v.y - y;
        float xSep = v.x - x;

        return ySep*ySep + xSep*xSep;
    }

    inline void Truncar(float max){
        if(length()> max){
            Normalize();
            *this *= max; 
        }
    }

    inline Vector2d getReverse() const{
        return Vector2d(-x,-y);
    };

   /* inline void Reflect(Vector2d norm){
        *this += 2.0 * Punto(norm) * norm.getReverse();
    };*/

    const Vector2d operator+=(const Vector2d rhs){
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    const Vector2d operator-=(const Vector2d rhs){
        x -= rhs.x;
        y -= rhs.y;

        return *this;
    }

    const Vector2d operator*=(const float rhs){
        x *= rhs;
        y *= rhs;

        return *this;
    }

     const Vector2d operator/=(const float rhs){
        x /= rhs;
        y /= rhs;

        return *this;
    }

    bool operator==(Vector2d rhs)const {
        return (islessequal(x,rhs.x) && islessequal(y,rhs.y));
        
    }

    bool operator!=(Vector2d rhs)const {
        return (x != rhs.x) || (y!=rhs.y);
    }
    

};

inline Vector2d operator*(const Vector2d lhs, float rhs);
inline Vector2d operator-(const Vector2d lhs, const Vector2d rhs);
inline Vector2d operator+(const Vector2d lhs, const Vector2d rhs);
inline Vector2d operator/(const Vector2d lhs, float val);


inline Vector2d operator*(const Vector2d lhs, float rhs){
        Vector2d result(lhs);
        result *= rhs;
     return result;
    }

inline Vector2d operator-(const Vector2d lhs, const Vector2d rhs){
  Vector2d result(lhs);
  result.x -= rhs.x;
  result.y -= rhs.y;
  
  return result;
}

inline Vector2d operator+(const Vector2d lhs, const Vector2d rhs)
{
  Vector2d result(lhs);
  result.x += rhs.x;
  result.y += rhs.y;
  
  return result;
}


inline Vector2d operator/(const Vector2d lhs, float val)
{
  Vector2d result(lhs);
  result.x /= val;
  result.y /= val;

  return result;
}