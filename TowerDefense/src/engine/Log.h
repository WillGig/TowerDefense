#pragma once

#define ASSERT(x) if(!(x)) __debugbreak();
#ifdef _DEBUG
#define GLCall(x) GLClearError();\
        x;\
        ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

//Clear all GL errors
void GLClearError();

//Prints out GL error and location
//Only called in debug call GLCall()
bool GLLogCall(const char* function, const char* file, int line);