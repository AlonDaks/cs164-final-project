#include <Array.h>

Array<int> a = Array<int>();
int test = 1;

void doTest() {
  a.append(0);
  a.append(1);
  a.append(2);
  a.append(3);
  a.append(4);
  a.append(5);
  a.append(6);
  a.append(7);
  a.append(8);
  a.append(9);
  Serial.print("After append: ");
  a.print();
  Serial.print("Size of a: ");
  Serial.println(a.size());
  
  Serial.print("Getting a[0]: ");
  Serial.println(a.get(0));
  Serial.print("Getting a[5]: ");
  Serial.println(a.get(5));
  Serial.print("Getting a[9]: ");
  Serial.println(a.get(9));
  
  Serial.print("Removing a[0] (should be 0): ");
  Serial.println(a.remove(0));
  Serial.print("Removing a[2] (should be 3): ");
  Serial.println(a.remove(2));
  Serial.print("Removing a[7] (should be 9): ");
  Serial.println(a.remove(7));
  Serial.print("After remove: ");
  a.print();
  Serial.print("Size of a: ");
  Serial.println(a.size());
  Serial.println();
  
  a.insert(1, 11);
  Serial.println("After inserting 11 at a[1]:");
  a.print();
  Serial.print("Size of a: ");
  Serial.println(a.size());
  Serial.println();
  
  Serial.println("Inserting 12");
  a.insert(a.size(), 12);
  Serial.println("After 12 at a[a.size()]:");
  a.print();
  Serial.print("Size of a: ");
  Serial.println(a.size());
}

void setup() {

}

void loop() {
  delay(2000);
  if (test) {
    doTest();
    test = 0;
  }
}
