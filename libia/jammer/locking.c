/*
** locking.c for <Lemipc> in /home/barrau_a//c/lemipc_soldier/core
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Thu May 19 23:39:47 2011 adrien barrau
** Last update Fri May 20 03:59:43 2011 adrien barrau
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "lemipc.h"

void		lock_battlefield(int semid)
{
  struct sembuf	sops;

  sops.sem_num = 0;
  sops.sem_op = -1;
  sops.sem_flg = 0;
  if (semop(semid, &sops, 1) == -1)
    printf("%s\n", CANNOT_LOCK_BATTLEFIELD);
}

void		unlock_battlefield(int semid)
{
  struct sembuf	sops;

  sops.sem_num = 0;
  sops.sem_op = 1;
  sops.sem_flg = 0;
  if (semop(semid, &sops, 1) == -1)
    printf("%s\n", CANNOT_UNLOCK_BATTLEFIELD);
}
