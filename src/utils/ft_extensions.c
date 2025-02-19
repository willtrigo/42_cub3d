/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extensions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:49:14 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/19 18:36:00 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>
#include "ft_ctype.h"
#include "utils/ft_extensions.h"
#include "ft_string.h"

bool	ft_is_blank(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

size_t	ft_strarr_len(char **strarr)
{
	size_t	len;

	len = 0;
	while (*(strarr++))
		len++;
	return (len);
}

bool	ft_atoi8_range(uint8_t *out_value, char *str, int range_low, \
			int range_high)
{
	int	out_ok;
	int	result;

	out_ok = 0;
	result = ft_atoi_strict(&out_ok, str);
	if (!out_ok)
		return (false);
	if (result < range_low || result > range_high)
		return (false);
	*out_value = (uint8_t)result;
	return (true);
}

int	ft_free_arr_retvalue(char **to_free, int retvalue)
{
	ft_strarr_free(to_free);
	return (retvalue);
}
