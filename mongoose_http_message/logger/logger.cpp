#include <cstdlib>
#include <ctime>
#include "logger.h"

std::ofstream Logger::m_error_log_file("error.log");
std::ofstream Logger::m_info_log_file("info.log");
std::ofstream Logger::m_warn_log_file("warning.log");

void initLogger(const std::string &info_log_filename,
                const std::string &warn_log_filename,
                const std::string &error_log_filename){
    Logger::m_info_log_file.open(info_log_filename.c_str());
    Logger::m_warn_log_file.open(warn_log_filename.c_str());
    Logger::m_error_log_file.open(error_log_filename.c_str());
}

std::ostream& Logger::getStream(log_rank_t log_rank){
    return (INFO == log_rank) ?
           (m_info_log_file.is_open() ? m_info_log_file : std::cout) :
           (WARNING == log_rank ?
            (m_warn_log_file.is_open() ? m_warn_log_file : std::cerr) :
            (m_error_log_file.is_open() ?  m_error_log_file : std::cerr));
}

std::ostream& Logger::start(log_rank_t log_rank,
                            const int line,
                            const std::string &function)
{
    time_t tm;
    time(&tm);
    char time_string[35];
    ctime_r(&tm, time_string);
    time_t t = time(0);
    char ch[64];
    strftime(ch, sizeof(ch), "[%Y-%m-%d %H-%M-%S]", localtime(&t));
    return getStream(log_rank) << ch << " line " << line << " "
                               << "function (" << function << ") "
                               << std::flush;
}

Logger::~Logger(){
    getStream(m_log_rank)  << std::flush;

    if (FATAL == m_log_rank) {
        m_info_log_file.close();
        m_info_log_file.close();
        m_info_log_file.close();
        abort();
    }
}
