---
title: (2021)온라인 서울 하드웨어 해커톤 - 탑메이커편' 
author: haeyeon.hwang
tags: [tizen, rpi, iot]
---

# (2021)온라인 서울 하드웨어 해커톤 - 탑메이커편
---
1. [팀명 및 팀원](#팀명-및-팀원)
2. [프로젝트 제목](#프로젝트-제목) 
3. [프로젝트 배경 및 목적](#프로젝트-배경-및-목적)
4. [타이젠 오픈소스에 컨트리뷰션한 내역](#타이젠-오픈소스에-컨트리뷰션한-내역)
5. [파일리스트](#파일리스트)
6. [코드 기여자](#코드-기여자)
7. [보드](#보드)
8. [구현 사항 가산점](#구현-사항-가산점)


[별첨](#별첨)

[![Watch the video](https://img.youtube.com/vi/uvsUo99V84U/hqdefault.jpg)](https://youtu.be/uvsUo99V84U)
![](images/b0.jpg)

---

## 팀명 및 팀원
- 팀명: WNB
- 팀원 
   
이름|역할
---|---
황해연|기획/설계/개발(하드웨어/소프트웨어)
김민전|개발(소프트웨어)
황인규|기획/테스트
황인후|테스트

![](images/m1.jpg)
![](images/mt1.jpg)
![](images/mt2.jpg)

---

## 프로젝트 제목

**에어코드를 이용한 QR체크인 (QR check-in w/ Air Code)**

![](images/m2.jpg)

---

## 프로젝트 배경 및 목적 
#### 배경
- 코로나 이후 주변에서 흔하게 QR체크인을 통해서 오프라인 사용자의 동선을 체크 함.
- 동선을 체크하기 위한 QR코드 체크인의 과정이 의외로 복잡한 단계를 거침
    - 휴대폰/앱 활성화 – 서비스 찾기 – QR발급 – QR인식 (리더기해상도에 따라 더 늦어짐)
    - 공연장 및 전시장과 같은 경우에는 구획별 파티션마다 QR체크인 수행
    - 언택트 기술의 일부인 음성통신을 이용한 QR체크인 활성화 기술

#### 하고자 하는것
- QR 체크인이 필요한 상황에서 알아서 체크인 코드가 활성화
- **에어코드를 이용한 QR체크인**

![](images/m3.jpg)

#### 실현가능성
- 실제 통신 데이터를 저대역 PCM(디지털 양자/부호화)
- 이를 오디오 내 추출 및 삽입을 통해 데이터의 통신구현이 가능할 것으로 보임
- QR 리더기 근처에 저대역/저음 송출이 가능한 스피커와 본체를 구현하여
- 마이크로 단위의 위치기반 서비스와 데이터 전송이 가능함.

- **음성통신을 이용한 실내외 위치기반 다양한 마이크로 서비스 가능 => 광고/방역/위치서비스 등**

---

## 타이젠 오픈소스에 컨트리뷰션한 내역
내역없음

---

## 파일리스트
  
#### 에어코드를 이용한 QR체크인 [[github]](https://github.com/pushdown99/aircode.git)
~~~console
├─camera
│  ├─inc
│  ├─shared
│  │  └─res
│  └─src
~~~

- 헤더파일(*.h)

파일명|내용
---|---
inc/baseUI.h|baseUI/EFL 관련 외부참조 및 함수정의 
inc/cam.h|카메라 관련 외부참조 변수 및 함수정의
inc/max4466.h|마이크앰프(MAX4466) 제어를 위한 외부참조 변수 및 함수정의
inc/misc.h|기타(miscellaneous) 외부참조 변수 및 함수정의
inc/piezoe.h|피에조 부저 (카메라셔터음) 제어 관련 외부참조 변수 및 함수정의
inc/post.h|외부서버에 데이터전송을 위한 curl/POST 관련 외부참조 변수 및 함수정의
inc/soundcam.h|소음감지어플리케션 주요구조체 및 관련 외부참조 변수 및 함수정의
inc/thread.h|쓰레드 처리를 위한 외부참조 변수 및 함수정의

- 소스파일(*.c)

파일명|내용
---|---
src/baseUI.c|baseUI/EFL을 이용 UI레이아웃 설정 및 제어 
src/cam.c|카메라 초기화 및 프리뷰관련 설정</br>baseUI와 연결
src/**main.c**|어플리케이초기화 및 환경설정</br>idler설정
src/max4466.c|마이크앰프(MAX4466) 제어를 위한 외부참조 변수 및 함수정의
src/misc.c|기타(miscellaneous) 함수
src/piezoe.c|피에조 부저 (카메라셔터음) 제어
src/post.c|외부서버에 데이터전송을 위한 curl/POST 
src/thread.c|쓰레드 처리 (마이크앰프별,코디네이터, GPIO, Thingspark 연동)

#### 카메라 대시보드 [[github]](https://github.com/pushdown99/sound-camera/tree/master/dashboard)

~~~console
├─dashboard
│  ├─public
│  │  └─data
│  └─views
~~~

- 소스파일(*.js)

파일명|내용
---|---
**app.js**|nodejs기반 웹어플리케이션  

- 소스파일(*.ejs)
  
파일명|내용
---|---
views/chart.ejs|google chart 및 카메라 이미지처리 html/javascript 템플릿  

---

## 코드 기여자 

#### 소음감지카메라

- 헤더파일(*.h)

파일명|기여자
---|---
inc/baseUI.h|황해연 
inc/cam.h|황해연
inc/max4466.h|황해연
inc/misc.h|황해연,김민전
inc/piezoe.h|황해연,김민전
inc/post.h|황해연
inc/soundcam.h|황해연
inc/thread.h|황해연

- 소스파일(*.c)

파일명|기여자
---|---
src/baseUI.c|황해연
src/cam.c|황해연
src/main.c|황해연
src/max4466.c|황해연
src/misc.c|황해연
src/piezoe.c|황해연
src/post.c|황해연 
src/thread.c|황해연

#### 카메라 대시보드

- 소스파일(*.js)

파일명|기여자
---|---
app.c|황해연

- 소스파일(*.ejs)
  
파일명|기여자
---|---
views/chart.ejs|황해연  

---

## 보드 

구현보드|목적|소스위치
:---|:---|:---
RPi 4|소음감지 카메라 본체</br>- 마이크앰프처리</br>- 카메라영상출력|[https://github.com/pushdown99/sound-camera/tree/master/camera](https://github.com/pushdown99/sound-camera/tree/master/camera)  


---

## 구현 사항 (가산점) 

#### Peripheral
종류|디바이스|목적|소스위치
:---|:---|:---|:---
SPI|MAX4466/MCP3008|마이크앰프 복수채널 I/O|src/mcp3008.c</br>src/max446.c
GPIO|버튼|카메라셔터|src/thread.c
GPIO|피에조부저|카메라셔터음|src/piezoe.c 

---

## 별첨

#### 자료다운로드
Output|Download
---|---
문서자료|[소음카메라(pptx)](noise-camera.pptx)
문서자료|[소음카메라(pdf)](noise-camera.pdf)
발표자료|[PRESENTATION.md](PRESENTATION.md)

# aircode