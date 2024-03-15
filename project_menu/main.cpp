#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>
using namespace std;

#define NUM_OF_MENU 6 //��ǰ�� �� ����

class MENU {
private:
	string goods[NUM_OF_MENU] = { "", }; //��ǰ��
	int price[NUM_OF_MENU] = { 0, }; //��ǰ ����
	int trans_price[NUM_OF_MENU] = { 0, }; //��ǰ�� �ŷ� �ܰ�
	int amount[NUM_OF_MENU] = { 0, }; //������ ��ǰ�� ����
	int accum_amount[NUM_OF_MENU] = { 0, };
	int total[NUM_OF_MENU] = { 0, }; //������ ��ǰ�� �� ����
	int accum_total[NUM_OF_MENU] = { 0, };
	int stock[NUM_OF_MENU] = { 0, }; //��ǰ ���
	int order_stock[NUM_OF_MENU] = { 0, };
	int pay = 0; //������ �ݾ�
	int sum = 0; //�� �ݾ�(�����ؾ��ϴ� �ݾ�)
	string password = "0000";
public:
	MENU();
	//���α׷� ����
	void start_menu();

	//��ǰ �Ǹ�
	void run_sale();
	void show_menu();
	void selete_menu();
	void delete_menu();
	void show_pay();
	void show_rec();
	void reset();

	//��� ����
	void run_control();
	void check_stock();
	void get_stock();
	void return_stock();

	//������ ��� ��й�ȣ Ȯ��
	bool check_password();
	//������ ���
	void run_manager();
	void check_goods();
	void change_goods();
	void change_price();
	void sales_status();
	void change_password();

	//���������Ȳ
	void check_sales();
	void check_order();
	void customer_status();

	//�ŷ�ó ��Ȳ
	void check_tradeItem();
	void check_warehouse();
	void change_tradePrice();

	void end_menu();

};

MENU::MENU() {
	ifstream fin;
	fin.open("goods.txt");
	if (!fin) {
		cout << "goods.txt ������ �� �� �����ϴ�." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fin >> goods[i];
	}
	fin.close();

	fin.open("stock.txt");
	if (!fin) {
		cout << "stock.txt ������ �� �� �����ϴ�." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fin >> stock[i];
	}
	fin.close();

	fin.open("price.txt");
	if (!fin) {
		cout << "price.txt ������ �� �� �����ϴ�." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fin >> price[i];
	}
	fin.close();

	fin.open("trans_price.txt");
	if (!fin) {
		cout << "trans_price.txt ������ �� �� �����ϴ�." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fin >> trans_price[i];
	}
	fin.close();
}

void MENU::start_menu() {
	int task_num; //���� ��ȣ

	do {
		system("cls");
		cout << "======== ���� �޴� ========" << endl;
		cout << "1. ��ǰ�Ǹ�" << endl << "2. ������" << endl << "3. ����" << endl << "4. ������ ���" << endl;
		cout << "===========================" << endl;

		cout << "� ������ �Ͻðڽ��ϱ�?  ";
		cin >> task_num;

		switch (task_num) {
		case 1: //��ǰ�Ǹ� ����
			run_sale();
			break;
		case 2: //������ ����
			run_control();
			break;
		case 3: //����
			end_menu();
			break;
		case 4:

			if (check_password())
				run_manager(); //�����ڸ�� ����
			break;
		default:
			cout << "�߸� �Է��߽��ϴ�. �ٽ� �Է����ּ���.";
		}
	} while (task_num != 3);

}




//��ǰ�Ǹ�
void MENU::run_sale() {
	char m = '1'; //�߰����� ���� flag
	char n = '1';//������� ���� flag
	while (m == '1' || m == 'Y' || m == 'y') {
		show_menu(); //�޴� ���
		selete_menu(); //�޴� ����
		//1 or Y�� �ԷµǸ� �߰����� ����, 0 or N�� �ԷµǸ� ���� ����
		cout << "�� �����Ͻðڽ��ϱ�? (��:1/Y, �ƴϿ�: 0/N)  ";
		cin >> m;
	}

	cout << "��ǰ�� ����Ͻðڽ��ϱ�? (��:1/Y, �ƴϿ�: 0/N)  ";
	cin >> n;
	while (1) {
		if (n == '1' || n == 'Y' || n == 'y') {
			delete_menu();
			cout << "�� ����Ͻðڽ��ϱ�? (��:1/Y, �ƴϿ�: 0/N)  ";
			cin >> n;
		}
		else
			break;
	}
	//���� ����
	show_pay();

	//������ ���
	show_rec();
}

