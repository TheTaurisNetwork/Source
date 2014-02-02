#ifndef _GUI_HYBRIDINPUT_H_
#define _GUI_HYBRIDINPUT_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif
#ifndef _GUICONTAINER_H_
#include "gui/containers/guiContainer.h"
#endif
//#ifndef _PLATFORMINPUT_H_
//#include "platform/platformInput.h"
//#endif


class  GuiHybridInput : public GuiContainer
{
   typedef GuiContainer Parent;
public:

//GuiHybridInput();

   DECLARE_CONOBJECT( GuiHybridInput );
   DECLARE_DESCRIPTION( "Filters input from mouse to control objects and still use gui elements" );

   // GuiControl   
   virtual void onMouseMove(const GuiEvent &event);
      virtual void onMouseEnter(const GuiEvent &event);
      virtual void onMouseLeave(const GuiEvent &event);
    
protected:
   
   DECLARE_CALLBACK( void, onMouseM, ( Point2I mPos ) );
   DECLARE_CALLBACK( void, onEnterFilter, () );
   DECLARE_CALLBACK( void, onLeaveFilter, () );
 
   Point2I mPos;
};

#endif 