#ifndef FLOG_H
#define FLOG_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


#ifdef __cplusplus
extern "C" {
#endif


//版本信息为8字节
#define SOFT_VERSION "20180816"
#define HW_VERSION   "20180502"
#define AUTHOR       "Fluency"


/**
 * \\：反斜线本身
 * \a：ALERT / BELL (从系统喇叭送出铃声)
 * \b：BACKSPACE，退格键
 * \c：取消行末换行符号（跟-n的作用一样）
 * \e：ESCAPE键
 * \f：FORMFEED，换页字符
 * \n：NEWLINE，换行字符
 * \r：RETURN，回车键
 * \t：TAB，表格跳位键
 * \v：VERTICAL TAB，垂直表格跳位键
 * 
 * 颜色宏  \e[显示方式;前景色;背景色m
 * 显示方式：0(默认)、1(粗体/高亮)、22(非粗体)、4(单条下划线)、24(无下划线)、5(闪烁)、25(无闪烁)、7(反显、翻转前景色和背景色)、27(无反显)
 * 颜色：0(黑)、1(红)、2(绿)、 3(黄)、4(蓝)、5(洋红)、6(青)、7(白)
 * 前景色为30+颜色值，如31表示前景色为红色；
 * 背景色为40+颜色值，如41表示背景色为红色。
 */
#define D_LOG_C_START      "\e["            //  ESCAPE键
#define D_LOG_C_AND        ";"
#define D_LOG_C_END        "m"
    
#define D_LOG_C_FORMAT_ZERO         D_LOG_C_START "0" D_LOG_C_END   //默认
#define D_LOG_C_FORMAT_BOLD         D_LOG_C_START "1" D_LOG_C_END   //粗体/高亮
#define D_LOG_C_FORMAT_NBOLD        D_LOG_C_START "22" D_LOG_C_END  //非粗体
#define D_LOG_C_FORMAT_UNDERLINE    D_LOG_C_START "4" D_LOG_C_END   //单条下划线
#define D_LOG_C_FORMAT_NDERLINE     D_LOG_C_START "24" D_LOG_C_END  //无下划线
#define D_LOG_C_FORMAT_BLINK        D_LOG_C_START "5" D_LOG_C_END   //闪烁
#define D_LOG_C_FORMAT_NBLINK       D_LOG_C_START "25" D_LOG_C_END  //无闪烁
#define D_LOG_C_FORMAT_REVERSE      D_LOG_C_START "7" D_LOG_C_END   //反显、翻转前景色和背景色
#define D_LOG_C_FORMAT_NREVERSE     D_LOG_C_START "27" D_LOG_C_END  //无反显

    //前景色
#define D_LOG_C_FOREC_BLACK         D_LOG_C_START "30" D_LOG_C_END
#define D_LOG_C_FOREC_RED           D_LOG_C_START "31" D_LOG_C_END
#define D_LOG_C_FOREC_GREEN         D_LOG_C_START "32" D_LOG_C_END
#define D_LOG_C_FOREC_YELLOW        D_LOG_C_START "33" D_LOG_C_END
#define D_LOG_C_FOREC_BLUE          D_LOG_C_START "34" D_LOG_C_END
#define D_LOG_C_FOREC_MAGENTA       D_LOG_C_START "35" D_LOG_C_END
#define D_LOG_C_FOREC_CYAN          D_LOG_C_START "36" D_LOG_C_END
#define D_LOG_C_FOREC_WHITE         D_LOG_C_START "37" D_LOG_C_END
    
    //背景色
#define D_LOG_C_BGC_BLACK           D_LOG_C_START "30" D_LOG_C_END
#define D_LOG_C_BGC_RED             D_LOG_C_START "31" D_LOG_C_END
#define D_LOG_C_BGC_GREEN           D_LOG_C_START "32" D_LOG_C_END
#define D_LOG_C_BGC_YELLOW          D_LOG_C_START "33" D_LOG_C_END
#define D_LOG_C_BGC_BLUE            D_LOG_C_START "34" D_LOG_C_END
#define D_LOG_C_BGC_MAGENTA         D_LOG_C_START "35" D_LOG_C_END
#define D_LOG_C_BGC_CYAN            D_LOG_C_START "36" D_LOG_C_END
#define D_LOG_C_BGC_WHITE           D_LOG_C_START "37" D_LOG_C_END
    
//其他功能码
//#define D_LOG_C_S_NONE              D_LOG_C_START D_LOG_C_FORMAT_ZERO D_LOG_C_END   //默认格式，用在打印最后作用清除之前的格式
#define D_LOG_C_S_NONE              "\e[0m"
#define D_LOG_C_CTL_A(num)          D_LOG_C_START num "A"               //\e[nA 上移n行 \e[10A
#define D_LOG_C_CTL_B(num)          D_LOG_C_START num "B"               //\e[nB 下
#define D_LOG_C_CTL_C(num)          D_LOG_C_START num "C"               //\e[nC 右
#define D_LOG_C_CTL_D(num)          D_LOG_C_START num "D"               //\e[nC 左
#define D_LOG_C_CTL_XYZ(x,y)        D_LOG_C_START x D_LOG_C_AND y "H"   //设置光标位置
#define D_LOG_C_CTL_CLEAR           D_LOG_C_START "2J"                  //清屏
#define D_LOG_C_CTL_CLRLINE         D_LOG_C_START "K"                   //清除从光标到行尾的内容
#define D_LOG_C_CTL_S               D_LOG_C_START "s"                   //保存光标位置
#define D_LOG_C_CTL_U               D_LOG_C_START "u"                   //恢复光标位置
#define D_LOG_C_CTL_L               D_LOG_C_START "?25l"                //隐藏光标   
#define D_LOG_C_CTL_H               D_LOG_C_START "?25h"                //显示光标
    


//log文件 PATH
// #define D_LOG_PATH "/var/log/Flog/"
// #define D_LOG_FILE_MAIN "/var/log/Flog/main.log"
// #define D_LOG_ID_MAIN 1
#define D_LOG_PATH "/home/fluency/workspace/Flog/dist/"
#define D_LOG_FILE_MAIN "/home/fluency/workspace/Flog/dist/main.log"
#define D_LOG_ID_MAIN 1
/*
 * 打印等级 
 */
enum D_LOG_LEVEL{
    D_LOG_LEVEL_DEBUG = 0,
    D_LOG_LEVEL,      //无额外信息
    D_LOG_LEVEL_INFO,
    D_LOG_LEVEL_WARN,
    D_LOG_LEVEL_ERROR,
    D_LOG_LEVEL_FATAL,
    D_LOG_LEVEL_NONE,
};
/**
 * 设置和获取log等级
 * @return 
 */
enum D_LOG_LEVEL get_d_log_level(void );
int set_d_log_level(const char *f);

/**
 * 检查log目录是否存在，不存在则创建
 * @param path
 * @return 
 */
int create_dir(char *path);

//标准输出，使用标准输出，使用 set_d_fp(D_LOG_ID_STDOUT,stdout); 初始化标准输出
#define D_LOG_ID_STDOUT 0
#define D_LOG_FILE_NUM 10
#define D_LOG_FILE_SIZE (1024*1000)//设置log文件大小

/**
 * 设置和获取log文件描述符
 */
//inline FILE* get_d_fp(int id);
int set_d_fp(int id,FILE* fp);

extern int d_log_open(const char *filename,int id);        
extern int d_log_close(int id);

#if 0
    #define __D_LOG__FILE__ ("-")
#endif
#if 1
    #define __D_LOG__FILE__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#endif 
#if 0
    #define __D_LOG__FILE__ __FILE__
#endif


extern int d_logp(int id,enum D_LOG_LEVEL level,const char *format,...);
#define d_log(id,format,...) \
            do{\
                d_logp(id,D_LOG_LEVEL,format,##__VA_ARGS__);\
            }while(0)
#define d_log_debug(id,format,...) \
            do{\
                d_logp(id,D_LOG_LEVEL_DEBUG, "[%s:%d]: "  format,__D_LOG__FILE__,__LINE__,##__VA_ARGS__);\
            }while(0)
#define d_log_info(id,format,...) \
            do{\
                d_logp(id,D_LOG_LEVEL_INFO, "[%s:%d]: "  format,__D_LOG__FILE__,__LINE__,##__VA_ARGS__);\
            }while(0)
#define d_log_warn(id,format,...) \
            do{\
                d_logp(id,D_LOG_LEVEL_WARN, "[%s:%d]: "  format,__D_LOG__FILE__,__LINE__,##__VA_ARGS__);\
            }while(0)
#define d_log_error(id,format,...) \
            do{\
                d_logp(id,D_LOG_LEVEL_ERROR, "[%s:%d]: "  format,__D_LOG__FILE__,__LINE__,##__VA_ARGS__);\
            }while(0)
#define d_log_fatal(id,format,...) \
            do{\
                d_logp(id,D_LOG_LEVEL_FATAL, "[%s:%d]: "  format,__D_LOG__FILE__,__LINE__,##__VA_ARGS__);\
            }while(0)

//打印 str : xx xx xx xx xx xx xx xx
int d_log_debug_strtohex(int id,char *str,int str_len,char *__c,int __cmaxlen);

#ifdef __cplusplus
}
#endif

#endif /* FLOG_H */

