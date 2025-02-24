/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:39:41 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/24 15:17:11 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/color.h"
#include "ft_stdio.h"
#include "test_suite.h"

void test_color(void)
{
	ft_printf("\n%s :START\n", __FUNCTION__);
	t_color color;

	color = ft_color(0, 0, 0, 0);
	FT_TEST(color.value == 0, "ft_color(0, 0, 0, 0) should have color.value == 0");

	color = ft_color(0xFF, 0, 0, 0);
	FT_TEST(color.value == 0xFF000000,
			"ft_color(0xFF, 0, 0, 0) should have color.value == 0xFF000000");

	color = ft_color(0, 0xA1, 0, 0);
	FT_TEST(color.value == 0x00A10000,
			"ft_color(0, 0xA1, 0, 0) should have color.value == 0x00A10000");

	color = ft_color(0, 0x0, 0x77, 0);
	FT_TEST(color.value == 0x00007700,
			"ft_color(0, 0, 0x77, 0) should have color.value == 0x00007700");

	color = ft_color(0, 0, 0, 0x13);
	FT_TEST(color.value == 0x000000013,
			"ft_color(0, 0, 0, 0x13) should have color.value == 0x00000013");

	color = ft_color(0xFE, 0xDC, 0xBA, 0x98);
	FT_TEST(color.value == 0xFEDCBA98,
			"ft_color(0xFE, 0xDC, 0xBA, 0x98) should have color.value == 0xFEDCBA98");
	ft_printf("%s: END\n", __FUNCTION__);
}
