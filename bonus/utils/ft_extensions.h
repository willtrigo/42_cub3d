/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extensions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:49:41 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/19 19:00:15 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXTENSIONS_H
# define FT_EXTENSIONS_H

# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>

bool	ft_is_blank(char *str);
size_t	ft_strarr_len(char **strarr);
bool	ft_atoi8_range(uint8_t *out_value, char *str, int range_low, \
			int range_high);
int		ft_free_arr_retvalue(char **to_free, int retvalue);
int		ft_free_retvalue(void *to_free, int retvalue);

#endif
