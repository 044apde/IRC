**[Info]**  
RFC IRC 기반 서버 프로그램입니다.  
단일 서버를 제공합니다.  
클라이언트 프로그램 IRSSI와 호환됩니다.  
BSD OS가 제공하는 KQUEUE 커널 이벤트 알림 API가 사용되었습니다.  
LINUX에서 사용하기 위해서는 이벤트 알림 API를 select OR epoll로 변경해야합니다.
BUILD SYSTEM: intel mac os  

**[Usage]**  
make  
./irc [port(클라이언트가 접근할 포트)] [pwd(ICR 서버가 사용할 비밀번호)]   
