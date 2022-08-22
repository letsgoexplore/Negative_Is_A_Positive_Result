/*************************************************************************
【文件名】                       CipherText.hpp
【功能模块和目的】         继承于MD5，对于密码进行加密
【开发者及日期】            Jingtao Fan 2021/08/02
【更改记录】                   暂无
*************************************************************************/


#ifndef CipherText_hpp
#define CipherText_hpp

#include <string>
#include <ostream>
#include "MD5.hpp"
using namespace std;

/*************************************************************************
【类名】             CipherText
【功能】             继承于MD5，对于明文进行加密成暗纹
【接口说明】
 赋值运算符： =
 运算符重载：==，!=
 流运算符：<< >>
【开发者及日期】     Jason Zhao 2022/07/21
【更改记录】         暂无
*************************************************************************/
class CipherText : public MD5 {
public:
    //构造函数
    CipherText();
    CipherText(const string& Plainext);

    //赋值运算符
    CipherText& operator= (const string& Plaintext);
    CipherText& operator= (const CipherText& anText);

    //运算符重载
    bool operator==(const string& Plaintext) const;
    bool operator!=(const string& Plaintext) const;

    //流运算符重载
    friend ostream& operator<<(ostream& Stream, const CipherText& aCiphertext);
    friend istream& operator>>(istream& Stream, CipherText& aCiphertext);
};

#endif /* CipherText_hpp */
