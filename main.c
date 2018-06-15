/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 13:44:37 by jfleisch          #+#    #+#             */
/*   Updated: 2018/06/06 13:44:38 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>

void 			img_clear(t_mlx *mlx)
{
	if (mlx->mode == 1)
		ft_bzero(mlx->img.data, sizeof(int) * mlx->img.width * mlx->img.height);
	else
		mlx_clear_window(mlx->mlx, mlx->win);
}

void 		draw_cube(t_mlx *mlx)
{
	t_file		file;

	file = *(t_file*)ft_memalloc(sizeof(file));
	read_file(mlx, &file);
	mlx->map.scale = 10;
	set_cord(mlx, &file);
	draw_c(mlx);
	mlx->map.move_x = 80;
	mlx->map.move_y = 40;
	connect_points(mlx);
	draw_c(mlx);
	// mlx->map.center_x = (WIN_WIDTH - (mlx->map.cols * mlx->map.scale)) / 2;
	// mlx->map.center_y = (WIN_HEIGHT - (mlx->map.rows * mlx->map.scale)) / 2;
}

void 		connect_points(t_mlx *mlx)
{
	t_vector	*points;
	// t_vector	pre;
	t_iterator	i;
	// int			ii;
	int		*color;

	color = (int*)ft_memalloc(sizeof(*color) * 6);
	points = mlx->map.vectors;
	i.x = mlx->map.rows;
	i.y = mlx->map.cols;
	i.i = -1;
	color[0] = RED;
	color[1] = GREEN;
	color[2] = BLUE;
	color[3] = PURPLE;
	color[4] = AMETHYST;
	color[5] = G_APPLE;
	color[6] = B_ORCHID;
	while (++i.i <= (i.y * i.y) + (mlx->map.move_y * 3))
	{
		i.z = -1;
		while (++i.z <= (i.x * i.x) + (mlx->map.move_x * 3))
		{
			if (i.z == 0 || i.z == (i.x * i.x) + mlx->map.move_x)
				mlx->map.vectors->color = color[5];
			else
				mlx->map.vectors->color = RED;
			blg(points[i.z].x, points[i.i].y, points[i.z].x + mlx->map.move_x,
				points[i.i].y + mlx->map.move_y, mlx);
		}
	}
}

void 		draw_c(t_mlx *mlx)
{
	int		r;
	int		c;
	int		i;
	t_vector	*points;
	int		ii;
	int		iii;
	int		*color;

	points = mlx->map.vectors;
	r = mlx->map.rows;
	c = mlx->map.cols;
	color = (int*)ft_memalloc(sizeof(*color) * 9);
	color[0] = RED;
	color[1] = GREEN;
	color[2] = BLUE;
	color[3] = PURPLE;
	color[4] = AMETHYST;
	color[5] = G_APPLE;
	color[6] = B_ORCHID;
	iii = 0;
	while (iii < WIN_HEIGHT)
	{
		ii = -1;
		while (++ii < r)
		{
			i = -1;
			while (++i < r)
			{
				if ((i == 0) || (i == r - 1))
					mlx->map.vectors->color = color[2];
				else
					mlx->map.vectors->color = RED;
				vlg(points[ii].x  + mlx->map.move_x,
					points[i + iii].y + mlx->map.move_y,
					points[i + 1 + iii].y + mlx->map.move_y, mlx);
			}
		}
		ii = 0;
		while (ii < c)
		{
			i = -1;
			while (++i < r)
			{
				if (i == 0 || i == r - 1)
					mlx->map.vectors->color = color[3];
				else
					mlx->map.vectors->color = RED;
				hlg(points[i].x  + mlx->map.move_x,
					points[i + 1].x + mlx->map.move_x,
					points[ii + iii].y + mlx->map.move_y, mlx);
			}
			ii += r;
		}
		iii += r;
	}
}

void		set_cord(t_mlx *mlx, t_file *file)
{
	t_vector *points;
	int		r;
	int		c;
	int		i;
	char	**matrix;
	char	*dd;

	points = (t_vector*)ft_memalloc(sizeof(*points) * 777);
	matrix = file->split_y;
	c = -1;
	i = -1;
	while (++c < mlx->map.cols)
	{
		r = -1;
		while (++r < mlx->map.rows)
		{
			points[++i].x = r * mlx->map.scale;
			points[i].y = c * mlx->map.scale;
			if ((matrix[c][r] > '0' && matrix[c][r] <= '9')
				&& (matrix[c][r + 1] >= '0' && matrix[c][r + 1] <= '9'))
			{
					dd = &matrix[c][r];
					ft_strjoin(dd, &matrix[c][r - 1]);
					points[i].z = ft_atoi(dd);
			}
			printf("points[%d] = (%d, %d, %d)\n\n", i, points[i].x, points[i].y, points[i].z);
		}
	}
	mlx->map.vectors = points;
	printf("dim = (%d, %d)\n", mlx->map.rows, mlx->map.cols);
}

int			key_pressed(int keycode, t_mlx *mlx)
{
	ft_putstr("key code: ");
	ft_putendl(ft_itoa(keycode));
	if (keycode == 53)
		exit(0);
	// else if (keycode == 34)
	// 	put_img_square(mlx);
	// else if (keycode == 35)
	// 	put_img_square(mlx);
	else if (keycode == 49)
		mlx_clear_window(mlx->mlx, mlx->win);
	else if (keycode == 13)
		mlx_string_put(mlx->mlx, mlx->win, 7, 7, DGREY, "Click to display image");
	else if (keycode == 12)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 400, 400);
	else
		ft_putendl("press 'space' to clear screen 'w' to show string or 'esc' to exit");
	return (0);
}

int			mouse_clicked(int button, int x, int y, t_mlx *mlx)
{
	ft_putstr("button: ");
	ft_putstr(ft_itoa(button));
	ft_putstr("	x cord: ");
	ft_putstr(ft_itoa(x));
	ft_putstr("	y cord: ");
	ft_putendl(ft_itoa(y));
	if ((x >= 0 && x <= 50) && (y >= 0 && y <= 50))
		mlx_clear_window(mlx->mlx, mlx->win);
	draw_cube(mlx);
	return (0);
}

void		read_file(t_mlx *mlx, t_file *file)
{
	int		i;

	check_err((file->fd = open(mlx->file, O_RDONLY)), "Failed to open file");
	file->cont = (char*)ft_memalloc(sizeof(*file->cont));
	while ((file->ret = read(file->fd, &file->buf, BUF_SIZE)))
	{
		file->buf[file->ret] = '\0';
		file->tmp = file->cont;
		file->cont = ft_strjoin(file->tmp, file->buf);
		free(file->tmp);
	}
	file->split_y = ft_strsplit(file->cont, '\n');
	file->split_x = ft_strsplit(file->split_y[0], ' ');
	i = -1;
	while (file->split_x[++i])
		free(file->split_x[i]);
	mlx->map.rows = i;
	i = 0;
	while (file->split_y[i])
		i++;
	mlx->map.cols = i;
	free(file->cont);
	free(file->split_x);
}

void		usage(void)
{
	ft_putendl("usage: ./fdf <MAP_FILE>");
	exit(1);
}

int			main(int ac, char **av)
{
	t_mlx	mlx;


	if (ac != 2)
		usage();
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
	mlx.file = av[1];
	mlx.img.width = WIN_WIDTH - OFF_X;
	mlx.img.height = WIN_HEIGHT - OFF_Y;
	mlx.img.img = mlx_new_image(mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx.img.data = (int*)mlx_get_data_addr(mlx.img.img, &mlx.img.bpp, &mlx.img.line_size, &mlx.img.endian);
	mlx.shift = 0;
	mlx.mode = 1;
	mlx.color_on = -1;
	// set_up(&mlx);
	mlx_string_put(mlx.mlx, mlx.win, 7, 7, DGREY, "Click to display image");
	mlx_key_hook(mlx.win, key_pressed, &mlx);
	mlx_mouse_hook(mlx.win, mouse_clicked, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
