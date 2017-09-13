##
## Makefile for Makefile in /home/ngonta_e//my_home/rendu/c/lemipc
## 
## Made by eugene-valentin ngontang-tchiadjie
## Login   <ngonta_e@epitech.net>
## 
## Started on  Wed May 18 19:06:44 2011 eugene-valentin ngontang-tchiadjie
## Last update Sun May 22 22:26:50 2011 adrien barrau
## Last update Sun May 22 18:17:41 2011 adrien barrau
##


LEMIPC		=	lemipc

GUI		=	viewer

CORE_DIR	=	core

SOLDIER		=	lib_soldier_player.so

CHEF		=	lib_chef_player.so

SCOUT		=	lib_scout_player.so

JAMMER		=	lib_jammer_player.so

CORE_SRC	=	$(CORE_DIR)/main.c			\
			$(CORE_DIR)/ia_loader.c			\
			$(CORE_DIR)/get_symbols.c		\
			$(CORE_DIR)/default_ia.c 		\
			$(CORE_DIR)/default_ia_init_free.c	\
			$(CORE_DIR)/game.c	 		\
			$(CORE_DIR)/game_end.c	 		\
			$(CORE_DIR)/args.c	 		\
			$(CORE_DIR)/locking.c	 		\
			$(CORE_DIR)/ipcs_init.c			\
			$(CORE_DIR)/ipcs.c

GUI_DIR		=	gui

LIB_DIR		=	libia

SOLDIER_DIR	=	soldier

CHEF_DIR	=	chef

SCOUT_DIR	=	scout

JAMMER_DIR	=	jammer

SOLDIER_SRC	=	$(LIB_DIR)/$(SOLDIER_DIR)/soldier_player.c	\
			$(LIB_DIR)/$(SOLDIER_DIR)/go_left.c		\
			$(LIB_DIR)/$(SOLDIER_DIR)/go_somewhere.c	\
			$(LIB_DIR)/$(SOLDIER_DIR)/go_there.c		\
			$(LIB_DIR)/$(SOLDIER_DIR)/has_order.c		\
			$(LIB_DIR)/$(SOLDIER_DIR)/locking.c		\
			$(LIB_DIR)/$(SOLDIER_DIR)/rec_msg.c

CHEF_SRC	=	$(LIB_DIR)/$(CHEF_DIR)/chef_player.c		\
			$(LIB_DIR)/$(CHEF_DIR)/come_into_me.c		\
			$(LIB_DIR)/$(CHEF_DIR)/go_left.c		\
			$(LIB_DIR)/$(CHEF_DIR)/go_order.c		\
			$(LIB_DIR)/$(CHEF_DIR)/locking.c		\
			$(LIB_DIR)/$(CHEF_DIR)/go_somewhere.c		\
			$(LIB_DIR)/$(CHEF_DIR)/go_there.c

SCOUT_SRC	=	$(LIB_DIR)/$(SCOUT_DIR)/scout_player.c		\
			$(LIB_DIR)/$(SCOUT_DIR)/go_somewhere.c		\
			$(LIB_DIR)/$(SCOUT_DIR)/locking.c		\
			$(LIB_DIR)/$(SCOUT_DIR)/go_left.c

JAMMER_SRC	=	$(LIB_DIR)/$(JAMMER_DIR)/jammer_player.c	\
			$(LIB_DIR)/$(JAMMER_DIR)/go_somewhere.c		\
			$(LIB_DIR)/$(JAMMER_DIR)/locking.c		\
			$(LIB_DIR)/$(JAMMER_DIR)/go_left.c

GUI_SRC		=	$(GUI_DIR)/main.c		\
			$(GUI_DIR)/display.c		\
			$(GUI_DIR)/free_ipcs.c		\
			$(GUI_DIR)/init_sdl_ipcs.c	\
			$(GUI_DIR)/load_img.c		\
			$(GUI_DIR)/locking.c		\
			$(GUI_DIR)/input.c		\
			$(GUI_DIR)/view.c

CORE_OBJ	=	$(CORE_SRC:.c=.o)

GUI_OBJ		=	$(GUI_SRC:.c=.o)

SOLDIER_OBJ	=	$(SOLDIER_SRC:.c=.o)

CHEF_OBJ	=	$(CHEF_SRC:.c=.o)

SCOUT_OBJ	=	$(SCOUT_SRC:.c=.o)

JAMMER_OBJ	=	$(JAMMER_SRC:.c=.o)

INC_PATH	=	includes

RM		=	rm -f

CC		=	gcc

CFLAGS		+=	-W -Wall -Werror -Wextra  -fPIC -I$(INC_PATH)

LDFLAGS		+=	

all		:	$(LEMIPC) $(GUI) $(SOLDIER) $(CHEF) $(SCOUT) $(JAMMER)

$(LEMIPC)	:	$(CORE_OBJ)
			$(CC) $(LDFLAGS) -ldl -o $(LEMIPC) $(CORE_OBJ)

$(GUI)		:	$(GUI_OBJ)
			$(CC) $(LDFLAGS) -lSDL -lSDL_image -lSDL_gfx -o $(GUI) $(GUI_OBJ)

$(SOLDIER)	:	$(SOLDIER_OBJ)
			$(CC) $(LDFLAGS) -shared -o $(SOLDIER) $(SOLDIER_OBJ)

$(CHEF)		:	$(CHEF_OBJ)
			$(CC) $(LDFLAGS) -shared -o $(CHEF) $(CHEF_OBJ)

$(SCOUT)	:	$(SCOUT_OBJ)
			$(CC) $(LDFLAGS) -shared -o $(SCOUT) $(SCOUT_OBJ)

$(JAMMER)	:	$(JAMMER_OBJ)
			$(CC) $(LDFLAGS) -shared -o $(JAMMER) $(JAMMER_OBJ)

clean		:
			$(RM) $(CORE_OBJ) $(GUI_OBJ) $(SOLDIER_OBJ) $(CHEF_OBJ) $(SCOUT_OBJ) $(JAMMER_OBJ)

fclean		:	clean
			$(RM) $(LEMIPC) $(GUI) $(SOLDIER) $(CHEF) $(SCOUT) $(JAMMER)

re		:	fclean all

.PHONY		:	all clean fclean re