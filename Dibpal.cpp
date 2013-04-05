// dibpal.cpp : implementation file
// @doc

#include "stdafx.h"
#include "dib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIBPal


CDIBPal::CDIBPal()
{
}

CDIBPal::~CDIBPal()
{
}

/*
@mfunc BOOL | CDIBPal | Create | Constructs a CDIBPal object.
@syntax BOOL Create(CDIB* pDIB);
@syntax BOOL Create(BITMAPINFO* pBMI);
@syntax BOOL Create(RGBQUAD* pRGB, int iClrs);
@parm CDIB* | pDIB | A pointer to a CDIB object containing the color table
tto be used to create the palette.
@parm BITMAPINFO* | pBMI | A pointer to a BITMAPINFO structure containing
the color table to create the palette from.
@parm RGBQUAD* | pRGB | A pointer to an array of RGBQUAD structures
describing the colors for the palette.
@parm int | iClrs | The number of entries int he RGBQUAD array.
@rdesc The return value is TRUE if the function succeeds, FALSE if not.
@xref <c CDIBPal>
*/

BOOL CDIBPal::Create(CDIB *pDIB)
{
    int iColors = pDIB->GetNumClrEntries();
    if (! iColors) return FALSE;

    // get a pointer to the RGB quads in the color table
    RGBQUAD* pRGB = pDIB->GetClrTabAddress();

    return Create(pRGB, iColors);
}

BOOL CDIBPal::Create(BITMAPINFO* pBMI)
{
    if (!pBMI) return FALSE;
    int iColors = CDIB::NumDIBColorEntries(pBMI);
    RGBQUAD* pRGB = (LPRGBQUAD)(((BYTE *)(pBMI)) 
                  + sizeof(BITMAPINFOHEADER));
    return Create(pRGB, iColors);
}

BOOL CDIBPal::Create(RGBQUAD* pRGB, int iClrs)
{
    if (iClrs == 0) return FALSE;
    if (!pRGB) return FALSE;

    // allocate a log pal and fill it with the color table info
    LOGPALETTE *pPal = (LOGPALETTE *) malloc(sizeof(LOGPALETTE) 
                     + iClrs * sizeof(PALETTEENTRY));
    if (!pPal) {
        TRACE("Out of memory for logpal");
        return FALSE;
    }
    pPal->palVersion = 0x300; // Windows 3.0
    pPal->palNumEntries = (WORD) iClrs; // table size
    for (int i = 0; i < iClrs; i++) {
        pPal->palPalEntry[i].peRed = pRGB[i].rgbRed;
        pPal->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
        pPal->palPalEntry[i].peBlue = pRGB[i].rgbBlue;
        pPal->palPalEntry[i].peFlags = 0;
    }
    if (m_hObject != NULL) {
        HGDIOBJ hOldPal = Detach();
        ::DeleteObject(hOldPal);
    }    
    BOOL bResult = CreatePalette(pPal);
    free (pPal);
    return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CDIBPal commands

/*
@mfunc int | CDIBPal | GetNumColors | Get the number of colors in
the palette.
@syntax int GetNumColors();
@rdesc The return value is the number of colors in the palette.
@xref <c CDIBPal>
*/

int CDIBPal::GetNumColors()
{
    int iColors = 0;
    if (!GetObject(sizeof(iColors), &iColors)) {
        TRACE("Failed to get num pal colors");
        return 0;
    }
    return iColors;
}


