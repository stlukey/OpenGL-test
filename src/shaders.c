#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GL/glew.h>

#include "shaders.h"
#include "config.h"

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



const GLchar * shader_getsrc(char * shadername)
{
    const char * prefix = SHADERS_PATH;
    size_t s_len = strlen(shadername);
    size_t p_len = strlen(prefix);
    char * filename = malloc(s_len + p_len + 1);
    memcpy(filename, prefix, p_len);
    memcpy(filename + p_len, shadername, s_len + 1);

    char * src = NULL;
    FILE * fp =  fopen(filename, "rb");
    free(filename);

    if( fp ) {
        fseek(fp, 0, SEEK_END);
        long len = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        src = malloc(len);
        if( src )
            (void)(fread(src, 1, len, fp) + 1);

        fclose(fp);
        src[len] = '\0';
    }

    return (const GLchar *)src;
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

