/*************************************************************************
【文件名】                      User.cpp
【功能模块和目的】
                  成员类实现文件。
                  1. User 和 Administrator两个类以及User 和 Tube 两个类之间，由于需要进行权限“签名” （即只有Collector/LabWorker能够创建或修改Tube，User被指定为Administrator后需要升级为Administrator)，所以需要相互include。我们在cpp文件中进行include避免编译错误。
 
                  2. 公有继承于UserBase，管理User成员的个人信息（包括身份证号码/姓名/密码/核酸记录）。
 
                  3. Collector/LabWorker成员也是属于User，但是类内部有二者专属的函数（即函数会验证User的身份， 只有当User是Collector/LabWorker，才能执行，否则报错）。Admininstrator继承于User类。
 
                  4. 从功能上来讲，Administrator需要修改其它User对象的角色，LabWorker需要修改其它User对象的 核酸信息，都会触碰到其它对象的私有信息。在本类中，考虑到只有对象自身能够修改自身信息，我们使Administrator/LabWorker只将更新的信息存储到静态向量 m_AllInfo中， 每一个用户登陆、 以及在任何操作之后， 用户都会从m_AllInfo中更新自己的信息。
 
【开发者及日期】            Jason Zhao 2022/07/18
【更改记录】                   暂无
*************************************************************************/


#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include "User.hpp"
#include "Administrator.hpp"
using namespace std;

unsigned int User::m_AdminCount = 0;
vector<shared_ptr<User>> User::m_All = {};
vector<shared_ptr<User::InfoRecord>> User::m_AllInfo = {};

NoCollectorAccess::NoCollectorAccess() : invalid_argument("This User does not have Collector Access"){
}

NoLabWorkerAccess::NoLabWorkerAccess() : invalid_argument("This User does not have Lab Worker Access"){
}

NoAdminAccess::NoAdminAccess() : invalid_argument("This User is not Administrator"){
}

NoAdminCreated::NoAdminCreated() : invalid_argument("No Administrator has been created in the Loading File, please initialize the Admin in the file first"){
}

ExceptionOnlyOneAdminLeft::ExceptionOnlyOneAdminLeft() : invalid_argument("This is the last administrator, so you cannot delete yourself"){
}


User::InfoRecord::InfoRecord(string anUserId){
    UserId = anUserId;
    m_AllInfo.push_back(shared_ptr<User::InfoRecord>(this));
}

