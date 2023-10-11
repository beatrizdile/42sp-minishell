#include "minishell.h"

static void		sort_env(t_list *export);
static t_list	*copy_env_list(t_list *env, t_list *lst);
static void		print_export(t_list *export);
static int		find_in_env(t_data *data, char	*prompt);

void	export_builtin(t_data *data, char **args)
{
	t_list	*export;
	int		i;
	int		len;

	export = NULL;
	len = ft_arrsize(args);
	if (len == 1)
		sort_env(copy_env_list(data->env, export));
	else
	{
		i = 0;
		while (++i < len)
			if (args[i])
				if (!find_in_env(data, args[i]))
					ft_lstadd_back(&data->env, ft_lstnew(ft_strdup(args[i])));
	}
	data->exit_status = 0;
}

static t_list	*copy_env_list(t_list *env, t_list *lst)
{
	while (env != NULL)
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(env->content)));
		env = env->next;
	}
	return (lst);
}

int	find_in_env(t_data *data, char *var)
{
	t_list	*temp;
	char	**arr;
	char	**env;

	temp = data->env;
	arr = ft_split(var, '=');
	while (temp)
	{
		env = ft_split(temp->content, '=');
		if (ft_strcmp(env[0], arr[0]) == 0)
		{
			if (arr[1])
			{
				free(temp->content);
				temp->content = ft_strdup(var);
			}
			ft_free_str_arr(&env);
			ft_free_str_arr(&arr);
			return (1);
		}
		ft_free_str_arr(&env);
		temp = temp->next;
	}
	ft_free_str_arr(&arr);
	return (0);
}

void	sort_env(t_list *export)
{
	t_list	*temp1;
	t_list	*temp2;
	int		swapped;

	temp2 = NULL;
	while (true)
	{
		temp1 = export;
		swapped = 0;
		while (temp1->next != temp2)
		{
			if (ft_strcmp(temp1->content, temp1->next->content) > 0)
			{
				ft_swap_lst(temp1);
				swapped = 1;
			}
			temp1 = temp1->next;
		}
		temp2 = temp1;
		if (!swapped)
			break ;
	}
	print_export(export);
	free_list(export);
}

void	print_export(t_list *export)
{
	char	**arr;

	while (export)
	{
		arr = ft_split((char *)export->content, '=');
		if (arr[1])
			printf("declare -x %s=\"%s\"\n", arr[0], arr[1]);
		else
			printf("declare -x %s=\"\"\n", arr[0]);
		ft_free_str_arr(&arr);
		export = export->next;
	}
}
