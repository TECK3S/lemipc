/*
** game.c for game.c in /home/ngonta_e//my_home/rendu/c/lemipc/core
** 
** Made by eugene-valentin ngontang-tchiadjie
** Login   <ngonta_e@epitech.net>
** 
** Started on  Wed May 18 22:23:14 2011 eugene-valentin ngontang-tchiadjie
** Last update Sun May 22 21:12:07 2011 eugene-valentin ngontang-tchiadjie
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "lemipc.h"

static void	set_xy(t_game * game, int pos)
{
  game->battlefield[pos] = game->team_num;
  game->pos.x = pos % game->width;
  game->pos.y = pos / game->width;
}

static bool	set_position(t_game * game)
{
  int	i = 0, pos;

  lock_battlefield(game->semid);
  while (i < NB_TRY_POS)
    {
      pos = random() % (game->width * game->height);
      if (game->battlefield[pos] == 0)
	break;
      i++;
    }
  if (i == NB_TRY_POS)
    {
      pos = 0;
      while (pos < (game->width * game->height))
	{
	  if (game->battlefield[pos] == 0)
	    break;
	  pos++;
	}
      if (pos == (game->width * game->height))
	return (false);
    }
  set_xy(game, pos);
  unlock_battlefield(game->semid);
  return (true);
}

void		init_game(t_game * my_game, t_opts * opts)
{
  char *	h = NULL;

  my_game->team_num = opts->num_team;
  my_game->time = opts->time;
  if (opts->size)
    {
      my_game->width = atoi(opts->size);
      my_game->height = 0;
      h = strchr(opts->size, 'x');
      if (h)
	my_game->height = atoi(&(h[1]));
    }
  else
    {
      my_game->width = DEFAULT_W;
      my_game->height = DEFAULT_H;
    }
  if (my_game->width < MIN_W || my_game->width > MAX_W)
    my_game->width = DEFAULT_W;
  if (my_game->height < MIN_H || my_game->height > MAX_H)
    my_game->height = DEFAULT_H;
 }

static void	lobby(t_game * game)
{
  printf("%s\n", LOBBY_WAITING);
  while (!enough_player(game));
}

void		launch_game(t_game * my_game, t_ia * my_ia)
{
  bool		game_over = false;

  if (init_ipcs(my_game) && set_position(my_game))
    {
      lobby(my_game);
      my_ia->settings = my_ia->init(my_game);
      while (!game_over)
	{
	  my_ia->play(my_game, my_ia->settings);
	  usleep(my_game->time);
	  game_over = end_of_game(my_game);
	}
      my_ia->free(my_game, my_ia->settings);
      free_ipcs(my_game);
    }
  else
    printf("%s\n", CANNOT_JOIN_BATTLEFIELD);
}
