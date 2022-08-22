/*************************************************************************
【文件名】                      main.cpp
【功能模块和目的】
                  主文件。include Controller，故而能够实现各种半通用类功能。
                  本文件中主要描述各个页面的信息与跳转关系，并且通过Controller实现页面下的功能。


【开发者及日期】            Jason Zhao 2022/07/18
【更改记录】                   暂无
*************************************************************************/

#include <iostream>
#include <string>
#include "Controller.hpp"
using namespace std;

string MainMenu(Controller& Controler);
string LoginMenu(Controller& Controler);
string RegisterMenu(Controller& Controler);
string ChoosingMenu(Controller& Controler);
string UserMenu(Controller& Controler);
string AdminMenu(Controller& Controler);
string CollectorMenu(Controller& Controler);
string LabWorkerMenu(Controller& Controler);

//string LoginMenu(Controller& Controler);
//string LoginMenu(Controller& Controler);

int main(int argc, const char * argv[]) {
    Controller Controler("/Users/jasonzhao/Desktop/Negative Is a Positive Result/UserFile.txt",
        "/Users/jasonzhao/Desktop/Negative Is a Positive Result/TubeFile.txt");
    cout << MainMenu(Controler) << endl;
    return 0;
}

string MainMenu(Controller& Controler){
    string Selection{};
    cout << "WELLCOME TO 水木健康宝" << endl;
    while(Selection!="1" && Selection!="2" && Selection!="3"){
        cout << "---------- Main Page----------" << endl;
        cout << "What Do You Wanna To Do?" << endl;
        cout << "1. Login" << endl
             << "2. Register" << endl
             << "3. Quit" << endl << "(1/2/3):";
        getline(cin, Selection);
        if (Selection == "1") {
            cout << LoginMenu(Controler) << endl;
        }
        if (Selection == "2"){
            cout << RegisterMenu(Controler) << endl;
        }
        if (Selection == "3"){
            break;
        }
        else{
            cout << "Wrong Input, Please Try Again" << endl;
        }
        Selection.clear();
    }
    return "---- Wish One Day You Will Never Use 水木健康宝 ----";
}


string LoginMenu(Controller& Controler) {
    string UserId;
    string UserName;
    string Password;
    string Selection = "N";
    while (Selection != "Y" && Selection != "y") {
        cout << "----------LOGIN----------" << endl;

        cout << "User ID:";
        getline(cin, UserId);

        cout << "User Name:";
        getline(cin, UserName);

        cout << "Password:";
        getline(cin, Password);

        RES Res = Controler.Login(UserId, UserName, Password);

        cout << ResStr[static_cast<int>(Res)].c_str() << endl;

        if(Res == RES::NO_USER) {
            cout << "Haven't Registered Yet. Do you want to Registered?(Y/N)";
            Selection.clear();
            getline(cin, Selection);
            if(Selection == "Y" || Selection == "y"){
                cout << RegisterMenu(Controler) << endl;
                Selection.clear();
                
            }
        }
        if(Res == RES::WRONG_NAMEORPASSWORD){
            cout << "Wrong name or password" << endl;
        }

        else if (Res == RES::USER_LOGINED){
            cout << ChoosingMenu(Controler) << endl;
            cout << "------ Back To LOGIN -------" << endl;
        }

        Selection.clear();
        while (Selection != "Y" && Selection != "N" && Selection != "y" && Selection != "n") {
            
            cout << "Exit? (Y/N):";
            getline(cin, Selection);
        }
    }
    return "------ Back To The Main Page ------";
}



string RegisterMenu(Controller& Controler){
    string UserId;
    string UserName;
    string Password;

    cout << "----Registering Page----" << endl;
    cout << "New user's Id(18bytes):";
    getline(cin, UserId);

    cout << "New user's Name:";
    getline(cin, UserName);

    cout << "New user's Password:";
    getline(cin, Password);

    RES Res = Controler.Register(UserId, UserName, Password);
    return ResStr[static_cast<int>(Res)].c_str();
}