//�޴� ���
void MENU::show_menu() {
	cout << "======== ��ǰ �޴� ========" << endl;
	for (int i = 1; i < NUM_OF_MENU; i++) {
		cout << i << ". " << goods[i] << '\t' << price[i] << "��" << "  " << stock[i] << "��" << endl;
	}
	cout << "==========================" << endl;
}

//�޴� ����
void MENU::selete_menu() {
	int goods_num = 0; //��ǰ ��ȣ
	int num = 0;//��ǰ ����
	char m = '1';

	//����ó��
	while (goods_num < 1 || goods_num >= NUM_OF_MENU) {
		cout << "� ��ǰ�� �����Ͻðڽ��ϱ�?  ";
		cin >> goods_num;
		//�Է��� ��ǰ ��ȣ�� �߸��Ǿ��� ��� �ǹ���
		if (goods_num < 1 || goods_num >= NUM_OF_MENU)
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
	}

	//������ ��ǰ�� ���� ǥ��
	cout << goods[goods_num] << "�� �����ϼ̽��ϴ�." << endl;
	cout << "�ܰ��� " << price[goods_num] << "���Դϴ�." << endl;

	while (1) {
		cout << "��� �����Ͻðڽ��ϱ�?  ";
		cin >> num;

		//���� ������ ��ǰ�� ��� �����ϴٸ� ���� �ٽ� ����
		if (num > stock[goods_num]) {
			cout << "��� �����մϴ�." << endl;
		}
		else
			break;
	}

	amount[goods_num] += num; //������ ����
	accum_amount[goods_num] += num;//���� ������ ����

	stock[goods_num] -= num; //���� ���

	total[goods_num] += price[goods_num] * num; //�� ��ǰ�� ���� ����
	accum_total[goods_num] += price[goods_num] * num;//�� ��ǰ�� ���� ���� ����

	cout << "�����Ͻ� �ݾ��� " << price[goods_num] * num << "�Դϴ�." << endl;

}

//�޴� ���
void MENU::delete_menu() {
	int goods_num = 0; //��ǰ ��ȣ
	int num; //��ǰ ����

	while (goods_num < 1 || goods_num >= NUM_OF_MENU) {
		cout << "� ��ǰ�� ����Ͻðڽ��ϱ�?";
		cin >> goods_num;
		//�Է��� ��ǰ ��ȣ�� �߸��Ǿ��� �� �ǹ���
		if (goods_num < 1 || goods_num >= NUM_OF_MENU)
			cout << "�߸� �Է��ϼ̽��ϴ�.  " << endl;
	}

	while (1) {
		cout << goods[goods_num] << " ��� ����Ͻðڽ��ϱ�?  ";
		cin >> num;

		//���� ��� ������ ���� �������� ���ٸ�
		if (num > amount[goods_num])
			cout << "������ ������ �������� �����ϴ�.  " << endl;
		else
			break;
	}

	amount[goods_num] -= num;			//����� ��ŭ ������ ���� ����
	accum_amount[goods_num] -= num;		//����� ��ŭ ������ ���� ���� ����
	stock[goods_num] += num;			//����� ��ŭ ��� �԰�

	total[goods_num] -= price[goods_num] * num; //����� �ݾ׸�ŭ �� �ݾ׿��� ����
	accum_total[goods_num] -= price[goods_num] * num;//����� �ݾ׸�ŭ ���� �ݾ׿��� ����
}

