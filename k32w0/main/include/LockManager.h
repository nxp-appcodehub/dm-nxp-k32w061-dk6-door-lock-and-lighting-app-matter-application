/*
 * Copyright 2023, 2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
#pragma once
 
#include <app/clusters/door-lock-server/door-lock-server.h>
 
class LockManager
{
public:
    enum Action_t
    {
        LOCK_ACTION = 0,
        UNLOCK_ACTION,
 
        INVALID_ACTION
    } Action;
 
    enum LockManagerLockState
    {
        kLockManagerLockState_NotFullyLocked = 0,
        kLockManagerLockState_Locked,
        kLockManagerLockState_Unlocked
    };
 
    enum LockManagerEvent
    {
        kLockManagerEvent_LockStarted = 0,
        kLockManagerEvent_LockComplete,
        kLockManagerEvent_UnlockStarted,
        kLockManagerEvent_UnlockComplete
    };
 
 
    void ExecuteCallback(LockManagerEvent);
 
    typedef void (*LockManagerCallback)(LockManagerEvent);
 
    LockManager();
    ~LockManager() = default;
 
    void Init();
    void SetCallback(LockManagerCallback);
 
    void SetLockState(LockManagerLockState);
    LockManagerLockState GetLockState();
 
private:
    friend LockManager & LockMgr();

    LockManagerCallback lockCallback;
    LockManagerLockState lockState;
 
    static LockManager sInstance;
};
 
inline LockManager & LockMgr()
{
    return LockManager::sInstance;
}
 
