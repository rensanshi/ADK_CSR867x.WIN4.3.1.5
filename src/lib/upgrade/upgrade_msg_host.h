/****************************************************************************
Copyright (c) 2004 - 2015 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3

FILE NAME
    upgrade_msg_host.h

DESCRIPTION
    Definition of upgrade protocol messages sent between host and device.

*/
#ifndef UPGRADE_MSG_HOST_H_
#define UPGRADE_MSG_HOST_H_

#include <csrtypes.h>

#ifndef UPGRADE_HOST_MSG_BASE
#define UPGRADE_HOST_MSG_BASE 0x200
#endif

/* Sent by host
   UPGRADE_HOST_START_REQ
   UPGRADE_HOST_DATA
   UPGRADE_HOST_ABORT_REQ
   UPGRADE_HOST_PROGRESS_REQ - also to be removed? TODO
   UPGRADE_HOST_TRANSFER_COMPLETE_RES
   UPGRADE_HOST_IN_PROGRESS_RES
   UPGRADE_HOST_COMMIT_CFM
   UPGRADE_HOST_SYNC_REQ
   UPGRADE_HOST_SYNC_AFTER_REBOOT_REQ
   UPGRADE_HOST_VERSION_REQ
   UPGRADE_HOST_VARIANT_REQ
 */

/* Sent by device
   UPGRADE_HOST_START_CFM
   UPGRADE_HOST_DATA_BYTES_REQ
   UPGRADE_HOST_SUSPEND_IND
   UPGRADE_HOST_RESUME_IND
   UPGRADE_HOST_ABORT_CFM
   UPGRADE_HOST_PROGRESS_CFM - it is going to be removed TODO
   UPGRADE_HOST_TRANSFER_COMPLETE_IND
   UPGRADE_HOST_IN_PROGRESS_IND
   UPGRADE_HOST_COMMIT_REQ
   UPGRADE_HOST_ERRORWARN_IND
   UPGRADE_HOST_COMPLETE_IND
   UPGRADE_HOST_SYNC_CFM
   UPGRADE_HOST_VERSION_CFM
   UPGRADE_HOST_VARIANT_CFM
 */

typedef enum {
    UPGRADE_HOST_START_REQ = 1 + UPGRADE_HOST_MSG_BASE,
    UPGRADE_HOST_START_CFM,
    UPGRADE_HOST_DATA_BYTES_REQ,
    UPGRADE_HOST_DATA,
    UPGRADE_HOST_SUSPEND_IND,
    UPGRADE_HOST_RESUME_IND,
    UPGRADE_HOST_ABORT_REQ,
    UPGRADE_HOST_ABORT_CFM,
    UPGRADE_HOST_PROGRESS_REQ,
    UPGRADE_HOST_PROGRESS_CFM,
    UPGRADE_HOST_TRANSFER_COMPLETE_IND,
    UPGRADE_HOST_TRANSFER_COMPLETE_RES,
    UPGRADE_HOST_IN_PROGRESS_IND,
    UPGRADE_HOST_IN_PROGRESS_RES,
    UPGRADE_HOST_COMMIT_REQ,
    UPGRADE_HOST_COMMIT_CFM,
    UPGRADE_HOST_ERRORWARN_IND, /* _RES below */
    UPGRADE_HOST_COMPLETE_IND,
    UPGRADE_HOST_SYNC_REQ,
    UPGRADE_HOST_SYNC_CFM,

    UPGRADE_HOST_START_DATA_REQ,
    UPGRADE_HOST_IS_CSR_VALID_DONE_REQ,
    UPGRADE_HOST_IS_CSR_VALID_DONE_CFM,
    UPGRADE_HOST_SYNC_AFTER_REBOOT_REQ,

    UPGRADE_HOST_VERSION_REQ,
    UPGRADE_HOST_VERSION_CFM,
    UPGRADE_HOST_VARIANT_REQ,
    UPGRADE_HOST_VARIANT_CFM,

    UPGRADE_HOST_ERASE_SQIF_REQ,
    UPGRADE_HOST_ERASE_SQIF_CFM,

    UPGRADE_HOST_ERRORWARN_RES
} UpgradeMsgHost;

