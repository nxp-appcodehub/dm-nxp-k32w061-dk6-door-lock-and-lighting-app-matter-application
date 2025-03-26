/*
 * Copyright 2023, 2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "LockManager.h"
 
#pragma GCC optimize ("O0")
 
//----------------------------------------------------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------------------------------------------------
 
//----------------------------------------------------------------------------------------------------------------------
// Variables
//----------------------------------------------------------------------------------------------------------------------
 
LockManager LockManager::sInstance;
 
//----------------------------------------------------------------------------------------------------------------------
// Public
//----------------------------------------------------------------------------------------------------------------------
 
enum Action_t
    {
        LOCK_ACTION = 0,
        UNLOCK_ACTION,
 
        INVALID_ACTION
    } Action;
 
LockManager::LockManager()
{
    lockCallback = nullptr;
}
 
void LockManager::Init()
{
    lockState = kLockManagerLockState_Unlocked;
}
 
void LockManager::SetCallback(LockManagerCallback callback)
{
    lockCallback = callback;
}
 
void LockManager::SetLockState(LockManagerLockState state)
{
    if (lockState == state)
    {
        return;
    }
 
    lockState = state;
 
    switch (state)
    {
        case kLockManagerLockState_Locked:
        {
            ExecuteCallback(LockManager::kLockManagerEvent_LockStarted);
            ExecuteCallback(LockManager::kLockManagerEvent_LockComplete);
            break;
        }
 
        case kLockManagerLockState_Unlocked:
        {
            ExecuteCallback(LockManager::kLockManagerEvent_UnlockStarted);
            ExecuteCallback(LockManager::kLockManagerEvent_UnlockComplete);
            break;
        }
 
        default:
            break;
    }
}
 
LockManager::LockManagerLockState LockManager::GetLockState()
{
    return lockState;
}
 
//----------------------------------------------------------------------------------------------------------------------
// Private
//----------------------------------------------------------------------------------------------------------------------
 
void LockManager::ExecuteCallback(LockManagerEvent event)
{
    if (nullptr != lockCallback)
    {
        lockCallback(event);
    }
}
