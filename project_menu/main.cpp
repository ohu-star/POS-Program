#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>
using namespace std;

#define NUM_OF_MENU 6 //상품의 총 갯수

class MENU {
private:
	string goods[NUM_OF_MENU] = { "", }; //상품명
	int price[NUM_OF_MENU] = { 0, }; //상품 가격
	int trans_price[NUM_OF_MENU] = { 0, }; //상품의 거래 단가
	int amount[NUM_OF_MENU] = { 0, }; //구매한 상품별 갯수
	int accum_amount[NUM_OF_MENU] = { 0, };
	int total[NUM_OF_MENU] = { 0, }; //구매한 상품의 총 가격
	int accum_total[NUM_OF_MENU] = { 0, };
	int stock[NUM_OF_MENU] = { 0, }; //상품 재고
	int order_stock[NUM_OF_MENU] = { 0, };
	int pay = 0; //지불한 금액
	int sum = 0; //총 금액(지불해야하는 금액)
	string password = "0000";
public:
	MENU();
	//프로그램 실행
	void start_menu();

	//상품 판매
	void run_sale();
	void show_menu();
	void selete_menu();
	void delete_menu();
	void show_pay();
	void show_rec();
	void reset();

	//재고 관리
	void run_control();
	void check_stock();
	void get_stock();
	void return_stock();

	//관리자 모드 비밀번호 확인
	bool check_password();
	//관리자 모드
	void run_manager();
	void check_goods();
	void change_goods();
	void change_price();
	void sales_status();
	void change_password();

	//매출실적현황
	void check_sales();
	void check_order();
	void customer_status();

	//거래처 현황
	void check_tradeItem();
	void check_warehouse();
	void change_tradePrice();

	void end_menu();

};

MENU::MENU() {
	ifstream fin;
	fin.open("goods.txt");
	if (!fin) {
		cout << "goods.txt 파일을 열 수 없습니다." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fin >> goods[i];
	}
	fin.close();

	fin.open("stock.txt");
	if (!fin) {
		cout << "stock.txt 파일을 열 수 없습니다." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fin >> stock[i];
	}
	fin.close();

	fin.open("price.txt");
	if (!fin) {
		cout << "price.txt 파일을 열 수 없습니다." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fin >> price[i];
	}
	fin.close();

	fin.open("trans_price.txt");
	if (!fin) {
		cout << "trans_price.txt 파일을 열 수 없습니다." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fin >> trans_price[i];
	}
	fin.close();
}

void MENU::start_menu() {
	int task_num; //업무 번호

	do {
		system("cls");
		cout << "======== 메인 메뉴 ========" << endl;
		cout << "1. 상품판매" << endl << "2. 재고관리" << endl << "3. 종료" << endl << "4. 관리자 모드" << endl;
		cout << "===========================" << endl;

		cout << "어떤 업무를 하시겠습니까?  ";
		cin >> task_num;

		switch (task_num) {
		case 1: //상품판매 실행
			run_sale();
			break;
		case 2: //재고관리 실행
			run_control();
			break;
		case 3: //종료
			end_menu();
			break;
		case 4:

			if (check_password())
				run_manager(); //관리자모드 실행
			break;
		default:
			cout << "잘못 입력했습니다. 다시 입력해주세요.";
		}
	} while (task_num != 3);

}




//상품판매
void MENU::run_sale() {
	char m = '1'; //추가구매 여부 flag
	char n = '1';//구매취소 여부 flag
	while (m == '1' || m == 'Y' || m == 'y') {
		show_menu(); //메뉴 출력
		selete_menu(); //메뉴 선택
		//1 or Y가 입력되면 추가구매 진행, 0 or N가 입력되면 구매 종료
		cout << "더 구매하시겠습니까? (예:1/Y, 아니오: 0/N)  ";
		cin >> m;
	}

	cout << "상품을 취소하시겠습니까? (예:1/Y, 아니오: 0/N)  ";
	cin >> n;
	while (1) {
		if (n == '1' || n == 'Y' || n == 'y') {
			delete_menu();
			cout << "더 취소하시겠습니까? (예:1/Y, 아니오: 0/N)  ";
			cin >> n;
		}
		else
			break;
	}
	//결제 진행
	show_pay();

	//영수증 출력
	show_rec();
}

