/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:38:33 by elavrich          #+#    #+#             */
/*   Updated: 2024/12/30 00:04:47 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_sec(int keycode, t_vars *vars, t_animation *animation)
{
	if (keycode == 115 && is_walkable(vars, vars->player_x, vars->player_y
			+ 1))
	{
		vars->player_y++;
		animation->direction = 3;
		vars->moves++;
		ft_printf("%d\n", vars->moves);
	}
	else if (keycode == 100 && is_walkable(vars, vars->player_x + 1,
			vars->player_y))
	{
		vars->player_x++;
		animation->direction = 1;
		vars->moves++;
		ft_printf("%d\n", vars->moves);
	}
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_map		*map;
	t_animation	animation;

	map = malloc(sizeof(t_map));
	if (!map)
		return (0);
	if (argc == 2)
	{
		vars.mlx = mlx_init();
		vars.is_closed = 0;
		if (init_game(&vars, &animation, map, argv))
		{
			vars.animation = &animation;
			mlx_hook(vars.win, 2, 1L << 0, ft_key_press, (void *)&vars);
			mlx_hook(vars.win, 3, 1L << 1, ft_key_release, (void *)&vars);
			mlx_loop(vars.mlx);
		}
	}
	return (0);
}
