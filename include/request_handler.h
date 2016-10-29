#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "include/cef_request_handler.h"
#include "./Human/include/Rendering/OPeffect.h"
#include "./Human/include/Rendering/OPmesh.h"
#include "./Human/include/Rendering/OPmodel.h"
#include "./Pipeline/include/OPtexture2D.h"


class RequestHandler : public CefRequestHandler {
  public:

	ReturnValue OnBeforeResourceLoad(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		CefRefPtr<CefRequestCallback> callback);

	bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		bool is_redirect);

  private:
	  
    IMPLEMENT_REFCOUNTING(RequestHandler);

};