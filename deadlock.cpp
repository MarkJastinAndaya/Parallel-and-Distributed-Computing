#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex m1, m2; // m1 is the pen, m2 is the notebook

void studentAlice() {
    m1.lock(); // STEP 1: Alice grabs the pen! It's hers now.
    cout << "Alice has the pen." << endl;
    
    this_thread::sleep_for(chrono::milliseconds(100)); 
    
    m2.lock(); // STEP 3: Alice tries to grab the notebook... but Bob has it. FREEZE!
    cout << "Alice has the notebook." << endl;
    
    m2.unlock();
    m1.unlock();
}

void studentBob() {
    m2.lock(); // STEP 2: Bob grabs the notebook at the same time!
    cout << "Bob has the notebook." << endl;
    
    this_thread::sleep_for(chrono::milliseconds(100)); 
    
    m1.lock(); // STEP 4: Bob tries to grab the pen... but Alice has it. FREEZE!
    cout << "Bob has the pen." << endl;
    
    m1.unlock();
    m2.unlock();
}

int main() {
    cout << "--- START PREVENTATIVE SOLUTION SIMULATION ---\n";
    cout << "  The program will freeze right after this!\n\n";
    
    thread t1(studentAlice);
    thread t2(studentBob);
    
    t1.join(); 
    t2.join();

    cout << "This line will NEVER be printed!" << endl;
    return 0;
}
