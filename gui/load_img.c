/*
** load_img.c for <Viewer> in /home/barrau_a//c/lemipc_soldier/gui
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 18:11:14 2011 adrien barrau
** Last update Sun May 22 18:17:10 2011 adrien barrau
*/

#define	 _SVID_SOURCE
#define	 _XOPEN_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "viewer.h"

SDL_Surface * load_image(const char * filename)
{
    SDL_Surface* loadedImage = NULL;

    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load(filename);
    if (loadedImage != NULL)
      {
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
	SDL_FreeSurface(loadedImage );
    }
    return (optimizedImage);
}

int	init_window(t_view * view)
{
  int	err_code = 0;

  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    err_code = SDL_INIT_ERR_CODE;
  if (!err_code && (view->screen = SDL_SetVideoMode(VIEW_W,
						    VIEW_H,
						    VIEW_BPP,
						    SDL_ANYFORMAT)) == NULL)
    err_code = VIDEOMODE_ERR_CODE;
  if (!err_code)
    SDL_WM_SetCaption(VIEW_TITLE, NULL);
  if (!err_code && (view->wait_img = load_image(WAIT_IMG_PATH)) == NULL)
    err_code = LOAD_ERR_CODE;
  if (!err_code && (view->background_img =
		    load_image(BACKGROUND_IMG_PATH)) == NULL)
    err_code = LOAD_ERR_CODE;
  return (err_code);
}
