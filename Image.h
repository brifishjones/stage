#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "dib.h"
#include "gl\gl.h"
#include "gl\glu.h"
//#include <gl/gl.h>

//class AFX_EXT_CLASS CGLImage 
class CGLImage 

{
	public:
		CGLImage() ;
		~CGLImage() ;

		enum TRANSLATEMETHOD {TRANS_DIY, TRANS_GDI, TRANS_BOTH} ;

		BOOL Load(LPCTSTR filename) ;
		BOOL Load(WORD wResId) ;

		//void DrawPixels(CGL* pGL) ;
		//void TexImage2D(CGL* pGL) ;

		int GetWidth() {return m_iWidth;}
		int GetHeight() {return m_iHeight;}

  		void* GetBitsPtr() {return m_pBits;}

		void SpecialCreate(int w, int h, void* pBits) ;
		void CreateFromStageFile(FILE *fp);
		void CreateFromStageFile(CArchive &);

		BOOL TexMapScalePow2();

	public:
		int m_iHeight ;
		int m_iWidth ;
		void *m_pBits ;
		GLenum m_PixelFormat ;

		// Translation methods.
		void Translate(CDIB& aDib) ;
		void TranslateByYourself(CDIB& aDib, CDIBPal& aPalSrc) ;
		void TranslateByGDI(CDIB& aDib, CDIBPal& aPalSrc) ;
		void TranslateByBoth(CDIB& aDib, CDIBPal& aPalSrc) ;

		void CleanUp() ;
};

#endif //__IMAGE_H__
