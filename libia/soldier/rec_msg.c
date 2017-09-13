/*
** rec_msg.c for <Soldier> in /home/barrau_a//c/lemipc_soldier/libia/soldier
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 20:00:51 2011 adrien barrau
** Last update Sun May 22 22:50:49 2011 adrien barrau
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "lemipc.h"

char *			rec_msg(int comid, int channel)
{
  static msg_queue	msg;
  ssize_t		size;

  if ((size = msgrcv(comid,
		     &msg,
		     MAX_MSGQ_LENGTH,
		     channel,
		     IPC_NOWAIT | MSG_NOERROR)) == -1)
    return (NULL);
  if (size == MAX_MSGQ_LENGTH)
    msg.queue_txt[MAX_MSGQ_LENGTH - 1] = '\0';
  else
    msg.queue_txt[size] = '\0';
  return (msg.queue_txt);
}
