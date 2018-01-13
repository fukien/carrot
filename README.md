# CarrotSQL

A simple implementation of database system.

Recommended debuging the code on Linux and code::blocks16.01.

## Getting Started

### Prerequisites

We recommand to build the project on Ubuntu(Version >= 16.04). There is what tings you need to install:
```
sudo apt install flex bison build-essential
```

### Usage
To run CarrotSQL, you need to change directory to bin/Debug/,  
&emsprun the command ./dbms.  
We support following SQL:  
&emspcreate table (create table XXX())  
&emspdrop table (drop table XXX)  
&emspinsert (insert into XXX values())  
&emspdelete (delete * from XXX;  delete from XXX where)  
&emspupdate (update XXX set where )  
&emspselect   
&emspmultiple table join  
P.S. select count(\*) and limit are supported.   


### Authors

- [Huang Wentao](https://github.com/huangwentao0831)
- [Han Han](https://github.com/hagen666)
- [Guan Hua](https://github.com/GH1995)
- [Shao Mingrui](https://github.com/crazyxuehu)
- [Han Xueran](https://github.com/lemontreehxr)
