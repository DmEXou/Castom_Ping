#include "pingwindow.h"

#include <QApplication>
#include <QLabel>
#include <QLocale>
#include <QTranslator>
//#include <iostream>
//#include <exception>
//#include <string>
/*
#include "winsock2.h"
#include "iphlpapi.h"
#include "icmpapi.h"

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

namespace VSping {

class Test_Error {
public:
    void Test_Handle(HANDLE& handle) {
        if (handle == INVALID_HANDLE_VALUE) {
            auto msg_error = GetLastError();
            std::cout << "\tUnable to open handle.\n";
            std::cout << "IcmpCreatefile returned error: %ld\n", msg_error;
            throw std::exception();
        }
    }
    void Test_Adress(IPAddr& addr) {
        if (addr == INADDR_NONE) {
            std::cout << "usage: %s IP address\n" << addr;
            throw std::exception();
        }
    }
    void Test_Lpvoid(LPVOID& lp_buf) {
        if (lp_buf == NULL) {
            std::cout << "\tUnable to allocate memory\n";
            throw std::exception();
        }
    }
};

class Castom_Ping {
public:
    Castom_Ping(const std::vector<std::string>& ip_adress, int time = 1000)
        :cont_ip_adress(ip_adress)
        ,response_time(time)
    {
    }

    int ping_adress(const std::string& ip) {
        Test_Error test;
        HANDLE handle;
        handle = IcmpCreateFile();
        test.Test_Handle(handle);

        IPAddr addr;
        std::string strr(ip);
        addr = inet_addr(&strr[0]);
        test.Test_Adress(addr);

        std::string str = "msg";

        LPVOID lp_reqest_data = &str;

        WORD word = sizeof(lp_reqest_data);

        PIP_OPTION_INFORMATION pip = NULL;

        DWORD ReplySize = 0;
        ReplySize = sizeof(ICMP_ECHO_REPLY) + word;

        LPVOID lp_buf = NULL;
        lp_buf = (VOID*)malloc(ReplySize);
        test.Test_Lpvoid(lp_buf);

        DWORD ping = IcmpSendEcho(handle, addr, lp_reqest_data, word, pip, lp_buf, ReplySize, response_time);

        //PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)lp_buf;
        //struct in_addr ReplyAddr;
        //ReplyAddr.S_un.S_addr = pEchoReply->Address;

        return ping;
    }

    std::vector<int> bild(){
        std::vector<int> fin = {};
        for(const auto& ip: cont_ip_adress){
            fin.push_back(ping_adress(ip));
        }
        return fin;
    }

private:
    std::vector<std::string> cont_ip_adress;
    int response_time;
};
}//VSping
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Castom_Ping_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    PingWindow w;
    w.show();

    return a.exec();
}
