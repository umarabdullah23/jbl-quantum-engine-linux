// ==== FUN_180083740 @ 180083740 ====

undefined8 * FUN_180083740(undefined8 *param_1,undefined2 param_2)

{
  *param_1 = BaseRacePacket::vftable;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0xf;
  *(undefined1 *)(param_1 + 0x12) = 0;
  *(undefined1 *)((longlong)param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 0x16) = 0;
  *(undefined1 *)(param_1 + 10) = 0;
  *(undefined2 *)(param_1 + 0x11) = 0;
  *(undefined2 *)((longlong)param_1 + 0xb4) = 0;
  *(undefined4 *)((longlong)param_1 + 0x3a) = 0x5b5a;
  *(undefined4 *)(param_1 + 8) = 7;
  param_1[9] = 6;
  *(undefined4 *)(param_1 + 0x17) = 4;
  *(undefined4 *)(param_1 + 0x18) = 2000;
  *(undefined8 *)((longlong)param_1 + 0xc4) = 3;
  *(undefined4 *)((longlong)param_1 + 0xbc) = 0xffffffff;
  *(undefined2 *)(param_1 + 7) = param_2;
  return param_1;
}



// ==== FUN_180083810 @ 180083810 ====

undefined8 FUN_180083810(undefined8 param_1,ulonglong param_2)

{
  FUN_180083850();
  if ((param_2 & 1) != 0) {
    thunk_FUN_180190730(param_1,0xd0);
  }
  return param_1;
}



// ==== FUN_180083850 @ 180083850 ====

void FUN_180083850(undefined8 *param_1)

{
  longlong lVar1;
  longlong lVar2;
  ulonglong uVar3;
  longlong local_18 [2];
  
  *param_1 = BaseRacePacket::vftable;
  lVar1 = param_1[5];
  if (param_1[4] != lVar1) {
    FUN_18002ce60(param_1[4],lVar1);
    lVar1 = param_1[4];
    param_1[5] = lVar1;
  }
  if (lVar1 != param_1[6]) {
    if (param_1[4] == lVar1) {
      FUN_18002c240(param_1 + 4);
    }
    else {
      local_18[0] = lVar1 - param_1[4] >> 4;
      FUN_18004c510(param_1 + 4,local_18);
    }
  }
  FUN_180017790(param_1 + 0x12);
  lVar1 = param_1[0xe];
  if (lVar1 != 0) {
    uVar3 = param_1[0x10] - lVar1;
    lVar2 = lVar1;
    if (0xfff < uVar3) {
      uVar3 = uVar3 + 0x27;
      lVar2 = *(longlong *)(lVar1 + -8);
      lVar1 = lVar1 - lVar2;
      if (0x1f < lVar1 - 8U) goto LAB_1800839b4;
    }
    thunk_FUN_180190730(lVar2,uVar3);
    param_1[0xe] = 0;
    param_1[0xf] = 0;
    param_1[0x10] = 0;
  }
  lVar1 = param_1[0xb];
  if (lVar1 != 0) {
    uVar3 = param_1[0xd] - lVar1;
    lVar2 = lVar1;
    if (0xfff < uVar3) {
      uVar3 = uVar3 + 0x27;
      lVar2 = *(longlong *)(lVar1 + -8);
      lVar1 = lVar1 - lVar2;
      if (0x1f < lVar1 - 8U) goto LAB_1800839b4;
    }
    thunk_FUN_180190730(lVar2,uVar3);
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    param_1[0xd] = 0;
  }
  FUN_18002c240(param_1 + 4);
  lVar1 = param_1[1];
  if (lVar1 != 0) {
    lVar2 = lVar1;
    if (0xfff < (ulonglong)(param_1[3] - lVar1)) {
      uVar3 = (param_1[3] - lVar1) + 0x27;
      lVar2 = *(longlong *)(lVar1 + -8);
      lVar1 = lVar1 - lVar2;
      if (0x1f < lVar1 - 8U) {
LAB_1800839b4:
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(lVar1,uVar3);
      }
    }
    thunk_FUN_180190730(lVar2);
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
  }
  return;
}



// ==== FUN_1800839c0 @ 1800839c0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

longlong * FUN_1800839c0(longlong param_1,longlong *param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  longlong *plVar3;
  int *piVar4;
  longlong *plVar5;
  int iVar6;
  undefined2 uVar7;
  uint uVar8;
  byte *pbVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  bool bVar12;
  short sVar13;
  short *psVar14;
  longlong *plVar15;
  longlong lVar16;
  undefined8 uVar17;
  undefined8 *puVar18;
  short *psVar19;
  undefined1 *puVar20;
  longlong lVar21;
  undefined2 *puVar22;
  undefined2 *puVar23;
  short *psVar24;
  undefined4 extraout_XMM0_Da;
  undefined4 uVar25;
  undefined1 auStack_158 [32];
  undefined8 local_138;
  longlong local_130;
  longlong local_128;
  byte local_118 [2];
  undefined2 local_116;
  undefined1 local_114;
  longlong *local_110;
  undefined4 local_108;
  longlong *local_100;
  undefined1 local_f8 [32];
  undefined1 local_d8 [32];
  undefined1 local_b8;
  undefined1 local_b7 [7];
  short *local_b0;
  short *psStack_a8;
  longlong local_a0;
  undefined2 *local_98;
  undefined2 *puStack_90;
  longlong local_88;
  short *local_80;
  longlong *plStack_78;
  longlong local_70;
  undefined4 uStack_68;
  undefined4 uStack_64;
  ulonglong local_60;
  longlong *local_58;
  ulonglong local_40;
  
  local_40 = DAT_180225100 ^ (ulonglong)auStack_158;
  local_108 = 0;
  plVar1 = (longlong *)(param_1 + 8);
  plVar2 = (longlong *)(param_1 + 0x70);
  plVar15 = (longlong *)(param_1 + 0x10);
  plVar3 = (longlong *)(param_1 + 0x80);
  local_110 = plVar15;
  local_100 = param_2;
  if (*(int *)(param_1 + 0xb0) - 2U < 2) {
    local_60 = (*plVar15 - *plVar1) + 0x11;
    if ((ulonglong)(*plVar3 - *plVar2) < local_60) goto joined_r0x000180083b33;
  }
  else {
    local_60 = (*plVar15 - *plVar1) + 9;
    if ((ulonglong)(*plVar3 - *plVar2) < local_60) {
joined_r0x000180083b33:
      if (0x7fffffffffffffff < local_60) {
                    /* WARNING: Subroutine does not return */
        FUN_180017770();
      }
      FUN_180042ed0(plVar2,&local_60);
    }
  }
  local_116 = 2;
  if (*plVar1 != *plVar15) {
    local_116 = ((short)*plVar15 - (short)*plVar1) + 2;
  }
  sVar13 = local_116;
  local_b0 = (short *)0x0;
  psStack_a8 = (short *)0x0;
  local_a0 = 0;
  local_110 = plVar15;
  FUN_18001b120(&local_b0);
  psVar24 = local_b0;
  *local_b0 = sVar13;
  psStack_a8 = local_b0 + 1;
  uVar7 = *(undefined2 *)(param_1 + 0xb4);
  local_98 = (undefined2 *)0x0;
  puStack_90 = (undefined2 *)0x0;
  local_88 = 0;
  FUN_18001b120(&local_98,2);
  puVar22 = local_98;
  *local_98 = uVar7;
  puStack_90 = local_98 + 1;
  uVar8 = *(uint *)(param_1 + 0xb0);
  if ((uVar8 < 8) && ((0x85U >> (uVar8 & 0x1f) & 1) != 0)) {
    local_118[0] = 0;
    puVar20 = *(undefined1 **)(param_1 + 0x78);
    if (puVar20 == (undefined1 *)*plVar3) {
      FUN_18001b340(plVar2,puVar20,local_118);
    }
    else {
      *puVar20 = 0;
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
    }
    goto LAB_180083cf3;
  }
  if ((uVar8 - 1 & 0xfffffffd) != 0) goto LAB_180083cf3;
  uVar17 = FUN_1801501a0();
  plVar15 = (longlong *)FUN_180150e70(uVar17,&local_80,*(undefined2 *)(param_1 + 0x38));
  bVar12 = false;
  local_108 = 0xc1;
  if (*(int *)(*plVar15 + 0x270) == 1) {
LAB_180083bb8:
    local_118[0] = 1;
  }
  else {
    uVar17 = FUN_1801501a0();
    plVar15 = (longlong *)FUN_180150e70(uVar17,&local_60,*(undefined2 *)(param_1 + 0x38));
    bVar12 = true;
    local_118[0] = 0;
    if (*(int *)(*plVar15 + 0x270) == 4) goto LAB_180083bb8;
  }
  if ((bVar12) && (local_58 != (longlong *)0x0)) {
    LOCK();
    plVar15 = local_58 + 1;
    lVar16 = *plVar15;
    *(int *)plVar15 = (int)*plVar15 + -1;
    UNLOCK();
    if ((int)lVar16 == 1) {
      (**(code **)*local_58)(local_58);
      LOCK();
      piVar4 = (int *)((longlong)local_58 + 0xc);
      iVar6 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar6 == 1) {
        (**(code **)(*local_58 + 8))(local_58);
      }
    }
  }
  plVar15 = plStack_78;
  if (plStack_78 != (longlong *)0x0) {
    LOCK();
    plVar5 = plStack_78 + 1;
    lVar16 = *plVar5;
    *(int *)plVar5 = (int)*plVar5 + -1;
    UNLOCK();
    if ((int)lVar16 == 1) {
      (**(code **)*plStack_78)(plStack_78);
      LOCK();
      piVar4 = (int *)((longlong)plVar15 + 0xc);
      iVar6 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar6 == 1) {
        (**(code **)(*plVar15 + 8))(plVar15);
      }
    }
  }
  if (local_118[0] == 0) {
    uVar17 = FUN_1801501a0();
    plVar15 = (longlong *)FUN_180150e70(uVar17,&local_80,*(undefined2 *)(param_1 + 0x38));
    if (*(undefined1 **)(param_1 + 0x78) == *(undefined1 **)(param_1 + 0x80)) {
      FUN_18001b340(param_1 + 0x70);
    }
    else {
      **(undefined1 **)(param_1 + 0x78) = *(undefined1 *)(*plVar15 + 0x243);
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
    }
    plVar15 = plStack_78;
    if (plStack_78 != (longlong *)0x0) {
      LOCK();
      plVar5 = plStack_78 + 1;
      lVar16 = *plVar5;
      *(int *)plVar5 = (int)*plVar5 + -1;
      UNLOCK();
      if ((int)lVar16 == 1) {
        (**(code **)*plStack_78)(plStack_78);
        LOCK();
        piVar4 = (int *)((longlong)plVar15 + 0xc);
        iVar6 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar6 == 1) {
          (**(code **)(*plVar15 + 8))(plVar15);
        }
      }
    }
  }
  else {
    local_118[0] = *(byte *)(param_1 + 0x38);
    pbVar9 = *(byte **)(param_1 + 0x78);
    if (pbVar9 == *(byte **)(param_1 + 0x80)) {
      FUN_18001b340(param_1 + 0x70,pbVar9,local_118);
    }
    else {
      *pbVar9 = local_118[0];
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
    }
  }
  puVar22 = local_98;
  psVar24 = local_b0;
LAB_180083cf3:
  if (*(int *)(param_1 + 0xb0) - 2U < 2) {
    local_116 = local_116 + 8;
    local_80 = (short *)0x0;
    plStack_78 = (longlong *)0x0;
    local_70 = 0;
    FUN_18001b120(&local_80,2);
    psVar14 = local_80;
    *local_80 = local_116;
    plStack_78 = (longlong *)(local_80 + 1);
    lVar16 = FUN_1801501a0();
    local_114 = *(undefined1 *)(lVar16 + 0x42);
    local_b7[0] = *(undefined1 *)(lVar16 + 0x43);
    local_116 = CONCAT11(local_116._1_1_,local_b7[0]);
    local_118[0] = *(byte *)(param_1 + 0x89) | 5;
    pbVar9 = *(byte **)(param_1 + 0x78);
    local_b8 = local_114;
    if (pbVar9 == (byte *)*plVar3) {
      uVar25 = FUN_18001b340(plVar2,pbVar9,local_118);
    }
    else {
      *pbVar9 = local_118[0];
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
      uVar25 = extraout_XMM0_Da;
    }
    local_118[0] = 0x5a;
    puVar20 = *(undefined1 **)(param_1 + 0x78);
    if (puVar20 == (undefined1 *)*plVar3) {
      uVar25 = FUN_18001b340(plVar2,puVar20,local_118);
    }
    else {
      *puVar20 = 0x5a;
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
    }
    puVar20 = *(undefined1 **)(param_1 + 0x78);
    if (puVar20 == (undefined1 *)*plVar3) {
      uVar25 = FUN_18001b340(plVar2,puVar20,psVar14);
    }
    else {
      *puVar20 = (char)*psVar14;
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
    }
    if (*(undefined1 **)(param_1 + 0x78) == (undefined1 *)*plVar3) {
      uVar25 = FUN_18001b340(plVar2);
    }
    else {
      **(undefined1 **)(param_1 + 0x78) = *(undefined1 *)((longlong)psVar14 + 1);
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
    }
    local_118[0] = 1;
    puVar20 = *(undefined1 **)(param_1 + 0x78);
    if (puVar20 == (undefined1 *)*plVar3) {
      uVar25 = FUN_18001b340(plVar2,puVar20,local_118);
    }
    else {
      *puVar20 = 1;
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
    }
    local_118[0] = 0xd;
    puVar20 = *(undefined1 **)(param_1 + 0x78);
    if (puVar20 == (undefined1 *)*plVar3) {
      uVar25 = FUN_18001b340(plVar2,puVar20,local_118);
    }
    else {
      *puVar20 = 0xd;
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
    }
    puVar20 = *(undefined1 **)(param_1 + 0x78);
    if (puVar20 == (undefined1 *)*plVar3) {
      uVar25 = FUN_18001b340(plVar2,puVar20,&local_b8);
    }
    else {
      *puVar20 = local_114;
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
    }
    puVar20 = *(undefined1 **)(param_1 + 0x78);
    if (puVar20 == (undefined1 *)*plVar3) {
      uVar25 = FUN_18001b340(plVar2,puVar20,local_b7);
    }
    else {
      *puVar20 = (undefined1)local_116;
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
    }
    if (psVar14 != (short *)0x0) {
      psVar19 = psVar14;
      if (0xfff < (ulonglong)(local_70 - (longlong)psVar14)) {
        psVar19 = *(short **)(psVar14 + -4);
        if (0x1f < (ulonglong)((longlong)psVar14 + (-8 - (longlong)psVar19))) {
                    /* WARNING: Subroutine does not return */
          FUN_18018f678(uVar25,(local_70 - (longlong)psVar14) + 0x27);
        }
      }
      thunk_FUN_180190730(psVar19);
    }
  }
  local_116 = CONCAT11(local_116._1_1_,*(byte *)(param_1 + 0x89)) | 5;
  pbVar9 = *(byte **)(param_1 + 0x78);
  if (pbVar9 == (byte *)*plVar3) {
    FUN_18001b340(plVar2,pbVar9,&local_116);
  }
  else {
    *pbVar9 = *(byte *)(param_1 + 0x89) | 5;
    *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
  }
  if (*(undefined1 **)(param_1 + 0x78) == (undefined1 *)*plVar3) {
    FUN_18001b340(plVar2);
  }
  else {
    **(undefined1 **)(param_1 + 0x78) = *(undefined1 *)(param_1 + 0x3a);
    *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
  }
  puVar20 = *(undefined1 **)(param_1 + 0x78);
  if (puVar20 == (undefined1 *)*plVar3) {
    FUN_18001b340(plVar2,puVar20,psVar24);
  }
  else {
    *puVar20 = (char)*psVar24;
    *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
  }
  if (*(undefined1 **)(param_1 + 0x78) == (undefined1 *)*plVar3) {
    FUN_18001b340(plVar2);
  }
  else {
    **(undefined1 **)(param_1 + 0x78) = *(undefined1 *)((longlong)psVar24 + 1);
    *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
  }
  puVar20 = *(undefined1 **)(param_1 + 0x78);
  if (puVar20 == (undefined1 *)*plVar3) {
    FUN_18001b340(plVar2,puVar20,puVar22);
  }
  else {
    *puVar20 = *(undefined1 *)puVar22;
    *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
  }
  if (*(undefined1 **)(param_1 + 0x78) == (undefined1 *)*plVar3) {
    FUN_18001b340(plVar2);
  }
  else {
    **(undefined1 **)(param_1 + 0x78) = *(undefined1 *)((longlong)puVar22 + 1);
    *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
  }
  puVar10 = (undefined1 *)*local_110;
  for (puVar20 = (undefined1 *)*plVar1; puVar20 != puVar10; puVar20 = puVar20 + 1) {
    local_116._1_1_ = (undefined1)(local_116 >> 8);
    local_116 = CONCAT11(local_116._1_1_,*puVar20);
    puVar11 = *(undefined1 **)(param_1 + 0x78);
    if (puVar11 == (undefined1 *)*plVar3) {
      FUN_18001b340(plVar2,puVar11,&local_116);
    }
    else {
      *puVar11 = *puVar20;
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
    }
  }
  uVar17 = FUN_1800026e0(local_d8,plVar2);
  local_130 = param_1 + 0x90;
  local_128 = *(longlong *)(param_1 + 0xa0);
  if (0x7fffffffffffffffU - local_128 < 6) {
                    /* WARNING: Subroutine does not return */
    FUN_1800013a0();
  }
  if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
    local_130 = *(longlong *)local_130;
  }
  local_138 = 6;
  FUN_18001ad90(local_f8);
  puVar18 = (undefined8 *)
            FUN_180017990(local_f8,", step = genRawRacePacket(), variable = packet: ",0x30);
  local_80 = (short *)*puVar18;
  plStack_78 = (longlong *)puVar18[1];
  uVar25 = *(undefined4 *)(puVar18 + 2);
  local_70 = puVar18[2];
  uStack_68 = *(undefined4 *)(puVar18 + 3);
  uStack_64 = *(undefined4 *)((longlong)puVar18 + 0x1c);
  puVar18[2] = 0;
  puVar18[3] = 0xf;
  *(undefined1 *)puVar18 = 0;
  FUN_18001aba0(&local_60,uVar25,&local_80,uVar17);
  uVar7 = *(undefined2 *)(param_1 + 0x38);
  uVar17 = FUN_180073fc0();
  FUN_180074040(uVar17,uVar7,2,&local_60);
  FUN_180017790(&local_60);
  FUN_180017790(&local_80);
  FUN_180017790(local_f8);
  uVar25 = FUN_180017790(local_d8);
  plVar1 = local_100;
  *local_100 = 0;
  local_100[1] = 0;
  local_100[2] = 0;
  if (*(longlong *)(param_1 + 0x78) != *plVar2) {
    if (0x7fffffffffffffff < (ulonglong)(*(longlong *)(param_1 + 0x78) - *plVar2)) {
                    /* WARNING: Subroutine does not return */
      FUN_180017770();
    }
    FUN_18001b120(local_100);
    lVar16 = *plVar1;
    lVar21 = *(longlong *)(param_1 + 0x78) - *plVar2;
    uVar25 = FUN_1801afa50(lVar16,*plVar2,lVar21);
    plVar1[1] = lVar21 + lVar16;
  }
  if (puVar22 != (undefined2 *)0x0) {
    puVar23 = puVar22;
    if (0xfff < (ulonglong)(local_88 - (longlong)puVar22)) {
      puVar23 = *(undefined2 **)(puVar22 + -4);
      if ((undefined1 *)0x1f < (undefined1 *)((longlong)puVar22 + (-8 - (longlong)puVar23))) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(uVar25,(local_88 - (longlong)puVar22) + 0x27);
      }
    }
    thunk_FUN_180190730(puVar23);
  }
  if (local_b0 != (short *)0x0) {
    if (0xfff < (ulonglong)(local_a0 - (longlong)local_b0)) {
      if ((undefined1 *)0x1f <
          (undefined1 *)((longlong)local_b0 + (-8 - *(longlong *)(local_b0 + -4)))) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(*(longlong *)(local_b0 + -4),(local_a0 - (longlong)local_b0) + 0x27);
      }
    }
    thunk_FUN_180190730();
  }
  return plVar1;
}



