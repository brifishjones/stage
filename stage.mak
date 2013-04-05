# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=stage - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to stage - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "stage - Win32 Release" && "$(CFG)" != "stage - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "stage.mak" CFG="stage - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "stage - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "stage - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "stage - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "stage - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\stage.exe"

CLEAN : 
	-@erase ".\Release\stage.exe"
	-@erase ".\Release\Dibpal.obj"
	-@erase ".\Release\stage.pch"
	-@erase ".\Release\StageViewTag.obj"
	-@erase ".\Release\stageDoc.obj"
	-@erase ".\Release\Image.obj"
	-@erase ".\Release\stage.obj"
	-@erase ".\Release\StagePrefsLighting.obj"
	-@erase ".\Release\StagePrefsRender.obj"
	-@erase ".\Release\StageMotionViewHistory.obj"
	-@erase ".\Release\stageView.obj"
	-@erase ".\Release\StageEyeViewDlg.obj"
	-@erase ".\Release\StageLightPartView.obj"
	-@erase ".\Release\StageRotaryTableDlg.obj"
	-@erase ".\Release\GripperDlg.obj"
	-@erase ".\Release\StageViewLightPart.obj"
	-@erase ".\Release\StageAnalysisDlg.obj"
	-@erase ".\Release\StagePartMotion.obj"
	-@erase ".\Release\StageViewPart.obj"
	-@erase ".\Release\StagePropPage2.obj"
	-@erase ".\Release\SrvrItem.obj"
	-@erase ".\Release\IpFrame.obj"
	-@erase ".\Release\StageEyeDialog.obj"
	-@erase ".\Release\StageEyeMotion.obj"
	-@erase ".\Release\StageLightDlg.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\StageLightDialog.obj"
	-@erase ".\Release\StageDeviceTransformation.obj"
	-@erase ".\Release\StageRobot6Dlg.obj"
	-@erase ".\Release\Dib.obj"
	-@erase ".\Release\StageInheritMaterial.obj"
	-@erase ".\Release\StageChooseName.obj"
	-@erase ".\Release\StageGripperDlg.obj"
	-@erase ".\Release\StageRobot6SetupDlg.obj"
	-@erase ".\Release\StagePrefsGrid.obj"
	-@erase ".\Release\StageDeviceTree.obj"
	-@erase ".\Release\StageChooseDevice.obj"
	-@erase ".\Release\stage.res"
	-@erase ".\Release\StageTrackDlg.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/stage.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/stage.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/stage.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/stage.pdb" /machine:I386\
 /out:"$(OUTDIR)/stage.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Dibpal.obj" \
	"$(INTDIR)/StageViewTag.obj" \
	"$(INTDIR)/stageDoc.obj" \
	"$(INTDIR)/Image.obj" \
	"$(INTDIR)/stage.obj" \
	"$(INTDIR)/StagePrefsLighting.obj" \
	"$(INTDIR)/StagePrefsRender.obj" \
	"$(INTDIR)/StageMotionViewHistory.obj" \
	"$(INTDIR)/stageView.obj" \
	"$(INTDIR)/StageEyeViewDlg.obj" \
	"$(INTDIR)/StageLightPartView.obj" \
	"$(INTDIR)/StageRotaryTableDlg.obj" \
	"$(INTDIR)/GripperDlg.obj" \
	"$(INTDIR)/StageViewLightPart.obj" \
	"$(INTDIR)/StageAnalysisDlg.obj" \
	"$(INTDIR)/StagePartMotion.obj" \
	"$(INTDIR)/StageViewPart.obj" \
	"$(INTDIR)/StagePropPage2.obj" \
	"$(INTDIR)/SrvrItem.obj" \
	"$(INTDIR)/IpFrame.obj" \
	"$(INTDIR)/StageEyeDialog.obj" \
	"$(INTDIR)/StageEyeMotion.obj" \
	"$(INTDIR)/StageLightDlg.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/StageLightDialog.obj" \
	"$(INTDIR)/StageDeviceTransformation.obj" \
	"$(INTDIR)/StageRobot6Dlg.obj" \
	"$(INTDIR)/Dib.obj" \
	"$(INTDIR)/StageInheritMaterial.obj" \
	"$(INTDIR)/StageChooseName.obj" \
	"$(INTDIR)/StageGripperDlg.obj" \
	"$(INTDIR)/StageRobot6SetupDlg.obj" \
	"$(INTDIR)/StagePrefsGrid.obj" \
	"$(INTDIR)/StageDeviceTree.obj" \
	"$(INTDIR)/StageChooseDevice.obj" \
	"$(INTDIR)/StageTrackDlg.obj" \
	"$(INTDIR)/stage.res"

