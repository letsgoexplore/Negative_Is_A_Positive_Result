/*************************************************************************
【文件名】                      Tube.hpp
【功能模块和目的】
                  试管类头文件。继承于TestResult。本文件中包含Tube类以及几个异常类，用以实现Tube的数据管理，包括试管的ID、测试者ID、检测与录入时间。
 
【开发者及日期】            Jason Zhao 2022/07/20
【更改记录】                   暂无
*************************************************************************/


#ifndef Tube_hpp
#define Tube_hpp

#include <stdio.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "TestResult.hpp"
using namespace std;

/*************************************************************************
【类名】             ExceptionInvalidUserId
【功能】             在给试管添加的用户ID无效时抛出异常
【接口说明】         异常函数，无接口
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class ExceptionInvalidUserId:public invalid_argument{
public:
    ExceptionInvalidUserId();
};


/*************************************************************************
【类名】             ExceptionNoUserInTube
【功能】             在试管下没有任何用户时抛出异常
【接口说明】         异常函数，无接口
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class ExceptionNoUserInTube:public invalid_argument{
public:
    ExceptionNoUserInTube();
};


/*************************************************************************
【类名】             ExceptionNoTubeId
【功能】             在遍历所有试管中没有找到时抛出异常
【接口说明】         异常函数，无接口
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class ExceptionNoTubeId:public invalid_argument{
public:
    ExceptionNoTubeId();
};

// 防止两个.h文件相互引用，所以在Tube.hpp中先单独声明User,在Tube.cpp中再include "User.hpp"。仅防止报错
class User;


/*************************************************************************
【类名】             Tube
【功能】             实现Tube的数据管理，包括试管的ID、测试者ID、检测与录入时间。
【接口说明】
 LabWorker
    LabWorker修改函数：LogTestResult
 读取与显示
     流运算符：  <<,>>
     从文件中读取：SaveToFile(const string& FileName) ,  LoadFromFile(const string& FileName
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class Tube{
public:
    //构造函数与析构函数
    //通过内部输入进行构造,需要先对于User的身份进行验证
    Tube(const User& anUser);
    Tube(const shared_ptr<User> anUser);
    //通过外部输入用户ID进行构造，需要先对于User的身份进行验证
    Tube(const User& anUser, vector<string> TesterId);
    Tube(const Tube&) = delete;
    Tube& operator=(const Tube&) = delete;
    ~Tube();
    
    //读取与存储函数
    friend ostream& operator<<(ostream& Stream, const Tube& Source);
    friend istream& operator>>(istream& Stream, Tube& Source);
    static void SaveToFile(const string& FileName);
    static void LoadFromFile(const string& FileName);
    
    //LabWorker修改函数
    static shared_ptr<Tube> LogTestResult(User& anUser, string aTubeId, bool aTestResult);
    
    //常引用
    const string& TubeId;
    const vector<string>& TesterId;
    const TestResult& TubeTestResult;
private:
    //LoadFromFile使用
    Tube(vector<string> TesterId);
    
    //私有成员
    string m_sTubeId;
    const static string m_sProduceDateTime;
    vector<string> m_TesterId;
    TestResult m_TubeTestResult;
    static vector<shared_ptr<Tube>> m_All;
    
};
#endif /* Tube_hpp */
