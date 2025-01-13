/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 03:46:29 by elavrich          #+#    #+#             */
/*   Updated: 2025/01/13 21:40:44 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_exit(t_vars *vars)
{
	if (vars->win && vars->mlx)
	{
		mlx_destroy_window(vars->mlx, vars->win);
	}
	exit(0);
}

void	events(t_vars *vars, t_animation *animation)
{
	if (vars->is_closed)
		return ;
	change_sprite(animation);
	collect(vars, vars->player_x, vars->player_y);
	win(vars, vars->player_x, vars->player_y);
	update_animation(animation, vars, vars->player_x, vars->player_y);
}

int	ft_key_press(int keycode, void *v)
{
	t_vars	*vars;

	vars = v;
	if (keycode == XK_Escape || keycode == 3)
	{
		vars->can_move = 0;
		ft_close(vars);
		return (0);
	}
	else if (vars->can_move == 1)
		move(keycode, vars, vars->animation);
	vars->is_moving = 0;
	events(vars, vars->animation);
	return (0);
}

int	ft_close(t_vars *vars)
{
	if (!vars->is_closed)
	{
		vars->is_closed = 1;
		ft_exit(vars);
	}
	return (0);
}

int	ft_key_release(int keycode, void *v)
{
	t_vars	*vars;

	vars = v;
	if (keycode == 97 || keycode == 100 || keycode == 115 || keycode == 119)
		update_animation(vars->animation, vars, vars->player_x, vars->player_y);
	return (0);
}
