/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 03:46:29 by elavrich          #+#    #+#             */
/*   Updated: 2024/12/16 22:40:47 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_exit(t_vars *vars, t_animation *animation)
{
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
	change_sprite(animation, vars);
	collect(vars, x, y);
	win(vars, vars->player_x, vars->player_y);
	update_animation(animation, vars, x, y);
}

int	ft_key_press(int keycode, void *v)
{
	int		x;
	int		y;
	t_vars	*vars;

	vars = v;
	x = vars->player_x;
	y = vars->player_y;
	if (keycode == XK_Escape || keycode == 3)
	{
		vars->can_move = 0;
		ft_close(vars, vars->animation);
		return (0);
	}
	else if (vars->can_move == 1)
	{
		move(keycode, vars, vars->animation);
		vars->moves++;
	}
	vars->is_moving = 0;
	events(vars, vars->animation);
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

int	ft_key_release(int keycode, void *v)
{
	int		x;
	int		y;
	t_vars	*vars;

	vars = v;
	x = vars->player_x;
	y = vars->player_y;
	if (keycode == 97 || keycode == 100 || keycode == 115 || keycode == 119)
		update_animation(vars->animation, vars, x, y);
	return (0);
}
