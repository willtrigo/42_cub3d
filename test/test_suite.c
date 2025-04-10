/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_suite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:24:50 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/09 22:53:28 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_stdio.h"
#include "test_suite.h"

void test_map() {
	//TODO: add tests for valid maps
	// test/maps/diamond.cub
	// test/maps/diamond_leftpad.cub
	// test/maps/diamond_trailing_spaces.cub
	return ;
}

int	main(void)
{
	test_color();
	test_parse_color();
	test_is_valid_args();
	test_config_init();
	ft_printf("\n");
	return (0);
}
