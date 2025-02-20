/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:43:11 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/19 19:46:07 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/config/parse/parse_internal.h"
#include "utils/color.h"
#include "test_suite.h"
#include <stdbool.h>

void	test_parse_color(void)
{
	ft_printf("\n%s :START\n", __FUNCTION__);

	t_color	color;
	bool	has_set_color;
	int		result;

	has_set_color = false;
	result = parse_color("F 220,100,0", &color, &has_set_color);
	FT_TEST(result == true,
		 "when parse color F 220,100,0 expect return == true");
	FT_TEST(color.value == 0xdc6400FF,
		 "when parse color F 220,100,0 expect color.value == xdc6400FF");
	FT_TEST(has_set_color == true,
		 "when parse color F 220,100,0 expect has_set_color == true");

	has_set_color = false;
	result = parse_color("C 225,30,0", &color, &has_set_color);
	FT_TEST(result == true,
		 "when parse color C 225,30,0 expect return == true");
	FT_TEST(color.value == 0xe11e00FF,
		 "when parse color C 225,30,0 expect color.value == xdc6400FF");
	FT_TEST(has_set_color == true,
		 "when parse color C 225,30,0 expect has_set_color == true");

	has_set_color = false;
	result = parse_color("F 220,100", &color, &has_set_color);
	FT_TEST(result == false,
		 "when parse color F 220,100 expect == false");
	FT_TEST(has_set_color == false,
		 "when parse color F 220,100,0 expect has_set_color == false");

	has_set_color = false;
	result = parse_color("", &color, &has_set_color);
	FT_TEST(result == false,
		 "when parse color '' expect == false");
	FT_TEST(has_set_color == false,
		 "when parse color '' expect has_set_color == false");

	has_set_color = false;
	result = parse_color("F 300,100,0", &color, &has_set_color);
	FT_TEST(result == false,
		 "when invalid range 'F 300,100,0' expect == false");
	FT_TEST(has_set_color == false,
		 "when invalid range 'F 300,100,0' expect has_set_color == false");
	ft_printf("%s: END\n", __FUNCTION__);
}
