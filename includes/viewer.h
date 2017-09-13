/*
** viewer.h for <Viewer> in /home/barrau_a//c/lemipc_soldier
** 
** Made by adrien barrau
** Login   <barrau_a@epitech.net>
** 
** Started on  Sat May 21 14:37:14 2011 adrien barrau
** Last update Sun May 22 18:17:18 2011 adrien barrau
*/

#ifndef VIEWER_H_
# define VIEWER_H_

#include <SDL/SDL.h>

# define	VIEW_TITLE			("Lemipc Soldier Viewer")
# define	VIEW_W				(800)
# define	VIEW_H				(800)
# define	VIEW_BPP			(32)

# define	PATH_MAX			(1024)
# define	KEY_DISTURBED			(0xdeadbeef)
# define	NUMBER_OF_SEM			(1)

# define	WAIT				(10)
# define	ERROR				(11)
# define	OKAY				(12)

# define	XO				(100)
# define	YO				(100)

# define	GRID_W				(600)
# define	GRID_H				(600)
# define	GRID_COLOR			(0xFFFFFFFF)

# define	RECT_OUT_COLOR			(0xFFCC00FF)
# define	RECT_IN_COLOR			(0xFFAA00FF)

# define	WAIT_IMG_PATH			("gui/img/wait.png")
# define	BACKGROUND_IMG_PATH		("gui/img/background.jpg")

# define	NO_ERROR			(0)
# define	SDL_INIT_ERR_CODE		(-1)
# define	VIDEOMODE_ERR_CODE		(-2)
# define	LOAD_ERR_CODE			(-3)
# define	BATTLEFIELD_KEY_ERR_CODE	(-4)
# define	BATTLEFIELD_SEM_ERR_CODE	(-5)

# define	SDL_INIT_ERR_MSG		("Cannot init sdl")
# define	VIDEOMODE_ERR_MSG		("Cannot retrieve the window")
# define	BATTLEFIELD_DTSHM_ERR_MSG	("Cannot detach shm")
# define	LOAD_ERR_MSG			("Cannot load image")
# define	BATTLEFIELD_KEY_ERR_MSG		("Cannot init keys")
# define	BATTLEFIELD_SEM_ERR_MSG		("Cannot init semaphore")

# define	false				(0)
# define	true				(!false)
typedef		int				bool;

typedef		char	battlefield;

typedef struct
{
  SDL_Surface *	screen;
  SDL_Surface * wait_img;
  SDL_Surface * background_img;
  battlefield *	battlefield;
  int		width;
  int		height;
  int		shmid;
  int		semid;
}	t_view;

/*	init_sdl_ipcs.c		*/
int		join_battlefield(t_view * view);

/*	load_img.c		*/
int		init_window(t_view * view);
SDL_Surface *	load_image(const char * filename);

/*	view.c			*/
void		view_battlefield(t_view * view);

/*	display.c		*/
void		display_wait(t_view * view);
void		display_background(t_view * view);
void		display_rect(t_view * view);

/*	free_ipcs.c		*/
void		free_ipcs(t_view * view);

/*	locking.c		*/
void		lock_battlefield(int semid);
void		unlock_battlefield(int semid);

/*	input.c			*/
bool		getInput();

#endif /* !VIEWER_H_ */
