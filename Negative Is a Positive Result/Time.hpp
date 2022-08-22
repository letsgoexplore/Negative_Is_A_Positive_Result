/*************************************************************************
【文件名】                      Time.hpp
【功能模块和目的】
                  时间类头文件。本文件中仅包含Time类，用以实现Time时分秒的管理。
                  本类参照课下小作业以及范老师demo，功能全面、高度可重用，符合通用类的要求。
 
【开发者及日期】            Jason Zhao 2022/07/18
【更改记录】                   暂无
*************************************************************************/


#ifndef Time_hpp
#define Time_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

/*************************************************************************
【类名】             Time
【功能】             管理时间信息的数据与功能
【接口说明】
 成员函数
     SetTime：设置时间数据
     SetHour：设置小时
     SetMinute：设置分钟
     SetSecond：设置秒
     CheckTime：检查时间是否合理
 
 静态函数
     TotalSecond：从今天第一秒开始到现在的总秒数
     Now：当前的时分秒
 
 运算符
     -：两个Date对象相减，即两个日期相减，返回中间的天数
     ==, !=,>,>=,<,<= ; 判断运算符
     =：赋值运算符
     ++,--：自运算符
     >>,<<: 流运算符
 
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class Time{
public:
    //构造函数和拷贝构造函数,析构函数
    Time(const Time& t);
    Time(unsigned int Hour = 0, unsigned int Minute = 0, unsigned int Second = 0);
    ~Time();
    
    
    //检查时间合理性与设置时间
    void SetTime(const Time& aTime);
    void SetTime(unsigned int Hour, unsigned int Minute, unsigned int Second);
    void SetSecond(unsigned int Second);
    void SetMinute(unsigned int Minute);
    void SetHour(unsigned int Hour);
    static bool CheckTime(unsigned int Hour, unsigned int Minute, unsigned int Second);
    
    //总时间
    unsigned int TotalSeconds() const;
    
    //当前时间
    Time Now();
    
    //运算符重载
    Time& operator= (const Time& source);
    bool operator>(const Time& source) const;
    bool operator<(const Time& source) const;
    bool operator>=(const Time& source) const;
    bool operator<=(const Time& source) const;
    bool operator==(const Time& source) const;
    bool operator!=(const Time& source) const;
    
    //重载自加运算符
    Time& operator++();
    Time  operator++(int);
    Time& operator--();
    Time  operator--(int);
    long long operator-(const Time& aTime) const;
    
    //流运算符
    friend ostream& operator<< (ostream& Stream, const Time& aTime);
    friend istream& operator>> (istream& Stream, Time& aTime);
    
    //常引用
    const unsigned int& Hour;
    const unsigned int& Minute;
    const unsigned int& Second;
    
protected:
    unsigned int m_uHour;
    unsigned int m_uMinute;
    unsigned int m_uSecond;
};
#endif /* Time_hpp */
