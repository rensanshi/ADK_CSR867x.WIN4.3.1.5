/****************************************************************************
Copyright (c) 2015 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3

FILE NAME
    upgrade_fw_if_priv.h
    
DESCRIPTION
    Definition of FW I/F state datatype.
*/

#ifndef UPGRADE_FW_IF_PRIV_H_
#define UPGRADE_FW_IF_PRIV_H_


typedef struct
{
    /*
     * Used by CONFIG_HYDRACORE and CONFIG_QCC300X to store a platform
     * specific validation context.
     *
     * It needs to be defined in this shared header so that the size and
     * layout of UpgradeFWIFCtx is consistent in both the general upgrade
     * code and the platform specifc bits.
     */
    void *vctx;

#ifdef UPGRADE_USE_FW_STUBS
    uint8 *lastPartitionData;
    uint16 lastPartitionDataLen;
    uint16 openPartitionNum;
#else
    uint16 partitionNum;
#endif
} UpgradeFWIFCtx;

#endif /* UPGRADE_FW_IF_PRIV_H_ */
