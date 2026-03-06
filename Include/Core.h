#ifndef GLRENDERER_CORE_H
#define GLRENDERER_CORE_H

// 系统头文件
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <fstream>
#include <assert.h>

// OpenGL第三方库头文件
#include <Glad/glad.h> // note：glad头文件放在GLFW头文件之前，避免重复包含
#include <GLFW/glfw3.h>
#include "Application/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// 自定义头文件
#include "Wrapper/ErrorChecker.h"

#endif //GLRENDERER_CORE_H