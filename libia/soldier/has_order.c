/*
** has_order.c for <Soldier> in /home/barrau_a//c/lemipc_soldier/libia/soldier
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 19:25:30 2011 adrien barrau
** Last update Sun May 22 21:47:17 2011 adrien barrau
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lemipc.h"

bool		has_order(t_game * game, int * x, int * y)
{
  char *	msg;
  char *	end_msg;

  msg = rec_msg(game->comid, game->team_num);
  if (msg != NULL
      && strncmp(msg, GO_THERE, strlen(GO_THERE)) == 0
      && (end_msg = strchr(msg, ':')) != NULL)
    {
      *x = atoi(&(msg[strlen(GO_THERE)]));
      *y = atoi(&(end_msg[1]));
      return (true);
    }
  else
    return (false);
}
