/*
** soldier_player.c for soldier_player.c in /home/ngonta_e//my_home/rendu/c/lemipc/lemipc_soldier/libia/soldier
** 
** Made by eugene-valentin ngontang-tchiadjie
** Login   <ngonta_e@epitech.net>
** 
** Started on  Sun May 22 16:01:15 2011 eugene-valentin ngontang-tchiadjie
** Last update Sun May 22 21:27:06 2011 adrien barrau
*/

#include <stdio.h>
#include "lemipc.h"

void    __attribute__((constructor)) begin()
{
  printf("[soldier_player] Loading library...\n");
}

ia_settings *	do_init(t_game * game __attribute__((unused)))
{
  printf("[soldier_player] Initialisation ..\n");
  return (NULL);
}

void		do_play(t_game * game,
			ia_settings * setting __attribute__((unused)))
{
  int		x = 0, y = 0;

  if (has_order(game, &x, &y))
    go_there(game, x, y);
  else
    go_somewhere(game);
}

void		do_free(t_game * game __attribute__((unused)),
			ia_settings * setting __attribute__((unused)))
{
  printf("[soldier_player] Leaving ..\n");
}

void    __attribute__((destructor)) end()
{
  printf("[soldier_player] Unloading library...\n");
}