typedef enum {
    UPGRADE_HOST_SUCCESS = 0,
    UPGRADE_HOST_OEM_VALIDATION_SUCCESS,

    UPGRADE_HOST_ERROR_INTERNAL_ERROR_DEPRECATED = 0x10,
    UPGRADE_HOST_ERROR_UNKNOWN_ID,
    UPGRADE_HOST_ERROR_BAD_LENGTH_DEPRECATED,
    UPGRADE_HOST_ERROR_WRONG_VARIANT,
    UPGRADE_HOST_ERROR_WRONG_PARTITION_NUMBER,

    UPGRADE_HOST_ERROR_PARTITION_SIZE_MISMATCH,
    UPGRADE_HOST_ERROR_PARTITION_TYPE_NOT_FOUND_DEPRECATED,
    UPGRADE_HOST_ERROR_PARTITION_OPEN_FAILED,
    UPGRADE_HOST_ERROR_PARTITION_WRITE_FAILED_DEPRECATED,
    UPGRADE_HOST_ERROR_PARTITION_CLOSE_FAILED_DEPRECATED,

    UPGRADE_HOST_ERROR_SFS_VALIDATION_FAILED,
    UPGRADE_HOST_ERROR_OEM_VALIDATION_FAILED_DEPRECATED,
    UPGRADE_HOST_ERROR_UPDATE_FAILED,
    UPGRADE_HOST_ERROR_APP_NOT_READY,

    UPGRADE_HOST_ERROR_LOADER_ERROR,
    UPGRADE_HOST_ERROR_UNEXPECTED_LOADER_MSG,
    UPGRADE_HOST_ERROR_MISSING_LOADER_MSG,

    UPGRADE_HOST_ERROR_BATTERY_LOW,
    UPGRADE_HOST_ERROR_INVALID_SYNC_ID,
    UPGRADE_HOST_ERROR_IN_ERROR_STATE,
    UPGRADE_HOST_ERROR_NO_MEMORY,
    UPGRADE_HOST_ERROR_SQIF_ERASE,
    UPGRADE_HOST_ERROR_SQIF_COPY,
    UPGRADE_HOST_ERROR_AUDIO_SQIF_COPY,

    /* The remaining errors are grouped, each section starting at a fixed
     * offset */
    UPGRADE_HOST_ERROR_BAD_LENGTH_PARTITION_PARSE = 0x30,
    UPGRADE_HOST_ERROR_BAD_LENGTH_TOO_SHORT,
    UPGRADE_HOST_ERROR_BAD_LENGTH_UPGRADE_HEADER,
    UPGRADE_HOST_ERROR_BAD_LENGTH_PARTITION_HEADER,
    UPGRADE_HOST_ERROR_BAD_LENGTH_SIGNATURE,
    UPGRADE_HOST_ERROR_BAD_LENGTH_DATAHDR_RESUME,

    UPGRADE_HOST_ERROR_OEM_VALIDATION_FAILED_HEADERS = 0x38,
    UPGRADE_HOST_ERROR_OEM_VALIDATION_FAILED_UPGRADE_HEADER,
    UPGRADE_HOST_ERROR_OEM_VALIDATION_FAILED_PARTITION_HEADER1,
    UPGRADE_HOST_ERROR_OEM_VALIDATION_FAILED_PARTITION_HEADER2,
    UPGRADE_HOST_ERROR_OEM_VALIDATION_FAILED_PARTITION_DATA,
    UPGRADE_HOST_ERROR_OEM_VALIDATION_FAILED_FOOTER,
    UPGRADE_HOST_ERROR_OEM_VALIDATION_FAILED_MEMORY,

    UPGRADE_HOST_ERROR_PARTITION_CLOSE_FAILED = 0x40,
    UPGRADE_HOST_ERROR_PARTITION_CLOSE_FAILED_HEADER,
    /*! When sent, the error indicates that an upgrade could not be completed 
     * due to concerns about space in Persistent Store.  No other upgrade
     * activities will be possible until the device restarts.
     * This error requires a UPGRADE_HOST_ERRORWARN_RES response (following
     * which the library will cause a restart, if the VM application permits)
     */
    UPGRADE_HOST_ERROR_PARTITION_CLOSE_FAILED_PS_SPACE,

    UPGRADE_HOST_ERROR_PARTITION_TYPE_NOT_MATCHING = 0x48,
    UPGRADE_HOST_ERROR_PARTITION_TYPE_TWO_DFU,

    UPGRADE_HOST_ERROR_PARTITION_WRITE_FAILED_HEADER = 0x50,
    UPGRADE_HOST_ERROR_PARTITION_WRITE_FAILED_DATA,

    UPGRADE_HOST_ERROR_FILE_TOO_SMALL = 0x58,
    UPGRADE_HOST_ERROR_FILE_TOO_BIG,

    UPGRADE_HOST_ERROR_INTERNAL_ERROR_1 = 0x65, /* 101 - Human readable decimal*/
    UPGRADE_HOST_ERROR_INTERNAL_ERROR_2,
    UPGRADE_HOST_ERROR_INTERNAL_ERROR_3,
    UPGRADE_HOST_ERROR_INTERNAL_ERROR_4,
    UPGRADE_HOST_ERROR_INTERNAL_ERROR_5,
    UPGRADE_HOST_ERROR_INTERNAL_ERROR_6,
    UPGRADE_HOST_ERROR_INTERNAL_ERROR_7,

    UPGRADE_HOST_WARN_APP_CONFIG_VERSION_INCOMPATIBLE = 0x80,
    UPGRADE_HOST_WARN_SYNC_ID_IS_DIFFERENT
} UpgradeHostErrorCode;

typedef enum {
    UPGRADE_HOSTACTION_REJECT = 1,
    UPGRADE_HOSTACTION_ACCEPT = 0,
    UPGRADE_HOSTACTION_NO = 1,
    UPGRADE_HOSTACTION_YES = 0
} UpgradeHostActionCode;

