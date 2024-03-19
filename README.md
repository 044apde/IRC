✅ U CAN USE ON MAC OS, BSD OS  

❌ U CAN'T USE ON LINUX 

DEV LOG [링크](https://maroon-face-0e4.notion.site/IRC-server-Socket-TCP-IP-RFC-IRC-0ea29959831848ff91ee8da86da4f85a?pvs=4)


**[Info]**  
RFC IRC 기반 서버 프로그램입니다.  
단일 서버를 제공합니다.  
클라이언트 프로그램 IRSSI와 호환됩니다.
BSD OS가 제공하는 KQUEUE 커널 이벤트 알림 API가 사용되었습니다.  
LINUX에서 사용하기 위해서는 이벤트 알림 API를 select OR epoll로 변경해야합니다.

**[Usage]**  
make  
./irc [port] [pwd]  
