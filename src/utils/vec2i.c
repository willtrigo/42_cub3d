/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:35:11 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/12 02:38:12 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/vec2.h"

t_vec2i	vec2i_scale(t_vec2i vec, int scalar)
{
	return ((t_vec2i){vec.x * scalar, vec.y * scalar});
}

t_vec2i	vec2i_add(t_vec2i vec_a, t_vec2i vec_b)
{
	return ((t_vec2i){vec_a.x + vec_b.x, vec_a.y + vec_b.y});
}

t_vec2f	vec2i_tof(t_vec2i vec_a)
{
	return ((t_vec2f){vec_a.x, vec_a.y});
}

t_vec2i	vec2i_addf(t_vec2i vec_a, t_vec2f vec_b)
{
	return ((t_vec2i){vec_a.x + (int) vec_b.x, vec_a.y + (int) vec_b.y});
}

t_vec2i	vec2i_offset(t_vec2i vec_a, int scalar)
{
	return ((t_vec2i){vec_a.x + scalar, vec_a.y + scalar});
}
