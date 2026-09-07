#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 3000
#define BUFFER_SIZE 4096

// HTML Response
const char* get_html_response() {
    return 
        "<!DOCTYPE html>"
        "<html lang='id'>"
        "<head>"
        "    <meta charset='UTF-8'>"
        "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>"
        "    <title>Operating Systems by Domain</title>"
        "    <style>"
        "        * { margin: 0; padding: 0; box-sizing: border-box; }"
        "        body {"
        "            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;"
        "            background: linear-gradient(135deg, #0f0c29, #302b63, #24243e);"
        "            min-height: 100vh;"
        "            display: flex;"
        "            justify-content: center;"
        "            align-items: center;"
        "            padding: 20px;"
        "        }"
        "        .container {"
        "            background: rgba(255, 255, 255, 0.95);"
        "            border-radius: 20px;"
        "            padding: 40px;"
        "            max-width: 900px;"
        "            width: 100%;"
        "            box-shadow: 0 20px 60px rgba(0,0,0,0.7);"
        "        }"
        "        h1 {"
        "            text-align: center;"
        "            font-size: 2.2em;"
        "            color: #1a1a2e;"
        "            margin-bottom: 30px;"
        "            border-bottom: 4px solid #302b63;"
        "            padding-bottom: 15px;"
        "        }"
        "        .domain-card {"
        "            display: flex;"
        "            justify-content: space-between;"
        "            align-items: center;"
        "            padding: 16px 20px;"
        "            margin: 10px 0;"
        "            background: #f8f9fc;"
        "            border-radius: 12px;"
        "            border-left: 6px solid #302b63;"
        "            transition: all 0.3s ease;"
        "        }"
        "        .domain-card:hover {"
        "            transform: translateX(8px);"
        "            box-shadow: 0 4px 15px rgba(48, 43, 99, 0.2);"
        "        }"
        "        .domain-label {"
        "            font-weight: 700;"
        "            font-size: 1.1em;"
        "            color: #1a1a2e;"
        "            min-width: 140px;"
        "        }"
        "        .domain-desc {"
        "            color: #555;"
        "            font-size: 0.95em;"
        "            flex: 1;"
        "            padding: 0 15px;"
        "        }"
        "        .domain-os {"
        "            font-weight: 700;"
        "            font-size: 1.2em;"
        "            color: #302b63;"
        "            background: #e8e6f0;"
        "            padding: 6px 18px;"
        "            border-radius: 30px;"
        "        }"
        "        .domain-os.windows { color: #0078d4; background: #e3f0ff; }"
        "        .domain-os.android { color: #3ddc84; background: #e6f9ed; }"
        "        .domain-os.linux { color: #f48024; background: #fff4e6; }"
        "        .domain-os.kali { color: #557c94; background: #eaf0f5; }"
        "        .domain-os.rtos { color: #e74c3c; background: #fde8e6; }"
        "        .domain-os.embedded { color: #2ecc71; background: #e8f8ef; }"
        "        .domain-os.dos { color: #7f8c8d; background: #ecf0f1; }"
        "        .footer {"
        "            text-align: center;"
        "            margin-top: 25px;"
        "            color: #999;"
        "            font-size: 0.85em;"
        "            border-top: 1px solid #ddd;"
        "            padding-top: 20px;"
        "        }"
        "        .footer span { color: #302b63; font-weight: 600; }"
        "        @media (max-width: 650px) {"
        "            .domain-card { flex-wrap: wrap; }"
        "            .domain-desc { padding: 8px 0; flex-basis: 100%; }"
        "            .domain-os { margin-left: auto; }"
        "        }"
        "    </style>"
        "</head>"
        "<body>"
        "    <div class='container'>"
        "        <h1>🖥️ Operating Systems by Domain</h1>"
        "        <div class='domain-card'>"
        "            <span class='domain-label'>Desktop</span>"
        "            <span class='domain-desc'>Personal computers & laptops</span>"
        "            <span class='domain-os windows'>WINDOWS</span>"
        "        </div>"
        "        <div class='domain-card'>"
        "            <span class='domain-label'>Mobile</span>"
        "            <span class='domain-desc'>Smartphones, tablets & mobile devices</span>"
        "            <span class='domain-os android'>ANDROID</span>"
        "        </div>"
        "        <div class='domain-card'>"
        "            <span class='domain-label'>Server</span>"
        "            <span class='domain-desc'>Servers, cloud computing & enterprise applications</span>"
        "            <span class='domain-os linux'>LINUX</span>"
        "        </div>"
        "        <div class='domain-card'>"
        "            <span class='domain-label'>Cybersecurity</span>"
        "            <span class='domain-desc'>Ethical hacking, penetration testing & security analysis</span>"
        "            <span class='domain-os kali'>KALI LINUX</span>"
        "        </div>"
        "        <div class='domain-card'>"
        "            <span class='domain-label'>RTOS</span>"
        "            <span class='domain-desc'>Real-time systems requiring immediate response</span>"
        "            <span class='domain-os rtos'>FREERTOS</span>"
        "        </div>"
        "        <div class='domain-card'>"
        "            <span class='domain-label'>Embedded</span>"
        "            <span class='domain-desc'>Dedicated devices like routers, TVs & ATMs</span>"
        "            <span class='domain-os embedded'>EMBEDDED LINUX</span>"
        "        </div>"
        "        <div class='domain-card'>"
        "            <span class='domain-label'>Legacy</span>"
        "            <span class='domain-desc'>Older computer operating systems</span>"
        "            <span class='domain-os dos'>MS-DOS</span>"
        "        </div>"
        "        <div class='footer'>"
        "            <span>/nameforge</span> &bull; Built with C"
        "        </div>"
        "    </div>"
        "</body>"
        "</html>";
}

void* handle_client(void* arg) {
    int client_fd = *(int*)arg;
    free(arg);

    char buffer[BUFFER_SIZE];
    read(client_fd, buffer, BUFFER_SIZE - 1);

    const char* html = get_html_response();
    char response[BUFFER_SIZE + 1024];

    snprintf(response, sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        strlen(html), html
    );

    write(client_fd, response, strlen(response));
    close(client_fd);

    return NULL;
}

int main() {
    int server_fd, *client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket option
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("✅ Server running on http://localhost:%d\n", PORT);
    printf("   Press Ctrl+C to stop\n");

    while (1) {
        client_fd = malloc(sizeof(int));
        if ((*client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            free(client_fd);
            continue;
        }

        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, client_fd);
        pthread_detach(thread);
    }

    close(server_fd);
    return 0;
}