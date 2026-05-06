#ifndef GLRENDERER_RESOURCEMANAGER_H
#define GLRENDERER_RESOURCEMANAGER_H

#include "Core.h"
#include "Framework/Shader.h"
#include "Framework/Texture.h"
#include "Framework/Geometry.h"

// 全局访问宏
#define RESOURCE_MANAGER ResourceManager::GetInstance()

class Shader;
class Texture;
class Geometry;

class ResourceManager
{
private:
    ResourceManager();
    ~ResourceManager();

    // 友元声明，允许std::make_unique访问私有构造函数
    friend std::unique_ptr<ResourceManager> std::make_unique<ResourceManager>();
    // 友元声明，允许std::default_delete访问私有析构函数
    friend std::default_delete<ResourceManager>;

    /**
     * @brief 资源管理器实例
     */
    static std::unique_ptr<ResourceManager> mInstance;
    /**
     * @brief 资源管理器实例互斥锁
     */
    static std::mutex mInstanceMutex;

public:
    /**
     * @brief 获取资源管理器实例
     * @return ResourceManager*: 资源管理器实例指针
     */
    static ResourceManager* GetInstance();

    /**
     * @brief 获取或加载着色器资源
     * @param vertexPath: 顶点着色器文件路径
     * @param fragmentPath: 片元着色器文件路径
     * @return std::shared_ptr<Shader>: 着色器资源指针
     */
    std::shared_ptr<Shader> GetShader(const std::string& vertexPath, const std::string& fragmentPath);
    /**
     * @brief 释放着色器资源
     * @param vertexPath: 顶点着色器文件路径
     * @param fragmentPath: 片元着色器文件路径
     */
    void ReleaseShader(const std::string& vertexPath, const std::string& fragmentPath);
    /**
     * @brief 获取或加载纹理资源
     * @param filePath: 纹理文件路径
     * @param textureUnit: 纹理单元索引
     * @return std::shared_ptr<Texture>: 纹理资源指针
     */
    std::shared_ptr<Texture> GetTexture(const std::string& filePath, unsigned int textureUnit);
    /**
     * @brief 释放纹理资源
     * @param filePath: 纹理文件路径
     */
    void ReleaseTexture(const std::string& filePath);
    /**
     * @brief 获取或加载几何体资源
     * @param type: 几何体类型
     * @param param1: 几何体参数1
     * @param param2: 几何体参数2
     * @param param3: 几何体参数3
     * @return std::shared_ptr<Geometry>: 几何体资源指针
     */
    std::shared_ptr<Geometry> GetGeometry(const std::string& type, float param1 = 1.0f, float param2 = 1.0f, float param3 = 1.0f);
    /**
     * @brief 释放几何体资源
     * @param type: 几何体类型
     * @param param1: 几何体参数1
     * @param param2: 几何体参数2
     * @param param3: 几何体参数3
     */
    void ReleaseGeometry(const std::string& type, float param1 = 1.0f, float param2 = 1.0f, float param3 = 1.0f);

    /**
     * @brief 清理所有资源
     */
    void ClearAllResources();

private:
    // 资源缓存
    std::unordered_map<std::string, std::shared_ptr<Shader>> mShaderCache; // 着色器缓存
    std::unordered_map<std::string, std::shared_ptr<Texture>> mTextureCache; // 纹理缓存
    std::unordered_map<std::string, std::shared_ptr<Geometry>> mGeometryCache; // 几何体缓存

    // 生成资源键
    /**
     * @brief 生成着色器资源键
     * @param vertexPath: 顶点着色器文件路径
     * @param fragmentPath: 片元着色器文件路径
     * @return std::string: 着色器资源键
     */
    std::string GenerateShaderKey(const std::string& vertexPath, const std::string& fragmentPath);
    /**
     * @brief 生成纹理资源键
     * @param filePath: 纹理文件路径
     * @return std::string: 纹理资源键
     */
    std::string GenerateTextureKey(const std::string& filePath);
    /**
     * @brief 生成几何体资源键
     * @param type: 几何体类型
     * @param param1: 几何体参数1
     * @param param2: 几何体参数2
     * @param param3: 几何体参数3
     * @return std::string: 几何体资源键
     */
    std::string GenerateGeometryKey(const std::string& type, float param1, float param2, float param3);
};

#endif //GLRENDERER_RESOURCEMANAGER_H