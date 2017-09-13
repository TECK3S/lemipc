/*
** init_sdl_ipcs.c for <Viewer> in /home/barrau_a//c/lemipc_soldier
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sat May 21 14:59:50 2011 adrien barrau
** Last update Sun May 22 18:11:36 2011 adrien barrau
*/

#define	 _SVID_SOURCE
#define	 _XOPEN_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "viewer.h"

static bool	get_key(key_t * key)
{
  char	path[PATH_MAX];

  if (getcwd(path, PATH_MAX) == NULL)
    return (false);
  if ((*key = ftok(path, KEY_DISTURBED)) == -1)
    return (false);
  return (true);
}

static int	init_shm(t_view * view, key_t key)
{
  if ((view->shmid = shmget(key,
			    1,
			    SHM_R)) == -1)
    {
      if (errno == ENOENT)
	return (WAIT);
      else
	return (ERROR);
    }
  if ((view->battlefield = shmat(view->shmid, NULL, 0)) == (void *)-1)
    {
      view->battlefield = NULL;
      return (ERROR);
    }
  return (OKAY);
}

static bool	init_sem(t_view * view, key_t key)
{
  if ((view->semid = semget(key,
			    NUMBER_OF_SEM,
			    SHM_R | SHM_W)) == -1)
    return (false);
  return (true);
}

static void	set_size(t_view * view)
{
  lock_battlefield(view->semid);
  view->width = view->battlefield[0];
  view->height = view->battlefield[1];
  view->battlefield = &(view->battlefield[2]);
  unlock_battlefield(view->semid);
}

int	join_battlefield(t_view * view)
{
  key_t	key;
  bool	joining = false, quit = false;
  int	shm_init = WAIT;

  if (get_key(&key) == false)
    return (BATTLEFIELD_KEY_ERR_CODE);
  while (!joining && !quit)
    {
      quit = getInput(view);
      shm_init = init_shm(view, key);
      if (shm_init == ERROR)
	break;
      if (shm_init == OKAY)
	joining = true;
      display_background(view);
      display_wait(view);
      SDL_Flip(view->screen);
    }
  if (joining && init_sem(view, key) == false)
    return (BATTLEFIELD_SEM_ERR_CODE);
  set_size(view);
  return (NO_ERROR);
}
