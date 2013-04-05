// dib.h : header file
//
// @doc
// All classes for animation
//

#include <mmsystem.h>

/////////////////////////////////////////////////////////////////////////////
// @class CDIB | This class encapsulates a Windows DIB.
// @base public | CObject
// @member GetBitmapInfoAddress | Get a pointer to the BITMAPINFO.
// @member GetBitsAddress | Get a pointer to the bitmap bits.
// @member GetClrTabAddress | Get a pointer to the color table.
// @member GetNumClrEntries | Get the number of entries in the color table.
// @member Create | Create a new CDIB object.
// @member GetPixelAddress | Get the address of a given pixel.
// @member Load | Load the DIB from a file or resource.
// @member Save | Save the DIB to a file.
// @member Draw | Draw the DIB to a CDC object.
// @member GetWidth | Get the width of the image.
// @member GetStorageWidth | Get the memory width of the image (DWORD aligned).
// @member GetHeight | Get the height of the image.
// @member MapColorsToPalette | Map the DIB colors to a given palette.
// @member GetRect | Get the bounding rectangle.
// @member CopyBits | Copy a rectangle to another DIB.
// @member StretchBits | Stretch a rectangle to another DIB.
// @member GetBitsPerPixel | Get the number of bits per pixel.
// @member SetColorTable | Set the color table entries.
/*
@mfunc BITMAPINFO* | CDIB | GetBitmapInfoAddress | Get a pointer to the BITMAPINFO.
@syntax BITMAPINFO* GetBitmapInfoAddress(); 
@rdesc The return value is a pointer to the DIB's BITMAPINFO structure.
@xref <c CDIB>

@mfunc void* | CDIB | GetBitsAddress | Get a pointer to the DIB bits.
@syntax void* GetBitsAddress(); 
@rdesc The return value is a pointer to the DIB's bits.
@xref <c CDIB>

@mfunc RGBQUAD* | CDIB | GetClrTabAddress | Get a pointer to the DIB's
color table.
@syntax RGBQUAD* GetClrTabAddress(); 
@rdesc The return value is a pointer to the DIB's color table.
@xref <c CDIB>

@mfunc int | CDIB | GetWidth | Get the width of the image.
@syntax int GetWidth(); 
@rdesc The return value is width of the DIB in pixels.
@xref <c CDIB>

@mfunc int | CDIB | GetStorageWidth | Get the width of the image in memory.
@syntax int GetStorageWidth(); 
@rdesc The return value is width of a sigle scanline of the DIB in pixels.
@comm DIB scanlines are DWORD aligned so the width in memory is >= the image width. 
@xref <c CDIB>

@mfunc int | CDIB | GetHeight | Get the height of the image.
@syntax int GetHeight(); 
@rdesc The return value is height of the DIB in pixels.
@xref <c CDIB>

@mfunc int | CDIB | GetBitsPerPixel | Get the number of bits used to store
each pixel of the image.
@syntax int GetBitsPerPixel(); 
@rdesc The return value is the number of bits used per pixel.
@xref <c CDIB>

*/

class CDIB : public CObject
{
    DECLARE_SERIAL(CDIB)
public:
    CDIB();
    ~CDIB();

