#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SOIL/SOIL.h>

#include "config.h"

#include "game.h"
#include "shaders.h"
#include "dbg.h"

Game * Game__new__()
{
    Game * self = malloc(sizeof(Game));
    
    self->vs = NULL; self->fs = NULL;
    self->sp = NULL;
    self->vao = 0; self->vbo = 0;
    self->ebo = 0;
    self->textures[0] = 0;
    self->textures[1] = 0;
    self->uni_time = 0;
    self->error = 0;
    self->running = true;
    
    Game__init__(self);


    return self;
}

void Game__init__(Game * self)
{
    game__load_texture(self);

    GLchar * vert_src = shader_getsrc("vs.glsl");
    check(vert_src != NULL,
          "Could not load vertex shader source code.");

    GLchar * frag_src = shader_getsrc("fs.glsl");
    check(vert_src != NULL,
          "Could not load fragment shader source code.");

    game__load_vertex_data(self);
    game__load_element_data(self);
    
    self->vs = NEW(Shader, GL_VERTEX_SHADER, vert_src);
    self->fs = NEW(Shader, GL_FRAGMENT_SHADER, frag_src);

    self->sp = NEW(ShaderProg, &self->vao,
                               &self->vbo,
                               self->vs,
                               self->fs,
                               NULL);
    glBindFragDataLocation(self->sp->ptr, 0, "out_color");
    shader_prog_link(self->sp);
    shader_prog_use(self->sp);
    
    game__set_vertex_data_layout(self);

    game__set_uniforms(self);

    return;

error:
    self->error = 1;
}

void Game__del__(Game * self)
{
    if( self->sp != NULL )
        DEL(ShaderProg, self->sp);
    if( self->vs != NULL )
        DEL(Shader, self->vs);
    if( self->fs != NULL )
        DEL(Shader, self->fs);

    if( self->vbo != 0 )
        glDeleteBuffers(1, &self->vbo);

    if( self->vao != 0 )
        glDeleteVertexArrays(1, &self->vao);

    free(self);
}

void game_events(Game * self)
{
    if (self->error != 0 ) return;

    SDL_Event e;
    SDL_Keycode key = 0;
    
    while( SDL_PollEvent(&e) ) {
        switch( e.type ) {
            case SDL_QUIT:
                return game__end(self);

            case SDL_KEYDOWN:
                key = e.key.keysym.sym;
                break;
        }

        switch( key ) {
            case SDLK_ESCAPE:
                return game__end(self);
            case SDLK_F5:
                log_info("Reloading shader...");
                game__shaders_reload(self);
        }
        key = 0;
    }
}

void game_update(Game * self)
{
    if (self->error != 0 ) return;
    
    GLfloat time_mod = sin(SDL_GetTicks() / 500.0f) + 0.5f;
    glUniform4f(self->uni_time, time_mod,
                time_mod, time_mod,
                SDL_GetTicks()/ 60.f);
}

void game_draw(Game * self)
{
    if (self->error != 0 ) return;

    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw a triangle from the 3 vertices
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void game__end(Game * self)
{
    self->running = false;
}

void game__load_texture(Game * self)
{
    glGenTextures(2, self->textures);

    int w, h;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self->textures[0]);
    unsigned char * image = SOIL_load_image(IMAGES_PATH "image.png",
                                            &w, &h,
                                            0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, self->textures[1]);
    image = SOIL_load_image(IMAGES_PATH "image2.png",
                            &w, &h,
                            0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

void game__load_element_data(Game * self)
{
    glGenBuffers(1, &self->ebo);
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(elements), elements, GL_STATIC_DRAW);
}

void game__load_vertex_data(Game * self)
{
    glGenVertexArrays(1, &self->vao);
    glBindVertexArray(self->vao);

    glGenBuffers(1, &self->vbo);
    GLfloat vertices[] = {
        // Position  /**/      Color       /**/  Texture
        -0.5f,  0.5f,/**/ 1.0f, 0.0f, 0.0f,/**/ 0.0f, 0.0f,
         0.5f,  0.5f,/**/ 0.0f, 1.0f, 0.0f,/**/ 1.0f, 0.0f,
         0.5f, -0.5f,/**/ 0.0f, 0.0f, 1.0f,/**/ 1.0f, 1.0f,
        -0.5f, -0.5f,/**/ 1.0f, 1.0f, 1.0f,/**/ 0.0f, 1.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void game__set_vertex_data_layout(Game * self)
{
    GLint pos_attr = shader_prog_attrib(self->sp, "position");
    glEnableVertexAttribArray(pos_attr);
    glVertexAttribPointer(pos_attr, 2, GL_FLOAT, GL_FALSE,
                          7 * sizeof(GLfloat), 0);


    GLint col_attr = shader_prog_attrib(self->sp, "color");
    glEnableVertexAttribArray(col_attr);
    glVertexAttribPointer(col_attr, 3, GL_FLOAT, GL_FALSE,
                          7 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));

    GLint tex_attr = shader_prog_attrib(self->sp, "texcoord");
    glEnableVertexAttribArray(tex_attr);
    glVertexAttribPointer(tex_attr, 2, GL_FLOAT, GL_FALSE,
                          7 * sizeof(GLfloat), (void *)(5 * sizeof(GLfloat)));
}

void game__set_uniforms(Game * self)
{
    self->uni_time = shader_prog_uniform(self->sp, "time_mod");
    glUniform1i(shader_prog_uniform(self->sp, "tex0"), 0);
    glUniform1i(shader_prog_uniform(self->sp, "tex1"), 1);
}

void game__shaders_reload(Game * self)
{
    self->vs->src = NULL;
    self->vs->src = shader_getsrc("vs.glsl");
    check(self->vs->src != NULL,
          "Could not load vertex shader source code.");


    self->fs->src = NULL;
    self->fs->src = shader_getsrc("fs.glsl");
    check(self->fs->src != NULL,
          "Could not load fragment shader source code.");

    shader_compile(self->vs);
    shader_compile(self->fs);

    shader_prog_link(self->sp);
    shader_prog_use(self->sp);

    return;


error:
    self->error = 1;
}
