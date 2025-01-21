/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:06:57 by dande-je          #+#    #+#             */
/*   Updated: 2025/01/21 20:34:08 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MLX42/MLX42.h"
#include "ft_stdio.h"

int	main(int argc, char **argv)
{
	mlx_t	*mlx;

	mlx = mlx_init(1920, 995, "cub3d", false);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	ft_printf("cub3d");
	exit(EXIT_SUCCESS);
}
