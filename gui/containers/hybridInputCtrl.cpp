

//#include "platform/platform.h"
#include "gui/containers/hybridInputCtrl.h"

#include "gui/core/guiCanvas.h"
#include "console/engineAPI.h"
#include "console/consoleTypes.h"

IMPLEMENT_CONOBJECT( GuiHybridInput );

ConsoleDocClass( GuiHybridInput, "");

//-----------------------------------------------------------------------------

//GuiHybridInput::GuiHybridInput()
//{
//}

//-----------------------------------------------------------------------------

IMPLEMENT_CALLBACK( GuiHybridInput, onMouseM, void, (Point2I mPos), (mPos), "" );

IMPLEMENT_CALLBACK( GuiHybridInput, onEnterFilter, void, (), (), "" );
IMPLEMENT_CALLBACK( GuiHybridInput, onLeaveFilter, void, (), (), "" );

//-----------------------------------------------------------------------------

void GuiHybridInput::onMouseMove(const GuiEvent &event)
{
   mPos = globalToLocalCoord(event.mousePoint);
   //mPos = event.mousePoint;
   

   onMouseM_callback(mPos);
}

//-----------------------------------------------------------------------------

void GuiHybridInput::onMouseLeave(const GuiEvent &event)
{
   //Parent::onMouseLeave();

   GuiCanvas *rootCtrl = getRoot();
   if ( !rootCtrl )
      return;   
   onLeaveFilter_callback();
   rootCtrl->setHybridInput(0);
}

//-----------------------------------------------------------------------------

void GuiHybridInput::onMouseEnter(const GuiEvent &event)
{
   //Parent::onMouseEnter();

   GuiCanvas *rootCtrl = getRoot();
   if ( !rootCtrl )
      return;
   onEnterFilter_callback();
   rootCtrl->setHybridInput(1);
}
