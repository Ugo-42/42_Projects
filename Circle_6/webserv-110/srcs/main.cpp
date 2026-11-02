/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:12:26 by ugwentzi          #+#    #+#             */
/*   Updated: 2026/03/27 12:17:40 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include "ServerManager.hpp"

bool g_stop(false);

void ctrl_c(int signum)
{
    (void)signum;
    std::cout << "\nShutting down server..." << std::endl;
    g_stop = true;
}

int main(int argc, char **argv)
{
    signal(SIGINT, ctrl_c);
	signal(SIGPIPE, SIG_IGN);

    if (argc > 2)
    {
        ERROR("Usage: " << argv[0] << " [configuration file]");
        return 1;
    }

    const RgbColor red(255, 0, 0);

    t_config config;

    try
    {
        parseConfigFile(argc > 1 ? argv[1] : "conf/default.conf", config);
    }
    catch (const std::exception &e)
    {
        ERROR(red("Error: ") << e.what());
        return 1;
    }

    try
    {
        ServerManager   mgr(config);
        mgr.run();
    }
    catch (const std::exception &e)
    {
        ERROR(red("Server error: ") << e.what());
        return 1;
    }

    return 0;
}