    BITMAPINFO *GetBitmapInfoAddress()
        {return m_pBMI;}                        // ptr to bitmap info
    void *GetBitsAddress()
        {return m_pBits;}                       // ptr to the bits
    RGBQUAD *GetClrTabAddress()
        {return (LPRGBQUAD)(((BYTE *)(m_pBMI)) 
            + sizeof(BITMAPINFOHEADER));}       // ptr to color table
    int GetNumClrEntries();                     // number of color table entries
    BOOL Create(int width, int height, CPalette* pPal = NULL);         // create a new DIB
    BOOL Create(int width, int height, HPALETTE hPal);         // create a new DIB
    BOOL Create(BITMAPINFO* pBMI, BYTE* pBits, BOOL bOwnBits = FALSE); // create from existing mem,
    BOOL Create(BITMAPINFO* pPackedDIB); // create from packed DIB
    void *GetPixelAddress(int x, int y);
    int GetBitsPerPixel()
        {return m_pBMI->bmiHeader.biBitCount;}
    virtual BOOL Load(const char* pszFileName = NULL);// load DIB from disk file
    virtual BOOL Load(CFile* fp);               // load from file
    virtual BOOL Load(WORD wResid);             // load DIB from resource
    virtual BOOL Save(const char* pszFileName = NULL);// save DIB to disk file
    virtual BOOL Save(CFile *fp);               // save to file
    virtual void Serialize(CArchive& ar);
    virtual void Draw(CDC *pDC, int x, int y);
    virtual void Draw(HDC hDC, int x, int y);
    virtual int GetWidth() {return DibWidth();}   // image width
    virtual int GetStorageWidth() {return StorageWidth();}   // memory width
    virtual int GetHeight() {return DibHeight();} // image height
    virtual BOOL MapColorsToPalette(CPalette *pPal);
    virtual BOOL MapColorsToPalette(HPALETTE hPal);
    virtual void GetRect(RECT* pRect);
    virtual void CopyBits(CDIB* pDIB, 
                          int xd, int yd,
                          int w, int h,
                          int xs, int ys,
                          COLORREF clrTrans = 0xFFFFFFFF);
    virtual void StretchBits(CDIB* pDIB, 
                             int xd, int yd,
                             int wd, int hd,
                             int xs, int ys,
                             int ws, int hs,
                             COLORREF clrTrans = 0xFFFFFFFF);
    virtual void DoubleBits(CDIB* pDIB, 
                            int xd, int yd,
                            int xs, int ys,
                            int ws, int hs,
                            COLORREF clrTrans = 0xFFFFFFFF);
    BOOL SetColorTable(CPalette* pPal);

    static BOOL IsWinDIB(BITMAPINFOHEADER* pBIH);
    static int NumDIBColorEntries(BITMAPINFO* pBmpInfo);

protected:
    BITMAPINFO *m_pBMI;         // pointer to BITMAPINFO struct
    BYTE *m_pBits;              // pointer to the bits
    BOOL m_bMyBits;             // TRUE if DIB owns Bits memory

private:
    int DibHeight() 
        {return m_pBMI->bmiHeader.biHeight;}
    int DibWidth()
        {return m_pBMI->bmiHeader.biWidth;}
    int StorageWidth()
        {return (((m_pBMI->bmiHeader.biWidth * m_pBMI->bmiHeader.biBitCount)
                     + 31) & ~31) >> 3;}
};

/////////////////////////////////////////////////////////////////////////////
// @class CDIBPal | This class enhances the CPalette class.
// @base public | CPalette
// @member Create | Create a new palette;
// @member Draw | Draw the palette to a CDC object.
// @member GetNumColors | Get the number of colors in the palette.
// @member SetSysPalColors | Create an identity palette.
// @member Load | Load a palette from a file.
// @member Save | Save the palette to a file.
// @member CreateWash | Create a color cube wash palette.
// @member CreateSystemColorPalette | Create a palette from
//         the 20 system reserved colors.

class CDIBPal : public CPalette
{
public:
    CDIBPal();
    ~CDIBPal();
    BOOL Create(CDIB *pDIB);            // create from a DIB
    BOOL Create(BITMAPINFO* pBMI);      // create from color table
    BOOL Create(RGBQUAD* pRGB, int iClrs); // create from clr table
    //void Draw(CDC *pDC, CRect *pRect, BOOL bBkgnd = FALSE); 
    //void Draw(HDC hDC, RECT* pRect, BOOL bBkgnd = FALSE); 
    int GetNumColors();                 // get the no. of colors in the pal.
    //BOOL SetSysPalColors();
    //BOOL Load(const char* pszFileName = NULL);
    //BOOL Load(CFile* fp);  
    //BOOL Load(UINT hFile);
    //BOOL Load(HMMIO hmmio);
    //BOOL Save(const char* pszFileName = NULL);
    //BOOL Save(CFile* fp);  
    //BOOL Save(UINT hFile);
    //BOOL Save(HMMIO hmmio);
    //BOOL CreateWash();
    //BOOL CreateSystemColorPalette();
};
