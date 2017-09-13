/*
** go_left.c for <Scout> in /home/barrau_a//c/lemipc_soldier/libia/scout
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 22:13:26 2011 adrien barrau
** Last update Sun May 22 22:13:53 2011 adrien barrau
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
