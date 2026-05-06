# C++

## 单例模式
* **核心目标**：确保证一个类在程序生命周期内只有一个实例，并提供全局访问点。
* **模板（C++11及以上版本）**：基于CRTP模式的单例模板，实现了线程安全、懒加载、禁止拷贝，适配任意类。
    ```cpp
    #include <mutex>
    #include <memory>
    #include <type_traits>
    
    // 单例模板类（CRTP奇异递归模板模式）
    template <typename T>
    class Singleton 
    {
    public:
        // 获取唯一实例（线程安全、懒加载）
        static T& GetInstance() 
        {
            // C++11 静态局部变量初始化是线程安全的
            static T instance;
            return instance;
        }
    
        // 禁用拷贝构造
        Singleton(const Singleton&) = delete;
        // 禁用移动构造
        Singleton(Singleton&&) = delete;
        // 禁用赋值运算符
        Singleton& operator=(const Singleton&) = delete;
        // 禁用移动赋值
        Singleton& operator=(Singleton&&) = delete;
    
    protected:
        // 保护构造函数：禁止外部直接创建，允许子类（目标类）构造
        Singleton() = default;
        // 保护析构函数：禁止外部直接删除，允许子类析构
        ~Singleton() = default;
    };
    
    // -------------------------- 用法示例 --------------------------
    // 1. 定义需要单例化的类（继承Singleton模板）
    class ConfigManager : public Singleton<ConfigManager> 
    {
        // 必须声明为友元，让Singleton能访问构造/析构
        friend class Singleton<ConfigManager>;
  
    private:
        // 私有构造函数：确保只能通过 GetInstance 创建
        ConfigManager() 
        {
            // 初始化逻辑（比如加载配置文件）
            printf("ConfigManager 实例创建\n");
        }
    
    public:
        // 业务方法示例
        void LoadConfig(const std::string& path) 
        {
            printf("加载配置文件：%s\n", path.c_str());
        }
    
        std::string GetConfig(const std::string& key) 
        {
            return "配置值：" + key;
        }
    };
    
    // 2. 测试代码
    int main() 
    {
        // 获取单例实例并调用方法
        ConfigManager& config = ConfigManager::GetInstance();
        config.LoadConfig("config.json");
        printf("%s\n", config.GetConfig("window_width").c_str());
    
        // 验证唯一性（两个引用指向同一个实例）
        ConfigManager& config2 = ConfigManager::GetInstance();
        printf("是否同一实例：%d\n", &config == &config2); // 输出 1
    
        return 0;
    }
   ```
* **适用场景**： 
  * **资源管理器**：配置管理器、日志管理器、数据库连接池；
  * **硬件控制**：打印机驱动、显卡/声卡等硬件设备的封装；
  * **全局状态存储**：游戏中的全局游戏状态、OpenGL上下文管理器；
  * **工具类**：全局工具函数的封装（如字符串工具、数学工具）。
* **优缺点**：

| 优点 | 缺点 |
|----|----|
| 保证实例唯一性，避免资源浪费 | 增加代码耦合性，不利于单元测试 |
| 增加代码耦合性，不利于单元测试 | 全局访问，简化调用逻辑 |
| 单例实例生命周期与程序绑定，无法灵活销毁 | 懒加载版本可节省启动资源多 |

* **注意事项**
  * **避免滥用**：不要把所有类都做成单例，仅用于真正需要 “全局唯一” 的场景；
  * **线程安全**：C++11前的懒汉式必须加锁，否则多线程会创建多个实例；
  * **析构顺序**：单例的析构由系统自动完成（程序退出时），无需手动 delete；
  * **拷贝控制**：必须禁用拷贝构造和赋值运算符，否则可能通过拷贝创建新实例。
