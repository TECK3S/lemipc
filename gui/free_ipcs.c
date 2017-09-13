/*
** free_ipcs.c for <Viewer> in /home/barrau_a//c/lemipc_soldier/gui
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 03:08:54 2011 adrien barrau
** Last update Sun May 22 03:59:23 2011 adrien barrau
*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include "viewer.h"

void	free_ipcs(t_view * view)
{
  if (view->battlefield && shmdt(&(view->battlefield[-2])) == -1)
    fprintf(stderr, "%s\n", BATTLEFIELD_DTSHM_ERR_MSG);
}
