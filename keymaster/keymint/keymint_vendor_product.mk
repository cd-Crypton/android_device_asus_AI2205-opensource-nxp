# Build Keymaster open source vendor modules
ESE_VENDOR_KEYMINT += android.hardware.security.keymint-service.strongbox
ESE_VENDOR_KEYMINT += hal_uuid_map_config.xml

ifeq ($(strip $(ENABLE_ESE_KEYMINT_SPLIT_MANIFEST)),true)
ESE_VENDOR_KEYMINT += android.hardware.security.keymint-service.strongbox.xml
ESE_VENDOR_KEYMINT += android.hardware.security.sharedsecret-service.strongbox.xml
endif

ifeq ($(strip $(TARGET_USES_ESE_KEYMINT)),true)
PRODUCT_PACKAGES += $(ESE_VENDOR_KEYMINT)
endif
