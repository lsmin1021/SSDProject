# 팀명 : **CleanCode**

## 📌 프로젝트 개요
이 프로젝트는 SSD 시뮬레이션을 위한 프로그램으로, 명령어 기반의 **Test Shell**과 **SSD 기능 구현 (Write/Read)** 기능을 제공합니다.  
**코드 컨벤션 및 TDD 기반 개발, Test Double 최소 1회 사용, 역할 분담에 따라 개발**을 진행합니다.

---

## **작성자**
### git 설정이 미흡하여 담당자가 여러 작성자로 commit 되었음에 주의바랍니다.
| 담당자          | 작성자     |
|----------------|------------|
| 이도영          | ldy <ldy@example.com> / eedoyoung1234 <2do00531@gmail.com> |
| 이승민          | Heeseung Yoo <heeseung.yoo@samsung.com> / lsmin1021 <dltmdals826@gmail.com> |
| 추창래          | Wontae Jeong <dev.jeong@samsung.com> / akachoochoo <cl.choo@samsung.com> | 
| 한창희          | CHANGHEE-H <jaduwvad2@naver.com> |

## 📝 **역할 분담**

| 역할            | 담당자       |
|----------------|------------|
| 코드 컨벤션 및 코딩 룰 적용 | 추창래 |
| SSD 기능 구현 (Write/Read) | 한창희, 이승민 |
| Test Shell 구현 | 이도영, 추창래 |
| Repository 생성 | 이승민 |

---

## 💻 **코딩 규칙**

### ✅ **네이밍 규칙**
- **변수명:** `camelCase`
- **클래스명:** `PascalCase`
- **멤버 변수:** `m_` 접두어 + `camelCase`
- **상수/매크로:** `UPPER_SNAKE_CASE`

### ✅ **중괄호 스타일**
- **K&R 스타일 권장 (Visual Studio 기본)**
```cpp
if (condition) {
    // do something
}
```
    
### ✅ **자동 포맷팅**  
- **Ctrl + K + D 단축키로 전체 코드 포맷팅**  

### ✅ **기본 코딩 룰**  
✔️ 함수 하나는 하나의 역할  
✔️ 함수 길이는 30줄 이하 권장  
✔️ 포인터 사용 시 nullptr 체크 필수  
✔️ magic number 금지 → const 변수 선언  


## 💻 **공통 규칙**
- 공통 코드 스타일, 네이밍, 주석 규칙 준수
- **TDD (Test-Driven Development)** 방식으로 개발
- **Test Double**을 최소 한 번 이상 사용

## 🏗️ **SSD 기능**

### ✅ **Write**
- `ssd_nand.txt` 파일이 없으면 **생성 후 데이터 기록**
- **`ssd_nand.txt` 파일에만 데이터 기록 (콘솔 출력 없음)**
- 잘못된 LBA 입력 시 `ssd_output.txt`에 `"ERROR"` 기록

### ✅ **Read**
- `ssd_nand.txt` 파일이 없으면 **생성 후 데이터 읽기**
- `ssd_nand.txt`에서 데이터를 읽어와 **`ssd_output.txt`에 기록 (콘솔 출력 없음)**
- `ssd_output.txt`에는 **항상 마지막 Read 결과 덮어쓰기 저장**
- 기록되지 않은 LBA를 읽으면 `0x00000000` 반환
- 잘못된 LBA 입력 시 `ssd_output.txt`에 `"ERROR"` 기록

### ✅ **데이터 범위**
- **LBA**: 0 ~ 99 (10진수 입력)
- **Value**: `"0x"` 접두사 + 8자리 16진수 (예: `0x00000000` ~ `0xFFFFFFFF`)
- 대소문자 구분 (예: `0xABCD1234` vs `0xabcd1234` → 구분됨)

### ✅ **`ssd_nand.txt` 구현 방식**
- 명령어 수행 시마다 **`ssd_nand.txt` 전체 데이터 읽어오기**
- 성능 개선 시 **랜덤 액세스 파일 I/O** 필요
- 파일 입출력 클래스는 **Singleton** 패턴 고려

## 🏗️ **SSD Command Buffer 구현**

### ✅ **Ignore Command**
- 버퍼에 저장된 명령어가 5개인 경우, Ignore가 가능한 명령어가 있어도 flush 수행
- 명령어(W/E)를 입력하기 전에 먼저 수행
- ignore 처리 후에 명령어 입력

### ✅ **Merge Command**
- 명령어가 병합되는 과정은 최근 명령어 -> 예전 명령어 방향임  
  **EX> Erase 5 ~ 10, Write 8 + Erase 9 ~ 13  
  => Erase 5 ~ 13, Write 8**
- 명령어 수를 최대한 줄이기 위함

## 🧪 **Test Shell **

### ✅ **Test Shell command **
| 명령어      | 설명                                       |
|-------------|------------------------------------------|
| `write`     | 특정 LBA에 Value 기록                     |
| `read`      | 특정 LBA에서 데이터 읽기                  |
| `fullwrite` | LBA 0 ~ 99까지 모든 영역 Write 수행        |
| `fullread`  | LBA 0 ~ 99까지 모든 영역 Read 수행         |
| `help`      | 제작자 이름 및 각 명령어 사용법 출력      |
| `exit`      | Test Shell 종료                           |

---

### ⚠️ **유의사항**
1. **입력된 매개변수 유효성 검사**
   - 파라미터 Format 정확성 검증
   - LBA 범위: `0 ~ 99`
   - Value 범위: `A-F`, `0-9` 허용
2. **없는 명령어 입력 시**
   - `"INVALID COMMAND"` 출력
3. **런타임 에러가 발생하지 않도록 안정성 확보**

---
