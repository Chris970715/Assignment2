

/*
   program:         gkim47_PRG355A.221.A2.cpp
   student name:    Gyubum Kim
   student number:  101492171
   section:         PRG355A (must include the exact course code and section)
   purpose:         solution for PRG355 assignment #2
*/

/* ========== CODE TO PLACE IN YOUR SOURCE FILE FOR SUBMISSION STARTS BELOW ========== */
CompactDisc::CompactDisc()
{
    p = new song [20];
    total = 20;
    current = 0;

    for (int i = 0; i < 20; i++ )
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

    for (int i = 0; i < num; i++ )
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
        return 0;
    }
    else
    {


        p[index].track = x.track;
        p[index].time = x.time;
        strcpy(p[index].title, x.title);
        current = index;



        return 1;
    }

}
void CompactDisc::getSong(struct song * ps)
{

    if(current > 0)
    {

        strcpy(ps -> title, (p + current - 1) -> title);
        ps -> track = (p + current - 1) -> track;
        ps -> time = (p + current - 1) -> time;
        /*
        ps->track = p[current - 1].track;
        ps->time = p[current - 1].time;
        strcpy(ps->title, p[current - 1].title);
         */
    }
    else
    {


        strcpy(ps -> title, (p + current) -> title);
        ps -> track = (p + current) -> track;
        ps -> time = (p + current) -> time;
        /*
        ps->track = p[current + 1].track;
        ps->time = p[current + 1].time;
        strcpy(ps->title, p[current + 1].title);
        */
    }


// error
}

song& CompactDisc::getSong(int pos)
{
    song &reference = p[pos];


    return reference;
}

int CompactDisc::operator+=(struct song copy)
{
    /*
    This operation adds the song structure 'copy' into the array of song
   structures pointed to by 'p' in the class. This is accomplished by copying all of
   the members of the 'copy' structure into the corresponding structure in the
   array 'p' in the CompactDisc.
    */
    if (current == total)
    {

        return 0;
    }
    else
    {
        p[current].time = copy.time;
        p[current].track = copy.track;
        strcpy(p[current].title, copy.title);
        current++;

        return 1;
    }
}
CompactDisc::CompactDisc(const CompactDisc& from) // deep copy constructor
{
    total = from.total;
    current = from.current;
    strcpy(artist, from.artist);

    delete []p;

    p = new song[current];

    for(int i = 0; i < total; i++)
    {

        p[i].track = from.p[i].track;
        p[i].time = from.p[i].time;
        strcpy(p[i].title, from.p[i].title);

    }

}
CompactDisc& CompactDisc::operator=(const CompactDisc &from)
{
    total = from.total;
    current = from.current;
    strcpy(artist, from.artist);

    delete []p;

    p = new song[current];

    for(int i = 0; i < total; i++)
    {

        p[i].track = from.p[i].track;
        p[i].time = from.p[i].time;
        strcpy(p[i].title, from.p[i].title);

    }

    return *this; // send dereferenced value
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