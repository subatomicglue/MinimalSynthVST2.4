#ifndef MINI_EDITOR_H
#define MINI_EDITOR_H

// c++
#include <string>
#include <stdio.h>

// vstsdk
#include <vstfxstore.h> // fxp file format
#include <aeffeditor.h> // base class for the GUI editor
#include <plugin-bindings/aeffguieditor.h> // base class for the GUI editor
#include <vstgui.h>

class MinimalEditor : public AEffGUIEditor, public IControlListener
{
public:
    inline MinimalEditor( AudioEffect* effect ) : AEffGUIEditor( effect ), IControlListener() {}
    virtual ~MinimalEditor() {}

public:
    virtual bool open( void* ptr ) {
        AEffGUIEditor::open( ptr );
        printf( "opening editor window\n" );
        CBitmap* bm = new CBitmap( CResourceDescription( 128 ) );
        CRect size = CRect(0, 0, bm->getWidth(), bm->getHeight() );
        rect.left   = 0;
        rect.top    = 0;
        rect.right  = size.getWidth();
        rect.bottom  = size.getHeight();
        frame = new CFrame( size, this );
        frame->open( ptr );
        frame->setBackground( bm );
        return true;
    }
    virtual void close () { printf( "closing editor window\n" ); frame->close(); frame = NULL; AEffGUIEditor::close(); }
    virtual void setParameter (VstInt32 index, float value) {}
    virtual void valueChanged (CControl* control) {}
    inline void setProgram( int which ) {}
    inline void setCurProgramName( const char* name, int curProgram ) {}

    // this exists on AEffEditor
    //virtual bool isOpen ()				{ return systemWindow != 0; }		///< Returns true if editor is currently open

    // this tells us if the frame is created
    virtual bool isOpen() { return AEffGUIEditor::isOpen() && frame != NULL; }

    virtual CMouseEventResult onMouseMoved (CPoint& where, const CButtonState& buttons) {}
};

#endif
