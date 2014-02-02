#include "T3D/gameTSCtrl.h"
#include "console/consoleTypes.h"
#include "T3D/gameBase/gameBase.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/shapeBase.h"
#include "T3D/gameFunctions.h"
#include "console/engineAPI.h"

//---------------------------------------------------------------------------
// Debug stuff:
Point3F lineTestStart = Point3F(0, 0, 0);
Point3F lineTestEnd =   Point3F(0, 1000, 0);
Point3F lineTestIntersect =  Point3F(0, 0, 0);
bool gSnapLine = false;

//----------------------------------------------------------------------------
// Class: GameTSCtrl
//----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(GameTSCtrl);

// See Torque manual (.CHM) for more information
ConsoleDocClass( GameTSCtrl,
        "@brief The main 3D viewport for a Torque 3D game.\n\n"
        "@ingroup Gui3D\n");

GameTSCtrl::GameTSCtrl()
{  
    mCursorObject = NULL;   // Last mouse-down object  
    mTrackObject = NULL;        // The object under cursor  
	dragging = false;
}

//---------------------------------------------------------------------------
bool GameTSCtrl::onAdd()
{
   if ( !Parent::onAdd() )
      return false;

   return true;
}

//---------------------------------------------------------------------------

bool GameTSCtrl::processCameraQuery(CameraQuery *camq)
{
   GameUpdateCameraFov();
   return GameProcessCameraQuery(camq);
}

//---------------------------------------------------------------------------
void GameTSCtrl::renderWorld(const RectI &updateRect)
{
   GameRenderWorld();
}

//---------------------------------------------------------------------------

void GameTSCtrl::onMouseDown(const GuiEvent &evt)
{ 
  lastCursor = evt.mousePoint;

  if (mCursorObject == NULL)
  {   
	static const char *argv[2];  
	argv[0] = "mouse0";  
    argv[1] = "1";
    Con::execute( 2, argv); 
  }

}

void GameTSCtrl::onMouseUp(const GuiEvent &evt)
{  
   if (mCursorObject == NULL)
   {
	 if (mTrackObject != NULL && !dragging)
	 {
 	    mTrackObject->setSelected(false); 
        mTrackObject = NULL;	 
	 }
   
     static const char *argv[2];  
	 argv[0] = "mouse0";  
	 argv[1] = "0";
     Con::execute( 2, argv);     
     dragging = false;
   }
   else
   {
	 if (mCursorObject != mTrackObject && mTrackObject != NULL) 
	    mTrackObject->setSelected(false);
	 mTrackObject = (ShapeBase*)mCursorObject;	  
     mTrackObject->setSelected( mTrackObject ); 
   }
}

//---------------------------------------------------------------------------
/*
IMPLEMENT_CALLBACK( GameTSCtrl, onMouseWheelUp, void, (), (), "");
IMPLEMENT_CALLBACK( GameTSCtrl, onMouseWheelDown, void, (), (), "");

void GameTSCtrl::onMouseWheelUp(const GuiEvent &evt)
{
  onMouseWheelUp_callback();
}

void GameTSCtrl::onMouseWheelDown(const GuiEvent &evt)
{
  onMouseWheelDown_callback();
}
*/
//---------------------------------------------------------------------------

void GameTSCtrl::onRightMouseDown(const GuiEvent &evt)
{
}

void GameTSCtrl::onRightMouseUp(const GuiEvent &evt)
{
}

//---------------------------------------------------------------------------

void GameTSCtrl::onMiddleMouseDown(const GuiEvent &evt)
{
}

void GameTSCtrl::onMiddleMouseUp(const GuiEvent &evt)
{
}

//---------------------------------------------------------------------------

void GameTSCtrl::onMouseDragged( const GuiEvent &evt) 
{  
	if (mCursorObject == NULL) 
	{      
        static const char *argv[2];  
        
		Point2I diff( evt.mousePoint - lastCursor);    
        
		dragging = true;

        if (diff.x) {  
			argv[0] = "yaw";  
            argv[1] = Con::getFloatArg( diff.x);  
            Con::execute( 2, argv);  
        }  
        if (diff.y) {  
			argv[0] = "pitch";  
            argv[1] = Con::getFloatArg( diff.y);  
            Con::execute( 2, argv);  
        }  
              
		// HACK - Have GuiCanvas skip next MouseMoveEvent  
        //Canvas->ignoreNextMove = true;  
        //Canvas->setCursorPos( lastCursor);  
    }  
}  

void GameTSCtrl::onMouseMove(const GuiEvent &evt)
{ 
   if(gSnapLine)
      return;
   
   MatrixF mat;
   Point3F vel;
   if ( GameGetCameraTransform(&mat, &vel) )
   {
      Point3F pos;
      mat.getColumn(3,&pos);
      Point3F screenPoint((F32)evt.mousePoint.x, (F32)evt.mousePoint.y, 1.0f);
      Point3F worldPoint;
      if (unproject(screenPoint, &worldPoint)) 
	  {
         Point3F vec = worldPoint - pos;
         lineTestStart = pos;
         vec.normalizeSafe();
         lineTestEnd = pos + vec * 500;
       
		 static U32 losMask = VehicleObjectType | StaticShapeObjectType;  
		 RayInfo ri;  
         bool hit = gClientContainer.castRay( lineTestStart, lineTestEnd, losMask, &ri);  

		 	 
		 if (!hit)
		 {
		    //Con::printf("no hit!");
			if (mCursorObject != NULL)
			   mCursorObject->setHighlighted(false);
			mCursorObject = NULL;		 
		 }
		 else
		 {	    
			if (ri.object != mCursorObject && mCursorObject != NULL)
			   mCursorObject->setHighlighted(false);
			mCursorObject = (ShapeBase*)ri.object;	
			mCursorObject->setHighlighted(true);
		 }
	  }
   }
}

//---------------------------------------------------------------------------

void GameTSCtrl::onRender(Point2I offset, const RectI &updateRect)
{
   // check if should bother with a render
   GameConnection * con = GameConnection::getConnectionToServer();
   bool skipRender = !con || (con->getWhiteOut() >= 1.f) || (con->getDamageFlash() >= 1.f) || (con->getBlackOut() >= 1.f);

   if(!skipRender || true)
      Parent::onRender(offset, updateRect);
}

//--------------------------------------------------------------------------
