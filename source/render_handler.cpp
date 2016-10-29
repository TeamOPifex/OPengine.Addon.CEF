#include <fstream>
#include "../include/render_handler.h"
#include "./Data/include/OPcman.h"
#include "./Human/include/Rendering/OPshader.h"
#include "./Human/include/Rendering/Primitives/OPquad.h"
#include "./Human/include/Systems/OPrenderSystem.h"

RenderHandler::RenderHandler()
{
  initialized = false;
}

void RenderHandler::init(void)
{
	OPtextureDesc desc = OPtextureDesc(OPRENDERER_ACTIVE->OPWINDOW_ACTIVE->Width, OPRENDERER_ACTIVE->OPWINDOW_ACTIVE->Height, OPtextureFormat::RGBA, OPtextureWrap::CLAMP_TO_BORDER, OPtextureFilter::NEAREST);
	texture = OPRENDERER_ACTIVE->Texture.Create(desc);

	Tex = OPtexture2DCreate(texture, NULL);
	initialized = true;
}

void RenderHandler::draw(void)
{
	OPrenderDepth(0);
	OPrenderCull(0);

	OPtexture2DRender(Tex);
}

void RenderHandler::reshape(int w_, int h_)
{
  w = w_;
  h = h_;
}

bool RenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect)
{
  rect = CefRect(0, 0, w, h);
  return true;
}

void RenderHandler::OnPaint(CefRefPtr<CefBrowser> browser,
                            PaintElementType type,
                            const RectList &dirtyRects,
                            const void* buffer,
                            int width,
                            int height)
{
	OPRENDERER_ACTIVE->Texture.Bind(texture, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (unsigned char*) buffer);
	//OPlog("+");

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint RenderHandler::compileShader(GLenum shaderType, const char* path)
{
	GLuint shader = glCreateShader(shaderType);

	std::ifstream ifs(path);
	std::string shaderStr( (std::istreambuf_iterator<char>(ifs) ),
							(std::istreambuf_iterator<char>()  ) );

	const char* shaderData = shaderStr.c_str();

	glShaderSource(shader, 1, &shaderData, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	printf("SHADER COMPILE ERROR\n");

	return shader;
}
