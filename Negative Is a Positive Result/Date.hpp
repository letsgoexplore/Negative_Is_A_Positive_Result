/*************************************************************************
【文件名】                      Date.hpp
【功能模块和目的】
                  日期类头文件。本文件中仅包含Date类，用以实现Date年月日的管理。
                  本类参照课下小作业以及范老师demo，功能全面、高度可重用，符合通用类的要求。
 
【开发者及日期】            Jintao Fan 2021/08/02
【更改记录】                   暂无
*************************************************************************/

#ifndef Date_hpp
#define Date_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>
using namespace std;

/*************************************************************************
【类名】             Date
【功能】             管理日期信息的数据与功能
【接口说明】         
 成员函数
     SetDate：设置日期数据
     SetYear：设置年份
     SetMonth：设置月份
     SetDay：设置天
     IsLeapYear : 判断是否是闰年
     IsValid： 日期是否有效
 
 静态函数
     InDaysFromAD: 从公元纪年开始到输入Date有多少Tina
     IsLeapYear:输入年份，判断是否是闰年
     IsValid： 输入年月日，判断是否有效
     Today：今天日期
 
 运算符
     -：两个Date对象相减，即两个日期相减，返回中间的天数
     ==, !=,>,>=,<,<= ; 判断运算符
     =：赋值运算符
     ++,--：自运算符
     >>,<<: 流运算符
 
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class Date{
public:
    //构造函数
    Date(unsigned int Year = 2000, unsigned int Month = 1, unsigned int Day = 1);
    Date(const Date& aDate);
    ~Date();
    
    //成员函数
    void SetDate(unsigned int Year, unsigned int Month, unsigned int Day);
    void SetDate(const Date& aDate);
    void SetYear(unsigned int Year);
    void SetMonth(unsigned int Month);
    void SetDay(unsigned int Day);
    void UpdateToday();
    bool IsLeapYear() const;
    bool IsValid() const;
    
    //基本判断函数
    static bool IsLeapYear(unsigned int Year);
    static bool IsValid(unsigned int Year, unsigned int Month, unsigned int Day);
    
    //当前时间
    static Date Today();
    
    //重载运算符
    Date& operator=(const Date& aDate);
    bool operator==(const Date& aDate) const;
    bool operator!=(const Date& aDate) const;
    bool operator> (const Date& aDate) const;
    bool operator< (const Date& aDate) const;
    bool operator>=(const Date& aDate) const;
    bool operator<=(const Date& aDate) const;
    
    //自加/自减运算符
    Date& operator++();
    Date  operator++(int);
    Date& operator--();
    Date  operator--(int);
    
    //Date相减
    unsigned int InDaysFromAD() const;
    long long operator-(const Date& aDate) const;
    
    //流运算符
    friend ostream& operator<<(ostream& Stream, const Date& aDate);
    friend istream& operator>>(istream& Stream, Date& aDate);
    
    //内嵌枚举类
    enum class DayType{
        MON=1,
        TUE=2,
        WED=3,
        THU=4,
        FRI=5,
        SAT=6,
        SUN=7
    };
    using DayType = DayType;
    
    //常引用
    const unsigned int& Year;
    const unsigned int& Month;
    const unsigned int& Day;
    const DayType& TodayType;
protected:
    unsigned int m_uYear;
    unsigned int m_uMonth;
    unsigned int m_uDay;
    DayType m_TodayType;
    static const unsigned int GrigoreyYear;
    static const unsigned int DaysOfMonth[2][13];
    
};
#endif /* Date_hpp */
