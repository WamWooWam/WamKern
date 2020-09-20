#include "lib/random.h"
namespace WamKern {
uint64_t Random::seed = 0xa170d4c9f256ce3f;
uint64_t Random::state[4] = {
    0xa170d4c9f256ce3f,
    0xd62dda09171872f6,
    0x893f854f6e739f1b,
    0x1f38fc71d27ed08b, 
};

}  // namespace WamKern