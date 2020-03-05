#pragma once
#include "OptionIndex.h"
#include "User.h"

namespace simulator
{
class Strategy
{
public:
    explicit Strategy(const std::string &userid) : user(userid){};

    virtual void onUnderlyingChanged(const std::string &instrumentId, const OptionIndex &optionIndex) = 0;

protected:
    User user;

    inline bool buyOption(const std::string &instrumentId, long vol, double price) { return user.buy(instrumentId, vol, price); }
    inline bool sellOption(const std::string &instrumentId, long vol, double price) { return user.sell(instrumentId, vol, price); };
};

class BaseStrategy : Strategy
{
public:
    explicit BaseStrategy(const std::string &userid) : Strategy(userid){};

    void onUnderlyingChanged(const std::string &instrumentId, const OptionIndex &optionIndex) override;
};

} // namespace simulator
