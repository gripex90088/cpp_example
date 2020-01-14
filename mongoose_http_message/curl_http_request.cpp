#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>

using namespace std;

size_t write_download(char *buffer, size_t size, size_t nmemb, void *stream)
{
    FILE *fptr = (FILE *)stream;
    fwrite(buffer, size, nmemb, fptr);

    return size*nmemb;
}


/**
 * @param url   download url
 * @param localFileName local file path
 * @return
 */
bool curlDownload(const char *url, char *localFileName)
{
    if (url == NULL) {
        return false;
    }

    FILE *fptr;
    CURL *curl;
    CURLcode codeRet;

    curl = curl_easy_init();
    if (NULL == curl) {
        return false;
    }

    if (NULL == (fptr = fopen(localFileName, "w"))) {
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_download);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fptr);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, true);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, true);

    long code = 0;
    codeRet = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
    curl_easy_cleanup(curl);
    fclose(fptr);

    if (codeRet == CURLE_OK && (code == 200 || code == 304 || code == 204)) {
    } else {
        return false;
    }

    return true;
}


size_t write_data_json(char *buffer, size_t size, size_t nmemb, ostringstream &stream)
{
    stream << buffer;
    return size*nmemb;
}

/*
 * curl post binary image
*/
bool curl_post_file_octet(char *url, char *fileName, string data, int dataLen, ostringstream &string)
{
    CURL *curl;
    CURLcode res;
    struct  curl_httppost *formpost = 0;
    struct	curl_httppost *lastptr = 0;
    curl = curl_easy_init();

    if (!curl) {
        goto end;
    }

    curl_formadd(&formpost, &lastptr,
                 CURLFORM_COPYNAME, fileName,
                 CURLFORM_BUFFER, fileName,
                 CURLFORM_BUFFERPTR, data.c_str(),
                 CURLFORM_BUFFERLENGTH,dataLen,
            //CURLFORM_CONTENTTYPE, "application/octet-stream",
                 CURLFORM_END
    );

    curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_json);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &string);
    curl_easy_setopt(curl, CURLOPT_URL, url);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        goto end;
    }

    curl_easy_cleanup(curl);
    curl_formfree(formpost);
    return true;

    end:
    curl_easy_cleanup(curl);
    curl_formfree(formpost);
    return false;
}
