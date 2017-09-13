/*
** go_there.c<2> for <Chef> in /home/barrau_a//c/lemipc_soldier/libia/chef
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 21:50:53 2011 adrien barrau
** Last update Sun May 22 21:50:56 2011 adrien barrau
*/

#include <stdio.h>
#include <stdlib.h>
#include "lemipc.h"

static void	set_pos(t_game * game, int npos)
{
  game->battlefield[(game->pos.y * game->width) + game->pos.x] = 0;
  game->battlefield[npos] = game->team_num;
  game->pos.x = npos % game->width;
  game->pos.y = npos / game->width;
}

void	go_there(t_game * game, int x, int y)
{
  int	dir = -1, npos;

  if (x != game->pos.x && y != game->pos.y)
    dir = random() % 2;
  if ((dir == -1 && x == game->pos.x)
      || dir == 0)
    {
      if (game->pos.y > y)
	npos = go_up(game);
      else
	npos = go_down(game);
    }
  else
    {
      if (game->pos.x > x)
	npos = go_left(game);
      else
	npos = go_right(game);
    }
  lock_battlefield(game->semid);
  if (game->battlefield[npos] == 0)
    set_pos(game, npos);
  unlock_battlefield(game->semid);
}
