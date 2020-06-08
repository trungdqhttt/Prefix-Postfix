#include<iostream>
using namespace std;
#include<string>

// ============================= KHỞI TẠO CẤU TRÚC STACK =============================

// khai báo cấu trúc 1 cái node
struct NODE
{
	string data; // dữ liệu của node
	NODE* pNext; // con trỏ liên kết đến các node khác trong stack
};

// khai báo cấu trúc STACK
struct STACK
{
	NODE* pTop; // con trỏ quản lý đầu STACK
};

// hàm khởi tạo node
NODE* KhoiTaoNode(string x)
{
	NODE* p = new NODE;
	p->data = x;
	p->pNext = NULL;
	return p;
}

// hàm kiểm tra xem STACK có rỗng hay không, trả về true nếu STACK rỗng, ngược lại trả về false
bool IsEmpty(STACK& s)
{
	if (s.pTop == NULL)
	{
		return true;
	}
	return false;
}

// hàm thêm node p vào đầu danh sách - hàm thêm phần tử vào STACK
bool Push(STACK& s, NODE* p)
{
	if (IsEmpty(s) == true)
	{
		s.pTop = p;
	}
	else
	{
		p->pNext = s.pTop;
		s.pTop = p;
	}
	return true;
}

// hàm lấy phần tử đầu STACK ra và xóa phần tử đầu STACK
bool Pop(STACK& s, string& x)
{
	if (IsEmpty(s) == true)
	{
		return false;
	}
	else
	{
		x = s.pTop->data; // lưu dữ liệu lại trước khi xóa
		NODE* k = s.pTop;
		s.pTop = s.pTop->pNext;
		delete k;
	}
	return true;
}

// hàm lấy phần tử đầu STACK ra xem
bool Top(STACK s, string& x)
{
	if (IsEmpty(s) == true)
	{
		return false;
	}
	else
	{
		x = s.pTop->data;
	}
	return true;
}
struct QUEUE
{
	NODE* pTop; // con trỏ quản lý đầu QUEUE
};

// hàm kiểm tra xem QUEUE có rỗng hay không, trả về true nếu QUEUE rỗng, ngược lại trả về false
bool IsEmpty(QUEUE& q)
{
	if (q.pTop == NULL)
	{
		return true;
	}
	return false;
}

// hàm thêm node p vào cuối danh sách - hàm thêm phần tử vào QUEUE
bool Push(QUEUE& q, NODE* p)
{
	if (IsEmpty(q) == true)
	{
		q.pTop = p;
	}
	else
	{
		for (NODE* k = q.pTop; k != NULL; k = k->pNext)
		{
			if (k->pNext == NULL)
			{
				k->pNext = p;
				return true;
			}
		}
	}
	return true;
}

// hàm lấy phần tử đầu QUEUE ra và xóa phần tử đầu QUEUE
bool Pop(QUEUE& q, string& x)
{
	if (IsEmpty(q) == true)
	{
		return false;
	}
	else
	{
		x = q.pTop->data; // lưu dữ liệu lại trước khi xóa
		NODE* k = q.pTop;
		q.pTop = q.pTop->pNext;
		delete k;
	}
	return true;
}

// hàm lấy phần tử đầu QUEUE ra xem
bool Top(QUEUE& q, string& x)
{
	if (IsEmpty(q) == true)
	{
		return false;
	}
	else
	{
		x = q.pTop->data;
	}
	return true;
}

int getPriority(string op) {
	if (op == "*" || op == "/") {
		return 2;
	}
	else if (op == "+" || op == "-") {
		return 1;
	}
	else {
		return 0;
	}
}

int isOperator(string op) {
	if (getPriority(op) == 0) { // != +, -, *, /
		if (op != "(" && op != ")") {
			return 0; // so 0 - 9
		}
		else { // ( || )
			return 1;
		}
	}
	return 2; // +, -, *, /
}

