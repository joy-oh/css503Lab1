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

    if (leaves > 1)

    {
        int pidL, pidR, counter = 0;
        pids.push(getpid());
        cout << "parent pid" << getpid() << endl;
       // fork a left child
        pidL = fork();//fork returns twice
        if (pidL > 0) {//parent
            cout << pidL << endl;
            cout << "wait for left child\n";
            wait(NULL);

            //fork a right child
            pidR = fork();

            if (pidR > 0) {//parent
                cout << "wait for right child\n";
                wait(NULL);
            }
        }

        recursive_creation(leaves - 1);
        exit (0);

    }
    else

   { // I'm a leaf process
        while(pids.size() > 0)

       {  // print out a list of my ascendants
            cout << pids.front() << " ";
            pids.pop( );
        }
        cout << getpid() << endl;   // print out myself
        exit(0);
    }

}


int main(int argc, char* argv[])

{
// validate arguments
   if (argc != 2)

   {
       cerr << "usage: lab1 #leaves" << endl;
       return -1;
   }
   int leaves = atoi(argv[1]);
   if ( leaves < 1 )

   {
      cerr << "usage: lab1 #leaves" << endl;
      cerr << "where #leaves >= 1" << endl;
      return -1;
   }
   recursive_creation(leaves);
   return 0;

}
