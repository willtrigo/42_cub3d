/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_valid_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:50:10 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/19 19:51:30 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/config/config_internal.h"
#include "test_suite.h"

void test_is_valid_args()
{
	ft_printf("\n%s :START\n", __FUNCTION__);

	FT_TEST(is_invalid_args(1, "name.cub")
			== true,
			"when argc == 1 and filename == name.cub expected invalid args to be true");

	FT_TEST(is_invalid_args(0, "name.cub")
			== false,
			"when argc == 0 and filename == name.cub expected invalid args to be false");

	FT_TEST(is_invalid_args(2, "name.cub")
			== false,
			"when argc == 2 and filename == name.cub expected invalid args to be false");

	FT_TEST(is_invalid_args(1, "name")
			== false,
			"when argc == 1 and filename == name expected invalid args to be false");

	FT_TEST(is_invalid_args(1, "cub")
			== false,
			"when argc == 1 and filename == cub expected invalid args to be false");

	FT_TEST(is_invalid_args(1, ".cub")
			== true,
			"when argc == 1 and filename == .cub expected invalid args to be true");

	ft_printf("%s: END\n", __FUNCTION__);
}
