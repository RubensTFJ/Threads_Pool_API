This Library API is a completely automatic and easy way to deal with thread pools. The Pool size is easily changeable in the header as well as how fast the threads check themselves for tasks.  

![image](https://github.com/RubensTFJ/Threads_Pool_API/assets/89268663/3b190168-a5db-46fb-bb47-d68d9052be50)

Like you see in the image to initialize the Thread Pool all you to do is call threads()->start(), that function call will handle all the necessary setup for the Pool.

After proper initialization, to use the Thread Pool you will call threads()->deploy(). deploy() recieves a structure called t_task, argument order is important: 
The first argument is the function you wish one thread to execute, the remaining elements are the arguments said function will recieve. 
(If the entire Pool is occupied, the main thread will be stuck passing the task until a thread is available).
Important to note: <\br>
  - The function passed in deploy() DOES NOT need to match 5 arguments, it can recieve anything from 0 to 5;
  - You can pass any function as long as it recieves less than 6 arguments, otherwise you will have to change the t_task structure in the header.
  - You can declare a t_task structure and manually fill it's members and then pass it to deploy(), but I highly recommend using a compound literal like the Example in the image.
  - After deploying a task the main thread WILL continue normally. It will not wait for the task to be finished unless the wait() ios called.

After deploying one or many tasks, you can choose to wait for the Threads to end their tasks before going foward, by calling threads()->wait().

And finally, when you dont need them anymore you can call threads()->end(), and this call will release any and all resources used to manage the threads. (This call gets stuck if any thread is still running a task).
