#ifndef _GAME_H_
#define _GAME_H_

#include <stdbool.h>

#include "objects.h"
#include "shaders.h"

/*******************************************************************
 *                          Game Object                            *
 *******************************************************************/

typedef struct Game {
    bool running;
    int error;
    Shader     * vs, * fs;
    ShaderProg * sp;
    GLuint vao, vbo;
    GLuint uni_time;
} Game;

/*** Special Methods ***/
Game * Game__new__ ();            /* Call via NEW(game) */
void   Game__init__(Game * self); /* Called by NEW(game) */
void   Game__del__ (Game * self); /* Call via DEL(game, self) */


/*** Public Methods ***/
void game_events   (Game           * self);
void game_update   (Game           * self);
void game_draw     (Game           * self);

/*** Private Methods ***/
void game__end     (Game           * self);

/*******************************************************************
 *******************************************************************/

#endif // _GAME_H_

