#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;
const int maxN = 2 << 17;

struct Node {
    int time;
    bool valid;
    unsigned int tag;
};

unsigned int addr; // address
int c_size, b_size; // cache & block size;
int block; // c_size / b_size
int assoc, r_algor; // associativity & replace algorithm
int correct, total; // hit & total count
Node* cache[maxN];

int main(int argc, char* argv[])
{
    unsigned int tag;
    int index, offset, line, tmp, pass = 0; // pass use to do LRU
    ifstream ifp(argv[1], ios::in);
    ofstream ofp(argv[2], ios::out);
    ifp >> c_size >> b_size >> assoc >> r_algor >> tmp;

    block = c_size / b_size; // calculation block
    offset = log(b_size) / log(2);

    for (int i = 0; i < maxN; i++)
        cache[i] = (Node*)malloc(sizeof(Node));

    if (assoc == 0) {
        index = log(block) / log(2);
        tag = 32 - index - offset;

        while (ifp >> addr) {
            total += 1;
            line = ((addr << tag) >> (tag + offset));
            tmp = addr >> (index + offset);

            if (cache[line]->valid == 0) {
                cache[line]->valid = 1, cache[line]->tag = tmp;
                ofp << -1 << '\n';
            } else {
                if (cache[line]->tag == tmp) {
                    ofp << -1 << '\n';
                    correct += 1;
                } else {
                    ofp << cache[line]->tag << '\n';
                    cache[line]->tag = tmp;
                }
            }
        }
    } else if (assoc == 1) {
        index = log(block / 4) / log(2);
        tag = 32 - index - offset;

        while (ifp >> addr) {
            int time = 0x3f3f3f3f, record;
            bool validate = true;

            total += 1, pass += 1;
            line = ((addr << tag) >> (tag + offset));
            tmp = addr >> (index + offset);

            for (int i = 0; i < 4; i++) {
                if (cache[(line << 2) + i]->valid == 1 && tmp == cache[(line << 2) + i]->tag) {
                    if (r_algor == 1)
                        cache[(line << 2) + i]->time = pass;
                    ofp << -1 << '\n';
                    correct += 1, validate = false;
                    break;
                }
            }

            if (validate) {
                for (int i = 0; i < 4; i++) {
                    if (cache[(line << 2) + i]->valid == 0) {
                        cache[(line << 2) + i]->valid = 1;
                        cache[(line << 2) + i]->tag = tmp;
                        cache[(line << 2) + i]->time = pass;
                        ofp << -1 << '\n';
                        validate = false;
                        break;
                    }
                }
            }

            if (validate) {
                for (int i = 0; i < 4; i++) {
                    if (time > cache[(line << 2) + i]->time) {
                        time = cache[(line << 2) + i]->time;
                        record = (line << 2) + i;
                    }
                }
                ofp << cache[record]->tag << '\n';
                cache[record]->time = pass;
                cache[record]->tag = tmp;
            }
        }
    } else {
        tag = 32 - offset;

        while (ifp >> addr) {
            int time = 0x3f3f3f3f, record;
            bool validate = true;

            total += 1, pass += 1;
            tmp = addr >> offset;

            for (int i = 0; i < block; i++) {
                if (cache[i]->valid == 1 && tmp == cache[i]->tag) {
                    if (r_algor == 1)
                        cache[i]->time = pass;
                    ofp << -1 << '\n';
                    correct += 1;
                    validate = false;
                    break;
                }
            }

            if (validate) {
                for (int i = 0; i < block; i++) {
                    if (cache[i]->valid == 0) {
                        cache[i]->valid = 1;
                        cache[i]->tag = tmp;
                        cache[i]->time = pass;
                        ofp << -1 << '\n';
                        validate = false;
                        break;
                    }
                }
            }

            if (validate) {
                for (int i = 0; i < block; i++) {
                    if (time > cache[i]->time) {
                        time = cache[i]->time;
                        record = i;
                    }
                }
                ofp << cache[record]->tag << '\n';
                cache[record]->time = pass;
                cache[record]->tag = tmp;
            }
        }
    }
    cout << "Miss rate = " << ((float)(total - correct) / (float)(total)) << '\n';
    ofp << "Miss rate = " << ((float)(total - correct) / (float)(total)) << '\n';
}