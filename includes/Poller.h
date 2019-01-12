#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>

typedef std::vector<std::string>	t_vs;

class Poller
{
public:
					Poller(double timeout, t_vs const &hosts) :
							m_timeout(timeout),
							m_hosts(hosts) {}
	virtual			~Poller(void) = default;
	virtual void	Poll(void) {};
	virtual void	UpdatePoller(t_vs hosts, double timeout) {};

protected:
    double			m_timeout;
    t_vs			m_hosts;
};
