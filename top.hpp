#include "hls_math.h"
#include <cmath>

void LOD(ap_uint<8> a, ap_uint<3> &l);

void LOD16(ap_uint<16> a,ap_uint<4> &l);

void getFraction(ap_uint<8> a, ap_uint<3> lod, ap_ufixed<16,8> &x);

void getFraction16(ap_uint<16> a, ap_uint<4> lod, ap_ufixed<32,16> &x);

void mitchel_mul(ap_uint<8> a, ap_uint<8> b, ap_uint<16> &c);

void mitchel_mul(ap_uint<16> a, ap_uint<16> b, ap_uint<32> &c);

void mitchel_mul(ap_int<16> a, ap_int<16> b, ap_int<32> &c);

void mitchel_mul(ap_int<8> a, ap_int<8> b, ap_int<16> &c);
