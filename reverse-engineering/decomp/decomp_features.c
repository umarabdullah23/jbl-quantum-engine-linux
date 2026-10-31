// ==== setBatteryLevel @ 180151fd0 ====

void setBatteryLevel(undefined4 param_1)

{
                    /* 0x151fd0  192  setBatteryLevel */
  DAT_180225ca0 = param_1;
  return;
}



// ==== GetBatteryInfo @ 180152f20 ====

void GetBatteryInfo(void)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined1 local_18 [8];
  longlong *local_10;
  
                    /* 0x152f20  29  GetBatteryInfo */
  uVar6 = FUN_1801501a0();
  puVar7 = (undefined8 *)FUN_180150c50(uVar6,local_18,DAT_180233f3c,DAT_180233f38);
  uVar6 = *puVar7;
  plVar4 = (longlong *)puVar7[1];
  *puVar7 = 0;
  puVar7[1] = 0;
  if (local_10 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_10 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*local_10)(local_10);
      LOCK();
      piVar2 = (int *)((longlong)local_10 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_10 + 8))(local_10);
      }
    }
  }
  FUN_18000b2d0(uVar6);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}



// ==== GetSidetoneLevel @ 180152ff0 ====

void GetSidetoneLevel(void)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined1 local_18 [8];
  longlong *local_10;
  
                    /* 0x152ff0  81  GetSidetoneLevel */
  uVar6 = FUN_1801501a0();
  puVar7 = (undefined8 *)FUN_180150c50(uVar6,local_18,DAT_180233f3c,DAT_180233f38);
  uVar6 = *puVar7;
  plVar4 = (longlong *)puVar7[1];
  *puVar7 = 0;
  puVar7[1] = 0;
  if (local_10 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_10 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*local_10)(local_10);
      LOCK();
      piVar2 = (int *)((longlong)local_10 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_10 + 8))(local_10);
      }
    }
  }
  FUN_18000c470(uVar6);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}



// ==== SetSidetoneLevel @ 1801530c0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetSidetoneLevel(int param_1)

{
  int *piVar1;
  longlong *plVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong lVar6;
  undefined8 uVar7;
  longlong *plVar8;
  longlong *plVar9;
  undefined1 auStack_68 [32];
  undefined8 local_48;
  longlong *plStack_40;
  undefined8 local_38;
  undefined8 uStack_30;
  ulonglong local_28;
  
                    /* 0x1530c0  159  SetSidetoneLevel */
  local_28 = DAT_180225100 ^ (ulonglong)auStack_68;
  uVar7 = FUN_1801501a0();
  plVar8 = (longlong *)FUN_180150c50(uVar7,&local_48,DAT_180233f3c,DAT_180233f38);
  lVar4 = *plVar8;
  plVar5 = (longlong *)plVar8[1];
  *plVar8 = 0;
  plVar8[1] = 0;
  if (plStack_40 != (longlong *)0x0) {
    LOCK();
    plVar8 = plStack_40 + 1;
    lVar6 = *plVar8;
    *(int *)plVar8 = (int)*plVar8 + -1;
    UNLOCK();
    if ((int)lVar6 == 1) {
      (**(code **)*plStack_40)(plStack_40);
      LOCK();
      piVar1 = (int *)((longlong)plStack_40 + 0xc);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plStack_40 + 8))(plStack_40);
      }
    }
  }
  local_48._4_4_ = local_48._4_4_ & 0xffff;
  local_38 = 0;
  local_48 = (longlong *)CONCAT44(local_48._4_4_,0x33);
  uStack_30 = 0;
  plVar9 = (longlong *)FUN_180185d80(0x58);
  plVar8 = (longlong *)(lVar4 + 0x50);
  plVar2 = plVar9 + 3;
  *(undefined4 *)(plVar9 + 1) = 1;
  *(undefined4 *)((longlong)plVar9 + 0xc) = 1;
  *plVar9 = (longlong)std::_Ref_count_obj2<BaseApiScheduleData>::vftable;
  *plVar2 = 0;
  plVar9[4] = 0;
  plVar9[5] = 0;
  plVar9[6] = 0xf;
  *(undefined1 *)plVar2 = 0;
  *(undefined2 *)((longlong)plVar9 + 0x3c) = 0;
  *(undefined4 *)(plVar9 + 7) = 0x6f;
  plVar9[8] = 0;
  plVar9[9] = 0;
  plVar9[10] = 0;
  *(undefined4 *)(plVar9 + 2) = 0;
  if (plVar2 != plVar8) {
    if (0xf < *(ulonglong *)(lVar4 + 0x68)) {
      plVar8 = (longlong *)*plVar8;
    }
    FUN_180017830(plVar2,plVar8,*(undefined8 *)(lVar4 + 0x60));
  }
  local_48._0_6_ = CONCAT24(*(undefined2 *)(lVar4 + 0x28),(undefined4)local_48);
  *(undefined4 *)(plVar9 + 7) = (undefined4)local_48;
  *(uint *)((longlong)plVar9 + 0x3c) = local_48._4_4_;
  plVar9[8] = (longlong)(double)param_1;
  *(undefined4 *)(plVar9 + 9) = (undefined4)local_38;
  *(undefined4 *)((longlong)plVar9 + 0x4c) = local_38._4_4_;
  *(undefined4 *)(plVar9 + 10) = (undefined4)uStack_30;
  *(undefined4 *)((longlong)plVar9 + 0x54) = uStack_30._4_4_;
  LOCK();
  *(int *)(plVar9 + 1) = (int)plVar9[1] + 1;
  UNLOCK();
  local_48 = plVar9 + 2;
  plStack_40 = plVar9;
  FUN_180009bf0(lVar4,&local_48);
  LOCK();
  plVar8 = plVar9 + 1;
  lVar4 = *plVar8;
  *(int *)plVar8 = (int)*plVar8 + -1;
  UNLOCK();
  if ((int)lVar4 == 1) {
    (**(code **)*plVar9)(plVar9);
    LOCK();
    piVar1 = (int *)((longlong)plVar9 + 0xc);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 == 1) {
      (**(code **)(*plVar9 + 8))(plVar9);
    }
  }
  if (plVar5 != (longlong *)0x0) {
    LOCK();
    plVar8 = plVar5 + 1;
    lVar4 = *plVar8;
    *(int *)plVar8 = (int)*plVar8 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plVar5)(plVar5);
      LOCK();
      piVar1 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetAncSettings @ 180155a00 ====

void GetAncSettings(void)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined1 local_18 [8];
  longlong *local_10;
  
                    /* 0x155a00  21  GetAncSettings */
  uVar6 = FUN_1801501a0();
  puVar7 = (undefined8 *)FUN_180150c50(uVar6,local_18,DAT_180233f3c,DAT_180233f38);
  uVar6 = *puVar7;
  plVar4 = (longlong *)puVar7[1];
  *puVar7 = 0;
  puVar7[1] = 0;
  if (local_10 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_10 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*local_10)(local_10);
      LOCK();
      piVar2 = (int *)((longlong)local_10 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_10 + 8))(local_10);
      }
    }
  }
  FUN_18000dcf0(uVar6);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}



// ==== GetGameChatBalanceSettings @ 180155ad0 ====

void GetGameChatBalanceSettings(void)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined1 local_18 [8];
  longlong *local_10;
  
                    /* 0x155ad0  55  GetGameChatBalanceSettings */
  uVar6 = FUN_1801501a0();
  puVar7 = (undefined8 *)FUN_180150c50(uVar6,local_18,DAT_180233f3c,DAT_180233f38);
  uVar6 = *puVar7;
  plVar4 = (longlong *)puVar7[1];
  *puVar7 = 0;
  puVar7[1] = 0;
  if (local_10 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_10 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*local_10)(local_10);
      LOCK();
      piVar2 = (int *)((longlong)local_10 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_10 + 8))(local_10);
      }
    }
  }
  FUN_18000e020(uVar6);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}



// ==== GetGameChatBalanceSettingsResult @ 180155ba0 ====

void GetGameChatBalanceSettingsResult(undefined4 *param_1)

{
  longlong lVar1;
  
                    /* 0x155ba0  57  GetGameChatBalanceSettingsResult */
  lVar1 = FUN_1801501a0();
  *param_1 = *(undefined4 *)(lVar1 + 0x44);
  lVar1 = FUN_1801501a0();
  param_1[1] = *(undefined4 *)(lVar1 + 0x48);
  lVar1 = FUN_1801501a0();
  param_1[2] = *(undefined4 *)(lVar1 + 0x50);
  return;
}



// ==== SetGameChatBalanceSettings @ 180155bd0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetGameChatBalanceSettings(undefined4 *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  int iVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  longlong lVar8;
  char *pcVar9;
  undefined8 uVar10;
  undefined8 ***pppuVar11;
  undefined1 auStack_498 [32];
  undefined1 local_478 [8];
  longlong *local_470;
  undefined8 ***local_468;
  undefined8 uStack_460;
  undefined8 local_458;
  ulonglong uStack_450;
  undefined4 local_448;
  undefined4 local_444;
  undefined8 local_440;
  undefined8 uStack_438;
  undefined1 local_430 [1032];
  ulonglong local_28;
  
                    /* 0x155bd0  145  SetGameChatBalanceSettings */
  local_28 = DAT_180225100 ^ (ulonglong)auStack_498;
  uVar6 = FUN_1801501a0();
  puVar7 = (undefined8 *)FUN_180150c50(uVar6,local_478,DAT_180233f3c,DAT_180233f38);
  plVar3 = local_470;
  uVar6 = *puVar7;
  plVar5 = (longlong *)puVar7[1];
  *puVar7 = 0;
  puVar7[1] = 0;
  if (local_470 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_470 + 1;
    lVar8 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar8 == 1) {
      (**(code **)*local_470)(local_470);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0xc);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 == 1) {
        (**(code **)(*plVar3 + 8))(plVar3);
      }
    }
  }
  if (param_1[1] + 0x2580 < 0x4b01) {
    if (param_1[2] + 0x2580 < 0x4b01) {
      lVar8 = FUN_1801501a0();
      *(undefined4 *)(lVar8 + 0x44) = *param_1;
      lVar8 = FUN_1801501a0();
      *(undefined4 *)(lVar8 + 0x48) = param_1[1];
      lVar8 = FUN_1801501a0();
      *(undefined4 *)(lVar8 + 0x50) = param_1[2];
      FUN_18000e190(uVar6);
      goto LAB_180155dba;
    }
    local_440 = 0;
    uStack_438 = 0;
    FUN_1801b0190(local_430,0,0x400);
    uVar10 = 0x21;
    pcVar9 = "failure_threshold is out of range";
  }
  else {
    local_440 = 0;
    uStack_438 = 0;
    FUN_1801b0190(local_430,0,0x400);
    uVar10 = 0x23;
    pcVar9 = "effective_threshold is out of range";
  }
  local_448 = 0x1771;
  local_444 = 4;
  local_468 = (undefined8 ***)0x0;
  uStack_460 = 0;
  local_458 = 0;
  uStack_450 = 0;
  FUN_180019380(&local_468,pcVar9,uVar10);
  pppuVar11 = &local_468;
  if (0xf < uStack_450) {
    pppuVar11 = local_468;
  }
  FUN_180001aa0(local_430,0x400,&DAT_1801d8f3c,pppuVar11);
  puVar7 = (undefined8 *)FUN_1800067b0(uVar6,local_478);
  FUN_1800253b0(*puVar7,&local_448);
  if (local_470 != (longlong *)0x0) {
    LOCK();
    plVar3 = local_470 + 1;
    lVar8 = *plVar3;
    *(int *)plVar3 = (int)*plVar3 + -1;
    UNLOCK();
    if ((int)lVar8 == 1) {
      (**(code **)*local_470)(local_470);
      LOCK();
      piVar2 = (int *)((longlong)local_470 + 0xc);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 == 1) {
        (**(code **)(*local_470 + 8))(local_470);
      }
    }
  }
  FUN_180017790(&local_468);
LAB_180155dba:
  if (plVar5 != (longlong *)0x0) {
    LOCK();
    plVar3 = plVar5 + 1;
    lVar8 = *plVar3;
    *(int *)plVar3 = (int)*plVar3 + -1;
    UNLOCK();
    if ((int)lVar8 == 1) {
      (**(code **)*plVar5)(plVar5);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetGameChatMixRatio @ 180155e20 ====

void GetGameChatMixRatio(void)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined1 local_18 [8];
  longlong *local_10;
  
                    /* 0x155e20  59  GetGameChatMixRatio */
  uVar6 = FUN_1801501a0();
  puVar7 = (undefined8 *)FUN_180150c50(uVar6,local_18,DAT_180233f3c,DAT_180233f38);
  uVar6 = *puVar7;
  plVar4 = (longlong *)puVar7[1];
  *puVar7 = 0;
  puVar7[1] = 0;
  if (local_10 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_10 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*local_10)(local_10);
      LOCK();
      piVar2 = (int *)((longlong)local_10 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_10 + 8))(local_10);
      }
    }
  }
  FUN_18000e300(uVar6);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}



// ==== SetGameChatMixRatio @ 180155ef0 ====

void SetGameChatMixRatio(undefined4 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined1 local_18 [8];
  longlong *local_10;
  
                    /* 0x155ef0  147  SetGameChatMixRatio */
  uVar6 = FUN_1801501a0();
  puVar7 = (undefined8 *)FUN_180150c50(uVar6,local_18,DAT_180233f3c,DAT_180233f38);
  uVar6 = *puVar7;
  plVar4 = (longlong *)puVar7[1];
  *puVar7 = 0;
  puVar7[1] = 0;
  if (local_10 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_10 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*local_10)(local_10);
      LOCK();
      piVar2 = (int *)((longlong)local_10 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_10 + 8))(local_10);
      }
    }
  }
  FUN_18000e470(uVar6,param_1);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}



// ==== GetGameMicVolume @ 180155fd0 ====

void GetGameMicVolume(void)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined1 local_18 [8];
  longlong *local_10;
  
                    /* 0x155fd0  61  GetGameMicVolume */
  uVar6 = FUN_1801501a0();
  puVar7 = (undefined8 *)FUN_180150c50(uVar6,local_18,DAT_180233f3c,DAT_180233f38);
  uVar6 = *puVar7;
  plVar4 = (longlong *)puVar7[1];
  *puVar7 = 0;
  puVar7[1] = 0;
  if (local_10 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_10 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*local_10)(local_10);
      LOCK();
      piVar2 = (int *)((longlong)local_10 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_10 + 8))(local_10);
      }
    }
  }
  FUN_18000e5f0(uVar6);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}



// ==== SetGameMicVolume @ 1801560a0 ====

void SetGameMicVolume(undefined4 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined1 local_18 [8];
  longlong *local_10;
  
                    /* 0x1560a0  149  SetGameMicVolume */
  uVar6 = FUN_1801501a0();
  puVar7 = (undefined8 *)FUN_180150c50(uVar6,local_18,DAT_180233f3c,DAT_180233f38);
  uVar6 = *puVar7;
  plVar4 = (longlong *)puVar7[1];
  *puVar7 = 0;
  puVar7[1] = 0;
  if (local_10 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_10 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*local_10)(local_10);
      LOCK();
      piVar2 = (int *)((longlong)local_10 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_10 + 8))(local_10);
      }
    }
  }
  FUN_18000e760(uVar6,param_1);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}



