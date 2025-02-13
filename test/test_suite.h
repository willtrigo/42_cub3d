/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_suite.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:29:35 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/13 14:24:44 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_SUITE_H
# define TEST_SUITE_H

// #include <assert.h>

#define FT_TEST(test, error_message)                                                    \
	do                                                                                  \
	{                                                                                   \
		if (!(test))                                                                    \
		{                                                                               \
			char *msg = NULL;                                                           \
			ft_asprintf(&msg, "\n%s:%d:0 => %s \n", __FILE__, __LINE__, error_message); \
			ft_assert((test), msg);                                                     \
			free(msg);                                                                  \
		}                                                                               \
	} while (0);

#endif
