/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extensions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:49:14 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/17 18:53:49 by dande-je         ###   ########.fr       */
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

size_t ft_strarr_len(char **strarr)
{
	size_t	len;

	len = 0;
	while (*(strarr++))
		len++;
	return (len);
}

bool	ft_atoi8_range(uint8_t *out_value, char *str, int range_low, int range_high)
{
	int	has_parse_error;

	has_parse_error = 0;
	*out_value = ft_atoi_strict(&has_parse_error, str);
	if (has_parse_error)
		return (true);
	if (*out_value >= range_low && *out_value <= range_high)
		return (false);
	return (true);
}

int	ft_free_arr_retvalue(char **to_free, int retvalue)
{
	ft_strarr_free(to_free);
	return (retvalue);
}
