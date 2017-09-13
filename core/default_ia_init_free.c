/*
** default_ia_init_free.c for <Lemipc> in /home/barrau_a//c/lemipc_soldier/core
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 17:46:06 2011 adrien barrau
** Last update Sun May 22 20:25:07 2011 adrien barrau
*/

#include <stdio.h>
#include <stdlib.h>
#include "lemipc.h"

ia_settings *	default_ia_init(t_game * game __attribute__((unused)))
{
  return (NULL);
}

void 		default_ia_free(t_game * game __attribute__((unused)),
				ia_settings * setting __attribute__((unused)))
{ }

int	go_left(t_game * game)
{
  if (game->pos.x == 0)
    return ((game->pos.y * game->width) + game->pos.x);
  else
    return ((game->pos.y * game->width) + (game->pos.x - 1));
}