// ==== FUN_1800841c0 @ 1800841c0 ====

void FUN_1800841c0(longlong param_1,undefined8 *param_2)

{
  int *piVar1;
  longlong *plVar2;
  int iVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  longlong lVar6;
  
  puVar4 = *(undefined8 **)(param_1 + 0x28);
  if (puVar4 == *(undefined8 **)(param_1 + 0x30)) {
    FUN_18004c850(param_1 + 0x20,puVar4,param_2);
  }
  else {
    *puVar4 = 0;
    puVar4[1] = 0;
    if (param_2[1] != 0) {
      LOCK();
      piVar1 = (int *)(param_2[1] + 8);
      *piVar1 = *piVar1 + 1;
      UNLOCK();
    }
    *puVar4 = *param_2;
    puVar4[1] = param_2[1];
    *(longlong *)(param_1 + 0x28) = *(longlong *)(param_1 + 0x28) + 0x10;
  }
  plVar5 = (longlong *)param_2[1];
  if (plVar5 != (longlong *)0x0) {
    LOCK();
    plVar2 = plVar5 + 1;
    lVar6 = *plVar2;
    *(int *)plVar2 = (int)*plVar2 + -1;
    UNLOCK();
    if ((int)lVar6 == 1) {
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



// ==== FUN_180084260 @ 180084260 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ulonglong FUN_180084260(longlong param_1,longlong *param_2)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  undefined2 uVar6;
  ushort uVar7;
  ulonglong uVar8;
  undefined4 uVar9;
  bool bVar10;
  bool bVar11;
  longlong lVar12;
  ushort *puVar13;
  undefined8 uVar14;
  undefined8 *puVar15;
  longlong *plVar16;
  ulonglong uVar17;
  longlong *plVar18;
  undefined4 *puVar19;
  longlong lVar20;
  ulonglong uVar21;
  ushort uVar22;
  uint uVar23;
  char *pcVar25;
  char *pcVar24;
  undefined1 auStack_1a8 [32];
  undefined8 local_188;
  longlong *local_180;
  longlong local_178;
  undefined8 local_168;
  undefined8 uStack_160;
  undefined8 local_158;
  undefined8 uStack_150;
  undefined1 local_148 [32];
  undefined4 local_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 local_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined1 local_108 [32];
  undefined1 local_e8 [32];
  undefined1 local_c8 [32];
  undefined1 local_a8 [32];
  longlong local_88;
  longlong *plStack_80;
  undefined8 local_78;
  longlong lStack_70;
  ushort *local_68;
  ushort *puStack_60;
  longlong local_58;
  undefined8 uStack_50;
  undefined4 local_48;
  ulonglong local_40;
  
  local_40 = DAT_180225100 ^ (ulonglong)auStack_1a8;
  local_48 = 0;
  uVar14 = FUN_1800026e0(local_a8);
  plVar16 = (longlong *)(param_1 + 0x90);
  local_178 = *(longlong *)(param_1 + 0xa0);
  if (0x7fffffffffffffffU - local_178 < 6) {
                    /* WARNING: Subroutine does not return */
    FUN_1800013a0();
  }
  local_180 = plVar16;
  if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
    local_180 = (longlong *)*plVar16;
  }
  local_188 = 6;
  FUN_18001ad90(&local_88);
  puVar15 = (undefined8 *)FUN_180017990(&local_88,", step = respParser(), variable = packet: ",0x2a)
  ;
  local_168 = *puVar15;
  uStack_160 = puVar15[1];
  uVar9 = *(undefined4 *)(puVar15 + 2);
  local_158 = puVar15[2];
  uStack_150 = puVar15[3];
  puVar15[2] = 0;
  puVar15[3] = 0xf;
  *(undefined1 *)puVar15 = 0;
  FUN_18001aba0(&local_128,uVar9,&local_168,uVar14);
  uVar6 = *(undefined2 *)(param_1 + 0x38);
  uVar14 = FUN_180073fc0();
  FUN_180074040(uVar14,uVar6,2,&local_128);
  FUN_180017790(&local_128);
  FUN_180017790(&local_168);
  FUN_180017790(&local_88);
  FUN_180017790(local_a8);
  uVar23 = *(uint *)(param_1 + 0xb0);
  pcVar24 = (char *)((longlong)&local_78 + 5);
  if ((int)uVar23 < 0) {
    uVar23 = -uVar23;
    do {
      pcVar25 = pcVar24;
      pcVar24 = pcVar25 + -1;
      *pcVar24 = (char)uVar23 + (char)((ulonglong)uVar23 / 10) * -10 + '0';
      uVar23 = (uint)((ulonglong)uVar23 / 10);
    } while (uVar23 != 0);
    pcVar24 = pcVar25 + -2;
    *pcVar24 = '-';
  }
  else {
    do {
      pcVar24 = pcVar24 + -1;
      *pcVar24 = (char)uVar23 + (char)((ulonglong)uVar23 / 10) * -10 + '0';
      uVar23 = (uint)((ulonglong)uVar23 / 10);
    } while (uVar23 != 0);
  }
  FUN_18001d100(local_148,pcVar24,(longlong)&local_78 + 5);
  if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
    FUN_1800013a0();
  }
  if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
    plVar16 = (longlong *)*plVar16;
  }
  local_188 = 6;
  local_180 = plVar16;
  local_178 = *(longlong *)(param_1 + 0xa0);
  FUN_18001ad90(&local_68);
  puVar15 = (undefined8 *)FUN_180017990(&local_68,"cmd recipient = ",0x10);
  local_168 = *puVar15;
  uStack_160 = puVar15[1];
  uVar9 = *(undefined4 *)(puVar15 + 2);
  local_158 = puVar15[2];
  uStack_150 = puVar15[3];
  puVar15[2] = 0;
  puVar15[3] = 0xf;
  *(undefined1 *)puVar15 = 0;
  FUN_18001aba0(&local_128,uVar9,&local_168,local_148);
  uVar6 = *(undefined2 *)(param_1 + 0x38);
  uVar14 = FUN_180073fc0();
  FUN_180074040(uVar14,uVar6,2,&local_128);
  FUN_180017790(&local_128);
  FUN_180017790(&local_168);
  FUN_180017790(&local_68);
  FUN_180017790(local_148);
  uVar23 = 0;
  if ((*(uint *)(param_1 + 0xb0) & 0xfffffffd) == 0) {
    if (*(char *)*param_2 != '\0') {
      plVar16 = (longlong *)(param_1 + 0x90);
      if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
        FUN_1800013a0();
      }
      if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
        plVar16 = (longlong *)*plVar16;
      }
      local_188 = 6;
      local_180 = plVar16;
      local_178 = *(longlong *)(param_1 + 0xa0);
      FUN_18001ad90(local_148);
      plVar16 = (longlong *)
                FUN_180017990(local_148,
                              ", step = respParser(), message = wrong target device byte, packet[0] is not local"
                              ,0x51);
      local_88 = *plVar16;
      plStack_80 = (longlong *)plVar16[1];
      local_78 = (longlong *)plVar16[2];
      lStack_70 = plVar16[3];
      plVar16[2] = 0;
      plVar16[3] = 0xf;
      *(undefined1 *)plVar16 = 0;
      uVar6 = *(undefined2 *)(param_1 + 0x38);
      uVar14 = FUN_180073fc0();
      FUN_180074040(uVar14,uVar6,0,&local_88);
      FUN_180017790(&local_88);
      uVar17 = FUN_180017790(local_148);
      return uVar17 & 0xffffffffffffff00;
    }