// ==== GetAncSettingsResult @ 180156180 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetAncSettingsResult(undefined4 *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  undefined4 *puVar4;
  longlong lVar5;
  int iVar6;
  undefined8 uVar7;
  undefined8 *puVar8;
  ulonglong uVar9;
  undefined8 ***pppuVar10;
  undefined1 auStack_4e8 [32];
  undefined1 local_4c8 [8];
  longlong *local_4c0;
  undefined8 local_4b8;
  longlong *plStack_4b0;
  undefined4 local_4a8;
  undefined4 local_4a4;
  undefined8 local_4a0;
  undefined4 local_498;
  undefined4 local_494;
  undefined4 local_490;
  undefined4 uStack_48c;
  undefined4 uStack_488;
  undefined4 uStack_484;
  undefined4 local_480;
  undefined4 local_47c;
  undefined4 uStack_478;
  undefined4 local_474;
  undefined4 uStack_470;
  undefined4 local_46c;
  undefined4 uStack_468;
  undefined4 local_464;
  undefined4 uStack_460;
  undefined4 local_45c;
  undefined8 ***local_458;
  undefined8 uStack_450;
  undefined8 local_448;
  ulonglong uStack_440;
  undefined4 local_438;
  undefined4 local_434;
  undefined8 local_430;
  undefined8 uStack_428;
  undefined1 local_420 [1032];
  ulonglong local_18;
  
                    /* 0x156180  23  GetAncSettingsResult */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_4e8;
  uVar7 = FUN_1801501a0();
  iVar6 = FUN_180151380(uVar7,DAT_180233f3c,DAT_180233f38);
  if (iVar6 == -1) {
    local_4b8 = 0;
    plStack_4b0 = (longlong *)0x0;
    uVar7 = FUN_1801501a0();
    FUN_180150c50(uVar7,&local_4b8,DAT_180233f3c,DAT_180233f38);
    local_430 = 0;
    uStack_428 = 0;
    FUN_1801b0190(local_420,0,0x400);
    local_438 = 0x3eb;
    local_434 = 4;
    local_458 = (undefined8 ***)0x0;
    uStack_450 = 0;
    local_448 = 0;
    uStack_440 = 0;
    FUN_180019380(&local_458,"device handler is not exist. device index = -1",0x2e);
    pppuVar10 = &local_458;
    if (0xf < uStack_440) {
      pppuVar10 = local_458;
    }
    FUN_180001aa0(local_420,0x400,&DAT_1801d8f3c,pppuVar10);
    puVar8 = (undefined8 *)FUN_1800067b0(local_4b8,local_4c8);
    FUN_1800253b0(*puVar8,&local_438);
    if (local_4c0 != (longlong *)0x0) {
      LOCK();
      plVar1 = local_4c0 + 1;
      lVar5 = *plVar1;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)lVar5 == 1) {
        (**(code **)*local_4c0)(local_4c0);
        LOCK();
        piVar2 = (int *)((longlong)local_4c0 + 0xc);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 == 1) {
          (**(code **)(*local_4c0 + 8))(local_4c0);
        }
      }
    }
    FUN_180017790(&local_458);
    plVar1 = plStack_4b0;
    if (plStack_4b0 != (longlong *)0x0) {
      LOCK();
      plVar3 = plStack_4b0 + 1;
      lVar5 = *plVar3;
      *(int *)plVar3 = (int)*plVar3 + -1;
      UNLOCK();
      if ((int)lVar5 == 1) {
        (**(code **)*plStack_4b0)(plStack_4b0);
        LOCK();
        piVar2 = (int *)((longlong)plVar1 + 0xc);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 == 1) {
          (**(code **)(*plVar1 + 8))(plVar1);
        }
      }
    }
  }
  else {
    local_4a4 = 0;
    local_494 = 0;
    local_47c = 0;
    uStack_478 = 0;
    local_474 = 0;
    uStack_470 = 0;
    local_46c = 0;
    uStack_468 = 0;
    local_464 = 0;
    uStack_460 = 0;
    local_45c = 0;
    uVar7 = FUN_1800bdc10();
    puVar8 = (undefined8 *)FUN_1800bdcd0(uVar7,local_4c8,iVar6);
    puVar4 = (undefined4 *)*puVar8;
    local_4a0 = *(undefined8 *)(puVar4 + 2);
    local_4a8 = *puVar4;
    local_498 = puVar4[4];
    local_490 = puVar4[6];
    uStack_48c = puVar4[7];
    uStack_488 = puVar4[8];
    uStack_484 = puVar4[9];
    local_480 = puVar4[10];
    FUN_18002c1c0(&uStack_478,puVar4 + 0xc);
    if (local_4c0 != (longlong *)0x0) {
      LOCK();
      plVar1 = local_4c0 + 1;
      lVar5 = *plVar1;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)lVar5 == 1) {
        (**(code **)*local_4c0)(local_4c0);
        LOCK();
        piVar2 = (int *)((longlong)local_4c0 + 0xc);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 == 1) {
          (**(code **)(*local_4c0 + 8))(local_4c0);
        }
      }
    }
    lVar5 = CONCAT44(local_474,uStack_478);
    *param_1 = local_4a8;
    param_1[1] = local_498;
    param_1[2] = local_490;
    param_1[3] = uStack_48c;
    param_1[4] = uStack_488;
    param_1[5] = uStack_484;
    if (lVar5 != 0) {
      uVar9 = CONCAT44(local_464,uStack_468) - lVar5;
      if (0xfff < uVar9) {
        if (0x1f < (lVar5 - *(longlong *)(lVar5 + -8)) - 8U) {
                    /* WARNING: Subroutine does not return */
          FUN_18018f678(*(longlong *)(lVar5 + -8),uVar9 + 0x27);
        }
      }
      thunk_FUN_180190730();
    }
  }
  return;
}



// ==== SetAncSettings @ 180156430 ====

void SetAncSettings(undefined4 *param_1,undefined4 param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined8 *puVar8;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined8 local_28;
  
                    /* 0x156430  121  SetAncSettings */
  uVar7 = FUN_1801501a0();
  puVar8 = (undefined8 *)FUN_180150c50(uVar7,&local_38,DAT_180233f3c,DAT_180233f38);
  uVar7 = *puVar8;
  plVar4 = (longlong *)puVar8[1];
  *puVar8 = 0;
  puVar8[1] = 0;
  plVar5 = (longlong *)CONCAT44(uStack_2c,uStack_30);
  if (plVar5 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar5 + 1;
    lVar6 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar6 == 1) {
      (**(code **)*plVar5)(plVar5);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  local_38 = *param_1;
  uStack_34 = param_1[1];
  uStack_30 = param_1[2];
  uStack_2c = param_1[3];
  local_28 = *(undefined8 *)(param_1 + 4);
  FUN_18000de60(uVar7,&local_38,param_2);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar5 = plVar4 + 1;
    lVar6 = *plVar5;
    *(int *)plVar5 = (int)*plVar5 + -1;
    UNLOCK();
    if ((int)lVar6 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}



// ==== GetStandAloneMicStatus @ 180156c20 ====

void GetStandAloneMicStatus(void)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined1 local_18 [8];
  longlong *local_10;
  
                    /* 0x156c20  85  GetStandAloneMicStatus */
  uVar6 = FUN_1801501a0();
  puVar7 = (undefined8 *)FUN_180150c50(uVar6,local_18,DAT_180233f3c,DAT_180233f38);
  uVar6 = *puVar7;
  plVar4 = (longlong *)puVar7[1];
  *puVar7 = 0;
  puVar7[1] = 0;
  if (local_10 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_10 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*local_10)(local_10);
      LOCK();
      piVar2 = (int *)((longlong)local_10 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_10 + 8))(local_10);
      }
    }
  }
  FUN_180013800(uVar6);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}



// ==== GetStandAloneMicVolume @ 180156cf0 ====

void GetStandAloneMicVolume(void)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined1 local_18 [8];
  longlong *local_10;
  
                    /* 0x156cf0  87  GetStandAloneMicVolume */
  uVar6 = FUN_1801501a0();
  puVar7 = (undefined8 *)FUN_180150c50(uVar6,local_18,DAT_180233f3c,DAT_180233f38);
  uVar6 = *puVar7;
  plVar4 = (longlong *)puVar7[1];
  *puVar7 = 0;
  puVar7[1] = 0;
  if (local_10 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_10 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*local_10)(local_10);
      LOCK();
      piVar2 = (int *)((longlong)local_10 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_10 + 8))(local_10);
      }
    }
  }
  FUN_180013970(uVar6);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}



// ==== SetStandAloneMicStatus @ 180156dc0 ====

void SetStandAloneMicStatus(undefined1 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined1 local_18 [8];
  longlong *local_10;
  
                    /* 0x156dc0  163  SetStandAloneMicStatus */
  uVar6 = FUN_1801501a0();
  puVar7 = (undefined8 *)FUN_180150c50(uVar6,local_18,DAT_180233f3c,DAT_180233f38);
  uVar6 = *puVar7;
  plVar4 = (longlong *)puVar7[1];
  *puVar7 = 0;
  puVar7[1] = 0;
  if (local_10 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_10 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*local_10)(local_10);
      LOCK();
      piVar2 = (int *)((longlong)local_10 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_10 + 8))(local_10);
      }
    }
  }
  FUN_180013ae0(uVar6,param_1);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}



// ==== SetStandAloneMicVolume @ 180156ea0 ====

void SetStandAloneMicVolume(undefined1 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined1 local_18 [8];
  longlong *local_10;
  
                    /* 0x156ea0  165  SetStandAloneMicVolume */
  uVar6 = FUN_1801501a0();
  puVar7 = (undefined8 *)FUN_180150c50(uVar6,local_18,DAT_180233f3c,DAT_180233f38);
  uVar6 = *puVar7;
  plVar4 = (longlong *)puVar7[1];
  *puVar7 = 0;
  puVar7[1] = 0;
  if (local_10 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_10 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*local_10)(local_10);
      LOCK();
      piVar2 = (int *)((longlong)local_10 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_10 + 8))(local_10);
      }
    }
  }
  FUN_180013c60(uVar6,param_1);
  if (plVar4 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar4 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*plVar4)(plVar4);
      LOCK();
      piVar2 = (int *)((longlong)plVar4 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar4 + 8))(plVar4);
      }
    }
  }
  return;
}



// ==== SetBatteryLevelEx @ 1801573f0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SetBatteryLevelEx(ushort param_1,undefined4 param_2)

{
  char cVar1;
  undefined8 *puVar2;
  undefined4 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  undefined8 ***pppuVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 extraout_XMM0_Da;
  undefined4 uVar9;
  undefined1 auStack_e8 [32];
  uint local_c8 [4];
  undefined4 local_b8;
  undefined8 local_b4;
  undefined8 ***local_a8;
  undefined8 uStack_a0;
  undefined8 local_98;
  ulonglong uStack_90;
  undefined8 local_88;
  undefined8 ***local_80;
  undefined8 uStack_78;
  undefined8 local_70;
  ulonglong local_68;
  undefined8 ***local_60;
  undefined8 uStack_58;
  undefined8 local_50;
  ulonglong local_48;
  ulonglong local_38;
  
                    /* 0x1573f0  126  SetBatteryLevelEx */
  local_38 = DAT_180225100 ^ (ulonglong)auStack_e8;
  cVar1 = *(char *)((longlong)DAT_180233f40[1] + 0x19);
  puVar2 = (undefined8 *)DAT_180233f40[1];
  puVar5 = DAT_180233f40;
  while (puVar4 = puVar2, cVar1 == '\0') {
    if (*(int *)(puVar4 + 4) < (int)(uint)param_1) {
      puVar2 = (undefined8 *)puVar4[2];
      puVar4 = puVar5;
    }
    else {
      puVar2 = (undefined8 *)*puVar4;
    }
    cVar1 = *(char *)((longlong)puVar2 + 0x19);
    puVar5 = puVar4;
  }
  uVar8 = (uint)param_1;
  if ((*(char *)((longlong)puVar5 + 0x19) != '\0') || ((int)uVar8 < *(int *)(puVar5 + 4))) {
    puVar5 = DAT_180233f40;
  }
  local_98 = _DAT_1801eacb0;
  uStack_90 = _UNK_1801eacb8;
  local_70 = 0;
  uVar9 = 1;
  local_68 = 0xf;
  local_50 = 0;
  local_48 = 0xf;
  local_88 = 1;
  local_b4 = 0x200;
  uStack_a0 = 0;
  local_a8 = (undefined8 ***)0x0;
  uStack_78 = 0;
  local_80 = (undefined8 ***)0x0;
  uStack_58 = 0;
  local_60 = (undefined8 ***)0x0;
  local_c8[0] = uVar8;
  if (puVar5 == DAT_180233f40) {
    local_b8 = param_2;
    puVar3 = (undefined4 *)FUN_180160300(0,local_c8);
    *puVar3 = param_2;
    *(undefined8 *)(puVar3 + 1) = 0x200;
    uVar7 = 0;
    if ((undefined8 ****)(puVar3 + 4) != &local_a8) {
      pppuVar6 = &local_a8;
      if (0xf < uStack_90) {
        pppuVar6 = local_a8;
      }
      FUN_180017830(puVar3 + 4,pppuVar6,local_98);
      uVar9 = (undefined4)local_88;
      uVar7 = local_88._4_4_;
    }
    puVar3[0xc] = uVar9;
    puVar3[0xd] = uVar7;
  }
  else {
    puVar3 = (undefined4 *)FUN_180160300(0,local_c8);
    local_b8 = *puVar3;
    pppuVar6 = (undefined8 ***)(puVar3 + 4);
    local_b4 = *(undefined8 *)(puVar3 + 1);
    uVar9 = extraout_XMM0_Da;
    if (&local_a8 != (undefined8 ****)pppuVar6) {
      if (0xf < *(ulonglong *)(puVar3 + 10)) {
        pppuVar6 = (undefined8 ***)*pppuVar6;
      }
      uVar9 = FUN_180017830(&local_a8,pppuVar6,*(undefined8 *)(puVar3 + 8));
    }
    pppuVar6 = (undefined8 ***)(puVar3 + 0xe);
    local_88 = *(undefined8 *)(puVar3 + 0xc);
    if (&local_80 != (undefined8 ****)pppuVar6) {
      if (0xf < *(ulonglong *)(puVar3 + 0x14)) {
        pppuVar6 = (undefined8 ***)*pppuVar6;
      }
      uVar9 = FUN_180017830(&local_80,pppuVar6,*(undefined8 *)(puVar3 + 0x12));
    }
    pppuVar6 = (undefined8 ***)(puVar3 + 0x16);
    if (&local_60 != (undefined8 ****)pppuVar6) {
      if (0xf < *(ulonglong *)(puVar3 + 0x1c)) {
        pppuVar6 = (undefined8 ***)*pppuVar6;
      }
      uVar9 = FUN_180017830(&local_60,pppuVar6,*(undefined8 *)(puVar3 + 0x1a));
    }
    local_c8[0] = uVar8;
    local_b8 = param_2;
    puVar3 = (undefined4 *)FUN_180160300(uVar9,local_c8);
    puVar3[1] = (undefined4)local_b4;
    puVar3[2] = local_b4._4_4_;
    *puVar3 = param_2;
    if ((undefined8 ****)(puVar3 + 4) != &local_a8) {
      pppuVar6 = &local_a8;
      if (0xf < uStack_90) {
        pppuVar6 = local_a8;
      }
      FUN_180017830(puVar3 + 4,pppuVar6,local_98);
    }
    puVar3[0xc] = (undefined4)local_88;
    puVar3[0xd] = local_88._4_4_;
  }
  if ((undefined8 ****)(puVar3 + 0xe) != &local_80) {
    pppuVar6 = &local_80;
    if (0xf < local_68) {
      pppuVar6 = local_80;
    }
    FUN_180017830(puVar3 + 0xe,pppuVar6,local_70);
  }
  if ((undefined8 ****)(puVar3 + 0x16) != &local_60) {
    pppuVar6 = &local_60;
    if (0xf < local_48) {
      pppuVar6 = local_60;
    }
    FUN_180017830(puVar3 + 0x16,pppuVar6,local_50);
  }
  FUN_180017790(&local_60);
  FUN_180017790(&local_80);
  FUN_180017790(&local_a8);
  return;
}



