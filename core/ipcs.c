/*
** ipcs.c for <Lemipc> in /home/barrau_a//c/lemipc_soldier/core
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Wed May 18 23:55:32 2011 adrien barrau
** Last update Sun May 22 18:09:03 2011 adrien barrau
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

void	init_battlefield(t_game * game)
{
  lock_battlefield(game->semid);
  memset((void *)game->battlefield, 0, (game->width * game->height) + 2);
  game->battlefield[0] = (char)game->width;
  game->battlefield[1] = (char)game->height;
  game->battlefield = &(game->battlefield[2]);
  unlock_battlefield(game->semid);
}

void	set_size(t_game * game)
{
  lock_battlefield(game->semid);
  game->width = game->battlefield[0];
  game->height = game->battlefield[1];
  game->battlefield = &(game->battlefield[2]);
  unlock_battlefield(game->semid);
}

bool	init_ipcs(t_game * game)
{
  key_t	key;

  if (get_key(&key) == false)
    {
      fprintf(stderr, "%s\n", BATTLEFIELD_KEY_ERR_MSG);
      return (false);
    }
  if (init_shm(game, key) == false)
    {
      fprintf(stderr, "%s\n", BATTLEFIELD_SHM_ERR_MSG);
      return (false);
    }
  if (init_sem(game, key) == false)
    {
      fprintf(stderr, "%s\n", BATTLEFIELD_SEM_ERR_MSG);
      return (false);
    }
  creation(game);
  if (init_msgq(game, key) == false)
    {
      fprintf(stderr, "%s\n", BATTLEFIELD_COM_ERR_MSG);
      return (false);
    }
  return (true);
}

static bool		last_men_standing(t_game * game)
{
  struct shmid_ds	infos;

  if (shmctl(game->shmid, IPC_STAT, &infos) == -1)
    return (false);
  if (infos.shm_nattch <= 1)
    {
      printf("%s\n", BATTLEFIELD_DESTROY_MSG);
      return (true);
    }
  return (false);
}

void	free_ipcs(t_game * game)
{
  if (game->battlefield && shmdt(&(game->battlefield[-2])) == -1)
    fprintf(stderr, "%s\n", BATTLEFIELD_DTSHM_ERR_MSG);
  if (last_men_standing(game))
    {
      if (game->shmid != -1 && shmctl(game->shmid, IPC_RMID, NULL) == -1)
	fprintf(stderr, "%s\n", BATTLEFIELD_DSHM_ERR_MSG);
      if (game->semid != -1 && semctl(game->semid, 0, IPC_RMID) == -1)
	fprintf(stderr, "%s\n", BATTLEFIELD_DSEM_ERR_MSG);
      if (game->comid != -1 && msgctl(game->comid, IPC_RMID, NULL) == -1)
	fprintf(stderr, "%s\n", BATTLEFIELD_DCOM_ERR_MSG);
    }
}
