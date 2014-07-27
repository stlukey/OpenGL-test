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

#define MAT4_X_ROTATE(rads) {{1.0f,  0.0f,     0.0f,       0.0f},\
                            {0.0f,  cos(rads), -sin(rads), 0.0f},\
                            {0.0f,  sin(rads), cos(rads),  0.0f},\
                            {0.0f,  0.0f,      0.0f,       1.0f}}

#define MAT4_Y_ROTATE(rads) {{cos(rads),   0.0f,  sin(rads), 0.0f},\
                            {0.0f,       1.0f,  0.0f,        0.0f},\
                            {-sin(rads),  0.0f,  cos(rads),  0.0f},\
                            {0.0f,       0.0f,  0.0f,        1.0f}}

#define MAT4_Z_ROTATE(rads) {{cos(rads), -sin(rads), 0.0f, 0.0f},\
                            {sin(rads),  cos(rads),  0.0f, 0.0f},\
                            {0.0f,       0.0f,       1.0f, 0.0f},\
                            {0.0f,       0.0f,       0.0f, 1.0f}}

static inline void mat4_mul_mat4(mat4 a, mat4 b)
{
    int i, j;
    for( i = 0; i < 3; ++i )
        for( j = 0; j < 3; ++j )
            a[i][j] *= b[i][j];
}

static inline void mat4_x_rotate(mat4 a, GLfloat rads)
{
    mat4 trans = MAT4_X_ROTATE(rads);
    mat4_mul_mat4(a, trans);
}

static inline void mat4_y_rotate(mat4 a, GLfloat rads)
{
    mat4 trans = MAT4_Y_ROTATE(rads);
    mat4_mul_mat4(a, trans);
}

static inline void mat4_z_rotate(mat4 a, GLfloat rads)
{
    mat4 trans = MAT4_Z_ROTATE(rads);
    mat4_mul_mat4(a, trans);
}

#endif // _GLS_MATH_H_
