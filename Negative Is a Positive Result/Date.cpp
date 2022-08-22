/*************************************************************************
【文件名】                      Date.cpp
【功能模块和目的】
                （由于本人同时有两个小学期，所以本类直接服用范老师的）
                  日期类实现文件。本文件中仅包含Date类，用以实现Date年月日的管理。
                  本类参照课下小作业以及范老师demo，功能全面、高度可重用，符合通用类的要求。
 
【开发者及日期】             Jintao Fan 2021/08/02
【更改记录】                   暂无
*************************************************************************/

#include <cstdint>
#include "Date.hpp"

// 静态对象初始化
const unsigned int Date::GrigoreyYear = 1582u;
const unsigned int Date::DaysOfMonth[2][13] = {
    {0u, 31u, 28u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u},
    {0u, 31u, 29u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u}
};



/*************************************************************************
【函数名称】       Date
【函数功能】       由参数构造函数
【参数】          unsigned int  年，月，日
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Date::Date(unsigned int Year, unsigned int Month, unsigned int Day) : Year(m_uYear), Month(m_uMonth), Day(m_uDay), TodayType(m_TodayType) {
    SetDate(Year, Month, Day);
}


/*************************************************************************
【函数名称】       Date
【函数功能】       拷贝构造函数
【参数】           Date对象
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Date::Date(const Date& aDate) : Year(m_uYear), Month(m_uMonth), Day(m_uDay) , TodayType(m_TodayType){
    SetDate(aDate.Year, aDate.Month, aDate.Day);
}



/*************************************************************************
【函数名称】       赋值运算符
【函数功能】       赋值
【参数】           Date对象
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Date& Date::operator=(const Date& aDate) {
    if (this != &aDate) {
        SetDate(aDate.Year, aDate.Month, aDate.Day);
    }
    return *this;
}

/*************************************************************************
【函数名称】       析构函数
【函数功能】       析构
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Date::~Date() {
}

/*************************************************************************
【函数名称】       UpdateToday
【函数功能】       更新星期几信息
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Date::UpdateToday(){
    unsigned int Days = InDaysFromAD();
    m_TodayType = (DayType)((Days + 5u) % 7u);
}

/*************************************************************************
【函数名称】       SetDate
【函数功能】       设置日期
【参数】          unsigned int 年月日
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Date::SetDate(unsigned int Year, unsigned int Month, unsigned int Day) {
    //check first
    if (!IsValid(Year, Month, Day)) {
        throw invalid_argument("Is not valid date");
    }
    //assigment
    m_uYear  = Year;
    m_uMonth = Month;
    m_uDay   = Day;
    //caluate week day form days form AD
    //the 0001-01-01 is Saturday
    unsigned int Days = InDaysFromAD();
    m_TodayType = (DayType)((Days + 5u) % 7u);
}

/*************************************************************************
【函数名称】       SetDate
【函数功能】       拷贝Date对象信息，设置日期
【参数】           Date对象
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Date::SetDate(const Date& aDate){
    m_uYear  = aDate.m_uYear;
    m_uMonth = aDate.m_uMonth;
    m_uDay   = aDate.m_uDay;
    m_TodayType = aDate.m_TodayType;
    unsigned int Days = InDaysFromAD();
    m_TodayType = (DayType)((Days + 5u) % 7u);
}

/*************************************************************************
【函数名称】      SetYear
【函数功能】       设置年份
【参数】           unsigned int，年份
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Date::SetYear(unsigned int Year){
    if (!IsValid(Year, Month, Day)) {
        throw invalid_argument("Is not valid date");
    }
}


/*************************************************************************
【函数名称】       SetMonth
【函数功能】       设置月份
【参数】           unsigned int，设置月份
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Date::SetMonth(unsigned int Month){
    if (!IsValid(Year, Month, Day)) {
        throw invalid_argument("Is not valid date");
    }
}

/*************************************************************************
【函数名称】       SetDay
【函数功能】       设置天
【参数】           unsigned int, 设置天数
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Date::SetDay(unsigned int Day){
    if (!IsValid(Year, Month, Day)) {
        throw invalid_argument("Is not valid date");
    }
}

/*************************************************************************
【函数名称】       IsLeapYear
【函数功能】       判断是否是闰年
【参数】           unsigned int 年
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Date::IsLeapYear(unsigned int Year) {
    if (Year < GrigoreyYear) {
        return (Year % 4u == 0u);
    }
    else {
        return (Year % 4u == 0u && Year % 100u != 0u) || (Year % 400u == 0u);
    }
}

/*************************************************************************
【函数名称】       IsValid
【函数功能】       判断日期是否有效
【参数】           年月日
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Date::IsValid(unsigned int Year, unsigned int Month, unsigned int Day) {
//1 0001-01-01 is the first day of AD, not 0000-01-01
//2 Pope Gregor VIII issued a decree on February 24, 1582, permanently erasing the period from October 5, 1582 to October 14, 1582. There have never been these 10 days in history. October 4, 1582 is Thursday, and its next day is Friday, October 15, 1582.
    if (Year == 0) {
        return false;
    }
    if (Month < 1 || Month > 12) {
        return false;
    }
    if (Day == 0 ) {
        return false;
    }
    if (Year == GrigoreyYear && Month == 10 && (Day >= 5 && Day <= 14)) {
        return false;
    }
    if (Day > DaysOfMonth[IsLeapYear(Year)][Month]) {
        return false;
    }
    return true;
}



/*************************************************************************
【函数名称】       IsLeapYear
【函数功能】       判断是否是闰年
【参数】           无（this指针）
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Date::IsLeapYear() const {
    return IsLeapYear(m_uYear);
}

/*************************************************************************
【函数名称】       IsValid
【函数功能】       判断日期是否有效
【参数】           无（this指针）
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Date::IsValid() const {
    return IsValid(m_uYear, m_uMonth, m_uDay);
}


/*************************************************************************
【函数名称】       InDaysFromAD
【函数功能】       计算从公元纪年开始到现在的天数
【参数】           无（this指针）
【返回值】         无
【开发者及日期】   Fan Jingtao 2021/8/2
【更改记录】       暂无
*************************************************************************/
unsigned int Date::InDaysFromAD() const {
    unsigned int LeapYearCount;
    //leap years'count before 1582, from AD
    if (Year < GrigoreyYear) {
        LeapYearCount = (Year - 1u) / 4u;
    }
    //leap years'count after 1582, from AD
    else {
        LeapYearCount =
              //count leap years form AD, with nowdays method
              (Year - 1u) / 4u - (Year - 1u) / 100u + (Year - 1u) / 400u
              //add leap years defferent before 1582
            + (GrigoreyYear - 1u) / 100u - (GrigoreyYear - 1u) / 400u;
    }
    
    //Days before this year
    unsigned int DaysFromAD = 365u * (Year - 1u) + LeapYearCount;
    //there are not the 10 days: 1582-10-5 ~ 1582-10-14
    if ((Year >  GrigoreyYear) ||
        (Year == GrigoreyYear && Month > 10u) ||
        (Year == GrigoreyYear && Month == 10u && (Day >= 15u))) {
        DaysFromAD -= 10u;
    }
    //add days before this month
    bool IsLeapYearValue = IsLeapYear();
    for (unsigned int i = 1; i < Month; i++) {
        DaysFromAD += DaysOfMonth[IsLeapYearValue][i];
    }
    //add this day, and the days beforethis day
    DaysFromAD += Day;
    return DaysFromAD;
}

