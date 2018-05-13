/*
	This is my "standard" controls library.

	CDisplay
		The program display (program number and name, boot message)

	CFader
		Drawbars

	CCircDisplay
		The knobs with integrated number display

	CTab
		Tabs to click on...
*/

#include "Controls.h"
#include "resource.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

CDisplay::CDisplay(CRect &size, CControlListener *listener, int tag, CBitmap *background) : CControl(size, listener, tag, background)
{
	my_listener=listener;
	my_tag=tag;
	bg=background;
	top=size.top;
	bottom=size.bottom;
	left=size.left;
	right=size.right;
	line1[0]=0;
	line2[0]=0;
	line3[0]=0;
	line4[0]=0;
	value=0;
	last_value=-2;
	linevalue=-1;
	my_drawcontext=NULL;
}

long CDisplay::getTag() const
{
	return(my_tag);
}

void shiftContext (CDrawContext* context, CView* view, bool back = false)
{
	CRect size;
	view->getViewSize (size);
	if (back)
	{
		size.x *= -1;
		size.y *= -1;
	}
	context->offset.offset (size.left, size.top);
	context->offsetScreen.offset (size.left, size.top);
}

void CDisplay::draw(CDrawContext *pContext)
{
	shiftContext (pContext, this);
	CDrawContext* oc = pContext;
	last_value=value;
	CRect rect(0,0,right-left,bottom-top);
	bg->draw(oc,rect,CPoint(left,top));
	oc->setFont(kNormalFontVerySmall);
	{
		CColor mc={255,236,200,255};
		oc->setFontColor(mc);
		oc->setLineWidth(1);
		oc->setFrameColor(mc);
		mc.red=126;
		mc.green=210;
		mc.blue=204;
		oc->setFillColor(mc);
	}
	oc->drawString(line1,CRect(2,0,right-left,10),false,kLeftText);
	oc->drawString(line2,CRect(2,10,right-left,10+10),false,kLeftText);
	oc->drawString(line3,CRect(2,20,right-left,20+10),false,kLeftText);
	oc->drawString(line4,CRect(2,30,right-left,30+10),false,kLeftText);
	if(linevalue>=0)
	{
		oc->drawRect(CRect(2,42,right-left-2,48));
		oc->fillRect(CRect(3,43,4+(int)((right-left-7)*linevalue),47));
	}
	setDirty (false);
	shiftContext (pContext, this, true);
}

void CDisplay::setline(float value)
{
	if (linevalue != value)
	{
		linevalue=value;
		this->setDirty();
	}
}

void CDisplay::setstring(int line, char *string)
{
	if(line==1)
	{
		if (strcmp (line4, string))
		{
			strncpy(line1,string,sizeof(line1));
			this->setDirty();
		}
	}
	else if(line==2)
	{
		if (strcmp (line4, string))
		{
			strncpy(line2,string,sizeof(line2));
			this->setDirty();
		}
	}
	else if(line==3)
	{
		if (strcmp (line4, string))
		{
			strncpy(line3,string,sizeof(line3));
			this->setDirty();
		}
	}
	else if(line==4)
	{
		if (strcmp (line4, string))
		{
			strncpy(line4,string,sizeof(line4));
			this->setDirty();
		}
	}
}

void CDisplay::setValue(float value)
{
	this->value=value;
}

float CDisplay::getValue() const
{
	return(value);
}

void CDisplay::mouse (CDrawContext *pContext, CPoint& where, long button)
{
	int	x;
	
	x=where.v;
	
	beginEdit();
	do
	{
		button = pContext->getMouseButtons();

		getMouseLocation(pContext,where);
		if(abs(where.v-x)>10)
		{
			if(where.v<x)
			{
				if(value>0)
				{
					setDirty(true);
					value--;
				}
			}
			else
			{
				setDirty(true);
				value++;
			}
			x=where.v;
		}
		if (isDirty ())
			listener->valueChanged(pContext, this);
		doIdleStuff();
	} while(button & kLButton);
	endEdit ();
}