//메뉴 출력
void MENU::show_menu() {
	cout << "======== 상품 메뉴 ========" << endl;
	for (int i = 1; i < NUM_OF_MENU; i++) {
		cout << i << ". " << goods[i] << '\t' << price[i] << "원" << "  " << stock[i] << "개" << endl;
	}
	cout << "==========================" << endl;
}

//메뉴 선택
void MENU::selete_menu() {
	int goods_num = 0; //상품 번호
	int num = 0;//상품 갯수
	char m = '1';

	//예외처리
	while (goods_num < 1 || goods_num >= NUM_OF_MENU) {
		cout << "어떤 상품을 구매하시겠습니까?  ";
		cin >> goods_num;
		//입력한 상품 번호가 잘못되었을 경우 되묻기
		if (goods_num < 1 || goods_num >= NUM_OF_MENU)
			cout << "잘못 입력하셨습니다." << endl;
	}

	//구매한 상품과 가격 표시
	cout << goods[goods_num] << "을 선택하셨습니다." << endl;
	cout << "단가는 " << price[goods_num] << "원입니다." << endl;

	while (1) {
		cout << "몇개를 구매하시겠습니까?  ";
		cin >> num;

		//만약 선택한 상품의 재고가 부족하다면 수량 다시 선택
		if (num > stock[goods_num]) {
			cout << "재고가 부족합니다." << endl;
		}
		else
			break;
	}

	amount[goods_num] += num; //구매한 수량
	accum_amount[goods_num] += num;//누적 구매한 수량

	stock[goods_num] -= num; //남은 재고

	total[goods_num] += price[goods_num] * num; //각 상품의 가격 총합
	accum_total[goods_num] += price[goods_num] * num;//각 상품의 누적 가격 총합

	cout << "구매하신 금액은 " << price[goods_num] * num << "입니다." << endl;

}

//메뉴 취소
void MENU::delete_menu() {
	int goods_num = 0; //상품 번호
	int num; //상품 갯수

	while (goods_num < 1 || goods_num >= NUM_OF_MENU) {
		cout << "어떤 상품을 취소하시겠습니까?";
		cin >> goods_num;
		//입력한 상품 번호가 잘못되었을 때 되묻기
		if (goods_num < 1 || goods_num >= NUM_OF_MENU)
			cout << "잘못 입력하셨습니다.  " << endl;
	}

	while (1) {
		cout << goods[goods_num] << " 몇개를 취소하시겠습니까?  ";
		cin >> num;

		//만약 취소 수량이 구매 수량보다 많다면
		if (num > amount[goods_num])
			cout << "갯수가 구매한 수량보다 많습니다.  " << endl;
		else
			break;
	}

	amount[goods_num] -= num;			//취소한 만큼 구매한 갯수 차감
	accum_amount[goods_num] -= num;		//취소한 만큼 구매한 누적 갯수 차감
	stock[goods_num] += num;			//취소한 만큼 재고 입고

	total[goods_num] -= price[goods_num] * num; //취소한 금액만큼 총 금액에서 차감
	accum_total[goods_num] -= price[goods_num] * num;//취소한 금액만큼 누적 금액에서 차감
}

//결제 진행
void MENU::show_pay() {
	int insert; //투입한 금액
	//구매한 상품의 가격의 총합 계산
	for (int i = 0; i < NUM_OF_MENU; i++) {
		sum += total[i];
	}
	cout << "구매하신 총 금액은 " << sum << "입니다." << endl;

	//금액을 모두 지불할 때까지 반복
	while (pay < sum) {
		cout << "결제금액을 입금해주시기 바랍니다." << endl;
		cout << "결제금액 : ";
		cin >> insert; //투입한 금액
		pay += insert; //총 지불한 금액
		//만약 지불한 금액이 총 금액보다 작다면
		if (pay < sum)
			cout << "결제금액에서 " << sum - pay << "원이 부족합니다." << endl;
	}

}

