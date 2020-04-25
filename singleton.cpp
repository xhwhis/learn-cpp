#include <iostream>
#include <mutex>
using namespace std;

class HttpServer {
public:
    static HttpServer *getInstance() {
        if (instance == nullptr) {
            unique_lock<mutex> lock(m_mutex);
            if (instance == nullptr) {
                instance = new HttpServer();
            }
        }
        return instance;
    }

private:
    HttpServer() {}
    HttpServer(const HttpServer &) = delete;
    //~HttpServer() = delete;
    static HttpServer *instance;
    static mutex m_mutex;
};

HttpServer *HttpServer::instance =  nullptr;
mutex HttpServer::m_mutex;

int main() {
    HttpServer *t1 = HttpServer::getInstance();
    //delete t1;
    HttpServer *t2 = HttpServer::getInstance();
    cout << t1 << '\n' << t2 << endl;
    return 0;
}