string ChoosingMenu(Controller& Controler){
    string Selection;
    while (Selection != "1" && Selection != "2" && Selection != "3" && Selection != "4" && Selection != "5") {
        Controler.UpdateInfo();
        cout << "----Choosing Which Role?----" << endl;
        cout << "1. Normal User" << endl;
        if(Controler.LoginedUser->MyUserRole.IsAdministrator){
            cout << "2. Administrator" << endl;
        }
        if(Controler.LoginedUser->MyUserRole.IsCollector){
            cout << "3. Collector" << endl;
        }
        if(Controler.LoginedUser->MyUserRole.IsLabWorker){
            cout << "4. LabWorker" << endl;
        }
        cout<<"5. Back to Login Menu"<< endl << "(1/2/3/4/5):";
        getline(cin, Selection);

        if (Selection == "1") {
            cout << UserMenu(Controler) << endl;
        }
        else if (Selection == "2" && Controler.LoginedUser->MyUserRole.IsAdministrator) {
            cout << AdminMenu(Controler) << endl;
        }
        else if (Selection == "3" && Controler.LoginedUser->MyUserRole.IsCollector) {
            cout << CollectorMenu(Controler) << endl;
        }
        else if (Selection == "4" && Controler.LoginedUser->MyUserRole.IsLabWorker) {
            cout << LabWorkerMenu(Controler) << endl;
        }
        else if (Selection == "5"){
            break;
        }
        else{
            cout << "Wrong Input, Please Try Again" << endl;
        }
        Selection.clear();
    }
    return "------ User Logout ------";
}



string UserMenu(Controller& Controler){
    string Selection{};
    cout << "---- Normal User Page ----" << endl;
    if(Controler.LoginedUser->LatestResult.NoHistoryRecord){
        cout << "No Test History" << endl;
    }
    else{
        cout << "Collect Time:" << Controler.LoginedUser->LatestResult.CollectTime << endl <<
        "Log Time:" << Controler.LoginedUser->LatestResult.LogTime << endl <<
        "Test Result:" << Controler.LoginedUser->LatestResult.Result << endl;
    }
    while (Selection != "Y" && Selection != "y"){
        Selection.clear();
        cout << "Go Back To Choosing Page?(Y/N)" ;
        getline(cin, Selection);
    }
    return "---- Quit Normal User Page ----";
}



string AdminMenu(Controller& Controler){
    string Selection{};
    string AddUserId{};
    while (Selection != "1" && Selection != "2" && Selection != "3" && Selection != "4" && Selection != "5" && Selection != "6" && Selection != "7") {
        cout << "---------- Admin Page ----------" << endl;
        cout << "-- Dear Admin, What Do you wanna to do? --" << endl;
        cout << "1. Add New Admin" << endl
            << "2. Add New Collector" << endl
            << "3. Delete Present Collector" << endl
            << "4. Add New Lab-Worker" << endl
        << "5. Delete Present Lab-Worker" << endl
            << "6. Quit Admin Role"<< endl
            << "7. Back to Choosing Menu" << endl
            << "(1/2/3/4/5/6/7):";
        getline(cin, Selection);

        if (Selection == "1") {
            string AddUserId{};
            cout << "Input User's Id: ";
            getline(cin, AddUserId);
            RES Ret = Controler.AddAdmin(AddUserId);
            if(Ret == RES::NO_USER){
                cout << "---- No Such User ----" << endl;
            }
            if(Ret == RES::ADD_DONE){
                cout << "-- Successfully Add A New Admin --" <<endl;
            }
        }
        else if (Selection == "2"){
            cout << "Input User's Id: ";
            getline(cin, AddUserId);
            RES Ret = Controler.AddCollector(AddUserId);
            if(Ret == RES::NO_USER){
                cout << "---- No Such User ----" << endl;
            }
            if(Ret == RES::ADD_DONE){
                cout << "-- Successfully Add A New Collector --" <<endl;
            }
        }

        else if (Selection == "3") {
            cout << "Input User's Id: ";
            getline(cin, AddUserId);
            RES Ret = Controler.DeleteCollector(AddUserId);
            if(Ret == RES::NO_USER){
                cout << "---- No Such User ----" << endl;
            }
            if(Ret == RES::ADD_DONE){
                cout << "-- Successfully Delete A Present Collector --" <<endl;
            }
        }

        else if (Selection == "4") {
            cout << "Input User's Id: ";
            getline(cin, AddUserId);
            RES Ret = Controler.AddLabWorker(AddUserId);
            if(Ret == RES::NO_USER){
                cout << "No Such User" << endl;
            }
            if(Ret == RES::ADD_DONE){
                cout << "Successfully Add A New Lab-Worker" <<endl;
            }
        }

        else if (Selection == "5"){
            cout << "Input User's Id: ";
            getline(cin, AddUserId);
            RES Ret = Controler.DeleteLabWorker(AddUserId);
            if(Ret == RES::NO_USER){
                cout << "---- No Such User ----" << endl;
            }
            if(Ret == RES::ADD_DONE){
                cout << "-- Successfully Delete A Present Lab-Worker --" <<endl;
            }
        }

        else if (Selection == "6"){
            RES Ret = Controler.QuitAdmin();
            if(Ret == RES::ONLY_ONE_ADMIN_LEFT){
                cout << "-- You Are The Only Admin, So can't Quit --" << endl;
            }
            if(Ret == RES::ADD_DONE){
                cout << "-- Successfully Quit Admin --" <<endl;
                Controler.UpdateInfo();
                break;
            }
        }
        else if (Selection == "7"){
            break;
        }
        else{
            cout << "Wrong Input, Please Try Again" << endl;
        }
        Selection.clear();
    }
    return "------ Quit Admin Page ------";
}




