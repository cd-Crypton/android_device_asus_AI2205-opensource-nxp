 /*
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
 ** Copyright 2020-2022 NXP
 **
 */
#ifndef __ESE_TRANSPORT_CONFIG__
#define __ESE_TRANSPORT_CONFIG__
#include <vector>

namespace se_transport {

#define MAX_GET_SERVICE_RETRY 50
#define FIFTY_MILLISEC  1000*50
#define SESSION_TIMEOUT 3*1000 // 3 secs
#define LOGICAL_CH_NOT_SUPPORTED_SW1 0x68
#define LOGICAL_CH_NOT_SUPPORTED_SW2 0x81
#define APDU_INS_OFFSET 1      // INS offset in command APDU
// Helper method to dump vector contents
static bool debug_omapi = true;
#define LOGD_OMAPI(x) \
  if(debug_omapi) { \
    LOG(INFO) <<"("<<__FUNCTION__ <<")"<<" "<<x; \
  }

#define LOGE_OMAPI(x) \
    LOG(INFO) <<"("<<__FUNCTION__ <<")"<<" "<<x;
std::ostream& operator<<(std::ostream& os, const std::vector<uint8_t>& vec);

} // namespace se_transport
#endif /* __ESE_TRANSPORT_CONFIG__ */