LAB_1800847fc:
    uVar23 = 1;
  }
  else if ((*(uint *)(param_1 + 0xb0) - 1 & 0xfffffffd) == 0) {
    uVar14 = FUN_1801501a0();
    plVar16 = (longlong *)FUN_180150e70(uVar14,&local_88,*(undefined2 *)(param_1 + 0x38));
    bVar10 = false;
    local_48 = 0x3fd;
    if (*(int *)(*plVar16 + 0x270) == 1) {
LAB_18008456a:
      bVar11 = true;
    }
    else {
      uVar14 = FUN_1801501a0();
      plVar16 = (longlong *)FUN_180150e70(uVar14,&local_68,*(undefined2 *)(param_1 + 0x38));
      bVar10 = true;
      if (*(int *)(*plVar16 + 0x270) == 4) goto LAB_18008456a;
      bVar11 = false;
    }
    puVar13 = puStack_60;
    if ((bVar10) && (puStack_60 != (ushort *)0x0)) {
      LOCK();
      plVar16 = (longlong *)((longlong)puStack_60 + 8);
      lVar12 = *plVar16;
      *(int *)plVar16 = (int)*plVar16 + -1;
      UNLOCK();
      if ((int)lVar12 == 1) {
        (*(code *)**(undefined8 **)puStack_60)(puStack_60);
        LOCK();
        piVar1 = (int *)((longlong)puVar13 + 0xc);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 == 1) {
          (**(code **)(*(longlong *)puVar13 + 8))(puVar13);
        }
      }
    }
    plVar16 = plStack_80;
    if (plStack_80 != (longlong *)0x0) {
      LOCK();
      plVar18 = plStack_80 + 1;
      lVar12 = *plVar18;
      *(int *)plVar18 = (int)*plVar18 + -1;
      UNLOCK();
      if ((int)lVar12 == 1) {
        (**(code **)*plStack_80)(plStack_80);
        LOCK();
        piVar1 = (int *)((longlong)plVar16 + 0xc);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 == 1) {
          (**(code **)(*plVar16 + 8))(plVar16);
        }
      }
    }
    uVar22 = *(ushort *)(param_1 + 0x38);
    if (bVar11) {
      if ((ushort)*(byte *)*param_2 != (uVar22 & 0xff)) {
        plVar16 = (longlong *)(param_1 + 0x90);
        if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
          FUN_1800013a0();
        }
        if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
          plVar16 = (longlong *)*plVar16;
        }
        local_188 = 6;
        local_180 = plVar16;
        local_178 = *(longlong *)(param_1 + 0xa0);
        FUN_18001ad90(local_148);
        plVar16 = (longlong *)
                  FUN_180017990(local_148,
                                ", step = respParser(), message = wrong target device byte, packet[0] is not remote"
                                ,0x52);
        local_88 = *plVar16;
        plStack_80 = (longlong *)plVar16[1];
        local_78 = (longlong *)plVar16[2];
        lStack_70 = plVar16[3];
        plVar16[2] = 0;
        plVar16[3] = 0xf;
        *(undefined1 *)plVar16 = 0;
        uVar6 = *(undefined2 *)(param_1 + 0x38);
        uVar14 = FUN_180073fc0();
        FUN_180074040(uVar14,uVar6,0,&local_88);
        FUN_180017790(&local_88);
        uVar17 = FUN_180017790(local_148);
        return uVar17 & 0xffffffffffffff00;
      }
    }
    else {
      uVar14 = FUN_1801501a0();
      plVar18 = (longlong *)FUN_180150e70(uVar14,&local_88,uVar22);
      plVar16 = plStack_80;
      cVar3 = *(char *)(*plVar18 + 0x243);
      cVar4 = *(char *)*param_2;
      if (plStack_80 != (longlong *)0x0) {
        LOCK();
        plVar18 = plStack_80 + 1;
        lVar12 = *plVar18;
        *(int *)plVar18 = (int)*plVar18 + -1;
        UNLOCK();
        if ((int)lVar12 == 1) {
          (**(code **)*plStack_80)(plStack_80);
          LOCK();
          piVar1 = (int *)((longlong)plVar16 + 0xc);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 == 1) {
            (**(code **)(*plVar16 + 8))(plVar16);
          }
        }
      }
      if (cVar4 != cVar3) {
        plVar16 = (longlong *)(param_1 + 0x90);
        if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
          FUN_1800013a0();
        }
        if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
          plVar16 = (longlong *)*plVar16;
        }
        local_188 = 6;
        local_180 = plVar16;
        local_178 = *(longlong *)(param_1 + 0xa0);
        FUN_18001ad90(local_148);
        plVar16 = (longlong *)
                  FUN_180017990(local_148,
                                ", step = respParser(), message = wrong target device byte, packet[0] is not remote"
                                ,0x52);
        local_88 = *plVar16;
        plStack_80 = (longlong *)plVar16[1];
        local_78 = (longlong *)plVar16[2];
        lStack_70 = plVar16[3];
        plVar16[2] = 0;
        plVar16[3] = 0xf;
        *(undefined1 *)plVar16 = 0;
        uVar6 = *(undefined2 *)(param_1 + 0x38);
        uVar14 = FUN_180073fc0();
        FUN_180074040(uVar14,uVar6,0,&local_88);
        FUN_180017790(&local_88);
        uVar17 = FUN_180017790(local_148);
        return uVar17 & 0xffffffffffffff00;
      }
    }
    goto LAB_1800847fc;
  }
  if (*(int *)(param_1 + 0xb0) - 2U < 2) {
    pcVar24 = (char *)((longlong)&local_78 + 5);
    uVar17 = param_2[1] - *param_2;
    do {
      pcVar24 = pcVar24 + -1;
      uVar21 = uVar17 / 10;
      *pcVar24 = (char)uVar17 + (char)uVar21 * -10 + '0';
      uVar17 = uVar21;
    } while (uVar21 != 0);
    FUN_18001d100(&local_68,pcVar24,(longlong)&local_78 + 5);
    plVar16 = (longlong *)(param_1 + 0x90);
    if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
      FUN_1800013a0();
    }
    if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
      plVar16 = (longlong *)*plVar16;
    }
    local_188 = 6;
    local_180 = plVar16;
    local_178 = *(longlong *)(param_1 + 0xa0);
    FUN_18001ad90(&local_128);
    puVar15 = (undefined8 *)FUN_180017990(&local_128,", message = relay packet length : ",0x22);
    local_168 = *puVar15;
    uStack_160 = puVar15[1];
    uVar9 = *(undefined4 *)(puVar15 + 2);
    local_158 = puVar15[2];
    uStack_150 = puVar15[3];
    puVar15[2] = 0;
    puVar15[3] = 0xf;
    *(undefined1 *)puVar15 = 0;
    FUN_18001aba0(local_148,uVar9,&local_168,&local_68);
    uVar6 = *(undefined2 *)(param_1 + 0x38);
    uVar14 = FUN_180073fc0();
    FUN_180074040(uVar14,uVar6,2,local_148);
    FUN_180017790(local_148);
    FUN_180017790(&local_168);
    FUN_180017790(&local_128);
    FUN_180017790(&local_68);
    lVar12 = *param_2;
    if ((ulonglong)(uVar23 + 8) <= (ulonglong)(param_2[1] - lVar12)) {
      if (*(char *)((ulonglong)(uVar23 + 1) + lVar12) != ']') {
        plVar16 = (longlong *)(param_1 + 0x90);
        if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
          FUN_1800013a0();
        }
        if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
          plVar16 = (longlong *)*plVar16;
        }
        local_188 = 6;
        local_180 = plVar16;
        local_178 = *(longlong *)(param_1 + 0xa0);
        FUN_18001ad90(local_148);
        plVar16 = (longlong *)
                  FUN_180017990(local_148,
                                ", step = respParser(), message = wrong relay resp type, expected 0x5D"
                                ,0x45);
        local_88 = *plVar16;
        plStack_80 = (longlong *)plVar16[1];
        local_78 = (longlong *)plVar16[2];
        lStack_70 = plVar16[3];
        plVar16[2] = 0;
        plVar16[3] = 0xf;
        *(undefined1 *)plVar16 = 0;
        uVar6 = *(undefined2 *)(param_1 + 0x38);
        uVar14 = FUN_180073fc0();
        FUN_180074040(uVar14,uVar6,0,&local_88);
        FUN_180017790(&local_88);
        uVar17 = FUN_180017790(local_148);
        *(undefined4 *)(param_1 + 0xb8) = 0x20;
        return uVar17 & 0xffffffffffffff00;
      }
      local_88 = 0;
      plStack_80 = (longlong *)0x0;
      local_78 = (longlong *)0x0;
      FUN_18001b340(&local_88,0,(ulonglong)(uVar23 + 4) + lVar12);
      if (plStack_80 == local_78) {
        FUN_18001b340(&local_88,plStack_80);
      }
      else {
        *(undefined1 *)plStack_80 = *(undefined1 *)((ulonglong)(uVar23 + 5) + *param_2);
        plStack_80 = (longlong *)((longlong)plStack_80 + 1);
      }
      plVar16 = local_78;
      lVar12 = local_88;
      uVar21 = 0;
      uVar22 = 0;
      uVar17 = 0;
      do {
        if ((ulonglong)((longlong)plStack_80 - local_88) <= uVar21) break;
        uVar22 = uVar22 | (ushort)*(byte *)(uVar21 + local_88) << ((byte)uVar17 & 0x1f);
        uVar21 = uVar21 + 1;
        uVar17 = uVar17 + 8;
      } while (uVar17 < 0x10);
      if (uVar22 != 0xd01) {
        plVar18 = (longlong *)(param_1 + 0x90);
        if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
          FUN_1800013a0();
        }
        if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
          plVar18 = (longlong *)*plVar18;
        }
        local_188 = 6;
        local_180 = plVar18;
        local_178 = *(longlong *)(param_1 + 0xa0);
        FUN_18001ad90(local_148,uVar21,uVar22,"tag = ");
        puVar15 = (undefined8 *)
                  FUN_180017990(local_148,
                                ", step = respParser(), message = wrong relay resp race ID, expected 0x0D01"
                                ,0x4a);
        local_68 = (ushort *)*puVar15;
        puStack_60 = (ushort *)puVar15[1];
        local_58 = puVar15[2];
        uStack_50 = puVar15[3];
        puVar15[2] = 0;
        puVar15[3] = 0xf;
        *(undefined1 *)puVar15 = 0;
        uVar6 = *(undefined2 *)(param_1 + 0x38);
        uVar14 = FUN_180073fc0();
        FUN_180074040(uVar14,uVar6,0,&local_68);
        FUN_180017790(&local_68);
        uVar17 = FUN_180017790(local_148);
        if (lVar12 != 0) {
          uVar17 = (longlong)plVar16 - lVar12;
          lVar20 = lVar12;
          if (uVar17 < 0x1000) {
LAB_180084d6c:
            uVar17 = thunk_FUN_180190730(lVar20,uVar17);
            return uVar17 & 0xffffffffffffff00;
          }
          uVar17 = uVar17 + 0x27;
          lVar20 = *(longlong *)(lVar12 + -8);
          if ((lVar12 - lVar20) - 8U < 0x20) goto LAB_180084d6c;
          goto LAB_18008584f;
        }
        goto LAB_180084b03;
      }
      lVar20 = *param_2 + 8 + (ulonglong)uVar23;
      FUN_18002cd30(param_1 + 0x58,lVar20,param_2[1] - lVar20);
      if (lVar12 != 0) {
        uVar17 = (longlong)plVar16 - lVar12;
        lVar20 = lVar12;
        if (0xfff < uVar17) {
          uVar17 = uVar17 + 0x27;
          lVar20 = *(longlong *)(lVar12 + -8);
          if (0x1f < (lVar12 - lVar20) - 8U) goto LAB_18008584f;
        }
        thunk_FUN_180190730(lVar20,uVar17);
      }
      goto LAB_180084de3;
    }
    plVar16 = (longlong *)(param_1 + 0x90);
    if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
      FUN_1800013a0();
    }
    if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
      plVar16 = (longlong *)*plVar16;
    }
    local_188 = 6;
    local_180 = plVar16;
    local_178 = *(longlong *)(param_1 + 0xa0);
    FUN_18001ad90(local_148);
    plVar16 = (longlong *)
              FUN_180017990(local_148,", step = respParser(), message = wrong relay resp length",
                            0x38);
    local_88 = *plVar16;
    plStack_80 = (longlong *)plVar16[1];
    local_78 = (longlong *)plVar16[2];
    lStack_70 = plVar16[3];
    plVar16[2] = 0;
    plVar16[3] = 0xf;
    *(undefined1 *)plVar16 = 0;
    uVar6 = *(undefined2 *)(param_1 + 0x38);
    uVar14 = FUN_180073fc0();
    FUN_180074040(uVar14,uVar6,0,&local_88);
    FUN_180017790(&local_88);
  }
  else {
    FUN_18002cd30(param_1 + 0x58,(ulonglong)uVar23 + *param_2,
                  param_2[1] - ((ulonglong)uVar23 + *param_2));
LAB_180084de3:
    pcVar24 = (char *)((longlong)&local_78 + 5);
    uVar17 = *(longlong *)(param_1 + 0x60) - *(longlong *)(param_1 + 0x58);
    do {
      pcVar24 = pcVar24 + -1;
      uVar21 = uVar17 / 10;
      *pcVar24 = (char)uVar17 + (char)uVar21 * -10 + '0';
      uVar17 = uVar21;
    } while (uVar21 != 0);
    FUN_18001d100(&local_68,pcVar24,(longlong)&local_78 + 5);
    plVar16 = (longlong *)(param_1 + 0x90);
    if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
      FUN_1800013a0();
    }
    if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
      plVar16 = (longlong *)*plVar16;
    }
    local_188 = 6;
    local_180 = plVar16;
    local_178 = *(longlong *)(param_1 + 0xa0);
    FUN_18001ad90(&local_128);
    puVar15 = (undefined8 *)FUN_180017990(&local_128,", variable = pure_packet_length : ",0x22);
    local_168 = *puVar15;
    uStack_160 = puVar15[1];
    uVar9 = *(undefined4 *)(puVar15 + 2);
    local_158 = puVar15[2];
    uStack_150 = puVar15[3];
    uVar17 = 0;
    puVar15[2] = 0;
    puVar15[3] = 0xf;
    *(undefined1 *)puVar15 = 0;
    FUN_18001aba0(local_148,uVar9,&local_168,&local_68);
    uVar6 = *(undefined2 *)(param_1 + 0x38);
    uVar14 = FUN_180073fc0();
    FUN_180074040(uVar14,uVar6,2,local_148);
    FUN_180017790(local_148);
    FUN_180017790(&local_168);
    FUN_180017790(&local_128);
    FUN_180017790(&local_68);
    lVar12 = *(longlong *)(param_1 + 0x58);
    if ((ulonglong)*(uint *)(param_1 + 0x40) <= (ulonglong)(*(longlong *)(param_1 + 0x60) - lVar12))
    {
      bVar5 = *(byte *)(lVar12 + 1);
      if (bVar5 != *(byte *)(param_1 + 0x3b)) {
        uVar23 = (uint)*(byte *)(param_1 + 0x3b);
        pcVar24 = (char *)((longlong)&local_78 + 5);
        do {
          pcVar24 = pcVar24 + -1;
          *pcVar24 = (char)uVar23 + (char)((ulonglong)uVar23 / 10) * -10 + '0';
          uVar23 = (uint)((ulonglong)uVar23 / 10);
        } while (uVar23 != 0);
        FUN_18001d100(local_108,pcVar24,(longlong)&local_78 + 5);
        uVar23 = (uint)bVar5;
        pcVar24 = (char *)((longlong)&local_78 + 5);
        do {
          pcVar24 = pcVar24 + -1;
          *pcVar24 = (char)uVar23 + (char)((ulonglong)uVar23 / 10) * -10 + '0';
          uVar23 = (uint)((ulonglong)uVar23 / 10);
        } while (uVar23 != 0);
        FUN_18001d100(local_c8,pcVar24,(longlong)&local_78 + 5);
        plVar16 = (longlong *)(param_1 + 0x90);
        if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
          FUN_1800013a0();
        }
        if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
          plVar16 = (longlong *)*plVar16;
        }
        local_188 = 6;
        local_180 = plVar16;
        local_178 = *(longlong *)(param_1 + 0xa0);
        FUN_18001ad90(local_e8);
        plVar16 = (longlong *)
                  FUN_180017990(local_e8,", step = respParser(), variable = RespType: ",0x2c);
        local_88 = *plVar16;
        plStack_80 = (longlong *)plVar16[1];
        lVar12 = plVar16[2];
        local_78 = (longlong *)plVar16[2];
        lStack_70 = plVar16[3];
        plVar16[2] = 0;
        plVar16[3] = 0xf;
        *(undefined1 *)plVar16 = 0;
        FUN_18001aba0(&local_128,(int)lVar12,&local_88,local_c8);
        puVar15 = (undefined8 *)FUN_180017990(&local_128," expected RespType: ",0x14);
        local_168 = *puVar15;
        uStack_160 = puVar15[1];
        uVar9 = *(undefined4 *)(puVar15 + 2);
        local_158 = puVar15[2];
        uStack_150 = puVar15[3];
        puVar15[2] = 0;
        puVar15[3] = 0xf;
        *(undefined1 *)puVar15 = 0;
        FUN_18001aba0(local_148,uVar9,&local_168,local_108);
        puVar15 = (undefined8 *)FUN_180017990(local_148,", message = wrong RespType",0x1a);
        local_68 = (ushort *)*puVar15;
        puStack_60 = (ushort *)puVar15[1];
        local_58 = puVar15[2];
        uStack_50 = puVar15[3];
        puVar15[2] = 0;
        puVar15[3] = 0xf;
        *(undefined1 *)puVar15 = 0;
        uVar6 = *(undefined2 *)(param_1 + 0x38);
        uVar14 = FUN_180073fc0();
        FUN_180074040(uVar14,uVar6,0,&local_68);
        FUN_180017790(&local_68);
        FUN_180017790(local_148);
        FUN_180017790(&local_168);
        FUN_180017790(&local_128);
        FUN_180017790(&local_88);
        FUN_180017790(local_e8);
        FUN_180017790(local_c8);
        uVar17 = FUN_180017790(local_108);
        *(undefined4 *)(param_1 + 0xb8) = 0x20;
        return uVar17 & 0xffffffffffffff00;
      }
      if (*(char *)(param_1 + 0x50) == '\0') {
        bVar5 = *(byte *)(lVar12 + *(longlong *)(param_1 + 0x48));
        pcVar24 = (char *)((longlong)&local_78 + 5);
        uVar21 = (ulonglong)bVar5;
        do {
          pcVar24 = pcVar24 + -1;
          uVar8 = uVar21 / 10;
          *pcVar24 = (char)uVar21 + (char)uVar8 * -10 + '0';
          uVar21 = uVar8;
        } while ((int)uVar8 != 0);
        FUN_18001d100(local_e8,pcVar24,(longlong)&local_78 + 5);
        plVar16 = (longlong *)(param_1 + 0x90);
        if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
          FUN_1800013a0();
        }
        if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
          plVar16 = (longlong *)*plVar16;
        }
        local_188 = 6;
        local_180 = plVar16;
        local_178 = *(longlong *)(param_1 + 0xa0);
        FUN_18001ad90(local_c8);
        puVar15 = (undefined8 *)
                  FUN_180017990(local_c8,", step = respParser(), variable = status: ",0x2a);
        local_168 = *puVar15;
        uStack_160 = puVar15[1];
        uVar9 = *(undefined4 *)(puVar15 + 2);
        local_158 = puVar15[2];
        uStack_150 = puVar15[3];
        puVar15[2] = 0;
        puVar15[3] = 0xf;
        *(undefined1 *)puVar15 = 0;
        FUN_18001aba0(local_108,uVar9,&local_168,local_e8);
        uVar6 = *(undefined2 *)(param_1 + 0x38);
        uVar14 = FUN_180073fc0();
        FUN_180074040(uVar14,uVar6,2,local_108);
        FUN_180017790(local_108);
        FUN_180017790(&local_168);
        FUN_180017790(local_c8);
        FUN_180017790(local_e8);
        if (bVar5 != 0) {
          plVar16 = (longlong *)(param_1 + 0x90);
          if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
            FUN_1800013a0();
          }
          if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
            plVar16 = (longlong *)*plVar16;
          }
          local_188 = 6;
          local_180 = plVar16;
          local_178 = *(longlong *)(param_1 + 0xa0);
          FUN_18001ad90(local_108);
          plVar16 = (longlong *)
                    FUN_180017990(local_108,
                                  ", step = respParser(), message = check pure resp status fail",
                                  0x3c);
          local_88 = *plVar16;
          plStack_80 = (longlong *)plVar16[1];
          local_78 = (longlong *)plVar16[2];
          lStack_70 = plVar16[3];
          plVar16[2] = 0;
          plVar16[3] = 0xf;
          *(undefined1 *)plVar16 = 0;
          uVar6 = *(undefined2 *)(param_1 + 0x38);
          uVar14 = FUN_180073fc0();
          FUN_180074040(uVar14,uVar6,0,&local_88);
          FUN_180017790(&local_88);
          uVar17 = FUN_180017790(local_108);
          *(undefined1 *)(param_1 + 0x88) = 0;
          *(undefined4 *)(param_1 + 0xb8) = 3;
          return uVar17 & 0xffffffffffffff00;
        }
      }
      *(undefined1 *)(param_1 + 0x88) = 1;
      local_88 = 0;
      plStack_80 = (longlong *)0x0;
      local_78 = (longlong *)0x0;
      FUN_18001b340(&local_88,0,*(longlong *)(param_1 + 0x58) + 4);
      if (plStack_80 == local_78) {
        FUN_18001b340(&local_88,plStack_80);
      }
      else {
        *(undefined1 *)plStack_80 = *(undefined1 *)(*(longlong *)(param_1 + 0x58) + 5);
        plStack_80 = (longlong *)((longlong)plStack_80 + 1);
      }
      plVar16 = local_78;
      lVar12 = local_88;
      uVar22 = 0;
      uVar21 = uVar17;
      do {
        if ((ulonglong)((longlong)plStack_80 - local_88) <= uVar21) break;
        uVar22 = uVar22 | (ushort)*(byte *)(local_88 + uVar21) << ((byte)uVar17 & 0x1f);
        uVar21 = uVar21 + 1;
        uVar17 = uVar17 + 8;
      } while (uVar17 < 0x10);
      uVar7 = *(ushort *)(param_1 + 0xb4);
      if (uVar22 == uVar7) {
        plVar18 = (longlong *)(param_1 + 0x90);
        if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
          FUN_1800013a0();
        }
        if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
          plVar18 = (longlong *)*plVar18;
        }
        local_188 = 6;
        local_180 = plVar18;
        local_178 = *(longlong *)(param_1 + 0xa0);
        FUN_18001ad90(local_a8);
        puVar15 = (undefined8 *)
                  FUN_180017990(local_a8,", step = respParser(), message = respParser success",0x33)
        ;
        local_168 = *puVar15;
        uStack_160 = puVar15[1];
        local_158 = puVar15[2];
        uStack_150 = puVar15[3];
        puVar15[2] = 0;
        puVar15[3] = 0xf;
        *(undefined1 *)puVar15 = 0;
        uVar6 = *(undefined2 *)(param_1 + 0x38);
        uVar14 = FUN_180073fc0();
        FUN_180074040(uVar14,uVar6,2,&local_168);
        FUN_180017790(&local_168);
        FUN_180017790(local_a8);
        uVar17 = 1;
      }
      else {
        local_68 = (ushort *)0x0;
        puStack_60 = (ushort *)0x0;
        local_58 = 0;
        FUN_18001b120(&local_68,2);
        *local_68 = uVar7;
        puStack_60 = local_68 + 1;
        FUN_1800026e0(local_a8,&local_68);
        if (local_68 != (ushort *)0x0) {
          if (0xfff < (ulonglong)(local_58 - (longlong)local_68)) {
            if (0x1f < (ulonglong)((longlong)local_68 + (-8 - *(longlong *)(local_68 + -4)))) {
                    /* WARNING: Subroutine does not return */
              FUN_18018f678(*(longlong *)(local_68 + -4),(local_58 - (longlong)local_68) + 0x27);
            }
          }
          thunk_FUN_180190730();
        }
        local_68 = (ushort *)0x0;
        puStack_60 = (ushort *)0x0;
        local_58 = 0;
        FUN_18001b120(&local_68,2);
        *local_68 = uVar22;
        puStack_60 = local_68 + 1;
        FUN_1800026e0(local_148,&local_68);
        if (local_68 != (ushort *)0x0) {
          if (0xfff < (ulonglong)(local_58 - (longlong)local_68)) {
            if (0x1f < (ulonglong)((longlong)local_68 + (-8 - *(longlong *)(local_68 + -4)))) {
                    /* WARNING: Subroutine does not return */
              FUN_18018f678(*(longlong *)(local_68 + -4),(local_58 - (longlong)local_68) + 0x27);
            }
          }
          thunk_FUN_180190730();
        }
        plVar18 = (longlong *)(param_1 + 0x90);
        if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
          FUN_1800013a0();
        }
        if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
          plVar18 = (longlong *)*plVar18;
        }
        local_188 = 6;
        local_180 = plVar18;
        local_178 = *(longlong *)(param_1 + 0xa0);
        FUN_18001ad90(local_e8);
        puVar19 = (undefined4 *)
                  FUN_180017990(local_e8,", step = respParser(), variable = RespRaceId: ",0x2e);
        local_128 = *puVar19;
        uStack_124 = puVar19[1];
        uStack_120 = puVar19[2];
        uStack_11c = puVar19[3];
        local_118 = puVar19[4];
        uStack_114 = puVar19[5];
        uStack_110 = puVar19[6];
        uStack_10c = puVar19[7];
        *(undefined8 *)(puVar19 + 4) = 0;
        *(undefined8 *)(puVar19 + 6) = 0xf;
        *(undefined1 *)puVar19 = 0;
        FUN_18001aba0(local_c8,local_118,&local_128,local_148);
        puVar15 = (undefined8 *)FUN_180017990(local_c8," expected RaceCmdId: ",0x15);
        local_68 = (ushort *)*puVar15;
        puStack_60 = (ushort *)puVar15[1];
        uVar9 = *(undefined4 *)(puVar15 + 2);
        local_58 = puVar15[2];
        uStack_50 = puVar15[3];
        puVar15[2] = 0;
        puVar15[3] = 0xf;
        *(undefined1 *)puVar15 = 0;
        FUN_18001aba0(local_108,uVar9,&local_68,local_a8);
        puVar15 = (undefined8 *)FUN_180017990(local_108,", message = not the expected race ID",0x24)
        ;
        local_168 = *puVar15;
        uStack_160 = puVar15[1];
        local_158 = puVar15[2];
        uStack_150 = puVar15[3];
        puVar15[2] = 0;
        puVar15[3] = 0xf;
        *(undefined1 *)puVar15 = 0;
        uVar6 = *(undefined2 *)(param_1 + 0x38);
        uVar14 = FUN_180073fc0();
        FUN_180074040(uVar14,uVar6,0,&local_168);
        FUN_180017790(&local_168);
        FUN_180017790(local_108);
        FUN_180017790(&local_68);
        FUN_180017790(local_c8);
        FUN_180017790(&local_128);
        FUN_180017790(local_e8);
        FUN_180017790(local_148);
        FUN_180017790(local_a8);
        *(undefined4 *)(param_1 + 0xb8) = 0x21;
        uVar17 = 0;
      }
      if (lVar12 != 0) {
        uVar21 = (longlong)plVar16 - lVar12;
        lVar20 = lVar12;
        if (0xfff < uVar21) {
          uVar21 = uVar21 + 0x27;
          lVar20 = *(longlong *)(lVar12 + -8);
          if (0x1f < (lVar12 - lVar20) - 8U) {
LAB_18008584f:
                    /* WARNING: Subroutine does not return */
            FUN_18018f678();
          }
        }
        thunk_FUN_180190730(lVar20,uVar21);
      }
      return uVar17;
    }
    plVar16 = (longlong *)(param_1 + 0x90);
    if (0x7fffffffffffffffU - *(longlong *)(param_1 + 0xa0) < 6) {
                    /* WARNING: Subroutine does not return */
      FUN_1800013a0();
    }
    if (0xf < *(ulonglong *)(param_1 + 0xa8)) {
      plVar16 = (longlong *)*plVar16;
    }
    local_188 = 6;
    local_180 = plVar16;
    local_178 = *(longlong *)(param_1 + 0xa0);
    FUN_18001ad90(local_148);
    plVar16 = (longlong *)
              FUN_180017990(local_148,", step = respParser(), message = wrong pure resp length",0x37
                           );
    local_88 = *plVar16;
    plStack_80 = (longlong *)plVar16[1];
    local_78 = (longlong *)plVar16[2];
    lStack_70 = plVar16[3];
    plVar16[2] = 0;
    plVar16[3] = 0xf;
    *(undefined1 *)plVar16 = 0;
    uVar6 = *(undefined2 *)(param_1 + 0x38);
    uVar14 = FUN_180073fc0();
    FUN_180074040(uVar14,uVar6,0,&local_88);
    FUN_180017790(&local_88);
  }
  uVar17 = FUN_180017790(local_148);
  *(undefined4 *)(param_1 + 0xb8) = 0x22;
