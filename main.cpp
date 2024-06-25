#include <uart.h>
#include "app.hpp"

int main (void)
{
#if defined(CONSOLE_TXD) || defined(CONSOLE_RXD)
    UART_configure(CONSOLE_DEV, CONSOLE_TXD, CONSOLE_RXD);
#endif
    __stdout_fd = UART_createfd(CONSOLE_DEV, 115200, UART_PARITY_NONE, UART_STOP_BITS_ONE);

    App = new TApplication();
    App->Run();
}
