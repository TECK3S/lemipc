/*
** default_ia.c for default_ia.c in /home/ngonta_e//my_home/rendu/c/lemipc/lemipc_soldier
** 
** Made by eugene-valentin ngontang-tchiadjie
** Login   <ngonta_e@epitech.net>
** 
** Started on  Thu May 19 02:28:16 2011 eugene-valentin ngontang-tchiadjie
** Last update Sun May 22 21:31:21 2011 adrien barrau
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

void 		default_ia_play(t_game * game,
				ia_settings * setting __attribute__((unused)))
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
