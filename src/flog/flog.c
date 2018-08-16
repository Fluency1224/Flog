
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <flog.h>

int create_dir(char *path)
{
    if(access(path,F_OK) == 0){
        return 0;//存在
    }else{//不存在创建
        return mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
}

static enum D_LOG_LEVEL m_d_log_level = D_LOG_LEVEL_WARN;
enum D_LOG_LEVEL get_d_log_level(void)
{
    return m_d_log_level;
}
int set_d_log_level(const char *f)
{
    const char *flags = f;
    switch(flags[0]){
        case 'd':
            if(strcmp("debug",flags) != 0){
                return false;
            }
            m_d_log_level = D_LOG_LEVEL_DEBUG;
            break;
        case 'i':
            if(strcmp("info",flags) != 0){
                return false;
            }
            m_d_log_level = D_LOG_LEVEL_INFO;
            break;
        case 'w':
            if(strcmp("warn",flags) != 0){
                return false;
            }
            m_d_log_level = D_LOG_LEVEL_WARN;
            break;
        case 'e':
            if(strcmp("error",flags) != 0){
                return false;
            }
            m_d_log_level = D_LOG_LEVEL_ERROR;
            break;
        case 'f':
            if(strcmp("fatal",flags) != 0){
                return false;
            }
            m_d_log_level = D_LOG_LEVEL_FATAL;
            break;
        case 'n':
            if(strcmp("none",flags) != 0){
                return false;
            }
            m_d_log_level = D_LOG_LEVEL_NONE;
            break;
        default:
            return false;
            break;
    }
    return true;
}

static FILE *D_LOG_FP[D_LOG_FILE_NUM] = {NULL};//设置日志文件个数
//D_LOG_FP[D_LOG_ID_STDOUT] = stdout;

int set_d_fp(int id,FILE* fp)
{
    if(id >= (sizeof(D_LOG_FP)/sizeof(FILE *))){
        //fclose(fp);
        return -1;
    }
    D_LOG_FP[id] = fp;
    return 0;
}
int d_log_open(const char *filename,int id)
{
    if(id >= (sizeof(D_LOG_FP)/sizeof(FILE *))){
        //fclose(fp);
        return -1;
    }
    D_LOG_FP[id] = fopen(filename,"w");
    if(D_LOG_FP[id] == NULL){
        return -1;
    }
    return 0;
}
int d_log_close(int id)
{
    fclose(D_LOG_FP[id]);
    D_LOG_FP[id] = NULL;
    return 0;
}

int d_logp(int id,enum D_LOG_LEVEL level,const char *format,...)
{
    if(level < m_d_log_level){
        return 0;
    }
    if(ftell(D_LOG_FP[id]) > D_LOG_FILE_SIZE){
        ftruncate(fileno(D_LOG_FP[id]), 0);
        fseek(D_LOG_FP[id],0,SEEK_SET);
    }
    
    switch(level){
        case D_LOG_LEVEL_DEBUG:
            fprintf(D_LOG_FP[id],D_LOG_C_BGC_BLUE D_LOG_C_FORMAT_BLINK "[debug]" );
            break;
        case D_LOG_LEVEL_INFO:
            fprintf(D_LOG_FP[id],D_LOG_C_BGC_YELLOW "[info]");
            break;
        case D_LOG_LEVEL_WARN:
            fprintf(D_LOG_FP[id],D_LOG_C_BGC_MAGENTA "[warn]");
            break;
        case D_LOG_LEVEL_ERROR:
            fprintf(D_LOG_FP[id],D_LOG_C_BGC_MAGENTA D_LOG_C_FORMAT_BOLD D_LOG_C_FORMAT_BLINK "[error]");
            break;
        case D_LOG_LEVEL_FATAL:
            fprintf(D_LOG_FP[id],D_LOG_C_BGC_RED D_LOG_C_FORMAT_BOLD D_LOG_C_FORMAT_BLINK "[fatal]");
            break;
        case D_LOG_LEVEL:
            break;
        default:
            break;
    }
    int ret = 0;
    va_list vp;
    va_start(vp,format);
    ret = vfprintf(D_LOG_FP[id],format,vp);
    va_end(vp);
    fprintf(D_LOG_FP[id],D_LOG_C_S_NONE);
    fflush(D_LOG_FP[id]);
    
    return ret;
}

int d_log_debug_strtohex(int id,char *str,int str_len,char *__c,int __cmaxlen)
{
    d_logp(id,D_LOG_LEVEL,"%s",str);
        int i = 0;
        for(i = 0;i < __cmaxlen;i++){
            d_logp(id,D_LOG_LEVEL," %02X ",__c[i]);
        }
        d_logp(id,D_LOG_LEVEL,"\n");
	return 0;
}