void Resolve(string str, STACK& s, QUEUE& q) {
	NODE* p;
	string number = ""; // luu toan hang co nhieu chu so
	for (int i = 0; i < str.length(); i++) {
		string sCurrent(1, str[i]);// char => string
		if (sCurrent != " ") {
			if (isOperator(sCurrent) == 0) { // la so 0 - 9
				number += sCurrent; // them toan hang vao chuoi number
			}
			else { // la toan tu or dau ngoac
				if (number.length() > 0) {
					p = KhoiTaoNode(number);
					Push(q, p); // push number <=> toan hang vao Queue
					number = ""; // cap nhat lai number = rong tiep tuc vong lap
				}
				if (isOperator(sCurrent) == 1) { // ( or ) 
					if (sCurrent == "(") {
						p = KhoiTaoNode(sCurrent);
						Push(s, p); // push vao Stack
					}
					else if (sCurrent == ")") {
						string pop;
						Pop(s, pop); // lay phan tu dau Stack ra kiem tra

						while (pop != "(") { // chay While den khi nao gap dau (
							p = KhoiTaoNode(pop);
							Push(q, p); // Push vao queue
							Pop(s, pop); // tiep tuc vong lap
						}
					}
				}
				else { // la toan tu
					string topS;
					Top(s, topS); // kiem tra phan dau dau Stack
					while (!IsEmpty(s) && getPriority(topS) >= getPriority(sCurrent)) { // kiem tra toan tu dau Stack voi toan tu hien tai
						Pop(s, topS);
						p = KhoiTaoNode(topS);		
						Push(q, p); // push vao Queue
						Top(s, topS); // tiep tuc lay phan tu dau Stack kiem tra
					}
					p = KhoiTaoNode(sCurrent);
					Push(s, p); // push toan tu hien tai vao Stack
				}
			}
		}
	}
	// kiem tra xem con toan hang nao khong
	if (number.length() > 0) {
		p = KhoiTaoNode(number);
		Push(q, p);
		number = "";
	}
	// kiem tra cac phan tu con lai trong Stack
	while (!IsEmpty(s)) {
		string data;
		Pop(s, data);
		p = KhoiTaoNode(data);
		Push(q, p);
	}
}

int Calculate(STACK& s, QUEUE& q) {
	string data;
	string tmp;
	string res;

	NODE* p = new NODE;
	int val1, val2;
	while (!IsEmpty(q)) {
		Pop(q, data);
		if (isOperator(data) == 0) { // la so 0 - 9
			p = KhoiTaoNode(data);
			Push(s, p); // push vao STACK
		}
		else if (isOperator(data) == 2) { // toan tu +, -, *, /
			Pop(s, tmp);
			val1 = stoi(tmp); // string to int
			Pop(s, tmp);
			val2 = stoi(tmp);
			if (data == "+") {
				res = to_string(val2 + val1); // int to string
				p = KhoiTaoNode(res);
				Push(s, p);
			}
			else if (data == "-") {
				res = to_string(val2 - val1);
				p = KhoiTaoNode(res);
				Push(s, p);
			}
			else if (data == "*") {
				res = to_string(val2 * val1);
				p = KhoiTaoNode(res);
				Push(s, p);
			}
			else {
				res = to_string(val2 / val1);
				p = KhoiTaoNode(res);
				Push(s, p);
			}
		}
	}
	Pop(s, data);
	return stoi(data);
}

int main() {
	STACK s;
	s.pTop = NULL; // STACK ĐANG RỖNG
	QUEUE q;
	q.pTop = NULL; // QUEUE ĐANG RỖNG
	string str;
	cout << "\n Nhap bieu thuc trung to can tinh: ";
	getline(cin, str);
	Resolve(str, s, q);

	QUEUE cal; // giu bieu thuc hau to de tinh toan
	cal.pTop = NULL;
	NODE* p = new NODE;

	cout << "\n Bieu thuc hau to: ";
	while (!IsEmpty(q)) {	
		string data;
		Pop(q, data);
		p = KhoiTaoNode(data);
		Push(cal, p);
		cout << data << " ";
	}
	cout << endl;

	cout << "\n\t KET QUA BIEU THUC = " << Calculate(s, cal) << endl;

	system("pause");
	return 0;
}