/*
** ia_loader.c for ia_loader.c in /home/ngonta_e//my_home/rendu/c/lemipc/core
** 
** Made by eugene-valentin ngontang-tchiadjie
** Login   <ngonta_e@epitech.net>
** 
** Started on  Wed May 18 20:22:51 2011 eugene-valentin ngontang-tchiadjie
** Last update Sun May 22 18:25:19 2011 eugene-valentin ngontang-tchiadjie
*/

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lemipc.h"

t_sym		load_tab[] =
  {
    {"do_init", &get_init},
    {"do_play", &get_play},
    {"do_free", &get_free},
    {"", NULL}
  };

static int	load_default_ia(t_ia * ia)
{
  ia->init = &default_ia_init;
  ia->play = &default_ia_play;
  ia->free = &default_ia_free;
  return (0);
}

static int	set_ia_sym(t_ia *ia)
{
  int		i;

  for (i = 0; load_tab[i].load_sym != NULL; ++i)
    {
      if (load_tab[i].load_sym(ia) == false)
	{
	  dlclose(ia->handle);
	  ia->handle = NULL;
	  load_default_ia(ia);
	  return (1);
	}
    }
  return (0);
}

static int	load_ia(t_ia * ia, char * ia_name)
{
  if ((ia->handle = dlopen(ia_name, RTLD_LAZY)) == NULL)
    {
      printf("%s\nYou entered a wrong IA lib name,"
	     "then your IA will be set to defaut values\n", dlerror());
      return (load_default_ia(ia));
    }
  else
    return (set_ia_sym(ia));
}

void		unload_ia_library(t_ia * ia)
{
  if (ia->handle != NULL)
    {
      dlerror();
      printf("We have to free the lib handler\n");
      if (dlclose(ia->handle) != 0)
	fprintf(stderr, "%s\nError when freeing the lib handler", dlerror());
    }
  else
    printf("No lib handler to free, we just leave the process!!!!\n");
}

int		load_ia_library(t_ia * ia, char * name)
{
  int		error = 0;
  char *	realname = NULL;

  ia->handle = NULL;
  if (name != NULL)
    {
      if ((realname = malloc((strlen(name) + 3) * sizeof(*realname))) == NULL)
	error = load_default_ia(ia);
      else
	{
	  realname[0] = '\0';
	  if (!(name[0] == '.' && name[1] == '/'))
	    realname = strcat(realname, "./");
	  realname = strncat(realname, name, strlen(name));
	  error = load_ia(ia, realname);
	}
    }
  else
    error = load_default_ia(ia);
  free(realname);
  return (error);
}
