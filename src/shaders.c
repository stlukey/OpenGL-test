#include <stdlib.h>
#include <GL/glew.h>

#include "shaders.h"

/*******************************************************************
 *                        Shader Methods                           *
 *******************************************************************/
Shader * Shader__new__(GLenum type,
                       const GLchar * src)
{
    Shader * self = malloc(sizeof(Shader));
    
    self->type  = type;
    self->src   = src;
    self->error = 0;
    self->ptr   = 0;

    Shader__init__(self);

    return self;
}

void Shader__init__(Shader * self)
{
    self->ptr = glCreateShader(self->type);
    glShaderSource(self->ptr, 1, &self->src, NULL);
    glCompileShader(self->ptr);
}

void Shader__del__(Shader * self)
{
   if( self->ptr != 0 )
       glDeleteShader(self->ptr);

   free(self);
}

GLchar * shader_getsrc(char * filename)
{
    return "";
}

/*******************************************************************
 *                    ShaderProg Methods                           *
 *******************************************************************/

ShaderProg * ShaderProg__new__(GLuint * vao,
                               GLuint * vbo,
                               Shader * vs,
                               Shader * fs,
                               Shader * gs)
{
    ShaderProg * self = malloc(sizeof(ShaderProg));

    self->vao   = vao; self->vbo = vbo;
    self->vs    = vs;  self->fs  = fs;
    self->gs    = gs;
    self->error = 0;
    self->ptr   = 0;

    ShaderProg__init__(self);

    return self;
}

void ShaderProg__init__(ShaderProg * self)
{
    self->ptr = glCreateProgram();

    if( self->vs != NULL )
        glAttachShader(self->ptr, self->vs->ptr);
    if( self->fs != NULL )
        glAttachShader(self->ptr, self->fs->ptr);
    if( self->gs != NULL )
        glAttachShader(self->ptr, self->gs->ptr);
}

void ShaderProg__del__(ShaderProg * self)
{
    if( self->ptr != 0 )
        glDeleteProgram(self->ptr);

    free(self);
}

void shader_prog_link(ShaderProg * self)
{
    glLinkProgram(self->ptr);
}

void shader_prog_use(ShaderProg * self)
{
    glUseProgram(self->ptr);
}

GLuint shader_prog_uniform(ShaderProg * self,
                           const GLchar * name)
{
    return glGetUniformLocation(self->ptr, name);
}

GLuint shader_prog_attrib(ShaderProg * self,
                          const GLchar * name)
{
    GLuint attr = glGetAttribLocation(self->ptr, name);
    glEnableVertexAttribArray(attr);
    return attr;
}

