/*************************************************************************
【文件名】                      TestResult.hpp
【功能模块和目的】
                  检测结果类头文件。本文件中仅包含TestResult类，用以实现TestResult的管理。
                  TestResult类的产生时考虑到User类和Tube类的公共部分：核酸结果既是User的核酸情况，也是试管的阴阳状态。
                  这一类高度可重用，符合通用类的要求。
 
【开发者及日期】            Jason Zhao 2022/07/18
【更改记录】                   暂无
*************************************************************************/

#ifndef TestResult_hpp
#define TestResult_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include "DateTime.hpp"
using namespace std;



/*************************************************************************
【类名】             TestResult
【功能】             实现检测结果的管理。
            TestResult类的产生时考虑到User类和Tube类的公共部分：核酸结果既是User的核酸情况，也是试管的阴阳状态。
            这一类高度可重用，符合通用类的要求。
【接口说明】
 修改值成员
     修改是否有记录：ChangeHistoryState
     修改采集时间：AddCollectTime
     修改录入时间：AddLogTime
     修改核酸结果：AddResult
 读取与显示
     流运算符：  <<,>>
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class TestResult{
public:
    //构造函数/析构函数
    TestResult();
    TestResult(const TestResult& Source);
    TestResult(DateTime CollectTime, DateTime LogTime, bool Result);
    ~TestResult();
    
    //修改值成员
    //这看上去像是给外界修改信息的“机会”，但是在User和Tube类里，TestResult都是私有成员，无法直接外部改变值
    void ChangeHistoryState();
    void AddCollectTime(DateTime aDateTime);
    void AddLogTime(DateTime aDateTime);
    void AddResult(bool aResult);
    
    //重载运算符
    friend ostream& operator<<(ostream& Stream, const TestResult& Source);
    friend istream& operator>>(istream& Stream, TestResult& Source);
    TestResult& operator=(const TestResult& Source);
    
    //更新DateTime的星期
    void UpdateTodayType();
    
    //常引用
    const bool& NoHistoryRecord;
    const DateTime& CollectTime;
    const DateTime& LogTime;
    const bool& Result;
    
protected:
    //如果没有历史记录，则显示为1；若有历史记录，则显示为0
    bool m_bNoHistoryRecord;
    DateTime m_CollectTime;
    DateTime m_LogTime;
    //阴性是0，阳性是1
    bool m_bResult;
    
};
#endif /* TestResult_hpp */
