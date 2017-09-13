/*
** ipcs_init.c for <Lemipc> in /home/barrau_a//c/lemipc_soldier/core
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 18:04:54 2011 adrien barrau
** Last update Sun May 22 18:06:08 2011 adrien barrau
*/

#define	 _SVID_SOURCE
#define	 _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include "lemipc.h"

static bool	creator = false;

bool	get_key(key_t * key)
{
  char	path[PATH_MAX];

  if (getcwd(path, PATH_MAX) == NULL)
    return (false);
  if ((*key = ftok(path, KEY_DISTURBED)) == -1)
    return (false);
  return (true);
}

bool	init_shm(t_game * game, key_t key)
{
  if ((game->shmid = shmget(key,
			    (game->width * game->height) + 2,
			    IPC_CREAT | IPC_EXCL | SHM_R | SHM_W)) == -1)
    {
      if ((game->shmid = shmget(key,
				1,
				SHM_R | SHM_W)) == -1)
	return (false);
      else
	printf("%s\n", BATTLEFIELD_JOIN_MSG);
    }
  else
    {
      printf("%s\n", BATTLEFIELD_CREATION_MSG);
      creator = true;
    }
  if ((game->battlefield = shmat(game->shmid, NULL, 0)) == (void *)-1)
    {
      game->battlefield = NULL;
      return (false);
    }
  return (true);
}

bool	init_sem(t_game * game, key_t key)
{
  if ((game->semid = semget(key,
			    NUMBER_OF_SEM,
			    IPC_CREAT | IPC_EXCL | SHM_R | SHM_W)) == -1)
    {
      if ((game->semid = semget(key,
				NUMBER_OF_SEM,
				SHM_R | SHM_W)) == -1)
	return (false);
    }
  else
    {
      if (semctl(game->semid, 0, SETVAL, 1) == -1)
	return (false);
    }
  return (true);
}

bool	init_msgq(t_game * game, key_t key)
{
  if ((game->comid = msgget(key,
			    IPC_CREAT | IPC_EXCL | SHM_R | SHM_W)) == -1)
    {
      if ((game->comid = msgget(key,
				SHM_R | SHM_W)) == -1)
	return (false);
    }
  return (true);
}

void	creation(t_game * game)
{
  if (creator == true)
    init_battlefield(game);
  else
    set_size(game);
}
