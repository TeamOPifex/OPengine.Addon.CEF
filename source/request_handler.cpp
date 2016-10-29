#include <fstream>
#include "../include/request_handler.h"
#include "include/cef_request_handler.h"

cef_return_value_t RequestHandler::OnBeforeResourceLoad(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	CefRefPtr<CefRequestCallback> callback) {
	//std::string reqStr = request.get()->GetURL().ToString();
	//const char* url = reqStr.c_str();
	//OPlogInfo("REQ %s", url);

	return cef_return_value_t::RV_CONTINUE;
}

bool RequestHandler::OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	bool is_redirect) {

	return false;
}