//���� ����
void MENU::show_pay() {
	int insert; //������ �ݾ�
	//������ ��ǰ�� ������ ���� ���
	for (int i = 0; i < NUM_OF_MENU; i++) {
		sum += total[i];
	}
	cout << "�����Ͻ� �� �ݾ��� " << sum << "�Դϴ�." << endl;

	//�ݾ��� ��� ������ ������ �ݺ�
	while (pay < sum) {
		cout << "�����ݾ��� �Ա����ֽñ� �ٶ��ϴ�." << endl;
		cout << "�����ݾ� : ";
		cin >> insert; //������ �ݾ�
		pay += insert; //�� ������ �ݾ�
		//���� ������ �ݾ��� �� �ݾ׺��� �۴ٸ�
		if (pay < sum)
			cout << "�����ݾ׿��� " << sum - pay << "���� �����մϴ�." << endl;
	}

}

//������ ���
void MENU::show_rec() {
	cout << endl << "======== �� �� �� ========" << endl;
	cout << setw(8) << "ǰ��" << setw(13) << "����" << setw(6) << "�ݾ�" << endl;
	for (int i = 0; i < NUM_OF_MENU; i++) {
		if (amount[i] > 0)
			cout << setw(8) << goods[i] << setw(5) << amount[i] << setw(6) << total[i] << endl;
	}
	cout << "==========================" << endl;
	cout << "�ѱ��űݾ�" << setw(13) << sum << "��" << endl;
	cout << "�����ݾ�" << setw(13) << pay << "��" << endl;
	cout << "�Ž�����" << setw(13) << pay - sum << "��" << endl;
	cout << "�����մϴ�~ ���� �Ϸ� �Ǽ���!" << endl;

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

//��� ����
void MENU::run_control() {
	int task_num; //���� ��ȣ

	do {
		system("cls");
		cout << "======== ��� ���� ========" << endl;
		cout << "1. �����ȸ" << endl << "2. ��ǰ�԰�" << endl << "3. ��ǰ��ǰ" << endl << "4. �����޴�" << endl;
		cout << "==========================" << endl;

		cout << "� ������ �Ͻðڽ��ϱ�?  ";
		cin >> task_num;

		switch (task_num) {
		case 1: //�����ȸ
			check_stock();
			break;
		case 2: //��ǰ�԰�
			get_stock();
			break;
		case 3: //��ǰ��ǰ
			return_stock();
			break;
		case 4: //�����޴�
			return;
		default:
			cout << "�߸� �Է��߽��ϴ�. �ٽ� �Է����ּ���.";
		}
	} while (task_num != 4);

}

//��� ��ȸ
void MENU::check_stock() {
	system("cls");
	cout << "======== ��� ��ȸ ========" << endl;
	//��� ���
	for (int i = 1; i < NUM_OF_MENU; i++) {
		cout << i << ". " << goods[i] << setw(5) << stock[i] << endl;
	}
	system("pause");
}

//��ǰ �԰�
void MENU::get_stock() {
	int goods_num; //��ǰ ��ȣ
	int num;//��ǰ ����
	for (int i = 1; i < NUM_OF_MENU; i++) {
		cout << i << ". " << goods[i] << endl;
	}
	cout << "� ��ǰ�� �԰��Ͻðڽ��ϱ�?" << endl;
	cin >> goods_num;

	cout << "��� �԰��Ͻðڽ��ϱ�?" << endl;
	cin >> num;

	stock[goods_num] += num; //��� �԰��� ������ŭ �߰�
	order_stock[goods_num] += num;
	
	cout << goods[goods_num] << " ��ǰ��" << num << "�� �԰�Ǿ����ϴ�." << endl;
	system("pause");
}

//��ǰ ��ǰ
void MENU::return_stock() {
	int goods_num; //��ǰ ��ȣ
	int num;//��ǰ ����
	for (int i = 1; i < NUM_OF_MENU; i++) {
		cout << i << ". " << goods[i] << endl;
	}
	cout << "� ��ǰ�� ��ǰ�Ͻðڽ��ϱ�?" << endl;
	cin >> goods_num;

	cout << "��� ��ǰ�Ͻðڽ��ϱ�?" << endl;
	cin >> num;

	stock[goods_num] -= num; //��� ��ǰ�� ������ŭ ����

	cout << goods[goods_num] << " ��ǰ��" << num << "�� ��ǰ�Ǿ����ϴ�." << endl;
	system("pause");
}
	
/*������ ��й�ȣ Ȯ��*/
bool MENU::check_password() {
	string input;
	cout << "��й�ȣ�� �Է����ּ���.  ";
	cin >> input;
	if (input == password)
		return true;
	else {
		cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�. " << endl;
		return false;
	}
	system("pause");
}

/*������ ���*/
void MENU::run_manager() {
	cout << "������ ��� ����" << endl;
	int task_num;

	do {
		cout << "======== ������ ��� ========" << endl;
		cout << "1. ��ǰ��ȸ" << endl << "2. ��ǰ����" << endl << "3. �ܰ�����" <<
			endl << "4. ���������Ȳ" << endl << "5. �����޴�" << endl << "6. ��й�ȣ ����" << endl;
		cout << "=============================" << endl;

		cout << "� ������ �Ͻðڽ��ϱ�?  ";
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
			cout << "�߸� �Է��߽��ϴ�. �ٽ� �Է����ּ���.";
		}
	} while (task_num != 5);
}

