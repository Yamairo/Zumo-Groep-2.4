#ifndef HANDMATIG_H
#define HADNMATIG_H
using namespace std;
/*!Header file*/
class Handmatig {
public:
    Handmatig();
    ~Handmatig();
    void HandmatigeBesturing(char);
private:
  Motor motor;
  char input;
};

#endif