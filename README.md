This Library API is a completely automatic and easy way to deal with thread pools. The Pool size is easily changeable in the header as well as how fast the Threads check themselves for tasks.  


![image](https://github.com/RubensTFJ/Threads_Pool_API/assets/89268663/3b190168-a5db-46fb-bb47-d68d9052be50)

As shown in the image,  initializing the thread pool is as simple as calling threads()->start(), This function call handles all the necessary setup for the pool.

After proper initialization, to use the Thread Pool you will call `threads()->deploy()`. The `deploy()` function takes a structure called `t_task`, and the order of arguments is crucial. The first argument is the function you want a thread to execute, followed by the arguments that this function will receive. If the entire Pool is occupied, the main thread will be blocked until a thread becomes available to handle the task.
Important to note:
  - The function passed to `deploy()` does not need to have exactly 5 arguments; it can receive anything from 0 to 5 arguments;
  - You can pass any function as long as it receives 5 or fewer arguments. To increase the number of arguments, you need to modify the `t_task` structure in the header;
  - You can declare a `t_task` structure, manually fill its members, and then pass it to `deploy()`, but I highly recommend using a compound literal, as shown in the example image;
  - After deploying a task, the main thread will continue normally; it will not wait for the task to finish unless the `wait()` function is called.

After deploying one or many tasks, you can choose to wait for the ENTIRE Thread Pool to end their tasks before going foward, by calling `threads()->wait()`.

And finally, when you dont need them anymore you can call `threads()->end()`, and this call will release any and all resources used to manage the threads. (Please note that this call will be stuck while any Thread is still running a task).