#if 0
typedef uint16 UPGRADE_HOST_START_REQ_T;
typedef uint16 UPGRADE_HOST_SUSPEND_IND_T;
typedef uint16 UPGRADE_HOST_RESUME_IND_T;
typedef uint16 UPGRADE_HOST_ABORT_REQ_T;
typedef uint16 UPGRADE_HOST_ABORT_CFM_T;
typedef uint16 UPGRADE_HOST_PROGRESS_REQ_T;
typedef uint16 UPGRADE_HOST_PROGRESS_CFM_T;
typedef uint16 UPGRADE_HOST_TRANSFER_COMPLETE_IND_T;
typedef uint16 UPGRADE_HOST_IN_PROGRESS_IND_T;
typedef uint16 UPGRADE_HOST_COMMIT_REQ_T;
typedef uint16 UPGRADE_HOST_COMPLETE_IND_T;
typedef uint16 UPGRADE_HOST_IS_CSR_VALID_DONE_REQ_T;
typedef uint16 UPGRADE_HOST_SYNC_AFTER_REBOOT_REQ_T;
typedef uint16 UPGRADE_HOST_VERSION_REQ_T;
typedef uint16 UPGRADE_HOST_VARIANT_REQ_T;
#endif

typedef struct {
    uint8 status;
    uint16 batteryLevel;
} UPGRADE_HOST_START_CFM_T;

#define UPGRADE_HOST_START_CFM_BYTE_SIZE 3

typedef struct {
    uint32 numBytes;
    uint32 startOffset;
} UPGRADE_HOST_DATA_BYTES_REQ_T;

#define UPGRADE_HOST_DATA_BYTES_REQ_BYTE_SIZE 8

typedef struct {
    uint16 length;
    uint16 moreData;
    uint16 data[1];
} UPGRADE_HOST_DATA_T;


typedef struct {
    uint16 action;
} UPGRADE_HOST_GENERIC_ACTION_T;

typedef UPGRADE_HOST_GENERIC_ACTION_T UPGRADE_HOST_TRANSFER_COMPLETE_RES_T;
typedef UPGRADE_HOST_GENERIC_ACTION_T UPGRADE_HOST_IN_PROGRESS_RES_T;
typedef UPGRADE_HOST_GENERIC_ACTION_T UPGRADE_HOST_COMMIT_CFM_T;
typedef UPGRADE_HOST_GENERIC_ACTION_T UPGRADE_HOST_ERASE_SQIF_CFM_T;

typedef struct {
    uint16 errorCode;
} UPGRADE_HOST_ERRORWARN_IND_T;

#define UPGRADE_HOST_ERRORWARN_IND_BYTE_SIZE 2

/*! Message used to respond to an UPGRADE_HOST_ERRORWARN_IND message.
 *
 * This is not required for every error/warning, but would not be harmful
 * if sent.
 *
 * See documentation for individual error codes
 */
typedef struct {
    uint16 errorCode;
} UPGRADE_HOST_ERRORWARN_RES_T;

#define UPGRADE_HOST_ERRORWARN_RES_BYTE_SIZE 2

typedef struct {
    uint32 inProgressId;
} UPGRADE_HOST_SYNC_REQ_T;

typedef struct {
    uint8 upgradeState;
    uint32 inProgressId;
    uint8 version;
} UPGRADE_HOST_SYNC_CFM_T;

#define UPGRADE_HOST_SYNC_CFM_BYTE_SIZE 6

typedef struct {
    uint16 backOffTime;
} UPGRADE_HOST_IS_CSR_VALID_DONE_CFM_T;

#define UPGRADE_HOST_IS_CSR_VALID_DONE_CFM_BYTE_SIZE 2

/*!
    Definition of the UPGRADE_HOST_VERSION_CFM message.

    Sent by the device to the host in response to the UPGRADE_HOST_VERSION_REQ
    message.
 */
typedef struct {
    /*! Current Major version of the software on the device. */
    uint16 upgrade_version_major;
    /*! Current Minor version of the software on the device. */
    uint16 upgrade_version_minor;
    /*! Current PS Config version of the device. */
    uint16 ps_config_version;
} UPGRADE_HOST_VERSION_CFM_T;

/*! Number of payload bytes in a UPGRADE_VERSION_CFM protocol message */
#define UPGRADE_HOST_VERSION_CFM_BYTE_SIZE 6

/*! Size of a device variant field, in UPGRADE_HOST_VARIANT_CFM_T message */
#define DEVICE_VARIANT_FIELD_SIZE 8
/*!
    Definition of the UPGRADE_HOST_VARIANT_CFM message.
    Sent by the device to the host in response to the UPGRADE_HOST_VARIANT_REQ
    message.
 */
typedef struct {
    /*! Variant of the device, for which an upgrade file must be matched, by
     * the DEVICE VARIANT field in the upgrade file header. */
    uint8 variant[DEVICE_VARIANT_FIELD_SIZE];
} UPGRADE_HOST_VARIANT_CFM_T;

/*! Number of payload bytes in an UPGRADE_VARIANT_CFM protocol message */
#define UPGRADE_HOST_VARIANT_CFM_BYTE_SIZE 8

#endif /* UPGRADE_MSG_HOST_H_ */
