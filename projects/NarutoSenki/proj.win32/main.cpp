#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "resource.h"
#endif

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("Naruto Senki");
    eglView->setFrameSize(1280, 720);
    // Set the frame size to the full screen value
    // eglView->setFrameSize(eglView->getFullscreenWidth(), eglView->getFullscreenHeight());
    // eglView->enterFullscreen(0, 0);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
    ::SendMessage(eglView->getHWnd(), WM_SETICON, true, LPARAM(hIcon));
#endif
    return CCApplication::sharedApplication()->run();
}
