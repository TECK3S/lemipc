/*
** jammer_player.c for jammer_player.c in /home/ngonta_e//my_home/rendu/c/lemipc/lemipc_soldier/libia/soldier
** 
** Made by eugene-valentin ngontang-tchiadjie
** Login   <ngonta_e@epitech.net>
** 
** Started on  Sun May 22 16:06:08 2011 eugene-valentin ngontang-tchiadjie
** Last update Sun May 22 22:49:42 2011 adrien barrau
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lemipc.h"

void    __attribute__((constructor)) debut()
{
  printf("[jammer_player] Loading library...\n");
}

ia_settings *	do_init(t_game * game __attribute__((unused)))
{
  printf("[jammer_player] Initialisation ..\n");
  return (NULL);
}

void			do_play(t_game * game,
				ia_settings * setting __attribute__((unused)))
{
  int			channel = 0;
  int			wt_error;
  msg_queue		send_msg;
  char		str_x[MAX_MSGQ_LENGTH];
  char		str_y[MAX_MSGQ_LENGTH];

  channel = random() % 128;
  if (channel != game->team_num)
    {
      send_msg.type = channel;
      sprintf(str_x, "%li", (random() % game->width));
      sprintf(str_y, "%li", (random() % game->height));
      sprintf(send_msg.queue_txt, "go %s:%s", str_x, str_y);
      if ((wt_error = msgsnd(game->comid, &send_msg,
			     strlen(send_msg.queue_txt), IPC_NOWAIT | MSG_NOERROR)) < 0)
	fprintf(stderr, "Error when writing on the queue\n");
    }
  go_somewhere(game);
}

void		do_free(t_game * game __attribute__((unused)),
			ia_settings * setting __attribute__((unused)))
{
  printf("[jammer_player] Leaving ..\n");
}

void    __attribute__((destructor)) fin()
{
  printf("[jammer_player] Unloading library...\n");
}
