#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "resource.h"

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
    //eglView->setFrameSize(eglView->getFullscreenWidth(), eglView->getFullscreenHeight());
    //eglView->enterFullscreen(0, 0);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
    ::SendMessage(eglView->getHWnd(), WM_SETICON, true, LPARAM(hIcon));

    int ret = CCApplication::sharedApplication()->run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
