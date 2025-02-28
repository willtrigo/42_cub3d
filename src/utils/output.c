/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:25:41 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/28 13:14:04 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

int	logerr_ret(char *str, int ret)
{
	ft_puterr("Error:\n\t");
	ft_puterrl(str);
	return (ret);
}
