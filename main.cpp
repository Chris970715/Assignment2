#define _CRT_SECURE_NO_WARNINGS
// Your solution may ONLY use functions from the following
// included C and C++ library header files.

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;


// You may add your own helper functions or symbolic constants here.
// The member functions below must ALL be correctly coded


struct song {
    char title[121];
    int track;
    float time;
};

class CompactDisc {
    struct song* p;
    char artist[121];
    int total, current;
public:
    CompactDisc();
    CompactDisc(int, const char*);
    int setSong(struct song, int);
    void getSong(struct song*);
    song& getSong(int);
    int operator+=(struct song);
    CompactDisc(const CompactDisc&); // copy constructor
    CompactDisc& operator=(const CompactDisc&);
    ~CompactDisc();
    int getTotal();
    int getCurrent();
    const char* getArtist();
};

void showSong(struct song);
void initSong(struct song*, const char*, int, float);

int main() {
    int i, status;
    char artists[3][41] = { "Styx", "Rush", "Tears For Fears" };
    char stringData[4][41] = { "Pieces Of Eight", "The Camera Eye", "Listen", "Everybody Wants To Rule The World" };
    struct song x1, x2, x3, x4, temp;

    initSong(&x1, stringData[0], 9, 4.44);
    initSong(&x2, stringData[1], 5, 10.58);
    initSong(&x3, stringData[2], 4, 6.48);
    initSong(&x4, stringData[3], 3, 4.10);

    cout << "initialized 4 song structures..." << endl;

    cout << "about to create CompactDiscs d1 and d2..." << endl;
    CompactDisc d1;                  // d1 can contain a total of 20 song structures
    CompactDisc d2(2, artists[2]);   // d2 can contain only 2 song structures
    // each song will have its integer and float members set to 0 and title
    // set to "unknown"
    cout << "created CompactDiscs d1 and d2..." << endl;

    cout << "checking d1.setSong(x3, 0)..." << endl;
    d1.setSong(x3, 0);
    cout << "checking d1.getSong(&temp)..." << endl;
    d1.getSong(&temp);     // temp should be set to: "Listen", 4, 6.48
    showSong(temp);

    cout << "attempting to overfill the d2 CompactDisc..." << endl;
    status = d2 += x1; // OK
    cout << "return from d2 += x1: " << status << endl;
    status = d2 += x2; // OK
    cout << "return from d2 += x2: " << status << endl;
    status = d2 += x3; // this should fail
    cout << "return from d2 += x3: " << status << endl;


    cout << "filling CompactDisc d1 with x1, x2, and x3..." << endl;
    d1 += x1;
    d1.getSong(&temp);     // temp should be set to: "Pieces Of Eight", 9, 4.44
    showSong(temp);

    d1 += x2;
    d1.getSong(&temp);     // temp should be set to: "The Camera Eye", 5, 10.58
    showSong(temp);

    d1 += x3;
    d1.getSong(&temp);     // temp should be set to: "Listen", 4, 6.48
    showSong(temp);

    d1.setSong(x4, 17);    // setting song[17] to: "Everybody Wants to Rule The World", 3, 4.10

    // displaying all songs in CompactDisc d1:
    cout << endl << "displaying all songs in CompactDisc 1..." << endl << endl;
    for (i = 0; i < 20; i++) {
        cout << "index: " << i << " ";
        temp = d1.getSong(i);
        showSong(temp);
    }
    cout << endl << "displaying artist names..." << endl;
    // displaying artists
    cout << "CompactDisc d1 artist: ";
    cout << d1.getArtist() << endl;
    cout << "CompactDisc d2 artist: ";
    cout << d2.getArtist() << endl;

    return 0;
}

void showSong(struct song x) {
    cout << "song title: " << x.title << " track: " << x.track <<
         " time: " << x.time << endl;
}

void initSong(struct song* pp, const char* s, int trk, float tm) {
    strcpy(pp->title, s);
    pp->track = trk;
    pp->time = tm;
}


/* ========== CODE TO PLACE IN YOUR SOURCE FILE FOR SUBMISSION STARTS BELOW ========== */
CompactDisc::CompactDisc()
{
    p = new song [20];
    total = 20;
    current = 0;

    for (int i = 0; i < 20; i++)
    {
        p[i].track = 0;
        p[i].time = 0.0;
        strcpy(p[i].title, "not-available");
    }

    strcpy(artist, "unknown");
}
CompactDisc::CompactDisc(int num, const char* name)
{
    p = new song[num];

    total = num;
    current = 0;

    for (int i = 0; i < 20; i++)
    {
        p[i].track = 0;
        p[i].time = 0.0;
        strcpy(p[i].title, "not-available");
    }

    strcpy(artist, name);

}
int CompactDisc::setSong(struct song x, int index)
{
    if (index < 0 || index > total)
    {
        return false;
    }
    else
    {
        p[index].time = x.time;
        p[index].track = x.track;
        strcpy(p[index].title, x.title);
        current = index + 1;


        return  true;
    }
}
void CompactDisc::getSong(struct song * ps)
{
    ps->track = (p[current - 1].track);
    ps->time = (p[current - 1].time);
    strcpy(ps->title, (p[current - 1]).title);
}
song& CompactDisc::getSong(int pos)
{
    song& reference = p[pos];

    return  reference;

}
int CompactDisc::operator+=(struct song copy)
{
    /*
    This operation adds the song structure 'copy' into the array of song
   structures pointed to by 'p' in the class. This is accomplished by copying all of
   the members of the 'copy' structure into the corresponding structure in the
   array 'p' in the CompactDisc.
    */
    if(current == total)
    {
        return false;
    }
    else
    {
        p[current].track = copy.track;
        p[current].time = copy.time;

        strcpy(p[current].title, copy.title);
        current++;
        return true;
    }

}
CompactDisc::CompactDisc(const CompactDisc& copied)
{
    int current_total, current_current;

    current_total = copied.total;
    current_current = copied.current;

    delete []p;
    //deep copy constructor
    p = new song[current_total];

    for (int i = 0; i < current_total; i++)
    {
        p[i] = copied.p[i];
    }

    strcpy(artist, copied.artist);


}
CompactDisc& CompactDisc::operator=(const CompactDisc &from)
{
    int from_total, from_current;

    from_total = from.total;
    from_current = from.current;
    delete []p;

    p = new song[from_total];

    for (int i = 0; i < from_total; i++)
    {
        p[i] = from.p[i];
    }

    strcpy(artist, from.artist);
    return *this;
}
CompactDisc::~CompactDisc()
{
    delete []p;
}
int CompactDisc::getTotal()
{
    return total;
}
int CompactDisc::getCurrent()
{
    return (current - 1);
}
const char* CompactDisc::getArtist()
{
    return artist;
}