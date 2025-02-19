/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_suite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:24:50 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/19 19:51:30 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/config/config.h"
#include "utils/color.h"
#include "infrastructure/config/parse/parse_internal.h"
#include "infrastructure/config/config_internal.h"
#include "ft_assert.h"
#include "ft_stdio.h"
#include "test_suite.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>



int	main(void)
{
	test_color();
	test_parse_color();
	test_is_valid_args();
	test_config_init();
	ft_printf("\n");
	return (0);
}
