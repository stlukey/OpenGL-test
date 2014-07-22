#ifndef _SHADERS_H
#define _SHADERS_H

#include "objects.h"


/*******************************************************************
 *                         Shader Object                           *
 *******************************************************************/

typedef struct Shader {
    GLenum         type;
    const GLchar * src;
    
    int            error;

    GLuint         ptr; /* OpenGL pointer */
} Shader;

/*** Special Methods ***/
Shader * Shader__new__ (GLenum type,
                        const GLchar * src);  /* NEW(game) */
void     Shader__init__(Shader * self);
void     Shader__del__ (Shader * self);       /* DEL(game, self) */

/*** Static Methods ***/
GLchar * shader_getsrc (char * filename);


/*******************************************************************
 *                      Shader Program Object                      *
 *******************************************************************/

typedef struct ShaderProg {
    GLuint * vao, /* Vertex Array  Object */
           * vbo; /* Vertex Buffer Object */

    Shader * vs,  /* Vertex   Shader */
           * fs,  /* Fragment Shader */
           * gs;  /* Geometry Shader */

    int error;

    GLuint   ptr; /* OpenGL pointer */
} ShaderProg;


/*** Special Methods ***/
ShaderProg * ShaderProg__new__  (GLuint * vao,
                                 GLuint * vbo,
                                 Shader * vs,
                                 Shader * fs,
                                 Shader * gs);

void         ShaderProg__init__ (ShaderProg * self);
void         ShaderProg__del__  (ShaderProg * self);


/*** Public Methods ***/
void         shader_prog_link    (ShaderProg * self);
void         shader_prog_use     (ShaderProg * self);
GLuint       shader_prog_uniform (ShaderProg * self,
                                  const GLchar * name);
GLuint       shader_prog_attrib  (ShaderProg * self,
                                  const GLchar * name);

/*******************************************************************
 *******************************************************************/

#endif // _SHADERS_H_
