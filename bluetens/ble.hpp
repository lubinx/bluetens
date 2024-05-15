#ifndef __BLUETENSQ_BT_HPP
#define __BLUETENSQ_BT_HPP

#include <ultracore/nvm.h>
#include <bluetooth/gap.tlv.hpp>
#include <bluetooth/sig/gap.h>
#include <uc++/stream.hpp>
#include <endian.h>

#include <rw.soc.hpp>
#include <rw.serial.hpp>
#include <rw.battery.hpp>
using namespace rwSoC;

#include "config.h"
#include "fstab.h"

    extern Bluetooth::BD_addr_t const *BDAddr;

    class TTensPeripheral: public TPeripheral
    {
        typedef TPeripheral inherited;

    public:
        TTensPeripheral() :
            TPeripheral(AdNameBuf, DISCOVER_MODE_GENERAL, CONNECT_MODE_UNDIRECTED),
            Shell(this)
        {
            if (0 != NVM_get(NVM_AD_NAME_ID, AdNameBuf, NVM_AD_NAME_SIZE))
                strncpy(AdNameBuf, PROJECT_NAME, NVM_AD_NAME_SIZE);

            RegisterService(&Shell);
        }

        TSerialPortService Shell;

    protected:
        /*
        virtual void GAP_OnReady(void) override
        {
            inherited::GAP_OnReady();
            ADV_Start();
        }
        */

        virtual void CLI_OnDisconnect(void *evt) override
        {
            inherited::CLI_OnDisconnect(evt);
            ADV_Start();
        }

        virtual void ADV_GetAdvData(TMemStream &adv) override
        {
            inherited::ADV_GetAdvData(adv);

            adv.WriteValue<uint8_t>(3); // size
            adv.WriteValue<uint8_t>(ADV_TYPE_16_BIT_UUID);
            adv.WriteValue<uint16_t>(SERIAL_SERVICE);
        }

        virtual void ADV_GetScanResponseData(TMemStream &scanrsp) override
        {
            scanrsp.WriteValue<uint8_t>(0);

            scanrsp.WriteValue<uint8_t>(ADV_TYPE_MANU_SPECIFIC_DATA);
            // tag of UltraCreation protocol, take manufactory data'id 2 bytes
            scanrsp.WriteValue<uint16_t>(htons(ULTRACREATION_AD2));
            // this project version
            scanrsp.WriteValue<uint16_t>(htons(PROJECT_VERSION));
            // device id
            scanrsp.Write(&FBDAddr, sizeof(FBDAddr));
            // device name
            scanrsp.Write(PROJECT_ID, sizeof(PROJECT_ID));

            uint8_t Size = scanrsp.Position();
            scanrsp.Seek(0, SEEK_SET);
            scanrsp.WriteValue<uint8_t>(Size - 1);
            scanrsp.Seek(Size, SEEK_SET);
        }

    private:
        char AdNameBuf[NVM_AD_NAME_SIZE];
    };

    extern TTensPeripheral *BLE;

#endif
