/*
** main.c for main.c in /home/ngonta_e//my_home/rendu/c/lemipc/core
** 
** Made by eugene-valentin ngontang-tchiadjie
** Login   <ngonta_e@epitech.net>
** 
** Started on  Wed May 18 19:42:13 2011 eugene-valentin ngontang-tchiadjie
** Last update Fri May 20 04:05:23 2011 adrien barrau
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lemipc.h"

int		main(int ac, char **av)
{
  t_ia		my_ia;
  t_game	my_game;
  t_opts	opts;

  srand(time(NULL));
  init_opts(&opts);
  if (parse_arg(&opts, ac, av) && opts.num_team > 0 && opts.num_team <= 127)
    {
      load_ia_library(&my_ia, opts.ia_name);
      init_game(&my_game, &opts);
      launch_game(&my_game, &my_ia);
      unload_ia_library(&my_ia);
    }
  else
    fprintf(stderr, "Syntax error\n%s\n", USAGE);
  return (0);
}
