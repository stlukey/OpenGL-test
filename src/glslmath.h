#ifndef _GLS_MATH_H_
#define _GLS_MATH_H_

#include <math.h>
#include <GL/glew.h>

typedef GLfloat vec3[3];
#define VEC3 {0, 0, 0}

typedef GLfloat vec4[4];
#define VEC4 {0, 0, 0, 0}

typedef vec4 mat4[4];
#define MAT4   {{1, 0, 0, 0},\
                {0, 1, 0, 0},\
                {0, 0, 1, 0},\
                {0, 0, 0, 1}}

#define MAT4_X_ROTATE(deg) {{1.0f,  0.0f,     0.0f,      0.0f},\
                            {0.0f,  cos(deg), -sin(deg), 0.0f},\
                            {0.0f,  sin(deg), cos(deg),  0.0f},\
                            {0.0f,  0.0f,     0.0f,      1.0f}}

#define MAT4_Y_ROTATE(deg) {{cos(deg),   0.0f,  sin(deg), 0.0f},\
                            {0.0f,       1.0f,  0.0f,     0.0f},\
                            {-sin(deg),  0.0f,  cos(deg), 0.0f},\
                            {0.0f,       0.0f,  0.0f,     1.0f}}

#define MAT4_Z_ROTATE(deg) {{cos(deg),   -sin(deg), 0.0f, 0.0f},\
                            {sin(deg),   cos(deg),  0.0f, 0.0f},\
                            {0.0f,       0.0f,      1.0f, 0.0f},\
                            {0.0f,       0.0f,      0.0f, 1.0f}}

static inline void mat4_mul_mat4(mat4 a, mat4 b)
{
    a[0][0]*=b[0][0]; a[0][1]*=b[0][1]; a[0][2]*=b[0][2]; a[0][3]*=b[0][3];
    a[1][0]*=b[1][0]; a[1][1]*=b[1][1]; a[1][2]*=b[1][2]; a[1][3]*=b[1][3];
    a[2][0]*=b[2][0]; a[2][1]*=b[2][1]; a[2][2]*=b[2][2]; a[2][3]*=b[2][3];
    a[3][0]*=b[3][0]; a[3][1]*=b[3][1]; a[3][2]*=b[3][2]; a[3][3]*=b[3][3];
}

static inline void mat4_x_rotate(mat4 a, GLfloat deg)
{
    mat4 trans = MAT4_X_ROTATE(deg);
    mat4_mul_mat4(a, trans);
}

static inline void mat4_y_rotate(mat4 a, GLfloat deg)
{
    mat4 trans = MAT4_Y_ROTATE(deg);
    mat4_mul_mat4(a, trans);
}

static inline void mat4_z_rotate(mat4 a, GLfloat deg)
{
    mat4 trans = MAT4_Z_ROTATE(deg);
    mat4_mul_mat4(a, trans);
}

#endif // _GLS_MATH_H_