//��ǰ��ȸ
void MENU::check_goods() {
	cout << "======== ��ǰ ��ȸ ========" << endl;
	for (int i = 1; i < NUM_OF_MENU; i++) {
		cout << i << ". " << goods[i] << setw(5) << price[i] << endl;
	}
}

//��ǰ����
void MENU::change_goods() {
	int goods_num = 0;
	string new_name = " ";
	while (goods_num < 1 || goods_num >= NUM_OF_MENU) {
		cout << "� ��ǰ�� �����Ͻðڽ��ϱ�?  " << endl;
		cin >> goods_num;
		if (goods_num < 1 || goods_num >= NUM_OF_MENU) {
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		}
		else
			break;
	}

	while (1) {
		cin.ignore();
		cout << goods[goods_num] << "�� ���ο� ��ǰ���� �Է����ּ���.  ";
		getline(cin, new_name);
		if (new_name == " ")
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		else
			break;
	}
	cout << goods[goods_num] << "�� ��ǰ���� " << new_name << "���� �����Ͽ����ϴ�." << endl;
	goods[goods_num] = new_name;

}

//�ܰ�����
void MENU::change_price() {
	int goods_num = 0;
	int new_price = 0;
	while (goods_num < 1 || goods_num >= NUM_OF_MENU) {
		cout << "� ��ǰ�� �ܰ��� �����Ͻðڽ��ϱ�?  ";
		cin >> goods_num;
		if (goods_num < 1 || goods_num >= NUM_OF_MENU)
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		else
			break;
	}

	while (new_price <= 0) {
		cout << goods[goods_num] << "�� ������ �󸶷� �����Ͻðڽ��ϱ�?  ";
		cin >> new_price;
		if (new_price <= 0)
			cout << "��ǰ ������ 0���� Ŀ���մϴ�.";
		else
			break;
	}

	cout << goods[goods_num] << "�� ������ " << new_price << "������ �����Ͽ����ϴ�." << endl;
	price[goods_num] = new_price;
}

//���������Ȳ
void MENU::sales_status() {
	int task_num;
	cout << "========���� ���� ��Ȳ========" << endl;
	cout << "1. ������Ȳ��ȸ" << endl << "2. �ֹ���ǰ��ȸ" << endl << "3. �ŷ�ó��Ȳ" << endl << "4. �����޴�" << endl;
	cout << "� ������ �Ͻðڽ��ϱ�?  ";
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
		cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���." << endl;
	}
}

//��й�ȣ����
void MENU::change_password() {
	string input;
	if (check_password()) {
		cout << "������ ��й�ȣ�� �Է����ּ���.  ";
		cin >> input;
		password = input;
		cout << "��й�ȣ�� ���������� ����Ǿ����ϴ�." << endl;
	}

}

/*���������Ȳ*/

