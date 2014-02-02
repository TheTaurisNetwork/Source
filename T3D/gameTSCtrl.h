#ifndef _GAMETSCTRL_H_
#define _GAMETSCTRL_H_

#ifndef _GAME_H_
#include "app/game.h"
#endif
#ifndef _GUITSCONTROL_H_
#include "gui/3d/guiTSControl.h"
#endif

#ifdef TORQUE_DEMO_WATERMARK
#ifndef _WATERMARK_H_
#include "demo/watermark/watermark.h"
#endif
#endif

class ProjectileData;
class GameBase;
class ShapeBase; 

//----------------------------------------------------------------------------
class GameTSCtrl : public GuiTSCtrl
{
private:
   typedef GuiTSCtrl Parent;

   //void makeScriptCall(const char *func, const GuiEvent &evt) const;
 
   Point2I lastCursor;
   bool dragging;
   ShapeBase* mTrackObject;    // Last mouse-down object  
   ShapeBase* mCursorObject;   // The object under cursor 

//protected:   
   
   //DECLARE_CALLBACK( void, onMouseWheelUp, () );
   //DECLARE_CALLBACK( void, onMouseWheelDown, () );

public:
   GameTSCtrl();

   DECLARE_CONOBJECT(GameTSCtrl);
   DECLARE_DESCRIPTION( "A control that renders a 3D view from the current control object." );

   bool processCameraQuery(CameraQuery *query);
   void renderWorld(const RectI &updateRect);

   // GuiControl
   virtual void onMouseDown(const GuiEvent &evt);
   virtual void onRightMouseDown(const GuiEvent &evt);
   virtual void onMiddleMouseDown(const GuiEvent &evt);

   //virtual void onMouseWheelUp(const GuiEvent &evt);
   //virtual void onMouseWheelDown(const GuiEvent &evt);
   
   virtual void onMouseUp(const GuiEvent &evt);
   virtual void onRightMouseUp(const GuiEvent &evt);
   virtual void onMiddleMouseUp(const GuiEvent &evt);

   void onMouseDragged(const GuiEvent &evt);
   void onMouseMove(const GuiEvent &evt);
   void onRender(Point2I offset, const RectI &updateRect);

   virtual bool onAdd();
};

#endif