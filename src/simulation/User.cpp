#include "User.h"
#include <mutex>
#include <iostream>

namespace sail { namespace onepunch { namespace simulator {

std::mutex UserDataMutex;

bool User::buy(const std::string &instrumentId, long vol, double price)
{
    // 加锁
    std::lock_guard<std::mutex> lk(UserDataMutex);

    if (userinfo.Available < vol * price)
        return false;

    userinfo.Available -= price * vol;

    if (userinfo.OpenVolume.find(instrumentId) == userinfo.OpenVolume.end())
        userinfo.OpenVolume[instrumentId] = vol;
    else
        userinfo.OpenVolume[instrumentId] += vol;

#ifdef DEBUG
    std::cout << userinfo.UserID << " buy " << instrumentId << std::endl
              << "at price: " << price << " vol: " << vol << std::endl;

    showInfo();

#endif

    return true;
}
bool User::sell(const std::string &instrumentId, long vol, double price)
{
    // 加锁
    std::lock_guard<std::mutex> lk(UserDataMutex);

    if (userinfo.OpenVolume.find(instrumentId) == userinfo.OpenVolume.end())
        return false;

    if (userinfo.OpenVolume[instrumentId] < vol)
        return false;

    userinfo.Available += price * vol;
    userinfo.OpenVolume[instrumentId] -= vol;

#ifdef DEBUG
    std::cout << userinfo.UserID << " sell " << instrumentId << std::endl
              << "at price: " << price << " vol: " << vol << std::endl;

    showInfo();
#endif
    return true;
}

void User::showInfo()
{
    std::cout << "UserId: " << userinfo.UserID << std::endl;
    for (auto x : userinfo.OpenVolume)
        std::cout << x.first << " " << x.second << std::endl;
    std::cout << "Available: " << userinfo.Available << std::endl;
    //   << "CloseProfit: " << userinfo.CloseProfit << std::endl;
}

}}} // namespace simulator
