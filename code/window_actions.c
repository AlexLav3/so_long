/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 03:46:29 by elavrich          #+#    #+#             */
/*   Updated: 2024/12/14 23:22:09 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_exit(t_vars *vars, t_animation *animation)
{
	clean(vars, animation);
	clean_vars(vars);
	if (vars->win)
	{
		mlx_destroy_window(vars->mlx, vars->win);
	}
	exit(0);
}
void	events(t_vars *vars, t_animation *animation)
{
	int	x;
	int	y;

	if (vars->is_closed)
		return ;
	x = vars->player_x;
	y = vars->player_y;
	set_frames(animation, vars);
	set_frames_u_d(animation, vars);
	change_sprite(animation, vars);
	collect(vars, x, y);
	win(vars, x, y);
	update_animation(animation, vars, x, y);
}

int	ft_key_press(int keycode, t_vars *vars, t_animation *animation, t_map *map)
{
	int	x;
	int	y;

	x = vars->player_x;
	y = vars->player_y;
	if (keycode == XK_Escape || keycode == 3)
	{
		vars->can_move = 0;
		ft_close(vars, animation);
		return (0);
	}
	else if (vars->can_move == 1)
	{
		move(keycode, vars, animation);
		vars->moves++;
	}
	vars->is_moving = 0;
	ft_printf("key: %d\n", keycode);
	events(vars, animation);
	ft_printf("%d\n", vars->moves);
	return (0);
}
int	ft_close(t_vars *vars, t_animation *animation)
{
	if (!vars->is_closed)
	{
		vars->is_closed = 1;
		ft_exit(vars, animation);
	}
	return (0);
}
int	ft_key_release(int keycode, t_vars *vars, t_animation *animation)
{
	int	x;
	int	y;

	x = vars->player_x;
	y = vars->player_y;
	if (keycode == 97 || keycode == 100 || keycode == 115 || keycode == 119)
		update_animation(animation, vars, x, y);
	return (0);
}
