typedef unsigned char u8;
typedef unsigned int u32;
typedef u32 usize;

extern char __bss[], __bss_end[], __stack_top[];

void *memset(void *buf, char val, usize cnt)
{
    u8 *start = (u8 *)buf;

    while (cnt > 0)
    {
        *start = val;
        start++;
        cnt--;
    }

    return buf;
}

void kernel_main(void)
{
    memset(__bss, 0, (usize)__bss_end - (usize)__bss);

    while (1)
    {
    }
}

__attribute__((section(".text.boot")))
__attribute__((naked)) void
boot(void)
{
    __asm__ __volatile__(
        "mv sp, %[stack_top]\n"
        "j kernel_main\n"
        :
        : [stack_top] "r"(__stack_top));
}
