// Version 2: Solution (Deadlock Prevention) Version
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex m1, m2; // m1 is the pen, m2 is the notebook

void studentAlice();
void studentBob();

int main() {
    cout << "--- START PREVENTATIVE SOLUTION SIMULATION ---\n" << endl;
    
    thread t1(studentAlice);
    thread t2(studentBob);
    
    t1.join(); // Alice finishes safely!
    t2.join(); // Bob finishes safely right after!

    cout << "\n------------- SIMULATION SUCCESS -------------\n"
         << "Program finished completely without freezing!\n";
    return 0;
}

void studentAlice() {
    // --- SIMULATION START ---
    m1.lock(); // STEP 1: Alice successfully grabs the pen first!
    cout << "Alice has the pen." << endl;
    
    // Alice takes a quick 100ms study break
    this_thread::sleep_for(chrono::milliseconds(100)); 
    
    m2.lock(); // STEP 2: Alice wakes up and grabs the notebook easily (it's free!)
    cout << "Alice has the notebook." << endl;
    
    // STEP 3: Alice finishes her work and puts both items back on the desk
    m2.unlock();
    m1.unlock();
    // Alice is totally done!
}

void studentBob() {
    // --- SIMULATION START ---
    // STEP 1 (Bob waits): Bob tries to grab the pen here...
    // BUT Alice already locked it! So Bob safely pauses right here and waits.
    m1.lock(); 
    
    // STEP 4: Alice put the pen back, so Bob finally wakes up and grabs it!
    cout << "Bob has the pen." << endl;
    
    // Bob takes his 100ms study break
    this_thread::sleep_for(chrono::milliseconds(100)); 
    
    m2.lock(); // STEP 5: Bob grabs the notebook (Alice already put it back too)
    cout << "Bob has the notebook." << endl;
    
    // STEP 6: Bob finishes his work and puts them back
    m2.unlock();
    m1.unlock();
}