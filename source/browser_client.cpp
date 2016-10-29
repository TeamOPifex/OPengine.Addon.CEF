#include "../include/browser_client.h"

#include "include/base/cef_logging.h"
#include "include/cef_cookie.h"

BrowserClient::BrowserClient(RenderHandler* renderHandler, RequestHandler* requestHandler)
{
  handler = renderHandler;
  handlerReq = requestHandler;
}

CefRefPtr<CefRenderHandler> BrowserClient::GetRenderHandler() {
  return handler;
};

CefRefPtr<CefRequestHandler> BrowserClient::GetRequestHandler() {
	return handlerReq;
};
