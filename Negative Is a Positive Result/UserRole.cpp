/*************************************************************************
【文件名】                      UserRole.cpp
【功能模块和目的】
                  成员权限类实现文件。本文件中仅包含UserRole类，用以实现User的权限管理。
 
【开发者及日期】            Jason Zhao 2022/07/18
【更改记录】                   暂无
*************************************************************************/

#include "UserRole.hpp"
/*************************************************************************
【函数名称】       UserRole
【函数功能】       默认构造函数
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
UserRole::UserRole(): IsAdministrator(m_bIsAdministrator), IsCollector(m_bIsCollector), IsLabWorker(m_bIsLabWorker){
    m_bIsAdministrator = 0;
    m_bIsCollector = 0;
    m_bIsLabWorker = 0;
}

/*************************************************************************
【函数名称】       UserRole
【函数功能】       构造函数
【参数】           3个bool，是否是Admin，是否是Collector，是否是LabWorker
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
UserRole::UserRole(bool IsAdministrator, bool IsCollector, bool IsLabWorker): IsAdministrator(m_bIsAdministrator), IsCollector(m_bIsCollector), IsLabWorker(m_bIsLabWorker){
    m_bIsAdministrator = IsAdministrator;
    m_bIsCollector = IsCollector;
    m_bIsLabWorker = IsLabWorker;
}

/*************************************************************************
【函数名称】       UserRole
【函数功能】       拷贝构造函数
【参数】          UserRole对象
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
UserRole::UserRole(const UserRole& anUserRole): IsAdministrator(m_bIsAdministrator), IsCollector(m_bIsCollector), IsLabWorker(m_bIsLabWorker){
    m_bIsAdministrator = anUserRole.IsAdministrator;
    m_bIsCollector = anUserRole.IsCollector;
    m_bIsLabWorker = anUserRole.IsLabWorker;
}


/*************************************************************************
【函数名称】       ～UserRole
【函数功能】       析构函数
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
UserRole::~UserRole(){
    
}

/*************************************************************************
【函数名称】       赋值运算符
【函数功能】        赋值运算符
【参数】           UserRole
【返回值】         UserRole
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
UserRole& UserRole::operator=(const class UserRole& anUserRole){
    m_bIsAdministrator = anUserRole.IsAdministrator;
    m_bIsCollector = anUserRole.IsCollector;
    m_bIsLabWorker = anUserRole.IsLabWorker;
    return (*this);
}

/*************************************************************************
【函数名称】       AddAdministrator
【函数功能】       增加权限
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void UserRole::AddAdministrator(){
    this->m_bIsAdministrator = 1;
}

/*************************************************************************
【函数名称】       AddCollector
【函数功能】       增加权限
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void UserRole::AddCollector(){
    this->m_bIsCollector = 1;
}

/*************************************************************************
【函数名称】       AddLabWorker
【函数功能】       增加权限
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void UserRole::AddLabWorker(){
    this->m_bIsLabWorker = 1;
}

/*************************************************************************
【函数名称】       DeleteAdministrator
【函数功能】       删除权限
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void UserRole::DeleteAdministrator(){
    this->m_bIsAdministrator = 0;
}

/*************************************************************************
【函数名称】       DeleteCollector
【函数功能】       删除权限
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void UserRole::DeleteCollector(){
    this->m_bIsCollector = 0;
}

/*************************************************************************
【函数名称】       DeleteLabWorker
【函数功能】       删除权限
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void UserRole::DeleteLabWorker(){
    this->m_bIsLabWorker = 0;
}

/*************************************************************************
【函数名称】       流输出运算符
【函数功能】       流输出
【参数】           流，UserRole对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
ostream& operator<<(ostream& Stream, const class UserRole& Source){
    Stream  << Source.m_bIsAdministrator << endl << Source.m_bIsCollector << endl << Source.m_bIsLabWorker;
    return Stream;
}

/*************************************************************************
【函数名称】       流输入运算符
【函数功能】       流输入
【参数】           流，UserRole对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
istream& operator>>(istream& Stream, class UserRole& Source){
    Stream >> Source.m_bIsAdministrator >> Source.m_bIsCollector >> Source.m_bIsLabWorker;
    return Stream;
}