"$(OUTDIR)\stage.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "stage - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\stage.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\stage.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\stage.exe"
	-@erase ".\Debug\StageRobot6Dlg.obj"
	-@erase ".\Debug\StageEyeViewDlg.obj"
	-@erase ".\Debug\SrvrItem.obj"
	-@erase ".\Debug\StageAnalysisDlg.obj"
	-@erase ".\Debug\StageMotionViewHistory.obj"
	-@erase ".\Debug\StagePrefsGrid.obj"
	-@erase ".\Debug\GripperDlg.obj"
	-@erase ".\Debug\StageLightPartView.obj"
	-@erase ".\Debug\StageRobot6SetupDlg.obj"
	-@erase ".\Debug\StageViewLightPart.obj"
	-@erase ".\Debug\StageLightDialog.obj"
	-@erase ".\Debug\Image.obj"
	-@erase ".\Debug\StagePrefsLighting.obj"
	-@erase ".\Debug\StageChooseDevice.obj"
	-@erase ".\Debug\stageView.obj"
	-@erase ".\Debug\StageViewPart.obj"
	-@erase ".\Debug\StageViewTag.obj"
	-@erase ".\Debug\stage.obj"
	-@erase ".\Debug\StageLightDlg.obj"
	-@erase ".\Debug\StageChooseName.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\stageDoc.obj"
	-@erase ".\Debug\StageGripperDlg.obj"
	-@erase ".\Debug\StageDeviceTree.obj"
	-@erase ".\Debug\StageInheritMaterial.obj"
	-@erase ".\Debug\StagePartMotion.obj"
	-@erase ".\Debug\StageDeviceTransformation.obj"
	-@erase ".\Debug\Dib.obj"
	-@erase ".\Debug\StagePrefsRender.obj"
	-@erase ".\Debug\StageRotaryTableDlg.obj"
	-@erase ".\Debug\Dibpal.obj"
	-@erase ".\Debug\StagePropPage2.obj"
	-@erase ".\Debug\StageEyeDialog.obj"
	-@erase ".\Debug\StageEyeMotion.obj"
	-@erase ".\Debug\IpFrame.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\stage.res"
	-@erase ".\Debug\StageTrackDlg.obj"
	-@erase ".\Debug\stage.ilk"
	-@erase ".\Debug\stage.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/stage.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/stage.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/stage.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/stage.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/stage.exe" 
LINK32_OBJS= \
	"$(INTDIR)/StageRobot6Dlg.obj" \
	"$(INTDIR)/StageEyeViewDlg.obj" \
	"$(INTDIR)/SrvrItem.obj" \
	"$(INTDIR)/StageAnalysisDlg.obj" \
	"$(INTDIR)/StageMotionViewHistory.obj" \
	"$(INTDIR)/StagePrefsGrid.obj" \
	"$(INTDIR)/GripperDlg.obj" \
	"$(INTDIR)/StageLightPartView.obj" \
	"$(INTDIR)/StageRobot6SetupDlg.obj" \
	"$(INTDIR)/StageViewLightPart.obj" \
	"$(INTDIR)/StageLightDialog.obj" \
	"$(INTDIR)/Image.obj" \
	"$(INTDIR)/StagePrefsLighting.obj" \
	"$(INTDIR)/StageChooseDevice.obj" \
	"$(INTDIR)/stageView.obj" \
	"$(INTDIR)/StageViewPart.obj" \
	"$(INTDIR)/StageViewTag.obj" \
	"$(INTDIR)/stage.obj" \
	"$(INTDIR)/StageLightDlg.obj" \
	"$(INTDIR)/StageChooseName.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/stageDoc.obj" \
	"$(INTDIR)/StageGripperDlg.obj" \
	"$(INTDIR)/StageDeviceTree.obj" \
	"$(INTDIR)/StageInheritMaterial.obj" \
	"$(INTDIR)/StagePartMotion.obj" \
	"$(INTDIR)/StageDeviceTransformation.obj" \
	"$(INTDIR)/Dib.obj" \
	"$(INTDIR)/StagePrefsRender.obj" \
	"$(INTDIR)/StageRotaryTableDlg.obj" \
	"$(INTDIR)/Dibpal.obj" \
	"$(INTDIR)/StagePropPage2.obj" \
	"$(INTDIR)/StageEyeDialog.obj" \
	"$(INTDIR)/StageEyeMotion.obj" \
	"$(INTDIR)/IpFrame.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/StageTrackDlg.obj" \
	"$(INTDIR)/stage.res"

