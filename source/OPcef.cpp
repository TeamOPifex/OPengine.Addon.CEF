#include "OPcef.h"
#include "cef_app.h"
#include "simple_app.h"
#include "render_handler.h"
#include "request_handler.h"
#include "browser_client.h"
#include "./Human/include/Rendering/OPrender.h"
#include "./Human/include/Input/OPmouse.h"
#include "./Human/include/Input/OPkeyboard.h"


RenderHandler* renderHandler;
RequestHandler* requestHandler;
CefRefPtr<CefBrowser> browser;

void OPcefInit() {
	OPlog("CEF Init");
	CefEnableHighDPISupport();
	void* sandbox_info = NULL;

#if defined(CEF_USE_SANDBOX)
	// Manage the life span of the sandbox information object. This is necessary
	// for sandbox support on Windows. See cef_sandbox_win.h for complete details.
	CefScopedSandboxInfo scoped_sandbox;
	sandbox_info = scoped_sandbox.sandbox_info();
#endif

	CefMainArgs args;
	CefExecuteProcess(args, nullptr, NULL);

	CefSettings settings;
	settings.single_process = 1;
	settings.remote_debugging_port = 9999;
	//settings.multi_threaded_message_loop = 1;
	settings.windowless_rendering_enabled = true; 
	const char* path = "log.txt";

	// Equivalent assignments.
	CefString(&settings.log_file).FromASCII(path);
	cef_string_from_ascii(path, strlen(path), &settings.log_file);

	//CefString(&settings.locales_dir_path) = OPIFEX_ASSETS;
	//CefRefPtr<SimpleApp> app(new SimpleApp);

	CefInitialize(args, settings, nullptr, sandbox_info);

	//CefRunMessageLoop();
	//CefShutdown();

	CefWindowInfo windowInfo;
	CefBrowserSettings browserSettings;
	browserSettings.webgl = STATE_ENABLED;
	browserSettings.windowless_frame_rate = 60;
	windowInfo.SetAsWindowless(nullptr, true);

	renderHandler = new RenderHandler();
	requestHandler = new RequestHandler();

	CefRefPtr<BrowserClient> client = new BrowserClient(renderHandler, requestHandler);
	browser = CefBrowserHost::CreateBrowserSync(windowInfo, client.get(), "", browserSettings, nullptr);

	//browser = CefBrowserHost::CreateBrowserSync(windowInfo, client.get(), "", browserSettings, nullptr);
	
	renderHandler->reshape(OPRENDERER_ACTIVE->OPWINDOW_ACTIVE->Width, OPRENDERER_ACTIVE->OPWINDOW_ACTIVE->Height);
}

void OPcefLoad(const OPchar* url) {
	if (!renderHandler->initialized)
		renderHandler->init();

	browser->StopLoad();
	browser->GetMainFrame()->LoadURL(url);
}

void OPcefUpdate() {
	CefMouseEvent mouse_event;
	mouse_event.x = OPMOUSE.X();
	mouse_event.y = OPMOUSE.Y();
	CefBrowserHost::MouseButtonType btnType = MBT_LEFT;

	if (OPMOUSE.WasPressed(OPmouseButton::LBUTTON)) {
		OPlogErr("Mouse Clicked: %d, %d", mouse_event.x, mouse_event.y);
		browser->GetHost()->SendMouseClickEvent(mouse_event, btnType, false, 1);
	}

	if (OPMOUSE.MovedX() || OPMOUSE.MovedY()) {
		browser->GetHost()->SendMouseMoveEvent(mouse_event, false);
	}

	if (OPMOUSE.WasReleased(OPmouseButton::LBUTTON)) {
		OPlogErr("Mouse Clicked: %d, %d", mouse_event.x, mouse_event.y);
		browser->GetHost()->SendMouseClickEvent(mouse_event, btnType, true, 1);
	}

	if (OPMOUSE.WasPressed(OPmouseButton::RBUTTON)) {
		btnType = MBT_RIGHT;
		OPlogErr("Mouse Clicked: %d, %d", mouse_event.x, mouse_event.y);
		browser->GetHost()->SendMouseClickEvent(mouse_event, btnType, false, 1);
	}

	if (OPMOUSE.WasReleased(OPmouseButton::RBUTTON)) {
		btnType = MBT_RIGHT;
		OPlogErr("Mouse Clicked: %d, %d", mouse_event.x, mouse_event.y);
		browser->GetHost()->SendMouseClickEvent(mouse_event, btnType, true, 1);
	}

	if (OPMOUSE.WheelMoved() != 0) {
		OPlogErr("Mouse Scroll: %d, %d", mouse_event.x, mouse_event.y);
		browser->GetHost()->SendMouseWheelEvent(mouse_event, 0, OPMOUSE.wheel * 100);
	}

	if (OPKEYBOARD.WasReleased(OPkeyboardKey::BACKSPACE)) {
		browser->GoBack();
	}


	browser->GetHost()->WasResized();
	browser->GetHost()->Invalidate(CefBrowserHost::PaintElementType::PET_VIEW);
	//browser->GetHost()->Invalidate(CefBrowserHost::PaintElementType::PET_POPUP);
	CefDoMessageLoopWork();

	//OPlog(".");

}


void OPcefRender() {
	renderHandler->draw();
}