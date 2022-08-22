/*************************************************************************
【文件名】                      Time.cpp
【功能模块和目的】
                （由于本人同时有两个小学期，所以本类忽略注释）
                  时间类实现文件。本文件中仅包含Time类，用以实现Time时分秒的管理。
                  本类参照课下小作业以及范老师demo，功能全面、高度可重用，符合通用类的要求。
 
【开发者及日期】            Jason Zhao 2022/07/18
【更改记录】                   暂无
*************************************************************************/
#include "Time.hpp"



//构造函数和拷贝构造函数
/*************************************************************************
【函数名称】       Time
【函数功能】       由参数构造函数
【参数】           unsigned int，时分秒
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Time::Time(unsigned int Hour , unsigned int Minute, unsigned int Second) : Hour(m_uHour), Minute(m_uMinute), Second(m_uSecond){
    if(CheckTime(Hour, Minute, Minute)){
        m_uHour = Hour;
        m_uMinute = Minute;
        m_uSecond = Second;
    };
};

/*************************************************************************
【函数名称】       Time
【函数功能】       拷贝构造函数
【参数】           Time对象
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Time::Time(const Time& t1): Hour(m_uHour), Minute(m_uMinute), Second(m_uSecond){
    m_uHour = t1.Hour;
    m_uMinute = t1.Minute;
    m_uSecond = t1.Second;
};

/*************************************************************************
【函数名称】       ～Time
【函数功能】       析构函数
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Time::~Time(){
}

//检查时间合理性函数
/*************************************************************************
【函数名称】       CheckTime
【函数功能】       检查输入的时间是否合理
【参数】           unsigned int， 年月日
【返回值】         bool， 是否合理
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Time::CheckTime(unsigned int Hour, unsigned int Minute, unsigned int Second){
    if(Hour < 24 && Minute < 60 && Second < 60){
        return true;
    }
    return false;
};

//设置时间函数
/*************************************************************************
【函数名称】       SetTime
【函数功能】       设置时间
【参数】           Time对象
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Time::SetTime(const Time& aTime){
    SetSecond(aTime.Second);
    SetMinute(aTime.Minute);
    SetHour(aTime.Hour);
}


/*************************************************************************
【函数名称】       SetTime
【函数功能】       设置时间
【参数】           unsigned int，时，分，秒
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Time::SetTime(unsigned int Hour, unsigned int Minute, unsigned int Second){
    SetSecond(Second);
    SetMinute(Minute);
    SetHour(Hour);
}

/*************************************************************************
【函数名称】       SetHour
【函数功能】       设置小时
【参数】           unsigned int，小时
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Time::SetHour(unsigned int Hour) {
    if (Hour >= 24) {
        throw invalid_argument("Hour should be in range (0,23).");
    }
    m_uHour = Hour;
}


/*************************************************************************
【函数名称】       SetMinute
【函数功能】       设置分钟
【参数】           unsigned int，分钟
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Time::SetMinute(unsigned int Minute) {
    if (Minute >= 60) {
        throw invalid_argument("Minute should be in range(0,59).");
    }
    m_uMinute = Minute;
}


/*************************************************************************
【函数名称】       SetSecond
【函数功能】       设置秒
【参数】           unsigned int，秒
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
void Time::SetSecond(unsigned int Second) {
    if (Second >= 60) {
        throw invalid_argument("Second should be in range(0,59).");
    }
    m_uSecond = Second;
}


//当前时间
/*************************************************************************
【函数名称】       Now
【函数功能】       给出当前的时间：时分秒
【参数】           无（this指针）
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Time Time::Now() {
    auto tp = chrono::system_clock::now();
    time_t cur_time = chrono::system_clock::to_time_t(tp);
    struct tm* pTimeInfo = localtime(&cur_time);
    return Time(pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec);
}

//计算总秒数
/*************************************************************************
【函数名称】       TotalSeconds
【函数功能】       从今天第一秒到现在的总秒数
【参数】           无
【返回值】         unsigned int，总秒数
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
unsigned int Time::TotalSeconds() const{
    return (m_uHour * 3600u + m_uMinute * 60u + m_uSecond) + 1;
}

//重载运算符
/*************************************************************************
【函数名称】       等于运算符
【函数功能】       判断是否等于
【参数】           Time对象
【返回值】         bool，是否小于
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Time::operator== (const Time& source) const{
    if(m_uHour == source.Hour && m_uMinute == source.Minute && m_uSecond == source.Second){
        return true;
    }
    return false;
}

/*************************************************************************
【函数名称】       不等运算符
【函数功能】       判断是否不等
【参数】           Time对象
【返回值】         bool，是否不等
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Time::operator!= (const Time& source) const{
    if(m_uHour == source.Hour && m_uMinute == source.Minute && m_uSecond == source.Second){
        return false;
    }
    return true;
}

/*************************************************************************
【函数名称】       大于等于运算符
【函数功能】       判断是否大于
【参数】           Time对象
【返回值】         bool，是否大于
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Time::operator> (const Time& source) const{
    if(m_uHour > source.Hour){
        return true;
    }
    else if (m_uHour == source.Hour){
        if(m_uMinute > source.Minute){
            return true;
        }
        else if(m_uMinute == source.Minute){
            if(m_uSecond > source.Second){
                return true;
            }
        }
    }
    return false;
}

/*************************************************************************
【函数名称】       小于运算符
【函数功能】       判断是否小于
【参数】           Time对象
【返回值】         bool，是否小于
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Time::operator< (const Time& source) const{
    if(m_uHour < source.Hour){
        return true;
    }
    else if (m_uHour == source.Hour){
        if(m_uMinute < source.Minute){
            return true;
        }
        else if(m_uMinute == source.Minute){
            if(m_uSecond < source.Second){
                return true;
            }
        }
    }
    return false;
}

/*************************************************************************
【函数名称】       大于等于运算符
【函数功能】       判断是否大于等于
【参数】           Time对象
【返回值】         bool，是否大于
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Time::operator>= (const Time& source) const{
    if(m_uHour > source.Hour){
        return true;
    }
    else if (m_uHour == source.Hour){
        if(m_uMinute > source.Minute){
            return true;
        }
        else if(m_uMinute == source.Minute){
            if(m_uSecond >= source.Second){
                return true;
            }
        }
    }
    return false;
}

/*************************************************************************
【函数名称】       小于等于运算符
【函数功能】       判断是否小于等于
【参数】           Time对象
【返回值】         bool，是否小于等于
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
bool Time::operator<= (const Time& source) const{
    if(m_uHour < source.Hour){
        return true;
    }
    else if (m_uHour == source.Hour){
        if(m_uMinute < source.Minute){
            return true;
        }
        else if(m_uMinute == source.Minute){
            if(m_uSecond <= source.Second){
                return true;
            }
        }
    }
    return false;
}

/*************************************************************************
【函数名称】       赋值运算符
【函数功能】       赋值
【参数】           Time对象
【返回值】         this指针
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Time& Time::operator= (const Time& source){
    m_uHour = Hour;
    m_uMinute = Minute;
    m_uSecond = Second;
    return *this;
};

// 重载自加/自减运算符
/*************************************************************************
【函数名称】       自加运算符
【函数功能】       自加
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Time& Time::operator++() {
    if (TotalSeconds() == Time(23, 59, 59).TotalSeconds()) {
        m_uHour = 0;
        m_uMinute = 0;
        m_uSecond = 0;
    }
    else {
        unsigned int NewInSeconds = TotalSeconds() + 1;
        m_uSecond = NewInSeconds % 60;
        NewInSeconds /= 60;
        m_uMinute = NewInSeconds % 60;
        m_uHour = NewInSeconds / 60;
    }
    return *this;
}


/*************************************************************************
【函数名称】       自加运算符
【函数功能】       自加
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Time Time::operator++(int) {
    Time Res = *this;
    ++(*this);
    return Res;
}


/*************************************************************************
【函数名称】       自减运算符
【函数功能】       自减
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Time& Time::operator--() {
    if (TotalSeconds() == 0) {
        m_uHour = 23;
        m_uMinute = 59;
        m_uSecond = 59;
    }
    else {
        unsigned int NewInSeconds = TotalSeconds() - 1;
        m_uSecond = NewInSeconds % 60;
        NewInSeconds /= 60;
        m_uMinute = NewInSeconds % 60;
        m_uHour = NewInSeconds / 60;
    }
    return *this;
}

/*************************************************************************
【函数名称】       自减运算符
【函数功能】       自减
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
Time Time::operator--(int) {
    Time Res = *this;
    --(*this);
    return Res;
}


/*************************************************************************
【函数名称】       减运算符
【函数功能】         两个Time对象相减操作
【参数】           无
【返回值】         无
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
long long Time::operator-(const Time& aTime) const {
    return static_cast<long long>(TotalSeconds()) - static_cast<long long>(aTime.TotalSeconds());
}


// 重载流运算符
/*************************************************************************
【函数名称】       流输出运算符
【函数功能】       流输出
【参数】           流，Time对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
ostream& operator<<(ostream& Stream, const Time& aTime) {
    Stream << aTime.m_uHour << ':' << aTime.m_uMinute << ':' << aTime.m_uSecond;
    return Stream;
}

/*************************************************************************
【函数名称】       流输入运算符
【函数功能】       流输入
【参数】           流，Time对象
【返回值】         流
【开发者及日期】    Jason Zhao 2022/07/21
【更改记录】       暂无
*************************************************************************/
istream& operator>>(istream& Stream, Time& aTime) {
    char Temp;
    Stream >> aTime.m_uHour   >> Temp
           >> aTime.m_uMinute >> Temp
           >> aTime.m_uSecond;
    return Stream;
}
