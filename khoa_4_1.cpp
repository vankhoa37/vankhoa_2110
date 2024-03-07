#include<bits/stdc++.h>
#include<stdio.h>
#include<SDL.h>
using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool init();
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_ENTER,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_K,
    KEY_PRESS_SURFACE_TOTAL
};
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces = NULL;
SDL_Surface* gCurrentSurface = NULL;
SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    return loadedSurface;
}


int main(int argc, char*args[])
{
gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
gScreenSurface = SDL_GetWindowSurface( gWindow );
gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "press.bmp" );
gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "up.bmp" );
gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "down.bmp" );
gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "left.bmp" );
gKeyPressSurfaces[ KEY_PRESS_SURFACE_K ] = loadSurface ("hello_world.bmp");
gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
    bool quit = false;
    SDL_Event e;
    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
    			while( !quit ){
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN )
					{
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							break;

							case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
							break;

							case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
							break;

							case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
							break;

							case SDLK_RETURN:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_ENTER ];
							break;

							default:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
						}
					}
				}
				SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}
	close();



}
