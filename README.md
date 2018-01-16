# CarrotSQL

A simple implementation of database system.

Recommended debuging the code on Linux and code::blocks16.01.

## Getting Started

### Prerequisites

We recommand to build the project on Ubuntu(Version >= 16.04). This is what you need to install:
```
sudo apt install flex bison build-essential
```

### Usage
To run CarrotSQL, you need to change directory to bin/Debug/,  
&emsp;run the command ./dbms.  
  
We support following SQL:  
  
&emsp;create table (create table XXX())  
&emsp;drop table (drop table XXX)  
&emsp;insert (insert into XXX values())  
&emsp;delete (delete * from XXX;  delete from XXX where)  
&emsp;update (update XXX set where )  
&emsp;select   
&emsp;multiple table join  
P.S. select count(\*) and limit are supported.   


### Authors

- [Huang Wentao](https://github.com/huangwentao0831)
- [Han Han](https://github.com/hagen666)
- [Guan Hua](https://github.com/GH1995)
- [Shao Mingrui](https://github.com/crazyxuehu)
- [Han Xueran](https://github.com/lemontreehxr)