"$(OUTDIR)\stage.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "stage - Win32 Release"
# Name "stage - Win32 Debug"

!IF  "$(CFG)" == "stage - Win32 Release"

!ELSEIF  "$(CFG)" == "stage - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "stage - Win32 Release"

!ELSEIF  "$(CFG)" == "stage - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\stage.cpp
DEP_CPP_STAGE=\
	".\StdAfx.h"\
	".\stage.h"\
	".\MainFrm.h"\
	".\IpFrame.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	

"$(INTDIR)\stage.obj" : $(SOURCE) $(DEP_CPP_STAGE) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "stage - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/stage.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\stage.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "stage - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/stage.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\stage.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\stage.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\StagePrefsRender.h"\
	".\StagePrefsGrid.h"\
	".\StagePrefsLighting.h"\
	".\StageDeviceTree.h"\
	".\StageMotionViewHistory.h"\
	".\StagePartMotion.h"\
	".\StageChooseName.h"\
	".\StageChooseDevice.h"\
	".\StageLightDialog.h"\
	".\StageRobot6Dlg.h"\
	".\stageRotaryTableDlg.h"\
	".\StageGripperDlg.h"\
	".\StageViewPart.h"\
	".\StageViewTag.h"\
	".\StageDeviceTransformation.h"\
	".\StageEyeDialog.h"\
	".\StageAnalysisDlg.h"\
	".\StageEyeViewDlg.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\stageDoc.cpp
DEP_CPP_STAGED=\
	".\StdAfx.h"\
	".\stage.h"\
	".\stageDoc.h"\
	".\SrvrItem.h"\
	".\stageView.h"\
	".\StageDeviceTransformation.h"\
	".\StageAnalysisDlg.h"\
	".\StageViewPart.h"\
	".\StageViewTag.h"\
	".\StageRobot6Dlg.h"\
	".\stageRotaryTableDlg.h"\
	".\StageGripperDlg.h"\
	".\MainFrm.h"\
	".\Image.h"\
	".\Dib.h"\
	

"$(INTDIR)\stageDoc.obj" : $(SOURCE) $(DEP_CPP_STAGED) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\stageView.cpp
DEP_CPP_STAGEV=\
	".\StdAfx.h"\
	".\stage.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\StageEyeDialog.h"\
	".\StageDeviceTransformation.h"\
	".\StageViewPart.h"\
	".\StageAnalysisDlg.h"\
	".\StageViewTag.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\stageView.obj" : $(SOURCE) $(DEP_CPP_STAGEV) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SrvrItem.cpp
DEP_CPP_SRVRI=\
	".\StdAfx.h"\
	".\stage.h"\
	".\stageDoc.h"\
	".\SrvrItem.h"\
	

"$(INTDIR)\SrvrItem.obj" : $(SOURCE) $(DEP_CPP_SRVRI) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IpFrame.cpp
DEP_CPP_IPFRA=\
	".\StdAfx.h"\
	".\stage.h"\
	".\IpFrame.h"\
	

