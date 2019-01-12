#ifndef TESTTASK_POLLER_H
#define TESTTASK_POLLER_H

#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>

typedef std::vector<std::string>	t_vs;

class Poller
{
public:
								Poller(double timeout, t_vs const &hosts) :
										m_timeout(timeout),
										m_hosts(hosts) {}
	virtual						~Poller(void) = default;
    double m_timeout;
    std::vector<std::string> m_hosts;

    virtual void Poll() {};
    virtual void UpdatePoller(std::vector<std::string> hosts, double timeout) {};
};


#endif //TESTTASK_POLLER_H
