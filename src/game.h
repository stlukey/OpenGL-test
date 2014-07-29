#ifndef _GAME_H_
#define _GAME_H_

#include <stdbool.h>
#include <GL/glew.h>

#include "objects.h"
#include "shaders.h"

/*******************************************************************
 *                          Game Object                            *
 *******************************************************************/

struct Uniforms {
    GLuint time,
           model,
           view,
           proj;
};


typedef struct Game {
    bool running;
    int error;
    Shader     * vs, * fs;
    ShaderProg * sp;
    GLuint vao, vbo, ebo;
    struct Uniforms uniforms;
    GLuint textures[2];
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
void game__shaders_reload         (Game * self);
void game__load_tex_image         (Game * self,
                                    int tex_num,
                                    const char * imagename);
void game__load_textures          (Game * self);
void game__load_element_data      (Game * self);
void game__load_vertex_data       (Game * self);
void game__set_vertex_data_layout (Game * self);
void game__set_uniforms           (Game * self);
/*******************************************************************
 *******************************************************************/

#endif // _GAME_H_

