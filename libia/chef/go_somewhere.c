/*
** go_somewhere.c for <Chef> in /home/barrau_a//c/lemipc_soldier/libia/chef
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 21:51:07 2011 adrien barrau
** Last update Sun May 22 21:51:23 2011 adrien barrau
*/

#include <stdio.h>
#include <stdlib.h>
#include "lemipc.h"

int	go_up(t_game * game)
{
  if (game->pos.y == 0)
    return ((game->pos.y * game->width) + game->pos.x);
  else
    return (((game->pos.y - 1) * game->width) + game->pos.x);
}

int	go_down(t_game * game)
{
  if (game->pos.y == game->height - 1)
    return ((game->pos.y * game->width) + game->pos.x);
  else
    return (((game->pos.y + 1) * game->width) + game->pos.x);
}

int	go_right(t_game * game)
{
  if (game->pos.x == game->width - 1)
    return ((game->pos.y * game->width) + game->pos.x);
  else
    return ((game->pos.y * game->width) + (game->pos.x + 1));
}

static int (*go_where[])(t_game *)=
{
  &go_up,
  &go_down,
  &go_right,
  &go_left
};

void	go_somewhere(t_game * game)
{
  int		dir = random() % 4;
  int		npos;

  lock_battlefield(game->semid);
  npos = go_where[dir](game);
  if (game->battlefield[npos] == 0)
    {
      game->battlefield[(game->pos.y * game->width) + game->pos.x] = 0;
      game->battlefield[npos] = game->team_num;
      game->pos.x = npos % game->width;
      game->pos.y = npos / game->width;
    }
  unlock_battlefield(game->semid);
}
