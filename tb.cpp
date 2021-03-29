#include "top.hpp"
#include <math.h>
#include <fstream>

using namespace std;

int test_LOD8(){
	ap_uint<8> a = 128;
	ap_uint<3> l = 0;
	int result = 7;
	for(int i=128;i>=2;i>>=1){
		a = i;
		l = 0;
		LOD(a, l);
		if (l.to_int() != result) {
			std::cout << "ERRRO expected "<<result<<" get " << l.to_int() << "\n";
			return 1;
		}
		a = i + 1;
		l = 0;
		LOD(a, l);
		if (l.to_int() != result) {
			std::cout << "ERRRO expected "<<result<<" get " << l.to_int() << "\n";
			return 1;
		}
		result-=1;
	}
	return 0;
}

int test_LOD16(){
	ap_uint<16> a = 32768;
	ap_uint<4> l = 0;
	int result = 15;
	for(int i=32768;i>=2;i>>=1){
		a = i;
		l = 0;
		LOD16(a, l);
		if (l.to_int() != result) {
			std::cout << "ERRRO expected "<<result<<" get " << l.to_int() << "\n";
			return 1;
		}
		a = i + 1;
		l = 0;
		LOD16(a, l);
		if (l.to_int() != result) {
			std::cout << "ERRRO expected "<<result<<" get " << l.to_int() << "\n";
			return 1;
		}
		result-=1;
	}
	return 0;
}



int test_mitchell_unsgn16() {
	ap_uint<16> a;
	ap_uint<16> b;
	ap_uint<32> c;
	ofstream results;
	results.open("unsgn16.txt");
	for (int i = -2048; i <= 2048; i++) {
		for (int j = -2048; j <=2048; j++) {
			a = i;
			b = j;
			mitchel_mul(a, b, c);
			int accurate = i*j;
			int absErr = accurate-c.to_int();
			float err = abs(((float)absErr/(float)accurate)*100);
			if (err >12){
				std::cout << "\tERROR to big "<<err<<"\n";
				return 0;
			}
			if (j!= 2048)
				std::cout << err << ";";
			else
				std::cout << err <<"\n";
		}
	}
	results.close();
	return 0;
}

int test_mitchell_unsgn8() {
	ap_uint<8> a;
	ap_uint<8> b;
	ap_uint<16> c;

	ofstream results;
	results.open("unsgn8.log");

	for (int i = 0; i <= 255; i++) {
		for (int j = 0; j <=255; j++) {
			a = i;
			b = j;
			mitchel_mul(a, b, c);
			int accurate = i*j;
			int absErr = accurate-c.to_int();
			float err = abs(((float)absErr/(float)accurate)*100);
			if (isinf(err))
				err = 0;
			if (err >12){
				std::cout << "\tERROR to big "<<err<<"\n";
				return 0;
			}
			if (j!= 255)
				results << err << ";";
			else
				results << err <<"\n";
		}
	}
	results.close();
	return 0;
}

int test_mitchell_sgn8() {
	ap_int<8> a;
	ap_int<8> b;
	ap_int<16> c;
	ofstream results;
	results.open("sgn8.log");
	for (int i = -127; i <= 127; i++) {
		for (int j = -127; j <=127; j++) {
			a = i;
			b = j;
			mitchel_mul(a, b, c);
			int accurate = i*j;
			int absErr = accurate-c.to_int();
			float err = abs(((float)absErr/(float)accurate)*100);
			if (isinf(err))
				err = 0;

			if (err >12){
				std::cout << "\tERROR to big "<<err<<"\n";
				return 0;
			}
			if (j!= 127)
				results << err << ";";
			else
				results << err <<"\n";
		}
	}
	results.close();
	return 0;
}


int main() {

	int res = test_mitchell_sgn8();
	if (res != 0)
		return res;
	res = test_mitchell_unsgn8();
	if (res != 0)
		return res;

	return res;
}
