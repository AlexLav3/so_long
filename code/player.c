/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 03:36:31 by elavrich          #+#    #+#             */
/*   Updated: 2024/12/30 00:02:57 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move(int keycode, t_vars *vars, t_animation *animation)
{
	if (keycode == 119 && is_walkable(vars, vars->player_x,
			vars->player_y - 1))
	{
		vars->player_y--;
		animation->direction = 2;
		vars->moves++;
		ft_printf("%d\n", vars->moves);
	}
	else if (keycode == 97 && is_walkable(vars, vars->player_x - 1,
			vars->player_y))
	{
		vars->player_x--;
		animation->direction = -1;
		vars->moves++;
		ft_printf("%d\n", vars->moves);
	}
	move_sec(keycode, vars, animation);
}

void	set_frames_u_d(t_animation *animation, t_vars *vars)
{
	int	img_width;
	int	img_height;

	animation->img[6] = mlx_xpm_file_to_image(vars->mlx,
			"player/idle_up.xpm", &img_width, &img_height);
	animation->img[7] = mlx_xpm_file_to_image(vars->mlx,
			"player/walk_up1.xpm", &img_width, &img_height);
	animation->img[8] = mlx_xpm_file_to_image(vars->mlx,
			"player/walk_up2.xpm", &img_width, &img_height);
	animation->img[9] = mlx_xpm_file_to_image(vars->mlx,
			"player/idle_down.xpm", &img_width, &img_height);
	animation->img[10] = mlx_xpm_file_to_image(vars->mlx,
			"player/walk_down1.xpm", &img_width, &img_height);
	animation->img[11] = mlx_xpm_file_to_image(vars->mlx,
			"player/walk_down2.xpm", &img_width, &img_height);
}

void	set_frames(t_animation *animation, t_vars *vars)
{
	int	img_width;
	int	img_height;

	animation->img[0] = mlx_xpm_file_to_image(vars->mlx,
			"player/idle_right.xpm", &img_width, &img_height);
	animation->img[1] = mlx_xpm_file_to_image(vars->mlx,
			"player/walk_right1.xpm", &img_width, &img_height);
	animation->img[2] = mlx_xpm_file_to_image(vars->mlx,
			"player/walk_right2.xpm", &img_width, &img_height);
	animation->img[3] = mlx_xpm_file_to_image(vars->mlx,
			"player/idle_left.xpm", &img_width, &img_height);
	animation->img[4] = mlx_xpm_file_to_image(vars->mlx,
			"player/walk_left1.xpm", &img_width, &img_height);
	animation->img[5] = mlx_xpm_file_to_image(vars->mlx,
			"player/walk_left2.xpm", &img_width, &img_height);
}

void	change_sprite(t_animation *animation, t_vars *vars)
{
	if (animation->direction == -1)
		animation->current_frame = 3;
	else if (animation->direction == 1)
		animation->current_frame = 0;
	else if (animation->direction == 2)
		animation->current_frame = 6;
	else if (animation->direction == 3)
		animation->current_frame = 9;
}

void	load_frame(t_animation *animation, t_vars *vars, int map_x,
		int map_y)
{
	int	a;

	a = TILE_SIZE;
	if (!map_x || !map_y)
		return ;
	if (vars->is_closed || !animation)
		return ;
	animation->current_frame = (animation->current_frame + 1) % 12;
	mlx_put_image_to_window(vars->mlx, vars->win,
		animation->img[animation->current_frame], map_x * a, map_y * a);
}
