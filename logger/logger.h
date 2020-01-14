// loggger.h 
#ifndef __LOGGER__
#define __LOGGER__

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stdint.h>
#include <string>

/**
 * type of log file
 */
typedef enum log_rank {
   INFO, 
   WARNING,
   ERROR,
   FATAL
} log_rank_t;

/**
 * Init log file
 */
void initLogger(const std::string & info_log_filename,
                const std::string & warn_log_filename,
                const std::string & error_log_filename);

/**
 * logger class
 */
class Logger
{
    friend void initLogger(const std::string& info_log_filename,
                           const std::string& warn_log_filename,
                           const std::string& error_log_filename);
public:
    Logger(log_rank_t log_rank) : m_log_rank(log_rank) {}
    ~Logger() {}
    
    /*
     *  log_rank: log grade
     *  line:   log generation line
     *  function: log generation function
     */
    static std::ostream& start(log_rank_t log_rank, 
                               const int line,
                               const std::string & function);

private:
    // get log ouput stream
    static std::ostream& getStream(log_rank_t log_rank);
 
    static std::ofstream m_info_log_file;
    static std::ofstream m_warn_log_file;
    static std::ofstream m_error_log_file;
    log_rank_t m_log_rank;
};

#define LOG(log_rank)   \
Logger(log_rank).start(log_rank, __LINE__, __FUNCTION__)

#define CHECK(a)                                \
if (!(a)) {                                     \
    LOG(ERROR) << " CHECK failed " << endl      \
                << #a << "= " << (a) << endl;   \
        abort();                                \
    }                                           

#define CHECK_NOTNULL(a)                            \
    if (NULL == (a)) {                              \
        LOG(ERROR) << " CHECK_NOTNULL failed "      \
                    << #a << "== NULL " << endl;    \
        abort();                                    \
    }                                           

#define CHECK_NULL(a)                                   \
    if (NULL != (a)) {                                  \
        LOG(ERROR) << " CHECK_NULL failed " << endl;    \
                    << #a << "!= NULL" << endl;         \
        abort();                                        \
    }

#define CHECK_EQ(a, b)                                  \
    if ( !( (a) == (b) ) ) {                            \
        LOG(ERROR) << " CHECK_EQ failed " << endl;      \
                    << #a << "= " << (a) << endl;       \
                    << #b << "= " << (b) << endl;       \
        abort();                                        \
    }

#define CHECK_NE(a, b)                                  \
    if ( !( (a) != (b) ) ) {                            \
        LOG(ERROR) << " CHECK_NE failed " << endl;      \
                    << #a << "= " << (a) << endl;       \
                    << #b << "= " << (b) << endl;       \
        abort();                                        \
    }

#define CHECK_LT(a, b)                                  \
    if ( !( (a) < (b) ) ) {                             \
        LOG(ERROR) << " CHECK_LT failed "               \
                    << #a << "= " << (a) << endl;       \
                    << #b << "= " << (b) << endl;       \
        abort();                                        \
    }

#define CHECK_GT(a, b)                                  \
    if ( !( (a) > (b) ) ) {                             \
        LOG(ERROR) << " CHECK_GT failed " << endl;      \
                    << #a << " = " << (a) << endl;      \
                    << #b << " = " << (b) << endl;      \
        abort();                                        \
    }

#define CHECK_LE(a, b)                                  \
    if ( !( (a) <= (b) ) ) {                            \
        LOG(ERROR) << " CHECK_LE failed" << endl;       \
                    << #a << " = " << (a) << endl;      \
                    << #b << " =" << (b) << endl;       \
        abort();                                        \
    }

#define CHECK_GE(a, b)                                  \
    if ( !( (a) >= (b) ) ) {                            \
        LOG(ERROR) << " CHECK_GE failed " << endl;      \
                    << #a << " = " << (a) << endl;      \
                    << #b << " = " << (b) << endl;      \
        abort();                                        \
    }

#define CHECK_DOUBLE_EQ(a, b)                           \
    do {                                                \
        CHECK_LE( (a), (b)+0.000000000000001L );        \
        CHECK_GE( (a), (b)-0.000000000000001L );        \
    } while(0)

#endif // endif __LOGGERR__