/*************************************************************************
【函数名称】       流输出运算符
【函数功能】       流输出
【参数】           流，InfoRecord对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
ostream& operator<<(ostream& Stream, const User::InfoRecord& anInfoRecord){
    Stream << anInfoRecord.UserId << endl << anInfoRecord.LatestUserRole << endl << anInfoRecord.UserTestResult;
    return Stream;
}


/*************************************************************************
【函数名称】       流输入运算符
【函数功能】       流输入
【参数】           流，InfoRecord对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
istream& operator>>(istream& Stream, User::InfoRecord& anInfoRecord){
    Stream >> anInfoRecord.UserId >> anInfoRecord.LatestUserRole >> anInfoRecord.UserTestResult;
    return Stream;
}

User::User(string UserId, string UserName, string PlainPassword):UserBase(UserId, UserName, PlainPassword),AdminCount(m_AdminCount),MyUserRole(m_UserRole), LatestResult(m_LatestResult) {
    AlreadyRegistered(UserId);
    m_All.push_back(shared_ptr<User>(this));
    new InfoRecord(UserId);
}

User::User(string UserId, string UserName, CipherText Password):UserBase(UserId, UserName, Password), AdminCount(m_AdminCount),MyUserRole(m_UserRole), LatestResult(m_LatestResult){
    AlreadyRegistered(UserId);
    m_All.push_back(shared_ptr<User>(this));
    new InfoRecord(UserId);
}

User::User(string UserId, string UserName, string PlainPassword, bool IsAdmin, bool IsColl, bool IsLabW): AdminCount(m_AdminCount),MyUserRole(m_UserRole),  LatestResult(m_LatestResult), UserBase(UserId,UserName, PlainPassword), m_UserRole(IsAdmin,IsColl,IsLabW) {
    AlreadyRegistered(UserId);
    m_All.push_back(shared_ptr<User>(this));
    new InfoRecord(UserId);
}

//拷贝构造函数：仅限于给Administrator签名使用，不会被加入到m_All的数据库中
User::User(const User& anUser):UserBase(anUser.UserId, "UserName", "Password"), AdminCount(m_AdminCount),MyUserRole(m_UserRole), LatestResult(m_LatestResult){
    m_UserRole.AddAdministrator();
    if(anUser.MyUserRole.IsCollector){
        m_UserRole.AddCollector();
    }
    if(anUser.MyUserRole.IsLabWorker){
        m_UserRole.AddLabWorker();
    }
}

/*************************************************************************
【函数名称】       ～User
【函数功能】       析构函数
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
User::~User(){
}



/*************************************************************************
【函数名称】       IsAdministrator
【函数功能】       是否是管理员
【参数】           无
【返回值】         bool，是否是管理员
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool User::IsAdministrator() const{
    return false;
}

/*************************************************************************
【函数名称】       DeleteSelf
【函数功能】       注销账号
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void User::DeleteSelf(){
    auto Finder = [&](shared_ptr<User> ptr)->bool{return (ptr->m_sUserId == this->m_sUserId);};
    auto it = find_if(m_All.begin(), m_All.end(), Finder);
    if (((*it)->IsAdministrator()) && (AdminCount == 1)) {
        throw ExceptionOnlyOneAdminLeft();
    }
    m_All.erase(it);
}

//void User::AdminDeleteSelf(){
//    auto Finder = [=](shared_ptr<User> ptr)->bool{return (ptr->m_sUserId == this->m_sUserId);};
//    auto it = find_if(m_All.begin(), m_All.end(), Finder);
//    if (!(*it)->IsAdministrator()) {
//        throw ThisIsNotAdmin();
//    }
//    m_All.erase(it);
//}

/*************************************************************************
【函数名称】       AlreadyRegistered
【函数功能】       检测用户ID是否注册
【参数】           用户ID
【返回值】         bool，是否注册
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool User::AlreadyRegistered(const string UserId){
    auto Finder = [&UserId](shared_ptr<User> ptr)->bool{return (ptr->m_sUserId == UserId);};
    //To find out the first user specified by name
    auto it = find_if(m_All.begin(), m_All.end(), Finder);
    if (it == m_All.end()) {
        return false;
    }
    
    //由于User的Id、Password没有常引用，
    //所以如果有User晋升为管理员或者有管理员注销为普通User，
    //在管理员生成或者注销的过程中可能会有一个阶段处于User对象和Administrator对象共存，
    //故而在此进行一些“不自然”的“特赦”
    else if(((*it)->IsAdministrator()) || ((*it)->MyUserRole.IsAdministrator)){
        return false;
    }
    else{
        throw ExceptionUserAlreadyRegistered();
    }
}


/*************************************************************************
【函数名称】       Verify
【函数功能】       验证登陆信息
【参数】           用户ID、姓名、密码
【返回值】         shared_ptr<User> 用户指针
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
shared_ptr<User> User::Verify(const string UserId, const string UserName, const string PlainPassword){
    auto Finder = [&UserId](shared_ptr<User> ptr)->bool{return (ptr->m_sUserId == UserId);};
    auto it = find_if(m_All.begin(), m_All.end(), Finder);
    if (it == m_All.end()) {
        throw ExceptionNoUser();
    }
    //found，but wrong password, throw WRONG PASSWORD exception
    else if (((*it)->m_Password != PlainPassword) || ((*it)->m_sUserName != UserName)){
        throw ExceptionWrongNameOrPassword();
    }
    else {
        return *it;
    }
}


/*************************************************************************
【函数名称】       IsRegistered
【函数功能】       寻找用户是否注册，并且返回用户最新的信息
【参数】           用户ID
【返回值】         shared_ptr<User::InfoRecord> 用户的最新信息
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
shared_ptr<User::InfoRecord> User::IsRegistered(const string UserId){
    auto FinderInfo = [&](shared_ptr<User::InfoRecord> ptr)->bool{return (ptr->UserId == UserId);};
    //To find out the first user specified by name
    auto itInfo = find_if(User::m_AllInfo.begin(), User::m_AllInfo.end(), FinderInfo);
    if (itInfo == User::m_AllInfo.end()) {
        throw ExceptionNoUser();
    }
    return  *itInfo;
}

//
/*************************************************************************
【函数名称】       AddRole
【函数功能】       增加权限，不用检查用户之前是不是该角色，只需要为该用户加上这一角色就好
【参数】           用户ID，删除的角色（UT：UserType，枚举类型）
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void User::AddRole(string UserId, UT NewUserType){
    auto it = IsRegistered(UserId);
    switch (NewUserType) {
        case UT::ADMIN :
            it->LatestUserRole.AddAdministrator();
            break;
        case UT::COLLECTOR :
            it->LatestUserRole.AddCollector();
            break;
        case UT::LABWORKER :
            it->LatestUserRole.AddLabWorker();
            break;
    }
}


//
/*************************************************************************
【函数名称】       DeleteRole
【函数功能】       删除权限，不用检查用户之前是不是该角色，只需要为该用户删去这一角色就好
【参数】           用户ID，删除的角色（UT：UserType，枚举类型）
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void User::DeleteRole(string UserId, UT NewUserType){
    auto it = IsRegistered(UserId);
    switch (NewUserType) {
        case UT::ADMIN :
            it->LatestUserRole.DeleteAdministrator();
            break;
        case UT::COLLECTOR :
            it->LatestUserRole.DeleteCollector();
            break;
        case UT::LABWORKER :
            it->LatestUserRole.DeleteLabWorker();
            break;
    }
}

/*************************************************************************
【函数名称】       AddResultToUser
【函数功能】       LabWorker在m_AllInfo中修改最新的核酸信息
【参数】           用户ID，核酸结果（bool）
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void User::AddResultToUser(string UserId, TestResult aTestResult){
    if(m_UserRole.IsLabWorker){
        auto it = IsRegistered(UserId);
        it->UserTestResult = aTestResult;
    }
    else{
        throw NoLabWorkerAccess();
    }
}

/*************************************************************************
【函数名称】       AddResult
【函数功能】       LabWorker通过Tube的静态函数LogTestResult同时为试管增添结果
            以及在m_AllInfo中修改最新的核酸信息
【参数】           试管ID，核酸结果（bool)
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void User::AddResult(string aTubeId, bool aResult){
    //需要传入User指针给Tube类进行Collector身份验证
    if(!MyUserRole.IsLabWorker){
        throw NoLabWorkerAccess();
    }
    shared_ptr<Tube> Tmp = Tube::LogTestResult(*this, aTubeId, aResult);
    for(auto Member : Tmp->TesterId){
        AddResultToUser(Member, TestResult(Tmp->TubeTestResult));
    }
}

/*************************************************************************
【函数名称】       UpdateResult
【函数功能】       User从m_AllInfo中更新自己最新的权限以及核酸结果
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void User::UpdateResult(){
    auto it = IsRegistered(m_sUserId);
    this->m_LatestResult = it->UserTestResult;
    this->m_UserRole = it->LatestUserRole;
    if(this->MyUserRole.IsAdministrator && (!this->IsAdministrator())){
        new Administrator((*this), this->m_sUserId, this->m_sUserName, this->m_Password, this->MyUserRole.IsCollector, this->MyUserRole.IsLabWorker);
    }
}

// 输入输出流
/*************************************************************************
【函数名称】       流输出运算符
【函数功能】       流输出
【参数】           流，User对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
ostream& operator<<(ostream& Stream, const User& anUser){
    Stream << anUser.m_sUserId << endl << anUser.m_sUserName<< endl << anUser.m_Password << endl << anUser.m_UserRole << endl << anUser.m_LatestResult;
    return Stream;
}

/*************************************************************************
【函数名称】       流输入运算符
【函数功能】       流输入
【参数】           流，User对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
istream& operator>>(istream& Stream, User& anUser){
    Stream >> anUser.m_sUserId >> anUser.m_sUserName >> anUser.m_Password >> anUser.m_UserRole >> anUser.m_LatestResult;
    return Stream;
}



//读取与存储函数
/*************************************************************************
【函数名称】        SaveToFile
【函数功能】       向文件写入
【参数】           文件名（string）
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void User::SaveToFile(const string& FileName){
    ofstream File(FileName);
    //如果无法打开
    if (!File.is_open()) {
        throw invalid_argument("Can't open/Create for saving, File : " + FileName);
    }
    auto Saver1 = [&File](shared_ptr<User> Ptr){File << *Ptr << endl;};
    File << m_All.size() << endl;
    for_each(m_All.begin(), m_All.end(),Saver1);
    auto Saver2 = [&File](shared_ptr<User::InfoRecord> Ptr){File << *Ptr << endl;};
    for_each(m_AllInfo.begin(), m_AllInfo.end(),Saver2);
    File.close();
}

/*************************************************************************
【函数名称】       LoadFromFile
【函数功能】       从文件读取
【参数】           文件名（string）
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void User::LoadFromFile(const string& FileName){
    ifstream File(FileName);
    if (!File.is_open()) {
        ofstream NewFile(FileName);
        NewFile << 0 << endl;
        NewFile.close();
        File.open(FileName);
        if (!NewFile.is_open()) {
            throw invalid_argument("Can't open/create for loading, file: " + FileName);
        }
    }
    unsigned long UserCount;
    File >> UserCount;
    File.get();
    
    //载入m_All
    m_All.clear();
    for (unsigned long i = 0; i < UserCount; i++) {
        new User{string{""},string{""}, CipherText{"123456"}};
        File >> *(*(m_All.end() - 1));
        if ((*(m_All.end()-1))->MyUserRole.IsAdministrator){
            m_AdminCount++;
            shared_ptr<User> Tmp = *(m_All.end()-1);
            new Administrator(Tmp, Tmp->m_sUserId, Tmp->m_sUserName, Tmp->m_Password, Tmp->m_UserRole.IsCollector, Tmp->m_UserRole.IsLabWorker);
        }
    }
    if(m_AdminCount == 0){
        throw NoAdminCreated();
    }
    
    //载入m_AllInfo
    m_AllInfo.clear();
    for (unsigned long i = 0; i < UserCount; i++) {
        new User::InfoRecord(string{""});
        File >> *(*(m_AllInfo.end() - 1));
    }
    
    //更新星期几信息
    for(auto member:m_All){
        (*member).m_LatestResult.UpdateTodayType();
    }
    for(auto member:m_AllInfo){
        (*member).UserTestResult.UpdateTodayType();
    }
}

