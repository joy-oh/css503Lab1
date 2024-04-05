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
        pid_t pidL, pidR, parent;
        pids.push(getpid());
        parent = getpid();
       // fork a left child
        pidL = fork();
        if (pidL > 0) {//parent
            // cout << "inside parent process of the left child " << getpid() << '\n';
            wait(NULL);//waif for left child

            //fork a right child
            pidR = fork();
            if (pidR > 0) {//parent
                // cout << "inside parent process of the right child " << getpid() << '\n';
                wait(NULL);
                exit(0);
            }
            else if (pidR < 0) {
                fprintf (stderr, "Right Fork Failed");
                exit (1);
            }
            // else {//right child
            //     recursive_creation(leaves/2);
            // }
        }
        else if (pidL < 0) {
            fprintf (stderr, "Left Fork Failed");
            exit (1);
        }
        // else {//left child
        //     recursive_creation(leaves/2 + 1);
        // }
        if (pidL == 0 && leaves % 2 != 0){
            recursive_creation(leaves/2 + 1);
        }
        if (pidR == 0 && leaves % 2 != 0){
            recursive_creation(leaves/2);
        }
        else {
            recursive_creation(leaves/2);
        }


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
