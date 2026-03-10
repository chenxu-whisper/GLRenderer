#include "Core.h"
#include "Framework/ResourceManager.h"
#include "Framework/Shader.h"
#include "../../Include/Framework/Texture.h"
#include "Framework/Geometry.h"

ResourceManager::ResourceManager() = default;

ResourceManager::~ResourceManager()
{
    ClearAllResources();
}

std::unique_ptr<ResourceManager> ResourceManager::mInstance = nullptr;
std::mutex ResourceManager::mInstanceMutex;

// 获取单例实例
ResourceManager* ResourceManager::GetInstance()
{
    std::lock_guard<std::mutex> lock(mInstanceMutex);

    if (mInstance == nullptr)
        mInstance = std::make_unique<ResourceManager>();

    return mInstance.get();
}

// 生成着色器键
std::string ResourceManager::GenerateShaderKey(const std::string& vertexPath, const std::string& fragmentPath)
{
    return vertexPath + "|" + fragmentPath;
}

// 生成纹理键
std::string ResourceManager::GenerateTextureKey(const std::string& filePath)
{
    return filePath;
}

// 生成几何体键
std::string ResourceManager::GenerateGeometryKey(const std::string& type, float param1, float param2, float param3)
{
    return type + "|" + std::to_string(param1) + "|" + std::to_string(param2) + "|" + std::to_string(param3);
}

// 获取着色器
std::shared_ptr<Shader> ResourceManager::GetShader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string key = GenerateShaderKey(vertexPath, fragmentPath);
    auto it = mShaderCache.find(key);

    if (it != mShaderCache.end())
        return it->second;

    // 创建新着色器
    auto shader = std::make_shared<Shader>();
    shader->LoadCompileShader(vertexPath, fragmentPath);
    mShaderCache[key] = shader;

    return shader;
}

// 释放着色器
void ResourceManager::ReleaseShader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string key = GenerateShaderKey(vertexPath, fragmentPath);
    mShaderCache.erase(key);
}

// 获取纹理
std::shared_ptr<Texture> ResourceManager::GetTexture(const std::string& filePath, unsigned int textureUnit)
{
    std::string key = GenerateTextureKey(filePath);
    auto it = mTextureCache.find(key);

    if (it != mTextureCache.end())
        return it->second;

    // 创建新纹理
    auto texture = std::make_shared<Texture>();
    texture->LoadTexture(filePath, textureUnit);
    mTextureCache[key] = texture;

    return texture;
}

// 释放纹理
void ResourceManager::ReleaseTexture(const std::string& filePath)
{
    std::string key = GenerateTextureKey(filePath);
    mTextureCache.erase(key);
}

// 获取几何体
std::shared_ptr<Geometry> ResourceManager::GetGeometry(const std::string& type, float param1, float param2, float param3)
{
    std::string key = GenerateGeometryKey(type, param1, param2, param3);
    auto it = mGeometryCache.find(key);

    if (it != mGeometryCache.end())
        return it->second;

    // 创建新几何体
    std::shared_ptr<Geometry> geometry;
    if (type == "cube")
        geometry = Geometry::CreateCube(param1, param2, param3);
    else if (type == "sphere")
        geometry = Geometry::CreateSphere(param1);

    if (geometry)
        mGeometryCache[key] = geometry;

    return geometry;
}

// 释放几何体
void ResourceManager::ReleaseGeometry(const std::string& type, float param1, float param2, float param3)
{
    std::string key = GenerateGeometryKey(type, param1, param2, param3);
    mGeometryCache.erase(key);
}

// 清理所有资源
void ResourceManager::ClearAllResources()
{
    mShaderCache.clear();
    mTextureCache.clear();
    mGeometryCache.clear();
}