LAB_180084b03:
  return uVar17 & 0xffffffffffffff00;
}



// ==== FUN_1800858d0 @ 1800858d0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 * FUN_1800858d0(undefined8 *param_1,undefined2 param_2)

{
  undefined8 ****ppppuVar1;
  undefined8 *puVar2;
  undefined8 ****ppppuVar3;
  longlong lVar4;
  undefined1 auStack_d8 [32];
  char *local_b8;
  undefined8 local_b0;
  undefined8 ****local_a8 [2];
  longlong local_98;
  ulonglong uStack_90;
  undefined8 ***local_88;
  undefined8 ***pppuStack_80;
  undefined8 ***local_78;
  undefined8 ***pppuStack_70;
  undefined8 *local_68;
  undefined2 *local_58;
  undefined2 *puStack_50;
  longlong local_48;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  ulonglong local_38;
  
  local_38 = DAT_180225100 ^ (ulonglong)auStack_d8;
  puVar2 = param_1;
  local_68 = param_1;
  FUN_180083740();
  *puVar2 = GetAgentChannelCmd::vftable;
  local_58 = (undefined2 *)0x0;
  puStack_50 = (undefined2 *)0x0;
  local_48 = 0;
  FUN_18001b120(&local_58,2);
  *local_58 = param_2;
  puStack_50 = local_58 + 1;
  FUN_180161430();
  FUN_1800026e0(local_a8,&local_58);
  if (local_58 != (undefined2 *)0x0) {
    if (0xfff < (ulonglong)(local_48 - (longlong)local_58)) {
      if (0x1f < (ulonglong)((longlong)local_58 + (-8 - *(longlong *)(local_58 + -4)))) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(*(longlong *)(local_58 + -4),(local_48 - (longlong)local_58) + 0x27);
      }
    }
    thunk_FUN_180190730();
  }
  if (uStack_90 - local_98 < 0x13) {
    local_b0 = 0x13;
    local_b8 = "GetAgentChannelCmd(";
    ppppuVar1 = (undefined8 ****)FUN_18001b490(local_a8,0x13);
  }
  else {
    ppppuVar1 = local_a8;
    if (0xf < uStack_90) {
      ppppuVar1 = local_a8[0];
    }
    if (((undefined8 ****)0x1801e2c92 < ppppuVar1) ||
       ((char *)((longlong)ppppuVar1 + local_98) < "GetAgentChannelCmd(")) {
      ppppuVar3 = (undefined8 ****)0x13;
    }
    else if ("GetAgentChannelCmd(" < ppppuVar1) {
      ppppuVar3 = ppppuVar1 + -0x3003c590;
    }
    else {
      ppppuVar3 = (undefined8 ****)0x0;
    }
    lVar4 = local_98 + 1;
    local_98 = local_98 + 0x13;
    FUN_1801afa50((char *)((longlong)ppppuVar1 + 0x13),ppppuVar1,lVar4);
    FUN_1801afa50(ppppuVar1,"GetAgentChannelCmd(",ppppuVar3);
    FUN_1801afa50((char *)((longlong)ppppuVar1 + (longlong)ppppuVar3),"" + (longlong)ppppuVar3,
                  0x13 - (longlong)ppppuVar3);
    ppppuVar1 = local_a8;
  }
  local_88 = (undefined8 ***)0x0;
  pppuStack_80 = (undefined8 ***)0x0;
  local_78 = (undefined8 ***)0x0;
  pppuStack_70 = (undefined8 ***)0x0;
  local_88 = *ppppuVar1;
  pppuStack_80 = ppppuVar1[1];
  local_78 = ppppuVar1[2];
  pppuStack_70 = ppppuVar1[3];
  ppppuVar1[2] = (undefined8 ***)0x0;
  ppppuVar1[3] = (undefined8 ***)0xf;
  *(undefined1 *)ppppuVar1 = 0;
  puVar2 = (undefined8 *)FUN_180017990(&local_88,&DAT_1801d8eac,1);
  local_58 = (undefined2 *)*puVar2;
  puStack_50 = (undefined2 *)puVar2[1];
  local_48 = puVar2[2];
  uStack_40 = *(undefined4 *)(puVar2 + 3);
  uStack_3c = *(undefined4 *)((longlong)puVar2 + 0x1c);
  puVar2[2] = 0;
  puVar2[3] = 0xf;
  *(undefined1 *)puVar2 = 0;
  FUN_180015d60(param_1 + 0x12,&local_58);
  FUN_180017790(&local_58);
  FUN_180017790(&local_88);
  FUN_180017790(local_a8);
  *(undefined2 *)((longlong)param_1 + 0xb4) = 0xcd4;
  *(undefined2 *)((longlong)param_1 + 0x3a) = 0x5b5a;
  *(undefined4 *)(param_1 + 8) = 8;
  param_1[9] = 6;
  return param_1;
}



// ==== FUN_180085b20 @ 180085b20 ====

undefined8 * FUN_180085b20(undefined8 *param_1,ulonglong param_2)

{
  *param_1 = GetAgentChannelCmd::vftable;
  FUN_180083850();
  if ((param_2 & 1) != 0) {
    thunk_FUN_180190730(param_1,0xd0);
  }
  return param_1;
}



// ==== FUN_180085b60 @ 180085b60 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined1 FUN_180085b60(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  char cVar5;
  undefined1 uVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined4 uVar9;
  undefined4 extraout_XMM0_Da;
  undefined4 extraout_XMM0_Da_00;
  undefined1 auStack_78 [32];
  longlong *local_58;
  longlong *plStack_50;
  longlong local_48;
  longlong lStack_40;
  longlong local_38;
  longlong *local_30;
  longlong *plStack_28;
  ulonglong local_20;
  
  local_20 = DAT_180225100 ^ (ulonglong)auStack_78;
  cVar5 = FUN_180084260();
  uVar6 = 0;
  if (cVar5 != '\0') {
    local_48 = 0;
    lStack_40 = 0;
    local_38 = 0;
    FUN_18001b340(&local_48,0,*(longlong *)(param_1 + 0x58) + 7);
    plVar7 = (longlong *)FUN_180185d80(0x30);
    lVar4 = local_48;
    *plVar7 = 0;
    plVar7[1] = 0;
    *(undefined4 *)(plVar7 + 1) = 1;
    *(undefined4 *)((longlong)plVar7 + 0xc) = 1;
    *plVar7 = (longlong)std::_Ref_count_obj2<RaceBaseResult>::vftable;
    plVar1 = plVar7 + 2;
    *plVar1 = (longlong)RaceBaseResult::vftable;
    plVar7[3] = 0;
    plVar7[4] = 0;
    plVar7[5] = 0;
    local_30 = plVar1;
    plStack_28 = plVar7;
    if (plVar7 + 3 != &local_48) {
      local_58 = plVar7;
      FUN_18002cd30(plVar7 + 3,local_48,lStack_40 - local_48);
    }
    LOCK();
    *(int *)(plVar7 + 1) = (int)plVar7[1] + 1;
    UNLOCK();
    local_58 = plVar1;
    plStack_50 = plVar7;
    uVar9 = FUN_1800841c0(param_1,&local_58);
    LOCK();
    plVar1 = plVar7 + 1;
    lVar8 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar8 == 1) {
      (**(code **)*plVar7)(plVar7);
      LOCK();
      piVar2 = (int *)((longlong)plVar7 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      uVar9 = extraout_XMM0_Da;
      if (iVar3 == 1) {
        (**(code **)(*plVar7 + 8))(plVar7);
        uVar9 = extraout_XMM0_Da_00;
      }
    }
    if (lVar4 != 0) {
      lVar8 = lVar4;
      if (0xfff < (ulonglong)(local_38 - lVar4)) {
        lVar8 = *(longlong *)(lVar4 + -8);
        if (0x1f < (lVar4 - lVar8) - 8U) {
                    /* WARNING: Subroutine does not return */
          FUN_18018f678(uVar9,(local_38 - lVar4) + 0x27);
        }
      }
      thunk_FUN_180190730(lVar8);
    }
    uVar6 = 1;
  }
  return uVar6;
}



// ==== FUN_180085ce0 @ 180085ce0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 * FUN_180085ce0(undefined8 *param_1,undefined2 param_2)

{
  undefined8 ****ppppuVar1;
  undefined8 *puVar2;
  undefined8 ****ppppuVar3;
  longlong lVar4;
  undefined1 auStack_d8 [32];
  char *local_b8;
  undefined8 local_b0;
  undefined8 ****local_a8 [2];
  longlong local_98;
  ulonglong uStack_90;
  undefined8 ***local_88;
  undefined8 ***pppuStack_80;
  undefined8 ***local_78;
  undefined8 ***pppuStack_70;
  undefined8 *local_68;
  undefined2 *local_58;
  undefined2 *puStack_50;
  longlong local_48;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  ulonglong local_38;
  
  local_38 = DAT_180225100 ^ (ulonglong)auStack_d8;
  puVar2 = param_1;
  local_68 = param_1;
  FUN_180083740();
  *(undefined4 *)(puVar2 + 0x18) = 9000;
  *puVar2 = GetAvaDstCmd::vftable;
  local_58 = (undefined2 *)0x0;
  puStack_50 = (undefined2 *)0x0;
  local_48 = 0;
  FUN_18001b120(&local_58,2);
  *local_58 = param_2;
  puStack_50 = local_58 + 1;
  FUN_180161430();
  FUN_1800026e0(local_a8,&local_58);
  if (local_58 != (undefined2 *)0x0) {
    if (0xfff < (ulonglong)(local_48 - (longlong)local_58)) {
      if (0x1f < (ulonglong)((longlong)local_58 + (-8 - *(longlong *)(local_58 + -4)))) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(*(longlong *)(local_58 + -4),(local_48 - (longlong)local_58) + 0x27);
      }
    }
    thunk_FUN_180190730();
  }
  if (uStack_90 - local_98 < 0xd) {
    local_b0 = 0xd;
    local_b8 = "GetAvaDstCmd(";
    ppppuVar1 = (undefined8 ****)FUN_18001b490(local_a8,0xd);
  }
  else {
    ppppuVar1 = local_a8;
    if (0xf < uStack_90) {
      ppppuVar1 = local_a8[0];
    }
    if (((undefined8 ****)0x1801e2cbc < ppppuVar1) ||
       ((char *)((longlong)ppppuVar1 + local_98) < "GetAvaDstCmd(")) {
      ppppuVar3 = (undefined8 ****)0xd;
    }
    else if ("GetAvaDstCmd(" < ppppuVar1) {
      ppppuVar3 = ppppuVar1 + -0x3003c596;
    }
    else {
      ppppuVar3 = (undefined8 ****)0x0;
    }
    lVar4 = local_98 + 1;
    local_98 = local_98 + 0xd;
    FUN_1801afa50((char *)((longlong)ppppuVar1 + 0xd),ppppuVar1,lVar4);
    FUN_1801afa50(ppppuVar1,"GetAvaDstCmd(",ppppuVar3);
    FUN_1801afa50((char *)((longlong)ppppuVar1 + (longlong)ppppuVar3),"" + (longlong)ppppuVar3,
                  0xd - (longlong)ppppuVar3);
    ppppuVar1 = local_a8;
  }
  local_88 = (undefined8 ***)0x0;
  pppuStack_80 = (undefined8 ***)0x0;
  local_78 = (undefined8 ***)0x0;
  pppuStack_70 = (undefined8 ***)0x0;
  local_88 = *ppppuVar1;
  pppuStack_80 = ppppuVar1[1];
  local_78 = ppppuVar1[2];
  pppuStack_70 = ppppuVar1[3];
  ppppuVar1[2] = (undefined8 ***)0x0;
  ppppuVar1[3] = (undefined8 ***)0xf;
  *(undefined1 *)ppppuVar1 = 0;
  puVar2 = (undefined8 *)FUN_180017990(&local_88,&DAT_1801d8eac,1);
  local_58 = (undefined2 *)*puVar2;
  puStack_50 = (undefined2 *)puVar2[1];
  local_48 = puVar2[2];
  uStack_40 = *(undefined4 *)(puVar2 + 3);
  uStack_3c = *(undefined4 *)((longlong)puVar2 + 0x1c);
  puVar2[2] = 0;
  puVar2[3] = 0xf;
  *(undefined1 *)puVar2 = 0;
  FUN_180015d60(param_1 + 0x12,&local_58);
  FUN_180017790(&local_58);
  FUN_180017790(&local_88);
  FUN_180017790(local_a8);
  *(undefined2 *)((longlong)param_1 + 0xb4) = 0xd00;
  *(undefined2 *)((longlong)param_1 + 0x3a) = 0x5b5a;
  *(undefined4 *)(param_1 + 8) = 6;
  *(undefined1 *)(param_1 + 10) = 1;
  return param_1;
}



