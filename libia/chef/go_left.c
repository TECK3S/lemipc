/*
** go_left.c for <Chef> in /home/barrau_a//c/lemipc_soldier/libia/chef
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 21:51:34 2011 adrien barrau
** Last update Sun May 22 21:51:46 2011 adrien barrau
*/

#include <stdio.h>
#include <stdlib.h>
#include "lemipc.h"

int	go_left(t_game * game)
{
  if (game->pos.x == 0)
    return ((game->pos.y * game->width) + game->pos.x);
  else
    return ((game->pos.y * game->width) + (game->pos.x - 1));
}
