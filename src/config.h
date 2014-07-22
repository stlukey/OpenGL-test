
#define TITLE "OpenGL test"

#define WIDTH  800
#define HEIGHT 400

#define SIZE WIDTH, HEIGHT

#define POS SDL_WINDOWPOS_UNDEFINED,\
            SDL_WINDOWPOS_UNDEFINED

#define CONFIG_GL_SET_ATTRS() \
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,\
                        SDL_GL_CONTEXT_PROFILE_CORE);\
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);\
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);\

#define RES_PATH "res/"
#define SHADERS_PATH RES_PATH "shaders/"

