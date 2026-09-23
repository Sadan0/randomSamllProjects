/* Windows-friendly minimal HTTP server for BUG HUNT. Compile with MinGW GCC.
   It serves the frontend and calculates totals. See README for commands. */
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib")
void send_reply(SOCKET c,const char* body,const char* type){char h[256];sprintf(h,"HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\nConnection: close\r\n\r\n",type,(int)strlen(body));send(c,h,(int)strlen(h),0);send(c,body,(int)strlen(body),0);}
int main(){WSADATA w;WSAStartup(MAKEWORD(2,2),&w);SOCKET s=socket(AF_INET,SOCK_STREAM,0);struct sockaddr_in a={0};a.sin_family=AF_INET;a.sin_port=htons(5000);a.sin_addr.s_addr=htonl(INADDR_ANY);bind(s,(struct sockaddr*)&a,sizeof(a));listen(s,10);printf("Open http://localhost:5000\n");while(1){SOCKET c=accept(s,0,0);char r[8192]={0};recv(c,r,sizeof(r)-1,0);if(strncmp(r,"GET /api/calculate?subtotal=",28)==0){char* p=strchr(r,'=')+1;double s0=atof(p),d=s0>=10000?s0*.10:0,t=(s0-d)*.18,total=s0-d+t;char out[512];sprintf(out,"{\"subtotal\":%.2f,\"discount\":%.2f,\"tax\":%.2f,\"total\":%.2f}",s0,d,t,total);send_reply(c,out,"application/json");}else{FILE*f=fopen("index.html","rb");char body[20000]={0};int n=fread(body,1,sizeof(body)-1,f);fclose(f);body[n]=0;send_reply(c,body,"text/html");}closesocket(c);}return 0;}
