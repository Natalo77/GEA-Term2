#include "Ogre3DApplication.h"

#include <OGRE/OgrePlatform.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "OgreString.h"
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#include "SampleBrowser_iOS.h"
#elif OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
#include "SampleBrowser_Android.h"
#endif

#include "Ogre3DApplication.h"

#ifdef NDEBUG
#pragma comment(lib, "OgreMain.lib")
#pragma comment(lib, "OgreBites.lib")
#pragma comment(lib, "OgreRTShaderSystem.lib")
#pragma comment(lib, "OgreOverlay.lib")
#else
#pragma comment(lib, "OgreMain_d.lib")
#pragma comment(lib, "OgreBites_d.lib")
#pragma comment(lib, "OgreRTShaderSystem_d.lib")
#pragma comment(lib, "OgreOverlay_d.lib")
#endif


/*int main(int argc, char *argv[])
{
	//Scenes are GO!
	///Create an instance of our ogre3D application. -> then initialise it -> then ask the 'rootNode' to start rendering things. -> then close the app once it's done.
	Ogre3DApplication app;
	app.initApp();
	app.getRoot()->startRendering();
	app.closeApp();
	///obligatory return 0 just for fun.
	return 0;
}*/

//WinMain()
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		WinMain()

Summary:	Creates an instance of our created Ogre3DApplication.
			Sets it off rendering.
			Then cleans up once it stops.

Args:		obligatory HINSTANCEs, cmdLine input and INT

Returns:	0 - becuase it did a great job with the thing!
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR cmdLine, INT) {
	int argc = __argc;
	char** argv = __argv;

	try
	{
		Ogre3DApplication app;

		app.initApp();
		app.getRoot()->startRendering();
		app.closeApp();

	}
	catch (Ogre::Exception& e)
	{
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_ICONERROR | MB_TASKMODAL);
	}
	return 0;
}