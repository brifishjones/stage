# Microsoft Developer Studio Project File - Name="stage" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=stage - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "stage.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "stage.mak" CFG="stage - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "stage - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "stage - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "stage - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "stage - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D _WIN32_WINNT=0x4000 /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib advapi32.lib /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "stage - Win32 Release"
# Name "stage - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Dib.cpp
# End Source File
# Begin Source File

SOURCE=.\Dibpal.cpp
# End Source File
# Begin Source File

SOURCE=.\GripperDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Image.cpp
# End Source File
# Begin Source File

SOURCE=.\IpFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\stage.cpp
# End Source File
# Begin Source File

SOURCE=.\stage.rc
# End Source File
# Begin Source File

SOURCE=.\StageAnalysisDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageBarCodeReaderDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageBarrettHandDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageCameraDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageChooseDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\StageChooseName.cpp
# End Source File
# Begin Source File

SOURCE=.\StageConveyorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageDeviceTransformation.cpp
# End Source File
# Begin Source File

SOURCE=.\StageDeviceTree.cpp
# End Source File
# Begin Source File

SOURCE=.\stageDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\StageEyeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StageEyeMotion.cpp
# End Source File
# Begin Source File

SOURCE=.\StageEyeViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageGripperDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageInheritMaterial.cpp
# End Source File
# Begin Source File

SOURCE=.\StageLightDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StageLightDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageLightPartView.cpp
# End Source File
# Begin Source File

SOURCE=.\StageMotionViewHistory.cpp
# End Source File
# Begin Source File

SOURCE=.\StagePartMotion.cpp
# End Source File
# Begin Source File

SOURCE=.\StagePrefsGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\StagePrefsLighting.cpp
# End Source File
# Begin Source File

SOURCE=.\StagePrefsNetwork.cpp
# End Source File
# Begin Source File

SOURCE=.\StagePrefsRender.cpp
# End Source File
# Begin Source File

SOURCE=.\StagePrefsUnits.cpp
# End Source File
# Begin Source File

SOURCE=.\StagePropPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\StageRobot6Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageRobot6SetupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageRotaryTableDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageScaleDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageScriptDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageSizeCustom.cpp
# End Source File
# Begin Source File

SOURCE=.\StageTopDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageTrackDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StageTrainDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\stageView.cpp
# End Source File
# Begin Source File

SOURCE=.\StageViewLightPart.cpp
# End Source File
# Begin Source File

SOURCE=.\StageViewPart.cpp
# End Source File
# Begin Source File

SOURCE=.\StageViewTag.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Dib.h
# End Source File
# Begin Source File

SOURCE=.\GripperDlg.h
# End Source File
# Begin Source File

SOURCE=.\Image.h
# End Source File
# Begin Source File

SOURCE=.\IpFrame.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.h
# End Source File
# Begin Source File

SOURCE=.\stage.h
# End Source File
# Begin Source File

SOURCE=.\StageAnalysisDlg.h
# End Source File
# Begin Source File

SOURCE=.\StageBarCodeReaderDlg.h
# End Source File
# Begin Source File

SOURCE=.\StageBarrettHandDlg.h
# End Source File
# Begin Source File

SOURCE=.\StageCameraDlg.h
# End Source File
# Begin Source File

SOURCE=.\StageChooseDevice.h
# End Source File
# Begin Source File

SOURCE=.\StageChooseName.h
# End Source File
# Begin Source File

SOURCE=.\StageConveyorDlg.h
# End Source File
# Begin Source File

SOURCE=.\StageDeviceTransformation.h
# End Source File
# Begin Source File

SOURCE=.\StageDeviceTree.h
# End Source File
# Begin Source File

SOURCE=.\stageDoc.h
# End Source File
# Begin Source File

SOURCE=.\StageEyeDialog.h
# End Source File
# Begin Source File

SOURCE=.\StageEyeMotion.h
# End Source File
# Begin Source File

SOURCE=.\StageEyeViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\StageGripperDlg.h
# End Source File
# Begin Source File

SOURCE=.\StageInheritMaterial.h
# End Source File
# Begin Source File

SOURCE=.\StageLightDialog.h
# End Source File
# Begin Source File

SOURCE=.\stageLightDlg.h
# End Source File
# Begin Source File

SOURCE=.\StageLightPartView.h
# End Source File
# Begin Source File

SOURCE=.\StageMotionViewHistory.h
# End Source File
# Begin Source File

SOURCE=.\StagePartMotion.h
# End Source File
# Begin Source File

SOURCE=.\StagePrefsGrid.h
# End Source File
# Begin Source File

SOURCE=.\StagePrefsLighting.h
# End Source File
# Begin Source File

SOURCE=.\StagePrefsNetwork.h
# End Source File
# Begin Source File

SOURCE=.\StagePrefsRender.h
# End Source File
# Begin Source File

SOURCE=.\StagePrefsUnits.h
# End Source File
# Begin Source File

SOURCE=.\StagePropPage2.h
# End Source File
# Begin Source File

SOURCE=.\StageRobot6Dlg.h
# End Source File
# Begin Source File

SOURCE=.\StageRobot6SetupDlg.h
# End Source File
# Begin Source File

SOURCE=.\stageRotaryTableDlg.h
# End Source File
# Begin Source File

SOURCE=.\StageScaleDlg.h
# End Source File
# Begin Source File

SOURCE=.\StageScriptDlg.h
# End Source File
# Begin Source File

SOURCE=.\StageSizeCustom.h
# End Source File
# Begin Source File

SOURCE=.\StageTopDlg.h
# End Source File
# Begin Source File

SOURCE=.\StageTrackDlg.h
# End Source File
# Begin Source File

SOURCE=.\StageTrainDlg.h
# End Source File
# Begin Source File

SOURCE=.\stageView.h
# End Source File
# Begin Source File

SOURCE=.\StageViewPart.h
# End Source File
# Begin Source File

SOURCE=.\StageViewTag.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\background256g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_t.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_test.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button256g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_b.bmp
# End Source File
# Begin Source File

SOURCE=.\res\circle_c.bmp
# End Source File
# Begin Source File

SOURCE=.\res\circle_g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\circle_r.bmp
# End Source File
# Begin Source File

SOURCE=.\res\circle_w.bmp
# End Source File
# Begin Source File

SOURCE=.\res\circle_y.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\device_t.bmp
# End Source File
# Begin Source File

SOURCE=.\res\devtrans24g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\eye24g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\eye_back.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idevice_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\ieye.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ipan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ipause.bmp
# End Source File
# Begin Source File

SOURCE=.\res\iplay.bmp
# End Source File
# Begin Source File

SOURCE=.\res\irecord.bmp
# End Source File
# Begin Source File

SOURCE=.\res\irewind.bmp
# End Source File
# Begin Source File

SOURCE=.\res\iscroll.bmp
# End Source File
# Begin Source File

SOURCE=.\res\isocket.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IToolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\link.cur
# End Source File
# Begin Source File

SOURCE=.\res\loop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\loop1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\loop_on1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pan1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pan24g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause24g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause24gHL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play24g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play24gHL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\record24g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rewind.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rewind1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rewind24g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rewind24gHL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\script24g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sim_rec.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sim_rec1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\socket24g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\square_g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\square_p.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stage.ico
# End Source File
# Begin Source File

SOURCE=.\res\stage.rc2
# End Source File
# Begin Source File

SOURCE=.\res\stageDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\unlink.cur
# End Source File
# Begin Source File

SOURCE=.\res\walk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk24g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\walk3.bmp
# End Source File
# End Group
# End Target
# End Project
