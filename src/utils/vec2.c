/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:21:24 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/12 02:45:32 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"
#include <math.h>

t_vec2f	vec2f_scalei(t_vec2f vec, int scalar)
{
	return ((t_vec2f){vec.x * scalar, vec.y * scalar});
}

t_vec2f	vec2f_addi(t_vec2f vec_a, t_vec2i vec_b)
{
	return ((t_vec2f){vec_a.x + vec_b.x, vec_a.y + vec_b.y});
}
