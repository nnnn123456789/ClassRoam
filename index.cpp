//
//index.cpp  the entry of the program
//

#include <cstdio>
#include <cstdlib>
#include <malloc.h>
#include <cstring>
#include <ctime>

//you should delete it unless you are programming on VC++
#pragma warning(disable:4996)   
#pragma warning(disable:4812)

//to give a location
class location
{
public:
    int x; int y;
    //the nearby point of this
    location left();
    location right();
    location up();
    location down();
};

template<int width, int height>
class _map
{
public:
    void* head;
    //constructor, to open a peroid of memory.
    _map();
    //destructor, to free the memory.
    ~_map();
    //to print the map
    int print();
    //for the range-based. begin function
    char* begin();
    //for the range-based. end function
    char* end();
    //override the operator[]
    char* operator [](int);
    //override the operator[] for location
    char& operator [](location);
    //to initialize the map by a given integer
    int init(int);
};
typedef _map<10, 10> map;




int main()
{
    //time
    int t = 0;
    //sleeptime, if sleeptime is zero, 
    //you can't catch the result clearly because it is too fast.
    int sleeptime = 100;
    map mapa;
    map mapb;
    //the max of the random integers
    int ran_max = 100;
    //randomize
    auto randomize = [] {srand((unsigned)time(0)); return 0; };
    //random function
    auto random = [](int max)
    {
        int ret = rand() % max;
        return ret;
    };
    //to set a new title of the console
    auto title = [](char* ch)
    {
        char* p = new char[87];
        memcpy(p, "title ", 7);
        strcat(p, ch);
        system(p);
        free(p);
        return 0;
    };
    //to clear the console
    auto cls = [] 
    {
        system("cls");
        return 0;
    };
    //to record all the wall of the map
    location wall[44] = {
        {0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8},{0,9},{0,10},{0,11},
        {1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0},
        {11,1},{11,2},{11,3},{11,4},{11,5},{11,6},{11,7},{11,8},{11,9},{11,10},
        {1,11},{2,11},{3,11},{4,11},{5,11},{6,11},{7,11},{8,11},{9,11},{10,11},
        {11,11}};
    //set the mapa into 0
    mapa.init(0);
    //set the current location of the guy
    location locate = { 1,1 };
    mapa[locate] = 1;

    randomize();
    title("Roam");
    while (true) {
        //1,2,3,4 for up, down, left, right.
        static int flag = 1;

        //the location of your aim
        location locaim;

        //to set all elements of mapb into a random integer.
        for (char& x : mapb)
        {
            x = random(ran_max);
        }
        //to set all walls into a integer big enough.
        for (location& loc : wall)
        {
            mapb[loc] = ran_max + 5;
        }

        //to read out the four directions of current place
        int vup = mapb[locate.up()];
        int vdo = mapb[locate.down()];
        int vle = mapb[locate.left()];
        int vri = mapb[locate.right()];
        flag = 0;
        //to get whose random is the minimum
        if (vup <= vdo && vup <= vle && vup <= vri)
            flag = 1;
        else if (vdo <= vup && vdo <= vle && vdo <= vri)
            flag = 2;
        else if (vle <= vup && vle <= vdo && vle <= vri)
            flag = 3;
        else if (vri <= vup && vri <= vdo && vri <= vle)
            flag = 4;

        //locaim is the min direction
        switch (flag)
        {
        case 1:
            locaim = locate.up();
            break;
        case 2:
            locaim = locate.down();
            break;
        case 3:
            locaim = locate.left();
            break;
        case 4:
            locaim = locate.right();
            break;
        default:
            throw(0);
        }

        //don't across the wall please
        ///for the flag of continue
        int con;
        con = 0;
        for (location& loc : wall)
        {
            if (loc.x == locaim.x && loc.y == locaim.y)
                con = 1;
        }
        if (con)
            continue;
        //move the guy
        mapa[locate] = 0;
        mapa[locaim] = 1;
        locate = locaim;
        //clear the console
        if(t)
            cls();

        //time++
        ++t;
        printf("time:\t%3d\n",t);
        mapa.print();
        //to pause for some microseconds
        _sleep(sleeptime);
        //printf("%3d%3d\n", locate.x, locate.y);
        //system("pause>nul");
    }
    return 0;
}



//the realize of the functions
template<int width, int height> 
_map<width, height>::_map<width,height>()
{
    this->head = (char**)malloc((width+1)*(height+1));
}
template<int width, int height>
_map<width, height>::~_map<width, height>()
{
    free(this->head);
}

template<int width, int height>
int _map<width, height>::print()
{
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            if (1 == (*this)[i][j])
                printf("* ");
            else
                printf(". ");
        }
        printf("\n");
    }
    return 0;
}
template<int width, int height>
char * _map<width, height>::begin()
{
    return (char*)this->head;
}
template<int width, int height>
char * _map<width, height>::end()
{
    return (char*)this->head + (width + 1)*(height + 1);
}
template<int width, int height>
char * _map<width, height>::operator[](int x)
{
    return (char*)( (long long)this->head + x * (width + 1));
}
template<int width, int height>
int _map<width, height>::init(int x)
{
    for (char& c : (*this))
    {
        c = (char)x;
    }
    return 0;
}
template<int width, int height>
char & _map<width, height>::operator[](location loc)
{
    return (*this)[loc.x][loc.y];
}
location location::left()
{
    location ret;
    ret.x = this->x - 1;
    ret.y = this->y;
    return ret;
}
location location::right()
{
    location ret;
    ret.x = this->x + 1;
    ret.y = this->y;
    return ret;
}
location location::up()
{
    location ret;
    ret.x = this->x;
    ret.y = this->y - 1;
    return ret;
}
location location::down()
{
    location ret;
    ret.x = this->x;
    ret.y = this->y + 1;
    return ret;
}
