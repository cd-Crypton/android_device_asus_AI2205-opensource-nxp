# Enable build support for NFC open source vendor modules
ifeq ($(call is-board-platform-in-list, kalama),true)
TARGET_USES_NQ_NFC := true
endif

NQ_VENDOR_NFC += android.hardware.nfc_snxxx@1.2-service
NQ_VENDOR_NFC += vendor.nxp.nxpnfc@2.0-impl
NQ_VENDOR_NFC += vendor.nxp.nxpnfc@2.0-service
NQ_VENDOR_NFC += nfc_nci_nxp_snxxx
NQ_VENDOR_NFC += android.hardware.secure_element_snxxx@1.2-service
NQ_VENDOR_NFC += init.asus.nfc.CN.rc

ifeq ($(strip $(TARGET_USES_NQ_NFC)),true)
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/com.nxp.mifare.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/com.nxp.mifare.xml \
    frameworks/native/data/etc/com.android.nfc_extras.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/com.android.nfc_extras.xml \
    frameworks/native/data/etc/android.hardware.nfc.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.nfc.xml \
    frameworks/native/data/etc/android.hardware.nfc.hce.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.nfc.hce.xml \
    frameworks/native/data/etc/android.hardware.nfc.hcef.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.nfc.hcef.xml \
    frameworks/native/data/etc/android.hardware.nfc.uicc.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.nfc.uicc.xml

PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.nfc.ese.xml:$(TARGET_COPY_OUT_ODM)/etc/permissions/sku_CN/android.hardware.nfc.ese.xml \
    frameworks/native/data/etc/android.hardware.se.omapi.ese.xml:$(TARGET_COPY_OUT_ODM)/etc/permissions/sku_CN/android.hardware.se.omapi.ese.xml

PRODUCT_PACKAGES += $(NQ_VENDOR_NFC)
endif


