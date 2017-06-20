/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:22:34 by pribault          #+#    #+#             */
/*   Updated: 2017/06/20 13:44:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	get_attrib_2(t_env *env, t_attribute *attr, char *tmp)
{
	t_element	*elems;
	char		**array;
	int			i[2];
	int			r;

	elems = get_elements();
	i[0] = 0;
	r = 0;
	while (elems[i[0]].name)
	{
		i[1] = 0;
		if (elems[i[0]].macro == ((t_object*)env->elem->content)->type)
			while (i[1] < elems[i[0]].n_params)
				if (!ft_strncmp(elems[i[0]].params[i[1]++], attr->name,
				ft_strlen(attr->name)))
					r = 1;
		i[0]++;
	}
	array = ft_multisplit(tmp, " ,\t");
	free(tmp);
	if (ft_arraylen(array) == attr->n_params && r)
		attr->func(env->elem->content, array);
	else
		return (0);
	return (1);
}

char	get_attrib(t_env *env, t_attribute *attr, char *line, int *i)
{
	char	*tmp;
	int		j;
	int		l;

	j = 0;
	while (attr[j].name)
	{
		if (!ft_strncmp(attr[j].name, line + *i, ft_strlen(attr[j].name)))
		{
			*i += ft_strlen(attr[j].name);
			while (line[*i] == '\t' || line[*i] == ' ')
				(*i)++;
			if (!env->elem || line[*i] != '(')
				return (0);
			l = 0;
			while (line[*i + 1 + l] && line[*i + 1 + l] != ')')
				l++;
			tmp = ft_strndup(line + *i + 1, l);
			return (get_attrib_2(env, &attr[j], tmp));
		}
		j++;
	}
	return (0);
}

char	get_elem(t_env *env, t_element *elem, char *line, int *i)
{
	t_list	*new;
	int		j;

	j = 0;
	while (elem[j].name)
	{
		if (!ft_strncmp(elem[j].name, line + *i, ft_strlen(elem[j].name)))
		{
			*i += ft_strlen(elem[j].name);
			if (!(new = (t_list*)malloc(sizeof(t_list))))
				return (0);
			if (!(new->content = (void*)malloc(sizeof(t_object))))
				return (0);
			ft_bzero(new->content, sizeof(t_object));
			((t_object*)new->content)->type = elem[j].macro;
			new->next = env->elem;
			env->elem = new;
			return (1);
		}
		j++;
	}
	return (0);
}

void	set_camera(t_env *env)
{
	t_object	*obj;
	t_list		*list;

	list = env->elem;
	while (list)
	{
		obj = list->content;
		if (obj->type == CAMERA)
		{
			env->cam.pos = obj->pos;
			env->cam.q = obj->angle;
			env->cam.d = obj->d;
			env->cam.fov_w = obj->fov_w;
			env->cam.fov_h = obj->fov_h;
			env->cam.w = 2 * env->cam.d * tan(env->cam.fov_w);
			env->cam.h = 2 * env->cam.d * tan(env->cam.fov_h);
		}
		list = list->next;
	}
}
