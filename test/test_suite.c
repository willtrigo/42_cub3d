/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_suite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:24:50 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/12 21:31:58 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_assert.h"
#include "ft_stdio.h"

// void initialize_stderr() {
//     // Reopen stderr to ensure it's properly initialized
//     if (freopen("/dev/null", "w", stderr) == NULL) {
//         // If freopen fails, print an error and exit
//         perror("freopen");
//         exit(EXIT_FAILURE);
//     }
// }
// void initialize_stderr() {
//     static FILE stderr_buf;
//     stderr = &stderr_buf;
//     // Additional setup for stderr if needed
// }

int	test_suite(void)
{
	t_color	color;
	int *str;

	str = malloc(sizeof(int));
	*str = 1;

	color = ft_color(0, 0, 0, 0);
	// printf("Hello test color %d", color.value);
	char *msg = NULL;
	ft_asprintf(&msg, "%s%d %s ", __FILE__, __LINE__, "some error message");
	ft_assert(0 == *str, msg);
	exit (EXIT_SUCCESS);
}
