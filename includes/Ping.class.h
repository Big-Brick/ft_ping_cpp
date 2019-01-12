#pragma once

#include <string>
#include <vector>

typedef std::vector<std::string>	t_vs;

class Ping
{
public:
	virtual			~Ping(void) = default;
	virtual void	setTimeout(double timeout) = 0;
	virtual void	addHosts(t_vs const &hosts) = 0;
	virtual void	removeHosts(t_vs const &hosts) = 0;
	virtual void	sendPing(void) = 0;
};