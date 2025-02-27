/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:21:24 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/27 15:28:49 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

t_vec2i	vec2i_scale(t_vec2i vec, int scalar)
{
	return (t_vec2i) { vec.x * scalar, vec.y * scalar};
}

t_vec2f	vec2f_scalei(t_vec2f vec, int scalar)
{
	return (t_vec2f) { vec.x * scalar, vec.y * scalar};
}

t_vec2f	vec2f_scale(t_vec2f vec, float scalar)
{
	return (t_vec2f) { vec.x * scalar, vec.y * scalar};
}

t_vec2i	vec2i_add(t_vec2i vec_a, t_vec2i vec_b)
{
	return (t_vec2i) { vec_a.x + vec_b.x, vec_a.y + vec_b.y};
}

t_vec2i	vec2i_addf(t_vec2i vec_a, t_vec2f vec_b)
{
	return (t_vec2i) { vec_a.x + (int) vec_b.x, vec_a.y + (int) vec_b.y};
}

t_vec2f	vec2f_add(t_vec2f vec_a, t_vec2f vec_b)
{
	return (t_vec2f) { vec_a.x + vec_b.x, vec_a.y + vec_b.y};
}

t_vec2f	vec2f_addi(t_vec2f vec_a, t_vec2i vec_b)
{
	return (t_vec2f) { vec_a.x + vec_b.x, vec_a.y + vec_b.y};
}

t_vec2i	vec2i_offset(t_vec2i vec_a, int scalar)
{
	return (t_vec2i) { vec_a.x + scalar, vec_a.y + scalar};
}

t_vec2f	vec2f_offset(t_vec2f vec_a, float scalar)
{
	return (t_vec2f) { vec_a.x + scalar, vec_a.y + scalar};
}
