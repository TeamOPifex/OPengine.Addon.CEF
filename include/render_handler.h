#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "include/cef_render_handler.h"
#include "./Human/include/Rendering/OPeffect.h"
#include "./Human/include/Rendering/OPmesh.h"
#include "./Human/include/Rendering/OPmodel.h"
#include "./Pipeline/include/OPtexture2D.h"

#ifndef RENDER_HANDLER_H
#define RENDER_HANDLER_H

class RenderHandler : public CefRenderHandler {
  public:
    RenderHandler();

    bool initialized;

    void init(void);
    void draw(void);
    void reshape(int, int);

    bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);

    void OnPaint(CefRefPtr<CefBrowser> browser,
                 PaintElementType type,
                 const RectList &dirtyRects,
                 const void* buffer,
                 int width,
                 int height);

  private:
    int w, h;

    GLuint positionLoc, vbo;

	OPtexture* texture;
	OPtexture2DOLD* Tex;

    GLuint compileShader(GLenum, const char*);

    IMPLEMENT_REFCOUNTING(RenderHandler);

};

#endif
