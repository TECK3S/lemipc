/*
** args.c for <Jtebez> in /home/barrau_a//c/lemipc_soldier
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Thu May 19 16:30:41 2011 adrien barrau
** Last update Thu May 19 16:43:56 2011 adrien barrau
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lemipc.h"

bool	parse_arg(t_opts * opts, int ac, char ** av)
{
  int		opt;

  while ((opt = getopt(ac, av, "n:t:i:s:")) != -1)
    {
      switch (opt)
	{
	case 'n':
	  opts->num_team = atoi(optarg);
	  break;
	case 't':
	  opts->time = (unsigned int)atoi(optarg);
	  break;
	case 'i':
	  opts->ia_name = optarg;
	  break;
	case 's':
	  opts->size = optarg;
	  break;
	default:
	  return (false);
	}
    }
  return (true);
}

void	init_opts(t_opts * opts)
{
  opts->num_team = 0;
  opts->time = 0;
  opts->ia_name = NULL;
  opts->size = NULL;
}
