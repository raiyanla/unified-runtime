// Copyright (C) $(year) Intel Corporation
// SPDX-License-Identifier: MIT

#include <uur/fixtures.h>

using urUSMAllocInfoTest =
    uur::urUSMDeviceAllocTestWithParam<ur_mem_alloc_info_t>;

UUR_TEST_SUITE_P(urUSMAllocInfoTest,
                 ::testing::Values(UR_MEM_ALLOC_INFO_ALLOC_TYPE,
                                   UR_MEM_ALLOC_INFO_ALLOC_BASE_PTR,
                                   UR_MEM_ALLOC_INFO_ALLOC_SIZE,
                                   UR_MEM_ALLOC_INFO_ALLOC_DEVICE),
                 uur::deviceTestWithParamPrinter<ur_mem_alloc_info_t>);

TEST_P(urUSMAllocInfoTest, Success) {
    size_t size = 0;
    auto alloc_info = getParam();
    ASSERT_SUCCESS(
        urMemGetMemAllocInfo(context, ptr, alloc_info, 0, nullptr, &size));
    ASSERT_NE(size, 0);
    std::vector<uint8_t> info_data(size);
    ASSERT_SUCCESS(urMemGetMemAllocInfo(context, ptr, alloc_info, size,
                                        info_data.data(), nullptr));
}

using urMemGetMemAllocInfoTest = uur::urUSMDeviceAllocTest;
UUR_INSTANTIATE_DEVICE_TEST_SUITE_P(urMemGetMemAllocInfoTest);

TEST_P(urMemGetMemAllocInfoTest, InvalidNullHandleContext) {
    ur_usm_type_t USMType;
    ASSERT_EQ_RESULT(
        UR_RESULT_ERROR_INVALID_NULL_HANDLE,
        urMemGetMemAllocInfo(nullptr, ptr, UR_MEM_ALLOC_INFO_ALLOC_TYPE,
                             sizeof(ur_usm_type_t), &USMType, nullptr));
}

TEST_P(urMemGetMemAllocInfoTest, InvalidNullPointerMem) {
    ur_usm_type_t USMType;
    ASSERT_EQ_RESULT(
        UR_RESULT_ERROR_INVALID_NULL_POINTER,
        urMemGetMemAllocInfo(context, nullptr, UR_MEM_ALLOC_INFO_ALLOC_TYPE,
                             sizeof(ur_usm_type_t), &USMType, nullptr));
}

TEST_P(urMemGetMemAllocInfoTest, InvalidEnumeration) {
    ur_usm_type_t USMType;
    ASSERT_EQ_RESULT(
        UR_RESULT_ERROR_INVALID_ENUMERATION,
        urMemGetMemAllocInfo(context, ptr, UR_MEM_ALLOC_INFO_FORCE_UINT32,
                             sizeof(ur_usm_type_t), &USMType, nullptr));
}
