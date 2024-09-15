ifeq ($(TARGET_FWK_SUPPORTS_FULL_VALUEADDS), true)
TARGET_USES_QSSI_NQ_NFC := true

NQ_SYSTEM_NFC := NfcNci
NQ_SYSTEM_NFC += libnfc-nci
NQ_SYSTEM_NFC += libnfc_nci_jni
NQ_SYSTEM_NFC += com.nxp.nfc
NQ_SYSTEM_NFC += com.nxp.nfc.xml
NQ_SYSTEM_NFC += com.gsma.services.nfc
NQ_SYSTEM_NFC += Tag
NQ_SYSTEM_NFC += com.android.nfc_extras
NQ_SYSTEM_NFC += vendor.nxp.nxpese@1.0

ifeq ($(TARGET_BUILD_VARIANT), userdebug)
NQ_SYSTEM_NFC += nfctest
NQ_SYSTEM_NFC += ncitest
NQ_SYSTEM_NFC += pnx
endif

ifeq ($(strip $(TARGET_USES_QSSI_NQ_NFC)),true)
PRODUCT_PACKAGES += $(NQ_SYSTEM_NFC)
PRODUCT_BOOT_JARS += com.nxp.nfc
endif
endif
