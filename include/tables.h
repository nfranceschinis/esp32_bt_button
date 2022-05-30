bool patterns [3][8] ={
    {1,0,1,0,1,0,1,0},      //Waiting for connection
    {1,1,0,0,1,1,0,0},      //Configuration mode
    {1,1,1,1,0,0,0,0}       //Low battery
};

struct message {
    char command;
    char message;
    char payload;
};