string CollectorMenu(Controller& Controler){
    string Selection{};
    while (Selection != "1" && Selection != "2") {
        cout << "---------- Collector Page ----------" << endl;
        cout << "1. New Tube" << endl
             << "2. Back to login menu" << endl << "(1/2):";
        getline(cin, Selection);
        if (Selection == "1") {
            RES Ret = Controler.NewTube();
            if(Ret == RES::ERROR_USERID || Ret == RES::NO_USER){
                cout << "Something wrong with one of the UserId You Input, Please Input Again" << endl;
            }
            else if(Ret == RES::NO_USER_UNDER_TUBE){
                cout << "No user is added under the tube" << endl;
            }
            else if(Ret == RES::TUBE_CREATED){
                cout << "---- Tube Successfully Created! ----" << endl;
            }
        }
        else if (Selection == "2") {
            break;
        }
        else {
            cout << "Wrong Input, Please Try Again" << endl;
        }
        Selection.clear();
    }
    return "COLLECTOR LOGOUT";
}


string LabWorkerMenu(Controller& Controler){
    string Selection{};
    while (Selection != "1" && Selection != "2") {
        cout << "---------- LabWorker Page ----------" << endl;
        cout << "1. Add Result" << endl
             << "2. Back to login menu" << endl << "(1/2):";
        getline(cin, Selection);
        if (Selection == "1") {
            string aTubeId{};
            string InputResult{};
            bool aResult = 0;

            cout << "The Tube Id:";
            getline(cin, aTubeId);

            //0代表阴性，1代表阳性
            cout << "The Result(0/1):";
            getline(cin, InputResult);
            if( InputResult == "0"){
                aResult = 0;
            }
            else if( InputResult == "1"){
                aResult = 1;
            }
            else{
                Selection.clear();
                continue;
            }

            //进行搜索
            RES Ret = Controler.NewResult(aTubeId, aResult);
            if(Ret == RES::NO_TUBE_ID){
                cout << "No such Tube Id, Please check again!" << endl;
            }
            else if(Ret == RES::TUBE_CREATED){
                cout << "---- Result Successfully Added! ----" << endl;
            }
        }
        else if (Selection == "2") {
            break;
        }
        else {
            cout << "Wrong Input, Please Try Again" << endl;
        }
        Selection.clear();
    }
    return "------ Quit LabWorker Page ------";
}


//# include <iostream>
//# include "CipherText.hpp"
//# include "User.hpp"
//using namespace std;
//
//int main(){
////    cout << CipherText("123456")<<endl;
////    return 0;
//    User anUser("110115200101010001", "ZhaoJia", "123456", 1, 1, 1);
//    cout << anUser << endl;
//    return 0;
//}