//영수증 출력
void MENU::show_rec() {
	cout << endl << "======== 영 수 증 ========" << endl;
	cout << setw(8) << "품목" << setw(13) << "수량" << setw(6) << "금액" << endl;
	for (int i = 0; i < NUM_OF_MENU; i++) {
		if (amount[i] > 0)
			cout << setw(8) << goods[i] << setw(5) << amount[i] << setw(6) << total[i] << endl;
	}
	cout << "==========================" << endl;
	cout << "총구매금액" << setw(13) << sum << "원" << endl;
	cout << "받은금액" << setw(13) << pay << "원" << endl;
	cout << "거스름돈" << setw(13) << pay - sum << "원" << endl;
	cout << "감사합니다~ 좋은 하루 되세요!" << endl;

	reset();
	system("pause");
}

void MENU::reset() {
	for (int i = 1; i < NUM_OF_MENU; i++) {
		amount[i] = 0;
		total[i] = 0;
	}
	pay = 0;
	sum = 0;
}

//재고 관리
void MENU::run_control() {
	int task_num; //업무 번호

	do {
		system("cls");
		cout << "======== 재고 관리 ========" << endl;
		cout << "1. 재고조회" << endl << "2. 상품입고" << endl << "3. 상품반품" << endl << "4. 이전메뉴" << endl;
		cout << "==========================" << endl;

		cout << "어떤 업무를 하시겠습니까?  ";
		cin >> task_num;

		switch (task_num) {
		case 1: //재고조회
			check_stock();
			break;
		case 2: //상품입고
			get_stock();
			break;
		case 3: //상품반품
			return_stock();
			break;
		case 4: //이전메뉴
			return;
		default:
			cout << "잘못 입력했습니다. 다시 입력해주세요.";
		}
	} while (task_num != 4);

}

//재고 조회
void MENU::check_stock() {
	system("cls");
	cout << "======== 재고 조회 ========" << endl;
	//재고 출력
	for (int i = 1; i < NUM_OF_MENU; i++) {
		cout << i << ". " << goods[i] << setw(5) << stock[i] << endl;
	}
	system("pause");
}

//상품 입고
void MENU::get_stock() {
	int goods_num; //상품 번호
	int num;//상품 갯수
	for (int i = 1; i < NUM_OF_MENU; i++) {
		cout << i << ". " << goods[i] << endl;
	}
	cout << "어떤 상품을 입고하시겠습니까?" << endl;
	cin >> goods_num;

	cout << "몇개를 입고하시겠습니까?" << endl;
	cin >> num;

	stock[goods_num] += num; //재고에 입고한 수량만큼 추가
	order_stock[goods_num] += num;
	
	cout << goods[goods_num] << " 상품이" << num << "개 입고되었습니다." << endl;
	system("pause");
}

//상품 반품
void MENU::return_stock() {
	int goods_num; //상품 번호
	int num;//상품 갯수
	for (int i = 1; i < NUM_OF_MENU; i++) {
		cout << i << ". " << goods[i] << endl;
	}
	cout << "어떤 상품을 반품하시겠습니까?" << endl;
	cin >> goods_num;

	cout << "몇개를 반품하시겠습니까?" << endl;
	cin >> num;

	stock[goods_num] -= num; //재고에 반품한 수량만큼 차감

	cout << goods[goods_num] << " 상품이" << num << "개 반품되었습니다." << endl;
	system("pause");
}
	
/*관리자 비밀번호 확인*/
bool MENU::check_password() {
	string input;
	cout << "비밀번호를 입력해주세요.  ";
	cin >> input;
	if (input == password)
		return true;
	else {
		cout << "비밀번호가 일치하지 않습니다. " << endl;
		return false;
	}
	system("pause");
}