// ==== FUN_180085f40 @ 180085f40 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined1 FUN_180085f40(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  char cVar5;
  undefined1 uVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong lVar9;
  ulonglong uVar10;
  undefined1 auStack_88 [32];
  longlong *local_68;
  longlong *plStack_60;
  longlong local_58;
  longlong lStack_50;
  longlong local_48;
  longlong *local_40;
  longlong *plStack_38;
  ulonglong local_30;
  
  local_30 = DAT_180225100 ^ (ulonglong)auStack_88;
  cVar5 = FUN_180081fc0();
  uVar6 = 0;
  if (cVar5 != '\0') {
    lVar8 = *(longlong *)(param_1 + 0x58) + 6;
    local_58 = 0;
    lStack_50 = 0;
    local_48 = 0;
    uVar10 = *(longlong *)(param_1 + 0x60) - lVar8;
    if (uVar10 == 0) {
      lVar9 = 0;
    }
    else {
      if (0x7fffffffffffffff < uVar10) {
                    /* WARNING: Subroutine does not return */
        FUN_180017770();
      }
      FUN_18001b120(&local_58,uVar10);
      lVar9 = local_58;
      FUN_1801afa50(local_58,lVar8,uVar10);
      lStack_50 = uVar10 + lVar9;
    }
    lVar4 = local_48;
    lVar8 = lStack_50;
    plVar7 = (longlong *)FUN_180185d80(0x30);
    *plVar7 = 0;
    plVar7[1] = 0;
    *(undefined4 *)(plVar7 + 1) = 1;
    *(undefined4 *)((longlong)plVar7 + 0xc) = 1;
    *plVar7 = (longlong)std::_Ref_count_obj2<RaceBaseResult>::vftable;
    plVar1 = plVar7 + 2;
    *plVar1 = (longlong)RaceBaseResult::vftable;
    plVar7[3] = 0;
    plVar7[4] = 0;
    plVar7[5] = 0;
    local_40 = plVar1;
    plStack_38 = plVar7;
    if (plVar7 + 3 != &local_58) {
      local_68 = plVar7;
      FUN_18002cd30(plVar7 + 3,lVar9,lVar8 - lVar9);
    }
    LOCK();
    *(int *)(plVar7 + 1) = (int)plVar7[1] + 1;
    UNLOCK();
    local_68 = plVar1;
    plStack_60 = plVar7;
    FUN_1800841c0(param_1,&local_68);
    LOCK();
    plVar1 = plVar7 + 1;
    lVar8 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar8 == 1) {
      (**(code **)*plVar7)(plVar7);
      LOCK();
      piVar2 = (int *)((longlong)plVar7 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar7 + 8))(plVar7);
      }
    }
    if (lVar9 != 0) {
      uVar10 = lVar4 - lVar9;
      lVar8 = lVar9;
      if (0xfff < uVar10) {
        uVar10 = uVar10 + 0x27;
        lVar8 = *(longlong *)(lVar9 + -8);
        if (0x1f < (lVar9 - lVar8) - 8U) {
                    /* WARNING: Subroutine does not return */
          FUN_18018f678();
        }
      }
      thunk_FUN_180190730(lVar8,uVar10);
    }
    uVar6 = 1;
  }
  return uVar6;
}



// ==== FUN_180086120 @ 180086120 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 * FUN_180086120(undefined8 *param_1,ulonglong param_2)

{
  undefined8 ****ppppuVar1;
  int *piVar2;
  int iVar3;
  ushort uVar4;
  int iVar5;
  bool bVar6;
  bool bVar7;
  undefined8 ****ppppuVar8;
  undefined2 uVar9;
  undefined8 *****pppppuVar10;
  undefined8 *puVar11;
  undefined8 uVar12;
  longlong *plVar13;
  longlong lVar14;
  longlong *plVar15;
  longlong lVar16;
  undefined8 *****pppppuVar17;
  longlong *plVar18;
  longlong lVar19;
  uint uVar20;
  undefined1 auStack_e8 [32];
  char *local_c8;
  undefined8 local_c0;
  undefined8 ****local_b8;
  undefined8 ****ppppuStack_b0;
  undefined8 ****local_a8;
  undefined8 ****ppppuStack_a0;
  undefined8 *****local_98 [2];
  longlong local_88;
  ulonglong uStack_80;
  undefined8 *local_78;
  uint local_70;
  undefined2 *local_68;
  longlong *plStack_60;
  longlong local_58;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  ulonglong local_48;
  
  local_48 = DAT_180225100 ^ (ulonglong)auStack_e8;
  uVar20 = (uint)param_2;
  local_70 = 0;
  puVar11 = param_1;
  local_78 = param_1;
  FUN_180083740();
  *puVar11 = GetDeviceTypeCmd::vftable;
  local_68 = (undefined2 *)0x0;
  plStack_60 = (longlong *)0x0;
  local_58 = 0;
  FUN_18001b120(&local_68,2);
  *local_68 = (short)(param_2 & 0xffffffff);
  plStack_60 = (longlong *)(local_68 + 1);
  FUN_180161430();
  FUN_1800026e0(local_98,&local_68);
  if (local_68 != (undefined2 *)0x0) {
    if (0xfff < (ulonglong)(local_58 - (longlong)local_68)) {
      if (0x1f < (ulonglong)((longlong)local_68 + (-8 - *(longlong *)(local_68 + -4)))) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(*(longlong *)(local_68 + -4),(local_58 - (longlong)local_68) + 0x27);
      }
    }
    thunk_FUN_180190730();
  }
  if (uStack_80 - local_88 < 0x11) {
    local_c0 = 0x11;
    local_c8 = "GetDeviceTypeCmd(";
    pppppuVar10 = (undefined8 *****)FUN_18001b490(local_98,0x11);
  }
  else {
    pppppuVar10 = local_98;
    if (0xf < uStack_80) {
      pppppuVar10 = local_98[0];
    }
    if (((undefined8 *****)0x1801e2d00 < pppppuVar10) ||
       ((char *)((longlong)pppppuVar10 + local_88) < "GetDeviceTypeCmd(")) {
      pppppuVar17 = (undefined8 *****)0x11;
    }
    else if ("GetDeviceTypeCmd(" < pppppuVar10) {
      pppppuVar17 = pppppuVar10 + -0x3003c59e;
    }
    else {
      pppppuVar17 = (undefined8 *****)0x0;
    }
    lVar19 = local_88 + 1;
    local_88 = local_88 + 0x11;
    FUN_1801afa50((char *)((longlong)pppppuVar10 + 0x11),pppppuVar10,lVar19);
    FUN_1801afa50(pppppuVar10,"GetDeviceTypeCmd(",pppppuVar17);
    FUN_1801afa50((char *)((longlong)pppppuVar10 + (longlong)pppppuVar17),"" + (longlong)pppppuVar17
                  ,0x11 - (longlong)pppppuVar17);
    pppppuVar10 = local_98;
  }
  local_b8 = *pppppuVar10;
  ppppuStack_b0 = pppppuVar10[1];
  local_a8 = pppppuVar10[2];
  ppppuStack_a0 = pppppuVar10[3];
  pppppuVar10[2] = (undefined8 ****)0x0;
  pppppuVar10[3] = (undefined8 ****)0xf;
  *(undefined1 *)pppppuVar10 = 0;
  puVar11 = (undefined8 *)FUN_180017990(&local_b8,&DAT_1801d8eac,1);
  local_68 = (undefined2 *)*puVar11;
  plStack_60 = (longlong *)puVar11[1];
  local_58 = puVar11[2];
  uStack_50 = *(undefined4 *)(puVar11 + 3);
  uStack_4c = *(undefined4 *)((longlong)puVar11 + 0x1c);
  puVar11[2] = 0;
  puVar11[3] = 0xf;
  *(undefined1 *)puVar11 = 0;
  FUN_180015d60(param_1 + 0x12,&local_68);
  FUN_180017790(&local_68);
  FUN_180017790(&local_b8);
  FUN_180017790(local_98);
  *(undefined2 *)((longlong)param_1 + 0xb4) = 0xa0c;
  *(undefined2 *)((longlong)param_1 + 0x3a) = 0x5b5a;
  *(undefined4 *)(param_1 + 8) = 0xb;
  param_1[9] = 6;
  uVar12 = FUN_1801501a0();
  plVar13 = (longlong *)FUN_180150e70(uVar12,&local_b8,*(undefined2 *)(param_1 + 7));
  ppppuVar8 = ppppuStack_b0;
  iVar5 = *(int *)(*plVar13 + 0x248);
  if (ppppuStack_b0 != (undefined8 ****)0x0) {
    LOCK();
    ppppuVar1 = ppppuStack_b0 + 1;
    iVar3 = *(int *)ppppuVar1;
    *(int *)ppppuVar1 = *(int *)ppppuVar1 + -1;
    UNLOCK();
    if (iVar3 == 1) {
      (*(code *)**ppppuStack_b0)(ppppuStack_b0);
      LOCK();
      piVar2 = (int *)((longlong)ppppuVar8 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (*(code *)(*ppppuVar8)[1])(ppppuVar8);
      }
    }
  }
  uVar9 = 0x183d;
  if (iVar5 < 0x65) {
    uVar9 = 0xf2b0;
  }
  *(undefined2 *)(param_1 + 0x1a) = uVar9;
  uVar9 = *(undefined2 *)(param_1 + 7);
  uVar12 = FUN_1801501a0();
  plVar13 = (longlong *)FUN_180150e70(uVar12,&local_68);
  bVar6 = false;
  local_70 = 0x79;
  if (*(int *)(*plVar13 + 0x270) == 1) {
LAB_18008641f:
    bVar7 = true;
  }
  else {
    uVar12 = FUN_1801501a0();
    plVar13 = (longlong *)FUN_180150e70(uVar12,&local_b8);
    bVar6 = true;
    if (*(int *)(*plVar13 + 0x270) == 4) goto LAB_18008641f;
    bVar7 = false;
  }
  ppppuVar8 = ppppuStack_b0;
  if ((bVar6) && (ppppuStack_b0 != (undefined8 ****)0x0)) {
    LOCK();
    ppppuVar1 = ppppuStack_b0 + 1;
    iVar5 = *(int *)ppppuVar1;
    *(int *)ppppuVar1 = *(int *)ppppuVar1 + -1;
    UNLOCK();
    if (iVar5 == 1) {
      (*(code *)**ppppuStack_b0)(ppppuStack_b0);
      LOCK();
      piVar2 = (int *)((longlong)ppppuVar8 + 0xc);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 == 1) {
        (*(code *)(*ppppuVar8)[1])(ppppuVar8);
      }
    }
  }
  plVar13 = plStack_60;
  if (plStack_60 != (longlong *)0x0) {
    LOCK();
    plVar15 = plStack_60 + 1;
    lVar19 = *plVar15;
    *(int *)plVar15 = (int)*plVar15 + -1;
    UNLOCK();
    if ((int)lVar19 == 1) {
      (**(code **)*plStack_60)(plStack_60);
      LOCK();
      piVar2 = (int *)((longlong)plVar13 + 0xc);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 == 1) {
        (**(code **)(*plVar13 + 8))(plVar13);
      }
    }
  }
  bVar6 = false;
  if (!bVar7) {
    uVar20 = (uint)CONCAT62((int6)((param_2 & 0xffffffff) >> 0x10),uVar9) & 0xffffff00 | 0x80;
  }
  uVar4 = *(ushort *)(param_1 + 7);
  local_70 = uVar20;
  lVar14 = FUN_1801501a0();
  uVar12 = 0;
  plVar13 = (longlong *)0x0;
  lVar19 = *(longlong *)(lVar14 + 0x28);
  if ((ulonglong)(uVar4 >> 8) < (ulonglong)(*(longlong *)(lVar14 + 0x30) - lVar19 >> 5)) {
    lVar16 = (ulonglong)(uVar4 >> 8) * 0x20;
    lVar14 = *(longlong *)(lVar16 + 0x18 + lVar19);
    if (lVar14 != 0) {
      LOCK();
      piVar2 = (int *)(lVar14 + 8);
      *piVar2 = *piVar2 + 1;
      UNLOCK();
    }
    uVar12 = *(undefined8 *)(lVar16 + 0x10 + lVar19);
    plVar13 = *(longlong **)(lVar16 + 0x18 + lVar19);
  }
  local_c8 = (char *)((ulonglong)local_c8 & 0xffffffff00000000);
  lVar19 = FUN_1801af878(uVar12,0,&AirohaBaseDevice::RTTI_Type_Descriptor,
                         &AirohaLocalDevice::RTTI_Type_Descriptor);
  plVar18 = plVar13;
  plVar15 = (longlong *)0x0;
  if (lVar19 == 0) {
    plVar18 = (longlong *)0x0;
    plVar15 = plVar13;
  }
  if (plVar15 != (longlong *)0x0) {
    LOCK();
    plVar13 = plVar15 + 1;
    lVar14 = *plVar13;
    *(int *)plVar13 = (int)*plVar13 + -1;
    UNLOCK();
    if ((int)lVar14 == 1) {
      (**(code **)*plVar15)(plVar15);
      LOCK();
      piVar2 = (int *)((longlong)plVar15 + 0xc);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 == 1) {
        (**(code **)(*plVar15 + 8))(plVar15);
      }
    }
  }
  if ((*(longlong *)(lVar19 + 0x378) - *(longlong *)(lVar19 + 0x370) & 0xfffffffffffffff0U) != 0) {
    plVar13 = (longlong *)FUN_180048b90(lVar19,&local_68,uVar20 & 0xffff);
    bVar6 = true;
    if (*plVar13 != 0) {
      bVar7 = false;
      goto LAB_180086586;
    }
  }
  bVar7 = true;
LAB_180086586:
  plVar13 = plStack_60;
  if ((bVar6) && (plStack_60 != (longlong *)0x0)) {
    LOCK();
    plVar15 = plStack_60 + 1;
    lVar14 = *plVar15;
    *(int *)plVar15 = (int)*plVar15 + -1;
    UNLOCK();
    if ((int)lVar14 == 1) {
      (**(code **)*plStack_60)(plStack_60);
      LOCK();
      piVar2 = (int *)((longlong)plVar13 + 0xc);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 == 1) {
        (**(code **)(*plVar13 + 8))(plVar13);
      }
    }
  }
  if (bVar7) {
    if (plVar18 != (longlong *)0x0) {
      LOCK();
      plVar13 = plVar18 + 1;
      lVar19 = *plVar13;
      *(int *)plVar13 = (int)*plVar13 + -1;
      UNLOCK();
      if ((int)lVar19 == 1) {
        (**(code **)*plVar18)(plVar18);
        LOCK();
        piVar2 = (int *)((longlong)plVar18 + 0xc);
        iVar5 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar5 == 1) {
          (**(code **)(*plVar18 + 8))(plVar18);
        }
      }
    }
  }
  else {
    plVar15 = (longlong *)FUN_180048b90(lVar19,&local_68,(undefined2)local_70);
    plVar13 = plStack_60;
    iVar5 = *(int *)(*plVar15 + 0x248);
    if (plStack_60 != (longlong *)0x0) {
      LOCK();
      plVar15 = plStack_60 + 1;
      lVar19 = *plVar15;
      *(int *)plVar15 = (int)*plVar15 + -1;
      UNLOCK();
      if ((int)lVar19 == 1) {
        (**(code **)*plStack_60)(plStack_60);
        LOCK();
        piVar2 = (int *)((longlong)plVar13 + 0xc);
        iVar3 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar3 == 1) {
          (**(code **)(*plVar13 + 8))(plVar13);
        }
      }
    }
    uVar9 = 0x183d;
    if (iVar5 < 0x65) {
      uVar9 = 0xf2b0;
    }
    *(undefined2 *)(param_1 + 0x1a) = uVar9;
    if (plVar18 != (longlong *)0x0) {
      LOCK();
      plVar13 = plVar18 + 1;
      lVar19 = *plVar13;
      *(int *)plVar13 = (int)*plVar13 + -1;
      UNLOCK();
      if ((int)lVar19 == 1) {
        (**(code **)*plVar18)(plVar18);
        LOCK();
        piVar2 = (int *)((longlong)plVar18 + 0xc);
        iVar5 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar5 == 1) {
          (**(code **)(*plVar18 + 8))(plVar18);
        }
      }
    }
  }
  return param_1;
}



// ==== FUN_1800866d0 @ 1800866d0 ====

undefined8 * FUN_1800866d0(undefined8 *param_1,ulonglong param_2)

