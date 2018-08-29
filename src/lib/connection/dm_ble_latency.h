/****************************************************************************
Copyright (c) 2017 - 2018 Qualcomm Technologies International, Ltd. 
Part of ADK_CSR867x.WIN 4.3

FILE NAME
    dm_ble_latency.h      

DESCRIPTION
    This file contains the implementation of configuration of latency control.

NOTES

*/

/****************************************************************************
NAME    
    connectionHandleDmUlpEnableSlaveLatencyCfm

DESCRIPTION
    Handle the DM_ULP_ENABLE_ZERO_SLAVE_LATENCY_CFM_T message from Bluestack and pass it
    on to the appliction that initialised the CL.

RETURNS
    void
*/
void connectionHandleDmUlpEnableSlaveLatencyCfm( 
        const DM_ULP_ENABLE_ZERO_SLAVE_LATENCY_CFM_T *ind
        );

