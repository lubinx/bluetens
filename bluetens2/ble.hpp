#ifndef __BLUETENS2_BT_HPP
#define __BLUETENS2_BT_HPP

#include <bluetooth/uuid.h>
#include <bluetooth/gap.tlv.hpp>
#include <uc++/stream.hpp>

#include <bluetooth/gatt.service.serialp.hpp>

#include "config.h"
#include BLE_INCLUDE_HEADER

class TTensPeripheral :public Bluetooth::BLE_NAMESPACE::TPeripheral
    {
        typedef Bluetooth::BLE_NAMESPACE::TPeripheral inherited;

    public:
        TTensPeripheral():
            TPeripheral(PROJECT_NAME),
            Shell()
        {
        }

        Bluetooth::TSerialPortService Shell;

    protected:
        /*
        virtual void GAP_OnReady(void) override
        {
            inherited::GAP_OnReady();
            // ADV_Start();
        }
        */

        virtual void CLI_OnDisconnect(uint16_t peer_id, void *arg) override
        {
            inherited::CLI_OnDisconnect(peer_id, arg);
            ADV_Start();
        }

        virtual void ADV_GetAdvData(Bluetooth::TAdvStream &adv) override
        {
            inherited::ADV_GetAdvData(adv);
            adv.PushBack<uint16_t>(ADV_TYPE_16_BIT_UUID, SERIAL_PORT_SERVICE);
        }

        virtual void ADV_GetScanResponseData(Bluetooth::TAdvStream &scanrsp) override
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

            uint8_t Size = (uint8_t)scanrsp.Position();
            scanrsp.Seek(0, SEEK_SET);
            scanrsp.WriteValue<uint8_t>(Size - 1);
            scanrsp.Seek(Size, SEEK_SET);
        }
    };
    extern TTensPeripheral *BLE;

#endif
