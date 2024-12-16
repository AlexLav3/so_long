/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 03:36:31 by elavrich          #+#    #+#             */
/*   Updated: 2024/12/16 22:47:08 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move(int keycode, t_vars *vars, t_animation *animation)
{
	if (keycode == 119 && is_walkable(vars, vars->player_x, vars->player_y - 1))
	{
		vars->player_y--;
		animation->direction = 2;
	}
	else if (keycode == 97 && is_walkable(vars, vars->player_x - 1,
			vars->player_y))
	{
		vars->player_x--;
		animation->direction = -1;
	}
	else if (keycode == 115 && is_walkable(vars, vars->player_x, vars->player_y
			+ 1))
	{
		vars->player_y++;
		animation->direction = 3;
	}
	else if (keycode == 100 && is_walkable(vars, vars->player_x + 1,
			vars->player_y))
	{
		vars->player_x++;
		animation->direction = 1;
	}
}

void	set_frames_u_d(t_animation *animation, t_vars *vars)
{
	int	img_width;
	int	img_height;

	animation->img[6] = mlx_xpm_file_to_image(vars->mlx, "player/idle_up.xpm",
			&img_width, &img_height);
	animation->img[7] = mlx_xpm_file_to_image(vars->mlx, "player/walk_up1.xpm",
			&img_width, &img_height);
	animation->img[8] = mlx_xpm_file_to_image(vars->mlx, "player/walk_up2.xpm",
			&img_width, &img_height);
	animation->img[9] = mlx_xpm_file_to_image(vars->mlx, "player/idle_down.xpm",
			&img_width, &img_height);
	animation->img[10] = mlx_xpm_file_to_image(vars->mlx, "player/walk_down1.xpm", 
			&img_width, &img_height);
	animation->img[11] = mlx_xpm_file_to_image(vars->mlx, "player/walk_down2.xpm", 
			&img_width, &img_height);
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
	int	img_width;
	int	img_height;

	if (animation->direction == -1)
		animation->current_frame = 3;
	else if (animation->direction == 1)
		animation->current_frame = 0;
	else if (animation->direction == 2)
		animation->current_frame = 6;
	else if (animation->direction == 3)
		animation->current_frame = 9;
}

void	player_first_pos(t_animation *animation, t_vars *vars, int map_x,
		int map_y)
{
	int	screen_x;
	int	screen_y;

	if (!map_x || !map_y)
		return ;
	screen_x = map_x * TILE_SIZE;
	screen_y = map_y * TILE_SIZE;
	if (vars->is_closed || !animation)
		return ;
	animation->current_frame = (animation->current_frame + 1) % 12;
	mlx_put_image_to_window(vars->mlx, vars->win,
		animation->img[animation->current_frame], screen_x, screen_y);
}

int	update_animation(t_animation *animation, t_vars *vars, int x, int y)
{
	int	screen_x;
	int	screen_y;

	screen_x = x * TILE_SIZE;
	screen_y = y * TILE_SIZE;
	if (vars->is_closed || !animation)
		return (0);
	if (vars->is_moving)
	{
		animation->frame_count++;
		if (animation->frame_count >= ANIMATION_DELAY)
			animation->frame_count = 0;
	}
	load_map(vars);
	player_first_pos(animation, vars, x, y);
	return (0);
}