CDisplay::~CDisplay()
{
}

CFader::CFader(CRect &size, CControlListener *listener, int tag, CBitmap *bitmap, CBitmap *background, int handleheight) : CControl (size, listener, tag, background)
{
	my_listener=listener;
	top=size.top;
	left=size.left;
	bottom=size.bottom;
	right=size.right;
	width=bitmap->getWidth();
	height=bitmap->getHeight();
	my_tag=tag;
	my_bm=bitmap;
	my_bg=background;
	my_handleheight=handleheight;
	value=0;
	last_value=-2;
}

long CFader::getTag() const
{
	return(my_tag);
}

void CFader::draw(CDrawContext *pContext)
{
	shiftContext (pContext, this);
	CDrawContext* oc = pContext;
	last_value=value;
	int	pos=int((1-value)*(height-my_handleheight));
	CRect rect(0,0,width,height - pos);
	my_bm->draw(oc,rect,CPoint(0,pos));
	setDirty (false);

	shiftContext (pContext, this, true);
}


void CFader::mouse (CDrawContext *pContext, CPoint& where, long button)
{
	int	x,x_start;
	float	range1=.01f;
	float	range2=.001f;
	float	range;
	float	l_value=value;
	static bool pressed=false;

	x_start=x=where.v;
	beginEdit();
	do
	{
		button = pContext->getMouseButtons();
		if(button&kLButton && !pressed)
		{
			pressed=true;
			((AEffGUIEditor*)getParentView()->getEditor())->setParameter(1000,(float)my_tag);
		}
		else if(!(button&kLButton) && pressed)
		{
			pressed=false;
			((AEffGUIEditor*)getParentView()->getEditor())->setParameter(1000,-1);
		}

		if(button & kShift)
			range=range2;
		else
			range=range1;
		getMouseLocation(pContext, where);
		if(where.v != x)
		{
			x=x_start-where.v;
			value-=range*(float)x;
			if(value<0.01f)
				value=0;
			else if(value>1)
				value=1;
			x=x_start=where.v;
			if(value!=l_value && my_tag<kNumParams)
				my_listener->valueChanged(pContext, (CControl *) this);
			l_value=value;
		}
		if (isDirty ())
			listener->valueChanged (pContext, this);
		doIdleStuff();
	} while(button & kLButton);
	endEdit ();
}

void CFader::setValue(float value)
{
	this->value=value;
}

float CFader::getValue() const
{
	return(value);
}

CFader::~CFader()
{
}

CCircDisplay::CCircDisplay(CRect &size, CControlListener *listener, int tag, CBitmap *bitmap, CBitmap *digits, CBitmap *background) : CControl (size, listener, tag, background)
{
	my_listener=listener;
	stringConvert=NULL;
	top=size.top;
	left=size.left;
	width=bitmap->getWidth();
	totalheight=bitmap->getHeight();
	numofbm=int(totalheight/width);
	my_tag=tag;
	my_bm=bitmap;
	my_digits=digits;
	my_bg=background;
	digitwidth=digits->getWidth();
	digitheight=digits->getHeight()/12;
	value=0;
	last_value=-2;
}

void CCircDisplay::setStringConvert (void (*convert) (float value, char *string))
{
	stringConvert = convert;
}

long CCircDisplay::getTag() const
{
	return(my_tag);
}


void CCircDisplay::setValue(float value)
{
	this->value=value;
}

float CCircDisplay::getValue() const
{
	return(value);
}

CCircDisplay::~CCircDisplay()
{
}

