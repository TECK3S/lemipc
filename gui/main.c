/*
** main.c for main.c in /home/ngonta_e//my_home/rendu/c/lemipc/lemipc_soldier
** 
** Made by eugene-valentin ngontang-tchiadjie
** Login   <ngonta_e@epitech.net>
** 
** Started on  Thu May 19 01:56:45 2011 eugene-valentin ngontang-tchiadjie
** Last update Sun May 22 03:51:53 2011 adrien barrau
*/

#include <stdio.h>
#include "viewer.h"

static const char *	errors[]=
  {
    "",
    SDL_INIT_ERR_MSG,
    VIDEOMODE_ERR_MSG,
    LOAD_ERR_MSG,
    BATTLEFIELD_KEY_ERR_MSG,
    BATTLEFIELD_SEM_ERR_MSG
  };

int		main()
{
  int		err_code = 0;
  t_view	view;

  err_code = init_window(&view);
  if (!err_code)
    err_code = join_battlefield(&view);
  if (!err_code)
    view_battlefield(&view);
  if (!err_code)
    free_ipcs(&view);
  if (!err_code)
    SDL_Quit();
  if (err_code)
    fprintf(stderr, "Error: %s\n", errors[err_code * -1]);
  return (err_code);
}
