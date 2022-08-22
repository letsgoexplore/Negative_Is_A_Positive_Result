/*************************************************************************
【文件名】                      UserBase.hpp
【功能模块和目的】
                  抽象成员类头文件。类中同时也声明了部分invalid_argument类。
                  这一抽象成员类高度可重用，符合通用类的要求。
 
【开发者及日期】            Jason Zhao 2022/07/18
【更改记录】                   暂无
*************************************************************************/

#ifndef UserBase_hpp
#define UserBase_hpp

#include <stdio.h>
#include <memory>
#include <iostream>
#include "CipherText.hpp"
using namespace std;

/*************************************************************************
【类名】             ExceptionUserAlreadyRegistered
【功能】             在输入ID的用户已经被创建时抛出异常
【接口说明】         异常函数，无接口
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class ExceptionUserAlreadyRegistered : public invalid_argument{
public:
    ExceptionUserAlreadyRegistered();
};



/*************************************************************************
【类名】             ExceptionNoUser
【功能】             在遍历所有已注册用户没搜寻到抛出异常
【接口说明】         异常函数，无接口
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class ExceptionNoUser : public invalid_argument{
public:
    ExceptionNoUser();
};



/*************************************************************************
【类名】             ExceptionWrongNameOrPassword
【功能】             在用户名/密码和ID不匹配时抛出异常
【接口说明】         异常函数，无接口
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class ExceptionWrongNameOrPassword : public invalid_argument{
public:
    ExceptionWrongNameOrPassword();
};



/*************************************************************************
【类名】             ExceptionCannotDeleteAdministrator
【功能】             在试图删除管理员时抛出异常。
            这一个异常在本项目中不会用到（因为管理员也可以注销自己的账号，只要他不是最后一个管理员）

【接口说明】         异常函数，无接口
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class ExceptionCannotDeleteAdministrator : public invalid_argument{
public:
    ExceptionCannotDeleteAdministrator();
};


/*************************************************************************
【类名】             UserBase
【功能】             抽象成员类，是具有ID、Name、密码三个要素的用户的抽象类，高度可重用
【接口说明】
 User
     是否是管理员: IsAdministrator
     注销账号：DeleteSelf
     修改密码：ChangePassword
 

 全局函数
     输入ID，遍历m_AllInfo时，返回ID对应的UserBase指针：IsRegistered
     输入ID、Name、Password，遍历m_All后，返回ID对应的UserBase指针：Verify
 读取与显示
     流运算符：  <<,>>
     从文件中读取：SaveToFile(const string& FileName) ,  LoadFromFile(const string& FileName
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class UserBase{
public:
    UserBase() = delete;
    UserBase(const UserBase&) = delete;
    UserBase(string UserId, string UserName, string PlainPassword);
    UserBase(string UserId, string UserName, CipherText Password);
    ~UserBase();
    
    
    //验证身份
    static shared_ptr<UserBase> IsRegistered(const string UserId);
    static shared_ptr<UserBase> Verify(const string UserId, const string UserName, const string PlainPassword);
    
    //个人操作
    virtual bool IsAdministrator() const;
    void ChangePassword(const string PlainPassword);
    virtual void DeleteSelf();
    
    //流运算符重载以及读取与保存文件(在User类里会重载）
    friend ostream& operator<<(ostream& Stream, const UserBase& anUser);
    friend istream& operator>>(istream& Stream, UserBase& anUser);
    
    //常引用
    const string& UserId;
protected:
    string m_sUserId;
    string m_sUserName;
    CipherText m_Password;

private:
    static vector<shared_ptr<UserBase>> m_All;
    
    
};
#endif /* UserBase_hpp */
