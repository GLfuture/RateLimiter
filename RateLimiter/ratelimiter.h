#ifndef GALAY_RATELIMITER_H
#define GALAY_RATELIMITER_H

#include "countsemaphore.h"

namespace galay{
    namespace Util{
        class GY_RateLimiter{
        public:
            //rate --> bytes/s , capacity --> box's capacity , deliveryIntervalMs --> during time to create token (ms)
            //最大可以应对(rate + capity) 的突发流量

            //deliveryInteralMs越大，每一次delivery的token越多，但是token更新频率低，性能提升，及时性下降
            //;反之，每一次delivery的token越多，但是token更新频率低，性能降低，及时性下降
            GY_RateLimiter(uint64_t rate, uint64_t capacity,uint64_t deliveryInteralMs);
            void Start();
            void Stop();
            bool Pass(uint64_t flow);
            ~GY_RateLimiter();
        private:
            void ProduceToken();
        private:
            uint64_t m_deliveryInteralMs;
            uint64_t m_rate;
            bool m_runing;
            CountSemaphore::uptr m_semaphore;
            std::unique_ptr<std::thread> m_deliveryThread;
        };
    }
}


#endif