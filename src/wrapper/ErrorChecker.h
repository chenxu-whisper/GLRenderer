#ifndef ERRORCHECKER_H
#define ERRORCHECKER_H

#ifdef DEBUG
#define CHECK_GL_ERROR(func) func; ErrorChecker()
#else
#define CHECK_GL_ERROR(func) func
#endif

// 检查OpenGL错误
void ErrorChecker();

#endif //ERRORCHECKER_H
