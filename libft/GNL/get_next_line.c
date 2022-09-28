/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:21:44 by jniemine          #+#    #+#             */
/*   Updated: 2022/01/17 10:27:59 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_hashNode	*ft_new_hash_node(int key, void *value)
{
	t_hashNode	*new_node;

	new_node = (t_hashNode *)ft_memalloc(sizeof(t_hashNode));
	if (new_node == NULL)
		return (NULL);
	(*new_node).key = key;
	if (value != NULL)
		(*new_node).v = value;
	else
		(*new_node).v = (void *)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1));
	if ((*new_node).v == NULL)
		return (NULL);
	(*new_node).p = 0;
	(*new_node).next = NULL;
	return (new_node);
}

ssize_t	reader(t_line *wrap, t_hashNode **node, size_t old_size, ssize_t *len)
{	
	if (old_size == 0 || ((*node)->p == BUFF_SIZE))
	{
		*len = read((*node)->key, (*node)->v, BUFF_SIZE);
		(*node)->p = 0;
		if (*len == -1)
		{
			free ((*node)->v);
			free (*node);
			return (-1);
		}
		if (*len < BUFF_SIZE)
			((signed char *)(*node)->v)[*len] = -1;
	}
	if (old_size >= wrap->space || old_size == 0)
	{
		wrap->space = 3 * wrap->space / 2 + 1000;
		*wrap->line = ft_realloc(*wrap->line, old_size, wrap->space + 1);
	}
	if (*wrap->line == NULL)
		return (-1);
	return (*len);
}

t_list	*search_for_key(int key, t_list **head, t_line *wrap, ssize_t *len)
{
	t_hashNode	*node;
	t_list		*lst_start;

	lst_start = *head;
	if (*wrap->line == NULL)
		return (NULL);
	while (*head != NULL && (*head)->content != NULL
		&& ((t_hashNode *)(*head)->content)->key != key)
		*head = (*head)->next;
	if (*head == NULL || (*head)->content == NULL)
	{
		node = ft_new_hash_node(key, NULL);
		if (node == NULL)
			return (NULL);
		*len = reader(wrap, &node, 0, len);
		if (*len == -1)
			return (NULL);
		*head = ft_lstnew(node, sizeof(t_hashNode));
		ft_lstadd(&lst_start, *head);
		free (node);
	}
	return (*head);
}

int	write_to_line(t_line *wrap, t_list *lst_node, t_list **hash, ssize_t *len)
{
	t_hashNode	*node;

	wrap->i = 0;
	node = lst_node->content;
	while (((char *)node->v)[node->p] != -1
	&& ((char *)node->v)[node->p] != '\n')
	{
		if ((node->p == BUFF_SIZE && ((char *)node->v)[node->p] != '\n')
		|| wrap->i == wrap->space)
			if (reader(wrap, &node, wrap->i, len) == -1)
				return (-1);
		while (node->p < BUFF_SIZE && ((char *)node->v)[node->p] != '\n'
		&& ((char *)node->v)[node->p] != -1 && wrap->i < wrap->space)
			(*wrap->line)[wrap->i++] = ((char *)node->v)[node->p++];
	}
	if ((((char *)node->v)[node->p] == '\n' && ++node->p) || wrap->i > 0)
		return (1);
	free (node->v);
	ft_lstdelany(hash, lst_node);
	free (lst_node);
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	int				code;
	ssize_t			len;
	static t_list	*hash[100] = {NULL};
	t_list			*lst_node;
	t_line			wrap;

	code = fd % 99;
	wrap.space = BUFF_SIZE + 1;
	len = 1;
	if (line == NULL || fd < 0 || fd > 10240)
		return (-1);
	*line = (char *)ft_memalloc(sizeof(**line) * wrap.space);
	wrap.line = line;
	lst_node = search_for_key(fd, &(hash[code]), &wrap, &len);
	if (len == 0)
	{
		free (((t_hashNode *)lst_node->content)->v);
		ft_lstdelany(&hash[code], lst_node);
		free (lst_node);
		return (0);
	}
	if (lst_node == NULL && len != 0)
		return (-1);
	return (write_to_line(&wrap, lst_node, &(hash[code]), &len));
}
