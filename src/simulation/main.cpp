#include "MarketSimulator.h"
#include <thread>

using namespace simulator;
using namespace std;

int main()
{
    string instrumentId = "i2005";
    Market one = Market(instrumentId);

    thread t1(bind(&Market::run, &one));

    // 每三秒去一次信息，取得五次信息就结束程序
    int lastTime = time(0);
    int thisTime;
    const int elapsed = 3; // sec

    int count = 0;
    while (true)
    {
        thisTime = time(0);
        if (thisTime - lastTime > elapsed)
        {
            one.getTradeInfo();

            lastTime = thisTime;

            count++;
            if (count == 5)
                break;
        }
    }

    one.stop();

    t1.join();

    return 0;
}