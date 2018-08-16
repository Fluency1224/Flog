#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <getopt.h>
#include <flog.h>

char	*ProgramName;
static void usage_help(void)
{
    printf( "\033[34m%s -[] 参数 --[] 参数\033[0m\n"
            "\033[36m=============================================\033[0m\n"
            "\033[35m-h or [help]            帮助信息\033[0m\n"
            "\033[35m-v or [version]         查看版本信息\033[0m\n"
            "\033[35m-s or [set-debug-level] 设置log打印等级\033[0m\n"
            "\033[33m      可选 debug info warn error fatal none\033[0m\n"
            "\033[36m=============================================\033[0m\n"
            ,ProgramName);
    exit(EXIT_FAILURE);
}

static void  parse_args(int argc, char *argv[]) 
{
    int opt;
    int option_index = 0;
    char *optstring = "";
    struct option long_options[] = {
        {"set-debug-flags",required_argument,NULL,'s'},
        {"version",no_argument,NULL,'v'},
        {"help",no_argument,NULL,'h'},
        {0,0,0,0}
    };
    
    while((opt = getopt_long_only(argc,argv,optstring,long_options,&option_index)) != -1){
        
        switch(opt){
            case 'h':
                usage_help();
                break;
            case 'v'://查看版本号
                printf("\033[32mSOFT_VERSION:%s\n"
                        "HW_VERSION:%s\n"
                        "AUTHOR:%s\033[0m\n"
                        ,SOFT_VERSION
                        ,HW_VERSION
                        ,AUTHOR);
                exit(EXIT_FAILURE);
                break;
            case 's'://设置log等级
                if(!set_d_log_level(optarg)){
                    usage_help();
                }
                printf("\033[32m设置log打印等级为:%s\033[0m\n",optarg);
                break;
            case '?':
                printf("\033[31m无效的选项字符!\033[0m\n");
                usage_help();
                break;
            case ':':
                printf("\033[31m缺少选项参数！\033[0m\n");
                usage_help();
                break;
            default:
                printf("\033[31m参数错误\033[0m\n");
                usage_help();
                break;
        }
    }
    return;
}

int log_init()
{
    create_dir(D_LOG_PATH);
    d_log_open(D_LOG_FILE_MAIN,D_LOG_ID_MAIN);
    d_log_debug(D_LOG_ID_MAIN,"main.log 启动，日志系统开启\n");
}


int main(int argc, char** argv) 
{
    ProgramName = argv[0];//设置程序名称
    setlocale(LC_ALL, "");//字符集
    parse_args(argc, argv);//参数解析

    log_init();

    while(1){
        usleep(100000);
        d_log_debug(D_LOG_ID_MAIN,"Fluency d_log_debug\n");
        usleep(100000);
        d_log_error(D_LOG_ID_MAIN,"Fluency d_log_error\n");
        usleep(100000);
        d_log_fatal(D_LOG_ID_MAIN,"Fluency d_log_fatal\n");
        usleep(100000);
        d_log_info(D_LOG_ID_MAIN,"Fluency d_log_info\n");
        usleep(100000);
        d_log_warn(D_LOG_ID_MAIN,"Fluency d_log_warn\n");
        usleep(100000);
    }
    
    d_log_close(D_LOG_ID_MAIN);
    return (EXIT_SUCCESS);
}