/*************************************************************************
【函数名称】       Today
【函数功能】       给出今天的年月日
【参数】           无（this指针）
【返回值】         无
【开发者及日期】    Fan Jingtao 2021/8/2
【更改记录】       暂无
*************************************************************************/
Date Date::Today() {
    auto tp = chrono::system_clock::now();
    time_t cur_time = chrono::system_clock::to_time_t(tp);
    struct tm* pTimeInfo = localtime(&cur_time);
    return Date(pTimeInfo->tm_year + 1900, pTimeInfo->tm_mon + 1, pTimeInfo->tm_mday);
}

/*************************************************************************
【函数名称】       大于运算符
【函数功能】       判断是否大于
【参数】           Date对象
【返回值】         bool
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Date::operator> (const Date& aDate) const {
    return InDaysFromAD() > aDate.InDaysFromAD();
}

/*************************************************************************
【函数名称】       小于运算符
【函数功能】       判断是否小于
【参数】           Date对象
【返回值】         bool
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Date::operator< (const Date& aDate) const {
    return InDaysFromAD() < aDate.InDaysFromAD();
}

/*************************************************************************
【函数名称】       大于等于运算符
【函数功能】       判断是否大于等于
【参数】           Date对象
【返回值】         bool
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Date::operator>=(const Date& aDate) const {
    return InDaysFromAD() >= aDate.InDaysFromAD();
}

/*************************************************************************
【函数名称】       小于等于运算符
【函数功能】       判断是否小于等于
【参数】           Date对象
【返回值】         bool
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Date::operator<=(const Date& aDate) const {
    return InDaysFromAD() <= aDate.InDaysFromAD();
}

/*************************************************************************
【函数名称】       等于运算符
【函数功能】       判断是否等于
【参数】           Date对象
【返回值】         bool
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Date::operator==(const Date& aDate) const {
    return (m_uYear == aDate.Year) && (m_uMonth == aDate.Month) && (m_uDay == aDate.Day);
}

/*************************************************************************
【函数名称】       不等运算符
【函数功能】       判断是否不等
【参数】           Date对象
【返回值】         bool
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Date::operator!=(const Date& aDate) const {
    return (m_uYear != aDate.Year) || (m_uMonth != aDate.Month) || (m_uDay != aDate.Day);
}

/*************************************************************************
【函数名称】       自加运算符
【函数功能】       进行自加操作
【参数】           无（this指针）
【返回值】         this 指针
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Date& Date::operator++() {
    if (m_uYear == GrigoreyYear && m_uMonth == 10 && m_uDay == 4){
        SetDate(GrigoreyYear, 10, 15);
    }
    else {
        unsigned int NewDay = m_uDay + 1;
        unsigned int NewMonth = m_uMonth;
        unsigned int NewYear = m_uYear;
        if (NewDay > DaysOfMonth[IsLeapYear()][NewMonth]) {
            NewDay = 1;
            NewMonth++;
        }
        if (NewMonth > 12) {
            NewMonth = 1;
            NewYear++;
        }
        SetDate(NewYear, NewMonth, NewDay);
    }
    return *this;
}

/*************************************************************************
【函数名称】       自加运算符
【函数功能】       进行自加操作
【参数】           无（this指针）
【返回值】         this 指针
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Date Date::operator++(int) {
    Date Res{*this};
    ++(*this);
    return Res;
}


/*************************************************************************
【函数名称】       自减运算符
【函数功能】       进行自减操作
【参数】           无（this指针）
【返回值】         this 指针
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Date& Date::operator--() {
    if (m_uYear == GrigoreyYear && m_uMonth == 10 && m_uDay == 15){
        SetDate(GrigoreyYear, 10, 4);
    }
    else {
        unsigned int NewDay = m_uDay;
        unsigned int NewMonth = m_uMonth;
        unsigned int NewYear = m_uYear;
        //XXXX-1-1
        if (NewDay == 1 && NewMonth == 1) {
            NewDay = 31;
            NewMonth = 31;
            NewYear--;
        }
        else if (NewDay == 1 && NewMonth != 1){
            NewDay = DaysOfMonth[IsLeapYear()][NewMonth - 1];
            NewMonth--;
        }
        else {
            NewDay--;
        }
        SetDate(NewYear, NewMonth, NewDay);
    }
    return *this;
}

/*************************************************************************
【函数名称】       自减运算符
【函数功能】       进行自减操作
【参数】           无（this指针）
【返回值】         this 指针
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Date Date::operator--(int) {
    Date Res{*this};
    --(*this);
    return Res;
}

/*************************************************************************
【函数名称】       减运算符
【函数功能】      两个Date对象相减，返回相隔天数
【参数】           被减Date对象
【返回值】         this 指针
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
long long Date::operator-(const Date& aDate) const {
    return static_cast<long long>(InDaysFromAD()) -  static_cast<long long>(aDate.InDaysFromAD());
}

/*************************************************************************
【函数名称】       流输出运算符
【函数功能】       流输出
【参数】           流，Date对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
ostream& operator<<(ostream& Stream, const Date& aDate) {
    Stream << aDate.m_uYear << '/' << aDate.m_uMonth << '/' << aDate.m_uDay;
//    switch (aDate.TodayType) {
//        case Date::DayType::MON ://MON = 1, TUES = 2, WED = 3, THUR = 4, FRI = 5, SAT = 6 , SUN
//            Stream << "MON";
//            break;
//        case Date::DayType::TUE :
//            Stream << "TUE";
//            break;
//        case Date::DayType::WED :
//            Stream << "WED";
//            break;
//        case Date::DayType::THU :
//            Stream << "THU";
//            break;
//        case Date::DayType::FRI :
//            Stream << "FRI";
//            break;
//        case Date::DayType::SAT :
//            Stream << "SAT";
//            break;
//        case Date::DayType::SUN :
//            Stream << "SUN";
//            break;
//        default:
//            break;
//    }
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
istream& operator>>(istream& Stream, Date& aDate) {
    char Temp;
    unsigned int Year;
    unsigned int Month;
    unsigned int Day;
    string WeekDayStr;
    Stream >> Year  >> Temp //jump first  '/'
           >> Month >> Temp //jump second '/'
    >> Day;//jump third  '/'
//           >> WeekDayStr;
    aDate.SetDate(Year, Month, Day);
    return Stream;
}

