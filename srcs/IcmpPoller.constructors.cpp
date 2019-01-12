#include "IcmpPoller.h"

#include "oping.class.h"

IcmpPoller::IcmpPoller(t_vs const &hosts, double timeout) :
		Poller(timeout, hosts), _ping(new oping(hosts, timeout)) {}

IcmpPoller::~IcmpPoller(void) {delete this->_ping;}
