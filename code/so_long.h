/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:31:02 by elavrich          #+#    #+#             */
/*   Updated: 2024/12/16 22:13:43 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/get_next_line/get_next_line.h"
# include "libft/printf/ft_printf.h"
# include "libft/src/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_W 690
# define WINDOW_H 390
# define TILE_SIZE 30
# define MAX_FRAMES 12
# define ANIMATION_DELAY 12

typedef struct s_map
{
	char		*image_file;
	char		*file;
	char		*line;
	char		*floor;
	char		*wall1;
	char		*exit;
	char		*col;
	int			y;
	int			x;
	char		**copy;
	int			walkable;
}				t_map;

typedef struct s_coll
{
	char		*image_file;
	char		*file;
	int			y;
	int			x;
}				t_coll;
typedef struct s_animation
{
	void		**frames;
	int			frame_count;
	char		*img[MAX_FRAMES];
	int			current_frame;
	int			direction;
	int			delay_counter;
}				t_animation;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	char		*addr;
	t_map		*map;
	t_animation	*animation;
	t_coll		*collect;
	int			player_x;
	int			can_move;
	int			player_y;
	int			is_closed;
	int			is_moving;
	int			moves;
}				t_vars;


void			change_sprite(t_animation *animation, t_vars *vars);
void			clean_collect(t_coll *collect);
void			clean_map(t_map *map);
void			clean_vars(t_vars *vars);
void			clean(t_vars *vars, t_animation *animation);

int				check_map(t_vars *vars);
int				is_exit(t_vars *vars);

int				init_game(t_vars *vars, t_animation *animation, t_map *map,
					char **argv);

void			move(int keycode, t_vars *vars, t_animation *animation);
void			events(t_vars *vars, t_animation *animation);
void			win(t_vars *vars, int x, int y);

int				win_cond(t_vars *vars, int x, int y);
void			init_collect(t_vars *vars);
int				is_coll(t_vars *vars, int x, int y);
void			collect(t_vars *vars, int x, int y);
int				count_coll(t_vars *vars);
void			set_frames_u_d(t_animation *animation, t_vars *vars);
int				is_walkable(t_vars *vars, int x, int y);

int				get_map_dimensions(t_vars *vars, int *rows, int *columns);
void			inizialize_map(t_map *map);
void			map_y_x(t_vars *vars);
void			set_map(t_vars *vars);
void			load_map(t_vars *vars);
void			find_pos(t_vars *vars, t_animation *animation);
int				ft_key_release(int keycode, void *v);

void			player_first_pos(t_animation *animation, t_vars *vars,
					int map_x, int map_y);
void			set_frames(t_animation *animation, t_vars *vars);
void			choose_image(char *image_name, t_vars *vars);
int				update_animation(t_animation *animation, t_vars *vars, int x,
					int y);

void			ft_exit(t_vars *vars, t_animation *animation);
int				ft_key_press(int keycode, void *v);
int				ft_close(t_vars *vars, t_animation *animation);

#endif
