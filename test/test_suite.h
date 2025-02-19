/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_suite.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:29:35 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/19 19:51:28 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_SUITE_H
# define TEST_SUITE_H

# include "ft_stdio.h"

#define FT_TEST(test, error_message)                                                    \
	do                                                                                  \
	{                                                                                   \
		if (!(test))                                                                    \
		{                                                                               \
			ft_printf("\n%s:%d:0 => %s \n", __FILE__, __LINE__, error_message);         \
		}                                                                               \
	} while (0);


void	test_config_init(void);
void    test_color(void);
void	test_parse_color(void);
void	test_is_valid_args();

#endif
