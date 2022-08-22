/*************************************************************************
【文件名】                       Administrator.cpp
【功能模块和目的】
                  管理员类实现文件。公有继承于User，管理User成员的角色，可以给予或剥夺User成员（包括自己）为 Administrator/Collector/LabWorker权限，同样也可以退出管理员成为普通成员.
                  
                  Administrator的构造函数需要由User进行“签名”，只有当User的一个元素（IsAdministartor）为true时， Administartor才能够用User的信息进行构造。
 
                  注意，我们在User类中既有IsAdministrator虚函数，也有 IsAdministrator这一元素， 这一机制并非是重复，而是要避免有User用其它已经成为Administer的成员的 User部分进行签名。
 
【开发者及日期】            Jason Zhao 2022/07/18
【更改记录】                   暂无
*************************************************************************/

#include "Administrator.hpp"

InvalidAdminSignature::InvalidAdminSignature() : invalid_argument("The User you used for signing is not Administrator"){
}

//anUser在这里相当于“签名”，
//先通过IsAdministrator()先判断anUser是否已经是管理员，
//再通过m_UserRole.IsAdministrator判断anUser是否被授权成为管理员，
//这样避免了有人用管理员Administrator的指针来给自己构建Administrator
/*************************************************************************
【函数名称】       Administrator
【函数功能】      构造函数，从File里直接读取的Administrator可以不用“签名”直接构造
【参数】           shared_ptr<User>签名，用户ID，用户名，密码，是否是Collector，是否是LabWorker
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Administrator::Administrator(shared_ptr<User> anUser, string UserId, string UserName, CipherText Password, bool IsCollector, bool IsLabWorker): User(UserId, UserName, Password){
    if(anUser->IsAdministrator()){
        throw InvalidAdminSignature();
    }
    else if(!(anUser->MyUserRole.IsAdministrator)){
        throw NoAdminAccess();
    }
    anUser->DeleteSelf();
    m_UserRole.AddAdministrator();
    if(IsCollector){
        m_UserRole.AddCollector();
    }
    if(IsLabWorker){
        m_UserRole.AddLabWorker();
    }
}

/*************************************************************************
【函数名称】       Administrator
【函数功能】      构造函数，从File里直接读取的Administrator可以不用“签名”直接构造
【参数】           User签名，用户ID，用户名，密码，是否是Collector，是否是LabWorker
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Administrator::Administrator(User anUser, string UserId, string UserName, CipherText Password, bool IsCollector, bool IsLabWorker): User(UserId, UserName, Password){
    if(anUser.IsAdministrator()){
        throw InvalidAdminSignature();
    }
    else if(!(anUser.MyUserRole.IsAdministrator)){
        throw NoAdminAccess();
    }
    anUser.DeleteSelf();
    m_UserRole.AddAdministrator();
    if(IsCollector){
        m_UserRole.AddCollector();
    }
    if(IsLabWorker){
        m_UserRole.AddLabWorker();
    }
    
}

//私有的构造函数，从File里直接读取的Administrator可以不用“签名”直接构造
/*************************************************************************
【函数名称】       Administrator
【函数功能】       私有的构造函数，从File里直接读取的Administrator可以不用“签名”直接构造
【参数】           用户ID，用户名，密码，是否是Collector，是否是LabWorker
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Administrator::Administrator(string UserId, string UserName, string PlainPassword, bool IsCollector, bool IsLabWorker): User(UserId, UserName, PlainPassword){
    m_UserRole.AddAdministrator();
    if(IsCollector){
        m_UserRole.AddCollector();
    }
    if(IsLabWorker){
        m_UserRole.AddLabWorker();
    }
}


/*************************************************************************
【函数名称】       AddAdministrator
【函数功能】       给某一用户增加管理员权限
【参数】           用户ID
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Administrator::AddAdministrator(string UserId){
    auto it = IsRegistered(UserId);
    it->LatestUserRole.AddAdministrator();
}

/*************************************************************************
【函数名称】       QuitAdministrator
【函数功能】       放弃管理员权限
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Administrator::QuitAdministrator(){
    //只剩下一个管理员时不能Quit
    if(User::AdminCount==1){
        throw ExceptionOnlyOneAdminLeft();
    }
    string UserId = m_sUserId;
    string UserName = m_sUserName;
    new User(UserId, UserName, m_Password);
    this->DeleteSelf();
}

/*************************************************************************
【函数名称】       IsAdministrator
【函数功能】       是否是管理员
【参数】           无
【返回值】         bool，是管理员
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Administrator::IsAdministrator() const{
    return true;
}


