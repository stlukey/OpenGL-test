#include <stdlib.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "config.h"
#include "dbg.h"

#include "game.h"

void at_exit()
{
    SDL_Quit();

#ifdef _WIN32
    puts("Press [ENTER] to close.");
    getchar();
#endif

}

int main(int argc, char * argv[])
{
    // Initialize all vars to NULL
    // in case of errors.
    SDL_Window    * window  = NULL;
    SDL_GLContext   context = NULL;
    Game          * g       = NULL;

#ifdef _WIN32
    DBG_WIN32_INIT();
#endif

    SDL_Init(SDL_INIT_VIDEO);
    atexit(at_exit);

    CONFIG_GL_SET_ATTRS();


    window = SDL_CreateWindow(TITLE, POS, SIZE,SDL_WINDOW_OPENGL);
    check( window != NULL,
          "Could not create window: %s", SDL_GetError());

    context = SDL_GL_CreateContext(window);
    check( window != NULL,
          "SDL failed to create GL context: %s", SDL_GetError());


    glewExperimental = GL_TRUE;
    glewInit();

    g = NEW(Game);
    check( (g != NULL) && (g->error == 0),
           "Failed to create game.");


    // Main game loop.
    while( g->running ) {
        game_events(g);
        game_update(g);
        game_draw(g);
    
        check( g->error == 0,
              "Game encountered errors.");

        SDL_GL_SwapWindow(window);
    }

    // Clean up
    DEL(Game, g);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);

    return EXIT_SUCCESS;


error:
    // All vars are initially NULL.
    if( g       != NULL ) DEL(Game, g);
    if( context != NULL ) SDL_GL_DeleteContext(context);
    if( window  != NULL ) SDL_DestroyWindow(window);

    return EXIT_FAILURE;
}

