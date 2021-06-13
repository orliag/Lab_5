#include <iostream>

using namespace std;

class rbuf {
private:
    int n = 8;
    int head = 0, tail = 0;
    int avail = 0;
    int* byte = new int[0];

    void inc_h() {
        if (head == n - 1) {
            head = 0;
        }
        else {
            head++;
        }
    }
    void inc_t() {
        if (tail == n - 1) {
            tail = 0;
        }
        else {
            tail++;
        }
    }
    void dec_h() {
        if (head == 0) {
            head = n - 1;
        }
        else {
            head--;
        }
    }
    void dec_t() {
        if (tail == 0) {
            tail = n - 1;
        }
        else {
            tail--;
        }
    }
public:
    rbuf() {
        n = 8;
        byte = new int [n];
    }

    rbuf(int size) {
        if (n > 0) {
            n = size;
            byte = new int[n];
        }
    }

    void put_s(int b) {
        if (avail != n) {
            if (tail != 0) {
                byte[tail - 1] = b;
            }
            else {
                byte[n - 1] = b;
            }
            dec_t();
            avail++;
        }
        else {
            change(n*2);
            put_s(b);
        }
    }
    void put_e(int b) {
        if (avail != n) {
            byte[head] = b;
            inc_h();
            avail++;
        }
        else {
            change(n*2);
            put_e(b);
        }
        
    }
    void pop_s() {
        if (avail != 0) {
            inc_t();
            avail--;
        }
    }
    void pop_e() {
        if (avail != 0) {
            dec_h();
            avail--;
        }
    }
    int& get_s() {
        return byte[tail];
    }
    int& get_e() {
        if (head != 0) {
            return byte[head - 1];
        }
        else {
            return byte[n - 1];
        }
    }
    int& get_i(int i) {
        return byte[(tail+i)%n];
    }

    void stat() {
        for (int i = tail; i < avail + tail; i++) {
            cout << i % n << "=>" << byte[i % n] << " ";
        }cout << endl;
    }

    void change(int size) {
        int* buf = new int[size];
        if (avail < size) {
            for (int i = 0; i < avail; i++) {
                buf[i] = byte[(tail + i) % n];
            }
            tail = 0; head = avail%size; n = size;
            delete[] byte;
            byte = buf;
        }
        else {
            for (int i = 0; i < size; i++) {
                buf[i] = byte[(tail + i + avail - size)%n];
            }
            tail = 0; head = 0; n = size; avail = size;
            delete[] byte;
            byte = buf;
        }
    }

    ~rbuf() {
        delete[] byte;
    }
};

int main()
{
    rbuf ring(4);

    ring.put_e(3);
    ring.stat();

    ring.put_e(5);
    ring.stat();
    
    ring.put_e(8);
    ring.stat();
    
    ring.put_e(11);
    ring.stat();

    ring.pop_s();
    ring.stat();

    ring.put_s(2);
    ring.stat();

    ring.pop_e();
    ring.put_e(10);
    ring.stat();


    ring.change(8);
    ring.stat();

    ring.put_e(10);
    ring.stat();
    ring.put_e(10);
    ring.stat();
    ring.put_e(10);
    ring.stat();
    ring.put_e(10);
    ring.stat();
    ring.change(6);
    ring.stat();
    ring.put_e(7);
    ring.stat();
    ring.put_s(7);
    ring.stat();



    return 0;
}
