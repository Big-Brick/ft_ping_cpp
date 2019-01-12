#include "IcmpPoller.h"

void IcmpPoller::Poll(void)
{
	while(true)
	{
		this->_ping->sendPing();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "--------------------------------------------------" << std::endl;
    }
}

void IcmpPoller::UpdatePoller(t_vs hosts, double timeout)
{
	t_vs	hostsToRemove;

    for(auto it = m_hosts.begin(); it != m_hosts.end(); )
    {
        auto found = std::find(hosts.begin(), hosts.end(), *it);
        if(found == hosts.end())
        {
        	hostsToRemove.push_back(*it);
            m_hosts.erase(it);

        }
        else
        {
            ++it;
            hosts.erase(found);
        }
    }
    this->_ping->addHosts(hosts);
    this->_ping->removeHosts(hostsToRemove);
    for (std::string host : hosts)
        m_hosts.push_back(host);
    if(timeout != m_timeout)
    {
        m_timeout = timeout;
        this->_ping->setTimeout(timeout);
    }
}
