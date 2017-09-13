/*
** game_end.c for <Lemipc> in /home/barrau_a//c/lemipc_soldier/core
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sun May 22 17:55:29 2011 adrien barrau
** Last update Sun May 22 23:00:57 2011 adrien barrau
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "lemipc.h"

bool	are_you_killing_me(t_game * game)
{
  int		i, j, box[8];

  box[0] = GET_UP(game->pos.x, game->pos.y);
  box[1] = GET_UP_RI(game->pos.x, game->pos.y);
  box[2] = GET_RIGHT(game->pos.x, game->pos.y);
  box[3] = GET_DO_RI(game->pos.x, game->pos.y);
  box[4] = GET_DOWN(game->pos.x, game->pos.y);
  box[5] = GET_DO_LE(game->pos.x, game->pos.y);
  box[6] = GET_LEFT(game->pos.x, game->pos.y);
  box[7] = GET_UP_LE(game->pos.x, game->pos.y);
  for (i = 0; i < 8; ++i)
    {
      if (box[i] == -1 || game->battlefield[box[i]] == 0
	  || game->battlefield[box[i]] == game->team_num)
	continue;
      for (j = i + 1; j < 8; ++j)
	if (box[j] != -1 && game->battlefield[box[i]]
	    == game->battlefield[box[j]])
	  break;
      if (j < 8)
	break;
    }
  if (i < 8)
    return (true);
  return (false);
}

bool	am_i_winner(t_game * game)
{
  int		num = 0, i = 0, lim = game->width * game->height;

  while (i < lim)
    {
      if (game->battlefield[i] != 0)
	{
	  if (num != 0 && game->battlefield[i] != num)
	    break;
	  num = game->battlefield[i];
	}
      ++i;
    }
  if (i < lim)
    return (false);
  return (true);
}

bool	c_est_draw_l(t_game * game)
{
  int		i = 0, lim = game->width * game->height;
  char		nums[128];

  memset(nums, 0, 128);
  while (i < lim)
    {
      if (game->battlefield[i] > 0)
	{
	  if (nums[(int)game->battlefield[i]] == 1)
	    break;
	  nums[(int)game->battlefield[i]] = 1;
	}
      ++i;
    }
  if (i < lim)
    return (false);
  return (true);
}

bool	end_of_game(t_game * game)
{
  bool		game_over = false;

  lock_battlefield(game->semid);
  if ((game_over = are_you_killing_me(game)))
    {
      game->battlefield[(game->pos.y * game->width) + game->pos.x] = 0;
      printf("%s\n", DEAD_MSG);
    }
  if (!game_over)
    {
      if ((game_over = c_est_draw_l(game)))
	printf("%s\n", DRAW_MATCH_MSG);
    }
  if (!game_over)
    {
      if ((game_over = am_i_winner(game)))
	printf("%s\n", WIN_MATCH_MSG);
    }
  unlock_battlefield(game->semid);
  return (game_over);
}

bool	enough_player(t_game * game)
{
  int		i = 0, lim = game->width * game->height, teams = 0;
  char		nums[128];

  memset(nums, 0, 128);
  lock_battlefield(game->semid);
  while (i < lim)
    {
      if (game->battlefield[i] > 0)
	{
	  if (nums[(int)game->battlefield[i]] == 1)
	    teams += 1;
	  nums[(int)game->battlefield[i]] += 1;
	}
      ++i;
    }
  unlock_battlefield(game->semid);
  if (teams >= 2)
    return (true);
  return (false);
}
