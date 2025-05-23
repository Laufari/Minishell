/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:30:25 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/24 14:40:30 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*int main_exec(t_data *data)
{
	t_dlist *i_node;

	create_files(data);
	i_node = data->cmd_list;
	while (i_node)
	{
		ft_echo(data->env_list, ((t_chunk *)(i_node->content))->argv);
		i_node = i_node->next;
	}
	return(SUCCESS);
}*/
int main_exec(t_data *data)
{
    t_dlist *i_node;
    int     status;

    setup_signals(); // Asegurar señales configuradas
    i_node = data->cmd_list;
    while (i_node)
    {
        if (is_builtin(((t_chunk *)i_node->content)->argv[0]))
            status = exec_builtin(data, ((t_chunk *)i_node->content)->argv);
        else
            status = exec_external(data, (t_chunk *)i_node->content); //FUnCION OLIV
        
        if (g_signal_received) // Manejo de señales durante ejecución
        {
            data->exit_status = g_signal_received;
            g_signal_received = 0;
            return (status);
        }
        i_node = i_node->next;
    }
    return (status);
}