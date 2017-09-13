/*
** go_order.c for <Chef> in /home/barrau_a//c/lemipc_soldier/libia/chef
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 21:47:09 2011 adrien barrau
** Last update Sun May 22 21:55:42 2011 adrien barrau
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lemipc.h"

bool		go_order(int * x, int * y, char * msg)
{
  char *	end_msg;

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
