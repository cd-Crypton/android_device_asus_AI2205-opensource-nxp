/*
 **
 ** Copyright 2020, The Android Open Source Project
 **
 ** Licensed under the Apache License, Version 2.0 (the "License");
 ** you may not use this file except in compliance with the License.
 ** You may obtain a copy of the License at
 **
 **     http://www.apache.org/licenses/LICENSE-2.0
 **
 ** Unless required by applicable law or agreed to in writing, software
 ** distributed under the License is distributed on an "AS IS" BASIS,
 ** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 ** See the License for the specific language governing permissions and
 ** limitations under the License.
 */
/******************************************************************************
 **
 ** The original Work has been changed by NXP.
 **
 ** Licensed under the Apache License, Version 2.0 (the "License");
 ** you may not use this file except in compliance with the License.
 ** You may obtain a copy of the License at
 **
 ** http://www.apache.org/licenses/LICENSE-2.0
 **
 ** Unless required by applicable law or agreed to in writing, software
 ** distributed under the License is distributed on an "AS IS" BASIS,
 ** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 ** See the License for the specific language governing permissions and
 ** limitations under the License.
 **
 ** Copyright 2022 NXP
 **
 *********************************************************************************/
#if defined OMAPI_TRANSPORT
#pragma once

#include <aidl/android/se/omapi/BnSecureElementListener.h>
#include <aidl/android/se/omapi/ISecureElementChannel.h>
#include <aidl/android/se/omapi/ISecureElementListener.h>
#include <aidl/android/se/omapi/ISecureElementReader.h>
#include <aidl/android/se/omapi/ISecureElementService.h>
#include <aidl/android/se/omapi/ISecureElementSession.h>
//#include <aidl/android/se/omapi/SecureElementErrorCode.h>
#include <android/binder_manager.h>

#include <map>

#include "ITransport.h"
#include <AppletConnection.h>
#include <IntervalTimer.h>
#include <memory>
#include <vector>

#include <SBAccessController.h>

namespace keymint::javacard {
using std::shared_ptr;
using std::vector;

/**
 * OmapiTransport is derived from ITransport. This class gets the OMAPI service binder instance and uses IPC to
 * communicate with OMAPI service. OMAPI inturn communicates with hardware via ISecureElement.
 */
class OmapiTransport : public ITransport {

public:
  OmapiTransport(const std::vector<uint8_t> &mAppletAID)
      : ITransport(mAppletAID), mSelectableAid(mAppletAID) {
#ifdef NXP_EXTNS
    mDeathRecipient = ::ndk::ScopedAIBinder_DeathRecipient(
        AIBinder_DeathRecipient_new(BinderDiedCallback));
#endif
  }

    /**
     * Gets the binder instance of ISEService, gets the reader corresponding to secure element, establishes a session
     * and opens a basic channel.
     */
    bool openConnection() override;
    /**
     * Transmists the data over the opened basic channel and receives the data back.
     */
    bool sendData(const vector<uint8_t>& inData, vector<uint8_t>& output) override;
    /**
     * Closes the connection.
     */
    bool closeConnection() override;
    /**
     * Returns the state of the connection status. Returns true if the connection is active, false if connection is
     * broken.
     */
    bool isConnected() override;
    void closeSession();
private:
    //AppletConnection mAppletConnection;
    SBAccessController mSBAccessController;
    IntervalTimer mTimer;
    std::vector<uint8_t> mSelectableAid;
    std::shared_ptr<aidl::android::se::omapi::ISecureElementService> omapiSeService = nullptr;
    std::shared_ptr<aidl::android::se::omapi::ISecureElementReader> eSEReader = nullptr;
    std::shared_ptr<aidl::android::se::omapi::ISecureElementSession> session = nullptr;
    std::shared_ptr<aidl::android::se::omapi::ISecureElementChannel> channel = nullptr;
    std::map<std::string, std::shared_ptr<aidl::android::se::omapi::ISecureElementReader>>
            mVSReaders = {};
    std::string const ESE_READER_PREFIX = "eSE";
    constexpr static const char omapiServiceName[] =
            "android.se.omapi.ISecureElementService/default";

    bool initialize();
    bool internalTransmitApdu(
            std::shared_ptr<aidl::android::se::omapi::ISecureElementReader> reader,
            std::vector<uint8_t> apdu, std::vector<uint8_t>& transmitResponse);

#ifdef NXP_EXTNS
    ::ndk::ScopedAIBinder_DeathRecipient mDeathRecipient;

    static void BinderDiedCallback(void *cookie);
    bool internalProtectedTransmitApdu(
            std::shared_ptr<aidl::android::se::omapi::ISecureElementReader> reader,
            std::vector<uint8_t> apdu, std::vector<uint8_t>& transmitResponse);
    void prepareErrorRepsponse(std::vector<uint8_t>& resp);
#endif
#ifdef INTERVAL_TIMER
    inline uint16_t getApduStatus(std::vector<uint8_t> &inputData) {
      // Last two bytes are the status SW0SW1
      uint8_t SW0 = inputData.at(inputData.size() - 2);
      uint8_t SW1 = inputData.at(inputData.size() - 1);
      return (SW0 << 8 | SW1);
    }
#endif
};
}  // namespace keymint::javacard
#endif