#include <iostream>
#include <cstring> // 문자열을 배열로 관리

using namespace std;
const int NAME_LEN = 20; // const: 개체 또는 변수를 수정할 수 없음.

void ShowMenu(void); // 메뉴 출력
void MakeAccount(void); // 계좌개설을 위한 함수
void DepositMoney(void); // 입 금
void WithdrawMoney(void); // 출 금
void ShowAllAccInfo(void); // 잔액조회

enum {MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT}; // enum: 사용자 정의 자료형
// {} 안의 요소들은 열거자(enumerator), 각 열거자는 쉼표로 구분
// 각 열거자는 열거 목록의 위치에 따라 정수 값이 자동으로 할당됨. 정의되지 않은 모든 열거자는 이전 열거자보다 1만큼 더 큰 값이 부여됨.

typedef struct { // typedef: 재정의 함수 -> 원하는 데이터 유형에 새로운 별명을 지어줌.
    // struct: 구조체 선언 -> 새로운 데이터 유형을 만들고 멤버 변수를 정의하여 구조체 타입의 새로운 메모리 공간 할당
    int accID; // 계좌 번호
    int balance; // 잔 액
    char cusName[NAME_LEN]; // 고객이름
} Account; // 구조체 정의 후, Account 라는 별명을 붙임 -> 이후 구조체 선언은 Account twalla;로 간편하게 쓸 수 있다.

Account accArr[100]; // Account 저장을 위한 배열
int accNum = 0; // 등록되는 계좌들 각각을 비교하기 위한 고유 num

int main(void) {
    int choice; // 사용자가 선택한 메뉴 번호

    while (1) { // 1 -> True
        ShowMenu(); // ShowMenu()함수 실행 -> 메뉴판 보여줌
        cout << "선택: ";
        cin >> choice; // 사용자의 선택을 받음.
        cout << endl; // choice 입력 후, 줄바꿈

        switch (choice) { // switch문 -> if문보다 일반적으로 더 효율적임.
            // switch (비교할 대상)
            case MAKE: // case 비굣값, 비굣값에는 상수만 올 수 있음. MAKE의 경우에는 1 -> if (choice == 1) 과 같은 역할
                MakeAccount(); // choice == 1일 경우, MakeAccount()함수 실행
                break; // case문의 끝

            case DEPOSIT:
                DepositMoney();
                break;

            case WITHDRAW:
                WithdrawMoney();
                break;

            case INQUIRE:
                ShowAllAccInfo();
                break;

            case EXIT:
                return 0;

            default: // 어떤 case에도 맞지 않으면 default가 실행됨.
                cout << "Illegal selection.." << endl;
        }
    }
    return 0;
}

void ShowMenu(void) { // 메뉴 보여주는 함수 정의
    cout << "-----Menu-----" << endl;
    cout << "1. 계좌개설" << endl;
    cout << "2. 입 금" << endl;
    cout << "3. 출 금" << endl;
    cout << "4. 계좌정보 전체 출력" <<endl;
    cout << "5. 프로그램 종료" << endl;
}

void MakeAccount(void) { // 계좌개설 함수 정의
    int id; // 계좌 id
    char name[NAME_LEN]; // 사용자 이름, MAKE_LEN은 20으로 고정되어 있음 -> 사용자 이름이 20을 넘을 수 없음
    int balance; // 계좌에 있는 금액

    // 사용자에게 계좌 정보를 받아서 변수에 저장
    cout << "[계좌개설]" << endl;
    cout << "계좌ID: "; cin >> id;
    cout << "이 름: "; cin >> name;
    cout << "입금액: "; cin >> balance;
    cout << endl;

    // 받은 정보를 accArr에 저장
    accArr[accNum].accID = id; // 크기가 [accNum]인 구조체 배열 생성 -> 인덱스로 요소에 접근 후, .으로 멤버에 접근
    accArr[accNum].balance = balance;
    strcpy(accArr[accNum].cusName, name); // strcpy: string copy -> 문자열을 복사하는 함수, name에 저장된 문자열을 accArr[accNum].cusName에 복사
    accNum++; // 다음에 저장되는 계좌의 고유 id를 1 증가
}

void DepositMoney(void) { // 입금 함수 정의
    int money; // 입금액
    int id; // 계좌 id

    cout << "[입 금]" << endl;
    cout << "계좌ID: "; cin >> id;
    cout << "입금액: "; cin >> money;

    for (int i = 0; i < accNum; i++) { // 입력받은 계좌id로 저장되어 있는 계좌 중에 해당 계좌를 찾음.
        if (accArr[i].accID == id) { // 찾고있는 계좌의 id와 저장되어 있는 계좌의 id가 같으면
            accArr[i].balance += money; // 계좌에 money 추가
            cout << "입금완료" << endl << endl;
            return;
        }
    }
    cout << "유효하지 않은 ID 입니다." << endl << endl; // 해당 계좌를 찾지 못함.
}

void WithdrawMoney(void) { // 출금 함수 정의
    int money; // 출금액
    int id; // 계좌 ID

    cout << "[출 금]" << endl;
    cout << "계좌ID: "; cin >> id;
    cout << "출금액: "; cin >> money;

    for (int i = 0; i < accNum; i++) { // 입력받은 ID로 계좌 찾기
        if (accArr[i].accID == id) { // 계좌를 찾으면
            if (accArr[i].balance < money) { // 만약 계좌에 있는 금액보다 출금액이 더 크면
                cout << "잔액부족" << endl << endl; // 출금 불가
                return;
            }

            accArr[i].balance -= money; // 출금이 가능할 경우 -> 계좌의 금액에서 출금액을 빼준다.
            cout << "출금완료" << endl << endl;
            return;
        }
    }
    cout << "유효하지 않은 ID 입니다." << endl << endl; // 해당 계좌를 찾지 못함.
}

void ShowAllAccInfo(void) { // 전체 계좌 정보를 출력하는 함수 정의
    for (int i = 0; i < accNum; i++) { // 각각의 계좌들에 대해
        cout << "계좌ID: " << accArr[i].accID << endl;
        cout << "이 름: " << accArr[i].cusName << endl;
        cout << "잔 액: " << accArr[i].balance << endl << endl;
    }
}