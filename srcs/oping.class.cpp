#include <iostream>

#include "oping.class.h"

		oping::oping(t_vs const &hosts, double timeout) : _ping(ping_construct())
{
	for (std::string const &host : hosts)
		ping_host_add(this->_ping, host.c_str());
	ping_setopt(_ping, PING_OPT_TIMEOUT, &timeout);
}

		oping::~oping(void) {ping_destroy(this->_ping);}

void	oping::setTimeout(double timeout)
{
	ping_setopt(this->_ping, PING_OPT_TIMEOUT, &timeout);
}

void	oping::addHosts(t_vs const &hosts)
{
	for (std::string const &host : hosts)
		ping_host_add(this->_ping, host.c_str());
}

void	oping::removeHosts(t_vs const &hosts)
{
	for (std::string const &host : hosts)
		ping_host_remove(this->_ping, host.c_str());
}

void	oping::sendPing(void)
{
	ping_send(_ping);
	pingobj_iter_t *_iter;
	for (_iter = ping_iterator_get(_ping);
		 _iter != NULL; _iter = ping_iterator_next(_iter))
	{
		char temphostname[100];
		double latency;
		long unsigned int len;
		len = 100;
		ping_iterator_get_info(_iter, PING_INFO_HOSTNAME, temphostname,
							   &len);
		len = sizeof(double);
		ping_iterator_get_info(_iter, PING_INFO_LATENCY, &latency, &len);
		std::cout << temphostname << " - " << latency << std::endl;
	}
}
