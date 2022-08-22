/*************************************************************************
【文件名】                      Controller.hpp
【功能模块和目的】
                  控制器类头文件。include Administrator，故而能访问其它的各个元素文件。
                  本文件中包含Controller类，构成半通用类，实现界面和功能的解耦。此外还有各种正常和异常结果构成的ControlerRet枚举类。
                  
 
【开发者及日期】            Jason Zhao 2022/07/22
【更改记录】                   暂无
*************************************************************************/

#ifndef Controller_hpp
#define Controller_hpp


#include <stdio.h>
#include <iostream>
#include <string>
#include "Administrator.hpp"
using namespace std;

#define enum_to_string(x) #x
/*************************************************************************
【类名】             ControlerRet
【功能】             枚举类，描述半通用类的各种正常和异常结果
【接口说明】         无
【开发者及日期】     Jason Zhao 2022/07/22
【更改记录】         暂无
*************************************************************************/
enum class ControlerRet{
    NO_USER,
    WRONG_NAMEORPASSWORD,
    ADMIN_LOGINED,
    USER_LOGINED,
    NO_ADMIN_ACCESS,
    USER_CREATED,
    NO_COLLECTOR_ACCESS,
    NO_LABWORKER_ACCESS,
    ERROR_USERID,
    NO_USER_UNDER_TUBE,
    TUBE_CREATED,
    ONLY_ONE_ADMIN_LEFT,
    DELETE_DONE,
    ADD_DONE,
    QUIT_DONE,
    USER_ALREADY_CREATED,
    NO_TUBE_ID,
    RESULT_ADDED
};

//shorter type name
using RES = ControlerRet;

//the return value strings of controler's functions
const string ResStr[] {
    enum_to_string(NO_USER),
    enum_to_string(WRONG_NAMEORPASSWORD),
    enum_to_string(ADMIN_LOGINED),
    enum_to_string(USER_LOGINED),
    enum_to_string(NO_ADMIN_ACCESS),
    enum_to_string(USER_CREATED),
    enum_to_string(NO_COLLECTOR_ACCESS),
    enum_to_string(NO_LABWORKER_ACCESS),
    enum_to_string(ERROR_USERID),
    enum_to_string(NO_USER_UNDER_TUBE),
    enum_to_string(TUBE_CREATED),
    enum_to_string(ONLY_ONE_ADMIN_LEFT),
    enum_to_string(DELETE_DONE),
    enum_to_string(ADD_DONE),
    enum_to_string(QUIT_DONE),
    enum_to_string(USER_ALREADY_CREATED),
    enum_to_string(NO_TUBE_ID),
    enum_to_string(RESULT_ADDED)
};

/*************************************************************************
【类名】             Controller
【功能】             半通用类，实现普通User，Admin，Collector， LabWorker的各项功能，并且返回RES作为结果
【接口说明】
 所有用户
     注册：Login
     登陆：Register
     更新数据： UpdateInfo
 
 Administrator
     增加管理员：AddAdmin
     退出管理员：QuitAdmin
     增加Collector：AddCollector
     剥夺Collector权限：DeleteCollector
     增加LabWorker： AddLabWorker
     剥夺LabWorker权限：DeleteLabWorker
 
 Collector
    创建新试管并且添加User： NewTube
 
 LabWorker
    添加核酸结果：NewResult
 
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class Controller{
public:
    //构造函数、析构函数
    Controller(const string& UserFileName, const string& MessageFileName);
    ~Controller();
    
    //操作函数
    RES Login(string UserId, string UserName, string Password);
    RES Register(string UserId,string UserName,string Password);
    RES AddAdmin(string UserId);
    RES AddCollector(string UserId);
    RES DeleteCollector(string UserId);
    RES AddLabWorker(string UserId);
    RES DeleteLabWorker(string UserId);
    RES QuitAdmin();
    RES NewTube();
    RES NewResult(string aTubeId, bool aResult);
    
    //更新函数
    void UpdateInfo();
    
    //常引用
    const shared_ptr<User>& LoginedUser;
private:
    string m_UsersFileName;
    string m_TubesFileName;
    shared_ptr<User> m_pLoginedUser = nullptr;
};
#endif /* Controller_hpp */
