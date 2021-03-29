#include "top.hpp"

void LOD(ap_uint<8> a, ap_uint<3> &l) {
#pragma HLS INLINE off
	if (a[7] == 1) {
		l = 7;
		return;
	}
	if (a[6] == 1) {
		l = 6;
		return;
	}
	if (a[5] == 1) {
		l = 5;
		return;
	}
	if (a[4] == 1) {
		l = 4;
		return;
	}
	if (a[3] == 1) {
		l = 3;
		return;
	}
	if (a[2] == 1) {
		l = 2;
		return;
	}
	if (a[1] == 1) {
		l = 1;
		return;
	}
	l = 0;
	return;
}

void LOD16(ap_uint<16> a,ap_uint<4> &l){
#pragma HLS INLINE off

	if (a[15] == 1) {
		l = 15;
		return;
	}
	if (a[14] == 1) {
		l = 14;
		return;
	}
	if (a[13] == 1) {
		l = 13;
		return;
	}
	if (a[12] == 1) {
		l = 12;
		return;
	}
	if (a[11] == 1) {
		l = 11;
		return;
	}
	if (a[10] == 1) {
		l = 10;
		return;
	}
	if (a[9] == 1) {
		l = 9;
		return;
	}
	if (a[8] == 1) {
		l = 8;
		return;
	}
	if (a[7] == 1) {
		l = 7;
		return;
	}
	if (a[6] == 1) {
		l = 6;
		return;
	}
	if (a[5] == 1) {
		l = 5;
		return;
	}
	if (a[4] == 1) {
		l = 4;
		return;
	}
	if (a[3] == 1) {
		l = 3;
		return;
	}
	if (a[2] == 1) {
		l = 2;
		return;
	}
	if (a[1] == 1) {
		l = 1;
		return;
	}
	l = 0;
	return;
}

void getFraction(ap_uint<8> a, ap_uint<3> lod, ap_ufixed<16,8> &x) {
#pragma HLS INLINE off
	x = ((ap_ufixed<16,8>)a) >> lod;
	x -=1;
}

void getFraction16(ap_uint<16> a, ap_uint<4> lod, ap_ufixed<32,16> &x) {
#pragma HLS INLINE off
	x = ((ap_ufixed<32,16>)a) >> lod;
	x -=1;
}

void mitchel_mul(ap_uint<8> a, ap_uint<8> b, ap_uint<16> &c) {
#pragma HLS INTERFACE ap_ctrl_none port=return

	ap_uint<3> k1, k2;
	LOD(a, k1);
	LOD(b, k2);

	ap_uint<4> K = k1 + k2;

	ap_ufixed<16,8> x1;
	ap_ufixed<16,8> x2;

	getFraction(a, k1, x1);
	getFraction(b, k2, x2);

	ap_ufixed<16+8,8+8> sum = x1 + x2;


	if (sum<1) {
		sum+=1;
		sum = sum << K;
	}else{
		sum = sum<< (K+1);
	}

	c = (ap_uint<16>)sum;

}

void mitchel_mul(ap_uint<16> a, ap_uint<16> b, ap_uint<32> &c) {
#pragma HLS INTERFACE ap_ctrl_none port=return

	static const int N = 16;
	static const int N_LOD = 4;

	ap_uint<N_LOD> k1, k2;
	LOD16(a, k1);
	LOD16(b, k2);

	ap_uint<N_LOD+1> K = k1 + k2;

	ap_ufixed<N*2,N> x1;
	ap_ufixed<N*2,N> x2;

	getFraction16(a, k1, x1);
	getFraction16(b, k2, x2);

	ap_ufixed<N*2,N> sum = x1 + x2;

	if (sum<1) {
		sum+=1;
		sum = sum << K;
	}else{
		sum = sum<< (K+1);
	}
	c = (ap_uint<N*2>)sum;
}

void mitchel_mul(ap_int<16> a, ap_int<16> b, ap_int<32> &c){
	static const int N = 16;
	static const int N_LOD = 4;

	if (a==1){
		c = (ap_int<N*2>)b;
		return;
	}
	if (b==1){
		c = (ap_int<N*2>)a;
		return;
	}

	bool sgn1 = a.get_bit(N-1);
	bool sgn2 = b.get_bit(N-1);

	if(sgn1){
		a = ~a+1;
	}
	if(sgn2){
		b = ~b+1;
	}

	ap_uint<N_LOD> k1, k2;
	LOD16(a, k1);
	LOD16(b, k2);

	ap_uint<N_LOD+1> K = k1 + k2;

	ap_ufixed<N*2,N> x1;
	ap_ufixed<N*2,N> x2;

	getFraction16(a, k1, x1);
	getFraction16(b, k2, x2);

	ap_ufixed<N*3,N*2> sum = x1 + x2;

	if (sum<1) {
		sum+=1;
		sum = sum << K;
	}else{
		sum = sum<< (K+1);
	}

	ap_int<N*2> tmp = (ap_int<N*2>)sum;
	if( sgn1 ==1 xor sgn2==1){
		tmp = ~tmp+1;
	}
	c = tmp;
}

void mitchel_mul(ap_int<8> a, ap_int<8> b, ap_int<16> &c){
	static const int N = 8;
	static const int N_LOD = 3;

	if (a==1){
		c = (ap_int<N*2>)b;
		return;
	}
	if (b==1){
		c = (ap_int<N*2>)a;
		return;
	}

	bool sgn1 = a.get_bit(N-1);
	bool sgn2 = b.get_bit(N-1);

	if(sgn1){
		a = ~a+1;
	}
	if(sgn2){
		b = ~b+1;
	}

	ap_uint<N_LOD> k1, k2;
	LOD(a, k1);
	LOD(b, k2);

	ap_uint<N_LOD+1> K = k1 + k2;

	ap_ufixed<N*2,N> x1;
	ap_ufixed<N*2,N> x2;

	getFraction(a, k1, x1);
	getFraction(b, k2, x2);

	ap_ufixed<N*3,N*2> sum = x1 + x2;

	if (sum<1) {
		sum+=1;
		sum = sum << K;
	}else{
		sum = sum<< (K+1);
	}

	ap_int<N*2> tmp = (ap_int<N*2>)sum;
	if( sgn1 ==1 xor sgn2==1){
		tmp = ~tmp+1;
	}
	c = tmp;
}
