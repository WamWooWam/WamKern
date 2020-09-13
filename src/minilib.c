// set of functions to make the C++ compiler not shit it's pants

void *memset(void *mem, int character, long count) {
    for (long i = 0; i < count; i++) {
        ((unsigned char*)mem)[i] = (unsigned char)character;
    }

    return mem;
}