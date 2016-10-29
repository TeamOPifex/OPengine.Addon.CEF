#include "include/cef_client.h"

#include "request_handler.h"
#include "render_handler.h"
#include "include/cef_command_line.h"
#include "include/cef_browser_process_handler.h"

#ifndef BROWSER_CLIENT_H
#define BROWSER_CLIENT_H

class BrowserClient : public CefClient,
	public CefBrowserProcessHandler {
    public:
      BrowserClient(RenderHandler*, RequestHandler*);

	  virtual CefRefPtr<CefRenderHandler> GetRenderHandler();
	  virtual CefRefPtr<CefRequestHandler> GetRequestHandler();

    private:
		CefRefPtr<CefRenderHandler> handler;
		CefRefPtr<CefRequestHandler> handlerReq;

      IMPLEMENT_REFCOUNTING(BrowserClient);
};

#endif
