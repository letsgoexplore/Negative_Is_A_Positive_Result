/*************************************************************************
【文件名】                      DateTime.hpp
【功能模块和目的】

                  日期时间类头文件。多继承于Date和Time类。
                  本文件中仅包含DateTime类，用以实现DateTime年月日时分秒的管理，全面管理时间。
                  选择多继承而非DateTime继承于Time，是为了更高的代码效率于性价比。三个类的灵活度远比两个类的灵活度高。
                  本类参照课下小作业以及范老师demo，功能全面、高度可重用，符合通用类的要求。
 
【开发者及日期】             Jintao Fan 2021/08/02
【更改记录】                   暂无
*************************************************************************/

#ifndef DateTime_hpp
#define DateTime_hpp

#include <stdio.h>
#include "Time.hpp"
#include "Date.hpp"
//#include <utility>
using namespace std;


/*************************************************************************
【类名】             DateTime
【功能】             多继承于Date、Time，管理日期时间的数据和操作
【接口说明】
 静态函数
     Now：当前的年月日时分秒
 
 运算符
     -：两个Date对象相减，即两个日期相减，返回中间的天数
     ==, !=,>,>=,<,<= ; 判断运算符
     =：赋值运算符
     ++,--：自运算符
     >>,<<: 流运算符
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class DateTime : public Date, public Time{
public:
    //构造函数/析构函数
    DateTime(const Date& aDate = Date(), const Time& aTime = Time());
    DateTime(unsigned int Year, unsigned int Month, unsigned int Day, unsigned int Hour, unsigned int Minute, unsigned int Second);
    ~DateTime();
    
    // 赋值运算符
    DateTime& operator=(const DateTime& aDateTime);
    
    // 判断运算符
    bool operator==(const DateTime& aDateTime) const;
    bool operator!=(const DateTime& aDateTime) const;
    bool operator>(const DateTime& aDateTime) const;
    bool operator<(const DateTime& aDateTime) const;
    bool operator>=(const DateTime& aDateTime) const;
    bool operator<=(const DateTime& aDateTime) const;
   
    
    // 自运算符
    DateTime& operator++();
    DateTime  operator++(int);
    DateTime& operator--();
    DateTime  operator--(int);
    
    //减运算符
    long long operator-(const DateTime& aDateTime) const;
 
    //流输入输出运算符
    friend ostream& operator<<(ostream& Stream, const DateTime& aDateTime);
    friend istream& operator>>(istream& Stream, DateTime& aDateTime);

    //静态函数
    static DateTime Now();
    void UpdateTodayType();

};

#endif /* DateTime_hpp */
