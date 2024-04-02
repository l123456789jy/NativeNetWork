/*
 * @build   make examples
 *
 * @server  bin/http_server_test 8080
 *
 * @client  bin/http_client_test
 *
 */

#include "requests.h"
#include "axios.h"
using namespace hv;

#include "hthread.h" // import hv_gettid
#include <iostream>
#include <memory>

static void test_http_sync_client(HttpClient* cli) {
    HttpRequest req;
    req.method = HTTP_POST;
    req.url = "https://suggest.taobao.com/sug?code=utf-8&q=%E5%A5%B6%E7%93%B6&callback=cb";
    req.headers["Connection"] = "keep-alive";
    req.body = "This is a sync request.";
    req.timeout = 10;
    HttpResponse resp;
    int ret = cli->send(&req, &resp);
    if (ret != 0) {
        printf("request failed!\n");
    } else {
        printf("%d %s\r\n", resp.status_code, resp.status_message());
        printf("%s\n", resp.body.c_str());
    }
}

static void test_requests() {
    // auto resp = requests::get("http://www.example.com");
    //
    // make clean && make WITH_OPENSSL=yes
    // auto resp = requests::get("https://www.baidu.com");

    auto resp = requests::get("https://suggest.taobao.com/sug?code=utf-8&q=%E5%A5%B6%E7%93%B6&callback=cb");
    if (resp == NULL) {
        printf("request failed!\n");
    } else {
        printf("%d %s\r\n", resp->status_code, resp->status_message());
        printf("%s\n", resp->body.c_str());
    }

    // Content-Type: application/json
    hv::Json jroot;
    jroot["user"] = "admin";
    jroot["pswd"] = "123456";
    http_headers headers;
    headers["Content-Type"] = "application/json";
    resp = requests::post("https://suggest.taobao.com/sug?code=utf-8&q=%E5%A5%B6%E7%93%B6&callback=cb", jroot.dump(), headers);
    if (resp == NULL) {
        printf("request failed!\n");
    } else {
        printf("%d %s\r\n", resp->status_code, resp->status_message());
        printf("%s\n", resp->body.c_str());
    }

    // Content-Type: multipart/form-data
    std::map<std::string, std::string> params;
    params["user"] = "admin";
    params["pswd"] = "123456";
    resp = requests::uploadFormFile("https://suggest.taobao.com/sug?code=utf-8&q=%E5%A5%B6%E7%93%B6&callback=cb", "avatar", "avatar.jpg", params);
    if (resp == NULL) {
        printf("uploadFormFile failed!\n");
    } else {
        printf("%d %s\r\n", resp->status_code, resp->status_message());
        printf("%s\n", resp->body.c_str());
    }
    
}


int main(int argc, char* argv[]) {
    int req_cnt = 0;
    if (argc > 1) req_cnt = atoi(argv[1]);
    if (req_cnt == 0) req_cnt = 1;

    HttpClient sync_client;
    HttpClient async_client;
    int resp_cnt = 0;

    for (int i = 0; i < req_cnt; ++i) {

        test_http_sync_client(&sync_client);

        test_requests();
    }

    // demo wait async finished
    while (resp_cnt < req_cnt) hv_delay(100);
    printf("finished!\n");

    return 0;
}
