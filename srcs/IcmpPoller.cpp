
#include "../includes/IcmpPoller.h"

		IcmpPoller::IcmpPoller(t_vs const &hosts, double timeout) :
				Poller(timeout, hosts), _ping(ping_construct())
{
    ping_setopt(_ping, PING_OPT_TIMEOUT, &m_timeout);
}

void IcmpPoller::Poll()
{
    while(true)
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
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "--------------------------------------------------" << std::endl;
    }
}

void IcmpPoller::UpdatePoller(std::vector<std::string> hosts, double timeout) {
    for(auto it = m_hosts.begin(); it != m_hosts.end(); ) {
        auto found = std::find(hosts.begin(), hosts.end(), *it);
        if(found == hosts.end()) {
            ping_host_remove(_ping, it->c_str());
            m_hosts.erase(it);

        }
        else {
            ++it;
            hosts.erase(found);
        }
    }
    for (std::string host : hosts) {
        ping_host_add(_ping, host.c_str());
        m_hosts.push_back(host);
    }
    if(timeout != m_timeout) {
        m_timeout = timeout;
        ping_setopt(_ping, PING_OPT_TIMEOUT, &m_timeout);
    }
}
