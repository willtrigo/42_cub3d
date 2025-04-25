/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:58:25 by maurodri          #+#    #+#             */
/*   Updated: 2025/03/12 02:47:43 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

typedef struct s_vec2i
{
	int	x;
	int	y;
}	t_vec2i;

typedef struct s_vec2f
{
	float	x;
	float	y;
}	t_vec2f;

// vec2i.c
t_vec2i	vec2i_scale(t_vec2i vec, int scalar);
t_vec2i	vec2i_add(t_vec2i vec_a, t_vec2i vec_b);
t_vec2i	vec2i_addf(t_vec2i vec_a, t_vec2f vec_b);
t_vec2f	vec2i_tof(t_vec2i vec_a);
t_vec2i	vec2i_offset(t_vec2i vec_a, int scalar);
// vec2.c
t_vec2f	vec2f_addi(t_vec2f vec_a, t_vec2i vec_b);
t_vec2f	vec2f_scalei(t_vec2f vec, int scalar);
// vec2f.c
t_vec2f	vec2f_scale(t_vec2f vec, float scalar);
t_vec2f	vec2f_add(t_vec2f vec_a, t_vec2f vec_b);
t_vec2f	vec2f_offset(t_vec2f vec_a, float scalar);
t_vec2f	vec2f_sub(t_vec2f vec_a, t_vec2f vec_b);
// vec2f_linear.c
float	vec2f_magnitude2(t_vec2f vec_a);
float	vec2f_magnitude(t_vec2f vec_a);
t_vec2f	vec2f_unit_vector(float angle);
t_vec2f	vec2f_to_unit(t_vec2f vec_a);
float	vec2f_dot_product(t_vec2f vec_a, t_vec2f vec_b);

#endif
