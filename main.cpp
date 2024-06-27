#include <uart.h>
#include "app.hpp"

#include <ultracore/log.h>
#include <nvds.h>
#include <flash.h>
#include <hash/crc_ccitt.h>

int main (void)
{
#if defined(CONSOLE_TXD) || defined(CONSOLE_RXD)
    UART_configure(CONSOLE_DEV, CONSOLE_TXD, CONSOLE_RXD);
#endif
    __stdout_fd = UART_createfd(CONSOLE_DEV, 115200, UART_PARITY_NONE, UART_STOP_BITS_ONE);

    /*
    printf("system configuration page:\n");
    LOG_dump_buffer((void *)FLASH_CONFIG_PAGE_ADDR, 64, FLASH_CONFIG_PAGE_ADDR, 32);

    printf("flash information page: 0x%02x\n", CRC_CCITT_hash((void *)0x210B0000, 2048));
    LOG_dump_buffer((void *)0x210B0000, 2048, 0x210B0000, 32);
    */

    App = new TApplication();
    App->Run();
}