// ==== GetBatteryInfoEx @ 18015b830 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetBatteryInfoEx(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15b830  30  GetBatteryInfoEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000b2d0(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetAncSettingsEx @ 18015b8d0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetAncSettingsEx(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15b8d0  22  GetAncSettingsEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000dcf0(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetAncSettingsResultEx @ 18015b970 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetAncSettingsResultEx(undefined2 param_1,undefined4 *param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  ulonglong uVar8;
  undefined1 auStack_98 [32];
  undefined1 local_78 [8];
  longlong *local_70;
  undefined4 local_68;
  undefined4 local_64;
  undefined8 local_60;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  ulonglong local_18;
  
                    /* 0x15b970  24  GetAncSettingsResultEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_98;
  local_64 = 0;
  local_54 = 0;
  local_3c = 0;
  uStack_38 = 0;
  local_34 = 0;
  uStack_30 = 0;
  local_2c = 0;
  uStack_28 = 0;
  local_24 = 0;
  uStack_20 = 0;
  local_1c = 0;
  uVar6 = FUN_1800bdc10();
  puVar7 = (undefined8 *)FUN_1800bdcd0(uVar6,local_78,param_1);
  puVar4 = (undefined4 *)*puVar7;
  local_60 = *(undefined8 *)(puVar4 + 2);
  local_68 = *puVar4;
  local_58 = puVar4[4];
  local_50 = puVar4[6];
  uStack_4c = puVar4[7];
  uStack_48 = puVar4[8];
  uStack_44 = puVar4[9];
  local_40 = puVar4[10];
  FUN_18002c1c0(&uStack_38,puVar4 + 0xc);
  if (local_70 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_70 + 1;
    lVar5 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar5 == 1) {
      (**(code **)*local_70)(local_70);
      LOCK();
      piVar2 = (int *)((longlong)local_70 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*local_70 + 8))(local_70);
      }
    }
  }
  lVar5 = CONCAT44(local_34,uStack_38);
  *param_2 = local_68;
  param_2[1] = local_58;
  param_2[2] = local_50;
  param_2[3] = uStack_4c;
  param_2[4] = uStack_48;
  param_2[5] = uStack_44;
  if (lVar5 != 0) {
    uVar8 = CONCAT44(local_24,uStack_28) - lVar5;
    if (0xfff < uVar8) {
      if (0x1f < (lVar5 - *(longlong *)(lVar5 + -8)) - 8U) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(*(longlong *)(lVar5 + -8),uVar8 + 0x27);
      }
    }
    thunk_FUN_180190730();
  }
  return;
}



// ==== SetAncSettingsEx @ 18015bad0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetAncSettingsEx(undefined2 param_1,undefined4 *param_2,undefined1 param_3)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_68 [32];
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined8 local_38;
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15bad0  122  SetAncSettingsEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_68;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  local_48 = *param_2;
  uStack_44 = param_2[1];
  uStack_40 = param_2[2];
  uStack_3c = param_2[3];
  local_38 = *(undefined8 *)(param_2 + 4);
  FUN_18000de60(local_28,&local_48,param_3);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetSidetoneStateEx @ 18015c980 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetSidetoneStateEx(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15c980  82  GetSidetoneStateEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000c170(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== SetSidetoneStateEx @ 18015ca20 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetSidetoneStateEx(undefined2 param_1,ulonglong param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  undefined8 local_20;
  longlong *plStack_18;
  ulonglong local_10;
  
                    /* 0x15ca20  160  SetSidetoneStateEx */
  local_10 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_20 = 0;
  plStack_18 = (longlong *)0x0;
  local_28 = param_2;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_20,param_1);
  FUN_18000c2e0(local_20,param_2 & 0xff,local_28._4_4_);
  plVar5 = plStack_18;
  if (plStack_18 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_18 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_18)(plStack_18);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== SetFactoryResetEx @ 18015cc10 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetFactoryResetEx(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15cc10  143  SetFactoryResetEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000d020(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetVoicePromptsStatusEx @ 18015ccb0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetVoicePromptsStatusEx(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15ccb0  98  GetVoicePromptsStatusEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000c5e0(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== SetVoicePromptsStatusEx @ 18015cd50 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetVoicePromptsStatusEx(undefined2 param_1,undefined1 param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15cd50  172  SetVoicePromptsStatusEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000c750(local_28,param_2);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetGameChatMixRatioEx @ 18015cdf0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetGameChatMixRatioEx(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15cdf0  60  GetGameChatMixRatioEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000e300(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== SetGameChatMixRatioEx @ 18015ce90 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetGameChatMixRatioEx(undefined2 param_1,undefined4 param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15ce90  148  SetGameChatMixRatioEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000e470(local_28,param_2);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetGameMicVolumeEx @ 18015cf30 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetGameMicVolumeEx(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15cf30  62  GetGameMicVolumeEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000e5f0(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== SetGameMicVolumeEx @ 18015cfd0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetGameMicVolumeEx(undefined2 param_1,undefined4 param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15cfd0  150  SetGameMicVolumeEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000e760(local_28,param_2);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetAdvancedPassthroughStatusEx @ 18015d070 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetAdvancedPassthroughStatusEx(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15d070  16  GetAdvancedPassthroughStatusEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000c8d0(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== SetAdvancedPassthroughStatusEx @ 18015d110 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetAdvancedPassthroughStatusEx(undefined2 param_1,undefined1 param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15d110  119  SetAdvancedPassthroughStatusEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000ca40(local_28,param_2);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetEnvironmentDetectionInfoEx @ 18015d1b0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetEnvironmentDetectionInfoEx(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15d1b0  47  GetEnvironmentDetectionInfoEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000cbc0(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetEnvironmentDetectionInfoResultEx @ 18015d250 ====

void GetEnvironmentDetectionInfoResultEx(undefined2 param_1,undefined4 *param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  longlong lVar8;
  undefined8 uVar9;
  longlong *plVar10;
  undefined1 local_38 [8];
  longlong *local_30;
  
                    /* 0x15d250  48  GetEnvironmentDetectionInfoResultEx */
  uVar9 = FUN_1800bb4d0();
  plVar10 = (longlong *)FUN_1800bb560(uVar9,local_38,param_1);
  puVar3 = (undefined4 *)*plVar10;
  uVar4 = *puVar3;
  uVar5 = puVar3[1];
  uVar6 = puVar3[2];
  uVar9 = *(undefined8 *)(puVar3 + 4);
  uVar7 = *(undefined8 *)(puVar3 + 6);
  if (local_30 != (longlong *)0x0) {
    LOCK();
    plVar10 = local_30 + 1;
    lVar8 = *plVar10;
    *(int *)plVar10 = (int)*plVar10 + -1;
    UNLOCK();
    if ((int)lVar8 == 1) {
      (**(code **)*local_30)(local_30);
      LOCK();
      piVar1 = (int *)((longlong)local_30 + 0xc);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 == 1) {
        (**(code **)(*local_30 + 8))(local_30);
      }
    }
  }
  *(undefined8 *)(param_2 + 4) = uVar9;
  *param_2 = uVar4;
  *(undefined8 *)(param_2 + 6) = uVar7;
  param_2[2] = uVar6;
  param_2[1] = uVar5;
  return;
}



// ==== GetEnvironmentDetectionStatusEx @ 18015d310 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetEnvironmentDetectionStatusEx(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15d310  49  GetEnvironmentDetectionStatusEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000cd30(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== SetEnvironmentDetectionStatusEx @ 18015d3b0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetEnvironmentDetectionStatusEx(undefined2 param_1,undefined1 param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15d3b0  142  SetEnvironmentDetectionStatusEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_18000cea0(local_28,param_2);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== CustomReadNvEx @ 18015e380 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void CustomReadNvEx(undefined2 param_1,undefined8 *param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  longlong *plVar15;
  undefined8 *puVar16;
  undefined8 uVar17;
  undefined8 *puVar18;
  longlong lVar19;
  undefined8 *puVar20;
  undefined1 auStack_458 [32];
  undefined8 local_438 [130];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15e380  11  CustomReadNvEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_458;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar17 = FUN_1801501a0();
  FUN_180150e70(uVar17,&local_28,param_1);
  lVar19 = 8;
  puVar16 = local_438;
  do {
    puVar20 = param_2;
    puVar18 = puVar16;
    uVar17 = puVar20[1];
    uVar12 = puVar20[2];
    uVar13 = puVar20[3];
    *puVar18 = *puVar20;
    puVar18[1] = uVar17;
    uVar17 = puVar20[4];
    uVar14 = puVar20[5];
    puVar18[2] = uVar12;
    puVar18[3] = uVar13;
    uVar12 = puVar20[6];
    uVar13 = puVar20[7];
    puVar18[4] = uVar17;
    puVar18[5] = uVar14;
    uVar17 = puVar20[8];
    uVar14 = puVar20[9];
    puVar18[6] = uVar12;
    puVar18[7] = uVar13;
    uVar12 = puVar20[10];
    uVar13 = puVar20[0xb];
    puVar18[8] = uVar17;
    puVar18[9] = uVar14;
    uVar4 = *(undefined4 *)(puVar20 + 0xc);
    uVar5 = *(undefined4 *)((longlong)puVar20 + 100);
    uVar6 = *(undefined4 *)(puVar20 + 0xd);
    uVar7 = *(undefined4 *)((longlong)puVar20 + 0x6c);
    puVar18[10] = uVar12;
    puVar18[0xb] = uVar13;
    uVar8 = *(undefined4 *)(puVar20 + 0xe);
    uVar9 = *(undefined4 *)((longlong)puVar20 + 0x74);
    uVar10 = *(undefined4 *)(puVar20 + 0xf);
    uVar11 = *(undefined4 *)((longlong)puVar20 + 0x7c);
    *(undefined4 *)(puVar18 + 0xc) = uVar4;
    *(undefined4 *)((longlong)puVar18 + 100) = uVar5;
    *(undefined4 *)(puVar18 + 0xd) = uVar6;
    *(undefined4 *)((longlong)puVar18 + 0x6c) = uVar7;
    *(undefined4 *)(puVar18 + 0xe) = uVar8;
    *(undefined4 *)((longlong)puVar18 + 0x74) = uVar9;
    *(undefined4 *)(puVar18 + 0xf) = uVar10;
    *(undefined4 *)((longlong)puVar18 + 0x7c) = uVar11;
    lVar19 = lVar19 + -1;
    puVar16 = puVar18 + 0x10;
    param_2 = puVar20 + 0x10;
  } while (lVar19 != 0);
  *(undefined4 *)(puVar18 + 0x10) = *(undefined4 *)(puVar20 + 0x10);
  *(undefined2 *)((longlong)puVar18 + 0x84) = *(undefined2 *)((longlong)puVar20 + 0x84);
  FUN_1800101a0(local_28,local_438);
  plVar15 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar19 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar19 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar15 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar15 + 8))(plVar15);
      }
    }
  }
  return;
}



// ==== CustomWriteNvEx @ 18015e4b0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void CustomWriteNvEx(undefined2 param_1,undefined8 *param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  longlong *plVar15;
  undefined8 *puVar16;
  undefined8 uVar17;
  undefined8 *puVar18;
  longlong lVar19;
  undefined8 *puVar20;
  undefined1 auStack_458 [32];
  undefined8 local_438 [130];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15e4b0  12  CustomWriteNvEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_458;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar17 = FUN_1801501a0();
  FUN_180150e70(uVar17,&local_28,param_1);
  lVar19 = 8;
  puVar16 = local_438;
  do {
    puVar20 = param_2;
    puVar18 = puVar16;
    uVar17 = puVar20[1];
    uVar12 = puVar20[2];
    uVar13 = puVar20[3];
    *puVar18 = *puVar20;
    puVar18[1] = uVar17;
    uVar17 = puVar20[4];
    uVar14 = puVar20[5];
    puVar18[2] = uVar12;
    puVar18[3] = uVar13;
    uVar12 = puVar20[6];
    uVar13 = puVar20[7];
    puVar18[4] = uVar17;
    puVar18[5] = uVar14;
    uVar17 = puVar20[8];
    uVar14 = puVar20[9];
    puVar18[6] = uVar12;
    puVar18[7] = uVar13;
    uVar12 = puVar20[10];
    uVar13 = puVar20[0xb];
    puVar18[8] = uVar17;
    puVar18[9] = uVar14;
    uVar4 = *(undefined4 *)(puVar20 + 0xc);
    uVar5 = *(undefined4 *)((longlong)puVar20 + 100);
    uVar6 = *(undefined4 *)(puVar20 + 0xd);
    uVar7 = *(undefined4 *)((longlong)puVar20 + 0x6c);
    puVar18[10] = uVar12;
    puVar18[0xb] = uVar13;
    uVar8 = *(undefined4 *)(puVar20 + 0xe);
    uVar9 = *(undefined4 *)((longlong)puVar20 + 0x74);
    uVar10 = *(undefined4 *)(puVar20 + 0xf);
    uVar11 = *(undefined4 *)((longlong)puVar20 + 0x7c);
    *(undefined4 *)(puVar18 + 0xc) = uVar4;
    *(undefined4 *)((longlong)puVar18 + 100) = uVar5;
    *(undefined4 *)(puVar18 + 0xd) = uVar6;
    *(undefined4 *)((longlong)puVar18 + 0x6c) = uVar7;
    *(undefined4 *)(puVar18 + 0xe) = uVar8;
    *(undefined4 *)((longlong)puVar18 + 0x74) = uVar9;
    *(undefined4 *)(puVar18 + 0xf) = uVar10;
    *(undefined4 *)((longlong)puVar18 + 0x7c) = uVar11;
    lVar19 = lVar19 + -1;
    puVar16 = puVar18 + 0x10;
    param_2 = puVar20 + 0x10;
  } while (lVar19 != 0);
  *(undefined4 *)(puVar18 + 0x10) = *(undefined4 *)(puVar20 + 0x10);
  *(undefined2 *)((longlong)puVar18 + 0x84) = *(undefined2 *)((longlong)puVar20 + 0x84);
  FUN_180010330(local_28,local_438);
  plVar15 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar19 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar19 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar15 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar15 + 8))(plVar15);
      }
    }
  }
  return;
}



// ==== SetWearDetection @ 18015ed90 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetWearDetection(undefined2 param_1,undefined1 param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15ed90  173  SetWearDetection */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_1800113f0(local_28,param_2);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetWearDetection @ 18015ee30 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetWearDetection(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15ee30  99  GetWearDetection */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_180011570(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== SetBusyLightStatus @ 18015eed0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetBusyLightStatus(undefined2 param_1,undefined1 param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15eed0  127  SetBusyLightStatus */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_1800116e0(local_28,param_2);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetBusyLightStatus @ 18015ef70 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetBusyLightStatus(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15ef70  31  GetBusyLightStatus */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_180011860(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== SetNotificationActivation @ 18015f1f0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetNotificationActivation(undefined2 param_1,undefined1 param_2,undefined2 param_3)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15f1f0  157  SetNotificationActivation */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_180011e30(local_28,param_2,param_3);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetNotificationActivation @ 18015f2a0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetNotificationActivation(undefined2 param_1,undefined1 param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15f2a0  73  GetNotificationActivation */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_180011fc0(local_28,param_2);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetNotificationMap @ 18015f340 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetNotificationMap(undefined2 param_1,undefined1 param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15f340  74  GetNotificationMap */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_180012140(local_28,param_2);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== SetVoiceGuidance @ 18015f530 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetVoiceGuidance(undefined2 param_1,undefined1 param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15f530  170  SetVoiceGuidance */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_1800125d0(local_28,param_2);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetVoiceGuidance @ 18015f5d0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetVoiceGuidance(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15f5d0  96  GetVoiceGuidance */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_180012750(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetStandAloneMicStatusEx @ 18015ffc0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetStandAloneMicStatusEx(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x15ffc0  86  GetStandAloneMicStatusEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_180013800(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== GetStandAloneMicVolumeEx @ 180160060 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void GetStandAloneMicVolumeEx(undefined2 param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x160060  88  GetStandAloneMicVolumeEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_180013970(local_28);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== SetStandAloneMicStatusEx @ 180160100 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetStandAloneMicStatusEx(undefined2 param_1,undefined1 param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x160100  164  SetStandAloneMicStatusEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_180013ae0(local_28,param_2);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== SetStandAloneMicVolumeEx @ 1801601a0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void SetStandAloneMicVolumeEx(undefined2 param_1,undefined1 param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong *plStack_20;
  ulonglong local_18;
  
                    /* 0x1601a0  166  SetStandAloneMicVolumeEx */
  local_18 = DAT_180225100 ^ (ulonglong)auStack_48;
  local_28 = 0;
  plStack_20 = (longlong *)0x0;
  uVar6 = FUN_1801501a0();
  FUN_180150e70(uVar6,&local_28,param_1);
  FUN_180013c60(local_28,param_2);
  plVar5 = plStack_20;
  if (plStack_20 != (longlong *)0x0) {
    LOCK();
    plVar1 = plStack_20 + 1;
    lVar4 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar4 == 1) {
      (**(code **)*plStack_20)(plStack_20);
      LOCK();
      piVar2 = (int *)((longlong)plVar5 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}



// ==== _invoke_watson @ 18018f6a8 ====

/* Library Function - Single Match
    _invoke_watson
   
   Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release */

void __cdecl
_invoke_watson(wchar_t *param_1,wchar_t *param_2,wchar_t *param_3,uint param_4,uintptr_t param_5)

{
  code *pcVar1;
  BOOL BVar2;
  HANDLE hProcess;
  undefined1 *puVar3;
  undefined1 auStack_28 [8];
  undefined1 auStack_20 [32];
  
  BVar2 = IsProcessorFeaturePresent(0x17);
  puVar3 = auStack_28;
  if (BVar2 != 0) {
    pcVar1 = (code *)swi(0x29);
    (*pcVar1)(5);
    puVar3 = auStack_20;
  }
  *(undefined8 *)(puVar3 + -8) = 0x18018f6d6;
  __acrt_call_reportfault(2,0xc0000417);
  *(undefined8 *)(puVar3 + -8) = 0x18018f6dc;
  hProcess = GetCurrentProcess();
                    /* WARNING: Could not recover jumptable at 0x00018018f6e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  TerminateProcess(hProcess,0xc0000417);
  return;
}



// ==== convert_decimal_string_to_floating_type_common @ 180197970 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    enum SLD_STATUS __cdecl __crt_strtox::convert_decimal_string_to_floating_type_common(struct
   __crt_strtox::floating_point_string const & __ptr64,class __crt_strtox::floating_point_value
   const & __ptr64)
   
   Library: Visual Studio 2017 Release */

SLD_STATUS __cdecl
__crt_strtox::convert_decimal_string_to_floating_type_common
          (floating_point_string *param_1,floating_point_value *param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  SLD_STATUS SVar10;
  floating_point_string *pfVar11;
  ulong *puVar12;
  ulonglong *puVar13;
  uint *puVar14;
  __uint64 _Var15;
  byte bVar16;
  uint uVar17;
  ulonglong uVar18;
  ulonglong uVar19;
  uint uVar20;
  uint *puVar21;
  floating_point_string fVar22;
  ulonglong uVar23;
  uint uVar24;
  uint uVar25;
  floating_point_string *pfVar26;
  rsize_t rVar27;
  uint uVar28;
  floating_point_string *pfVar29;
  ulonglong uVar30;
  uint uVar31;
  ulonglong uVar32;
  bool bVar33;
  undefined1 auStackY_ba8 [32];
  uint local_b24 [115];
  uint local_958;
  uint local_954 [115];
  uint local_788;
  uint local_784 [115];
  uint local_5b8;
  undefined8 local_5b4;
  uint local_3e8;
  uint local_3e4 [115];
  uint local_218;
  uint local_214 [115];
  ulonglong local_48;
  
  local_48 = DAT_180225100 ^ (ulonglong)auStackY_ba8;
  uVar28 = *(uint *)param_1;
  uVar3 = *(uint *)(param_1 + 4);
  uVar2 = (-(uint)(param_2[8] != (floating_point_value)0x0) & 0x1d) + 0x19;
  local_958 = 0;
  if ((int)uVar28 < 0) {
    uVar28 = 0;
  }
  uVar31 = 0;
  uVar32 = 0;
  uVar6 = uVar28;
  if (uVar3 <= uVar28) {
    uVar6 = uVar3;
  }
  uVar24 = 0;
  uVar28 = uVar28 - uVar6;
  pfVar26 = param_1 + (ulonglong)uVar6 + 8;
  pfVar11 = param_1 + (ulonglong)uVar3 + 8;
  pfVar29 = param_1 + 8;
  uVar3 = (int)pfVar11 - (int)pfVar26;
  if (pfVar29 != pfVar26) {
    do {
      uVar6 = (uint)uVar32;
      if (uVar24 == 9) {
        if (uVar31 != 0) {
          uVar23 = 0;
          uVar30 = 0;
          do {
            uVar24 = (int)uVar30 + 1;
            uVar18 = (ulonglong)local_954[uVar30] * 1000000000 + uVar23;
            local_954[uVar30] = (uint)uVar18;
            uVar23 = uVar18 >> 0x20;
            uVar30 = (ulonglong)uVar24;
          } while (uVar24 != uVar31);
          uVar31 = (uint)(uVar18 >> 0x20);
          if (uVar31 == 0) {
            uVar31 = local_958;
          }
          else if (local_958 < 0x73) {
            local_954[local_958] = uVar31;
            local_958 = local_958 + 1;
            uVar31 = local_958;
          }
          else {
            local_958 = 0;
            uVar31 = 0;
          }
        }
        if (uVar6 != 0) {
          uVar30 = 0;
          if (uVar31 != 0) {
            do {
              uVar24 = (int)uVar30 + 1;
              uVar23 = local_954[uVar30] + uVar32;
              local_954[uVar30] = (uint)uVar23;
              uVar32 = uVar23 >> 0x20;
              uVar6 = (uint)(uVar23 >> 0x20);
              uVar30 = (ulonglong)uVar24;
              uVar31 = local_958;
            } while (uVar24 != local_958);
          }
          if (uVar6 != 0) {
            if (uVar31 < 0x73) {
              local_954[uVar31] = uVar6;
              uVar31 = local_958 + 1;
              local_958 = uVar31;
            }
            else {
              uVar31 = 0;
              local_958 = 0;
            }
          }
        }
        uVar6 = 0;
        uVar24 = 0;
      }
      fVar22 = *pfVar29;
      uVar24 = uVar24 + 1;
      pfVar29 = pfVar29 + 1;
      uVar6 = (uint)(byte)fVar22 + uVar6 * 10;
      uVar32 = (ulonglong)uVar6;
    } while (pfVar29 != pfVar26);
    if (uVar24 != 0) {
      for (uVar4 = uVar24 / 10; uVar4 != 0; uVar4 = uVar4 - uVar20) {
        uVar20 = uVar4;
        if (0x26 < uVar4) {
          uVar20 = 0x26;
        }
        uVar5 = uVar20 - 1;
        bVar16 = (&DAT_1801cd532)[(ulonglong)uVar5 * 4];
        bVar1 = (&DAT_1801cd533)[(ulonglong)uVar5 * 4];
        local_3e8 = (uint)bVar1 + (uint)bVar16;
        FUN_1801b0190(local_3e4,0,(ulonglong)bVar16 * 4);
        FUN_1801afa50(local_3e4 + bVar16,
                      &DAT_1801ccc20 +
                      (ulonglong)*(ushort *)(&DAT_1801cd530 + (ulonglong)uVar5 * 4) * 4,
                      (ulonglong)bVar1 << 2);
        uVar5 = local_954[0];
        if (local_3e8 < 2) {
          uVar30 = (ulonglong)local_3e4[0];
          if (local_3e4[0] == 0) {
LAB_180197bf3:
            local_958 = 0;
            uVar31 = 0;
            goto LAB_180197f19;
          }
          if ((local_3e4[0] == 1) || (uVar31 == 0)) goto LAB_180197f19;
          uVar18 = 0;
          uVar23 = 0;
          do {
            uVar25 = (int)uVar23 + 1;
            uVar19 = local_954[uVar23] * uVar30 + uVar18;
            local_954[uVar23] = (uint)uVar19;
            uVar18 = uVar19 >> 0x20;
            uVar5 = (uint)(uVar19 >> 0x20);
            uVar23 = (ulonglong)uVar25;
          } while (uVar25 != uVar31);
LAB_180197c46:
          uVar31 = 0;
          if (uVar5 == 0) {
            uVar31 = local_958;
            goto LAB_180197f19;
          }
          if (local_958 < 0x73) {
            local_954[local_958] = uVar5;
            local_958 = local_958 + 1;
            uVar31 = local_958;
            goto LAB_180197f19;
          }
          local_958 = 0;
          bVar33 = false;
        }
        else {
          if (uVar31 < 2) {
            uVar30 = (ulonglong)local_954[0];
            local_958 = local_3e8;
            if ((ulonglong)local_3e8 != 0) {
              if ((ulonglong)local_3e8 * 4 < 0x1cd) {
                FUN_1801afa50();
              }
              else {
                FUN_1801b0190(local_954,0,0x1cc);
                puVar12 = __doserrno();
                *puVar12 = 0x22;
                FUN_18018f658();
              }
            }
            if (uVar5 == 0) goto LAB_180197bf3;
            uVar31 = local_958;
            if ((uVar5 != 1) && (local_958 != 0)) {
              uVar18 = 0;
              uVar23 = 0;
              do {
                uVar31 = (int)uVar23 + 1;
                uVar19 = local_954[uVar23] * uVar30 + uVar18;
                local_954[uVar23] = (uint)uVar19;
                uVar18 = uVar19 >> 0x20;
                uVar5 = (uint)(uVar19 >> 0x20);
                uVar23 = (ulonglong)uVar31;
              } while (uVar31 != local_958);
              goto LAB_180197c46;
            }
          }
          else {
            puVar14 = local_954;
            puVar21 = local_3e4;
            if (uVar31 <= local_3e8) {
              uVar5 = uVar31;
            }
            else {
              puVar21 = local_954;
              uVar5 = local_3e8;
              puVar14 = local_3e4;
            }
            local_5b8 = 0;
            uVar30 = 0;
            uVar25 = local_3e8;
            if (uVar31 > local_3e8) {
              uVar25 = uVar31;
            }
            local_958 = 0;
            if (uVar5 != 0) {
              do {
                uVar9 = (uint)uVar30;
                uVar31 = puVar14[uVar30];
                if (uVar31 == 0) {
                  if (uVar9 == local_958) {
                    local_958 = uVar9 + 1;
                    local_784[uVar30 + 0x74] = 0;
                    local_5b8 = local_958;
                  }
                }
                else {
                  uVar23 = 0;
                  uVar8 = uVar9;
                  if (uVar25 != 0) {
                    do {
                      uVar8 = (uint)uVar30;
                      uVar18 = uVar30;
                      if (uVar8 == 0x73) break;
                      if (uVar8 == local_958) {
                        local_784[uVar30 + 0x74] = 0;
                        local_5b8 = uVar8 + 1;
                      }
                      uVar18 = (ulonglong)(uVar8 + 1);
                      uVar23 = (ulonglong)puVar21[-uVar9 + uVar8] * (ulonglong)uVar31 +
                               (ulonglong)local_784[uVar30 + 0x74] + uVar23;
                      local_784[uVar30 + 0x74] = (uint)uVar23;
                      uVar23 = uVar23 >> 0x20;
                      uVar30 = uVar18;
                      local_958 = local_5b8;
                    } while (-uVar9 + uVar8 + 1 != uVar25);
                    uVar8 = (uint)uVar18;
                    uVar31 = (uint)uVar23;
                    while (uVar31 != 0) {
                      uVar8 = (uint)uVar18;
                      if (uVar8 == 0x73) goto LAB_180197fe5;
                      if (uVar8 == local_958) {
                        local_784[uVar18 + 0x74] = 0;
                        local_5b8 = uVar8 + 1;
                      }
                      uVar31 = local_784[uVar18 + 0x74];
                      uVar8 = uVar8 + 1;
                      local_784[uVar18 + 0x74] = (uint)(uVar31 + uVar23);
                      uVar31 = (uint)(uVar31 + uVar23 >> 0x20);
                      uVar23 = (ulonglong)uVar31;
                      uVar18 = (ulonglong)uVar8;
                      local_958 = local_5b8;
                    }
                  }
                  if (uVar8 == 0x73) goto LAB_180197fe5;
                }
                uVar30 = (ulonglong)(uVar9 + 1);
              } while (uVar9 + 1 != uVar5);
            }
            if ((ulonglong)local_958 != 0) {
              if ((ulonglong)local_958 * 4 < 0x1cd) {
                FUN_1801afa50();
              }
              else {
                FUN_1801b0190(local_954,0,0x1cc);
                puVar12 = __doserrno();
                *puVar12 = 0x22;
                FUN_18018f658();
              }
            }
            uVar31 = local_958;
          }
LAB_180197f19:
          bVar33 = true;
        }
        if (!bVar33) goto LAB_180197fe5;
      }
      if (uVar24 % 10 != 0) {
        uVar24 = *(uint *)(&DAT_1801cd5c8 + (ulonglong)(uVar24 % 10 - 1) * 4);
        if (uVar24 == 0) {
LAB_180197fe5:
          local_958 = 0;
          uVar31 = 0;
        }
        else if ((uVar24 != 1) && (uVar31 != 0)) {
          uVar23 = 0;
          uVar30 = 0;
          do {
            uVar4 = (int)uVar30 + 1;
            uVar18 = (ulonglong)local_954[uVar30] * (ulonglong)uVar24 + uVar23;
            local_954[uVar30] = (uint)uVar18;
            uVar23 = uVar18 >> 0x20;
            uVar30 = (ulonglong)uVar4;
          } while (uVar4 != uVar31);
          uVar31 = (uint)(uVar18 >> 0x20);
          if (uVar31 == 0) {
            uVar31 = local_958;
          }
          else {
            if (0x72 < local_958) goto LAB_180197fe5;
            local_954[local_958] = uVar31;
            local_958 = local_958 + 1;
            uVar31 = local_958;
          }
        }
      }
      if (uVar6 != 0) {
        uVar30 = 0;
        if (uVar31 != 0) {
          do {
            uVar24 = (int)uVar30 + 1;
            uVar23 = local_954[uVar30] + uVar32;
            local_954[uVar30] = (uint)uVar23;
            uVar32 = uVar23 >> 0x20;
            uVar6 = (uint)(uVar23 >> 0x20);
            uVar30 = (ulonglong)uVar24;
            uVar31 = local_958;
          } while (uVar24 != local_958);
        }
        if (uVar6 != 0) {
          if (uVar31 < 0x73) {
            local_954[uVar31] = uVar6;
            uVar31 = local_958 + 1;
            local_958 = uVar31;
          }
          else {
            uVar31 = 0;
            local_958 = 0;
          }
        }
      }
    }
  }
  if (uVar28 == 0) {
LAB_180198598:
    if (uVar31 == 0) goto LAB_18019859d;
    iVar7 = 0x1f;
    bVar33 = local_954[uVar31 - 1] == 0;
    if (!bVar33) {
      for (; local_954[uVar31 - 1] >> iVar7 == 0; iVar7 = iVar7 + -1) {
      }
    }
    if (bVar33) {
      iVar7 = 0;
    }
    else {
      iVar7 = iVar7 + 1;
    }
    uVar28 = (uVar31 - 1) * 0x20 + iVar7;
  }
  else {
    for (uVar6 = uVar28 / 10; uVar6 != 0; uVar6 = uVar6 - uVar24) {
      uVar24 = uVar6;
      if (0x26 < uVar6) {
        uVar24 = 0x26;
      }
      uVar4 = uVar24 - 1;
      bVar16 = (&DAT_1801cd532)[(ulonglong)uVar4 * 4];
      bVar1 = (&DAT_1801cd533)[(ulonglong)uVar4 * 4];
      local_3e8 = (uint)bVar1 + (uint)bVar16;
      FUN_1801b0190(local_3e4,0,(ulonglong)bVar16 * 4);
      FUN_1801afa50(local_3e4 + bVar16,
                    &DAT_1801ccc20 +
                    (ulonglong)*(ushort *)(&DAT_1801cd530 + (ulonglong)uVar4 * 4) * 4,
                    (ulonglong)bVar1 << 2);
      uVar4 = local_954[0];
      if (local_3e8 < 2) {
        uVar32 = (ulonglong)local_3e4[0];
        if (local_3e4[0] == 0) {
LAB_18019812e:
          local_958 = 0;
          uVar31 = 0;
          goto LAB_180198443;
        }
        if ((local_3e4[0] == 1) || (uVar31 == 0)) goto LAB_180198443;
        uVar23 = 0;
        uVar30 = 0;
        do {
          uVar20 = (int)uVar30 + 1;
          uVar18 = local_954[uVar30] * uVar32 + uVar23;
          local_954[uVar30] = (uint)uVar18;
          uVar23 = uVar18 >> 0x20;
          uVar4 = (uint)(uVar18 >> 0x20);
          uVar30 = (ulonglong)uVar20;
        } while (uVar20 != uVar31);
LAB_180198181:
        uVar31 = 0;
        if (uVar4 == 0) {
          uVar31 = local_958;
          goto LAB_180198443;
        }
        if (local_958 < 0x73) {
          local_954[local_958] = uVar4;
          local_958 = local_958 + 1;
          uVar31 = local_958;
          goto LAB_180198443;
        }
        local_958 = 0;
        bVar33 = false;
      }
      else {
        if (uVar31 < 2) {
          uVar32 = (ulonglong)local_954[0];
          local_958 = local_3e8;
          if ((ulonglong)local_3e8 != 0) {
            if ((ulonglong)local_3e8 * 4 < 0x1cd) {
              FUN_1801afa50();
            }
            else {
              FUN_1801b0190(local_954,0,0x1cc);
              puVar12 = __doserrno();
              *puVar12 = 0x22;
              FUN_18018f658();
            }
          }
          if (uVar4 == 0) goto LAB_18019812e;
          uVar31 = local_958;
          if ((uVar4 != 1) && (local_958 != 0)) {
            uVar23 = 0;
            uVar30 = 0;
            do {
              uVar31 = (int)uVar30 + 1;
              uVar18 = local_954[uVar30] * uVar32 + uVar23;
              local_954[uVar30] = (uint)uVar18;
              uVar23 = uVar18 >> 0x20;
              uVar4 = (uint)(uVar18 >> 0x20);
              uVar30 = (ulonglong)uVar31;
            } while (uVar31 != local_958);
            goto LAB_180198181;
          }
        }
        else {
          puVar14 = local_954;
          puVar21 = local_3e4;
          if (uVar31 <= local_3e8) {
            uVar4 = uVar31;
          }
          else {
            puVar21 = local_954;
            uVar4 = local_3e8;
            puVar14 = local_3e4;
          }
          local_5b8 = 0;
          uVar32 = 0;
          uVar20 = local_3e8;
          if (uVar31 > local_3e8) {
            uVar20 = uVar31;
          }
          local_958 = 0;
          if (uVar4 != 0) {
            do {
              uVar5 = (uint)uVar32;
              uVar31 = puVar14[uVar32];
              if (uVar31 == 0) {
                if (uVar5 == local_958) {
                  local_958 = uVar5 + 1;
                  local_784[uVar32 + 0x74] = 0;
                  local_5b8 = local_958;
                }
              }
              else {
                uVar30 = 0;
                uVar25 = uVar5;
                if (uVar20 != 0) {
                  do {
                    uVar25 = (uint)uVar32;
                    uVar23 = uVar32;
                    if (uVar25 == 0x73) break;
                    if (uVar25 == local_958) {
                      local_784[uVar32 + 0x74] = 0;
                      local_5b8 = uVar25 + 1;
                    }
                    uVar23 = (ulonglong)(uVar25 + 1);
                    uVar30 = (ulonglong)puVar21[-uVar5 + uVar25] * (ulonglong)uVar31 + uVar30 +
                             (ulonglong)local_784[uVar32 + 0x74];
                    local_784[uVar32 + 0x74] = (uint)uVar30;
                    uVar30 = uVar30 >> 0x20;
                    uVar32 = uVar23;
                    local_958 = local_5b8;
                  } while (-uVar5 + uVar25 + 1 != uVar20);
                  uVar25 = (uint)uVar23;
                  uVar31 = (uint)uVar30;
                  while (uVar31 != 0) {
                    uVar25 = (uint)uVar23;
                    if (uVar25 == 0x73) goto LAB_180198512;
                    if (uVar25 == local_958) {
                      local_784[uVar23 + 0x74] = 0;
                      local_5b8 = uVar25 + 1;
                    }
                    uVar31 = local_784[uVar23 + 0x74];
                    uVar25 = uVar25 + 1;
                    local_784[uVar23 + 0x74] = (uint)(uVar30 + uVar31);
                    uVar31 = (uint)(uVar30 + uVar31 >> 0x20);
                    uVar30 = (ulonglong)uVar31;
                    uVar23 = (ulonglong)uVar25;
                    local_958 = local_5b8;
                  }
                }
                if (uVar25 == 0x73) goto LAB_180198512;
              }
              uVar32 = (ulonglong)(uVar5 + 1);
            } while (uVar5 + 1 != uVar4);
          }
          if ((ulonglong)local_958 != 0) {
            if ((ulonglong)local_958 * 4 < 0x1cd) {
              FUN_1801afa50();
            }
            else {
              FUN_1801b0190(local_954,0,0x1cc);
              puVar12 = __doserrno();
              *puVar12 = 0x22;
              FUN_18018f658();
            }
          }
          uVar31 = local_958;
        }
LAB_180198443:
        bVar33 = true;
      }
      if (!bVar33) goto LAB_180198512;
    }
    if (uVar28 % 10 == 0) goto LAB_180198598;
    uVar28 = *(uint *)(&DAT_1801cd5c8 + (ulonglong)(uVar28 % 10 - 1) * 4);
    if (uVar28 != 0) {
      if (uVar28 != 1) {
        if (uVar31 == 0) goto LAB_18019859d;
        uVar30 = 0;
        uVar32 = 0;
        do {
          uVar6 = (int)uVar32 + 1;
          uVar23 = (ulonglong)local_954[uVar32] * (ulonglong)uVar28 + uVar30;
          local_954[uVar32] = (uint)uVar23;
          uVar30 = uVar23 >> 0x20;
          uVar32 = (ulonglong)uVar6;
        } while (uVar6 != uVar31);
        uVar28 = (uint)(uVar23 >> 0x20);
        if (uVar28 == 0) {
          uVar31 = local_958;
        }
        else {
          if (0x72 < local_958) {
LAB_180198512:
            puVar13 = *(ulonglong **)param_2;
            if (param_2[8] == (floating_point_value)0x0) {
              *(uint *)puVar13 =
                   (-(uint)(param_1[0x308] != (floating_point_string)0x0) & 0x80000000) + 0x7f800000
                   | (uint)*puVar13 & 0x7f800000;
            }
            else {
              *puVar13 = (-(ulonglong)(param_1[0x308] != (floating_point_string)0x0) &
                         0x8000000000000000) + 0x7ff0000000000000 | *puVar13 & 0x7ff0000000000000;
            }
            return 3;
          }
          local_954[local_958] = uVar28;
          local_958 = local_958 + 1;
          uVar31 = local_958;
        }
      }
      goto LAB_180198598;
    }
    uVar31 = 0;
    local_958 = 0;
LAB_18019859d:
    uVar28 = 0;
  }
  if ((uVar2 <= uVar28) || (uVar3 == 0)) {
    bVar33 = uVar3 != 0;
    fVar22 = param_1[0x308];
    goto LAB_1801996ba;
  }
  uVar6 = 0;
  uVar32 = 0;
  local_788 = 0;
  uVar24 = 0;
  if (pfVar26 != pfVar11) {
    do {
      uVar4 = (uint)uVar32;
      if (uVar24 == 9) {
        if (uVar6 != 0) {
          uVar23 = 0;
          uVar30 = 0;
          do {
            uVar24 = (int)uVar30 + 1;
            uVar18 = (ulonglong)local_784[uVar30] * 1000000000 + uVar23;
            local_784[uVar30] = (uint)uVar18;
            uVar23 = uVar18 >> 0x20;
            uVar30 = (ulonglong)uVar24;
          } while (uVar24 != uVar6);
          uVar6 = (uint)(uVar18 >> 0x20);
          if (uVar6 != 0) {
            if (local_788 < 0x73) {
              local_784[local_788] = uVar6;
              local_788 = local_788 + 1;
              uVar6 = local_788;
              goto LAB_18019869d;
            }
            local_218 = 0;
            local_788 = 0;
            memcpy_s(local_784,0x1cc,local_214,0);
          }
          uVar6 = local_788;
        }
LAB_18019869d:
        if (uVar4 != 0) {
          uVar24 = 0;
          if (uVar6 != 0) {
            do {
              uVar20 = uVar24 + 1;
              uVar30 = uVar32 + local_784[uVar24];
              local_784[uVar24] = (uint)uVar30;
              uVar32 = uVar30 >> 0x20;
              uVar4 = (uint)(uVar30 >> 0x20);
              uVar6 = local_788;
              uVar24 = uVar20;
            } while (uVar20 != local_788);
          }
          if (uVar4 != 0) {
            if (uVar6 < 0x73) {
              local_784[uVar6] = uVar4;
              local_788 = local_788 + 1;
              uVar6 = local_788;
            }
            else {
              local_218 = 0;
              local_788 = 0;
              memcpy_s(local_784,0x1cc,local_214,0);
              uVar6 = local_788;
            }
          }
        }
        uVar4 = 0;
        uVar24 = 0;
      }
      fVar22 = *pfVar26;
      uVar24 = uVar24 + 1;
      pfVar26 = pfVar26 + 1;
      uVar4 = (uint)(byte)fVar22 + uVar4 * 10;
      uVar32 = (ulonglong)uVar4;
    } while (pfVar26 != pfVar11);
    if (uVar24 != 0) {
      for (uVar20 = uVar24 / 10; uVar20 != 0; uVar20 = uVar20 - uVar5) {
        uVar5 = uVar20;
        if (0x26 < uVar20) {
          uVar5 = 0x26;
        }
        uVar30 = (ulonglong)(uVar5 - 1);
        bVar16 = (&DAT_1801cd532)[uVar30 * 4];
        bVar1 = (&DAT_1801cd533)[uVar30 * 4];
        local_3e8 = (uint)bVar1 + (uint)bVar16;
        FUN_1801b0190(local_3e4,0,(ulonglong)bVar16 * 4);
        FUN_1801afa50(local_3e4 + bVar16,
                      &DAT_1801ccc20 + (ulonglong)*(ushort *)(&DAT_1801cd530 + uVar30 * 4) * 4,
                      (ulonglong)bVar1 << 2);
        uVar25 = local_784[0];
        if (local_3e8 < 2) {
          uVar30 = (ulonglong)local_3e4[0];
          if (local_3e4[0] == 0) goto LAB_18019880c;
          if ((local_3e4[0] == 1) || (uVar6 == 0)) goto LAB_180198ab5;
          uVar18 = 0;
          uVar23 = 0;
          do {
            uVar25 = (int)uVar23 + 1;
            uVar19 = local_784[uVar23] * uVar30 + uVar18;
            local_784[uVar23] = (uint)uVar19;
            uVar18 = uVar19 >> 0x20;
            uVar9 = (uint)(uVar19 >> 0x20);
            uVar23 = (ulonglong)uVar25;
          } while (uVar25 != uVar6);
LAB_18019886c:
          if (uVar9 == 0) goto LAB_180198aae;
          if (local_788 < 0x73) {
            local_784[local_788] = uVar9;
            local_788 = local_788 + 1;
            uVar6 = local_788;
            goto LAB_180198ab5;
          }
LAB_180198b75:
          local_218 = 0;
          local_788 = 0;
          memcpy_s(local_784,0x1cc,local_214,0);
          bVar33 = false;
          uVar6 = local_788;
        }
        else {
          puVar14 = local_3e4;
          puVar21 = local_784;
          if (uVar6 < 2) {
            local_788 = local_3e8;
            memcpy_s(puVar21,0x1cc,puVar14,(ulonglong)local_3e8 << 2);
            if (uVar25 != 0) {
              uVar6 = local_788;
              if ((uVar25 != 1) && (local_788 != 0)) {
                uVar23 = 0;
                uVar30 = 0;
                do {
                  uVar6 = (int)uVar30 + 1;
                  uVar18 = (ulonglong)local_784[uVar30] * (ulonglong)uVar25 + uVar23;
                  local_784[uVar30] = (uint)uVar18;
                  uVar23 = uVar18 >> 0x20;
                  uVar9 = (uint)(uVar18 >> 0x20);
                  uVar30 = (ulonglong)uVar6;
                } while (uVar6 != local_788);
                goto LAB_18019886c;
              }
              goto LAB_180198ab5;
            }
LAB_18019880c:
            local_218 = 0;
            puVar14 = local_214;
            local_788 = 0;
            rVar27 = 0;
          }
          else {
            if (local_3e8 < uVar6) {
              puVar14 = local_784;
              uVar25 = local_3e8;
              puVar21 = local_3e4;
            }
            else {
              uVar25 = uVar6;
            }
            uVar30 = 0;
            local_788 = 0;
            uVar9 = local_3e8;
            if (local_3e8 < uVar6) {
              uVar9 = uVar6;
            }
            local_5b8 = 0;
            if (uVar25 != 0) {
              do {
                uVar8 = (uint)uVar30;
                uVar6 = puVar21[uVar30];
                if (uVar6 == 0) {
                  if (uVar8 == local_788) {
                    local_788 = uVar8 + 1;
                    local_784[uVar30 + 0x74] = 0;
                    local_5b8 = local_788;
                  }
                }
                else {
                  uVar23 = 0;
                  if (uVar9 == 0) {
                    uVar6 = uVar8;
                  }
                  else {
                    do {
                      uVar17 = (uint)uVar30;
                      uVar18 = uVar30;
                      if (uVar17 == 0x73) break;
                      if (uVar17 == local_788) {
                        local_784[uVar30 + 0x74] = 0;
                        local_5b8 = uVar17 + 1;
                      }
                      uVar18 = (ulonglong)(uVar17 + 1);
                      uVar23 = (ulonglong)puVar14[-uVar8 + uVar17] * (ulonglong)uVar6 +
                               (ulonglong)local_784[uVar30 + 0x74] + uVar23;
                      local_784[uVar30 + 0x74] = (uint)uVar23;
                      uVar23 = uVar23 >> 0x20;
                      uVar30 = uVar18;
                      local_788 = local_5b8;
                    } while (-uVar8 + uVar17 + 1 != uVar9);
                    uVar6 = (uint)uVar18;
                    uVar17 = (uint)uVar23;
                    while ((uVar17 != 0 && (uVar6 = (uint)uVar18, uVar6 != 0x73))) {
                      if (uVar6 == local_788) {
                        local_784[uVar18 + 0x74] = 0;
                        local_5b8 = uVar6 + 1;
                      }
                      uVar17 = local_784[uVar18 + 0x74];
                      uVar6 = uVar6 + 1;
                      local_784[uVar18 + 0x74] = (uint)(uVar17 + uVar23);
                      uVar17 = (uint)(uVar17 + uVar23 >> 0x20);
                      uVar23 = (ulonglong)uVar17;
                      local_788 = local_5b8;
                      uVar18 = (ulonglong)uVar6;
                    }
                  }
                  if (uVar6 == 0x73) goto LAB_180198b75;
                }
                uVar30 = (ulonglong)(uVar8 + 1);
              } while (uVar8 + 1 != uVar25);
            }
            puVar14 = (uint *)&local_5b4;
            rVar27 = (ulonglong)local_788 << 2;
          }
          memcpy_s(local_784,0x1cc,puVar14,rVar27);
LAB_180198aae:
          uVar6 = local_788;
LAB_180198ab5:
          bVar33 = true;
        }
        if (!bVar33) goto LAB_180198bab;
      }
      if (uVar24 % 10 != 0) {
        uVar24 = *(uint *)(&DAT_1801cd5c8 + (ulonglong)(uVar24 % 10 - 1) * 4);
        if (uVar24 == 0) {
LAB_180198bab:
          local_218 = 0;
          local_788 = 0;
          memcpy_s(local_784,0x1cc,local_214,0);
LAB_180198bd2:
          uVar6 = local_788;
        }
        else if ((uVar24 != 1) && (uVar6 != 0)) {
          uVar23 = 0;
          uVar30 = 0;
          do {
            uVar20 = (int)uVar30 + 1;
            uVar18 = (ulonglong)local_784[uVar30] * (ulonglong)uVar24 + uVar23;
            local_784[uVar30] = (uint)uVar18;
            uVar23 = uVar18 >> 0x20;
            uVar30 = (ulonglong)uVar20;
          } while (uVar20 != uVar6);
          uVar6 = (uint)(uVar18 >> 0x20);
          if (uVar6 == 0) goto LAB_180198bd2;
          if (0x72 < local_788) goto LAB_180198bab;
          local_784[local_788] = uVar6;
          local_788 = local_788 + 1;
          uVar6 = local_788;
        }
      }
      if (uVar4 != 0) {
        uVar30 = 0;
        if (uVar6 != 0) {
          do {
            uVar24 = (int)uVar30 + 1;
            uVar23 = uVar32 + local_784[uVar30];
            local_784[uVar30] = (uint)uVar23;
            uVar32 = uVar23 >> 0x20;
            uVar4 = (uint)(uVar23 >> 0x20);
            uVar30 = (ulonglong)uVar24;
            uVar6 = local_788;
          } while (uVar24 != local_788);
        }
        if (uVar4 != 0) {
          if (uVar6 < 0x73) {
            local_784[uVar6] = uVar4;
            local_788 = local_788 + 1;
            uVar6 = local_788;
          }
          else {
            local_218 = 0;
            local_788 = 0;
            memcpy_s(local_784,0x1cc,local_214,0);
            uVar6 = local_788;
          }
        }
      }
    }
  }
  uVar24 = 1;
  local_5b4 = 1;
  local_5b8 = 1;
  uVar4 = uVar3 - *(int *)param_1;
  if (-1 < *(int *)param_1) {
    uVar4 = uVar3;
  }
  for (uVar3 = uVar4 / 10; uVar3 != 0; uVar3 = uVar3 - uVar20) {
    uVar20 = uVar3;
    if (0x26 < uVar3) {
      uVar20 = 0x26;
    }
    uVar32 = (ulonglong)(uVar20 - 1);
    bVar16 = (&DAT_1801cd532)[uVar32 * 4];
    bVar1 = (&DAT_1801cd533)[uVar32 * 4];
    local_218 = (uint)bVar1 + (uint)bVar16;
    FUN_1801b0190(local_214,0,(ulonglong)bVar16 * 4);
    FUN_1801afa50(local_214 + bVar16,
                  &DAT_1801ccc20 + (ulonglong)*(ushort *)(&DAT_1801cd530 + uVar32 * 4) * 4,
                  (ulonglong)bVar1 << 2);
    if (local_218 < 2) {
      uVar32 = (ulonglong)local_214[0];
      if (local_214[0] == 0) {
        local_3e8 = 0;
        local_5b8 = 0;
        memcpy_s(&local_5b4,0x1cc,local_3e4,0);
LAB_180198d78:
        uVar24 = local_5b8;
LAB_180198d7f:
        bVar33 = true;
      }
      else {
        if ((local_214[0] == 1) || (uVar24 == 0)) goto LAB_180198d7f;
        uVar23 = 0;
        uVar30 = 0;
        do {
          uVar5 = (int)uVar30 + 1;
          uVar18 = local_784[uVar30 + 0x74] * uVar32 + uVar23;
          local_784[uVar30 + 0x74] = (uint)uVar18;
          uVar23 = uVar18 >> 0x20;
          uVar30 = (ulonglong)uVar5;
        } while (uVar5 != uVar24);
        uVar24 = (uint)(uVar18 >> 0x20);
        if (uVar24 == 0) goto LAB_180198d78;
        if (local_5b8 < 0x73) {
          local_784[(ulonglong)local_5b8 + 0x74] = uVar24;
          uVar24 = local_5b8 + 1;
          local_5b8 = uVar24;
          goto LAB_180198d7f;
        }
        local_218 = 0;
        local_5b8 = 0;
        memcpy_s(&local_5b4,0x1cc,local_214,0);
        bVar33 = false;
        uVar24 = local_5b8;
      }
    }
    else {
      puVar14 = local_214;
      puVar21 = (uint *)&local_5b4;
      if (uVar24 < 2) {
        uVar24 = (uint)local_5b4;
        uVar32 = local_5b4 & 0xffffffff;
        local_5b8 = local_218;
        memcpy_s(puVar21,0x1cc,puVar14,(ulonglong)local_218 << 2);
        if (uVar24 == 0) {
          local_218 = 0;
          puVar14 = local_214;
          local_5b8 = 0;
          rVar27 = 0;
          goto LAB_18019908a;
        }
        if ((uVar24 != 1) && (local_5b8 != 0)) {
          uVar23 = 0;
          uVar30 = 0;
          do {
            uVar24 = (int)uVar30 + 1;
            uVar18 = local_784[uVar30 + 0x74] * uVar32 + uVar23;
            local_784[uVar30 + 0x74] = (uint)uVar18;
            uVar23 = uVar18 >> 0x20;
            uVar30 = (ulonglong)uVar24;
          } while (uVar24 != local_5b8);
          uVar24 = (uint)(uVar18 >> 0x20);
          if (uVar24 != 0) {
            if (0x72 < local_5b8) {
              local_218 = 0;
              puVar14 = local_214;
LAB_180199125:
              local_5b8 = 0;
              memcpy_s(&local_5b4,0x1cc,puVar14,0);
              bVar33 = false;
              uVar24 = local_5b8;
              goto LAB_1801990a2;
            }
            local_784[(ulonglong)local_5b8 + 0x74] = uVar24;
            local_5b8 = local_5b8 + 1;
          }
        }
      }
      else {
        if (local_218 < uVar24) {
          puVar14 = (uint *)&local_5b4;
          uVar5 = local_218;
          puVar21 = local_214;
        }
        else {
          uVar5 = uVar24;
        }
        uVar32 = 0;
        local_5b8 = 0;
        uVar25 = local_218;
        if (local_218 < uVar24) {
          uVar25 = uVar24;
        }
        local_3e8 = 0;
        if (uVar5 != 0) {
          do {
            uVar9 = (uint)uVar32;
            uVar24 = puVar21[uVar32];
            if (uVar24 == 0) {
              if (uVar9 == local_5b8) {
                local_5b8 = uVar9 + 1;
                local_3e4[uVar32] = 0;
                local_3e8 = local_5b8;
              }
            }
            else {
              uVar30 = 0;
              if (uVar25 == 0) {
                uVar24 = uVar9;
              }
              else {
                do {
                  uVar8 = (uint)uVar32;
                  uVar23 = uVar32;
                  if (uVar8 == 0x73) break;
                  if (uVar8 == local_5b8) {
                    local_3e4[uVar32] = 0;
                    local_3e8 = uVar8 + 1;
                  }
                  uVar23 = (ulonglong)(uVar8 + 1);
                  uVar30 = (ulonglong)puVar14[-uVar9 + uVar8] * (ulonglong)uVar24 + uVar30 +
                           (ulonglong)local_3e4[uVar32];
                  local_3e4[uVar32] = (uint)uVar30;
                  uVar30 = uVar30 >> 0x20;
                  uVar32 = uVar23;
                  local_5b8 = local_3e8;
                } while (-uVar9 + uVar8 + 1 != uVar25);
                uVar24 = (uint)uVar23;
                uVar8 = (uint)uVar30;
                while ((uVar8 != 0 && (uVar24 = (uint)uVar23, uVar24 != 0x73))) {
                  if (uVar24 == local_5b8) {
                    local_3e4[uVar23] = 0;
                    local_3e8 = uVar24 + 1;
                  }
                  uVar8 = local_3e4[uVar23];
                  uVar24 = uVar24 + 1;
                  local_3e4[uVar23] = (uint)(uVar8 + uVar30);
                  uVar8 = (uint)(uVar8 + uVar30 >> 0x20);
                  uVar30 = (ulonglong)uVar8;
                  local_5b8 = local_3e8;
                  uVar23 = (ulonglong)uVar24;
                }
              }
              if (uVar24 == 0x73) {
                puVar14 = local_b24;
                goto LAB_180199125;
              }
            }
            uVar32 = (ulonglong)(uVar9 + 1);
          } while (uVar9 + 1 != uVar5);
        }
        puVar14 = local_3e4;
        rVar27 = (ulonglong)local_5b8 << 2;
LAB_18019908a:
        memcpy_s(&local_5b4,0x1cc,puVar14,rVar27);
      }
      bVar33 = true;
      uVar24 = local_5b8;
    }
LAB_1801990a2:
    if (!bVar33) goto LAB_1801991c9;
  }
  if (uVar4 % 10 != 0) {
    uVar3 = *(uint *)(&DAT_1801cd5c8 + (ulonglong)(uVar4 % 10 - 1) * 4);
    if (uVar3 == 0) {
      local_5b8 = 0;
      memcpy_s(&local_5b4,0x1cc,local_b24,0);
LAB_180199102:
      uVar24 = local_5b8;
    }
    else if ((uVar3 != 1) && (uVar24 != 0)) {
      uVar30 = 0;
      uVar32 = 0;
      do {
        uVar4 = (int)uVar32 + 1;
        uVar23 = (ulonglong)local_784[uVar32 + 0x74] * (ulonglong)uVar3 + uVar30;
        local_784[uVar32 + 0x74] = (uint)uVar23;
        uVar30 = uVar23 >> 0x20;
        uVar32 = (ulonglong)uVar4;
      } while (uVar4 != uVar24);
      uVar3 = (uint)(uVar23 >> 0x20);
      if (uVar3 == 0) goto LAB_180199102;
      if (0x72 < local_5b8) {
LAB_1801991c9:
        local_5b8 = 0;
        memcpy_s(&local_5b4,0x1cc,local_b24,0);
        fVar22 = param_1[0x308];
        if (param_2[8] == (floating_point_value)0x0) {
          puVar14 = (uint *)FUN_180197428();
          *puVar14 = -(uint)(fVar22 != (floating_point_string)0x0) & 0x80000000;
        }
        else {
          puVar13 = (ulonglong *)FUN_1801973ec();
          *puVar13 = -(ulonglong)(fVar22 != (floating_point_string)0x0) & 0x8000000000000000;
        }
        return 2;
      }
      local_784[(ulonglong)local_5b8 + 0x74] = uVar3;
      uVar24 = local_5b8 + 1;
      local_5b8 = uVar24;
    }
  }
  if (uVar6 == 0) {
    uVar3 = 0;
  }
  else {
    iVar7 = 0x1f;
    bVar33 = local_784[uVar6 - 1] == 0;
    if (!bVar33) {
      for (; local_784[uVar6 - 1] >> iVar7 == 0; iVar7 = iVar7 + -1) {
      }
    }
    if (bVar33) {
      iVar7 = 0;
    }
    else {
      iVar7 = iVar7 + 1;
    }
    uVar3 = (uVar6 - 1) * 0x20 + iVar7;
  }
  if (uVar24 == 0) {
    uVar4 = 0;
  }
  else {
    iVar7 = 0x1f;
    bVar33 = local_784[(ulonglong)(uVar24 - 1) + 0x74] == 0;
    if (!bVar33) {
      for (; local_784[(ulonglong)(uVar24 - 1) + 0x74] >> iVar7 == 0; iVar7 = iVar7 + -1) {
      }
    }
    if (bVar33) {
      iVar7 = 0;
    }
    else {
      iVar7 = iVar7 + 1;
    }
    uVar4 = (uVar24 - 1) * 0x20 + iVar7;
  }
  uVar3 = -(uint)(uVar3 < uVar4) & uVar4 - uVar3;
  if (uVar3 != 0) {
    uVar20 = uVar3 & 0x1f;
    uVar5 = uVar3 >> 5;
    bVar16 = 0x20 - (sbyte)uVar20;
    uVar4 = (int)(1L << (bVar16 & 0x3f)) - 1;
    iVar7 = 0x1f;
    bVar33 = local_784[uVar6 - 1] == 0;
    if (!bVar33) {
      for (; local_784[uVar6 - 1] >> iVar7 == 0; iVar7 = iVar7 + -1) {
      }
    }
    if (bVar33) {
      iVar7 = 0;
    }
    else {
      iVar7 = iVar7 + 1;
    }
    uVar25 = uVar5 + uVar6;
    if ((uVar25 == 0x73) && (0x20U - iVar7 < uVar20)) {
      bVar33 = true;
    }
    else {
      bVar33 = false;
    }
    if ((0x73 < uVar25) || (bVar33)) {
      local_788 = 0;
      memcpy_s(local_784,0x1cc,local_b24,0);
      uVar6 = local_788;
    }
    else {
      uVar32 = 0x72;
      if (uVar25 < 0x72) {
        uVar32 = (ulonglong)uVar25;
      }
      uVar25 = (uint)uVar32;
      if (uVar25 != 0xffffffff) {
        while (uVar9 = (uint)uVar32, uVar5 <= uVar9) {
          uVar8 = uVar9 - uVar5;
          if (uVar8 < uVar6) {
            uVar17 = local_784[uVar8];
          }
          else {
            uVar17 = 0;
          }
          if (uVar8 - 1 < uVar6) {
            uVar6 = local_784[uVar8 - 1];
          }
          else {
            uVar6 = 0;
          }
          local_784[uVar32] =
               (uVar6 & ~uVar4) >> (bVar16 & 0x1f) | (uVar17 & uVar4) << (sbyte)uVar20;
          uVar32 = (ulonglong)(uVar9 - 1);
          if (uVar9 - 1 == 0xffffffff) break;
          uVar6 = local_788;
        }
      }
      uVar32 = 0;
      if (uVar5 != 0) {
        do {
          local_784[uVar32] = 0;
          uVar6 = (int)uVar32 + 1;
          uVar32 = (ulonglong)uVar6;
        } while (uVar6 != uVar5);
      }
      if (0x20U - iVar7 < uVar20) {
        uVar25 = uVar25 + 1;
      }
      local_788 = uVar25;
      uVar6 = local_788;
    }
  }
  uVar2 = uVar2 - uVar28;
  uVar4 = uVar2;
  if (uVar28 != 0) {
    if (uVar2 < uVar3) {
      bVar33 = true;
      fVar22 = param_1[0x308];
LAB_1801996ba:
      SVar10 = assemble_floating_point_value_from_big_integer
                         ((big_integer *)&local_958,uVar28,(bool)fVar22,bVar33,param_2);
      return SVar10;
    }
    uVar4 = uVar2 - uVar3;
  }
  if (uVar6 <= uVar24) {
    if (uVar6 < uVar24) {
      bVar33 = true;
      goto LAB_180199493;
    }
    uVar32 = (ulonglong)(uVar6 - 1);
    if (uVar6 - 1 != 0xffffffff) {
      do {
        if (local_784[uVar32] != local_784[uVar32 + 0x74]) break;
        uVar24 = (int)uVar32 - 1;
        uVar32 = (ulonglong)uVar24;
      } while (uVar24 != 0xffffffff);
      if ((int)uVar32 != -1) {
        bVar33 = local_784[uVar32] <= local_784[uVar32 + 0x74];
        goto LAB_180199493;
      }
    }
  }
  bVar33 = false;
LAB_180199493:
  if (bVar33) {
    uVar3 = uVar3 + 1;
  }
  uVar20 = uVar4 & 0x1f;
  uVar4 = uVar4 >> 5;
  bVar16 = 0x20 - (sbyte)uVar20;
  uVar24 = (int)(1L << (bVar16 & 0x3f)) - 1;
  iVar7 = 0x1f;
  bVar33 = local_784[uVar6 - 1] == 0;
  if (!bVar33) {
    for (; local_784[uVar6 - 1] >> iVar7 == 0; iVar7 = iVar7 + -1) {
    }
  }
  if (bVar33) {
    iVar7 = 0;
  }
  else {
    iVar7 = iVar7 + 1;
  }
  uVar5 = uVar4 + uVar6;
  if ((uVar5 == 0x73) && (0x20U - iVar7 < uVar20)) {
    bVar33 = true;
  }
  else {
    bVar33 = false;
  }
  if ((0x73 < uVar5) || (bVar33)) {
    local_788 = 0;
    memcpy_s(local_784,0x1cc,local_b24,0);
  }
  else {
    uVar25 = 0x72;
    if (uVar5 < 0x72) {
      uVar25 = uVar5;
    }
    uVar5 = uVar25;
    if (uVar25 != 0xffffffff) {
      for (; uVar4 <= uVar5; uVar5 = uVar5 - 1) {
        uVar9 = uVar5 - uVar4;
        if (uVar9 < uVar6) {
          uVar8 = local_784[uVar9];
        }
        else {
          uVar8 = 0;
        }
        if (uVar9 - 1 < uVar6) {
          uVar6 = local_784[uVar9 - 1];
        }
        else {
          uVar6 = 0;
        }
        local_784[uVar5] = (uVar6 & ~uVar24) >> (bVar16 & 0x1f) | (uVar8 & uVar24) << (sbyte)uVar20;
        if (uVar5 - 1 == 0xffffffff) break;
        uVar6 = local_788;
      }
    }
    uVar6 = 0;
    if (uVar4 != 0) {
      do {
        uVar32 = (ulonglong)uVar6;
        uVar6 = uVar6 + 1;
        local_784[uVar32] = 0;
      } while (uVar6 != uVar4);
    }
    local_788 = uVar25;
    if (0x20U - iVar7 < uVar20) {
      local_788 = uVar25 + 1;
    }
  }
  _Var15 = divide((big_integer *)&local_788,(big_integer *)&local_5b8);
  bVar33 = local_788 == 0;
  if (_Var15 < 0x100000000) {
    iVar7 = 0x1f;
    uVar6 = (uint)_Var15;
    if (uVar6 != 0) {
      for (; uVar6 >> iVar7 == 0; iVar7 = iVar7 + -1) {
      }
    }
    if (uVar6 == 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = iVar7 + 1;
    }
  }
  else {
    iVar7 = 0x1f;
    uVar6 = (uint)(_Var15 >> 0x20);
    if (uVar6 != 0) {
      for (; uVar6 >> iVar7 == 0; iVar7 = iVar7 + -1) {
      }
    }
    if (uVar6 == 0) {
      iVar7 = 0;
    }
    else {
      iVar7 = iVar7 + 1;
    }
    uVar6 = iVar7 + 0x20;
  }
  if (uVar2 < uVar6) {
    bVar16 = (char)uVar6 - (byte)uVar2;
    if ((!bVar33) || (bVar33 = true, (_Var15 & (1L << (bVar16 & 0x3f)) - 1U) != 0)) {
      bVar33 = false;
    }
    _Var15 = _Var15 >> (bVar16 & 0x3f);
  }
  uVar6 = 0;
  if (uVar31 != 0) {
    uVar6 = local_954[0];
  }
  uVar24 = 0;
  if (1 < uVar31) {
    uVar24 = local_954[1];
  }
  uVar3 = ~uVar3;
  if (uVar28 != 0) {
    uVar3 = uVar28 - 2;
  }
  SVar10 = assemble_floating_point_value
                     (_Var15 + (CONCAT44(uVar24,uVar6) << ((byte)uVar2 & 0x3f)),uVar3,
                      (bool)param_1[0x308],bVar33,param_2);
  return SVar10;
}



// ==== convert_hexadecimal_string_to_floating_type_common @ 1801996f0 ====

/* Library Function - Single Match
    enum SLD_STATUS __cdecl __crt_strtox::convert_hexadecimal_string_to_floating_type_common(struct
   __crt_strtox::floating_point_string const & __ptr64,class __crt_strtox::floating_point_value
   const & __ptr64)
   
   Library: Visual Studio 2017 Release */

SLD_STATUS __cdecl
__crt_strtox::convert_hexadecimal_string_to_floating_type_common
          (floating_point_string *param_1,floating_point_value *param_2)

{
  floating_point_string fVar1;
  SLD_STATUS SVar2;
  __uint64 _Var3;
  floating_point_string *pfVar4;
  bool bVar5;
  int iVar6;
  floating_point_string *pfVar7;
  
  _Var3 = 0;
  pfVar4 = param_1 + 8;
  pfVar7 = param_1 + (ulonglong)*(uint *)(param_1 + 4) + 8;
  iVar6 = (-(uint)(param_2[8] != (floating_point_value)0x0) & 0x1d) + 0x17 + *(int *)param_1;
  if (pfVar4 != pfVar7) {
    do {
      if ((-(ulonglong)(param_2[8] != (floating_point_value)0x0) & 0x1fffffff000000) + 0xffffff <
          _Var3) break;
      fVar1 = *pfVar4;
      iVar6 = iVar6 + -4;
      pfVar4 = pfVar4 + 1;
      _Var3 = _Var3 * 0x10 + (ulonglong)(byte)fVar1;
    } while (pfVar4 != pfVar7);
  }
  bVar5 = true;
  while ((pfVar4 != pfVar7 && (bVar5 != false))) {
    fVar1 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    bVar5 = fVar1 == (floating_point_string)0x0;
  }
  SVar2 = assemble_floating_point_value(_Var3,iVar6,(bool)param_1[0x308],bVar5,param_2);
  return SVar2;
}



// ==== common_initialize_environment_nolock<char> @ 18019a804 ====

/* Library Function - Single Match
    int __cdecl common_initialize_environment_nolock<char>(void)
   
   Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release */

int __cdecl common_initialize_environment_nolock<char>(void)

{
  longlong lVar1;
  longlong lVar2;
  int iVar3;
  
  iVar3 = 0;
  if (DAT_1802335d8 == 0) {
    __acrt_initialize_multibyte();
    lVar1 = __dcrt_get_narrow_environment_from_os();
    if (lVar1 == 0) {
      iVar3 = -1;
    }
    else {
      lVar2 = FUN_18019a870(lVar1);
      if (lVar2 == 0) {
        iVar3 = -1;
      }
      else {
        DAT_1802335d8 = lVar2;
        DAT_1802335f0 = lVar2;
      }
      _free_base(0);
    }
    _free_base(lVar1);
  }
  else {
    iVar3 = 0;
  }
  return iVar3;
}



// ==== free_environment<> @ 18019a978 ====

/* Library Function - Multiple Matches With Same Base Name
    void __cdecl free_environment<char>(char * __ptr64 * __ptr64 const)
    void __cdecl free_environment<wchar_t>(wchar_t * __ptr64 * __ptr64 const)
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

void free_environment<>(longlong *param_1)

{
  longlong lVar1;
  longlong *plVar2;
  
  if (param_1 != (longlong *)0x0) {
    lVar1 = *param_1;
    plVar2 = param_1;
    while (lVar1 != 0) {
      _free_base(lVar1);
      plVar2 = plVar2 + 1;
      lVar1 = *plVar2;
    }
    _free_base(param_1);
  }
  return;
}



// ==== initialize_environment_by_cloning_nolock<char> @ 18019a9bc ====

/* Library Function - Single Match
    int __cdecl initialize_environment_by_cloning_nolock<char>(void)
   
   Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release */

int __cdecl initialize_environment_by_cloning_nolock<char>(void)

{
  int iVar1;
  longlong lVar2;
  longlong *plVar3;
  
  plVar3 = DAT_1802335e0;
  if (DAT_1802335e0 == (longlong *)0x0) {
LAB_18019a9db:
    iVar1 = -1;
  }
  else {
    for (; *plVar3 != 0; plVar3 = plVar3 + 1) {
      iVar1 = __acrt_WideCharToMultiByte(0,0,*plVar3,0xffffffff,0,0,0,0);
      if (iVar1 == 0) goto LAB_18019a9db;
      lVar2 = _calloc_base((longlong)iVar1);
      if (lVar2 == 0) {
LAB_18019aa80:
        _free_base(lVar2);
        goto LAB_18019a9db;
      }
      iVar1 = __acrt_WideCharToMultiByte(0,0,*plVar3,0xffffffff,lVar2,iVar1,0,0);
      if (iVar1 == 0) goto LAB_18019aa80;
      thunk_FUN_1801a6a58();
      _free_base();
    }
    iVar1 = 0;
  }
  return iVar1;
}



// ==== uninitialize_environment_internal<> @ 18019aa90 ====

/* Library Function - Multiple Matches With Same Base Name
    void __cdecl uninitialize_environment_internal<char>(char * __ptr64 * __ptr64 & __ptr64)
    void __cdecl uninitialize_environment_internal<wchar_t>(wchar_t * __ptr64 * __ptr64 & __ptr64)
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

void uninitialize_environment_internal<>(longlong *param_1)

{
  if (*param_1 != DAT_1802335f0) {
    free_environment<>();
  }
  return;
}



// ==== uninitialize_environment_internal<> @ 18019aaac ====

/* Library Function - Multiple Matches With Same Base Name
    void __cdecl uninitialize_environment_internal<char>(char * __ptr64 * __ptr64 & __ptr64)
    void __cdecl uninitialize_environment_internal<wchar_t>(wchar_t * __ptr64 * __ptr64 & __ptr64)
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

void uninitialize_environment_internal<>(longlong *param_1)

{
  if (*param_1 != DAT_1802335e8) {
    free_environment<>();
  }
  return;
}



// ==== __dcrt_get_or_create_narrow_environment_nolock @ 18019aac8 ====

/* Library Function - Single Match
    __dcrt_get_or_create_narrow_environment_nolock
   
   Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release */

longlong __dcrt_get_or_create_narrow_environment_nolock(void)

{
  int iVar1;
  longlong lVar2;
  
  if (DAT_1802335d8 != 0) {
    return DAT_1802335d8;
  }
  if ((DAT_1802335e0 == 0) ||
     ((iVar1 = common_initialize_environment_nolock<char>(), iVar1 != 0 &&
      (iVar1 = initialize_environment_by_cloning_nolock<char>(), iVar1 != 0)))) {
    lVar2 = 0;
  }
  else {
    lVar2 = DAT_1802335d8;
  }
  return lVar2;
}



// ==== __dcrt_uninitialize_environments_nolock @ 18019ab04 ====

/* Library Function - Single Match
    __dcrt_uninitialize_environments_nolock
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

void __dcrt_uninitialize_environments_nolock(void)

{
  uninitialize_environment_internal<>(&DAT_1802335d8);
  uninitialize_environment_internal<>(&DAT_1802335e0);
  free_environment<>(DAT_1802335f0);
  free_environment<>(DAT_1802335e8);
  return;
}



// ==== common_initialize_environment_nolock<char> @ 18019ab3c ====

int __cdecl common_initialize_environment_nolock<char>(void)

{
  longlong lVar1;
  longlong lVar2;
  int iVar3;
  
  iVar3 = 0;
  if (DAT_1802335d8 == 0) {
    __acrt_initialize_multibyte();
    lVar1 = __dcrt_get_narrow_environment_from_os();
    if (lVar1 == 0) {
      iVar3 = -1;
    }
    else {
      lVar2 = FUN_18019a870(lVar1);
      if (lVar2 == 0) {
        iVar3 = -1;
      }
      else {
        DAT_1802335d8 = lVar2;
        DAT_1802335f0 = lVar2;
      }
      _free_base(0);
    }
    _free_base(lVar1);
  }
  else {
    iVar3 = 0;
  }
  return iVar3;
}



// ==== __dcrt_get_narrow_environment_from_os @ 1801a6954 ====

/* Library Function - Single Match
    __dcrt_get_narrow_environment_from_os
   
   Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release */

longlong __dcrt_get_narrow_environment_from_os(void)

{
  WCHAR WVar1;
  int iVar2;
  LPWCH pWVar3;
  longlong lVar4;
  WCHAR *pWVar5;
  ulonglong uVar6;
  longlong lVar7;
  
  pWVar3 = GetEnvironmentStringsW();
  if (pWVar3 != (LPWCH)0x0) {
    WVar1 = *pWVar3;
    pWVar5 = pWVar3;
    while (WVar1 != L'\0') {
      lVar4 = -1;
      do {
        lVar7 = lVar4;
        lVar4 = lVar7 + 1;
      } while (pWVar5[lVar4] != L'\0');
      pWVar5 = pWVar5 + lVar7 + 2;
      WVar1 = *pWVar5;
    }
    uVar6 = (longlong)pWVar5 + (2 - (longlong)pWVar3) >> 1;
    iVar2 = __acrt_WideCharToMultiByte(0,0,pWVar3,uVar6 & 0xffffffff,0,0,0,0);
    if (iVar2 != 0) {
      lVar4 = _malloc_base((longlong)iVar2);
      if ((lVar4 == 0) ||
         (iVar2 = __acrt_WideCharToMultiByte(0,0,pWVar3,uVar6 & 0xffffffff,lVar4,iVar2,0,0),
         iVar2 == 0)) {
        lVar7 = 0;
      }
      else {
        lVar7 = lVar4;
        lVar4 = 0;
      }
      _free_base(lVar4);
      goto LAB_1801a6a29;
    }
  }
  lVar7 = 0;
LAB_1801a6a29:
  if (pWVar3 != (LPWCH)0x0) {
    FreeEnvironmentStringsW(pWVar3);
  }
  return lVar7;
}



// ==== common_getenv_nolock<char> @ 1801ab6a0 ====

/* Library Function - Single Match
    char * __ptr64 __cdecl common_getenv_nolock<char>(char const * __ptr64 const)
   
   Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release */

char * __cdecl common_getenv_nolock<char>(char *param_1)

{
  int iVar1;
  longlong *plVar2;
  char *_Str1;
  ulonglong uVar3;
  ulonglong _MaxCount;
  
  plVar2 = (longlong *)__dcrt_get_or_create_narrow_environment_nolock();
  if ((plVar2 != (longlong *)0x0) && (param_1 != (char *)0x0)) {
    _MaxCount = 0xffffffffffffffff;
    do {
      _MaxCount = _MaxCount + 1;
    } while (param_1[_MaxCount] != '\0');
    _Str1 = (char *)*plVar2;
    while (_Str1 != (char *)0x0) {
      uVar3 = 0xffffffffffffffff;
      do {
        uVar3 = uVar3 + 1;
      } while (_Str1[uVar3] != '\0');
      if (((_MaxCount < uVar3) && (_Str1[_MaxCount] == '=')) &&
         (iVar1 = _strnicoll(_Str1,param_1,_MaxCount), iVar1 == 0)) {
        return (char *)(*plVar2 + 1 + _MaxCount);
      }
      plVar2 = plVar2 + 1;
      _Str1 = (char *)*plVar2;
    }
  }
  return (char *)0x0;
}



// ==== __acrt_fenv_get_control @ 1801ac9ac ====

/* Library Function - Single Match
    __acrt_fenv_get_control
   
   Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release */

uint __acrt_fenv_get_control(void)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = (ushort)MXCSR & 0x8040;
  if (uVar1 == 0x8000) {
    uVar4 = 0xc00;
  }
  else if (uVar1 == 0x40) {
    uVar4 = 0x800;
  }
  else {
    uVar4 = 0;
    if (uVar1 == 0x8040) {
      uVar4 = 0x400;
    }
  }
  uVar2 = MXCSR & 0x6000;
  if (uVar2 == 0) {
    uVar3 = 0;
  }
  else if (uVar2 == 0x2000) {
    uVar3 = 0x100;
  }
  else if (uVar2 == 0x4000) {
    uVar3 = 0x200;
  }
  else {
    uVar3 = 0x300;
    if (uVar2 != 0x6000) {
      uVar3 = 0;
    }
  }
  uVar2 = (MXCSR >> 8 & 1) << 5 | (MXCSR >> 7 & 1) << 4 | (MXCSR >> 9 & 1) << 3 |
          (MXCSR >> 10 & 1) << 2 | (MXCSR >> 0xb & 1) * 2 | MXCSR >> 0xc & 1;
  return uVar3 << 0x16 | uVar2 << 0x18 | uVar2 | uVar3 | uVar4;
}



// ==== __acrt_fenv_get_status @ 1801acaa0 ====

/* Library Function - Single Match
    __acrt_fenv_get_status
   
   Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release */

uint __acrt_fenv_get_status(void)

{
  uint uVar1;
  
  uVar1 = MXCSR & 0x3f;
  uVar1 = (uVar1 >> 1 & 1) << 5 | (uVar1 >> 2 & 1) << 3 | (uVar1 >> 3 & 1) << 2 |
          (uVar1 >> 4 & 1) * 2 | (MXCSR & 1) << 4 | uVar1 >> 5;
  return uVar1 << 0x18 | uVar1;
}



// ==== __acrt_fenv_set_control @ 1801acaf4 ====

/* Library Function - Single Match
    __acrt_fenv_set_control
   
   Library: Visual Studio 2017 Release */

void __acrt_fenv_set_control(uint param_1)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  uint uVar7;
  ushort uVar8;
  ushort uVar9;
  ushort uVar10;
  
  uVar7 = param_1 >> 2;
  uVar6 = 0x400;
  uVar3 = param_1 & 0xc00;
  uVar10 = 0x800;
  if (uVar3 == 0x400) {
    uVar8 = 0x8040;
  }
  else if (uVar3 == 0x800) {
    uVar8 = 0x40;
  }
  else if (uVar3 == 0xc00) {
    uVar8 = 0x8000;
  }
  else {
    uVar8 = 0;
  }
  uVar5 = 0x100;
  uVar9 = 0x200;
  uVar3 = (param_1 & 0xc0000000) >> 0x16;
  if (uVar3 != 0) {
    if (uVar3 == 0x100) {
      uVar2 = 0x2000;
      goto LAB_1801acb98;
    }
    if (uVar3 == 0x200) {
      uVar2 = 0x4000;
      goto LAB_1801acb98;
    }
    if (uVar3 == 0x300) {
      uVar2 = 0x6000;
      goto LAB_1801acb98;
    }
  }
  uVar2 = 0;
LAB_1801acb98:
  if ((uVar7 & 0x400000) == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = 0x1000;
  }
  if ((uVar7 & 0x800000) == 0) {
    uVar10 = 0;
  }
  if ((uVar7 & 0x1000000) == 0) {
    uVar6 = 0;
  }
  if ((uVar7 & 0x2000000) == 0) {
    uVar9 = 0;
  }
  if ((uVar7 & 0x4000000) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x80;
  }
  if ((uVar7 & 0x8000000) == 0) {
    uVar5 = 0;
  }
  MXCSR = MXCSR & 0xffff003f |
          (uint)(ushort)(uVar4 | uVar10 | uVar6 | uVar9 | uVar1 | uVar5 | uVar2 | uVar8);
  return;
}



// ==== __acrt_fenv_set_status @ 1801acc3c ====

/* Library Function - Single Match
    __acrt_fenv_set_status
   
   Library: Visual Studio 2017 Release */

void __acrt_fenv_set_status(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 >> 0x18 & 0x3f;
  MXCSR = MXCSR & 0xffffffc0 |
          (param_1 >> 0x18 & 1) << 5 | (uVar1 >> 1 & 1) << 4 | (uVar1 >> 2 & 1) << 3 |
          (uVar1 >> 3 & 1) << 2 | uVar1 >> 4 & 1 | (uVar1 >> 5) * 2;
  return;
}



// ==== __acrt_SetEnvironmentVariableA @ 1801ad6cc ====

/* Library Function - Single Match
    __acrt_SetEnvironmentVariableA
   
   Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release */

BOOL __acrt_SetEnvironmentVariableA(char *param_1,char *param_2)

{
  int iVar1;
  BOOL BVar2;
  uint uVar3;
  LPCWSTR pWVar4;
  uint uVar5;
  longlong local_98;
  longlong local_90;
  char local_80;
  undefined8 local_78;
  undefined8 local_70;
  LPCWSTR local_68;
  undefined8 local_60;
  undefined8 local_58;
  char local_50;
  undefined8 local_48;
  undefined8 local_40;
  LPCWSTR local_38;
  undefined8 local_30;
  undefined8 local_28;
  char local_20;
  
  local_48 = 0;
  local_40 = 0;
  local_38 = (LPCWSTR)0x0;
  local_30 = 0;
  local_28 = 0;
  local_20 = '\0';
  local_78 = 0;
  local_70 = 0;
  local_68 = (LPCWSTR)0x0;
  local_60 = 0;
  local_58 = 0;
  local_50 = '\0';
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_98,(__crt_locale_pointers *)0x0);
  uVar3 = 0xfde9;
  if (*(int *)(local_90 + 0xc) == 0xfde9) {
    if (local_80 != '\0') {
      *(uint *)(local_98 + 0x3a8) = *(uint *)(local_98 + 0x3a8) & 0xfffffffd;
    }
    uVar5 = 0xfde9;
  }
  else {
    iVar1 = __acrt_AreFileApisANSI();
    if (iVar1 == 0) {
      if (local_80 != '\0') {
        *(uint *)(local_98 + 0x3a8) = *(uint *)(local_98 + 0x3a8) & 0xfffffffd;
      }
      uVar5 = 1;
    }
    else {
      if (local_80 != '\0') {
        *(uint *)(local_98 + 0x3a8) = *(uint *)(local_98 + 0x3a8) & 0xfffffffd;
      }
      uVar5 = 0;
    }
  }
  iVar1 = __acrt_mbs_to_wcs_cp<__crt_win32_buffer_internal_dynamic_resizing>
                    (param_1,(__crt_win32_buffer<wchar_t,__crt_win32_buffer_internal_dynamic_resizing>
                              *)&local_48,uVar5);
  pWVar4 = (LPCWSTR)0x0;
  if (iVar1 == 0) {
    _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_98,(__crt_locale_pointers *)0x0);
    if (*(int *)(local_90 + 0xc) == 0xfde9) {
      if (local_80 != '\0') {
        *(uint *)(local_98 + 0x3a8) = *(uint *)(local_98 + 0x3a8) & 0xfffffffd;
      }
    }
    else {
      iVar1 = __acrt_AreFileApisANSI();
      if (iVar1 == 0) {
        if (local_80 != '\0') {
          *(uint *)(local_98 + 0x3a8) = *(uint *)(local_98 + 0x3a8) & 0xfffffffd;
        }
        uVar3 = 1;
      }
      else {
        if (local_80 != '\0') {
          *(uint *)(local_98 + 0x3a8) = *(uint *)(local_98 + 0x3a8) & 0xfffffffd;
        }
        uVar3 = 0;
      }
    }
    iVar1 = __acrt_mbs_to_wcs_cp<__crt_win32_buffer_internal_dynamic_resizing>
                      (param_2,(__crt_win32_buffer<wchar_t,__crt_win32_buffer_internal_dynamic_resizing>
                                *)&local_78,uVar3);
    pWVar4 = local_68;
    if (iVar1 == 0) {
      BVar2 = SetEnvironmentVariableW(local_38,local_68);
      goto LAB_1801ad827;
    }
  }
  BVar2 = 0;
LAB_1801ad827:
  if (local_50 != '\0') {
    _free_base(pWVar4);
  }
  if (local_20 != '\0') {
    _free_base(local_38);
  }
  return BVar2;
}



// ==== fegetenv @ 1801ada7c ====

/* Library Function - Single Match
    fegetenv
   
   Library: Visual Studio 2017 Release */

undefined8 fegetenv(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = __acrt_fenv_get_control();
  *param_1 = uVar1;
  uVar1 = __acrt_fenv_get_status();
  param_1[1] = uVar1;
  return 0;
}



// ==== fesetenv @ 1801ada9c ====

/* Library Function - Single Match
    fesetenv
   
   Library: Visual Studio 2017 Release */

undefined8 fesetenv(int *param_1)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 local_res8;
  
  __acrt_fenv_set_control(*param_1);
  __acrt_fenv_set_status(param_1[1]);
  local_res8 = 0;
  iVar1 = fegetenv(&local_res8);
  if (((iVar1 == 0) && (*param_1 == (int)local_res8)) && (param_1[1] == local_res8._4_4_)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