{
  *param_1 = GetDeviceTypeCmd::vftable;
  FUN_180083850();
  if ((param_2 & 1) != 0) {
    thunk_FUN_180190730(param_1,0xd8);
  }
  return param_1;
}



// ==== FUN_180086710 @ 180086710 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_180086710(longlong param_1,undefined8 param_2)

{
  undefined2 uVar1;
  longlong lVar2;
  undefined1 *puVar3;
  undefined2 *puVar4;
  ulonglong uVar5;
  longlong lVar6;
  undefined2 *puVar7;
  undefined2 *puVar8;
  undefined4 uVar9;
  undefined1 auStack_b8 [32];
  undefined8 local_98;
  longlong local_88;
  undefined1 *puStack_80;
  undefined1 *local_78;
  undefined2 *local_68;
  undefined2 *puStack_60;
  longlong local_58;
  undefined2 *local_50;
  undefined2 *puStack_48;
  longlong local_40;
  ulonglong local_38;
  
  local_38 = DAT_180225100 ^ (ulonglong)auStack_b8;
  local_88 = 0;
  puStack_80 = (undefined1 *)0x0;
  local_78 = (undefined1 *)0x0;
  uVar1 = *(undefined2 *)(param_1 + 0xd0);
  local_50 = (undefined2 *)0x0;
  puStack_48 = (undefined2 *)0x0;
  local_40 = 0;
  local_98 = param_2;
  FUN_18001b120(&local_50,2);
  puVar4 = local_50;
  *local_50 = uVar1;
  puStack_48 = local_50 + 1;
  local_68 = (undefined2 *)0x0;
  puStack_60 = (undefined2 *)0x0;
  local_58 = 0;
  FUN_18001b120(&local_68,2);
  puVar8 = local_68;
  *local_68 = 1000;
  puStack_60 = local_68 + 1;
  FUN_18001b340(&local_88,0,puVar4);
  if (puStack_80 == local_78) {
    FUN_18001b340(&local_88,puStack_80);
  }
  else {
    *puStack_80 = *(undefined1 *)((longlong)puVar4 + 1);
    puStack_80 = puStack_80 + 1;
  }
  if (puStack_80 == local_78) {
    FUN_18001b340(&local_88,puStack_80,puVar8);
  }
  else {
    *puStack_80 = *(undefined1 *)puVar8;
    puStack_80 = puStack_80 + 1;
  }
  if (puStack_80 == local_78) {
    FUN_18001b340(&local_88,puStack_80);
  }
  else {
    *puStack_80 = *(undefined1 *)((longlong)puVar8 + 1);
    puStack_80 = puStack_80 + 1;
  }
  puVar3 = local_78;
  lVar2 = local_88;
  if ((longlong *)(param_1 + 8) != &local_88) {
    FUN_18002cd30((longlong *)(param_1 + 8),local_88,(longlong)puStack_80 - local_88);
  }
  uVar9 = FUN_1800839c0(param_1,param_2);
  if (puVar8 != (undefined2 *)0x0) {
    puVar7 = puVar8;
    if (0xfff < (ulonglong)(local_58 - (longlong)puVar8)) {
      puVar7 = *(undefined2 **)(puVar8 + -4);
      if (0x1f < (ulonglong)((longlong)puVar8 + (-8 - (longlong)puVar7))) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(uVar9,(local_58 - (longlong)puVar8) + 0x27);
      }
    }
    uVar9 = thunk_FUN_180190730(puVar7);
  }
  if (puVar4 != (undefined2 *)0x0) {
    puVar8 = puVar4;
    if (0xfff < (ulonglong)(local_40 - (longlong)puVar4)) {
      puVar8 = *(undefined2 **)(puVar4 + -4);
      if (0x1f < (ulonglong)((longlong)puVar4 + (-8 - (longlong)puVar8))) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(uVar9,(local_40 - (longlong)puVar4) + 0x27);
      }
    }
    thunk_FUN_180190730(puVar8);
  }
  if (lVar2 != 0) {
    uVar5 = (longlong)puVar3 - lVar2;
    lVar6 = lVar2;
    if (0xfff < uVar5) {
      uVar5 = uVar5 + 0x27;
      lVar6 = *(longlong *)(lVar2 + -8);
      if (0x1f < (lVar2 - lVar6) - 8U) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678();
      }
    }
    thunk_FUN_180190730(lVar6,uVar5);
  }
  return param_2;
}



// ==== FUN_180086960 @ 180086960 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_180086960(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  undefined2 uVar4;
  undefined1 *puVar5;
  longlong lVar6;
  undefined1 *puVar7;
  undefined8 uVar8;
  longlong *plVar9;
  ulonglong uVar10;
  ulonglong uVar11;
  longlong lVar12;
  longlong lVar13;
  longlong lVar14;
  ushort uVar15;
  undefined4 uVar16;
  undefined1 auStack_d8 [32];
  longlong *local_b8;
  longlong *plStack_b0;
  longlong local_a8;
  undefined1 *puStack_a0;
  undefined1 *local_98;
  undefined8 local_90;
  longlong local_88;
  undefined1 *puStack_80;
  undefined1 *local_78;
  longlong local_70;
  longlong lStack_68;
  longlong local_60;
  longlong *local_58;
  longlong *plStack_50;
  ulonglong local_48;
  
  local_48 = DAT_180225100 ^ (ulonglong)auStack_d8;
  uVar8 = FUN_180084260();
  if ((char)uVar8 != '\0') {
    local_88 = 0;
    puStack_80 = (undefined1 *)0x0;
    local_78 = (undefined1 *)0x0;
    FUN_18001b340(&local_88,0,*(longlong *)(param_1 + 0x58) + 7);
    if (puStack_80 == local_78) {
      FUN_18001b340(&local_88,puStack_80);
    }
    else {
      *puStack_80 = *(undefined1 *)(*(longlong *)(param_1 + 0x58) + 8);
      puStack_80 = puStack_80 + 1;
    }
    puVar7 = local_78;
    lVar6 = local_88;
    uVar15 = 0;
    uVar11 = 0;
    uVar10 = 0;
    do {
      if ((ulonglong)((longlong)puStack_80 - local_88) <= uVar11) break;
      uVar15 = uVar15 | (ushort)*(byte *)(local_88 + uVar11) << ((byte)uVar10 & 0x1f);
      uVar11 = uVar11 + 1;
      uVar10 = uVar10 + 8;
    } while (uVar10 < 0x10);
    local_98 = (undefined1 *)0x0;
    if (uVar15 == *(ushort *)(param_1 + 0xd0)) {
      local_a8 = 0;
      puStack_a0 = (undefined1 *)0x0;
      FUN_18001b340(&local_a8,0,*(longlong *)(param_1 + 0x58) + 9);
      if (puStack_a0 == local_98) {
        FUN_18001b340(&local_a8,puStack_a0);
      }
      else {
        *puStack_a0 = *(undefined1 *)(*(longlong *)(param_1 + 0x58) + 10);
        puStack_a0 = puStack_a0 + 1;
      }
      puVar5 = local_98;
      lVar13 = local_a8;
      uVar15 = 0;
      uVar11 = 0;
      uVar10 = 0;
      do {
        if ((ulonglong)((longlong)puStack_a0 - local_a8) <= uVar11) break;
        uVar15 = uVar15 | (ushort)*(byte *)(local_a8 + uVar11) << ((byte)uVar10 & 0x1f);
        uVar11 = uVar11 + 1;
        uVar10 = uVar10 + 8;
      } while (uVar10 < 0x10);
      if (uVar15 != 0) {
        local_70 = 0;
        lStack_68 = 0;
        local_60 = 0;
        FUN_18002dbf0(&local_70,0,*(longlong *)(param_1 + 0x58) + 0xb,uVar15);
        plVar9 = (longlong *)FUN_180185d80(0x30);
        lVar14 = local_70;
        *plVar9 = 0;
        plVar9[1] = 0;
        *(undefined4 *)(plVar9 + 1) = 1;
        *(undefined4 *)((longlong)plVar9 + 0xc) = 1;
        *plVar9 = (longlong)std::_Ref_count_obj2<RaceBaseResult>::vftable;
        local_58 = plVar9 + 2;
        *local_58 = (longlong)RaceBaseResult::vftable;
        plVar9[3] = 0;
        plVar9[4] = 0;
        plVar9[5] = 0;
        plStack_50 = plVar9;
        if (plVar9 + 3 != &local_70) {
          local_b8 = plVar9;
          FUN_18002cd30(plVar9 + 3,local_70,lStack_68 - local_70);
        }
        local_b8 = plVar9 + 2;
        LOCK();
        *(int *)(plVar9 + 1) = (int)plVar9[1] + 1;
        UNLOCK();
        plStack_b0 = plVar9;
        uVar16 = FUN_1800841c0(param_1,&local_b8);
        LOCK();
        plVar1 = plVar9 + 1;
        lVar12 = *plVar1;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)lVar12 == 1) {
          uVar16 = (**(code **)*plVar9)(plVar9);
          LOCK();
          piVar2 = (int *)((longlong)plVar9 + 0xc);
          iVar3 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar3 == 1) {
            uVar16 = (**(code **)(*plVar9 + 8))(plVar9);
          }
        }
        if (lVar14 != 0) {
          lVar12 = lVar14;
          if (0xfff < (ulonglong)(local_60 - lVar14)) {
            lVar12 = *(longlong *)(lVar14 + -8);
            if (0x1f < (lVar14 - lVar12) - 8U) {
                    /* WARNING: Subroutine does not return */
              FUN_18018f678(uVar16,(local_60 - lVar14) + 0x27);
            }
          }
          thunk_FUN_180190730(lVar12);
        }
      }
      uVar8 = 1;
      if (lVar13 != 0) {
        uVar10 = (longlong)puVar5 - lVar13;
        lVar14 = lVar13;
        if (0xfff < uVar10) {
          uVar10 = uVar10 + 0x27;
          lVar14 = *(longlong *)(lVar13 + -8);
          if (0x1f < (lVar13 - lVar14) - 8U) {
                    /* WARNING: Subroutine does not return */
            FUN_18018f678();
          }
        }
        thunk_FUN_180190730(lVar14,uVar10);
      }
    }
    else {
      local_a8 = 0;
      puStack_a0 = (undefined1 *)0x0;
      local_90 = 0;
      FUN_180019380(&local_a8,"check nv id fail!",0x11);
      uVar4 = *(undefined2 *)(param_1 + 0x38);
      uVar8 = FUN_180073fc0();
      FUN_180074110(uVar8,uVar4,param_1 + 0x90,&local_a8);
      FUN_180017790(&local_a8);
      uVar8 = 0;
    }
    if (lVar6 != 0) {
      uVar10 = (longlong)puVar7 - lVar6;
      lVar13 = lVar6;
      if (0xfff < uVar10) {
        uVar10 = uVar10 + 0x27;
        lVar13 = *(longlong *)(lVar6 + -8);
        if (0x1f < (lVar6 - lVar13) - 8U) {
                    /* WARNING: Subroutine does not return */
          FUN_18018f678();
        }
      }
      thunk_FUN_180190730(lVar13,uVar10);
    }
  }
  return uVar8;
}



// ==== FUN_180086ce0 @ 180086ce0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 * FUN_180086ce0(undefined8 *param_1,undefined2 param_2)

{
  undefined8 ****ppppuVar1;
  undefined8 *puVar2;
  undefined8 ****ppppuVar3;
  longlong lVar4;
  undefined1 auStack_d8 [32];
  char *local_b8;
  undefined8 local_b0;
  undefined8 ****local_a8 [2];
  longlong local_98;
  ulonglong uStack_90;
  undefined8 ***local_88;
  undefined8 ***pppuStack_80;
  undefined8 ***local_78;
  undefined8 ***pppuStack_70;
  undefined8 *local_68;
  undefined2 *local_58;
  undefined2 *puStack_50;
  longlong local_48;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  ulonglong local_38;
  
  local_38 = DAT_180225100 ^ (ulonglong)auStack_d8;
  puVar2 = param_1;
  local_68 = param_1;
  FUN_180083740();
  *puVar2 = RaceGetAwsRole::vftable;
  local_58 = (undefined2 *)0x0;
  puStack_50 = (undefined2 *)0x0;
  local_48 = 0;
  FUN_18001b120(&local_58,2);
  *local_58 = param_2;
  puStack_50 = local_58 + 1;
  FUN_180161430();
  FUN_1800026e0(local_a8,&local_58);
  if (local_58 != (undefined2 *)0x0) {
    if (0xfff < (ulonglong)(local_48 - (longlong)local_58)) {
      if (0x1f < (ulonglong)((longlong)local_58 + (-8 - *(longlong *)(local_58 + -4)))) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(*(longlong *)(local_58 + -4),(local_48 - (longlong)local_58) + 0x27);
      }
    }
    thunk_FUN_180190730();
  }
  if (uStack_90 - local_98 < 0xf) {
    local_b0 = 0xf;
    local_b8 = "RaceGetAwsRole(";
    ppppuVar1 = (undefined8 ****)FUN_18001b490(local_a8,0xf);
  }
  else {
    ppppuVar1 = local_a8;
    if (0xf < uStack_90) {
      ppppuVar1 = local_a8[0];
    }
    if (((undefined8 ****)0x1801e2d2e < ppppuVar1) ||
       ((char *)((longlong)ppppuVar1 + local_98) < "RaceGetAwsRole(")) {
      ppppuVar3 = (undefined8 ****)0xf;
    }
    else if ("RaceGetAwsRole(" < ppppuVar1) {
      ppppuVar3 = ppppuVar1 + -0x3003c5a4;
    }
    else {
      ppppuVar3 = (undefined8 ****)0x0;
    }
    lVar4 = local_98 + 1;
    local_98 = local_98 + 0xf;
    FUN_1801afa50((char *)((longlong)ppppuVar1 + 0xf),ppppuVar1,lVar4);
    FUN_1801afa50(ppppuVar1,"RaceGetAwsRole(",ppppuVar3);
    FUN_1801afa50((char *)((longlong)ppppuVar1 + (longlong)ppppuVar3),"" + (longlong)ppppuVar3,
                  0xf - (longlong)ppppuVar3);
    ppppuVar1 = local_a8;
  }
  local_88 = (undefined8 ***)0x0;
  pppuStack_80 = (undefined8 ***)0x0;
  local_78 = (undefined8 ***)0x0;
  pppuStack_70 = (undefined8 ***)0x0;
  local_88 = *ppppuVar1;
  pppuStack_80 = ppppuVar1[1];
  local_78 = ppppuVar1[2];
  pppuStack_70 = ppppuVar1[3];
  ppppuVar1[2] = (undefined8 ***)0x0;
  ppppuVar1[3] = (undefined8 ***)0xf;
  *(undefined1 *)ppppuVar1 = 0;
  puVar2 = (undefined8 *)FUN_180017990(&local_88,&DAT_1801d8eac,1);
  local_58 = (undefined2 *)*puVar2;
  puStack_50 = (undefined2 *)puVar2[1];
  local_48 = puVar2[2];
  uStack_40 = *(undefined4 *)(puVar2 + 3);
  uStack_3c = *(undefined4 *)((longlong)puVar2 + 0x1c);
  puVar2[2] = 0;
  puVar2[3] = 0xf;
  *(undefined1 *)puVar2 = 0;
  FUN_180015d60(param_1 + 0x12,&local_58);
  FUN_180017790(&local_58);
  FUN_180017790(&local_88);
  FUN_180017790(local_a8);
  *(undefined2 *)((longlong)param_1 + 0xb4) = 0xcc4;
  *(undefined2 *)((longlong)param_1 + 0x3a) = 0x5b5a;
  *(undefined4 *)(param_1 + 8) = 6;
  *(undefined1 *)(param_1 + 10) = 1;
  return param_1;
}



// ==== FUN_180086f30 @ 180086f30 ====

undefined8 * FUN_180086f30(undefined8 *param_1,ulonglong param_2)

{
  *param_1 = RaceGetAwsRole::vftable;
  FUN_180083850();
  if ((param_2 & 1) != 0) {
    thunk_FUN_180190730(param_1,0xd0);
  }
  return param_1;
}



// ==== FUN_180086f70 @ 180086f70 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 * FUN_180086f70(undefined8 *param_1,undefined2 param_2)

