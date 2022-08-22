/*************************************************************************
【文件名】                       Administrator.hpp
【功能模块和目的】
                  管理员类头文件。公有继承于User，管理User成员的角色，可以给予或剥夺User成员（包括自己）为 Administrator/Collector/LabWorker权限，同样也可以退出管理员成为普通成员.
                  
                  Administrator的构造函数需要由User进行“签名”，只有当User的一个元素（IsAdministartor）为true时， Administartor才能够用User的信息进行构造。
 
                  注意，我们在User类中既有IsAdministrator虚函数，也有 IsAdministrator这一元素， 这一机制并非是重复，而是要避免有User用其它已经成为Administer的成员的 User部分进行签名。
 
【开发者及日期】            Jason Zhao 2022/07/18
【更改记录】                   暂无
*************************************************************************/
#ifndef Administrator_hpp
#define Administrator_hpp


#include "User.hpp"
using namespace std;

class InvalidAdminSignature : public invalid_argument{
public:
    InvalidAdminSignature();
};

/*************************************************************************
【类名】             Administrator
【功能】             管理User成员的角色，可以给予或剥夺User成员（包括自己）为Administrator/Collector/LabWorker权限，
            同样也可以退出管理员成为普通成员.
【接口说明】
 是否是管理员：IsAdministrator
 增加管理员：AddAdministrator
 退出管理员：QuitAdministrator
 增加Collector/LabWorker权限：AddRole
 剥夺Collector/LabWorker权限：DeleteRole
 
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class Administrator : public User{
public:
    //构造函数、析构函数、赋值运算符
    Administrator() = delete;
    Administrator(const Administrator&) = delete;
    //anUser在这里相当于“签名”，
    //先通过IsAdministrator()先判断anUser是否已经是管理员，
    //再通过m_UserRole.IsAdministrator判断anUser是否被授权成为管理员，
    //这样避免了有人用管理员Administrator的指针来给自己构建Administrator
    Administrator(shared_ptr<User> anUser, string UserId, string UserName, CipherText Password, bool IsCollector, bool IsLabWorker);
    Administrator(User anUser, string UserId, string UserName, CipherText Password, bool IsCollector, bool IsLabWorker);
    Administrator& operator=(const Administrator&) = delete;
    
    //管理员可进行的操作
    void AddAdministrator(string UserId);
    void QuitAdministrator();
    using User::AddRole;
    using User::DeleteRole;
    bool IsAdministrator() const override;
private:
    //从File里直接读取的Administrator可以不用“签名”直接构造
    Administrator(string UserId, string UserName, string PlainPassword, bool IsCollector, bool IsLabWorker);
    
};
#endif /* Administrator_hpp */
