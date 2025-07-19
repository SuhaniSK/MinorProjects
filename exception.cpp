#include <iostream>
using namespace std;
class person{
int age;
public:person(int n):age(n){};
void display()
{try {
    
    if (age >= 18) {
      cout << "Access granted - you are old enough.";
    } else {
      throw (age);
    }
  }
  catch (int myNum) {
    cout << "Access denied - You must be at least 18 years old.\n";
    cout << "Age is: " << myNum;  
  }}};

int main() {
  person p(40);
  p.display();
  
  return 0;
}
