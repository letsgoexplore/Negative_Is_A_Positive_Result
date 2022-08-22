/*************************************************************************
【文件名】                      DateTime.cpp
【功能模块和目的】
                （由于本人同时有两个小学期，所以本类直接复用范老师demo）
                  日期时间类实现文件。多继承于Date和Time类。
                  本文件中仅包含DateTime类，用以实现DateTime年月日时分秒的管理，全面管理时间。
                  选择多继承而非DateTime继承于Time，是为了更高的代码效率于性价比。三个类的灵活度远比两个类的灵活度高。
                  本类参照课下小作业以及范老师demo，功能全面、高度可重用，符合通用类的要求。
 
【开发者及日期】             Jintao Fan 2021/08/02
【更改记录】                   暂无
*************************************************************************/


#include <cstdint>
#include "DateTime.hpp"



/*************************************************************************
【函数名称】      DateTime
【函数功能】       半拷贝构造函数
【参数】           Date对象，Time对象
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
DateTime::DateTime(const Date& aDate, const Time& aTime):Date(aDate), Time(aTime){
}

/*************************************************************************
【函数名称】       DateTime
【函数功能】       由参数构造函数
【参数】           unsigned int 年月日时分秒
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
DateTime::DateTime(unsigned int Year, unsigned int Month, unsigned int Day, unsigned int Hour, unsigned int Minute, unsigned int Second) : Date(Year, Month, Day), Time(Hour, Minute, Second){
}

/*************************************************************************
【函数名称】       ～DateTime
【函数功能】       析构函数
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
DateTime::~DateTime(){
}

/*************************************************************************
【函数名称】       赋值运算符
【函数功能】       赋值
【参数】           DateTime对象
【返回值】         this指针
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
DateTime& DateTime::operator=(const DateTime& aDateTime){
    SetDate(aDateTime);
    SetTime(aDateTime);
    return *this;
}


/*************************************************************************
【函数名称】       等于运算符
【函数功能】       判断是否等于
【参数】           DateTime对象
【返回值】         bool，是否等于
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool DateTime::operator==(const DateTime& aDateTime) const {
    return (this->Date::operator==(aDateTime) && this->Time::operator==(aDateTime));
}

/*************************************************************************
【函数名称】       不等运算符
【函数功能】       判断是否不等
【参数】           DateTime对象
【返回值】         bool，是否不等
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool DateTime::operator!=(const DateTime& aDateTime) const {
    return !operator==(aDateTime);
}

/*************************************************************************
【函数名称】       大于运算符
【函数功能】       判断是否大于
【参数】           DateTime对象
【返回值】         bool，是否大于
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool DateTime::operator>(const DateTime& aDateTime) const{
    return (this->Date::operator>(aDateTime)) || (this->Date::operator==(aDateTime) && this->Time::operator>(aDateTime));
}

/*************************************************************************
【函数名称】       小于运算符
【函数功能】       判断是否小于
【参数】           DateTime对象
【返回值】         bool，是否小于
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool DateTime::operator<(const DateTime& aDateTime) const{
    return (this->Date::operator<(aDateTime)) || (this->Date::operator==(aDateTime) && this->Time::operator<(aDateTime));
}

/*************************************************************************
【函数名称】       大于等于运算符
【函数功能】       判断是否大于等于
【参数】           DateTime对象
【返回值】         bool，是否大于等于
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool DateTime::operator>=(const DateTime& aDateTime) const {
    return operator>(aDateTime) || operator==(aDateTime);
}

/*************************************************************************
【函数名称】       小于等于运算符
【函数功能】       判断是否小于等于
【参数】           DateTime对象
【返回值】         bool，是否小于等于
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool DateTime::operator<=(const DateTime& aDateTime) const {
    return operator<(aDateTime) || operator==(aDateTime);
}


/*************************************************************************
【函数名称】       自加运算符
【函数功能】       自加
【参数】           无（this指针）
【返回值】         this指针
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
DateTime& DateTime::operator++() {
    this->Time::operator++();
    if (this->Time::Hour == 0 && this->Time::Minute == 0 && this->Time::Second == 0) {
        this->Date::operator++();
    }
    return *this;
}

/*************************************************************************
【函数名称】       自加运算符
【函数功能】       自加
【参数】           无（this指针）
【返回值】         this指针
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
DateTime DateTime::operator++(int){
    DateTime Res{*this};
    ++(*this);
    return Res;
}

/*************************************************************************
【函数名称】       自减运算符
【函数功能】       自减
【参数】           无（this指针）
【返回值】         this指针
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
DateTime& DateTime::operator--() {
    this->Time::operator--();
    if (this->Time::Hour == 23 && this->Time::Minute == 59 && this->Time::Second == 59) {
        this->Date::operator--();
    }
    return *this;
}


/*************************************************************************
【函数名称】       自减运算符
【函数功能】       自减
【参数】           无（this指针）
【返回值】         this指针
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
DateTime DateTime::operator--(int) {
    DateTime Res{*this};
    --(*this);
    return Res;
}

/*************************************************************************
【函数名称】       流输出运算符
【函数功能】       流输出
【参数】           流，DateTime对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
ostream& operator<<(ostream& Stream, const DateTime& aDateTime) {
    Stream << static_cast<const Date&>(aDateTime)
           << ' '
           << static_cast<const Time&>(aDateTime);
    return Stream;
}

/*************************************************************************
【函数名称】       流输入运算符
【函数功能】       流输入
【参数】           流，DateTime对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
istream& operator>>(istream& Stream, DateTime& aDateTime) {
    Stream >> static_cast<Date&>(aDateTime) //space is not need to jump
           >> static_cast<Time&>(aDateTime);
    return Stream;
}

/*************************************************************************
【函数名称】       减运算符
【函数功能】       减操作
【参数】           DateTime对象
【返回值】         longlong，两个DateTime之间相隔的秒数
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
long long DateTime::operator-(const DateTime& aDateTime) const {
    return this->Date::operator-(aDateTime) * 3600 * 24 + this->Time::operator-(aDateTime);
}

/*************************************************************************
【函数名称】       Now
【函数功能】       给出现在的年月日时分秒
【参数】           无
【返回值】         DateTime
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
DateTime DateTime::Now(){
    auto tp = chrono::system_clock::now();
    time_t cur_time = chrono::system_clock::to_time_t(tp);
    struct tm* pTimeInfo = localtime(&cur_time);
    return DateTime(pTimeInfo->tm_year + 1900, pTimeInfo->tm_mon + 1, pTimeInfo->tm_mday, pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec);
}

/*************************************************************************
【函数名称】       UpdateTodayType
【函数功能】       由于Now没有更新星期几的信息，故而创建另外接口
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void DateTime::UpdateTodayType(){
    UpdateToday();
}
