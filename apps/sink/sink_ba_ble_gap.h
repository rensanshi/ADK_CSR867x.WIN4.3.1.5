/****************************************************************************
Copyright (c) 2014 - 2016 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3

FILE NAME
    sink_ba_ble_gap.h

DESCRIPTION
    BA BLE GAP functionality
*/

#ifndef _SINK_BA_BLE_GAP_H_
#define _SINK_BA_BLE_GAP_H_

#include "sink_ble_gap.h"
#include "sink_ble_advertising.h"

#include <connection.h>
#include <csrtypes.h>

/* Advertising TX parameters for fast and slow advertising. */
#define ADV_INTERVAL_MIN_FAST   0x0020
#define ADV_INTERVAL_MAX_FAST   0x0020
#define ADV_INTERVAL_MIN_SLOW   0x0800
#define ADV_INTERVAL_MAX_SLOW   0x0800

/*******************************************************************************
NAME
    gapBaStartScanning
    
DESCRIPTION
    Start scanning for BA devices.
    
PARAMETERS
    None
    
RETURNS
    TRUE if the scanning was started. FALSE otherwise.
*/
#ifdef ENABLE_BROADCAST_AUDIO
bool gapBaStartScanning(void);
#else
#define gapBaStartScanning() (FALSE)
#endif

/*******************************************************************************
NAME
    gapBaStopScanning
    
DESCRIPTION
    Stop scanning for BA devices.
    
PARAMETERS
    None
    
RETURNS
    TRUE if the scanning was started. FALSE otherwise.
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaStopScanning(void);
#else
#define gapBaStopScanning() ((void)(0))
#endif

/*******************************************************************************
NAME
    gapBaTriggerAdvertising
    
DESCRIPTION
    Trigger actual advertising of data
    
PARAMETERS
    None
    
RETURNS
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaTriggerAdvertising(void);
#else
#define gapBaTriggerAdvertising() ((void)(0))
#endif

/*******************************************************************************
NAME
    gapBaStartAdvertising
    
DESCRIPTION
    Start advertising BA adverts.
    
PARAMETERS
    None
    
RETURNS
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
bool gapBaStartAdvertising(void);
#else
#define gapBaStartAdvertising() (FALSE)
#endif

/*******************************************************************************
NAME
    gapBaStartAssociation
    
DESCRIPTION
    Interface to start broadcast association
    
PARAMETERS
    None
    
RETURNS
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaStartAssociation(void);
#else
#define gapBaStartAssociation() ((void)(0))
#endif

/*******************************************************************************
NAME
    gapBaStopAssociation
    
DESCRIPTION
    Interface to stop broadcast association
    
PARAMETERS
    None
    
RETURNS
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaStopAssociation(void);
#else
#define gapBaStopAssociation() ((void)(0))
#endif

/*******************************************************************************
NAME
    gapBaStartAssociationTimer
    
DESCRIPTION
    Starts the timer for association.
    
PARAMETERS
    None
    
RETURNS
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaStartAssociationTimer(void);
#else
#define gapBaStartAssociationTimer() ((void)(0))
#endif

/*******************************************************************************
NAME
    gapBaStopAssociationTimer
    
DESCRIPTION
    Stops the timer for association.
    
PARAMETERS
    None
    
RETURNS
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaStopAssociationTimer(void);
#else
#define gapBaStopAssociationTimer() ((void)(0))
#endif

/*******************************************************************************
NAME
    gapBaRestartAssociationTimer
    
DESCRIPTION
    restart the timer for association.
    
PARAMETERS
    None
    
RETURNS
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaRestartAssociationTimer(void);
#else
#define gapBaRestartAssociationTimer() ((void)(0))
#endif

/*******************************************************************************
NAME
    gapBaSetAssociationInProgress
    
DESCRIPTION
    Utility function to set the association progress flag
    
PARAMETERS
    None
    
RETURNS
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaSetAssociationInProgress(bool assoc_in_progress);
#else
#define gapBaSetAssociationInProgress(assoc_in_progress) ((void)(0))
#endif

/*******************************************************************************
NAME
    gapBaGetAssociationInProgress
    
DESCRIPTION
    Utility function to set the association progress flag
    
PARAMETERS
    None
    
RETURNS
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
bool gapBaGetAssociationInProgress(void);
#else
#define gapBaGetAssociationInProgress() (FALSE)
#endif

/*******************************************************************************
NAME    
    gapBaSetupAdData
    
DESCRIPTION
    Function to setup the connectable BA BLE Advertising data for the device.
    
PARAMETERS
    size_local_name Length of the local name buffer.
    local_name      Buffer containing the local name.
    mode            Mode
    
RETURN
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaSetupAdData(uint16 size_local_name, const uint8 *local_name, adv_discoverable_mode_t mode, ble_gap_read_name_t reason);
#else
#define gapBaSetupAdData(size_local_name, local_name, mode, reason) ((void)(0))
#endif

/*******************************************************************************
NAME    
    gapBaSetBroadcastToAdvert
    
DESCRIPTION
    Utility function to set the broadcaster advertising (non-conn) IV
    
PARAMETERS
    requires_advertising Boolean to set it TRUE or FALSE
    
RETURN
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaSetBroadcastToAdvert(bool requires_advertising);
#else
#define gapBaSetBroadcastToAdvert(requires_advertising) ((void)(0))
#endif

/*******************************************************************************
NAME    
    gapBaRequiresBroadcastToAdvert
    
DESCRIPTION
    Utility function to check if broadcaster needs to advert (non-conn) IV
    
PARAMETERS
    None
    
RETURN
    TRUE if broadcaster needs to advert, else FALSE
*/
#ifdef ENABLE_BROADCAST_AUDIO
bool gapBaRequiresBroadcastToAdvert(void);
#else
#define gapBaRequiresBroadcastToAdvert() (FALSE)
#endif

