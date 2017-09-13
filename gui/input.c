/*
** input.c for <Viewer< in /home/barrau_a//c/lemipc_soldier/gui
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 13:34:36 2011 adrien barrau
** Last update Sun May 22 13:47:37 2011 adrien barrau
*/

#include "viewer.h"

bool	getInput()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
    {
      if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	  || event.type == SDL_QUIT)
	return (true);
    }
  return (false);
}
