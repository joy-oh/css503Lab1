#include <iostream>    // cout, cerr
#include <queue>       // stl queue
#include <sys/types.h> // fork, wait
#include <sys/wait.h>  // wait
#include <unistd.h>    // fork
#include <stdlib.h>    // for exit

using namespace std;

queue<int> pids;      // stores a list of processes from the parent to a leaf process

void recursive_creation(int leaves)
{
    pid_t pleft, pright;
    if (leaves > 1)
    {
        pids.push(getpid());
        // fork left
        pleft = fork();
        if (pleft < 0) // error handler
        {
            fprintf(stderr, "Fork Failed");
            exit(EXIT_FAILURE);
        }
        if (pleft == 0) // process is left fork
        {
            // recurse with half of the leaves (rounded up)
            recursive_creation(leaves/2 + leaves%2);
        }
        else // process is parent
        {
            wait(NULL); // wait for termination of left fork
            // fork right
            pright = fork();
            if (pright < 0)
            {
                fprintf(stderr, "Fork Failed");
                exit(EXIT_FAILURE);
            }
            else if (pright == 0) //process is right fork
            {       
                // recurse with half of the leaves (rounded down)
                recursive_creation(leaves/2);
            }
            wait(NULL);
        }
        exit(0);
    }
    else
    {
        while (pids.size() > 0)
        {
            cout << pids.front() << ' ';
            pids.pop();
        }
        cout << getpid() << endl;
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "usage: lab1 #leaves" << endl;
        return -1;
    }
    int leaves = atoi(argv[1]);
    if (leaves < 1)
    {
        cerr << "usage: lab1 #leaves" << endl;
        cerr << "where #leaves >= 1" << endl;
        return -1;
    }
    recursive_creation(leaves);
    return 0;
}