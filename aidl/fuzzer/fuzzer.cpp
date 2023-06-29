/*
 * Copyright (c) 2024 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include <fuzzbinder/libbinder_ndk_driver.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "BootControl.h"
#include "BootControl.cpp"

using aidl::android::hardware::boot::BootControl;

std::shared_ptr<BootControl> service = ndk::SharedRefBase::make<BootControl>();

extern "C" int LLVMFuzzerInitialize(int* argc, char*** argv) {
    service = ndk::SharedRefBase::make<BootControl>();
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if  (service == nullptr ) {
        return -1;
    }

    android::fuzzService(service->asBinder().get(), FuzzedDataProvider(data, size));

    return 0;
}