/*
** come_into_me.c for come_into_me.c in /home/ngonta_e//my_home/rendu/c/lemipc/lemipc_soldier
** 
** Made by eugene-valentin ngontang-tchiadjie
** Login   <ngonta_e@epitech.net>
** 
** Started on  Sun May 22 18:51:13 2011 eugene-valentin ngontang-tchiadjie
** Last update Sun May 22 21:12:09 2011 eugene-valentin ngontang-tchiadjie
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lemipc.h"

void	come_into_me(t_game const * game)
{
  int		wt_error;
  msg_queue	send_msg;
  char		str_x[MAX_MSGQ_LENGTH];
  char		str_y[MAX_MSGQ_LENGTH];

  send_msg.type = game->team_num;
  sprintf(str_x, "%d", game->pos.x);
  sprintf(str_y, "%d", game->pos.y);
  sprintf(send_msg.queue_txt, "go %s:%s", str_x, str_y);
  if ((wt_error = msgsnd(game->comid, &send_msg,
			 strlen(send_msg.queue_txt), IPC_NOWAIT | MSG_NOERROR)) < 0)
    fprintf(stderr, "Error when writing on the queue\n");
}
