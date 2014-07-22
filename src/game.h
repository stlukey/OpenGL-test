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
    int error, pause;
    Shader     * vs, * fs;
    ShaderProg * sp;
    GLuint vao, vbo;
    GLuint uni_time;
    GLfloat time_mod;
} Game;

/*** Special Methods ***/
Game * Game__new__                ();            /* NEW(game) */
void   Game__init__               (Game * self); 
void   Game__del__                (Game * self); /* DEL(game, self) */


/*** Public Methods ***/
void game_events                  (Game * self);
void game_update                  (Game * self);
void game_draw                    (Game * self);

/*** Private Methods ***/
void game__end                    (Game * self);
void game__load_vertex_data       (Game * self);
void game__set_vertex_data_layout (Game * self);
void game__set_uniforms           (Game * self);
/*******************************************************************
 *******************************************************************/

#endif // _GAME_H_

