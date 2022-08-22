/*************************************************************************
【文件名】                      TestResult.cpp
【功能模块和目的】
                  检测结果类实现文件。本文件中仅包含TestResult类，用以实现TestResult的管理。
                  这一类高度可重用，符合通用类的要求。
 
【开发者及日期】            Jason Zhao 2022/07/18
【更改记录】                   暂无
*************************************************************************/

#include "TestResult.hpp"
#include <iostream>
using namespace std;

/*************************************************************************
【函数名称】       TestResult
【函数功能】       默认构造函数
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
TestResult::TestResult() :NoHistoryRecord(m_bNoHistoryRecord),CollectTime(m_CollectTime),LogTime(m_LogTime),Result(m_bResult){
    m_bNoHistoryRecord = 1;
    m_CollectTime = DateTime();
    m_CollectTime.UpdateTodayType();//防止星期几信息没有更新
    m_LogTime = DateTime();
    m_LogTime.UpdateTodayType();//防止星期几信息没有更新
    m_bResult = 0;
}

/*************************************************************************
【函数名称】       TestResult
【函数功能】       值输入构造函数
【参数】           采集时间，录入时间，核酸结果
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
TestResult::TestResult(DateTime CollectTime, DateTime LogTime, bool Result) :NoHistoryRecord(m_bNoHistoryRecord),CollectTime(m_CollectTime),LogTime(m_LogTime),Result(m_bResult){
    m_CollectTime = CollectTime;
    m_LogTime = LogTime;
    m_bResult = Result;
    //防止星期几信息没有更新
    m_CollectTime.UpdateTodayType();
    m_LogTime.UpdateTodayType();
    if((CollectTime!=DateTime()) || (LogTime!=DateTime())){
        m_bNoHistoryRecord = 0;
    }
    else{
        m_bNoHistoryRecord = 1;
    }
}

/*************************************************************************
【函数名称】  TestResult
【函数功能】       拷贝构造函数
【参数】           TestResult类型对象
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
TestResult::TestResult(const TestResult& Source) :NoHistoryRecord(m_bNoHistoryRecord),CollectTime(m_CollectTime), LogTime(m_LogTime),Result(m_bResult){
    m_bNoHistoryRecord = Source.NoHistoryRecord;
    m_CollectTime = Source.CollectTime;
    m_LogTime = Source.LogTime;
    m_bResult = Source.Result;
    //防止星期几信息没有更新
    m_CollectTime.UpdateTodayType();
    m_LogTime.UpdateTodayType();
    
}

/*************************************************************************
【函数名称】      ~TestResult
【函数功能】       析构函数
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
TestResult::~TestResult(){
}



/*************************************************************************
【函数名称】       ChangeHistoryState
【函数功能】       修改HistoryRecordt状态
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void TestResult::ChangeHistoryState(){
    this->m_bNoHistoryRecord = 0;
}


/*************************************************************************
【函数名称】       AddCollectTime
【函数功能】       修改采集时间状态
【参数】           DateTime 对象
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void TestResult::AddCollectTime(DateTime aDateTime){
    this->m_CollectTime = aDateTime;
    
}

/*************************************************************************
【函数名称】       AddLogTime
【函数功能】       修改录入时间状态
【参数】           DateTime 对象
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void TestResult::AddLogTime(DateTime aDateTime){
    this->m_LogTime = aDateTime;
}


/*************************************************************************
【函数名称】       AddResult
【函数功能】       添加结果状态
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void TestResult::AddResult(bool aResult){
    this->m_bResult = aResult;
}

/*************************************************************************
【函数名称】       流输出运算符
【函数功能】       流输出
【参数】           流，TestResult对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
ostream& operator<<(ostream& Stream, const TestResult& Source){
    Stream  << Source.NoHistoryRecord << endl << Source.m_CollectTime << endl<< Source.m_LogTime << endl << Source.m_bResult;
    return Stream;
}

/*************************************************************************
【函数名称】       流输出运算符
【函数功能】       流输出
【参数】           流，TestResult对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
istream& operator>>(istream& Stream, TestResult& Source){
    Stream >> Source.m_bNoHistoryRecord >> Source.m_CollectTime >> Source.m_LogTime >> Source.m_bResult;
    return Stream;
}


/*************************************************************************
【函数名称】       赋值运算符
【函数功能】       输出
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
TestResult& TestResult::operator=(const TestResult& Source){
    if(!(Source.NoHistoryRecord)){
        this->m_bNoHistoryRecord = 0;
        this->m_CollectTime = Source.m_CollectTime;
        this->m_LogTime = Source.m_LogTime;
        this->m_bResult = Source.m_bResult;
    }
    return (*this);
}


/*************************************************************************
【函数名称】      UpdateTodayType
【函数功能】      更新DateTime对应的日期
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void TestResult::UpdateTodayType(){
    m_CollectTime.UpdateTodayType();
    m_LogTime.UpdateTodayType();
}
