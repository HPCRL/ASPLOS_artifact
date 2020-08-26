#pragma once
#include "UkrUtils.h"
namespace ukrgen {
struct Avx2Set {
  static map<int, string> fmadd;
  static map<int, string> vxor;
  static map<int, string> vmova;
  static map<int, string> vmovu;
  static map<int, string> bcast_elem;
  static map<int, string> vadd;
  static map<int, string> vmul;
  static map<int, string> vmovlo;
  static map<int, string> vmovhi;
  static map<int, string> vunpacklo;
  static map<int, string> vunpackhi;
  static map<int, string> vshuffle;
  static map<int, string> vextractf128;
  static map<int, string> vmovss;

  static string test;
  static string cmp;
  static string je;
  static string jne;
  static string jz;
  static string jnz;
  static string rxor;
  static string add;
  static string sub;
  static string mov;
  static string prefetchR;
  static string prefetchW;
};



} // namespace ukrgen
