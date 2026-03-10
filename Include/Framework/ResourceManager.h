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

    static std::unique_ptr<ResourceManager> mInstance;
    static std::mutex mInstanceMutex;

public:
    static ResourceManager* GetInstance();

    // 着色器管理
    std::shared_ptr<Shader> GetShader(const std::string& vertexPath, const std::string& fragmentPath);
    void ReleaseShader(const std::string& vertexPath, const std::string& fragmentPath);

    // 纹理管理
    std::shared_ptr<Texture> GetTexture(const std::string& filePath, unsigned int textureUnit);
    void ReleaseTexture(const std::string& filePath);

    // 几何体管理
    std::shared_ptr<Geometry> GetGeometry(const std::string& type, float param1 = 1.0f, float param2 = 1.0f, float param3 = 1.0f);
    void ReleaseGeometry(const std::string& type, float param1 = 1.0f, float param2 = 1.0f, float param3 = 1.0f);

    // 清理所有资源
    void ClearAllResources();

private:
    // 资源缓存
    std::unordered_map<std::string, std::shared_ptr<Shader>> mShaderCache;
    std::unordered_map<std::string, std::shared_ptr<Texture>> mTextureCache;
    std::unordered_map<std::string, std::shared_ptr<Geometry>> mGeometryCache;

    // 生成资源键
    std::string GenerateShaderKey(const std::string& vertexPath, const std::string& fragmentPath);
    std::string GenerateTextureKey(const std::string& filePath);
    std::string GenerateGeometryKey(const std::string& type, float param1, float param2, float param3);
};

#endif //GLRENDERER_RESOURCEMANAGER_H