"$(INTDIR)\IpFrame.obj" : $(SOURCE) $(DEP_CPP_IPFRA) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\stage.rc
DEP_RSC_STAGE_=\
	".\res\stage.ico"\
	".\res\stageDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\IToolbar.bmp"\
	".\res\bitmap_test.bmp"\
	".\res\rewind.bmp"\
	".\res\play.bmp"\
	".\res\pause.bmp"\
	".\res\walk.bmp"\
	".\res\pan.bmp"\
	".\res\play1.bmp"\
	".\res\circle_g.bmp"\
	".\res\bmp00001.bmp"\
	".\res\pan1.bmp"\
	".\res\square_g.bmp"\
	".\res\square_p.bmp"\
	".\res\cursor1.cur"\
	".\link.cur"\
	".\res\unlink.cur"\
	".\res\stage.rc2"\
	

"$(INTDIR)\stage.res" : $(SOURCE) $(DEP_RSC_STAGE_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StagePrefsRender.cpp
DEP_CPP_STAGEP=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StagePrefsRender.h"\
	".\stageDoc.h"\
	

"$(INTDIR)\StagePrefsRender.obj" : $(SOURCE) $(DEP_CPP_STAGEP) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StagePrefsGrid.cpp
DEP_CPP_STAGEPR=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StagePrefsGrid.h"\
	".\stageDoc.h"\
	

"$(INTDIR)\StagePrefsGrid.obj" : $(SOURCE) $(DEP_CPP_STAGEPR) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StagePrefsLighting.cpp
DEP_CPP_STAGEPRE=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StagePrefsLighting.h"\
	

"$(INTDIR)\StagePrefsLighting.obj" : $(SOURCE) $(DEP_CPP_STAGEPRE) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageDeviceTree.cpp
DEP_CPP_STAGEDE=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageDeviceTree.h"\
	

"$(INTDIR)\StageDeviceTree.obj" : $(SOURCE) $(DEP_CPP_STAGEDE) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageMotionViewHistory.cpp
DEP_CPP_STAGEM=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageMotionViewHistory.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	

"$(INTDIR)\StageMotionViewHistory.obj" : $(SOURCE) $(DEP_CPP_STAGEM)\
 "$(INTDIR)" "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageViewPart.cpp
DEP_CPP_STAGEVI=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageInheritMaterial.h"\
	".\StageViewPart.h"\
	".\StageLightDialog.h"\
	".\StageRobot6Dlg.h"\
	".\stageRotaryTableDlg.h"\
	".\StageGripperDlg.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageViewPart.obj" : $(SOURCE) $(DEP_CPP_STAGEVI) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageChooseName.cpp
DEP_CPP_STAGEC=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageChooseName.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageChooseName.obj" : $(SOURCE) $(DEP_CPP_STAGEC) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageChooseDevice.cpp
DEP_CPP_STAGECH=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageChooseDevice.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageChooseDevice.obj" : $(SOURCE) $(DEP_CPP_STAGECH) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageDeviceTransformation.cpp
DEP_CPP_STAGEDEV=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageDeviceTransformation.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageDeviceTransformation.obj" : $(SOURCE) $(DEP_CPP_STAGEDEV)\
 "$(INTDIR)" "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StagePropPage2.cpp
DEP_CPP_STAGEPRO=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StagePropPage2.h"\
	

"$(INTDIR)\StagePropPage2.obj" : $(SOURCE) $(DEP_CPP_STAGEPRO) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageEyeMotion.cpp
DEP_CPP_STAGEE=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageEyeMotion.h"\
	

"$(INTDIR)\StageEyeMotion.obj" : $(SOURCE) $(DEP_CPP_STAGEE) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageEyeDialog.cpp
DEP_CPP_STAGEEY=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageEyeDialog.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageEyeDialog.obj" : $(SOURCE) $(DEP_CPP_STAGEEY) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dib.cpp
DEP_CPP_DIB_C=\
	".\StdAfx.h"\
	".\Dib.h"\
	

"$(INTDIR)\Dib.obj" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dibpal.cpp
DEP_CPP_DIBPA=\
	".\StdAfx.h"\
	".\Dib.h"\
	

"$(INTDIR)\Dibpal.obj" : $(SOURCE) $(DEP_CPP_DIBPA) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Image.cpp
DEP_CPP_IMAGE=\
	".\StdAfx.h"\
	".\Image.h"\
	".\Dib.h"\
	

"$(INTDIR)\Image.obj" : $(SOURCE) $(DEP_CPP_IMAGE) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StagePartMotion.cpp
DEP_CPP_STAGEPA=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StagePartMotion.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	

"$(INTDIR)\StagePartMotion.obj" : $(SOURCE) $(DEP_CPP_STAGEPA) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageLightPartView.cpp
DEP_CPP_STAGEL=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageLightPartView.h"\
	

"$(INTDIR)\StageLightPartView.obj" : $(SOURCE) $(DEP_CPP_STAGEL) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageViewLightPart.cpp
DEP_CPP_STAGEVIE=\
	".\StdAfx.h"\
	".\stage.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageViewLightPart.obj" : $(SOURCE) $(DEP_CPP_STAGEVIE) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageLightDlg.cpp
DEP_CPP_STAGELI=\
	".\StdAfx.h"\
	".\stage.h"\
	".\stageLightDlg.h"\
	

"$(INTDIR)\StageLightDlg.obj" : $(SOURCE) $(DEP_CPP_STAGELI) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageLightDialog.cpp
DEP_CPP_STAGELIG=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageViewPart.h"\
	".\StageLightDialog.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageLightDialog.obj" : $(SOURCE) $(DEP_CPP_STAGELIG) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageInheritMaterial.cpp
DEP_CPP_STAGEI=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageInheritMaterial.h"\
	".\StageViewPart.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageInheritMaterial.obj" : $(SOURCE) $(DEP_CPP_STAGEI) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageAnalysisDlg.cpp

!IF  "$(CFG)" == "stage - Win32 Release"

DEP_CPP_STAGEA=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageAnalysisDlg.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageAnalysisDlg.obj" : $(SOURCE) $(DEP_CPP_STAGEA) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


!ELSEIF  "$(CFG)" == "stage - Win32 Debug"

DEP_CPP_STAGEA=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageAnalysisDlg.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	
NODEP_CPP_STAGEA=\
	".\;"\
	

"$(INTDIR)\StageAnalysisDlg.obj" : $(SOURCE) $(DEP_CPP_STAGEA) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageViewTag.cpp
DEP_CPP_STAGEVIEW=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageViewTag.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageViewTag.obj" : $(SOURCE) $(DEP_CPP_STAGEVIEW) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageRobot6Dlg.cpp
DEP_CPP_STAGER=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageViewPart.h"\
	".\StageRobot6Dlg.h"\
	".\StageRobot6SetupDlg.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageRobot6Dlg.obj" : $(SOURCE) $(DEP_CPP_STAGER) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageRobot6SetupDlg.cpp
DEP_CPP_STAGERO=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageRobot6SetupDlg.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageRobot6SetupDlg.obj" : $(SOURCE) $(DEP_CPP_STAGERO) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageRotaryTableDlg.cpp
DEP_CPP_STAGEROT=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageViewPart.h"\
	".\stageRotaryTableDlg.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageRotaryTableDlg.obj" : $(SOURCE) $(DEP_CPP_STAGEROT) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GripperDlg.cpp
DEP_CPP_GRIPP=\
	".\StdAfx.h"\
	".\stage.h"\
	".\GripperDlg.h"\
	

"$(INTDIR)\GripperDlg.obj" : $(SOURCE) $(DEP_CPP_GRIPP) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageGripperDlg.cpp
DEP_CPP_STAGEG=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageViewPart.h"\
	".\StageGripperDlg.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageGripperDlg.obj" : $(SOURCE) $(DEP_CPP_STAGEG) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageEyeViewDlg.cpp
DEP_CPP_STAGEEYE=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageEyeViewDlg.h"\
	".\stageDoc.h"\
	".\stageView.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\StageEyeViewDlg.obj" : $(SOURCE) $(DEP_CPP_STAGEEYE) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StageTrackDlg.cpp
DEP_CPP_STAGET=\
	".\StdAfx.h"\
	".\stage.h"\
	".\StageTrackDlg.h"\
	

"$(INTDIR)\StageTrackDlg.obj" : $(SOURCE) $(DEP_CPP_STAGET) "$(INTDIR)"\
 "$(INTDIR)\stage.pch"


# End Source File
# End Target
# End Project
################################################################################
