/*
** display.c<2> for <Viewer> in /home/barrau_a//c/lemipc_soldier/gui
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 01:36:21 2011 adrien barrau
** Last update Sun May 22 17:34:23 2011 adrien barrau
*/

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "viewer.h"

void	display_wait(t_view * view)
{
  SDL_Rect pos;

  pos.x = (VIEW_W / 2) - (500 / 2);
  pos.y = (VIEW_H / 2) - (300 / 2);
  SDL_BlitSurface(view->wait_img, NULL, view->screen, &pos);
}

void	display_background(t_view * view)
{
  SDL_Rect pos;

  pos.x = 0;
  pos.y = 0;
  SDL_BlitSurface(view->background_img, NULL, view->screen, &pos);
}

void	display_rect(t_view * view)
{
  int	x11 = XO - 1,       y11 = YO - 1;
  int	x21 = XO,           y21 = YO;
  int	x31 = XO + 1,       y31 = YO + 1;
  int	x12 = XO + 600 - 1, y12 = YO + 600 - 1;
  int	x22 = XO + 600,     y22 = YO + 600;
  int	x32 = XO + 600 + 1, y32 = YO + 600 + 1;

  rectangleColor(view->screen, x11, y11, x12, y12, RECT_OUT_COLOR);
  rectangleColor(view->screen, x21, y21, x22, y22, RECT_IN_COLOR);
  rectangleColor(view->screen, x31, y31, x32, y32, RECT_OUT_COLOR);
}