void CCircDisplay::draw(CDrawContext *pContext)
{
	shiftContext (pContext, this);
	CDrawContext* oc = pContext;
	char	t[16];
	unsigned int		x;
	int					y=0,z;
		
	last_value=value;

	if(stringConvert)
		stringConvert(value,t);
	else
		sprintf(t,"%3d%",int(100*value+.001f));

	CRect rect(0,0,width,width);
	my_bg->draw(oc,rect,CPoint(left,top));
	my_bm->drawTransparent(oc,rect,CPoint(0,int(value*(numofbm-1))*width));

	for(x=0;x<strlen(t);x++)
	{
		if(t[x]=='.')
		{
			int a;
			if(y>=digitwidth)
				a=y-digitwidth;
			rect(12+a,19,12+a+digitwidth,19+digitheight);
			my_digits->drawTransparent(oc,rect,CPoint(0,10*digitheight));
			continue;
		}
		else if(t[x]==' ')
		{
			y+=digitwidth;
			continue;
		}
		else if(t[x]=='%')
			z=11*digitheight;
		else if(!isdigit(t[x]))
			continue;
		else
			z=digitheight*(t[x]-'0');

		rect(12+y,18,12+y+digitwidth,18+digitheight);
		my_digits->drawTransparent(oc,rect,CPoint(0,z));
		y+=digitwidth;
	}
	setDirty (false);
	shiftContext (pContext, this, true);
}

void CCircDisplay::mouse (CDrawContext *pContext, CPoint& where, long button)
{
	int	x,x_start;
	float	range1=.01f;
	float	range2=.001f;
	float	range;
	float	l_value=value;
	static bool	pressed=false;

	x_start=x=where.v;
	beginEdit();
	do
	{
		button = pContext->getMouseButtons();
		if((button&kLButton) && !pressed)
		{
			pressed=true;
			((AEffGUIEditor*)getParentView()->getEditor())->setParameter(1000,(float)my_tag);
		}
		else if(!(button&kLButton) && pressed)
		{
			pressed=false;
			((AEffGUIEditor*)getParentView()->getEditor())->setParameter(1000,-1);
		}

		if(button & kShift)
			range=range2;
		else
			range=range1;
		getMouseLocation(pContext, where);
		if(where.v != x)
		{
			x=x_start-where.v;
			value+=range*(float)x;
			if(value<0.01f)
				value=0;
			else if(value>1)
				value=1;
			x=x_start=where.v;
//			if(value!=l_value && my_tag<kNumParams && isDirty())
			if(value!=l_value && my_tag<kNumParams)
			{
				setDirty(true);
				my_listener->valueChanged(pContext, (CControl *) this);
			}
			l_value=value;
		}
		if (isDirty ())
			listener->valueChanged (pContext, this);
		getMouseLocation (pContext, where);
		doIdleStuff();
	} while(button & kLButton);
	endEdit ();
}

CTextSplash::CTextSplash(CRect &size,CControlListener *listener, int tag, CBitmap *background, CRect   &toDisplay, CPoint  &offset) : CSplashScreen(size,listener,tag,background,toDisplay,offset)
{
}

void CTextSplash::draw(CDrawContext *pContext)
{
	if (value && pBackground)
	{
		pBackground->draw (pContext, toDisplay, offset);
		pContext->setFont(kNormalFontSmaller);
		{
			int	x;
			CColor mc={0,0,0,255};
			pContext->setFontColor(mc);

			for(x=0;x<100;x++)
			{
				pContext->drawString(text[x],CRect(158,x*10,250,10+x*10),false,kLeftText);
			}
		}
	}
	setDirty (false);
}

CTab::CTab(CRect &size,CControlListener *listener,int tag,CBitmap *bm) : CControl(size, listener, tag, bm)
{
}

CTab::~CTab()
{
}

void CTab::draw(CDrawContext *pContext)
{
	setDirty (false);
}

void CTab::mouse(CDrawContext *pContext, CPoint& where, long button)
{
//	long	button = pContext->getMouseButtons();
	if(button)
		((AEffGUIEditor*)getParentView()->getEditor())->setParameter(tag,1);
}
