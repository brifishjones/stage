// dibpal.h : header file
//

//#include <mmsystem.h>


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
    void Draw(CDC *pDC, CRect *pRect, BOOL bBkgnd = FALSE); 
    void Draw(HDC hDC, RECT* pRect, BOOL bBkgnd = FALSE); 
    int GetNumColors();                 // get the no. of colors in the pal.
    BOOL SetSysPalColors();
    BOOL Load(const char* pszFileName = NULL);
    BOOL Load(CFile* fp);  
    BOOL Load(UINT hFile);
    BOOL Load(HMMIO hmmio);
    BOOL Save(const char* pszFileName = NULL);
    BOOL Save(CFile* fp);  
    BOOL Save(UINT hFile);
    BOOL Save(HMMIO hmmio);
    BOOL CreateWash();
    BOOL CreateSystemColorPalette();
};
