#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "game.h"

Game * game__new__()
{
    Game * self = malloc(sizeof(Game));
    
    game__init__(self);

    return self;
    
}

void game__init__(Game * self)
{
    self->error = 0;

    game__gl_init(&self->_gl_ptrs);

    self->running = true;
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
        }
        key = 0;
    }
}

void game_update(Game * self)
{
    if (self->error != 0 ) return;
    
    struct GL_Ptrs * glp = &self->_gl_ptrs; 
    GLfloat time_mod = sin(SDL_GetTicks() / 500.0f) + 0.5f;
    glUniform3f(glp->uni_color, time_mod, time_mod, time_mod);
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

void game__del__(Game * self)
{
    game__gl_del(&self->_gl_ptrs);
    free(self);
}

void game__gl_init(struct GL_Ptrs * glp)
{
    glp->vao = 0; glp->vbo = 0;
    glp->vs = 0;  glp->fs = 0;
    glp->shader_prog = 0;
    glp->uni_color = 0;

    // `glp->*s` src
    const GLchar* vert_src =
        #include "shaders/vs.glsl.h"
    ;
    const GLchar* frag_src =
        #include "shaders/fs.glsl.h"
    ;

    // Create `glp->vao`
    glGenVertexArrays(1, &glp->vao);
    glBindVertexArray(glp->vao);

    // Create `glp->vbo` and copy data
    glGenBuffers(1, &glp->vbo);
    GLfloat vertices[] = {
         0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, glp->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // Compile `glp->*s`
    glp->vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(glp->vs, 1, &vert_src, NULL);
    glCompileShader(glp->vs);

    glp->fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(glp->fs, 1, &frag_src, NULL);
    glCompileShader(glp->fs);


    // Linking `glp->*s` into `glp->shader_prog`
    glp->shader_prog = glCreateProgram();
    glAttachShader(glp->shader_prog, glp->vs);
    glAttachShader(glp->shader_prog, glp->fs);
    glBindFragDataLocation(glp->shader_prog, 0, "out_color");
    glLinkProgram(glp->shader_prog);
    glUseProgram(glp->shader_prog);

    // Layout of `vertices`
    GLint pos_attr = glGetAttribLocation(glp->shader_prog, "position");
    glEnableVertexAttribArray(pos_attr);
    glVertexAttribPointer(pos_attr, 2, GL_FLOAT, GL_FALSE,
                          5 * sizeof(GLfloat), 0);

    GLint col_attr = glGetAttribLocation(glp->shader_prog, "color");
    glEnableVertexAttribArray(col_attr);
    glVertexAttribPointer(col_attr, 3, GL_FLOAT, GL_FALSE,
                          5 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));

    // Uniforms
    glp->uni_color = glGetUniformLocation(glp->shader_prog, "time_mod");
}

void game__gl_del(struct GL_Ptrs * glp)
{
    if( glp->shader_prog != 0 ) glDeleteProgram(glp->shader_prog);
    if( glp->fs != 0 ) glDeleteShader(glp->fs);
    if( glp->vs != 0 ) glDeleteShader(glp->vs);

    if( glp->vbo != 0 ) glDeleteBuffers(1, &glp->vbo);

    if( glp->vao != 0 ) glDeleteVertexArrays(1, &glp->vao);
}

void game__end(Game * self)
{
    self->running = false;
}


