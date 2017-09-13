/*
** get_symbols.c for get_symbols\ in /home/ngonta_e//my_home/rendu/c/lemipc/lemipc_soldier
** 
** Made by eugene-valentin ngontang-tchiadjie
** Login   <ngonta_e@epitech.net>
** 
** Started on  Thu May 19 01:15:49 2011 eugene-valentin ngontang-tchiadjie
** Last update Sun May 22 17:43:43 2011 adrien barrau
*/

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "lemipc.h"

bool		get_init(t_ia * ia)
{
  bool		find = true;

  dlerror();
  if ((ia->init = (ia_init)dlsym(ia->handle, "do_init")) == NULL)
    {
      fprintf(stderr,
	      "%s\nfail to load the symbol 'init' from the lib\n",
	      dlerror());
      find = false;
    }
  return (find);
}

bool		get_play(t_ia * ia)
{
  bool		find = true;

  dlerror();
  if ((ia->play = (ia_play)dlsym(ia->handle, "do_play")) == NULL)
    {
      fprintf(stderr,
	      "%s\nfail to load the symbol 'play' from the lib\n",
	      dlerror());
      find = false;
    }
  return (find);
}

bool		get_free(t_ia * ia)
{
  bool		find = true;

  dlerror();
  if ((ia->free = (ia_free)dlsym(ia->handle, "do_free")) == NULL)
    {
      fprintf(stderr,
	      "%s\nfail to load the symbol 'free' from the lib\n",
	      dlerror());
      find = false;
    }
  return (find);
}
