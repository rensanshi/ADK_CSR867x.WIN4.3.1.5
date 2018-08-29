/****************************************************************************
Copyright (c) 2017 - 2018 Qualcomm Technologies International, Ltd. 
Part of ADK_CSR867x.WIN 4.3

FILE NAME
    dm_crypto_api_handler.h        

DESCRIPTION
    This file contains the prototypes of functions for handling the confirmation messages from the 
    Bluestack regarding cryptography.

NOTES

*/

#include "connection.h"

/*******************************************************************************
 *                      Message handling function prototypes                    *
 *******************************************************************************/
 
 /*!
    @brief Handle the Bluestack response to a request for the generation of a public/private encryption key pair using ECC.

    @param cfm      The confirmation message from Bluestack.

    @return None.
*/
 void connectionHandleGeneratePublicPrivateKeyCfm(DM_CRYPTO_GENERATE_PUBLIC_PRIVATE_KEY_CFM_T *cfm);
 
  /*!
    @brief Handle the Bluestack response to a request for the generation of a shared secret encryption key from a public/private key pair using ECHD.

    @param cfm      The confirmation message from Bluestack.

    @return None.
*/
 void connectionHandleGenerateSharedSecretKey(DM_CRYPTO_GENERATE_SHARED_SECRET_KEY_CFM_T * cfm);
 
 /*!
    @brief Handle the Bluestack response to a request for the encryption of a 128-bit block of data using a 128-bit encryption key using AES.

    @param cfm      The confirmation message from Bluestack.

    @return None.
*/
 void connectionHandleAesEncrypt(DM_CRYPTO_ENCRYPT_CFM_T * cfm);
 
 /*!
    @brief Handle the Bluestack response to a request for the encryption of a data block of arbitrary length using SHA256.

    @param cfm      The confirmation message from Bluestack.

    @return None.
*/
 void connectionHandleHash(DM_CRYPTO_HASH_CFM_T * cfm);
