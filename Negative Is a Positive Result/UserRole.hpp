/*************************************************************************
【文件名】                      UserRole.hpp
【功能模块和目的】
                  成员权限类头文件。本文件中仅包含UserRole类，用以实现User权限的管理。本身可以设计为内嵌类，
                  但是考虑到User类的可重用性，以及代码的美观性，最终将UserRole单独拿出来形成独立的类。
 
【开发者及日期】            Jason Zhao 2022/07/18
【更改记录】                   暂无
*************************************************************************/

#ifndef UserRole_hpp
#define UserRole_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

/*************************************************************************
【类名】             UserRole
【功能】             实现User权限的管理。本身可以设计为内嵌类，
            但是考虑到User类的可重用性，以及代码的美观性，最终将UserRole单独拿出来形成独立的类。
【接口说明】
 增加管理员：AddAdministrator
 退出管理员：DeleteAdministrator
 增加Collector：AddCollector
 剥夺Collector权限：DeleteCollector
 增加LabWorker： AddLabWorker
 剥夺LabWorker权限：DeleteLabWorker
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class UserRole{
public:
    UserRole();
    UserRole(bool IsAdministrator, bool IsCollector, bool IsLabWorker);
    UserRole(const UserRole& anUserRole);
    ~UserRole();
    UserRole& operator=(const UserRole& anUserRole);
    
    friend ostream& operator<<(ostream& Stream, const UserRole& Source);
    friend istream& operator>>(istream& Stream, UserRole& Source);
    
    void AddAdministrator();
    void AddCollector();
    void AddLabWorker();
    void DeleteAdministrator();
    void DeleteCollector();
    void DeleteLabWorker();
    const bool& IsAdministrator;
    const bool& IsCollector;
    const bool& IsLabWorker;
private:
    bool m_bIsAdministrator;
    bool m_bIsCollector;
    bool m_bIsLabWorker;
};
#endif /* UserRole_hpp */
