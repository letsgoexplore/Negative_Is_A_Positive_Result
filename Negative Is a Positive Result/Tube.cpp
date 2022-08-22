/*************************************************************************
【文件名】                      Tube.cpp
【功能模块和目的】
                  试管类实现文件。继承于TestResult。本文件中包含Tube类以及几个异常类，用以实现Tube的数据管理，包括试管的ID、测试者ID、检测与录入时间。
 
【开发者及日期】            Jason Zhao 2022/07/20
【更改记录】                   暂无
*************************************************************************/

#include "Tube.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <fstream>
#include <algorithm>
#include "DateTime.hpp"
#include "TestResult.hpp"
#include "User.hpp"
using namespace std;

const string Tube::m_sProduceDateTime = "20220101";
vector<shared_ptr<Tube>> Tube::m_All = {};

ExceptionInvalidUserId::ExceptionInvalidUserId() : invalid_argument("The Input of the UserId does not match the size of 18"){
}

ExceptionNoTubeId::ExceptionNoTubeId() : invalid_argument("No Such Tube Created"){
}

ExceptionNoUserInTube::ExceptionNoUserInTube() : invalid_argument("The new tube has no User adding under it"){
}


/*************************************************************************
【函数名称】       Tube
【函数功能】       构造函数
【参数】           拥有Collector权限的User
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Tube::Tube(const User& anUser): m_TubeTestResult(DateTime::Now(), DateTime(), false), TubeTestResult(m_TubeTestResult), TubeId(m_sTubeId), TesterId(m_TesterId){
    if(!anUser.MyUserRole.IsCollector){
        throw NoCollectorAccess();
    }
    this->m_TubeTestResult.UpdateTodayType();
    unsigned int Counter = 0;
    string Tmp;
    while(true){
        Tmp.clear();
        cout<<"Adding New Tester?(Y/N)"<<endl;
        cin>>Tmp;
        //检查输入是否是“Y”
        if((Tmp == "Y")||(Tmp == "y")){
            string TmpTesterId{};
            cout<<"Please Input Tester's Id:";
            cin>>TmpTesterId;
            if(Tmp.size()!=18){
                throw ExceptionInvalidUserId();
            }
            if(!User::AlreadyRegistered(Tmp)){
                throw ExceptionNoUser();
            }
            m_TesterId.push_back(TmpTesterId);
            Counter += 1;
        }
        else{
            //如果一个User都没有添加到试管的名下，就会报错
            if(Counter == 0){
                throw ExceptionNoUserInTube();
            }
            else{
                break;
            }
        }
        
    }
    
    //由于要从0到999999构成TubeId的后六位，所以要进行截取（如果超过1000000）或者补零（如果小于100000）
    unsigned long Number = m_All.size();
    //先把数值转化为字符串，就可以通过.size()得知数值有多少位
    unsigned long NumberLength = to_string(Number).size();
    string TubeId;
    if(NumberLength > 6){
        Number = Number %1000000;
        TubeId = m_sProduceDateTime + to_string(Number);
    }
    else{
        string Tmp;
        Tmp = "";
        for(int i = 0; i < 6 - NumberLength; i++){
            Tmp = Tmp + "0";
        }
        TubeId = m_sProduceDateTime + Tmp + to_string(Number);
    }
    m_sTubeId = TubeId;
    m_All.push_back(shared_ptr<Tube>(this));
    cout<< m_sTubeId << "created" << endl;
}


/*************************************************************************
【函数名称】       Tube
【函数功能】       构造函数
【参数】           拥有Collector权限的User（shared_ptr<User>，考虑到方便性）
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Tube::Tube(const shared_ptr<User> anUser): m_TubeTestResult(DateTime::Now(), DateTime(), false), TubeTestResult(m_TubeTestResult), TubeId(m_sTubeId), TesterId(m_TesterId){
    if(!anUser->MyUserRole.IsCollector){
        throw NoCollectorAccess();
    }
    this->m_TubeTestResult.UpdateTodayType();
    unsigned int Counter = 0;
    string Tmp;
    while(true){
        cout<<"Adding New Tester?(Y/N)"<<endl;
        cin>>Tmp;
        //检查输入是否是“Y”
        if((Tmp == "Y")||(Tmp == "y")){
            cout<<"Please Input Tester's Id:";
            cin>>Tmp;
            if(Tmp.size()!=18){
                throw ExceptionInvalidUserId();
            }
            m_TesterId.push_back(Tmp);
            Counter += 1;
        }
        else{
            //如果一个User都没有添加到试管的名下，就会报错
            if(Counter == 0){
                throw ExceptionNoUserInTube();
            }
            else{
                break;
            }
        }
    }
    
    //由于要从0到999999构成TubeId的后六位，所以要进行截取（如果超过1000000）或者补零（如果小于100000）
    unsigned long Number = m_All.size();
    //先把数值转化为字符串，就可以通过.size()得知数值有多少位
    unsigned long NumberLength = to_string(Number).size();
    string TubeId;
    if(NumberLength > 6){
        Number = Number %1000000;
        TubeId = m_sProduceDateTime + to_string(Number);
    }
    else{
        string Tmp;
        Tmp = "";
        for(int i = 0; i < 6 - NumberLength; i++){
            Tmp = Tmp + "0";
        }
        TubeId = m_sProduceDateTime + Tmp + to_string(Number);
    }
    m_sTubeId = TubeId;
    m_All.push_back(shared_ptr<Tube>(this));
    cout<< m_sTubeId << "created" << endl;
}
    
/*************************************************************************
【函数名称】       Tube
【函数功能】       构造函数
【参数】           拥有Collector权限的User，有试管用户的vector<string> TesterId
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Tube::Tube(const User& anUser, vector<string> TesterId):m_TubeTestResult(DateTime::Now(), DateTime(), false),TubeTestResult(m_TubeTestResult),TubeId(m_sTubeId),TesterId(m_TesterId){
    if(!anUser.MyUserRole.IsCollector){
        throw NoCollectorAccess();
    }
    this->m_TubeTestResult.UpdateTodayType();
    m_TesterId = TesterId;
    //由于要从0到999999构成TubeId的后六位，所以要进行截取（如果超过1000000）或者补零（如果小于100000）
    unsigned long Number = m_All.size();
    //先把数值转化为字符串，就可以通过.size()得知数值有多少位
    unsigned long NumberLength = to_string(Number).size();
    string TubeId;
    if(NumberLength > 6){
        Number = Number %1000000;
        TubeId = m_sProduceDateTime + to_string(Number);
    }
    else{
        string Tmp;
        Tmp = "";
        for(int i = 0; i < 6 - NumberLength; i++){
            Tmp = Tmp + "0";
        }
        TubeId = m_sProduceDateTime + Tmp + to_string(Number);
    }
    m_sTubeId = TubeId;
    m_All.push_back(shared_ptr<Tube>(this));
}

//私有的构造函数，仅限于LoadFromFile中调用构造
Tube::Tube(vector<string> TesterId): m_TubeTestResult(DateTime::Now(), DateTime(), false),TubeTestResult(m_TubeTestResult),TubeId(m_sTubeId),TesterId(m_TesterId){
    m_TesterId = TesterId;
    //由于要从0到999999构成TubeId的后六位，所以要进行截取（如果超过1000000）或者补零（如果小于100000）
    unsigned long Number = m_All.size();
    //先把数值转化为字符串，就可以通过.size()得知数值有多少位
    unsigned long NumberLength = to_string(Number).size();
    string TubeId;
    if(NumberLength > 6){
        Number = Number %1000000;
        TubeId = m_sProduceDateTime + to_string(Number);
    }
    else{
        string Tmp;
        Tmp = "";
        for(int i = 0; i < 6 - NumberLength; i++){
            Tmp = Tmp + "0";
        }
        TubeId = m_sProduceDateTime + Tmp + to_string(Number);
    }
    m_sTubeId = TubeId;
    m_All.push_back(shared_ptr<Tube>(this));
    cout<< m_sTubeId << "created" << endl;
}

/*************************************************************************
【函数名称】       ～Tube
【函数功能】       析构函数
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Tube::~Tube(){
//    auto Func = [&](string* ptr)->void{delete ptr;};
//    for_each(Tube::m_All.begin(), Tube::m_All.end(), Func);
    m_TesterId.clear();
    
    
}


shared_ptr<Tube> Tube::LogTestResult(User& anUser, string aTubeId, bool aTestResult){
    if(!anUser.MyUserRole.IsLabWorker){
        throw NoLabWorkerAccess();
    }
    auto Finder = [=](shared_ptr<Tube> ptr)->bool{return (ptr->TubeId == aTubeId);};
    auto it = find_if(Tube::m_All.begin(), Tube::m_All.end(), Finder);
    if (it == Tube::m_All.end()) {
        throw ExceptionNoTubeId();
    }
    else{
        (*it)->m_TubeTestResult.AddLogTime(DateTime::Now());
        (*it)->m_TubeTestResult.UpdateTodayType();
        (*it)->m_TubeTestResult.AddResult(aTestResult);
    }
    return (*it);
}


/*************************************************************************
【函数名称】       流输出运算符
【函数功能】       流输出
【参数】           流，Date对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
ostream& operator<<(ostream& Stream, const Tube& Source){
    Stream << Source.m_sTubeId << endl << Source.m_TubeTestResult << endl << Source.m_TesterId.size() << endl;
    for(auto member:Source.m_TesterId){
        Stream << member;
    }
    return Stream;
}


/*************************************************************************
【函数名称】       流输入运算符
【函数功能】       流输入
【参数】           流，Date对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
istream& operator>>(istream& Stream, Tube& Source){
    unsigned long TesterIdSize;
    Stream >> Source.m_sTubeId >> Source.m_TubeTestResult >> TesterIdSize;
    for(int i = 0; i < TesterIdSize; i++){
        string Tmp;
        Stream >> Tmp;
        Source.m_TesterId.push_back(Tmp);
    }
    return Stream;
}

/*************************************************************************
【函数名称】       LoadFromFile SaveToFile
【函数功能】       从文件读取 向文件写入
【参数】           文件名（string）
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Tube::SaveToFile(const string& FileName){
    ofstream File(FileName);
    if (!File.is_open()) {
        throw invalid_argument("Can't open/Create for saving, File : " + FileName);
    }
    auto Saver = [&File](shared_ptr<Tube> Ptr){File << *Ptr << endl;};
    File << m_All.size() << endl;
    for_each(m_All.begin(), m_All.end(),Saver);
    File.close();
}

/*************************************************************************
【函数名称】       LoadFromFile SaveToFile
【函数功能】       从文件读取 向文件写入
【参数】           文件名（string）
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Tube::LoadFromFile(const string& FileName){
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
    unsigned long TubeCount;
    File >> TubeCount;
    File.get();
    //载入m_All
    m_All.clear();
    for (unsigned long i = 0; i < TubeCount; i++) {
        new Tube(vector<string>{});
        File >> *(*(m_All.end() - 1));
    }
}
