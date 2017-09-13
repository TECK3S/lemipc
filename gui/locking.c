/*
** locking.c for <Lemipc> in /home/barrau_a//c/lemipc_soldier/core
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Thu May 19 23:39:47 2011 adrien barrau
** Last update Sun May 22 17:02:02 2011 adrien barrau
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "viewer.h"

void		lock_battlefield(int semid)
{
  struct sembuf	sops;
  int		errcode = 0;

  sops.sem_num = 0;
  sops.sem_op = -1;
  sops.sem_flg = 0;
  if (semop(semid, &sops, 1) == -1)
    errcode = NO_ERROR;
}

void		unlock_battlefield(int semid)
{
  struct sembuf	sops;
  int		errcode = 0;

  sops.sem_num = 0;
  sops.sem_op = 1;
  sops.sem_flg = 0;
  if (semop(semid, &sops, 1) == -1)
    errcode = NO_ERROR;
}
