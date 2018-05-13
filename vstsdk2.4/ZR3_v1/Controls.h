#include "Globals.h"
#include <vstgui.h>
#include "aeffguieditor.h"
#if !defined(flp_Controls_h__INCLUDED_)
#define flp_Controls_h__INCLUDED_

class CDisplay : public CControl
{
public:
	CDisplay(CRect &size,CControlListener *listener,int tag,CBitmap *background);
	~CDisplay();
	long	getTag() const;
	float	getValue() const;
	void	setValue(float value);
    void	draw (CDrawContext *pContext);
	void	mouse (CDrawContext *pContext, CPoint& where, long buttons);
	void	setstring(int line, char *string);
	void	setline(float value);
protected:
	float	value,last_value;
	CControlListener *my_listener;
	int		top,left,bottom,right,width,height,my_tag;
	CBitmap	*bg;
	CDrawContext	*my_drawcontext;
	char	line1[256],line2[256],line3[256],line4[256];
	float	linevalue;
};

class CFader : public CControl
{
public:
	CFader(CRect &size,CControlListener *listener,int tag,CBitmap *bitmap,CBitmap *background, int handleheight);
	~CFader();
	long	getTag() const;
	float	getValue() const;
	void	setValue(float value);
    void	draw (CDrawContext *pContext);
	void	mouse (CDrawContext *pContext, CPoint& where, long buttons);
protected:
	float	value,last_value;
	CControlListener *my_listener;
	int		top,left,bottom,right,width,height,my_tag;
	int		my_handleheight;
	CBitmap	*my_bm,*my_bg;
};

class CCircDisplay : public CControl
{
public:
	CCircDisplay(CRect &size,CControlListener *listener,int tag,CBitmap *bitmap, CBitmap *digits, CBitmap *background);
	~CCircDisplay();
	long getTag() const;
	void setValue(float value);
	float getValue() const;
	virtual void setStringConvert (void (*convert) (float value, char *string));
    void draw (CDrawContext *pContext);
	void mouse (CDrawContext *pContext, CPoint& where, long buttons);
protected:
	void (*stringConvert) (float value, char *string);
	float	value,last_value;
	CControlListener *my_listener;
	int		top,left,width,totalheight,numofbm,my_tag,digitwidth,digitheight;
	CBitmap	*my_bm,*my_bg,*my_digits;
};

class CTab : public CControl
{
public:
	CTab(CRect &size,CControlListener *listener,int tag,CBitmap *bm);
	~CTab();
    void draw (CDrawContext *pContext);
	void mouse (CDrawContext *pContext, CPoint& where, long buttons);
};

class CTextSplash : public CSplashScreen
{
public:
	char	text[100][100];
	CTextSplash(CRect &size,
                              CControlListener *listener, 
                              int     tag,
                              CBitmap *background,
                              CRect   &toDisplay,
                              CPoint  &offset);
	void draw (CDrawContext *pContext);
};

#endif flp_Controls_h__INCLUDED_