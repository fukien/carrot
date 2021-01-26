# CarrotSQL

A simple implementation of database system.

Recommended code debugging on Linux and Code::Blocks-16.01.

## Getting Started

### Requirements

We recommand to build the project on Ubuntu(Version >= 16.04) with Code::Blocks-16.01. You may also need to install the following tools:
```
sudo apt install flex bison build-essential
sudo apt install glibc-doc
sudo apt install manpages-posix-dev
```

### Usage
To run CarrotSQL, you need to change directory to dbms/, and make new directory as a workspace for the project (e.g., mkdir workspace).

Open the project in Code::Blocks
  
We support following SQL operations:  
  
&emsp;create table (create table XXX())  

&emsp;drop table (drop table XXX)  

&emsp;insert (insert into XXX values())  

&emsp;delete (delete * from XXX;  delete from XXX where)  

&emsp;update (update XXX set where )  

&emsp;select   

&emsp;multiple tables join  

P.S. select count(\*) and limit are supported.   


### Authors

- [Huang Wentao](https://github.com/fukien)
- [Han Han](https://github.com/hagen666)
- [Shao Mingrui](https://github.com/crazyxuehu)
- [Guan Hua](https://github.com/GH1995)
- [Han Xueran](https://github.com/lemontreehxr)
