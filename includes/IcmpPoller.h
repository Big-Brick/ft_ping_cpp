#pragma once

#include "Poller.h"
#include "Ping.class.h"

class IcmpPoller : public Poller
{
public:
    			IcmpPoller(t_vs const &hosts, double timeout);
    			~IcmpPoller(void);
    void		Poll(void) override;
    void		UpdatePoller(t_vs hosts, double timeout) override;

private:
    Ping		*_ping;
};
