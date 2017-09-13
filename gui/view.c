/*
** view.c for <Viewer> in /home/barrau_a//c/lemipc_soldier/gui
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sat May 21 20:35:55 2011 adrien barrau
** Last update Sun May 22 18:09:42 2011 adrien barrau
*/

#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "viewer.h"

static int	colors[]=
  {
    0x000000FF,
    0xF0F8FFFF,
    0xFAEBD7FF,
    0x00FFFFFF,
    0x7FFFD4FF,
    0xF0FFFFFF,
    0xF5F5DCFF,
    0xFFE4C4FF,
    0xFFEBCDFF,
    0x0000FFFF,
    0x8A2BE2FF,
    0xA52A2AFF,
    0xDEB887FF,
    0x5F9EA0FF,
    0x7FFF00FF,
    0xD2691EFF,
    0xFF7F50FF,
    0x6495EDFF,
    0xFFF8DCFF,
    0xDC1436FF,
    0x00FFFFFF,
    0x00008BFF,
    0x008B8BFF,
    0xB8860BFF,
    0xA9A9A9FF,
    0x006400FF,
    0xBDB76BFF,
    0x8B008BFF,
    0x556B2FFF,
    0xFF8C00FF,
    0x9932CCFF,
    0x8B0000FF,
    0xE9967AFF,
    0x8FBC8FFF,
    0x483D8BFF,
    0x2F4F4FFF,
    0x00CED1FF,
    0x9400D3FF,
    0xFF1493FF,
    0x00BFFFFF,
    0x696969FF,
    0x1E90FFFF,
    0xB22222FF,
    0xFFFAF0FF,
    0x228B22FF,
    0xFF00FFFF,
    0xDCDCDCFF,
    0xF8F8FFFF,
    0xFFD700FF,
    0xDAA520FF,
    0x808080FF,
    0x008000FF,
    0xADFF2FFF,
    0xF0FFF0FF,
    0xFF69B4FF,
    0xCD5C5CFF,
    0x4B0082FF,
    0xFFFFF0FF,
    0xF0E68CFF,
    0xE6E6FAFF,
    0xFFF0F5FF,
    0x7CFC00FF,
    0xFFFACDFF,
    0xADD8E6FF,
    0xF08080FF,
    0xE0FFFFFF,
    0xFAFAD2FF,
    0x90EE90FF,
    0xD3D3D3FF,
    0xFFB6C1FF,
    0xFFA07AFF,
    0x20B2AAFF,
    0x87CEFAFF,
    0x778899FF,
    0xB0C4DEFF,
    0xFFFFE0FF,
    0x00FF00FF,
    0x32CD32FF,
    0xFAF0E6FF,
    0xFF00FFFF,
    0x800000FF,
    0x66CDAAFF,
    0x0000CDFF,
    0xBA55D3FF,
    0x9370DBFF,
    0x3CB371FF,
    0x7B68EEFF,
    0x00FA9AFF,
    0x48D1CCFF,
    0xC71585FF,
    0x191970FF,
    0xF5FFFAFF,
    0xFFE4E1FF,
    0xFFE4B5FF,
    0xFFDEADFF,
    0x000080FF,
    0xFDF5E6FF,
    0x808000FF,
    0x6B8E23FF,
    0xFFA500FF,
    0xFF4500FF,
    0xDA70D6FF,
    0xEEE8AAFF,
    0x98FB98FF,
    0xAFEEEEFF,
    0xDB7093FF,
    0xFFEFD5FF,
    0xFFDAB9FF,
    0xCD853FFF,
    0xFFC0CBFF,
    0xDDA0DDFF,
    0xB0E0E6FF,
    0x800080FF,
    0xFF0000FF,
    0xBC8F8FFF,
    0x4169E1FF,
    0x8B4513FF,
    0xFA8072FF,
    0xF4A460FF,
    0x2E8B57FF,
    0xFFF5EEFF,
    0xA0522DFF,
    0xC0C0C0FF,
    0x87CEEBFF,
    0x6A5ACDFF,
    0x708090FF,
    0xFFFAFAFF,
    0x40E0D0FF
  };

static void	display_grid(t_view * view)
{
  int		i = 0;
  int		wo = GRID_W / view->width;
  int		ho = GRID_H / view->height;

  for (i = 0; i <= GRID_W; i += wo)
    lineColor(view->screen, i + XO, YO, i + XO, GRID_H + YO, GRID_COLOR);
  for (i = 0; i <= GRID_H; i += ho)
    lineColor(view->screen, XO, i + YO, GRID_H + XO, i + YO, GRID_COLOR);
}

static void	display_player(t_view * view)
{
  int		i = 0, lim = view->width * view->height;
  int		wbox = GRID_W / view->width, hbox = GRID_H / view->height;
  int		x1, y1;

  lock_battlefield(view->semid);
  while (i < lim)
    {
      if (view->battlefield[i] > 0)
	{
	  x1 = (i % view->width) * wbox;
	  y1 = (i / view->width) * hbox;
	  boxColor(view->screen, x1 + XO, y1 + YO, x1 + wbox + XO, y1 + hbox + YO,
		   colors[(int)view->battlefield[i]]);
	}
      ++i;
    }
  unlock_battlefield(view->semid);
}

void	view_battlefield(t_view * view)
{
  bool	quit = false;

  while (!quit)
    {
      quit = getInput(view);
      display_background(view);
      display_grid(view);
      display_rect(view);
      display_player(view);
      SDL_Flip(view->screen);
    }
}
