# LightCppConfigParser
A lighter simpler alternative to json files and jsoncpp.
## FORMAT
  
  key0: value0
  
  key1: value1, value2, value3, ...
  
  key2: 12.345678
  
  key3: 38, 23, 12
  
## FORMAT specifications
  double slash '//' means comment till end of line.
  
  spaces are ignored EVEN LIKE THIS: "NO SPACE HERE".
  
  tabs aswell.
  
  empty lines are ignored.

The (#define DELIM) delimeter is used for list content. Changeable.

See .h for value types.  


## Compile Demo (gcc):
  g++ Demo.cpp ConfigParser.cpp
