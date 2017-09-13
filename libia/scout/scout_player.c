/*
** scout_player.c for scout_player.c in /home/ngonta_e//my_home/rendu/c/lemipc/lemipc_soldier/libia/soldier
** 
** Made by eugene-valentin ngontang-tchiadjie
** Login   <ngonta_e@epitech.net>
** 
** Started on  Sun May 22 16:04:55 2011 eugene-valentin ngontang-tchiadjie
** Last update Sun May 22 22:50:20 2011 adrien barrau
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
  printf("[scout_player] Loading library...\n");
}

ia_settings *	do_init(t_game * game __attribute__ ((unused)))
{
  printf("[scout_player] Initialisation ..\n");
  return (NULL);
}

void		do_play(t_game * game,
			ia_settings * setting __attribute__((unused)))
{
  int		wt_error, i = 0;
  bool		found = false;
  msg_queue	send_msg;

  lock_battlefield(game->semid);
  while (i < (game->width * game->height) && !false)
    {
      if (game->battlefield[i] != 0 && game->battlefield[i] != game->team_num)
	{
	  found = true;
	  break;
	}
      ++i;
    }
  unlock_battlefield(game->semid);
  if (found)
    {
      send_msg.type = game->team_num;
      sprintf(send_msg.queue_txt, "enemy %d:%d",
	      i % game->width, i / game->height);
      if ((wt_error = msgsnd(game->comid, &send_msg,
			     strlen(send_msg.queue_txt), IPC_NOWAIT | MSG_NOERROR)) < 0)
	fprintf(stderr, "Error when writing on the queue\n");
    }
  go_somewhere(game);
}

void		do_free(t_game * game __attribute__((unused)),
			ia_settings * setting __attribute__((unused)))
{
  printf("[scout_player] Leaving ..\n");
}

void    __attribute__((destructor)) end()
{
  printf("[scout_player] Unloading library...\n");
}
