#ifndef _GAME_H_
#define _GAME_H_

#include <stdbool.h>

struct GL_Ptrs {
    GLuint vao, /* Vertex Array Object */
           vbo, /* Vertex Buffer Object */
           vs,  /* Vertex Shader */
           fs,  /* Fragment Shader */
           uni_color,
           shader_prog;
};

/*******************************************************************
 *                          Game Object                            *
 *******************************************************************/

typedef struct Game {
    bool running;
    int error;
    struct GL_Ptrs _gl_ptrs;
} Game;

/*** Constructor ***/
Game * game_new();


/*** Public Methods ***/
void game_events      (Game           * self);
void game_update      (Game           * self);
void game_draw        (Game           * self);
void game_destroy     (Game           * self);

/*** Private Methods ***/
void game__init__     (Game           * self);
void game__end        (Game           * self);

void game__gl_init    (struct GL_Ptrs * glp);
void game__gl_destroy (struct GL_Ptrs * glp);

/*******************************************************************
 *******************************************************************/

#endif // _GAME_H_
