#pragma once

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    int m_Count;

public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline int getCount() const { return m_Count; }
};