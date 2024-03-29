# Game_Server_Study

# Mento : m-jacking75
- [게임서버 만들기](https://docs.google.com/presentation/d/14_gxv8RbwDW_zVhq7kk-FJ62_floC9kZx9E6OWt4mWU/edit?usp=sharing )    
- [게임서버 만들기 - 기초 학습](https://docs.google.com/presentation/d/1qT7rgZeZARd_-wBgCAQrUb6aT_evHjuEAxexhWOIYcU/edit?usp=sharing )  
  
  
## 학습 자료 
- [(유튜브) 네트워크 기초(개정판)](https://www.youtube.com/playlist?app=desktop&list=PL0d8NnikouEWcF1jJueLdjRIC4HsUlULi)    
- [(C#) WinForms 프로그래밍](http://www.csharpstudy.com/WinForms/WinForms-Intro.aspx )  
- [(인프런 무료) C# 처음부터 배우기](https://inf.run/zQzN )
- [(인프런 무료) C# 프로그래밍](https://inf.run/VLuv )  
- [(인프런 무료) C# 네트워크 프로그래밍](https://inf.run/TrPZ )  
- [클라이언트 게임 개발자를 위한 소켓 프로그래밍 기초에서 활용까지](https://youtu.be/hcM_PReblyg )

    
  
<br>  
  
    
# curriculum

1. 게임 서버 틀 만들기
  - 첫 시간에는 같이 모여서 멘토가 알려주는 방식으로 로그인 기능을 가진 게임서버를 만든다.
  - 네트워크 프로그래밍은 멘토가 제공하는 네트워크 라이브러리 코드를 사용한다.
  - 패킷에 대한 설명
  - 테스트용 클라이언트에 대한 설명
  - 게임서버 큰 틀이 만들어지고, 앞으로 클라이언트와 주고 받는 기능은 어떻게 만들면 되는지 알 수 있다.
2. 방 입장, 방 나가기, 방 채팅 만들기

3. 오목 게임 컨텐츠 만들기
  - 게임 시작 요청, 게임 시작
  - 오목 두기(타임아웃 적용)
  - 오목 체크, 게임종료
4. 클라우드를 사용하여 게임 배포하기
  - 클라우드(AWS, Azure, GCP 등)에 서버를 실행한다.
  - 클라이언트를 지인들에게 배포한 후 게임 테스트를 요청한다
  
<br>    
    
# 과제 
  
## 1) 방 입장
- 클라이언트에서 요청 시에 방번호를 보낸다
- 방번호가 0 이상이면 유저를 요청한 방에 입장시킨다
- 방번호가 -1 이면 서버에서 빈 방을 골라서 입장시킨다.
- 방에 이미 입장한 유저가 있는 경우 이미 있는 유저들에게 새로 들어온 유저의 정보를 보내준다.  
  
```mermaid
sequenceDiagram
   participant c_other as 요청 클라이언트 이외의 모든 클라이언트
   participant c as 요청 클라이언트    
   participant s as 서버
  
   c ->>+ s: PK_ENTER_ROOM_REQ
   s -->+ c: PK_ENTER_ROOM_RES
   s ->>+ c_other: PK_NEW_USER_ENTER_ROOM_NTF
```   
    
    
## 2) 방 나가기 
- 클라이언트는 이 요청에는 Body 데이터가 없다(서버는 이 클라이언트가 어느 방에 들어가 있는지 알고 있으므로)
- 방에 있는 유저 수가 2 이상인 경우에 나가는 경우 아직 남아 있는 유저들에게 방을 나가가는 유저가 누구인지 알려준다
- 클라이언트가 방에 있는 상태에서 프로그램을 종료하면 네트워크 접속이 끊어지고, 서버는 접속이 끊어진 유저가 방에 있는지 조사하 후 방에 있다면 방 나가기 처리를 한다.  
  
```mermaid
sequenceDiagram
   participant c_other as 요청 클라이언트 이외의 모든 클라이언트
   participant c as 요청 클라이언트    
   participant s as 서버
  
   c ->>+ s: PK_LEAVE_ROOM_REQ
   s -->+ c: PK_LEAVE_ROOM_RES
   s ->>+ c_other: PK_USER_LEAVE_ROOM_NTF
```   
    
	
## 3) 방 채팅
- 방에 있는 유저가 채팅 메시지를 보내면 방에 있는 모든 유저에게 브로드캐스트 한다.
   
```mermaid
sequenceDiagram
   participant c_other as 요청 클라이언트 이외의 모든 클라이언트
   participant c as 요청 클라이언트    
   participant s as 서버
  
   c ->>+ s: PK_CHAT_ROOM_REQ
   s -->+ c: PK_CHAT_ROOM_RES
   s ->>+ c_other: PK_CHAT_ROOM_NTF
```  
  
    
## 4) 게임 시작 요청
- 방에 있는 유저가 게임 시작 요청을 ㅎ보내면 방에 있는 모든 유저에게 브로드캐스트 한다.  
  
```mermaid
sequenceDiagram
   participant c_other as 요청 클라이언트 이외의 모든 클라이언트
   participant c as 요청 클라이언트    
   participant s as 서버
  
   c ->>+ s: PK_READY_GAME_ROOM_REQ
   s -->+ c: PK_READY_GAME_ROOM_RES
   s ->>+ c_other: PK_READY_GAME_ROOM_NTF
```    
   
## 5) 게임 시작 취소

```mermaid
sequenceDiagram
   participant c_other as 요청 클라이언트 이외의 모든 클라이언트
   participant c as 요청 클라이언트    
   participant s as 서버
  
   c ->>+ s: PK_CANCEL_READY_GAME_ROOM_REQ
   s -->+ c: PK_CANCEL_READY_GAME_ROOM_RES
   s ->>+ c_other: PK_CANCEL_READY_GAME_ROOM_NTF
```    
  

## 5) 게임 시작 통보
- 방의 게임을 할 유저가 모두 게임 시작 요청을 했다면 게임 시작을 알린다. 첫번째 턴 유저 정보도 담는다  
  
```mermaid
sequenceDiagram
   participant c_all as 방의 모든 클라이언트    
   participant s as 서버
  
   s -->+ c_all: PK_START_GAME_ROOM_NTF   
```      
  
## 6) 알 두기 
- 턴을 가진 유저만 요청할 수 있다. NTF 패킷에서 다음 유저의 턴 정보를 알려준다   
  
```mermaid
sequenceDiagram
   participant c_all as 방의 모든 클라이언트
   participant c as 요청 클라이언트    
   participant c_all as 서버
  
   c ->>+ s: PK_PUT_AL_GAME_ROOM_REQ
   s -->+ c: PK_PUT_AL_GAME_ROOM_RES
   s ->>+ c_all: PK_PUT_AL_GAME_ROOM_NTF
```    
  
## 게임 종료 체크    
- 위의 알 두기 이후 오목 체크를 한 후 게임이 종료 되면 알린다   

```mermaid
sequenceDiagram
   participant c_all as 방의 모든 클라이언트    
   participant s as 서버
  
   s -->+ c_all: PK_END_GAME_ROOM_NTF   
```        
  
  
  
  
