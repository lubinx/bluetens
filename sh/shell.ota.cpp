#include <cctype>
#include <cstdlib>

#include <adc.h>
#include <flash.h>
#include <hash/crc_ccitt.h>

#include "app.hpp"
#include "shell.hpp"
#include "fstab.h"

int SHELL_ota(struct UCSH_env *env)
{
    App->Stop();

    struct OTA_packet
    {
        uint16_t Offset;
        CRC_CCITT_t CRC;
        uint8_t Payload[16];
    };

    struct OTA_packet packet;
    uint32_t size;
    CRC_CCITT_t crc;

    int ota_fd;
    int retval;
    {
        char *param;
        char *p;

        param = CMD_paramvalue_byname("s", env->argc, env->argv);
        if (! param)
            return EINVAL;
        size = std::strtoul(param, &p, 10);
        if (0 == size && 'x' == std::tolower(*p))
            size = std::strtoul(param, NULL, 16);

        param = CMD_paramvalue_byname("c", env->argc, env->argv);
        if (! param)
            return EINVAL;
        crc  = (uint16_t)std::strtoul(param, &p, 10);
        if (0 == crc && 'x' == std::tolower(*p))
            crc = (uint16_t)std::strtoul(param, NULL, 16);
    }

    /// @NOTE: unmount before FLASH_otafd()
    //      due to OTA will destroy filesystem
    //      also freeup FLASH_PAGE sizeof memory
    FLASH_unmountfs();

    ota_fd = FLASH_otafd(size); // open("ota.bin", O_RDWR | O_CREAT | O_TRUNC);
    if (-1 == ota_fd)
    {
        /// @insufficient memory is only case, that we can't do anything about it
        NVIC_SystemReset();
        while (1);
    }
    // response "ok"
    UCSH_error_handle(env, 0);

    /// @ADC breaking the OTA, it detected low battery when flashing on QN9020 board
    /*
#if PROJECT_VERSION < VERSION_INFO(3, 1, 0) && ! defined(NO_DET_BATTERY)
    extern ADC_attr_t batt;
    ADC_stop_convert(&batt);
#endif
    */

#if PROJECT_VERSION >= VERSION_INFO(3, 1, 0)
    // BG22 & QN908x new firmware may > 65535 bytes
    uint32_t step;

    if (size > 0xFFFF)
    {
        size = ((size + sizeof(packet.Payload) - 1) & ~(sizeof(packet.Payload) - 1)) / sizeof(packet.Payload);
        step = 1;
    }
    else
        step = sizeof(packet.Payload);

    for (unsigned offset = 0; offset < size; offset += step)
#else
    for (unsigned offset = 0; offset < size; offset += sizeof(packet.Payload))
#endif
    {
        if (sizeof(packet) != readbuf(env->fd, &packet, sizeof(packet)) || offset != packet.Offset)
            goto ota_payload_error;

        // packet crc
        uint16_t packet_crc = CRC_CCITT_hash(packet.Payload, sizeof(packet.Payload));
        if (packet_crc != packet.CRC)
            goto ota_crc_error;

        // ota writing
        if (sizeof(packet.Payload) != writebuf(ota_fd, packet.Payload, sizeof(packet.Payload)))
            goto ota_payload_error;

        App->UpdateLastActivity();
        FILE_downloading();
    }
    FILE_download_complete();

    if (FLASH_ota_final(ota_fd, crc))
    {
        /// @successful sometimes need to reset to finish UPGRADE
        NVIC_SystemReset();
    }
    else
        goto ota_crc_error;

    if (false)
    {
ota_crc_error:
        retval = EOTA_CRC;
    }
    if (false)
    {
ota_payload_error:
        retval = EOTA_PAYLOAD;
    }

    close(ota_fd);
    FLASH_mountfs();

    /*
#if PROJECT_VERSION < VERSION_INFO(3, 1, 0) && ! defined(NO_DET_BATTERY)
    ADC_start_convert(&batt, App);
#endif
    */
    return retval;
}
