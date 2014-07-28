#ifndef _GLS_MATH_H_
#define _GLS_MATH_H_

#include <math.h>
#include <string.h>
#include <GL/glew.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

static inline void mat4_mul_mat4(mat4 a, mat4 b, mat4 r)
{
    unsigned int i, j, k;
    for( i = 0; i < 4; ++i )
        for( j = 0; j < 4; ++j ) {
            r[i][j] = 0;
            for( j = 0; j < 4; ++j )
                r[i][j] += a[k][j] * b[i][k];
        }
}

static inline void mat4_x_rotate(mat4 a, GLfloat rads)
{
    mat4 res, trans = MAT4_X_ROTATE(rads);
    mat4_mul_mat4(a, trans, res);
    memcpy(a, res, sizeof(mat4));
}

static inline void mat4_y_rotate(mat4 a, GLfloat rads)
{
    mat4 res, trans = MAT4_X_ROTATE(rads);
    mat4_mul_mat4(a, trans, res);
    memcpy(a, res, sizeof(mat4));
}

static inline void mat4_z_rotate(mat4 a, GLfloat rads)
{
    mat4 res, trans = MAT4_X_ROTATE(rads);
    mat4_mul_mat4(a, trans, res);
    memcpy(a, res, sizeof(mat4));
}

#endif // _GLS_MATH_H_