/*관리자 모드*/
void MENU::run_manager() {
	cout << "관리자 모드 실행" << endl;
	int task_num;

	do {
		cout << "======== 관리자 모드 ========" << endl;
		cout << "1. 상품조회" << endl << "2. 상품변경" << endl << "3. 단가변경" <<
			endl << "4. 매출실적현황" << endl << "5. 이전메뉴" << endl << "6. 비밀번호 변경" << endl;
		cout << "=============================" << endl;

		cout << "어떤 업무를 하시겠습니까?  ";
		cin >> task_num;

		switch (task_num) {
		case 1:
			check_goods();
			break;
		case 2:
			change_goods();
			break;
		case 3:
			change_price();
			break;
		case 4:
			sales_status();
			break;
		case 5:
			return;
		case 6:
			change_password();
			break;
		default:
			cout << "잘못 입력했습니다. 다시 입력해주세요.";
		}
	} while (task_num != 5);
}

//상품조회
void MENU::check_goods() {
	cout << "======== 상품 조회 ========" << endl;
	for (int i = 1; i < NUM_OF_MENU; i++) {
		cout << i << ". " << goods[i] << setw(5) << price[i] << endl;
	}
}

//상품변경
void MENU::change_goods() {
	int goods_num = 0;
	string new_name = " ";
	while (goods_num < 1 || goods_num >= NUM_OF_MENU) {
		cout << "어떤 상품을 변경하시겠습니까?  " << endl;
		cin >> goods_num;
		if (goods_num < 1 || goods_num >= NUM_OF_MENU) {
			cout << "잘못 입력하셨습니다." << endl;
		}
		else
			break;
	}

	while (1) {
		cin.ignore();
		cout << goods[goods_num] << "의 새로운 상품명을 입력해주세요.  ";
		getline(cin, new_name);
		if (new_name == " ")
			cout << "잘못 입력하셨습니다." << endl;
		else
			break;
	}
	cout << goods[goods_num] << "의 상품명을 " << new_name << "으로 변경하였습니다." << endl;
	goods[goods_num] = new_name;

}

//단가변경
void MENU::change_price() {
	int goods_num = 0;
	int new_price = 0;
	while (goods_num < 1 || goods_num >= NUM_OF_MENU) {
		cout << "어떤 상품의 단가를 변경하시겠습니까?  ";
		cin >> goods_num;
		if (goods_num < 1 || goods_num >= NUM_OF_MENU)
			cout << "잘못 입력하셨습니다." << endl;
		else
			break;
	}

	while (new_price <= 0) {
		cout << goods[goods_num] << "의 가격을 얼마로 변경하시겠습니까?  ";
		cin >> new_price;
		if (new_price <= 0)
			cout << "상품 가격은 0보다 커야합니다.";
		else
			break;
	}

	cout << goods[goods_num] << "의 가격을 " << new_price << "원으로 변경하였습니다." << endl;
	price[goods_num] = new_price;
}

//매출실적현황
void MENU::sales_status() {
	int task_num;
	cout << "========매출 실적 현황========" << endl;
	cout << "1. 매출현황조회" << endl << "2. 주문상품조회" << endl << "3. 거래처현황" << endl << "4. 이전메뉴" << endl;
	cout << "어떤 업무를 하시겠습니까?  ";
	cin >> task_num;
	switch (task_num) {
	case 1:
		check_sales();
		break;
	case 2:
		check_order();
		break;
	case 3:
		customer_status();
		break;
	case 4:
		return;
	default:
		cout << "잘못 입력하셨습니다. 다시 입력해주세요." << endl;
	}
}

//비밀번호변경
void MENU::change_password() {
	string input;
	if (check_password()) {
		cout << "변경할 비밀번호를 입력해주세요.  ";
		cin >> input;
		password = input;
		cout << "비밀번호가 성공적으로 변경되었습니다." << endl;
	}

}

/*매출실적현황*/

//매출현황조회
void MENU::check_sales() {
	int accum_num = 0;
	int accum_price = 0;
	cout << "========매출 현황 조회========" << endl;
	cout << "품명         누적판매수량   누적판매금액   " << endl;
	for (int i = 1; i < NUM_OF_MENU; i++) {
		if (accum_amount[i] > 0) {
			cout << goods[i] << setw(10) << accum_amount[i] << setw(10) << accum_total[i] << endl;
			accum_num += accum_amount[i];
			accum_price += accum_total[i];
		}
	}
	cout << "==============================" << endl;
	cout << "             " << accum_num << "    " << accum_price << endl;
}

