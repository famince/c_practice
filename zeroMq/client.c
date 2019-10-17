#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
  printf ("connecting to hello world server…\n");
  void *context = zmq_ctx_new ();
  void *requester = zmq_socket (context, zmq_req);
  zmq_connect (requester, "tcp://localhost:5555");
  int request_nbr;
  for (request_nbr = 0; request_nbr != 10; request_nbr++) {
    char buffer [10];
    printf ("sending hello %d…\n", request_nbr);
    zmq_send (requester, "hello", 5, 0);
    zmq_recv (requester, buffer, 10, 0);
    printf ("received world %d\n", request_nbr);
  }
  zmq_close (requester);
  zmq_ctx_destroy (context);
  return 0;
}
