/*
** lemipc.h for <Lemipc> in /home/ngonta_e//my_home/rendu/c/lemipc/core
** 
** Made by eugene-valentin ngontang-tchiadjie
** Login   <ngonta_e@epitech.net>
** 
** Started on  Wed May 18 22:48:41 2011 eugene-valentin ngontang-tchiadjie
** Last update Sun May 22 21:56:01 2011 adrien barrau
*/

#ifndef		LEMIPC_H_
# define	LEMIPC_H_

# define	USAGE				("Usage: ./lemipc -n TEAM [-i IA_NAME] [-t TIME] [-s WxH]")

# define	PATH_MAX			(1024)
# define	MAX_MSGQ_LENGTH			(512)
# define	KEY_DISTURBED			(0xdeadbeef)
# define	NUMBER_OF_SEM			(1)
# define	NB_TRY_POS			(5)

# define	BATTLEFIELD_JOIN_MSG		("I'am joining the battlefield sir !")
# define	BATTLEFIELD_CREATION_MSG	("I'am building the battlefield sir !")
# define	BATTLEFIELD_DESTROY_MSG		("I'am destroying the battlefield sir !")
# define	BATTLEFIELD_KEY_ERR_MSG		("I cannot get the key..")
# define	BATTLEFIELD_SHM_ERR_MSG		("I cannot create the battlefield..")
# define	BATTLEFIELD_SEM_ERR_MSG		("I cannot create the semaphore..")
# define	BATTLEFIELD_COM_ERR_MSG		("I cannot create the com..")
# define	BATTLEFIELD_DTSHM_ERR_MSG	("I cannot leave from the battlefield..")
# define	BATTLEFIELD_DSHM_ERR_MSG	("I cannot destroy the battlefield..")
# define	BATTLEFIELD_DSEM_ERR_MSG	("I cannot destroy the semaphore..")
# define	BATTLEFIELD_DCOM_ERR_MSG	("I cannot destroy the com..")
# define	CANNOT_LOCK_BATTLEFIELD		("I cannot lock the battlefield")
# define	CANNOT_UNLOCK_BATTLEFIELD	("I cannot unlock the battlefield")
# define	CANNOT_JOIN_BATTLEFIELD		("I cannot join the battlefield")
# define	DEAD_MSG			("I died with honors")
# define	DRAW_MATCH_MSG			("The winner cannot be determined")
# define	WIN_MATCH_MSG			("We've killed everyone sir !")
# define	LOBBY_WAITING			("Waiting in the lobby for players to come..")

# define	MIN_W				(10)
# define	MAX_W				(100)
# define	DEFAULT_W			(20)
# define	MIN_H				(10)
# define	MAX_H				(100)
# define	DEFAULT_H			(20)

# define	GO_THERE			("go ")

# define	GET_UP(x, y)			((y) > 0 ? ((((y) - 1) * game->width) + (x)) : -1)
# define	GET_UP_RI(x, y)			(((y) > 0 && (x) < game->width - 1) ? (((y - 1) * game->width) + (x) + 1) : -1)
# define	GET_RIGHT(x, y)			((x) < (game->width - 1) ? ((y * game->width) + (x) + 1) : -1)
# define	GET_DO_RI(x, y)			((((y) + 1) < (game->height - 1) && (x) < game->width) ? ((((y) + 1) * game->width) + (x) + 1) : -1)
# define	GET_DOWN(x, y)			(((y) + 1) < (game->height - 1) ? ((((y) + 1) * game->width) + (x)) : -1)
# define	GET_DO_LE(x, y)			((((y) + 1) < (game->height - 1) && (x) > 0) ? ((((y) + 1) * game->width) + (x) - 1) : -1)
# define	GET_LEFT(x, y)			((x) > 0 ? ((y * game->width) + (x) - 1) : -1)
# define	GET_UP_LE(x, y)			(((y) > 0 && (x) > 0) ? (((y - 1) * game->width) + (x) - 1) : -1)

# define	false				(0)
# define	true				(!false)
typedef		int				bool;

typedef		char	battlefield;

typedef		struct
{
  int		x;
  int		y;
}		position;

typedef		struct
{
  long		type;
  char		queue_txt[MAX_MSGQ_LENGTH];
}		msg_queue;


typedef		struct
{
  int		team_num;
  unsigned int	time;
  int		width;
  int		height;
  position	pos;
  int		shmid;
  battlefield *	battlefield;
  int		semid;
  int		comid;
}		t_game;

typedef		void	ia_settings;
typedef		ia_settings * (* ia_init)(t_game *);
typedef		void (* ia_play)(t_game *, ia_settings *);
typedef		void (* ia_free)(t_game *, ia_settings *);

typedef		struct
{
  ia_settings *	settings;
  void *	handle;
  ia_init	init;
  ia_play	play;
  ia_free	free;
}		t_ia;

typedef		struct
{
  char *	symbol;
  bool (* load_sym)(t_ia * ia);
}		t_sym;

typedef		struct
{
  int		num_team;
  int		time;
  char *	ia_name;
  char *	size;
}		t_opts;

#include <sys/types.h>

/*	game.c			*/
void		init_game(t_game * my_game, t_opts * opts);
void		launch_game(t_game * my_game, t_ia * my_ia);

/*	game_end.c		*/
bool		are_you_killing_me(t_game * game);
bool		am_i_winner(t_game * game);
bool		c_est_draw_l(t_game * game);
bool		end_of_game(t_game * game);
bool		enough_player(t_game * game);

/*	ipcs.c			*/
bool		init_ipcs(t_game * game);
void		free_ipcs(t_game * game);
void		init_battlefield(t_game * game);
void		set_size(t_game * game);

/*	ipcs_init.c		*/
bool		get_key(key_t * key);
bool		init_shm(t_game * game, key_t key);
bool		init_sem(t_game * game, key_t key);
bool		init_msgq(t_game * game, key_t key);
void		creation(t_game * game);

/*	default_ia.c		*/
void 		default_ia_play(t_game *, ia_settings *);

/*	default_ia_init_free.c	*/
ia_settings *	default_ia_init(t_game *);
void 		default_ia_free(t_game *, ia_settings *);
int		go_left(t_game * game);

/*	ia_loader.c		*/
int		load_ia_library(t_ia * ia, char * name);
void		unload_ia_library(t_ia * ia);

/*	get_symbols.c		*/
bool		get_init(t_ia * ia);
bool		get_play(t_ia * ia);
bool		get_free(t_ia * ia);

/*	args.c			*/
bool		parse_arg(t_opts * opts, int ac, char ** av);
void		init_opts(t_opts * opts);

/*	locking.c		*/
void		lock_battlefield(int semid);
void		unlock_battlefield(int semid);

/*----------------------------ia_utils--------------------------------------------*/

/*	chef.c			*/
void		come_into_me(t_game const * game);

/*	has_order.c		*/
bool		has_order(t_game * game, int * x, int * y);

/*	go_somewhere.c		*/
void		go_somewhere(t_game * game);
int		go_up(t_game * game);
int		go_down(t_game * game);
int		go_right(t_game * game);


/*	go_there.c		*/
void		go_there(t_game * game, int x, int y);

/*	rec_msg.c		*/
char *		rec_msg(int comid, int channel);

/*	go_order.c		*/
bool		go_order(int * x, int * y, char * msg);

#endif		/* LEMIPC_H_ */
