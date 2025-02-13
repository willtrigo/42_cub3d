/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:46:45 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/13 19:27:05 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "ft_ctype.h"
#include "ft_memlib.h"
#include "ft_stdio.h"
#include <stdlib.h>
#include "color.h"
#include "ft_string.h"
#include "get_next_line.h"
#include "ft_extensions.h"
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int	is_invalid_args(int argc, char **argv)
{
	//TODO: validade argc and filename on arg[0] 
	return (EXIT_SUCCESS);
}

typedef struct s_config_file
{
	// TODO: include textures fields
	t_color	ceil;
	t_color	floor;

	// TODO: ? map
} t_config_file;

int parse_textures(int file_fd, t_config_file *config)
{
	char	*line;

	while (1)
	{
		line = get_next_line(file_fd);
		if (line == 0)
			return (EXIT_FAILURE);
		if (ft_is_blank(line))
		{
			// TODO: ? support multiple blank lines
			free(line);
			break ;
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}

int	parse_color(char *color_line, t_color *color, bool *has_set_color)
{
	char	**split_line;

	*has_set_color = false;
	// andar
	color_line++;
		// assuming line does not contain \n
	while (ft_isspace(*color_line))
		color_line++;
	// split
	split_line = ft_split(color_line, ',');
	if (ft_strarr_len(split_line) != 3)
		return (ft_free_arr_retvalue(split_line, EXIT_FAILURE));
	// parseInt
	color->a = 255;
	if (!ft_atoi8_range(&color->r, split_line[0], 0, 255))
		return (ft_free_arr_retvalue(split_line, EXIT_FAILURE));
	if (!ft_atoi8_range(&color->g, split_line[1], 0, 255))
		return (ft_free_arr_retvalue(split_line, EXIT_FAILURE));
	if (!ft_atoi8_range(&color->b, split_line[2], 0, 255))
		return (ft_free_arr_retvalue(split_line, EXIT_FAILURE));
	// set color && has_set_color
	*has_set_color = true;
	return (ft_free_arr_retvalue(split_line, EXIT_SUCCESS));
}

int parse_colors(int file_fd, t_config_file *config)
{
	char	*line;
	bool	has_set_color[2];

	has_set_color[0] = false;
	has_set_color[1] = false;
	while (!has_set_color[0] || !has_set_color[1])
	{
		line = ft_chomp(get_next_line(file_fd));
		if (line == 0)
			return (EXIT_FAILURE);
		if (ft_is_blank(line))
		{
			free(line);
			break ;
		}
		if (*line == 'F' && parse_color(line, &config->floor, has_set_color))
			return (EXIT_FAILURE);
		else if (*line == 'C' && parse_color(line, &config->ceil, has_set_color + 1))
			return (EXIT_FAILURE);
		free(line);
	}
	if (!has_set_color[0] || !has_set_color[1])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_file(char *filename, t_config_file *config)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0666);
	if (fd < 0)
		return (EXIT_FAILURE);
	if (parse_textures(fd, config) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_colors(fd, config) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// TODO: parse_map;
	return (EXIT_SUCCESS);
}

void	config_clean(t_config_file *config)
{
	
	// TODO: clean texture filenames

}

int	config_init(int argc, char **argv, t_config_file *config)
{
	
	if (is_invalid_args(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_file(*argv, config) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	set_pixel(int x, int y, mlx_image_t *img, t_color *color)
{
	mlx_put_pixel(img, x, y, color->value);
}

int	cube_main(int argc, char **argv)
{
	mlx_t			*mlx;
	mlx_image_t		*bg;
	t_config_file 	config;
	int				window_height;
	int				x;
	int				y;

	window_height = 995;
	y = -1;
	if (config_init(--argc, ++argv, &config) == EXIT_FAILURE)
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
