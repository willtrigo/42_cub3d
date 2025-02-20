/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_suite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:24:50 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/20 12:40:55 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_stdio.h"
#include "test_suite.h"

int	main(void)
{
	test_color();
	test_parse_color();
	test_is_valid_args();
	test_config_init();
	ft_printf("\n");
	return (0);
}