//주문상품조회
void MENU::check_order() {
	int num = 0;
	cout << "========주문 상품 조회========" << endl;
	cout << "품명            재고수량" << endl;
	for (int i = 1; i < NUM_OF_MENU; i++) {
		if (stock[i] < 4) {
			cout << goods[i] << setw(10) << stock[i] << endl;
			num = 1;
		}
	}
	if (num == 0)
		cout << endl << "모든 상품의 재고가 충분합니다." << endl;
}

//거래처현황
void MENU::customer_status() {
	int task_num;
	cout << "========거래처 현황========" << endl;
	cout << "1. 거래품목 현황조회" << endl << "2. 거래품목 입고 현황조회" << endl << "3. 거래단가 변경" << endl << "4. 이전메뉴" << endl;
	cout << "어떤 업무를 하시겠습니까?  ";
	cin >> task_num;
	switch (task_num) {
	case 1:
		check_tradeItem();
		break;
	case 2:
		check_warehouse();
		break;
	case 3:
		change_tradePrice();
		break;
	case 4:
		return;
	default:
		cout << "잘못 입력하셨습니다. 다시 입력해주세요." << endl;
	}
}



/*거래처 현황*/

//거래품목 현황조회
void MENU::check_tradeItem() {
	cout << "========거래품목 현황조회========" << endl;
	cout << "상품명        판매단가      거래단가" << endl;
	for (int i = 1; i < NUM_OF_MENU; i++) {
		cout << goods[i] << setw(14) << price[i] << setw(14) << trans_price[i] << endl;
	}
}

//거래품목 입고 현황조회
void MENU::check_warehouse() {
	int sum = 0;
	cout << "========거래품목 입고 현황조회========" << endl;
	cout << "상품명        총입고수량     제품별 결제금액" << endl;
	for (int i = 1; i < NUM_OF_MENU; i++) {
		if (order_stock[i] > 0) {
			cout << goods[i] << setw(14) << order_stock[i] << setw(14) << trans_price[i] * order_stock[i] << endl;
			sum += trans_price[i] * order_stock[i];
		}
	}
	cout << "                          총 결제금액" << endl;
	cout << "                          " << sum << endl;

}

//거래단가 변경
void MENU::change_tradePrice() {
	cout << "========거래단가 변경========" << endl;
	int goods_num = 0;
	int new_price = 0;
	while (goods_num < 1 || goods_num >= NUM_OF_MENU) {
		cout << "어떤 상품의 거래단가를 변경하시겠습니까?  ";
		cin >> goods_num;
		if (goods_num < 1 || goods_num >= NUM_OF_MENU)
			cout << "잘못 입력하셨습니다." << endl;
		else
			break;
	}

	while (new_price <= 0) {
		cout << goods[goods_num] << "의 거래단가를 얼마로 변경하시겠습니까?  ";
		cin >> new_price;
		if (new_price <= 0)
			cout << "상품 가격은 0보다 커야합니다.";
		else
			break;
	}

	cout << goods[goods_num] << "의 거래단가를 " << new_price << "원으로 변경하였습니다." << endl;
	trans_price[goods_num] = new_price;

}

void MENU::end_menu() {
	ofstream fout;
	fout.open("goods.txt");
	if (!fout) {
		cout << "goods.txt 파일을 열 수 없습니다." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fout << goods[i] << endl;
	}
	fout.close();

	fout.open("stock.txt");
	if (!fout) {
		cout << "stock.txt 파일을 열 수 없습니다." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fout << stock[i] << endl;
	}
	fout.close();

	fout.open("price.txt");
	if (!fout) {
		cout << "price.txt 파일을 열 수 없습니다." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fout << price[i] << endl;
	}
	fout.close();

	fout.open("trans_price.txt");
	if (!fout) {
		cout << "trans_price.txt 파일을 열 수 없습니다." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fout << trans_price[i] << endl;
	}
	fout.close();
}

int main() {
	MENU menu;
	menu.start_menu();

	return 0;
}