{
  undefined8 ****ppppuVar1;
  undefined8 *puVar2;
  undefined8 ****ppppuVar3;
  longlong lVar4;
  undefined1 auStack_d8 [32];
  char *local_b8;
  undefined8 local_b0;
  undefined8 ****local_a8 [2];
  longlong local_98;
  ulonglong uStack_90;
  undefined8 ***local_88;
  undefined8 ***pppuStack_80;
  undefined8 ***local_78;
  undefined8 ***pppuStack_70;
  undefined8 *local_68;
  undefined2 *local_58;
  undefined2 *puStack_50;
  longlong local_48;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  ulonglong local_38;
  
  local_38 = DAT_180225100 ^ (ulonglong)auStack_d8;
  puVar2 = param_1;
  local_68 = param_1;
  FUN_180083740();
  *puVar2 = RaceCustomRace::vftable;
  *(undefined2 *)(puVar2 + 0x1a) = 0;
  puVar2[0x1b] = 0;
  puVar2[0x1c] = 0;
  puVar2[0x1d] = 0;
  *(undefined1 *)(puVar2 + 0x1e) = 0x5b;
  local_58 = (undefined2 *)0x0;
  puStack_50 = (undefined2 *)0x0;
  local_48 = 0;
  FUN_18001b120(&local_58,2);
  *local_58 = param_2;
  puStack_50 = local_58 + 1;
  FUN_180161430();
  FUN_1800026e0(local_a8,&local_58);
  if (local_58 != (undefined2 *)0x0) {
    if (0xfff < (ulonglong)(local_48 - (longlong)local_58)) {
      if (0x1f < (ulonglong)((longlong)local_58 + (-8 - *(longlong *)(local_58 + -4)))) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(*(longlong *)(local_58 + -4),(local_48 - (longlong)local_58) + 0x27);
      }
    }
    thunk_FUN_180190730();
  }
  if (uStack_90 - local_98 < 0xf) {
    local_b0 = 0xf;
    local_b8 = "RaceCustomRace(";
    ppppuVar1 = (undefined8 ****)FUN_18001b490(local_a8,0xf);
  }
  else {
    ppppuVar1 = local_a8;
    if (0xf < uStack_90) {
      ppppuVar1 = local_a8[0];
    }
    if (((undefined8 ****)0x1801e2d56 < ppppuVar1) ||
       ((char *)((longlong)ppppuVar1 + local_98) < "RaceCustomRace(")) {
      ppppuVar3 = (undefined8 ****)0xf;
    }
    else if ("RaceCustomRace(" < ppppuVar1) {
      ppppuVar3 = ppppuVar1 + -0x3003c5a9;
    }
    else {
      ppppuVar3 = (undefined8 ****)0x0;
    }
    lVar4 = local_98 + 1;
    local_98 = local_98 + 0xf;
    FUN_1801afa50((char *)((longlong)ppppuVar1 + 0xf),ppppuVar1,lVar4);
    FUN_1801afa50(ppppuVar1,"RaceCustomRace(",ppppuVar3);
    FUN_1801afa50((char *)((longlong)ppppuVar1 + (longlong)ppppuVar3),"" + (longlong)ppppuVar3,
                  0xf - (longlong)ppppuVar3);
    ppppuVar1 = local_a8;
  }
  local_88 = (undefined8 ***)0x0;
  pppuStack_80 = (undefined8 ***)0x0;
  local_78 = (undefined8 ***)0x0;
  pppuStack_70 = (undefined8 ***)0x0;
  local_88 = *ppppuVar1;
  pppuStack_80 = ppppuVar1[1];
  local_78 = ppppuVar1[2];
  pppuStack_70 = ppppuVar1[3];
  ppppuVar1[2] = (undefined8 ***)0x0;
  ppppuVar1[3] = (undefined8 ***)0xf;
  *(undefined1 *)ppppuVar1 = 0;
  puVar2 = (undefined8 *)FUN_180017990(&local_88,&DAT_1801d8eac,1);
  local_58 = (undefined2 *)*puVar2;
  puStack_50 = (undefined2 *)puVar2[1];
  local_48 = puVar2[2];
  uStack_40 = *(undefined4 *)(puVar2 + 3);
  uStack_3c = *(undefined4 *)((longlong)puVar2 + 0x1c);
  puVar2[2] = 0;
  puVar2[3] = 0xf;
  *(undefined1 *)puVar2 = 0;
  FUN_180015d60(param_1 + 0x12,&local_58);
  FUN_180017790(&local_58);
  FUN_180017790(&local_88);
  FUN_180017790(local_a8);
  return param_1;
}



// ==== FUN_1800871c0 @ 1800871c0 ====

undefined8 * FUN_1800871c0(undefined8 *param_1,uint param_2)

{
  longlong lVar1;
  longlong lVar2;
  
  *param_1 = RaceCustomRace::vftable;
  lVar1 = param_1[0x1b];
  if (lVar1 != 0) {
    lVar2 = lVar1;
    if (0xfff < (ulonglong)(param_1[0x1d] - lVar1)) {
      lVar2 = *(longlong *)(lVar1 + -8);
      if (0x1f < (lVar1 - lVar2) - 8U) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(lVar1 - lVar2,(param_1[0x1d] - lVar1) + 0x27);
      }
    }
    thunk_FUN_180190730(lVar2);
    param_1[0x1b] = 0;
    param_1[0x1c] = 0;
    param_1[0x1d] = 0;
  }
  FUN_180083850(param_1);
  if ((param_2 & 1) != 0) {
    thunk_FUN_180190730(param_1,0xf8);
  }
  return param_1;
}



// ==== FUN_180087260 @ 180087260 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_180087260(longlong param_1,undefined8 param_2)

{
  int *piVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong *plVar7;
  ulonglong uVar8;
  undefined1 *puVar9;
  ulonglong uVar10;
  ushort uVar11;
  longlong lVar12;
  undefined1 auStack_98 [32];
  undefined1 local_78 [4];
  undefined4 local_74;
  undefined8 local_70;
  longlong *local_68;
  longlong local_60;
  longlong *plStack_58;
  undefined1 *local_50;
  ulonglong local_48;
  
  local_48 = DAT_180225100 ^ (ulonglong)auStack_98;
  uVar11 = 0;
  local_74 = 0;
  local_70 = param_2;
  if ((*(uint *)(param_1 + 0xb0) & 0xfffffffd) == 0) {
    local_78[0] = 0;
    puVar9 = *(undefined1 **)(param_1 + 0x78);
    if (puVar9 != *(undefined1 **)(param_1 + 0x80)) {
      *puVar9 = 0;
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
      goto LAB_1800873ec;
    }
  }
  else {
    if ((*(uint *)(param_1 + 0xb0) - 1 & 0xfffffffd) != 0) goto LAB_1800873ec;
    uVar6 = FUN_1801501a0();
    plVar7 = (longlong *)FUN_180150e70(uVar6,&local_60,*(undefined2 *)(param_1 + 0x38));
    bVar3 = false;
    local_74 = 1;
    if (*(int *)(*plVar7 + 0x270) == 1) {
LAB_18008730c:
      bVar4 = true;
    }
    else {
      uVar6 = FUN_1801501a0();
      plVar7 = (longlong *)FUN_180150e70(uVar6,&local_70,*(undefined2 *)(param_1 + 0x38));
      bVar3 = true;
      if (*(int *)(*plVar7 + 0x270) == 4) goto LAB_18008730c;
      bVar4 = false;
    }
    if ((bVar3) && (local_68 != (longlong *)0x0)) {
      LOCK();
      plVar7 = local_68 + 1;
      lVar5 = *plVar7;
      *(int *)plVar7 = (int)*plVar7 + -1;
      UNLOCK();
      if ((int)lVar5 == 1) {
        (**(code **)*local_68)(local_68);
        LOCK();
        piVar1 = (int *)((longlong)local_68 + 0xc);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 == 1) {
          (**(code **)(*local_68 + 8))(local_68);
        }
      }
    }
    if (plStack_58 != (longlong *)0x0) {
      LOCK();
      plVar7 = plStack_58 + 1;
      lVar5 = *plVar7;
      *(int *)plVar7 = (int)*plVar7 + -1;
      UNLOCK();
      if ((int)lVar5 == 1) {
        (**(code **)*plStack_58)(plStack_58);
        LOCK();
        piVar1 = (int *)((longlong)plStack_58 + 0xc);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 == 1) {
          (**(code **)(*plStack_58 + 8))(plStack_58);
        }
      }
    }
    puVar9 = *(undefined1 **)(param_1 + 0x78);
    if (bVar4) {
      local_78[0] = *(undefined1 *)(param_1 + 0x38);
      if (puVar9 == *(undefined1 **)(param_1 + 0x80)) {
        FUN_18001b340(param_1 + 0x70,puVar9,local_78);
      }
      else {
        *puVar9 = local_78[0];
        *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
      }
      goto LAB_1800873ec;
    }
    local_78[0] = 0x80;
    if (puVar9 != *(undefined1 **)(param_1 + 0x80)) {
      *puVar9 = 0x80;
      *(longlong *)(param_1 + 0x78) = *(longlong *)(param_1 + 0x78) + 1;
      goto LAB_1800873ec;
    }
  }
  FUN_18001b340(param_1 + 0x70,puVar9,local_78);
LAB_1800873ec:
  *(undefined1 *)(param_1 + 0x3b) = *(undefined1 *)(param_1 + 0xf0);
  local_60 = 0;
  plStack_58 = (longlong *)0x0;
  local_50 = (undefined1 *)0x0;
  FUN_18001b340(&local_60,0,*(longlong *)(param_1 + 0xd8) + 4);
  if (plStack_58 == (longlong *)local_50) {
    FUN_18001b340(&local_60,plStack_58);
  }
  else {
    *(undefined1 *)plStack_58 = *(undefined1 *)(*(longlong *)(param_1 + 0xd8) + 5);
    plStack_58 = (longlong *)((longlong)plStack_58 + 1);
  }
  puVar9 = local_50;
  lVar5 = local_60;
  uVar10 = 0;
  uVar8 = 0;
  do {
    if ((ulonglong)((longlong)plStack_58 - local_60) <= uVar10) break;
    uVar11 = uVar11 | (ushort)*(byte *)(local_60 + uVar10) << ((byte)uVar8 & 0x1f);
    uVar10 = uVar10 + 1;
    uVar8 = uVar8 + 8;
  } while (uVar8 < 0x10);
  *(ushort *)(param_1 + 0xd0) = uVar11;
  FUN_18002dbf0(param_1 + 0x70,*(undefined8 *)(param_1 + 0x78),*(longlong *)(param_1 + 0xd8),
                *(longlong *)(param_1 + 0xe0) - *(longlong *)(param_1 + 0xd8));
  FUN_18002c1c0(param_2,param_1 + 0x70);
  if (lVar5 != 0) {
    uVar8 = (longlong)puVar9 - lVar5;
    lVar12 = lVar5;
    if (0xfff < uVar8) {
      uVar8 = uVar8 + 0x27;
      lVar12 = *(longlong *)(lVar5 + -8);
      if (0x1f < (lVar5 - lVar12) - 8U) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678();
      }
    }
    thunk_FUN_180190730(lVar12,uVar8);
  }
  return param_2;
}



// ==== FUN_180087520 @ 180087520 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_180087520(longlong param_1,longlong *param_2)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  char cVar4;
  longlong lVar5;
  undefined1 *puVar6;
  longlong *plVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  longlong lVar10;
  ushort uVar11;
  undefined8 uVar12;
  undefined1 auStack_88 [32];
  longlong *local_68;
  longlong *plStack_60;
  longlong local_58;
  undefined1 *puStack_50;
  undefined1 *local_48;
  longlong *local_40;
  longlong *plStack_38;
  ulonglong local_30;
  
  local_30 = DAT_180225100 ^ (ulonglong)auStack_88;
  cVar4 = *(char *)(*param_2 + 2);
  local_58 = 0;
  puStack_50 = (undefined1 *)0x0;
  local_48 = (undefined1 *)0x0;
  FUN_18001b340(&local_58,0,*param_2 + 5);
  if (puStack_50 == local_48) {
    FUN_18001b340(&local_58,puStack_50);
  }
  else {
    *puStack_50 = *(undefined1 *)(*param_2 + 6);
    puStack_50 = puStack_50 + 1;
  }
  puVar6 = local_48;
  lVar5 = local_58;
  uVar11 = 0;
  uVar9 = 0;
  uVar8 = 0;
  do {
    if ((ulonglong)((longlong)puStack_50 - local_58) <= uVar9) break;
    uVar11 = uVar11 | (ushort)*(byte *)(local_58 + uVar9) << ((byte)uVar8 & 0x1f);
    uVar9 = uVar9 + 1;
    uVar8 = uVar8 + 8;
  } while (uVar8 < 0x10);
  if ((cVar4 == *(char *)(param_1 + 0x3b)) && (uVar11 == *(ushort *)(param_1 + 0xd0))) {
    *(undefined1 *)(param_1 + 0x88) = 1;
    plVar7 = (longlong *)FUN_180185d80(0x30);
    *plVar7 = 0;
    plVar7[1] = 0;
    *(undefined4 *)(plVar7 + 1) = 1;
    *(undefined4 *)((longlong)plVar7 + 0xc) = 1;
    *plVar7 = (longlong)std::_Ref_count_obj2<RaceBaseResult>::vftable;
    plVar1 = plVar7 + 2;
    *plVar1 = (longlong)RaceBaseResult::vftable;
    plVar7[3] = 0;
    plVar7[4] = 0;
    plVar7[5] = 0;
    local_40 = plVar1;
    plStack_38 = plVar7;
    if (plVar7 + 3 != param_2) {
      local_68 = plVar7;
      FUN_18002cd30(plVar7 + 3,*param_2,param_2[1] - *param_2);
    }
    LOCK();
    *(int *)(plVar7 + 1) = (int)plVar7[1] + 1;
    UNLOCK();
    local_68 = plVar1;
    plStack_60 = plVar7;
    FUN_1800841c0(param_1,&local_68);
    uVar12 = 1;
    LOCK();
    plVar1 = plVar7 + 1;
    lVar10 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar10 == 1) {
      (**(code **)*plVar7)(plVar7);
      LOCK();
      piVar2 = (int *)((longlong)plVar7 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar7 + 8))(plVar7);
      }
    }
  }
  else {
    uVar12 = 0;
  }
  if (lVar5 != 0) {
    uVar8 = (longlong)puVar6 - lVar5;
    lVar10 = lVar5;
    if (0xfff < uVar8) {
      uVar8 = uVar8 + 0x27;
      lVar10 = *(longlong *)(lVar5 + -8);
      if (0x1f < (lVar5 - lVar10) - 8U) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678();
      }
    }
    thunk_FUN_180190730(lVar10,uVar8);
  }
  return uVar12;
}



// ==== FUN_180087730 @ 180087730 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 * FUN_180087730(undefined8 *param_1,undefined2 param_2)

{
  undefined8 ****ppppuVar1;
  undefined8 *puVar2;
  undefined8 ****ppppuVar3;
  longlong lVar4;
  undefined1 auStack_d8 [32];
  char *local_b8;
  undefined8 local_b0;
  undefined8 ****local_a8 [2];
  longlong local_98;
  ulonglong uStack_90;
  undefined8 ***local_88;
  undefined8 ***pppuStack_80;
  undefined8 ***local_78;
  undefined8 ***pppuStack_70;
  undefined8 *local_68;
  undefined2 *local_58;
  undefined2 *puStack_50;
  longlong local_48;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  ulonglong local_38;
  
  local_38 = DAT_180225100 ^ (ulonglong)auStack_d8;
  puVar2 = param_1;
  local_68 = param_1;
  FUN_180083740();
  *puVar2 = RaceGetBusyLightStatus::vftable;
  local_58 = (undefined2 *)0x0;
  puStack_50 = (undefined2 *)0x0;
  local_48 = 0;
  FUN_18001b120(&local_58,2);
  *local_58 = param_2;
  puStack_50 = local_58 + 1;
  FUN_180161430();
  FUN_1800026e0(local_a8,&local_58);
  if (local_58 != (undefined2 *)0x0) {
    if (0xfff < (ulonglong)(local_48 - (longlong)local_58)) {
      if (0x1f < (ulonglong)((longlong)local_58 + (-8 - *(longlong *)(local_58 + -4)))) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(*(longlong *)(local_58 + -4),(local_48 - (longlong)local_58) + 0x27);
      }
    }
    thunk_FUN_180190730();
  }
  if (uStack_90 - local_98 < 0x17) {
    local_b0 = 0x17;
    local_b8 = "RaceGetBusyLightStatus(";
    ppppuVar1 = (undefined8 ****)FUN_18001b490(local_a8,0x17);
  }
  else {
    ppppuVar1 = local_a8;
    if (0xf < uStack_90) {
      ppppuVar1 = local_a8[0];
    }
    if (((undefined8 ****)0x1801e2d86 < ppppuVar1) ||
       ((char *)((longlong)ppppuVar1 + local_98) < "RaceGetBusyLightStatus(")) {
      ppppuVar3 = (undefined8 ****)0x17;
    }
    else if ("RaceGetBusyLightStatus(" < ppppuVar1) {
      ppppuVar3 = ppppuVar1 + -0x3003c5ae;
    }
    else {
      ppppuVar3 = (undefined8 ****)0x0;
    }
    lVar4 = local_98 + 1;
    local_98 = local_98 + 0x17;
    FUN_1801afa50((char *)((longlong)ppppuVar1 + 0x17),ppppuVar1,lVar4);
    FUN_1801afa50(ppppuVar1,"RaceGetBusyLightStatus(",ppppuVar3);
    FUN_1801afa50((char *)((longlong)ppppuVar1 + (longlong)ppppuVar3),"" + (longlong)ppppuVar3,
                  0x17 - (longlong)ppppuVar3);
    ppppuVar1 = local_a8;
  }
  local_88 = (undefined8 ***)0x0;
  pppuStack_80 = (undefined8 ***)0x0;
  local_78 = (undefined8 ***)0x0;
  pppuStack_70 = (undefined8 ***)0x0;
  local_88 = *ppppuVar1;
  pppuStack_80 = ppppuVar1[1];
  local_78 = ppppuVar1[2];
  pppuStack_70 = ppppuVar1[3];
  ppppuVar1[2] = (undefined8 ***)0x0;
  ppppuVar1[3] = (undefined8 ***)0xf;
  *(undefined1 *)ppppuVar1 = 0;
  puVar2 = (undefined8 *)FUN_180017990(&local_88,&DAT_1801d8eac,1);
  local_58 = (undefined2 *)*puVar2;
  puStack_50 = (undefined2 *)puVar2[1];
  local_48 = puVar2[2];
  uStack_40 = *(undefined4 *)(puVar2 + 3);
  uStack_3c = *(undefined4 *)((longlong)puVar2 + 0x1c);
  puVar2[2] = 0;
  puVar2[3] = 0xf;
  *(undefined1 *)puVar2 = 0;
  FUN_180015d60(param_1 + 0x12,&local_58);
  FUN_180017790(&local_58);
  FUN_180017790(&local_88);
  FUN_180017790(local_a8);
  *(undefined2 *)((longlong)param_1 + 0xb4) = 0x23;
  *(undefined2 *)((longlong)param_1 + 0x3a) = 0x5b5a;
  return param_1;
}



