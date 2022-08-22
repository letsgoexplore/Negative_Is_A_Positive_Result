/*************************************************************************
【文件名】                      User.hpp
【功能模块和目的】
                  成员类头文件。类中同时也声明了部分invalid_argument类。
                  1. User 和 Administrator两个类以及User 和 Tube 两个类之间，由于需要进行权限“签名” （即只有Collector/LabWorker能够创建或修改Tube，User被指定为Administrator后需要升级为Administrator)，所以需要相互include。我们在cpp文件中进行include避免编译错误。
 
                  2. 公有继承于UserBase，管理User成员的个人信息（包括身份证号码/姓名/密码/核酸记录）。
 
                  3. Collector/LabWorker成员也是属于User，但是类内部有二者专属的函数（即函数会验证User的身份， 只有当User是Collector/LabWorker，才能执行，否则报错）。Admininstrator继承于User类。
 
                  4. 从功能上来讲，Administrator需要修改其它User对象的角色，LabWorker需要修改其它User对象的 核酸信息，都会触碰到其它对象的私有信息。在本类中，考虑到只有对象自身能够修改自身信息，我们使Administrator/LabWorker只将更新的信息存储到静态向量 m_AllInfo中， 每一个用户登陆、 以及在任何操作之后， 用户都会从m_AllInfo中更新自己的信息。
 
【开发者及日期】            Jason Zhao 2022/07/18
【更改记录】                   暂无
*************************************************************************/

#ifndef User_hpp
#define User_hpp


#include <stdexcept>
#include "UserBase.hpp"
#include "UserRole.hpp"
#include "Tube.hpp"
using namespace std;

//枚举类，由于Admin不通过同样的方式进行添加，所以只有采集者和结果录入者两个身份
enum class UserType{
    ADMIN = 1,
    COLLECTOR = 2,
    LABWORKER = 3
};

using UT = UserType;

/*************************************************************************
【类名】             NoCollectorAccess
【功能】             在不具备Collector权限的User使用Collector权限时抛出异常
【接口说明】         异常函数，无接口
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class NoCollectorAccess : public invalid_argument{
public:
    NoCollectorAccess();
};

/*************************************************************************
【类名】             NoLabWorkerAccess
【功能】             在不具备LabWorker权限的User使用LabWorker权限时抛出异常
【接口说明】         异常函数，无接口
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class NoLabWorkerAccess : public invalid_argument{
public:
    NoLabWorkerAccess();
};

/*************************************************************************
【类名】             NoAdminAccess
【功能】             在不具备Admin权限的User使用Admin权限时抛出异常
【接口说明】         异常函数，无接口
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class NoAdminAccess : public invalid_argument{
public:
    NoAdminAccess();
};

/*************************************************************************
【类名】             NoAdminCreated
【功能】             在从txt文件中读取后没有任何Admin被创建时抛出异常
【接口说明】         异常函数，无接口
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class NoAdminCreated : public invalid_argument{
public:
    NoAdminCreated();
};

/*************************************************************************
【类名】             ExceptionOnlyOneAdminLeft
【功能】             在仅剩的Admin试图舍弃Admin权限时抛出异常
【接口说明】         异常函数，无接口
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class ExceptionOnlyOneAdminLeft : public invalid_argument{
public:
    ExceptionOnlyOneAdminLeft();
};


/*************************************************************************
【类名】             User
【功能】             管理User成员的个人信息（包括身份证号码/姓名/密码/核酸记录），根据User权限实现相应功能。
            考虑到只有对象自身能够修改自身信息，我们使Administrator/LabWorker只将更新的信息存储到静态向量 m_AllInfo中， 每一个用户登陆、 以及在任何操作之后， 用户都会从m_AllInfo中更新自己的信息。所以中间会生成内嵌类InfoRecord.
【接口说明】
 Normal User
     是否是管理员: IsAdministrator
     注销账号：DeleteSelf
     更新信息：UpdateResult
 LabWorker
    添加结果：AddResult
 Admin(待继承）
     授予权限：AddRole；
     剥夺权限：DeleteRole；
 全局函数
     输入ID，注册时，检查是否已经在m_All被创建：AlreadyRegistered
     输入ID，遍历m_AllInfo时，返回ID对应的InfoRecord指针：IsRegistered
     输入ID，遍历时，返回ID对应的User指针：Verify
 读取与显示
     流运算符：  <<,>>
     从文件中读取：SaveToFile(const string& FileName) ,  LoadFromFile(const string& FileName
 
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class User : public UserBase{
public:
    //构造函数、析构函数
    User() = delete;
    User& operator=(const User&) = delete;
    //公有的构造函数默认User不是任何角色UserRole，私有的构造函数能修改UserRole
    User(string UserId, string UserName, string PlainPassword);
    User(string UserId, string UserName, CipherText Password);
    ~User();
    
    //拷贝构造函数：仅限于给Administrator签名使用，不会被加入到m_All的数据库中
    User(const User& anUser);
    
    //流运算符重载以及读取与保存文件
    friend ostream& operator<<(ostream& Stream, const User& anUser);
    friend istream& operator>>(istream& Stream, User& anUser);
    static void SaveToFile(const string& FileName);
    static void LoadFromFile(const string& FileName);
        
    //Normal User:个人操作
    bool IsAdministrator() const override;
    void DeleteSelf() override;
    void UpdateResult();
    
    //LabWorker:向m_AllInfo中添加结果
    void AddResultToUser(string UserId, TestResult aTestResult);
    void AddResult(string aTubeId, bool aResult);
    
    //内嵌类声明
    //由于录入员无法直接操作每个User成员的数据，所以我们新建一个向量专门存储最新的核酸信息以及最新的Role信息;
    //考虑到是内嵌类，就不加m_s前缀了
    /*************************************************************************
    【类名】             User::InfoRecord
    【功能】            维护最新的数据信息
    【接口说明】         无
    【开发者及日期】     Jason Zhao 2022/07/21
    【更改记录】         暂无
    *************************************************************************/
    class InfoRecord{
    public:
        InfoRecord(string anUserId);
        string UserId;
        UserRole LatestUserRole;
        TestResult UserTestResult;
        friend ostream& operator<<(ostream& Stream, const User::InfoRecord& anInfoRecord);
        friend istream& operator>>(istream& Stream, User::InfoRecord& anInfoRecord);
    };
    
    //静态函数：验证身份
    static bool AlreadyRegistered(const string UserId);
    static shared_ptr<InfoRecord> IsRegistered(const string UserId);
    static shared_ptr<User> Verify(const string UserId, const string UserName, const string PlainPassword);
    
    //常引用
    const unsigned int& AdminCount;
    const UserRole& MyUserRole;
    const TestResult& LatestResult;
    
    
protected:
    //Admin: 授予或剥夺User成员（包括自己）为Administrator/Collector/LabWorker权限， 同样也可以退出管理员成为普通成员
    void AddRole(string UserId, UT NewUserType);
    void DeleteRole(string UserId, UT NewUserType);
    UserRole m_UserRole;
    TestResult m_LatestResult;
    
private:
    //私有构造函数：能够修改UserRole的构造函数是私有的
    User(string UserId, string UserName, string PlainPassword, bool IsAdministrator, bool IsCollector, bool IsLabWorker);
    
    //私有数据成员
    static unsigned int m_AdminCount;
    static vector<shared_ptr<User>> m_All;
    static vector<shared_ptr<InfoRecord>> m_AllInfo;
    
    
    
};
#endif /* User_hpp */
