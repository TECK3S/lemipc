/*
** chef_player.c for chef_player.c in /home/ngonta_e//my_home/rendu/c/lemipc/lemipc_soldier/libia/soldier
** 
** Made by eugene-valentin ngontang-tchiadjie
** Login   <ngonta_e@epitech.net>
** 
** Started on  Sun May 22 16:02:27 2011 eugene-valentin ngontang-tchiadjie
** Last update Sun May 22 22:49:16 2011 adrien barrau
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lemipc.h"

void    __attribute__((constructor)) begin()
{
  printf("[chef_player] Loading library...\n");
}

ia_settings *	do_init(t_game * game __attribute__((unused)))
{
  printf("[chef_player] Initialisation ..\n");
  return (NULL);
}

void		do_play(t_game * game,
			ia_settings * setting __attribute__((unused)))
{
  size_t	rd_size;
  int		wt_error, x, y;
  msg_queue	rcv_msg;
  msg_queue	send_msg;

  if ((rd_size = msgrcv(game->comid,
			&rcv_msg, MAX_MSGQ_LENGTH, game->team_num,
			IPC_NOWAIT | MSG_NOERROR)) > 0
      && strncmp(rcv_msg.queue_txt, "enemy ", 6) == 0)
    {
      send_msg.type = game->team_num;
      snprintf(send_msg.queue_txt, 3, "go ");
      memcpy(send_msg.queue_txt + 3, rcv_msg.queue_txt + 6, rd_size - 6);
      if ((wt_error = msgsnd(game->comid,
			     &send_msg, strlen(send_msg.queue_txt),
			     IPC_NOWAIT | MSG_NOERROR)) < 0)
	fprintf(stderr, "Error when writing on the queue\n");
      if (go_order(&x, &y, send_msg.queue_txt))
	go_there(game, x, y);
    }
  else
    {
      go_somewhere(game);
      come_into_me(game);
    }
}

void		do_free(t_game * game __attribute__((unused)),
			ia_settings *  setting __attribute__((unused)))
{
  printf("[chef_player] Leaving ..\n");
}

void    __attribute__((destructor)) end()
{
  printf("[chef_player] Unloading library...\n");
}
