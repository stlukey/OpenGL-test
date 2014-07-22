#ifndef _GAME_H_
#define _GAME_H_

#include <stdbool.h>

#include "objects.h"

struct GL_Ptrs {
    GLuint vao, /* Vertex Array Object */
           vbo, /* Vertex Buffer Object */
           vs,  /* Vertex Shader */
           fs,  /* Fragment Shader */
           uni_time, shader_prog;
};

/*******************************************************************
 *                          Game Object                            *
 *******************************************************************/

typedef struct Game {
    bool running;
    int error;
    struct GL_Ptrs _gl_ptrs;
} Game;

/*** Special Methods ***/
Game * Game__new__ ();            /* Call via NEW(game) */
void   Game__init__(Game * self); /* Called by __new__ */
void   Game__del__ (Game * self); /* Call via DEL(game, self) */


/*** Public Methods ***/
void game_events   (Game           * self);
void game_update   (Game           * self);
void game_draw     (Game           * self);

/*** Private Methods ***/
void game__end     (Game           * self);

void game__gl_init (struct GL_Ptrs * glp);
void game__gl_del  (struct GL_Ptrs * glp);

/*******************************************************************
 *******************************************************************/

#endif // _GAME_H_

