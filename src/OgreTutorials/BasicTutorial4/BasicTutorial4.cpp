
#include "BasicTutorial4.h"

//-----------------------------------------------------------------------------
BasicTutorial4::BasicTutorial4(void)
{

}
//-----------------------------------------------------------------------------
BasicTutorial4::~BasicTutorial4(void)
{

}
//-----------------------------------------------------------------------------
void BasicTutorial4::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));

	Ogre::Entity *ninjaEntity = mSceneMgr->createEntity("Ninja", "ninja.mesh");
	Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("NinjaNode");
	node->attachObject(ninjaEntity);

	Ogre::Light *pointLight = mSceneMgr->createLight("pointLight");
	pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setPosition(Ogre::Vector3(250, 150, 250));
	pointLight->setDiffuseColour(Ogre::ColourValue::White);
	pointLight->setSpecularColour(Ogre::ColourValue::White);
}
//-----------------------------------------------------------------------------
bool BasicTutorial4::processUnbufferedInput(const Ogre::FrameEvent &evt)
{
	static bool mouseDown = false;
	static Ogre::Real toggle = 0.0;
	static Ogre::Real rotate = 0.13;
	static Ogre::Real move = 250;
	
	bool currMouse = mMouse->getMouseState().buttonDown(OIS::MB_Left);
	if (currMouse && !mouseDown)
	{
		Ogre::Light *light = mSceneMgr->getLight("pointLight");
		light->setVisible(!light->getVisible());
	}
	mouseDown = currMouse;

	toggle -= evt.timeSinceLastFrame;
	if ((toggle < 0.0f ) && mKeyboard->isKeyDown(OIS::KC_1))
	{
		toggle = 0.5;
		Ogre::Light* light = mSceneMgr->getLight("pointLight");
		light->setVisible(!light->isVisible());
	}

	Ogre::Vector3 transVector = Ogre::Vector3::ZERO;
	if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
	{
		transVector.z -= move;
	}
	if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
	{
		transVector.z += move;
	}
	if (mKeyboard->isKeyDown(OIS::KC_J)) // Left - yaw or strafe
	{
		if(mKeyboard->isKeyDown( OIS::KC_LSHIFT ))
		{
			// Yaw left
			mSceneMgr->getSceneNode("NinjaNode")->yaw(Ogre::Degree(rotate * 5));
		} 
		else
		{
			transVector.x -= move; // Strafe left
		}
	}
	if (mKeyboard->isKeyDown(OIS::KC_L)) // Right - yaw or strafe
	{
		if(mKeyboard->isKeyDown( OIS::KC_LSHIFT ))
		{
			// Yaw right
			mSceneMgr->getSceneNode("NinjaNode")->yaw(Ogre::Degree(-rotate * 5));
		} 
		else 
		{
			transVector.x += move; // Strafe right
		}
	}
	if (mKeyboard->isKeyDown(OIS::KC_U)) // Up
	{
		transVector.y += move;
	}
	if (mKeyboard->isKeyDown(OIS::KC_O)) // Down
	{
		transVector.y -= move;
	}

	mSceneMgr->getSceneNode("NinjaNode")->translate(transVector * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	return true;
}
//-----------------------------------------------------------------------------
bool BasicTutorial4::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
	bool ret = BaseApplication::frameRenderingQueued(evt);
	if (!processUnbufferedInput(evt))
		return false;
	return ret;
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
	int main(int argc, char *argv[])
#endif
	{
		// Create application object
		BasicTutorial4 app;

		try {
			app.go();
		} catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif
