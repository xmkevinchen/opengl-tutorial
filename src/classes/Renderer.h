#pragma once

#include <GL/glew.h>
#include <signal.h>
#include <cassert>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) \
    if (!(x))     \
        raise(SIGTRAP);

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

class Renderer
{
public:
    void draw(const VertexArray &va,
              const IndexBuffer &ib,
              const Shader &shader) const;
    void clear();
};
