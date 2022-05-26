#include "api.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}


int request(const string &URL, const vector<string> &EHeaders, string &readBuffer, string type, string postParameters) {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        const char *constURL = URL.c_str();
        curl_easy_setopt(curl, CURLOPT_URL, constURL);
        for (int i = 0; i < EHeaders.size(); i++)
        {
            const char *constHeader = EHeaders[i].c_str();
            headers = curl_slist_append(headers, constHeader);
        }
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        if(type == "post"){
            std::cout << postParameters <<std::endl;
            const char *constpostParameters = postParameters.c_str();
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, constpostParameters);
        }
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);     
    }
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return -1;
    }
    curl_global_cleanup();
    return 1;
}