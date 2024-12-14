/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:38:33 by elavrich          #+#    #+#             */
/*   Updated: 2024/12/14 23:15:32 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_map		*map;
	t_animation	 animation;

	map = malloc(sizeof(t_map));
	if (!map)
		return (free(map), 0);
	if (argc == 2)
	{
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, WINDOW_W, WINDOW_H, "so_long");
		vars.is_closed = 0;
		if (init_game(&vars, &animation, map, argv))
		{
			mlx_hook(vars.win, 2, 1L << 0, ft_key_press, (void *)&vars);
			mlx_hook(vars.win, 3, 1L << 1, ft_key_release, (void *)&vars);
			mlx_loop(vars.mlx);
		}
	}
	return (0);
}
