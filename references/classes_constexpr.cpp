#include <stdio.h>

#include <libdragon.h>

class Test
{
private:
    uint8_t mBlah;
public:
    explicit Test(uint8_t blah)
        : mBlah(blah)
	{}
    uint8_t GetBlah() const { return mBlah; }
};

constexpr int fib(int n)
{
    return n <= 1 ? n : fib(n - 1) + fib(n - 2);
}

int main(void)
{
    console_init();

    debug_init_usblog();
    console_set_debug(true);

    if constexpr (fib(15) > 5)
    {
        const Test c(static_cast<uint8_t>(6));
        printf("From class %d via constexpr\n", c.GetBlah());
    }
    else
    {
        printf("Hello world!\n");
    }

    while(1) 
    {
    }
}
