/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f_linear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:46:14 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/12 02:46:15 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/vec2.h"
#include <math.h>

float	vec2f_magnitude2(t_vec2f vec_a)
{
	return ((vec_a.x * vec_a.x) + (vec_a.y * vec_a.y));
}

float	vec2f_magnitude(t_vec2f vec_a)
{
	return (sqrt(vec2f_magnitude2(vec_a)));
}

t_vec2f	vec2f_unit_vector(float angle)
{
	return ((t_vec2f){1.f * cosf(angle), 1.f * sinf(angle)});
}

t_vec2f	vec2f_to_unit(t_vec2f vec_a)
{
	const float	mag = vec2f_magnitude(vec_a);

	if (mag < 0.00000001f)
		return ((t_vec2f){0, 0});
	return ((t_vec2f){vec_a.x / mag, vec_a.y / mag});
}

float	vec2f_dot_product(t_vec2f vec_a, t_vec2f vec_b)
{
	return ((vec_a.x * vec_b.x) + (vec_a.y * vec_b.y));
}