// ==== FUN_180087970 @ 180087970 ====

undefined8 * FUN_180087970(undefined8 *param_1,ulonglong param_2)

{
  *param_1 = RaceGetBusyLightStatus::vftable;
  FUN_180083850();
  if ((param_2 & 1) != 0) {
    thunk_FUN_180190730(param_1,0xd0);
  }
  return param_1;
}



// ==== FUN_1800879b0 @ 1800879b0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined1 FUN_1800879b0(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  char cVar5;
  undefined1 uVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined4 uVar9;
  undefined4 extraout_XMM0_Da;
  undefined4 extraout_XMM0_Da_00;
  undefined1 auStack_88 [32];
  undefined1 local_68 [8];
  longlong *local_60;
  longlong *plStack_58;
  longlong local_50;
  longlong lStack_48;
  longlong local_40;
  longlong *local_38;
  longlong *plStack_30;
  ulonglong local_28;
  
  local_28 = DAT_180225100 ^ (ulonglong)auStack_88;
  cVar5 = FUN_180084260();
  uVar6 = 0;
  if (cVar5 != '\0') {
    local_68[0] = *(undefined1 *)(*(longlong *)(param_1 + 0x58) + 7);
    local_50 = 0;
    lStack_48 = 0;
    local_40 = 0;
    FUN_18001b340(&local_50,0,local_68);
    plVar7 = (longlong *)FUN_180185d80(0x30);
    lVar4 = local_50;
    *plVar7 = 0;
    plVar7[1] = 0;
    *(undefined4 *)(plVar7 + 1) = 1;
    *(undefined4 *)((longlong)plVar7 + 0xc) = 1;
    *plVar7 = (longlong)std::_Ref_count_obj2<RaceBaseResult>::vftable;
    plVar1 = plVar7 + 2;
    *plVar1 = (longlong)RaceBaseResult::vftable;
    plVar7[3] = 0;
    plVar7[4] = 0;
    plVar7[5] = 0;
    local_38 = plVar1;
    plStack_30 = plVar7;
    if (plVar7 + 3 != &local_50) {
      local_60 = plVar7;
      FUN_18002cd30(plVar7 + 3,local_50,lStack_48 - local_50);
    }
    LOCK();
    *(int *)(plVar7 + 1) = (int)plVar7[1] + 1;
    UNLOCK();
    local_60 = plVar1;
    plStack_58 = plVar7;
    uVar9 = FUN_1800841c0(param_1,&local_60);
    LOCK();
    plVar1 = plVar7 + 1;
    lVar8 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar8 == 1) {
      (**(code **)*plVar7)(plVar7);
      LOCK();
      piVar2 = (int *)((longlong)plVar7 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      uVar9 = extraout_XMM0_Da;
      if (iVar3 == 1) {
        (**(code **)(*plVar7 + 8))(plVar7);
        uVar9 = extraout_XMM0_Da_00;
      }
    }
    if (lVar4 != 0) {
      lVar8 = lVar4;
      if (0xfff < (ulonglong)(local_40 - lVar4)) {
        lVar8 = *(longlong *)(lVar4 + -8);
        if (0x1f < (lVar4 - lVar8) - 8U) {
                    /* WARNING: Subroutine does not return */
          FUN_18018f678(uVar9,(local_40 - lVar4) + 0x27);
        }
      }
      thunk_FUN_180190730(lVar8);
    }
    uVar6 = 1;
  }
  return uVar6;
}



// ==== FUN_180087b40 @ 180087b40 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 * FUN_180087b40(undefined8 *param_1,undefined2 param_2)

{
  undefined8 ****ppppuVar1;
  undefined8 *puVar2;
  undefined8 ****ppppuVar3;
  longlong lVar4;
  undefined1 auStack_d8 [32];
  char *local_b8;
  undefined8 local_b0;
  undefined8 ****local_a8 [2];
  longlong local_98;
  ulonglong uStack_90;
  undefined8 ***local_88;
  undefined8 ***pppuStack_80;
  undefined8 ***local_78;
  undefined8 ***pppuStack_70;
  undefined8 *local_68;
  undefined2 *local_58;
  undefined2 *puStack_50;
  longlong local_48;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  ulonglong local_38;
  
  local_38 = DAT_180225100 ^ (ulonglong)auStack_d8;
  puVar2 = param_1;
  local_68 = param_1;
  FUN_180083740();
  *puVar2 = RaceGetDisInformation::vftable;
  *(undefined1 *)(puVar2 + 0x1a) = 0;
  local_58 = (undefined2 *)0x0;
  puStack_50 = (undefined2 *)0x0;
  local_48 = 0;
  FUN_18001b120(&local_58,2);
  *local_58 = param_2;
  puStack_50 = local_58 + 1;
  FUN_180161430();
  FUN_1800026e0(local_a8,&local_58);
  if (local_58 != (undefined2 *)0x0) {
    if (0xfff < (ulonglong)(local_48 - (longlong)local_58)) {
      if (0x1f < (ulonglong)((longlong)local_58 + (-8 - *(longlong *)(local_58 + -4)))) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(*(longlong *)(local_58 + -4),(local_48 - (longlong)local_58) + 0x27);
      }
    }
    thunk_FUN_180190730();
  }
  if (uStack_90 - local_98 < 0x16) {
    local_b0 = 0x16;
    local_b8 = "RaceGetDisInformation(";
    ppppuVar1 = (undefined8 ****)FUN_18001b490(local_a8,0x16);
  }
  else {
    ppppuVar1 = local_a8;
    if (0xf < uStack_90) {
      ppppuVar1 = local_a8[0];
    }
    if (((undefined8 ****)0x1801e2db5 < ppppuVar1) ||
       ((char *)((longlong)ppppuVar1 + local_98) < "RaceGetDisInformation(")) {
      ppppuVar3 = (undefined8 ****)0x16;
    }
    else if ("RaceGetDisInformation(" < ppppuVar1) {
      ppppuVar3 = ppppuVar1 + -0x3003c5b4;
    }
    else {
      ppppuVar3 = (undefined8 ****)0x0;
    }
    lVar4 = local_98 + 1;
    local_98 = local_98 + 0x16;
    FUN_1801afa50((char *)((longlong)ppppuVar1 + 0x16),ppppuVar1,lVar4);
    FUN_1801afa50(ppppuVar1,"RaceGetDisInformation(",ppppuVar3);
    FUN_1801afa50((char *)((longlong)ppppuVar1 + (longlong)ppppuVar3),"" + (longlong)ppppuVar3,
                  0x16 - (longlong)ppppuVar3);
    ppppuVar1 = local_a8;
  }
  local_88 = (undefined8 ***)0x0;
  pppuStack_80 = (undefined8 ***)0x0;
  local_78 = (undefined8 ***)0x0;
  pppuStack_70 = (undefined8 ***)0x0;
  local_88 = *ppppuVar1;
  pppuStack_80 = ppppuVar1[1];
  local_78 = ppppuVar1[2];
  pppuStack_70 = ppppuVar1[3];
  ppppuVar1[2] = (undefined8 ***)0x0;
  ppppuVar1[3] = (undefined8 ***)0xf;
  *(undefined1 *)ppppuVar1 = 0;
  puVar2 = (undefined8 *)FUN_180017990(&local_88,&DAT_1801d8eac,1);
  local_58 = (undefined2 *)*puVar2;
  puStack_50 = (undefined2 *)puVar2[1];
  local_48 = puVar2[2];
  uStack_40 = *(undefined4 *)(puVar2 + 3);
  uStack_3c = *(undefined4 *)((longlong)puVar2 + 0x1c);
  puVar2[2] = 0;
  puVar2[3] = 0xf;
  *(undefined1 *)puVar2 = 0;
  FUN_180015d60(param_1 + 0x12,&local_58);
  FUN_180017790(&local_58);
  FUN_180017790(&local_88);
  FUN_180017790(local_a8);
  *(undefined2 *)((longlong)param_1 + 0xb4) = 99;
  *(undefined2 *)((longlong)param_1 + 0x3a) = 0x5b5a;
  return param_1;
}



// ==== FUN_180087d90 @ 180087d90 ====

undefined8 * FUN_180087d90(undefined8 *param_1,ulonglong param_2)

{
  *param_1 = RaceGetDisInformation::vftable;
  FUN_180083850();
  if ((param_2 & 1) != 0) {
    thunk_FUN_180190730(param_1,0xd8);
  }
  return param_1;
}



// ==== FUN_180087dd0 @ 180087dd0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined1 FUN_180087dd0(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  char cVar5;
  undefined1 uVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong lVar9;
  longlong lVar10;
  ulonglong uVar11;
  undefined1 auStack_88 [32];
  longlong *local_68;
  longlong *plStack_60;
  longlong local_58;
  longlong lStack_50;
  longlong local_48;
  longlong *local_40;
  longlong *plStack_38;
  ulonglong local_30;
  
  local_30 = DAT_180225100 ^ (ulonglong)auStack_88;
  cVar5 = FUN_180084260();
  uVar6 = 0;
  if (cVar5 != '\0') {
    local_58 = 0;
    lStack_50 = 0;
    local_48 = 0;
    uVar11 = (*(longlong *)(param_1 + 0x60) - *(longlong *)(param_1 + 0x58)) - 7;
    if (uVar11 == 0) {
      lVar9 = 0;
    }
    else {
      if (0x7fffffffffffffff < uVar11) {
                    /* WARNING: Subroutine does not return */
        FUN_180017770();
      }
      FUN_18001b120(&local_58,uVar11);
      lVar9 = local_58;
      FUN_1801b0190(local_58,0,uVar11);
      lStack_50 = lVar9 + uVar11;
    }
    lVar4 = local_48;
    lVar10 = lStack_50;
    lVar8 = *(longlong *)(param_1 + 0x58) + 7;
    FUN_1801afa50(lVar9,lVar8,*(longlong *)(param_1 + 0x60) - lVar8);
    plVar7 = (longlong *)FUN_180185d80(0x30);
    *plVar7 = 0;
    plVar7[1] = 0;
    *(undefined4 *)(plVar7 + 1) = 1;
    *(undefined4 *)((longlong)plVar7 + 0xc) = 1;
    *plVar7 = (longlong)std::_Ref_count_obj2<RaceBaseResult>::vftable;
    plVar1 = plVar7 + 2;
    *plVar1 = (longlong)RaceBaseResult::vftable;
    plVar7[3] = 0;
    plVar7[4] = 0;
    plVar7[5] = 0;
    local_40 = plVar1;
    plStack_38 = plVar7;
    if (plVar7 + 3 != &local_58) {
      local_68 = plVar7;
      FUN_18002cd30(plVar7 + 3,lVar9,lVar10 - lVar9);
    }
    LOCK();
    *(int *)(plVar7 + 1) = (int)plVar7[1] + 1;
    UNLOCK();
    local_68 = plVar1;
    plStack_60 = plVar7;
    FUN_1800841c0(param_1,&local_68);
    LOCK();
    plVar1 = plVar7 + 1;
    lVar10 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)lVar10 == 1) {
      (**(code **)*plVar7)(plVar7);
      LOCK();
      piVar2 = (int *)((longlong)plVar7 + 0xc);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        (**(code **)(*plVar7 + 8))(plVar7);
      }
    }
    if (lVar9 != 0) {
      uVar11 = lVar4 - lVar9;
      lVar10 = lVar9;
      if (0xfff < uVar11) {
        uVar11 = uVar11 + 0x27;
        lVar10 = *(longlong *)(lVar9 + -8);
        if (0x1f < (lVar9 - lVar10) - 8U) {
                    /* WARNING: Subroutine does not return */
          FUN_18018f678();
        }
      }
      thunk_FUN_180190730(lVar10,uVar11);
    }
    uVar6 = 1;
  }
  return uVar6;
}



// ==== FUN_180087fc0 @ 180087fc0 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 * FUN_180087fc0(undefined8 *param_1,undefined2 param_2)

{
  undefined8 ****ppppuVar1;
  undefined8 *puVar2;
  undefined8 ****ppppuVar3;
  longlong lVar4;
  undefined1 auStack_d8 [32];
  char *local_b8;
  undefined8 local_b0;
  undefined8 ****local_a8 [2];
  longlong local_98;
  ulonglong uStack_90;
  undefined8 ***local_88;
  undefined8 ***pppuStack_80;
  undefined8 ***local_78;
  undefined8 ***pppuStack_70;
  undefined8 *local_68;
  undefined2 *local_58;
  undefined2 *puStack_50;
  longlong local_48;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  ulonglong local_38;
  
  local_38 = DAT_180225100 ^ (ulonglong)auStack_d8;
  puVar2 = param_1;
  local_68 = param_1;
  FUN_180083740();
  *puVar2 = RaceGetEDRDeviceName::vftable;
  local_58 = (undefined2 *)0x0;
  puStack_50 = (undefined2 *)0x0;
  local_48 = 0;
  FUN_18001b120(&local_58,2);
  *local_58 = param_2;
  puStack_50 = local_58 + 1;
  FUN_180161430();
  FUN_1800026e0(local_a8,&local_58);
  if (local_58 != (undefined2 *)0x0) {
    if (0xfff < (ulonglong)(local_48 - (longlong)local_58)) {
      if (0x1f < (ulonglong)((longlong)local_58 + (-8 - *(longlong *)(local_58 + -4)))) {
                    /* WARNING: Subroutine does not return */
        FUN_18018f678(*(longlong *)(local_58 + -4),(local_48 - (longlong)local_58) + 0x27);
      }
    }
    thunk_FUN_180190730();
  }
  if (uStack_90 - local_98 < 0x15) {
    local_b0 = 0x15;
    local_b8 = "RaceGetEDRDeviceName(";
    ppppuVar1 = (undefined8 ****)FUN_18001b490(local_a8,0x15);
  }
  else {
    ppppuVar1 = local_a8;
    if (0xf < uStack_90) {
      ppppuVar1 = local_a8[0];
    }
    if (((undefined8 ****)0x1801e2de4 < ppppuVar1) ||
       ((char *)((longlong)ppppuVar1 + local_98) < "RaceGetEDRDeviceName(")) {
      ppppuVar3 = (undefined8 ****)0x15;
    }
    else if ("RaceGetEDRDeviceName(" < ppppuVar1) {
      ppppuVar3 = ppppuVar1 + -0x3003c5ba;
    }
    else {
      ppppuVar3 = (undefined8 ****)0x0;
    }
    lVar4 = local_98 + 1;
    local_98 = local_98 + 0x15;
    FUN_1801afa50((char *)((longlong)ppppuVar1 + 0x15),ppppuVar1,lVar4);
    FUN_1801afa50(ppppuVar1,"RaceGetEDRDeviceName(",ppppuVar3);
    FUN_1801afa50((char *)((longlong)ppppuVar1 + (longlong)ppppuVar3),"" + (longlong)ppppuVar3,
                  0x15 - (longlong)ppppuVar3);
    ppppuVar1 = local_a8;
  }
  local_88 = (undefined8 ***)0x0;
  pppuStack_80 = (undefined8 ***)0x0;
  local_78 = (undefined8 ***)0x0;
  pppuStack_70 = (undefined8 ***)0x0;
  local_88 = *ppppuVar1;
  pppuStack_80 = ppppuVar1[1];
  local_78 = ppppuVar1[2];
  pppuStack_70 = ppppuVar1[3];
  ppppuVar1[2] = (undefined8 ***)0x0;
  ppppuVar1[3] = (undefined8 ***)0xf;
  *(undefined1 *)ppppuVar1 = 0;
  puVar2 = (undefined8 *)FUN_180017990(&local_88,&DAT_1801d8eac,1);
  local_58 = (undefined2 *)*puVar2;
  puStack_50 = (undefined2 *)puVar2[1];
  local_48 = puVar2[2];
  uStack_40 = *(undefined4 *)(puVar2 + 3);
  uStack_3c = *(undefined4 *)((longlong)puVar2 + 0x1c);
  puVar2[2] = 0;
  puVar2[3] = 0xf;
  *(undefined1 *)puVar2 = 0;
  FUN_180015d60(param_1 + 0x12,&local_58);
  FUN_180017790(&local_58);
  FUN_180017790(&local_88);
  FUN_180017790(local_a8);
  *(undefined2 *)((longlong)param_1 + 0xb4) = 0xcc6;
  *(undefined2 *)((longlong)param_1 + 0x3a) = 0x5b5a;
  return param_1;
}



