/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_colision_walls_internal.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:56:46 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/25 17:10:16 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system_colision_walls_internal.h"
#include "graphic/render.h"

void	system_colision_walls_h(
	t_manager *manager, t_location *intention, float p_half_size)
{
	int		offset;
	char	scene_entity;

	offset = (2 * (intention->pos.x > manager->player.loc.pos.x)) - 1;
	scene_entity = chart_entity(&manager->chart, (t_vec2f){
			intention->pos.x + (p_half_size * offset), intention->pos.y});
	if (scene_entity != '1')
		return ;
	else if (offset > 0)
		intention->pos.x = ((int) intention->pos.x + 1) - p_half_size;
	else
		intention->pos.x = ((int) intention->pos.x) + p_half_size;
}

void	system_colision_walls_v(
	t_manager *manager, t_location *intention, float p_half_size)
{
	int		offset;
	char	scene_entity;

	offset = (2 * (intention->pos.y > manager->player.loc.pos.y)) - 1;
	scene_entity = chart_entity(&manager->chart, (t_vec2f){
			intention->pos.x, intention->pos.y + (p_half_size * offset)});
	if (scene_entity != '1')
		return ;
	else if (offset > 0)
		intention->pos.y = ((int) intention->pos.y + 1) - p_half_size;
	else
		intention->pos.y = ((int) intention->pos.y) + p_half_size;
}

static void	resolve_diagonal(\
	const t_vec2f	*movement_vec, t_location *intention, float p_half_size)
{
	const float		diag_component = p_half_size * M_SQRT1_2 + 0.08;

	if (movement_vec->x > 0)
		intention->pos.x = ((int) intention->pos.x + 1) - diag_component;
	else
		intention->pos.x = ((int) intention->pos.x) + diag_component;
	if (movement_vec->y > 0)
		intention->pos.y = ((int) intention->pos.y + 1) - diag_component;
	else
		intention->pos.y = ((int) intention->pos.y) + diag_component;
}

void	system_colision_walls_diag_resolve(
	t_manager *manager, t_location *intention, float p_half_size)
{
	const t_vec2f	movement_vec = vec2f_sub(\
		intention->pos, manager->player.loc.pos);

	if (fabs(movement_vec.y) >= fabs(movement_vec.x))
	{
		if (movement_vec.x > 0)
			intention->pos.x = ((int) intention->pos.x + 1) - p_half_size;
		else
			intention->pos.x = ((int) intention->pos.x) + p_half_size;
		return ;
	}
	else if (fabs(movement_vec.x) > fabs(movement_vec.y))
	{
		if (movement_vec.y > 0)
			intention->pos.y = ((int) intention->pos.y + 1) - p_half_size;
		else
			intention->pos.y = ((int) intention->pos.y) + p_half_size;
		return ;
	}
	resolve_diagonal(&movement_vec, intention, p_half_size);
}

void	system_colision_walls_diag(
	t_manager *manager, t_location *intention, float p_half_size)
{
	t_vec2i		offset;
	char		scene_entity_x;
	char		scene_entity_y;
	char		scene_entity_diag;

	offset.y = (2 * (intention->pos.y > manager->player.loc.pos.y)) - 1;
	offset.x = (2 * (intention->pos.x > manager->player.loc.pos.x)) - 1;
	scene_entity_y = chart_entity(&manager->chart, (t_vec2f){
			intention->pos.x, intention->pos.y + (p_half_size * offset.y)});
	scene_entity_x = chart_entity(&manager->chart, (t_vec2f){
			intention->pos.x + (p_half_size * offset.x), intention->pos.y});
	scene_entity_diag = chart_entity(&manager->chart, (t_vec2f){
			intention->pos.x + (p_half_size * offset.x),
			intention->pos.y + (p_half_size * offset.y)});
	if (scene_entity_x == '1' && scene_entity_y == '1')
	{
		system_colision_walls_h(manager, intention, p_half_size);
		system_colision_walls_v(manager, intention, p_half_size);
	}
	else if (scene_entity_x == '1')
		system_colision_walls_h(manager, intention, p_half_size);
	else if (scene_entity_y == '1')
		system_colision_walls_v(manager, intention, p_half_size);
	else if (scene_entity_diag == '1')
		system_colision_walls_diag_resolve(manager, intention, p_half_size);
}
