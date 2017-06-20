/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 17:31:39 by pribault          #+#    #+#             */
/*   Updated: 2017/06/21 00:50:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_attribute	*get_attributes(void)
{
	static t_attribute	attribs[] = {
		{"name", 1, {STRING}, &set_name},
		{"color", 3, {UCHAR, UCHAR, UCHAR}, &set_color},
		{"alpha", 1, {UCHAR}, &set_alpha},
		{"reflection", 1, {FLOAT}, &set_reflection},
		{"position", 3, {FLOAT, FLOAT, FLOAT}, &set_position},
		{"radius", 1, {FLOAT}, &set_radius},
		{"distance", 1, {FLOAT}, &set_distance},
		{"angle", 3, {FLOAT, FLOAT, FLOAT}, &set_angle},
		{"intensity", 3, {FLOAT, FLOAT, FLOAT}, &set_intensity},
		{"fov", 2, {FLOAT, FLOAT}, &set_fov},
		{"normal", 3, {FLOAT, FLOAT, FLOAT}, &set_normal},
		{NULL, 0, {0}, NULL}};

	return (attribs);
}

t_element	*get_elements(void)
{
	static char			*t[][11] = {
	{"name", "position", "color", "reflection", "radius"},
	{"name", "position", "distance", "angle", "fov"},
	{"name", "position", "intensity", "alpha"},
	{"name", "position", "normal", "color", "reflection"},
	{"name", "position", "color", "reflection", "alpha", "normal"},
	{"name", "position", "color", "reflection", "normal", "radius"}};
	static t_element	elements[] = {
		{"sphere", 5, t[0], SPHERE},
		{"plan", 5, t[3], PLAN},
		{"cone", 6, t[4], CONE},
		{"cylinder", 6, t[5], CYLINDER},
		{"camera", 5, t[1], CAMERA},
		{"lightspot", 4, t[2], LIGHT_SPOT},
		{NULL, 0, NULL, 0}};

	return (elements);
}

char		understand_instruction(t_env *env, t_attribute *attribs,
			t_element *elems, char *line)
{
	static char	state = 0;
	int			i[2];
	char		r;

	i[0] = 0;
	while (line[i[0]] == '\t' || line[i[0]] == ' ')
		i[0]++;
	if (line[i[0]] == '{' || line[i[0]] == '}')
		state = (line[i[0]++] == '{') ? 1 : 0;
	i[1] = 0;
	if (!ft_strlen(line + i[0]))
		return (1);
	if (!state)
	{
		r = get_elem(env, elems, line, &i[0]);
		while (line[i[0]] == '\t' || line[i[0]] == ' ')
			i[0]++;
		if (line[i[0]] == '{')
			state = 1;
		return (r);
	}
	else
		return (get_attrib(env, attribs, line, &i[0]));
}

char		load_scene(t_env *env, char *scene)
{
	t_attribute	*attribs;
	t_element	*elems;
	char		*line;
	int			fd;
	int			i;

	if ((fd = open(scene, O_RDONLY)) == -1)
		return (0);
	i = 0;
	attribs = get_attributes();
	elems = get_elements();
	while (ft_get_next_line(fd, &line))
	{
		if (line[0] != '#' && !understand_instruction(env, attribs,
		elems, line))
			return (0);
		free(line);
	}
	free(line);
	close(fd);
	return (1);
}
