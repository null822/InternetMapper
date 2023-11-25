#include <iostream>
#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <cstdio>
#include <future>
#include <thread>

#include "ColoredText.h"

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")

class InternetMapper {

    const bool debug = true;

    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE icmp_handle = IcmpCreateFile();

    char send_data[32] = "Data Buffer";
    long reply_size = sizeof(ICMP_ECHO_REPLY) + sizeof(send_data);
    void* reply_buffer = malloc(reply_size);

public:
    int Main() {

        for (int i = 0; i < 16; i++) {

            SetConsoleTextAttribute(console_handle, TextColor(i, i).Get());
            std::cout << "Fancy Text" << std::endl;

        }



        const char* ip_arr[] = {"60.240.109.117", "69.69.69.69", "8.8.8.8", "notanip"};


        if (icmp_handle == INVALID_HANDLE_VALUE) {
            printf("\tUnable to open handle.\n");
            printf("IcmpCreatefile returned error: %ld\n", GetLastError() );
            return 2;
        }

        if (reply_buffer == nullptr) {
            printf("\tUnable to allocate replyBuffer memory\n");
            return 3;
        }

        std::future<PICMP_ECHO_REPLY>* futures[sizeof(ip_arr)];

        int i = 0;
        for (const auto ip_string: ip_arr) {

            auto future = std::async(Ping, this, ip_string, 1000);

            futures[i] = &future;

            i++;
        }
        PrintColor(14, "created threads");

        for (const auto future: futures) {

            const auto result = future->get();

            printf("%lu\n", result->RoundTripTime);
        }

        return 0;
    }

private:

    PICMP_ECHO_REPLY Ping(const char* ip_string, const long timeout) {

        const IPAddr ip_adress = inet_addr(ip_string);

        const DWORD reply_count = IcmpSendEcho(
            icmp_handle,
            ip_adress,
            send_data,
            sizeof(send_data),
            nullptr,
            reply_buffer,
            reply_size,
            timeout
            );

        // if we got any responses
        if (reply_count != 0) {

            const auto reply = static_cast<PICMP_ECHO_REPLY>(reply_buffer);
            in_addr replyAddr{};
            replyAddr.S_un.S_addr = reply->Address;

            PrintColor(10, "Received from %s\n", inet_ntoa(replyAddr));
            PrintColor(15, "\tStatus = %ld\n", reply->Status);
            PrintColor(15, "\tRoundtrip time = %ld milliseconds\n", reply->RoundTripTime);
            PrintColor(15, "\tIntegrity = %s\n", reply->Data);

            return reply;
        }
        // otherwise, display the error

        PrintColor(14, "Error from %s: %ld\n", ip_string, GetLastError());

        return nullptr;
    }

    void PrintColor(const int color, const char *text, ...) {

        __builtin_va_list local_argv;
        __builtin_va_start( local_argv, text );
        __builtin_va_end( local_argv );

        SetConsoleTextAttribute(console_handle, color);
        __mingw_vfprintf(stdout, text, local_argv);
        SetConsoleTextAttribute(console_handle, 15); // reset color to white
    }

    void PrintIntegrity(const char* original, const char* damaged) {

    }

};


int main()
{
    auto main = InternetMapper();
    return main.Main();
}
