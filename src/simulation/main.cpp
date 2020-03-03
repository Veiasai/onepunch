#include "MarketSimulator.h"
#include "Strategy.h"
#include <thread>

using namespace simulator;
using namespace std;

int main()
{
    string instrumentId = "i2005";
    Market one = Market(instrumentId);

    BaseStrategy bs1 = BaseStrategy("zwq");
    OptionIndex optionIndex = OptionIndex();
    optionIndex.addInstrument(instrumentId);

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
            TradeInfo ti = one.getTradeInfo();
            optionIndex.updateInstrument(instrumentId, ti);

            bs1.onUnderlyingChanged(instrumentId, optionIndex);

            lastTime = thisTime;

            count++;
        }
    }

    one.stop();

    t1.join();

    return 0;
}