//������Ȳ��ȸ
void MENU::check_sales() {
	int accum_num = 0;
	int accum_price = 0;
	cout << "========���� ��Ȳ ��ȸ========" << endl;
	cout << "ǰ��         �����Ǹż���   �����Ǹűݾ�   " << endl;
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

//�ֹ���ǰ��ȸ
void MENU::check_order() {
	int num = 0;
	cout << "========�ֹ� ��ǰ ��ȸ========" << endl;
	cout << "ǰ��            ������" << endl;
	for (int i = 1; i < NUM_OF_MENU; i++) {
		if (stock[i] < 4) {
			cout << goods[i] << setw(10) << stock[i] << endl;
			num = 1;
		}
	}
	if (num == 0)
		cout << endl << "��� ��ǰ�� ��� ����մϴ�." << endl;
}

//�ŷ�ó��Ȳ
void MENU::customer_status() {
	int task_num;
	cout << "========�ŷ�ó ��Ȳ========" << endl;
	cout << "1. �ŷ�ǰ�� ��Ȳ��ȸ" << endl << "2. �ŷ�ǰ�� �԰� ��Ȳ��ȸ" << endl << "3. �ŷ��ܰ� ����" << endl << "4. �����޴�" << endl;
	cout << "� ������ �Ͻðڽ��ϱ�?  ";
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
		cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���." << endl;
	}
}



/*�ŷ�ó ��Ȳ*/

//�ŷ�ǰ�� ��Ȳ��ȸ
void MENU::check_tradeItem() {
	cout << "========�ŷ�ǰ�� ��Ȳ��ȸ========" << endl;
	cout << "��ǰ��        �ǸŴܰ�      �ŷ��ܰ�" << endl;
	for (int i = 1; i < NUM_OF_MENU; i++) {
		cout << goods[i] << setw(14) << price[i] << setw(14) << trans_price[i] << endl;
	}
}

//�ŷ�ǰ�� �԰� ��Ȳ��ȸ
void MENU::check_warehouse() {
	int sum = 0;
	cout << "========�ŷ�ǰ�� �԰� ��Ȳ��ȸ========" << endl;
	cout << "��ǰ��        ���԰����     ��ǰ�� �����ݾ�" << endl;
	for (int i = 1; i < NUM_OF_MENU; i++) {
		if (order_stock[i] > 0) {
			cout << goods[i] << setw(14) << order_stock[i] << setw(14) << trans_price[i] * order_stock[i] << endl;
			sum += trans_price[i] * order_stock[i];
		}
	}
	cout << "                          �� �����ݾ�" << endl;
	cout << "                          " << sum << endl;

}

//�ŷ��ܰ� ����
void MENU::change_tradePrice() {
	cout << "========�ŷ��ܰ� ����========" << endl;
	int goods_num = 0;
	int new_price = 0;
	while (goods_num < 1 || goods_num >= NUM_OF_MENU) {
		cout << "� ��ǰ�� �ŷ��ܰ��� �����Ͻðڽ��ϱ�?  ";
		cin >> goods_num;
		if (goods_num < 1 || goods_num >= NUM_OF_MENU)
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		else
			break;
	}

	while (new_price <= 0) {
		cout << goods[goods_num] << "�� �ŷ��ܰ��� �󸶷� �����Ͻðڽ��ϱ�?  ";
		cin >> new_price;
		if (new_price <= 0)
			cout << "��ǰ ������ 0���� Ŀ���մϴ�.";
		else
			break;
	}

	cout << goods[goods_num] << "�� �ŷ��ܰ��� " << new_price << "������ �����Ͽ����ϴ�." << endl;
	trans_price[goods_num] = new_price;

}

void MENU::end_menu() {
	ofstream fout;
	fout.open("goods.txt");
	if (!fout) {
		cout << "goods.txt ������ �� �� �����ϴ�." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fout << goods[i] << endl;
	}
	fout.close();

	fout.open("stock.txt");
	if (!fout) {
		cout << "stock.txt ������ �� �� �����ϴ�." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fout << stock[i] << endl;
	}
	fout.close();

	fout.open("price.txt");
	if (!fout) {
		cout << "price.txt ������ �� �� �����ϴ�." << endl;
		return;
	}
	for (int i = 1; i < NUM_OF_MENU; i++) {
		fout << price[i] << endl;
	}
	fout.close();

	fout.open("trans_price.txt");
	if (!fout) {
		cout << "trans_price.txt ������ �� �� �����ϴ�." << endl;
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