#include <iostream>

using namespace std;

class Thing {
private:
  static int total;
  string name;


public:
  static int count;
  int value;

  int get_total() {
    return total;
  }
  void set_total(int t) {
    total = t;
  }

  string get_name() {
    return name;
  }
  void set_name(string n) {
    name = n;
  }

  void print();
};

void Thing::print() {
  cout << "Non-Static" << endl;
  cout << "Name: " << name << " address " << &name << endl;
  cout << "Value: " << value << " address " << &value << endl;
  cout << "Static" << endl;
  cout << "Count: " << count << " address " << &count << endl;
  cout << "Total: " << total << " address " << &total << endl;

}

int Thing::count = 0;
int Thing::total = 0;

int main() {
  Thing t1;
  t1.set_name("t1");
  t1.set_total(1);
  t1.value = 1;

  Thing t2;
  t2.set_name("t2");
  t2.set_total(2);
  t2.value = 2;
  
  t1.print();
  t2.print();

  cout << "memory addresses of non-static members vary between objects" << endl;
  cout << "memory addresses of static members are the same between objects" << endl;
  cout << "static members are shared between objects" << endl;
  return 0;


}
