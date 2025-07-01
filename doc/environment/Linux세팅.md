https://velog.io/@maasj/Mac-M3-UTM-ubuntu-%ED%99%98%EA%B2%BD%EA%B3%BC-mac-%EA%B3%B5%EC%9C%A0-%ED%8F%B4%EB%8D%94-%EC%83%9D%EC%84%B1

# 리눅스 개발환경 설정
- [리눅스 개발환경 설정](#리눅스-개발환경-설정)
  - [Overview](#overview)
    - [Why Linux/Mac](#why-linuxmac)
    - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [System](#system)
    - [Korean Keyboard](#korean-keyboard)
    - [Root Password](#root-password)
    - [Wayland (22.04)](#wayland-2204)
  - [Shell](#shell)
    - [Zsh](#zsh)
    - [Oh My Zsh](#oh-my-zsh)
    - [Plugins](#plugins)
    - [Terminator](#terminator)
  - [Tools](#tools)
    - [Vim](#vim)
    - [Git](#git)
    - [Docker](#docker)
  - [Program](#program)
    - [KakaoTalk](#kakaotalk)
    - [VSCode](#vscode)
    - [pinta (그림판)](#pinta-그림판)
    - [obs-studio (화면 녹화)](#obs-studio-화면-녹화)


## Overview
 이 문서에서는 동아리 프로젝트 개발에 유용한 우분투(리눅스) 설정 및 플러그인, 프로그램 등을 소개합니다. 동아리 개발문서는 리눅스를 기준으로 작성될 것이므로 윈도우를 이용하고 있다면 이 문서에 따라 개발환경을 설정하기를 권장합니다. 백엔드 개발자라면 반드시 리눅스나 MacOS 환경에서 개발하시기 바랍니다.
 > MacOS 사용자 -> zsh과 tools만 설정

### Why Linux/Mac
 윈도우 프로그램은 대부분 GUI 개발을 수반하고 커맨드라인도 UNIX 명령어와 많은 차이가 있습니다. 또한 윈도우의 라이센스로 인해 공개되지 않은 소스코드가 많으며 소프트웨어 개발 중 OS 레벨의 문제를 발견하면, 마이크로소프트 측에 개선 요청을 해야만 피드백을 받을 수 있습니다. 리눅스로 개발하는 주된 이유는 이처럼 **커맨드라인 환경**과 **오픈소스** 두 가지이며 이미 비즈니스 레벨의 수많은 개발툴은 리눅스(UNIX)를 기반으로 합니다. MacOS는 UNIX를 기반으로 하고 있고, 커맨드라인 환경을 지향하므로 MacOS도 개발에 좋은 옵션입니다. 

 - 다양한 개발툴은 리눅스를 바탕으로 한다. (Docker, Kubernetes, Bazel 등)
 - AWS, GCP 등 배포 환경 및 원격접속 환경은 리눅스이다. (ssh)
 - CI/CD는 리눅스 명령어로 작성된다.
 - 자동화 스크립트를 작성하려면 커맨드라인 환경에 익숙해야 한다.

### Prerequisites
다음은 Windows에서 Ubuntu를 Dual-OS로 설치하고자 할 때 최소 요구사항입니다.
  - 16GB+ USB
  - [Ubuntu 22.04/23.04 이미지](https://ubuntu.com/download/desktop)
  - 리눅스에 할당 가능한 100GB+의 여유공간
## Installation
 동아리는 Ubuntu 22.04LTS 또는 23.04를 기준으로 합니다. 설치는 다음 블로그 글을 참고하시기 바랍니다.
1. 부팅 USB 만들기: [블로그 글](https://heisanbug.tistory.com/17)
2. 우분투 설치: [블로그 글](https://jimnong.tistory.com/676)

 우분투 설치 시 파티션 축소를 건너뛰고 `Windows를 그대로 두고 설치` 옵션을 선택해도 됩니다. 그러면 파티션 설정을 우분투 설치 중에 하게 됩니다. (노트북이나 BIOS 설정에 따라 안 되는 경우도 있음)

## System
### Korean Keyboard
🔗 [Ubuntu 키보드 한글 입력 설정 하기](https://shanepark.tistory.com/231)  

### Root Password
root 계정으로 시스템을 설정해야 하거나, `sudo`를 매번 사용하기 번거롭다면 `su`로 root 계정에 로그인해야 합니다. 아래 명령어로 루트 계정의 비밀번호를 설정할 수 있습니다.
```bash
$ su -i
$ passwd
> password: 
```

### Wayland (22.04)
> 🔗 [Screen Share Not Working](https://askubuntu.com/questions/1407494/screen-share-not-working-in-ubuntu-22-04-in-all-platforms-zoom-teams-google-m)

우분투 22.04는 화면 디스플레이 프로토콜로 Wayland를 사용하지만, 이는 전체 화면 공유가 불가능한 이슈가 있습니다. 이전 프로토콜인 Xorg로 디스플레이 설정을 바꿔주어야 Google Meet, Discord 등에서 화면 공유가 가능합니다.
```bash
# 현재 디스플레이 설정 확인 (Wayland)
$ echo $XDG_SESSION_TYPE

# 디스플레이 설정을 Xorg로 변경
$ sudo vi /etc/gdm3/custom.conf
WaylandEnable=false # 주석 해제

# 재부팅 및 변경 확인 (x11)
$ echo $XDG_SESSION_TYPE
```

## Shell
### Zsh
&nbsp;zsh은 리눅스 기본 bash 보다 다양한 확장 기능을 제공하는 터미널 쉘입니다. 터미널 테마와 자동완성, 텍스트 하이라이트 등 유용한 플러그인 덕분에 개발에 필수적이라 할 수 있습니다. Zsh은 Mac OS의 기본 터미널 쉘이기도 합니다.  
**설치방법**: 🔗 [Install and Setup ZSH on Ubuntu Linux](https://itsfoss.com/zsh-ubuntu/#install-zsh-on-ubuntu)
```bash
# zsh 설치 및 첫 환경설정
$ sudo apt install zsh git fonts-font-awesome
$ zsh          // 주로 0번이나 1번 선택
$ which zsh    // 설치여부 확인

# zsh을 기본 쉘로 설정 (-s = 특정 쉘로 설정)
# 설정 이후 재로그인 또는 재부팅 필요
$ chsh -s $(which zsh)
```
### Oh My Zsh
&nbsp;OMZ는 Zsh에 다양한 부가 기능을 추가 및 관리해주는 플러그인입니다. 대표적으로 자동완성, 간편한 명령어 별명 기능 등이 있습니다. 아래 커맨드라인을 통해 설치가 완료되면 ```.zshrc```가 업데이트되며, 자동으로 OMZ가 반영됩니다.  
**설치방법**: 🔗 [Oh My Zsh Installation](https://github.com/ohmyzsh/ohmyzsh/tree/master#basic-installation)
```bash
// OMZ 설치용 쉘 스크립트 다운로드 및 실행
sh -c "$(wget -O- https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
sh install.sh
```

### Plugins
![image](https://github.com/ApptiveDev/.github/assets/51331195/98b9c881-5707-4f52-b1e1-6a15eade34b1)
- [Auto Suggestion](https://github.com/zsh-users/zsh-autosuggestions/blob/master/INSTALL.md#oh-my-zsh): 최근 사용한 명령어를 자동으로 추천해주는 기능
- [Syntax Highlighting](https://github.com/zsh-users/zsh-syntax-highlighting/blob/master/INSTALL.md#oh-my-zsh) : 문자열, 유저명 등 텍스트에 색상을 입히는 기능. 잘못된 명령어는 빨간색으로 표시됨.
- History Search: 현재 프롬프트에 입력된 텍스트에서 화살표 키를 통해 최근 사용된 명령어를 검색
```bash
# 기본 플러그인 폴더에 Auto Suggestion, Syntax Highlight 소스코드 다운로드
$ git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
$ git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting

# zsh 환경설정
$ vi ~/.zshrc

# .zshrc 내에서 플러그인 활성화
plugins=( 
    # other plugins...
    git
    docker
    docker-compose
    zsh-autosuggestions
    zsh-syntax-highlighting
)

# .zshrc 내에서 명령어 히스토리 단축기 설정 (적당한 곳에 아래 2줄 복붙)
bindkey "^[[A" history-beginning-search-backward    # ↑ (이전 명령어)
bindkey "^[[B" history-beginning-search-forward     # ↓ (최근 명령어)

# zsh 새로고침
$ source ~/.zshrc
```

### Terminator
![image](https://github.com/ApptiveDev/.github/assets/51331195/c57fd26b-fbef-4f88-a159-f93d2f466822)  
Terminator는 한 터미널 창에서 여러 터미널을 분할해 사용할 수 있도록 하는 프로그램입니다. 더 확장된 프로그램으로 `tmux`를 사용할 수 있습니다.
```bash
# Terminator 설치 및 기본 터미널로 설정 (Ctrl + Alt + T)
$ sudo apt update
$ sudo apt install terminator
$ sudo update-alternatives --config x-terminal-emulator
```

## Tools

### Vim
 vim은 텍스트 에디터로, 각종 config 파일이나 YAML, XML 등의 파일을 편집할 때 자주 사용하고, 특히 git 커밋 메시지 등을 편집할 때 유용합니다.
```bash
$ sudo apt-get update
$ sudo apt-get install vim 
```

### Git
```bash
# git 설치
$ sudo apt-get update
$ sudo apt-get install git

# git 기본 텍스트 에디터로 vim 설정
$ git config --global core.editor "vim"

# 커밋 작성자에 쓰일 계정정보 설정
$ git config --global user.name <닉네임>
$ git config --global user.email <계정 이메일 주소>
```
git 커맨드라인 환경 이용 시 ssh 방식의 원격 리포지토리 접근이 일반적입니다. HTTPs 방식은 매번 ID, 비밀번호를 입력해야 해서 번거롭습니다.  
ssh도 설정을 하지 않으면 매번 계정을 입력해야 하는데, 편하게 사용하려면 아래 절차를 따라주시기 바랍니다.

```bash
# ssh key 생성 (RSA 방식)
# 다른 방식도 무관하나 github가 이 형식을 지원해야 함.
$ ssh-keygen -t rsa
# 아래 프롬프트에서 키를 저장할 경로와 비밀번호 입력
# 경로는 ~/.ssh/id_rsa_github와 같이 .ssh 폴더 내에 위치하도록 입력
Generating public/private rsa key pair.
Enter file in which to save the key (/home/<본인 계정>/.ssh/id_rsa):
Enter passphrase (empty for no passphrase): # 비밀번호

# 생성된 공개키(.pub) 출력 후 드래그하여 복사 후 Github에 등록
# [Github 본인계정] > [Settings] > [SSH and GPG keys] > [New SSH Key]에 복사한 키 등록
$ cat ~/.ssh/<저장한 키 파일>.pub
ssh-rsa AAAAB3NzaC1yc2EAAAADA...

# github.com에 대한 SSH 접근 시 자동으로 사용할 키를 로컬에 등록
# config 파일 생성 후 아래 내용 입력 및 저장
$ vi ~/.ssh/config
Host *github*
  User git
  Hostname github.com
  IdentityFile ~/.ssh/<생성한 파일명>
```

### Docker
🔗 [Official Installation](https://docs.docker.com/engine/install/ubuntu/)  
흔히 말하는 컨테이너 플랫폼인 Docker는 **Docker Engine**을 뜻합니다. Docker는 가상화를 위해 Linux의 내장 Virtual Machine 기능을 요구하며, **Docker Desktop**은 Linux가 아닌 다른 운영체제(Windows, Mac)에서 이를 지원하기 위한 GUI 도구입니다. 따라서 리눅스는 Docker Engine을 설치하고, 다른 운영체제는 Docker Desktop을 설치해야 합니다. 위에서 apt repository 등록 및 Docker Engine 설치 절차를 따르시기 바랍니다.
```sh
# 도커 다운로드를 위한 GPG 키 등록
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# 도커 다운로드 리포지토리 (apt) 등록
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update

# 도커 설치
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

# 도커 실행에 관리자 권한 획득
sudo groupadd docker
sudo usermod -aG docker $USER
newgrp docker

# 도커 정상 설치 확인
docker run hello-world
```

## Program
### KakaoTalk
카카오톡은 리눅스를 공식적으로 지원하지 않으므로 우툰부에서 윈도우 환경을 에뮬레이션하는 `wine`을 이용해야 합니다.
1. wine 설치 ([공식 홈페이지](https://wiki.winehq.org/Ubuntu))
```shell
# 32bit 아키텍처 활성화
sudo dpkg --add-architecture i386
# wine 리포지토리 추가
sudo mkdir -pm755 /etc/apt/keyrings
sudo wget -O /etc/apt/keyrings/winehq-archive.key https://dl.winehq.org/wine-builds/winehq.key 
sudo apt update
# wine 설치
sudo apt install --install-recommends winehq-stable
```
2. Windows용 카카오톡 설치 프로그램 [다운로드](https://www.kakaocorp.com/page/service/service/KakaoTalk)
3. `wine`을 통한 카카오톡 설치
   - 설치 시 폴더를 `/home/tools/` 등 확인하기 편한 곳으로 지정
   - 기본 폴더 지정 시 `~/.wine/drive_c`에서 확인 가능
   - 터미널에서 카카오톡을 실행하려면 `wine <설치한 폴더>/Kakaotalk.exe`
```shell
cd ~/Downloads
LANG="ko_KR.UTF-8" wine KakaoTalk_Setup.exe
```
4. 한글폰트(나눔고딕) 설치 및 설정  
   - [gulim.ttc](../tools/gulim.ttc) 파일을 다운받아 `~/.wine/drive_c/Windows/Fonts`에 옮긴 후
   - `vi ~/.wine/system.reg`의 `MS Shell Dlg` 항목을 `"Gulim"`으로 설정 (스크린샷 참고)
<p align="center">
	<img src="../images/dev-setting-kakaotalk-favorite.jpg" width="200"/>
  <img src="../images/dev-setting-winecfg-gulim-font.jpg" width="200"/>
</p>

### VSCode
**(설치방법)**
먼저 [VS Code](https://code.visualstudio.com/download)에서 .deb 파일을 다운로드한 후 다음 명령어를 실행합니다. 
```
$ sudo apt install ~/Downloads/<파일명>.deb
$ code --version
```

**추천 확장프로그램**
- **GitLens**: 에디터에서 어떤 부분이 어떤 커밋에 의해 수정되었는지 알 수 있음
- **GitGraph**: 커밋, 브랜치 히스토리를 시각적으로 표현
- **Material Theme Icons**: 이쁜 파일/폴더 아이콘
- **Markdown All In One**: 마크다운 문서(.md) 편집 시 미리보기 가능
- **Markdown Emoji**: 마크다운 미리보기에서 이모티콘까지 렌더링 (단, 이모티콘 텍스트는 [여기](https://gist.github.com/rxaviers/7360908)서 확인)

### pinta (그림판)
![image](https://github.com/ApptiveDev/.github/assets/51331195/06d7dc22-7b28-4690-b7a8-19cd556a74c4)  
**(설치방법)**  
[Ubuntu Software] -> Pinta 검색 및 설치


### obs-studio (화면 녹화)
![image](https://github.com/ApptiveDev/.github/assets/51331195/75c23bdb-9a0e-4e8e-a2e7-7e674304555c)  
**(설치방법)** 🔗 [OBS Linux Installation](https://obsproject.com/kb/linux-installation)  
```bash
// apt 리포지토리 등록 및 설치
sudo add-apt-repository ppa:obsproject/obs-studio
sudo apt install obs-studio

// 실행
obs
```

> ### 참고

https://github.com/ApptiveDev/.github/blob/main/docs/Dev%20Environment%20Setup.md