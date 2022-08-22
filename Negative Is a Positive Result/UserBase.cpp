/*************************************************************************
【文件名】                      UserBase.cpp
【功能模块和目的】
                  抽象成员类实现文件。
                  这一抽象成员类高度可重用，符合通用类的要求。
 
【开发者及日期】            Jason Zhao 2022/07/18
【更改记录】                   暂无
*************************************************************************/

#include "UserBase.hpp"
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdexcept>

vector<shared_ptr<UserBase>> UserBase::m_All = {};
ExceptionUserAlreadyRegistered::ExceptionUserAlreadyRegistered(): invalid_argument("This UserId is already created"){
}

ExceptionNoUser::ExceptionNoUser() : invalid_argument("The UserId is not created"){
}

ExceptionCannotDeleteAdministrator::ExceptionCannotDeleteAdministrator() : invalid_argument("Can't Delete the Administrator"){    
}

ExceptionWrongNameOrPassword::ExceptionWrongNameOrPassword() : invalid_argument("Wrong Name or Password"){
}

/*************************************************************************
【函数名称】       UserBase
【函数功能】       用户注册
【参数】           ID，用户名，密码（string）
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
UserBase::UserBase(string UserId, string UserName, string PlainPassword):UserId(m_sUserId){
    m_sUserId = UserId;
    m_sUserName = UserName;
    m_Password = PlainPassword;
    m_All.push_back(shared_ptr<UserBase>(this));
}

/*************************************************************************
【函数名称】       UserBase
【函数功能】       用户注册
【参数】           ID，用户名，密码（string）
【返回值】        无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
UserBase::UserBase(string UserId, string UserName, CipherText Password):UserId(m_sUserId){
    m_sUserId = UserId;
    m_sUserName = UserName;
    m_Password = Password;
    m_All.push_back(shared_ptr<UserBase>(this));
}

/*************************************************************************
【函数名称】       ～UserBase
【函数功能】       析构函数
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
UserBase::~UserBase(){
}

/*************************************************************************
【函数名称】       IsAdministrator
【函数功能】       判断管理员权限对外接口
【参数】           无
【返回值】         bool
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool UserBase::IsAdministrator() const{
    return false;
}

/*************************************************************************
【函数名称】       IsAdministrator
【函数功能】       输入ID，遍历m_AllInfo时，返回ID对应的UserBase指针
【参数】           无
【返回值】         bool 是否是
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
shared_ptr<UserBase> UserBase::IsRegistered(const string UserId){
    auto Finder = [&UserId](shared_ptr<UserBase> ptr)->bool{return (ptr->m_sUserId == UserId);};
    //To find out the first user specified by name
    auto it = find_if(m_All.begin(), m_All.end(), Finder);
    if (it == m_All.end()) {
        throw ExceptionNoUser();
    }
    return  *it;
}

/*************************************************************************
【函数名称】       Verify
【函数功能】       输入ID、Name、Password，遍历m_All后，返回ID对应的UserBase指针
【参数】           shared_ptr<UserBase>，找到的对象
【返回值】         bool
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
shared_ptr<UserBase> UserBase::Verify(const string UserId, const string UserName, const string PlainPassword){
    auto it = IsRegistered(UserId);
    //found，but wrong password, throw WRONG PASSWORD exception
    if ((it->m_Password != PlainPassword) ||
             (it->m_sUserName != UserName)){
        throw ExceptionWrongNameOrPassword();
    }
    //return the user's smart pointer
    else {
        return it;
    }
}


/*************************************************************************
【函数名称】       ChangePassword
【函数功能】       改密码
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void UserBase::ChangePassword(const string PlainPassword){
    m_Password = CipherText(PlainPassword);
}


/*************************************************************************
【函数名称】       DeleteSelf
【函数功能】       注销账号
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void UserBase::DeleteSelf(){
    auto Finder = [=](shared_ptr<UserBase> ptr)->bool{return (ptr->m_sUserId == this->m_sUserId);};
    auto it = find_if(m_All.begin(), m_All.end(), Finder);
    if ((*it)->IsAdministrator()) {
        throw ExceptionCannotDeleteAdministrator();
    }
    m_All.erase(it);
}

/*************************************************************************
【函数名称】       流输出运算符
【函数功能】       流输出
【参数】           流，UserBase对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
ostream& operator<<(ostream& Stream, const UserBase& anUserBase){
    Stream << anUserBase.m_sUserId << endl << anUserBase.m_sUserName<< endl << anUserBase.m_Password;
    return Stream;
}

/*************************************************************************
【函数名称】       流输入运算符
【函数功能】       流输入
【参数】           流，UserBase对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
istream& operator>>(istream& Stream, UserBase& anUserBase){
    Stream >> anUserBase.m_sUserId >> anUserBase.m_sUserName >> anUserBase.m_Password;
    return Stream;
}
