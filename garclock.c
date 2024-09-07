#include <stdio.h>


#ifdef _WIN32
    #include <windows.h>
#endif



const char ascii_zero[101]  = " 00000000 " \
                              "0000000000" \
                              "000    000" \
                              "00      00" \
                              "00      00" \
                              "00      00" \
                              "00      00" \
                              "000    000" \
                              "0000000000" \
                              " 00000000 "

const char ascii_one[101]   = "   1111   " \
                              " 111111   " \
                              "   1111   " \
                              "   1111   " \
                              "   1111   " \
                              "   1111   " \
                              "   1111   " \
                              "   1111   " \
                              " 11111111 " \
                              "1111111111"

const char ascii_two[101]   = "  22222   " \
                              "  222222  " \
                              "222    222" \
                              "222    222" \
                              "      2222" \
                              "    2222  " \
                              "   2222   " \
                              "  2222    " \
                              "2222222222" \
                              "2222222222"

const char ascii_three[101] = " 333333333" \
                              "3333333333" \
                              "        33" \
                              "       333" \
                              " 333333333" \
                              "3333333333" \
                              "        33" \
                              "       333" \
                              " 333333333" \
                              "3333333333"

const char ascii_four[101]  = "    444444" \
                              "   4444444" \
                              "  444  444" \
                              " 444   444" \
                              "444    444" \
                              "4444444444" \
                              "4444444444" \
                              "       444" \
                              "       444" \
                              "       444"

const char ascii_five[101]  = "5555555555" \
                              "5555555555" \
                              "555       " \
                              "555       " \
                              " 55555555 " \
                              "   5555555" \
                              "       555" \
                              "555    555" \
                              "5555555555" \
                              " 55555555 "

const char ascii_six[101]   = " 66666666 " \
                              "6666666666" \
                              "666    666" \
                              "666       " \
                              "666666666 " \
                              "6666666666" \
                              "66      66" \
                              "66      66" \
                              "6666666666" \
                              " 66666666 "

const char ascii_seven[101] = "777777777 " \
                              "7777777777" \
                              "       777" \
                              "       777" \
                              "       777" \
                              "      777 " \
                              "     777  " \
                              "     777  " \
                              "     777  " \
                              "     777  "

const char ascii_eight[101] = " 88888888 " \
                              "8888888888" \
                              "88      88" \
                              "88      88" \
                              " 88888888 " \
                              " 88888888 " \
                              "88      88" \
                              "88      88" \
                              "8888888888" \
                              " 88888888 "

const char ascii_nine[101]  = " 99999999 " \
                              "9999999999" \
                              "99      99" \
                              "99      99" \
                              "9999999999" \
                              " 999999999" \
                              "       999" \
                              "999    999" \
                              "9999999999" \
                              " 99999999 "


const char ascii_colon[101]  = "   ::::   " \
                               "   ::::   " \
                               "   ::::   " \
                               "   ::::   " \
                               "          " \
                               "          " \
                               "   ::::   " \
                               "   ::::   " \
                               "   ::::   " \
                               "   ::::   "

const char ascii_slash[101]  = "        //" \
                               "       ///" \
                               "      /// " \
                               "     ///  " \
                               "    ///   " \
                               "   ///    " \
                               "  ///     " \
                               " ///      " \
                               "///       " \
                               "//        "

const char ascii_period[101]  = "          " \
                                "          " \
                                "          " \
                                "          " \
                                "          " \
                                "          " \
                                "   ....   " \
                                "   ....   " \
                                "   ....   " \
                                "   ....   "



void clear_screen(void)
{
    fprintf(stderr, ("\033[2J\033[H"));
}



int main(void)
{

    // Microshit wants us to explicitly enable ANSI functionality.
    #ifdef _WIN32

        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return 1;

        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) return 1;

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        if (!SetConsoleMode(hOut, dwMode)) return 1;

    #elif !defined(__unix__)

        #warning "Only written to support windows and unix-like systems."

    #endif





    return 0;
}