/*******************************************************************************
NAME    
    gapBaSetBroadcastToScan
    
DESCRIPTION
    Utility function to set the broadcast system to scan
    
PARAMETERS
    requires_scanning Boolean to set it TRUE or FALSE
    
RETURN
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaSetBroadcastToScan(bool requires_scanning);
#else
#define gapBaSetBroadcastToScan(requires_scanning) ((void)(0))
#endif

/*******************************************************************************
NAME    
    gapBaRequiresBroadcastToScan
    
DESCRIPTION
    Utility function to check if broadcaster needs to scan (non-conn) IV
    
PARAMETERS
    None
    
RETURN
    TRUE if broadcaster needs to scan, else FALSE
*/
#ifdef ENABLE_BROADCAST_AUDIO
bool gapBaRequiresBroadcastToScan(void);
#else
#define gapBaRequiresBroadcastToScan() (FALSE)
#endif

/*******************************************************************************
NAME    
    gapBaStartBroadcast
    
DESCRIPTION
    This function triggers either advertising variant IV or scanning for one
    
PARAMETERS
    None
    
RETURN
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaStartBroadcast(void);
#else
#define gapBaStartBroadcast() ((void)(0))
#endif

/*******************************************************************************
NAME    
    gapBaStopBroadcast
    
DESCRIPTION
    This function stops either advertising variant IV or scanning for one
    
PARAMETERS
    None
    
RETURN
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaStopBroadcast(void);
#else
#define gapBaStopBroadcast() ((void)(0))
#endif

/*******************************************************************************
NAME    
    gapBaActionCancelAssociation
    
DESCRIPTION
    This function acts on association timeout/cancellation, which state to move and what actions to take
    
PARAMETERS
    None
    
RETURN
    None
*/
#ifdef ENABLE_BROADCAST_AUDIO
void gapBaActionCancelAssociation(void);
#else
#define gapBaActionCancelAssociation() ((void)(0))
#endif

#endif /* _SINK_BLE_GAP_H_ */
