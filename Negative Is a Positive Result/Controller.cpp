/*************************************************************************
【文件名】                      Controller.cpp
【功能模块和目的】
                  控制器类实现文件。
                  本文件中包含Controller类，构成半通用类，实现界面和功能的解耦。此外还有各种正常和异常结果构成的ControlerRet枚举类。
                  
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
【开发者及日期】            Jason Zhao 2022/07/22
【更改记录】                   暂无
*************************************************************************/

#include "Controller.hpp"

/*************************************************************************
【函数名称】       Controller
【函数功能】       值输入构造函数
【参数】           用户信息存储文件，试管信息存储文件
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Controller::Controller(const string& UserFileName, const string& TubeFileName):LoginedUser(m_pLoginedUser){
    m_UsersFileName = UserFileName;
    m_TubesFileName = TubeFileName;
    User::LoadFromFile(m_UsersFileName);
    Tube::LoadFromFile(m_TubesFileName);
}

/*************************************************************************
【函数名称】       ～Controller
【函数功能】       析构函数
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Controller::~Controller(){
    Tube::SaveToFile(m_TubesFileName);
    User::SaveToFile(m_UsersFileName);
}


/*************************************************************************
【函数名称】       Login
【函数功能】       用户登陆
【参数】           ID，用户名，密码（string）
【返回值】         结果类型RES
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
RES Controller::Login(string UserId, string UserName, string Password) {
    try {
        m_pLoginedUser = User::Verify(UserId, UserName, Password);
        //更新最新数据
        m_pLoginedUser->UpdateResult();
    }
    catch(ExceptionNoUser e) {
        return ControlerRet::NO_USER;
    }
    catch(ExceptionWrongNameOrPassword e) {
        return ControlerRet::WRONG_NAMEORPASSWORD;
    }
    return ControlerRet::USER_LOGINED;
}

/*************************************************************************
【函数名称】       Register
【函数功能】       用户注册
【参数】           ID，用户名，密码（string）
【返回值】         结果类型RES
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
RES Controller::Register(string UserId,string UserName,string Password){
    try{
        new User(UserId, UserName, Password);
    }
    catch(ExceptionUserAlreadyRegistered e){
        return ControlerRet::USER_ALREADY_CREATED;
    }
    return ControlerRet::USER_CREATED;
}

/*************************************************************************
【函数名称】       AddAdmin
【函数功能】       授予管理员权限
【参数】           ID
【返回值】         结果类型RES
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
RES Controller::AddAdmin(string UserId){
    if (!m_pLoginedUser->IsAdministrator()) {
        return RES::NO_ADMIN_ACCESS;
    }
    try {
        shared_ptr<Administrator> ptrAdmin = dynamic_pointer_cast<Administrator>(m_pLoginedUser);
        ptrAdmin->AddAdministrator(UserId);
    }
    catch(ExceptionNoUser e){
        return RES::NO_USER;
    }
    return RES::ADD_DONE;
}

/*************************************************************************
【函数名称】       AddCollector
【函数功能】       授予Collector权限
【参数】           ID
【返回值】         结果类型RES
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
RES Controller::AddCollector(string UserId){
    if (!m_pLoginedUser->IsAdministrator()) {
        return RES::NO_ADMIN_ACCESS;
    }
    try {
        shared_ptr<Administrator> ptrAdmin = dynamic_pointer_cast<Administrator>(m_pLoginedUser);
        ptrAdmin->AddRole(UserId, UT::COLLECTOR);
    }
    catch(ExceptionNoUser e){
        return RES::NO_USER;
    }
    return RES::ADD_DONE;
}

/*************************************************************************
【函数名称】       DeleteCollector
【函数功能】       剥夺Collector权限
【参数】           ID
【返回值】         结果类型RES
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
RES Controller::DeleteCollector(string UserId){
    if (!m_pLoginedUser->IsAdministrator()) {
        return RES::NO_ADMIN_ACCESS;
    }
    try {
        shared_ptr<Administrator> ptrAdmin = dynamic_pointer_cast<Administrator>(m_pLoginedUser);
        ptrAdmin->DeleteRole(UserId, UT::COLLECTOR);
    }
    catch(ExceptionNoUser e){
        return RES::NO_USER;
    }
    return RES::DELETE_DONE;
}

/*************************************************************************
【函数名称】       AddLabWorker
【函数功能】       授予LabWorker权限
【参数】           ID
【返回值】         结果类型RES
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
RES Controller::AddLabWorker(string UserId){
    if (!m_pLoginedUser->IsAdministrator()) {
        return RES::NO_ADMIN_ACCESS;
    }
    try {
        shared_ptr<Administrator> ptrAdmin = dynamic_pointer_cast<Administrator>(m_pLoginedUser);
        ptrAdmin->AddRole(UserId, UT::LABWORKER);
    }
    catch(ExceptionNoUser e){
        return RES::NO_USER;
    }
    return RES::ADD_DONE;
}

/*************************************************************************
【函数名称】       DeleteLabWorker
【函数功能】       授予LabWorker权限
【参数】           ID
【返回值】         结果类型RES
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
RES Controller::DeleteLabWorker(string UserId){
    if (!m_pLoginedUser->IsAdministrator()) {
        return RES::NO_ADMIN_ACCESS;
    }
    try {
        shared_ptr<Administrator> ptrAdmin = dynamic_pointer_cast<Administrator>(m_pLoginedUser);
        ptrAdmin->DeleteRole(UserId, UT::LABWORKER);
    }
    catch(ExceptionNoUser e){
        return RES::NO_USER;
    }
    return RES::DELETE_DONE;
}

/*************************************************************************
【函数名称】       QuitAdmin
【函数功能】       放弃Admin权限
【参数】           无
【返回值】         结果类型RES
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
RES Controller::QuitAdmin(){
    if (!m_pLoginedUser->IsAdministrator()) {
        return RES::NO_ADMIN_ACCESS;
    }
    try {
        shared_ptr<Administrator> ptrAdmin = dynamic_pointer_cast<Administrator>(m_pLoginedUser);
        ptrAdmin->QuitAdministrator();
    }
    catch(ExceptionOnlyOneAdminLeft e){
        return RES::ONLY_ONE_ADMIN_LEFT;
    }
    return RES::QUIT_DONE;
}


/*************************************************************************
【函数名称】       NewTube
【函数功能】       Collector创建新试管
【参数】           无
【返回值】           结果类型RES
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
RES Controller::NewTube(){
    if(!m_pLoginedUser->MyUserRole.IsCollector){
        return RES::NO_COLLECTOR_ACCESS;
    }
    try {
        new Tube(m_pLoginedUser);
    }
    catch(ExceptionInvalidUserId e){
        return RES::ERROR_USERID;
    }
    catch(ExceptionNoUser e){
        return RES::NO_USER;
    }
    catch(ExceptionNoUserInTube e){
        return RES::NO_USER_UNDER_TUBE;
    }
    return RES::TUBE_CREATED;
}

/*************************************************************************
【函数名称】       NewResult
【函数功能】       LabWorker添加新结果
【参数】           试管ID，核酸结果
【返回值】           结果类型RES
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
RES Controller::NewResult(string aTubeId, bool aResult){
    if(!m_pLoginedUser->MyUserRole.IsLabWorker){
        return RES::NO_LABWORKER_ACCESS;
    }
    try {
        m_pLoginedUser->AddResult(aTubeId, aResult);
    }
    catch(ExceptionNoTubeId){
        return RES::NO_TUBE_ID;
    }
    return RES::RESULT_ADDED;
}

/*************************************************************************
【函数名称】       UpdateInfo
【函数功能】      用户更新信息
【参数】           无
【返回值】           无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Controller::UpdateInfo(){
    m_pLoginedUser->UpdateResult();
}

