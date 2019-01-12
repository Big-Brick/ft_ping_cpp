#pragma once

#include "Ping.class.h"

#include <oping.h>

class oping : public Ping
{
public:
				oping(t_vs const &hosts, double timeout);
	virtual		~oping(void);
	void		setTimeout(double timeout) override;
	void		addHosts(t_vs const &hosts) override;
	void		removeHosts(t_vs const &hosts) override;
	void		sendPing(void) override;

private:
	pingobj_t*	_ping;
};
