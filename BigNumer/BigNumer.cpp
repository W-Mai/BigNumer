// BigNumer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;

#define Max 401

string Get_sum(int a[], int b[], int length) {
	string result = "";
	int s[Max] = { 0 };
	int to_high = 0, l = length, i;
	for (i = 0; i < l; i++) {
		s[i] = (a[i] + b[i] + to_high) % 10;
		to_high = (a[i] + b[i] + to_high) / 10;
	}
	if (to_high > 0) s[l++] = 1;
	for (i = 0; i < l; i++) result.insert(0, to_string(s[i]));
	return result;
}

string Get_diff(int a[], int b[], int length) {
	string result = "";
	int s[Max] = { 0 };
	int need_high = 0, l = length, i;
	for (i = 0; i < l; i++) {
		if ((a[i] - need_high) < b[i]) {
			s[i] = a[i] + 10 - b[i] - need_high;
			need_high = 1;
		} else {
			s[i] = a[i] - b[i] - need_high;
			need_high = 0;
		}
	}
	for (i = 0; i < l; i++) result.insert(0, to_string(s[i]));
	while (result.length() > 0) {
		if (result[0] == '0') result.erase(0, 1);
		else break;
	}
	return result;
}

string Get_mul(int a[], int b[], int a_length, int b_length) {
	string result = "";
	int s[Max * 2] = { 0 };
	for (int i = 0; i < a_length; i++) {
		for (int j = 0; j < b_length; j++) {
			s[i + j] += a[i] * b[j];
		}
	}
	int to_high = 0, total = a_length + b_length;
	for (int i = 0; i < total; i++) {
		int temp = s[i];
		s[i] = (temp + to_high) % 10;
		to_high = (temp + to_high) / 10;
	}
	if (s[total - 1] == 0) total -= 1;
	for (int i = 0; i < total; i++) result.insert(0, to_string(s[i]));
	return result;
}

int main() {
	string a, b;
	while (cin >> a >> b) {
		int s1[Max] = { 0 }, s2[Max] = { 0 };
		bool a_flag = false, b_flag = false;
		if (a[0] == '-') {
			a.erase(0, 1);
			a_flag = true;
		}
		if (b[0] == '-') {
			b.erase(0, 1);
			b_flag = true;
		}
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		unsigned int k;
		for (k = 0; k < a.length(); k++) s1[k] = a[k] - 48;
		for (k = 0; k < b.length(); k++) s2[k] = b[k] - 48;
		string result;
		int length = max(a.length(), b.length());
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		if ((!a_flag) && (!b_flag)) {
			cout << Get_sum(s1, s2, length) << endl;

			if (a.length() > b.length() || (a.length() == b.length() && a >= b)) // a >= b
				cout << Get_diff(s1, s2, length) << endl;
				// cout << "YES" <<endl;
			else cout << "-" << Get_diff(s2, s1, length) << endl;

			cout << Get_mul(s1, s2, a.length(), b.length()) << endl;
		} else if (a_flag && b_flag) {
			cout << "-" << Get_sum(s1, s2, length) << endl;

			if (b.length() > a.length() || (a.length() == b.length() && b >= a)) cout << Get_diff(s2, s1, length) << endl; // b >= a
			else cout << "-" << Get_diff(s1, s2, length) << endl;

			cout << Get_mul(s1, s2, a.length(), b.length()) << endl;
		} else {
			if ((!a_flag) && b_flag) {
				if (a.length() > b.length() || (a.length() == b.length() && a >= b)) // a >= b
					cout << Get_diff(s1, s2, length) << endl;
				else cout << "-" << Get_diff(s2, s1, length) << endl;

				cout << Get_sum(s1, s2, length) << endl;
			} else {
				if (b.length() > a.length() || (a.length() == b.length() && b >= a)) cout << Get_diff(s2, s1, length) << endl; // b >= a
				else cout << "-" << Get_diff(s1, s2, length) << endl;

				cout << "-" << Get_sum(s1, s2, length) << endl;
			}
			cout << "-" << Get_mul(s1, s2, a.length(), b.length()) << endl;
		}
	}
	return 0;
}