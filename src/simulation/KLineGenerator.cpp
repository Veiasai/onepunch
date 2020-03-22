#include "KLineGenerator.h"

namespace sail { namespace onepunch { namespace simulator {

void KLineGenerator::poll(int num) {
    for (; num > 0; num--) {
        double price = normal_dist(mt);
        k_line_data.open_price = price;
		k_line_data.high_price = price + 5;
		k_line_data.low_price = price - 5;
		k_line_data.close_price = price;
        k_line_data.volume = 5;
        g_KlineHash[instrumentId].PushData(k_line_data);
    }
}

}}}