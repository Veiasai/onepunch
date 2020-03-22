#pragma once

#include "Parameter.h"

namespace sail { namespace onepunch { namespace simulator {

class User
{
private:
    UserInfo userinfo;

public:
    explicit User(const std::string &userid) : userinfo(UserInfo(userid)){};

    bool buy(const std::string &instrumentId, long vol, double price);
    bool sell(const std::string &instrumentId, long vol, double price);
    void showInfo();
};

}}} // namespace simulator
