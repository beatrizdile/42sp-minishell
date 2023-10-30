#include "minishell.h"

static void		sort_env(t_list *export);
static t_list	*copy_env_list(t_list *env, t_list *lst);
static int		find_in_env(t_data *data, char	*prompt);
static int		search_key(char **env, t_list *temp, char **arr, char *var);

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
				if (find_in_env(data, args[i]) == 0)
					ft_lstadd_back(&data->env, ft_lstnew(ft_strdup(args[i])));
	}
	if (data->exit_status != 0)
		return ;
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

static int	find_in_env(t_data *data, char *var)
{
	t_list	*temp;
	char	**arr;
	char	**env;

	temp = data->env;
	arr = split_key_and_value(var, '=');
	if (check_key(arr[0]) == 0)
	{
		ft_printf_fd(2, "export: '%s': not a valid identifier\n", arr[0]);
		data->exit_status = 1;
		ft_free_str_arr(&arr);
		return (2);
	}
	env = NULL;
	if (search_key(env, temp, arr, var) == 1)
		return (1);
	ft_free_str_arr(&arr);
	return (0);
}

static int	search_key(char **env, t_list *temp, char **arr, char *var)
{
	while (temp)
	{
		env = split_key_and_value(temp->content, '=');
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
	return (0);
}

static void	sort_env(t_list *export)
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
