#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "game.h"
#include "shaders.h"
#include "dbg.h"

Game * Game__new__()
{
    Game * self = malloc(sizeof(Game));
    
    self->vs = NULL; self->fs = NULL;
    self->sp = NULL;
    self->vao = 0; self->vbo = 0;
    self->uni_time = 0;
    self->error = 0;
    self->running = true;
    self->pause = 0;
    self->time_mod = 1.0f;

    Game__init__(self);


    return self;
    
}

void Game__init__(Game * self)
{
    const GLchar * vert_src = shader_getsrc("vs.glsl");
    check(vert_src != NULL,
          "Could not load vertex shader source code.");

    const GLchar * frag_src = shader_getsrc("fs.glsl");
    check(vert_src != NULL,
          "Could not load fragment shader source code.");

    game__load_vertex_data(self);
    
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
                log_info("Restarting game...");
                DEL(Game, self);
                self = NEW(Game);
                break;

            case SDLK_p:
                self->pause = !self->pause;
                break;
        }
        key = 0;
    }
}

void game_update(Game * self)
{
    if (self->error != 0 ) return;
    
    GLfloat time_mod = (self->time_mod * !self->pause) + ((sin(SDL_GetTicks() / 500.0f) + 0.5f) * self->pause);
    glUniform4f(self->uni_time, time_mod, time_mod, time_mod, SDL_GetTicks() / 60.0f);
    self->time_mod = time_mod;
}

void game_draw(Game * self)
{
    if (self->error != 0 ) return;

    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw a triangle from the 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void game__end(Game * self)
{
    self->running = false;
}

void game__load_vertex_data(Game * self)
{
    glGenVertexArrays(1, &self->vao);
    glBindVertexArray(self->vao);

    glGenBuffers(1, &self->vbo);
    GLfloat vertices[] = {
         0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void game__set_vertex_data_layout(Game * self)
{
    GLint pos_attr = shader_prog_attrib(self->sp, "position");
    glEnableVertexAttribArray(pos_attr);
    glVertexAttribPointer(pos_attr, 2, GL_FLOAT, GL_FALSE,
                          5 * sizeof(GLfloat), 0);


    GLint col_attr = shader_prog_attrib(self->sp, "color");
    glEnableVertexAttribArray(col_attr);
    glVertexAttribPointer(col_attr, 3, GL_FLOAT, GL_FALSE,
                          5 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));
}

void game__set_uniforms(Game * self)
{
    self->uni_time = shader_prog_uniform(self->sp, "time_mod");
}

