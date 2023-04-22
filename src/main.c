#include "charstring.h"
#include <stdio.h>

typedef String(32) JSON;
JSON json = {};

int main() {
  String(8) str = Literal("val");
  strappf(str, ",word,key");


  strsub(json, str, .after = 'w', .until = '?');
  strappf(json, ":{%s}", str.c_str);

  return 0;
}