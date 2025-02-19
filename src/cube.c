/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:46:45 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/19 17:17:54 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include "infrastructure/config/config.h"
#include "utils/color.h"
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ft_stdio.h"

void	set_pixel(int x, int y, mlx_image_t *img, t_color *color)
{
	mlx_put_pixel(img, x, y, color->value);
}

int	cube_main(int argc, char **argv)
{
	// TODO: criar estrutura game, e mover o que precisar dentro dela.
	mlx_t			*mlx;
	mlx_image_t		*bg;
	int				window_height;
	int				x;
	int				y;
	// TODO: criar contexto para as images

	// TODO: config/parse inicializar o game passando t_config_file
	t_config_file 	config;

	window_height = 995;
	y = -1;
	if (!config_init(--argc, ++argv, &config))
		return(EXIT_FAILURE);

	mlx = mlx_init(1920, window_height, "cub3d", false);
	bg = mlx_new_image(mlx, 1920, window_height);
	while (++y < window_height / 2)
	{
		x = -1;
		while (++x < 1920)
			set_pixel(x, y, bg, &config.ceil);
	}
	y--;
	while (++y < window_height)
	{
		x = -1;
		while (++x < 1920)
			set_pixel(x, y, bg, &config.floor);
	}
	mlx_image_to_window(mlx, bg, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);

	ft_printf("cub3d ceil color: R:%d G:%d B:%d A:%d\n", config.ceil.r, config.ceil.g, config.ceil.b, config.ceil.a);
	ft_printf("cub3d floor color: R:%d G:%d B:%d A:%d\n", config.floor.r, config.floor.g, config.floor.b, config.floor.a);
	config_clean(&config);
	return (EXIT_SUCCESS);
}
