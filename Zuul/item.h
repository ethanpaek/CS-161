#ifndef ITEM_H //if not defined
#define ITEM_H //define

class Item{
 private:
  char* name;
 public:
  Item(const char* someName);
  ~Item();
  char* getName();
};

#endif
