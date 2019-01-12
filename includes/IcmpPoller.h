#ifndef TESTTASK_ICMPPOLLER_H
#define TESTTASK_ICMPPOLLER_H

#include "Poller.h"
#include <oping.h>

class IcmpPoller : public Poller
{
public:
    			IcmpPoller(t_vs const &hosts, double timeout);
    			~IcmpPoller(void) {ping_destroy(this->_ping);}
    void		Poll(void) override;
    void		UpdatePoller(std::vector<std::string> hosts, double timeout) override;

private:
    pingobj_t*	_ping;
};


#endif //TESTTASK_ICMPPOLLER_H
