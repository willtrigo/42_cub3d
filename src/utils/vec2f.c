/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:42:44 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/12 02:44:52 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/vec2.h"

t_vec2f	vec2f_scale(t_vec2f vec, float scalar)
{
	return ((t_vec2f){vec.x * scalar, vec.y * scalar});
}

t_vec2f	vec2f_add(t_vec2f vec_a, t_vec2f vec_b)
{
	return ((t_vec2f){vec_a.x + vec_b.x, vec_a.y + vec_b.y});
}

t_vec2f	vec2f_sub(t_vec2f vec_a, t_vec2f vec_b)
{
	return ((t_vec2f){vec_a.x - vec_b.x, vec_a.y - vec_b.y});
}

t_vec2f	vec2f_offset(t_vec2f vec_a, float scalar)
{
	return ((t_vec2f){vec_a.x + scalar, vec_a.y + scalar});
}
